/****************************************************************************************************************************
  EthernetServer_Impl.h - Driver for W5x00

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

  Version: 2.8.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.0.0   K Hoang      31/03/2022 Initial porting and coding to support SPI2, debug, h-only library
  ...
  2.6.0   K Hoang      11/09/2022 Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  2.6.1   K Hoang      23/09/2022 Fix bug for W5200
  2.6.2   K Hoang      26/10/2022 Add support to Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE using `mbed` or `nRF52` core
  2.7.0   K Hoang      14/11/2022 Fix severe limitation to permit sending larger data than 2/4/8/16K buffer
  2.7.1   K Hoang      15/11/2022 Auto-detect W5x00 and settings to set MAX_SIZE to send
  2.8.0   K Hoang      27/12/2022 Add support to W6100 using IPv4
  2.8.1   K Hoang      06/01/2023 Fix W6100 minor bug
 *****************************************************************************************************************************/

#pragma once

#ifndef ETHERNET_SERVER_GENERIC_IMPL_H
#define ETHERNET_SERVER_GENERIC_IMPL_H

#include <Arduino.h>
#include "Ethernet_Generic.hpp"

#include "utility/w5100.h"

uint16_t EthernetServer::server_port[MAX_SOCK_NUM];

////////////////////////////////////////

void EthernetServer::begin()
{
  uint8_t sockindex = Ethernet.socketBegin(SnMR::TCP, _port);

  if (sockindex < MAX_SOCK_NUM)
  {
    if (Ethernet.socketListen(sockindex))
    {
      server_port[sockindex] = _port;
    }
    else
    {
      Ethernet.socketDisconnect(sockindex);
    }
  }
}

////////////////////////////////////////

EthernetClient EthernetServer::available()
{
  bool listening = false;
  uint8_t sockindex = MAX_SOCK_NUM;
  EthernetChip_t chip;
  uint8_t maxindex = MAX_SOCK_NUM;

  chip = W5100.getChip();

  if (chip == noChip)
    return EthernetClient(MAX_SOCK_NUM);

#if MAX_SOCK_NUM > 4

  if ( (chip == w5100) || (chip == w5100s) )
    maxindex = 4; // W5100/W5100S chip never supports more than 4 sockets

#endif

  for (uint8_t i = 0; i < maxindex; i++)
  {
    if (server_port[i] == _port)
    {
      uint8_t stat = Ethernet.socketStatus(i);

      if (stat == SnSR::ESTABLISHED || stat == SnSR::CLOSE_WAIT)
      {
        if (Ethernet.socketRecvAvailable(i) > 0)
        {
          sockindex = i;
        }
        else
        {
          // remote host closed connection, our end still open
          if (stat == SnSR::CLOSE_WAIT)
          {
            Ethernet.socketDisconnect(i);
            // status becomes LAST_ACK for short time
          }
        }
      }
      else if (stat == SnSR::LISTEN)
      {
        listening = true;
      }
      else if (stat == SnSR::CLOSED)
      {
        server_port[i] = 0;
      }
    }
  }

  if (!listening)
    begin();

  return EthernetClient(sockindex);
}

////////////////////////////////////////

EthernetClient EthernetServer::accept()
{
  bool listening = false;
  uint8_t sockindex = MAX_SOCK_NUM;
  EthernetChip_t chip;
  uint8_t maxindex = MAX_SOCK_NUM;

  chip = W5100.getChip();

  if (chip == noChip)
    return EthernetClient(MAX_SOCK_NUM);

#if MAX_SOCK_NUM > 4

  if ( (chip == w5100) || (chip == w5100s) )
    maxindex = 4; // W5100 chip never supports more than 4 sockets

#endif

  for (uint8_t i = 0; i < maxindex; i++)
  {
    if (server_port[i] == _port)
    {
      uint8_t stat = Ethernet.socketStatus(i);

      if (sockindex == MAX_SOCK_NUM && (stat == SnSR::ESTABLISHED || stat == SnSR::CLOSE_WAIT))
      {
        // Return the connected client even if no data received.
        // Some protocols like FTP expect the server to send the
        // first data.
        sockindex = i;
        server_port[i] = 0; // only return the client once
      }
      else if (stat == SnSR::LISTEN)
      {
        listening = true;
      }
      else if (stat == SnSR::CLOSED)
      {
        server_port[i] = 0;
      }
    }
  }

  if (!listening)
    begin();

  return EthernetClient(sockindex);
}

////////////////////////////////////////

EthernetServer::operator bool()
{
  uint8_t maxindex = MAX_SOCK_NUM;

#if MAX_SOCK_NUM > 4
  EthernetChip_t chip;

  chip = W5100.getChip();

  if ( (chip == w5100) || (chip == w5100s) )
    maxindex = 4; // W5100/W5100S chip never supports more than 4 sockets

#endif

  for (uint8_t i = 0; i < maxindex; i++)
  {
    if (server_port[i] == _port)
    {
      if (Ethernet.socketStatus(i) == SnSR::LISTEN)
      {
        return true; // server is listening for incoming clients
      }
    }
  }

  return false;
}

////////////////////////////////////////

void EthernetServer::statusreport()
{
  ETG_LOGDEBUG1("EthernetServer, port =", _port);

  for (uint8_t i = 0; i < MAX_SOCK_NUM; i++)
  {
    uint16_t port = server_port[i];
    uint8_t stat = Ethernet.socketStatus(i);
    const char *name;

    switch (stat)
    {
      case 0x00:
        name = "CLOSED";
        break;

      case 0x13:
        name = "INIT";
        break;

      case 0x14:
        name = "LISTEN";
        break;

      case 0x15:
        name = "SYNSENT";
        break;

      case 0x16:
        name = "SYNRECV";
        break;

      case 0x17:
        name = "ESTABLISHED";
        break;

      case 0x18:
        name = "FIN_WAIT";
        break;

      case 0x1A:
        name = "CLOSING";
        break;

      case 0x1B:
        name = "TIME_WAIT";
        break;

      case 0x1C:
        name = "CLOSE_WAIT";
        break;

      case 0x1D:
        name = "LAST_ACK";
        break;

      case 0x22:
        name = "UDP";
        break;

      case 0x32:
        name = "IPRAW";
        break;

      case 0x42:
        name = "MACRAW";
        break;

      case 0x5F:
        name = "PPPOE";
        break;

      default:
        name = "???";
    }

    int avail = Ethernet.socketRecvAvailable(i);

    ETG_LOGDEBUG3("index =", i, ", port= =", port);
    ETG_LOGDEBUG3("status =", name, ", avail =", avail);
  }
}

////////////////////////////////////////

size_t EthernetServer::write(uint8_t b)
{
  return write(&b, 1);
}

////////////////////////////////////////

// KH rewrite to enable chunk-sending for large file

#define ETHERNET_SERVER_MAX_WRITE_RETRY       100

////////////////////////////////////////

// Private function
size_t EthernetServer::_write(const uint8_t sockindex, const uint8_t *buf, size_t size)
{
  int written = 0;
  int retry = ETHERNET_SERVER_MAX_WRITE_RETRY;

  uint16_t ETHERNET_SERVER_SEND_MAX_SIZE = W5100.SSIZE;

  size_t totalBytesSent = 0;
  size_t bytesRemaining = size;

  ETG_LOGINFO1("EthernetServer::write: chip = ", W5100.getChip());
  ETG_LOGINFO3("EthernetServer::write: size = ", size, ", MAX_SIZE =", ETHERNET_SERVER_SEND_MAX_SIZE);

  if (size == 0)
  {
    setWriteError();

    ETG_LOGDEBUG("EthernetServer::write: size = 0");

    return 0;
  }

  while (retry)
  {
    written =  Ethernet.socketSend(sockindex, buf, min(bytesRemaining, (size_t) ETHERNET_SERVER_SEND_MAX_SIZE) );

    if (written > 0)
    {
      totalBytesSent += written;

      ETG_LOGINFO3("EthernetServer::write: written = ", written, ", totalBytesSent =", totalBytesSent);

      if (totalBytesSent >= size)
      {
        ETG_LOGINFO3("EthernetServer::write: Done, written = ", written, ", totalBytesSent =", totalBytesSent);

        //completed successfully
        retry = 0;
      }
      else
      {
        buf += written;
        bytesRemaining -= written;
        retry = ETHERNET_SERVER_MAX_WRITE_RETRY;

        ETG_LOGINFO3("EthernetServer::write: Partially Done, written = ", written, ", bytesRemaining =", bytesRemaining);
      }
    }
    else if (written <= 0)
    {
      ETG_LOGERROR("EthernetServer::write: written error");

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

size_t EthernetServer::write(const uint8_t *buffer, size_t size)
{
  EthernetChip_t chip;
  uint8_t maxindex = MAX_SOCK_NUM;

  chip = W5100.getChip();

  if (chip == noChip)
    return 0;

#if MAX_SOCK_NUM > 4

  if ( (chip == w5100) || (chip == w5100s) )
    maxindex = 4; // W5100/W5100S chip never supports more than 4 sockets

#endif

  available();

  for (uint8_t i = 0; i < maxindex; i++)
  {
    if (server_port[i] == _port)
    {
      if (Ethernet.socketStatus(i) == SnSR::ESTABLISHED)
      {
        //Ethernet.socketSend(i, buffer, size);
        _write(i, buffer, size);
      }
    }
  }

  return size;
}

////////////////////////////////////////

#endif    // ETHERNET_SERVER_GENERIC_IMPL_H
