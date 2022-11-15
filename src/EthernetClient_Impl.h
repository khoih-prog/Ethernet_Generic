/****************************************************************************************************************************
  EthernetClient_Impl.h - Driver for W5x00

  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries

  Based on and modified from

  1) Ethernet Library         https://github.com/arduino-libraries/Ethernet
  2) EthernetLarge Library    https://github.com/OPEnSLab-OSU/EthernetLarge
  3) Ethernet2 Library        https://github.com/adafruit/Ethernet2
  4) Ethernet3 Library        https://github.com/sstaub/Ethernet3

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer

  Copyright 2018 Paul Stoffregen

  Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to the following
  conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  Version: 2.7.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.0.0   K Hoang      31/03/2022 Initial porting and coding to support SPI2, debug, h-only library
  2.0.1   K Hoang      08/04/2022 Add support to SPI1 for RP2040 using arduino-pico core
  2.1.0   K Hoang      22/04/2022 Add support to WIZNet W5100S
  2.2.0   K Hoang      02/05/2022 Add support to custom SPI for any board, such as STM32
  2.3.0   K Hoang      03/05/2022 Add support to custom SPI for RP2040, Portenta_H7, etc. using Arduino-mbed core
  2.3.1   K Hoang      21/05/2022 Add setHostname() and related functions
  2.4.0   K Hoang      31/07/2022 Using raw_address() as default instead of private IPAddress data
  2.4.1   K Hoang      25/08/2022 Auto-select SPI SS/CS pin according to board package
  2.5.0   K Hoang      26/08/2022 Using raw_address() as default only for arduino-pico for compatibility
  2.5.1   K Hoang      01/09/2022 Slow SPI clock for old W5100 shield using SAMD Zero
  2.5.2   K Hoang      06/09/2022 Slow SPI clock only when necessary. Improve support for SAMD21
  2.6.0   K Hoang      11/09/2022 Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  2.6.1   K Hoang      23/09/2022 Fix bug for W5200
  2.6.2   K Hoang      26/10/2022 Add support to Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE using `mbed` or `nRF52` core
  2.7.0   K Hoang      14/11/2022 Fix severe limitation to permit sending larger data than 2/4/8/16K buffer
  2.7.1   K Hoang      15/11/2022 Auto-detect W5x00 and settings to set MAX_SIZE to send
 *****************************************************************************************************************************/

#pragma once

#ifndef ETHERNET_CLIENT_GENERIC_IMPL_H
#define ETHERNET_CLIENT_GENERIC_IMPL_H

#include <Arduino.h>
#include "Ethernet_Generic.hpp"

#include "Dns_Impl.h"

#include "utility/w5100.h"

////////////////////////////////////////

int EthernetClient::connect(const char * host, uint16_t port)
{
  DNSClient dns; // Look up the host first
  IPAddress remote_addr;

  if (_sockindex < MAX_SOCK_NUM)
  {
    if (Ethernet.socketStatus(_sockindex) != SnSR::CLOSED)
    {
      Ethernet.socketDisconnect(_sockindex); // TODO: should we call stop()?
    }

    _sockindex = MAX_SOCK_NUM;
  }

  dns.begin(Ethernet.dnsServerIP());

  if (!dns.getHostByName(host, remote_addr))
    return 0; // TODO: use _timeout

  return connect(remote_addr, port);
}

////////////////////////////////////////

int EthernetClient::connect(IPAddress ip, uint16_t port)
{
  if (_sockindex < MAX_SOCK_NUM)
  {
    if (Ethernet.socketStatus(_sockindex) != SnSR::CLOSED)
    {
      Ethernet.socketDisconnect(_sockindex); // TODO: should we call stop()?
    }

    _sockindex = MAX_SOCK_NUM;
  }

#if defined(ESP8266) || defined(ESP32)

  if (ip == IPAddress((uint32_t)0) || ip == IPAddress(0xFFFFFFFFul))
    return 0;

#else

  if (ip == IPAddress(0ul) || ip == IPAddress(0xFFFFFFFFul))
    return 0;

#endif

  _sockindex = Ethernet.socketBegin(SnMR::TCP, 0);

  if (_sockindex >= MAX_SOCK_NUM)
    return 0;

  Ethernet.socketConnect(_sockindex, rawIPAddress(ip), port);
  uint32_t start = millis();

  while (1)
  {
    uint8_t stat = Ethernet.socketStatus(_sockindex);

    if (stat == SnSR::ESTABLISHED)
      return 1;

    if (stat == SnSR::CLOSE_WAIT)
      return 1;

    if (stat == SnSR::CLOSED)
      return 0;

    if (millis() - start > _timeout)
      break;

    delay(1);
  }

  Ethernet.socketClose(_sockindex);
  _sockindex = MAX_SOCK_NUM;

  return 0;
}

////////////////////////////////////////

int EthernetClient::availableForWrite()
{
  if (_sockindex >= MAX_SOCK_NUM)
    return 0;

  return Ethernet.socketSendAvailable(_sockindex);
}

////////////////////////////////////////

size_t EthernetClient::write(uint8_t b)
{
  return write(&b, 1);
}

////////////////////////////////////////

// KH rewrite to enable chunk-sending for large file

#define ETHERNET_CLIENT_MAX_WRITE_RETRY       100

////////////////////////////////////////

size_t EthernetClient::write(const uint8_t *buf, size_t size)
{
  int written = 0;
  int retry = ETHERNET_CLIENT_MAX_WRITE_RETRY;

  size_t totalBytesSent = 0;
  size_t bytesRemaining = size;

  uint16_t ETHERNET_CLIENT_SEND_MAX_SIZE = W5100.SSIZE;

  ETG_LOGINFO1("EthernetClient::write: chip = ", W5100.getChip());
  ETG_LOGINFO3("EthernetClient::write: size = ", size, ", MAX_SIZE =", ETHERNET_CLIENT_SEND_MAX_SIZE);

  if (_sockindex >= MAX_SOCK_NUM)
    return 0;

  if (size == 0)
  {
    setWriteError();

    ETG_LOGDEBUG("EthernetClient::write: size = 0");

    return 0;
  }

  while (retry)
  {
    written =  Ethernet.socketSend(_sockindex, buf, min(bytesRemaining, (size_t) ETHERNET_CLIENT_SEND_MAX_SIZE) );

    if (written > 0)
    {
      totalBytesSent += written;

      ETG_LOGINFO3("EthernetClient::write: written = ", written, ", totalBytesSent =", totalBytesSent);

      if (totalBytesSent >= size)
      {
        ETG_LOGINFO3("EthernetClient::write: Done, written = ", written, ", totalBytesSent =", totalBytesSent);

        //completed successfully
        retry = 0;
      }
      else
      {
        buf += written;
        bytesRemaining -= written;
        retry = ETHERNET_CLIENT_MAX_WRITE_RETRY;

        ETG_LOGINFO3("EthernetClient::write: Partially Done, written = ", written, ", bytesRemaining =", bytesRemaining);
      }
    }
    else if (written <= 0)
    {
      ETG_LOGERROR("EthernetClient::write: written error");

      setWriteError();

      written = 0;
      retry = 0;
    }

    // Looping
  }

  setWriteError();

  return 0;
}

////////////////////////////////////////

int EthernetClient::available()
{
  if (_sockindex >= MAX_SOCK_NUM)
    return 0;

  return Ethernet.socketRecvAvailable(_sockindex);
  // TODO: do the WIZnet chips automatically retransmit TCP ACK
  // packets if they are lost by the network?  Someday this should
  // be checked by a man-in-the-middle test which discards certain
  // packets.  If ACKs aren't resent, we would need to check for
  // returning 0 here and after a timeout do another Sock_RECV
  // command to cause the WIZnet chip to resend the ACK packet.
}

////////////////////////////////////////

int EthernetClient::read(uint8_t *buf, size_t size)
{
  if (_sockindex >= MAX_SOCK_NUM)
    return 0;

  return Ethernet.socketRecv(_sockindex, buf, size);
}

////////////////////////////////////////

int EthernetClient::peek()
{
  if (_sockindex >= MAX_SOCK_NUM)
    return -1;

  if (!available())
    return -1;

  return Ethernet.socketPeek(_sockindex);
}

////////////////////////////////////////

int EthernetClient::read()
{
  uint8_t b;

  if (Ethernet.socketRecv(_sockindex, &b, 1) > 0)
    return b;

  return -1;
}

////////////////////////////////////////

void EthernetClient::flush()
{
  while (_sockindex < MAX_SOCK_NUM)
  {
    uint8_t stat = Ethernet.socketStatus(_sockindex);

    if (stat != SnSR::ESTABLISHED && stat != SnSR::CLOSE_WAIT)
      return;

    if (Ethernet.socketSendAvailable(_sockindex) >= W5100.SSIZE)
      return;
  }
}

////////////////////////////////////////

void EthernetClient::stop()
{
  if (_sockindex >= MAX_SOCK_NUM)
    return;

  // attempt to close the connection gracefully (send a FIN to other side)
  Ethernet.socketDisconnect(_sockindex);

  unsigned long start = millis();

  // wait up to a second for the connection to close
  do
  {
    if (Ethernet.socketStatus(_sockindex) == SnSR::CLOSED)
    {
      _sockindex = MAX_SOCK_NUM;
      return; // exit the loop
    }

    delay(1);
  } while (millis() - start < _timeout);

  // if it hasn't closed, close it forcefully
  Ethernet.socketClose(_sockindex);
  _sockindex = MAX_SOCK_NUM;
}

////////////////////////////////////////

uint8_t EthernetClient::connected()
{
  if (_sockindex >= MAX_SOCK_NUM)
    return 0;

  uint8_t s = Ethernet.socketStatus(_sockindex);

  return !(s == SnSR::LISTEN || s == SnSR::CLOSED || s == SnSR::FIN_WAIT || (s == SnSR::CLOSE_WAIT && !available()));
}

////////////////////////////////////////

uint8_t EthernetClient::status()
{
  if (_sockindex >= MAX_SOCK_NUM)
    return SnSR::CLOSED;

  return Ethernet.socketStatus(_sockindex);
}

////////////////////////////////////////

// the next function allows us to use the client returned by
// EthernetServer::available() as the condition in an if-statement.
bool EthernetClient::operator==(const EthernetClient& rhs)
{
  if (_sockindex != rhs._sockindex)
    return false;

  if (_sockindex >= MAX_SOCK_NUM)
    return false;

  if (rhs._sockindex >= MAX_SOCK_NUM)
    return false;

  return true;
}

////////////////////////////////////////

// https://github.com/per1234/EthernetMod
// from: https://github.com/ntruchsess/Arduino-1/commit/937bce1a0bb2567f6d03b15df79525569377dabd
uint16_t EthernetClient::localPort()
{
  if (_sockindex >= MAX_SOCK_NUM)
    return 0;

  uint16_t port;

  W5100.beginSPITransaction();
  port = W5100.readSnPORT(_sockindex);
  W5100.endSPITransaction();

  return port;
}

////////////////////////////////////////

// https://github.com/per1234/EthernetMod
// returns the remote IP address: http://forum.arduino.cc/index.php?topic=82416.0
IPAddress EthernetClient::remoteIP()
{
  if (_sockindex >= MAX_SOCK_NUM)
    return IPAddress((uint32_t)0);

  uint8_t remoteIParray[4];

  W5100.beginSPITransaction();
  W5100.readSnDIPR(_sockindex, remoteIParray);
  W5100.endSPITransaction();

  return IPAddress(remoteIParray);
}

////////////////////////////////////////

// https://github.com/per1234/EthernetMod
// from: https://github.com/ntruchsess/Arduino-1/commit/ca37de4ba4ecbdb941f14ac1fe7dd40f3008af75
uint16_t EthernetClient::remotePort()
{
  if (_sockindex >= MAX_SOCK_NUM)
    return 0;

  uint16_t port;

  W5100.beginSPITransaction();
  port = W5100.readSnDPORT(_sockindex);
  W5100.endSPITransaction();

  return port;
}

////////////////////////////////////////

#endif    // ETHERNET_CLIENT_GENERIC_IMPL_H
