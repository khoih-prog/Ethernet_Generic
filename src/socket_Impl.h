/****************************************************************************************************************************
  socket_Impl.h - Driver for W5x00

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

#ifndef ETHERNET_SOCKET_GENERIC_IMPL_H
#define ETHERNET_SOCKET_GENERIC_IMPL_H

#include <Arduino.h>
#include "Ethernet_Generic.hpp"

#include "utility/w5100.h"

////////////////////////////////////////

#if ARDUINO >= 156 && !defined(ARDUINO_ARCH_PIC32)
  extern void yield();
#else
  #define yield()
#endif

// TODO: randomize this when not using DHCP, but how?
static uint16_t local_port = 49152;  // 49152 to 65535

////////////////////////////////////////

typedef struct
{
  uint16_t RX_RSR; // Number of bytes received
  uint16_t RX_RD;  // Address to read
  uint16_t TX_FSR; // Free space ready for transmit
  uint8_t  RX_inc; // how much have we advanced RX_RD
} socketstate_t;

static socketstate_t state[MAX_SOCK_NUM];

/////////////////////////////////////////////////////////

static uint16_t getSnTX_FSR(uint8_t s);
static uint16_t getSnRX_RSR(uint8_t s);

static void write_data(uint8_t s, uint16_t offset, const uint8_t *data, uint16_t len);
static void read_data(uint8_t s, uint16_t src, uint8_t *dst, uint16_t len);

////////////////////////////////////////

/*****************************************/
/*          Socket management            */
/*****************************************/

void EthernetClass::socketPortRand(uint16_t n)
{
  n &= 0x3FFF;
  local_port ^= n;

  ETG_LOGDEBUG3("socketPortRand, socketPortRand =", n, ", srcport =", local_port);
}

////////////////////////////////////////

uint8_t EthernetClass::socketBegin(uint8_t protocol, uint16_t port)
{
  uint8_t s;
  EthernetChip_t chip;
  uint8_t status[MAX_SOCK_NUM];
  uint8_t maxindex = MAX_SOCK_NUM;

  // first check hardware compatibility
  chip = W5100.getChip();

  if (chip == noChip)
    return MAX_SOCK_NUM; // immediate error if no hardware detected

#if MAX_SOCK_NUM > 4

  if ( (chip == w5100) || (chip == w5100s) )
    maxindex = 4; // W5100/W5100S chip never supports more than 4 sockets

#endif

  ETG_LOGDEBUG3("socketBegin, protocol =", protocol, ", port =", port);

  W5100.beginSPITransaction();

  // look at all the hardware sockets, use any that are closed (unused)
  for (s = 0; s < maxindex; s++)
  {
    status[s] = W5100.readSnSR(s);

    if (status[s] == SnSR::CLOSED)
      goto makesocket;
  }

  ETG_LOGDEBUG("socketBegin step2");

  // as a last resort, forcibly close any already closing
  for (s = 0; s < maxindex; s++)
  {
    uint8_t stat = status[s];

    if (stat == SnSR::LAST_ACK)
      goto closemakesocket;

    if (stat == SnSR::TIME_WAIT)
      goto closemakesocket;

    if (stat == SnSR::FIN_WAIT)
      goto closemakesocket;

    if (stat == SnSR::CLOSING)
      goto closemakesocket;
  }

  W5100.endSPITransaction();

  return MAX_SOCK_NUM; // all sockets are in use

closemakesocket:

  ETG_LOGDEBUG("socketBegin close");

  W5100.execCmdSn(s, Sock_CLOSE);

makesocket:

  ETG_LOGDEBUG1("socketBegin, socket index =", s);

  EthernetServer::server_port[s] = 0;
  delayMicroseconds(250); // TODO: is this needed??
  W5100.writeSnMR(s, protocol);
  W5100.writeSnIR(s, 0xFF);

  if (port > 0)
  {
    W5100.writeSnPORT(s, port);
  }
  else
  {
    // if don't set the source port, set local_port number.
    if (++local_port < 49152)
      local_port = 49152;

    W5100.writeSnPORT(s, local_port);
  }

  W5100.execCmdSn(s, Sock_OPEN);
  state[s].RX_RSR = 0;
  state[s].RX_RD  = W5100.readSnRX_RD(s); // always zero?
  state[s].RX_inc = 0;
  state[s].TX_FSR = 0;

  ETG_LOGDEBUG3("socketBegin, prot =", W5100.readSnMR(s), ", RX_RD =", state[s].RX_RD);

  W5100.endSPITransaction();

  return s;
}

////////////////////////////////////////

// multicast version to set fields before open  thd
uint8_t EthernetClass::socketBeginMulticast(uint8_t protocol, IPAddress ip, uint16_t port)
{
  uint8_t s;
  EthernetChip_t chip;
  uint8_t status[MAX_SOCK_NUM];
  uint8_t maxindex = MAX_SOCK_NUM;

  // first check hardware compatibility
  chip = W5100.getChip();

  if (chip == noChip)
    return 0;

#if MAX_SOCK_NUM > 4

  if ( (chip == w5100) || (chip == w5100s) )
    maxindex = 4; // W5100/W5100S chip never supports more than 4 sockets

#endif

  ETG_LOGDEBUG3("socketBeginMulticast, protocol =", protocol, ", port =", port);

  W5100.beginSPITransaction();

  // look at all the hardware sockets, use any that are closed (unused)
  for (s = 0; s < maxindex; s++)
  {
    status[s] = W5100.readSnSR(s);

    if (status[s] == SnSR::CLOSED)
      goto makesocket;
  }

  ETG_LOGDEBUG("socketBeginMulticast: step2");

  // as a last resort, forcibly close any already closing
  for (s = 0; s < maxindex; s++)
  {
    uint8_t stat = status[s];

    if (stat == SnSR::LAST_ACK)
      goto closemakesocket;

    if (stat == SnSR::TIME_WAIT)
      goto closemakesocket;

    if (stat == SnSR::FIN_WAIT)
      goto closemakesocket;

    if (stat == SnSR::CLOSING)
      goto closemakesocket;
  }

  W5100.endSPITransaction();

  return MAX_SOCK_NUM; // all sockets are in use

closemakesocket:

  ETG_LOGDEBUG("socketBeginMulticast: close");

  W5100.execCmdSn(s, Sock_CLOSE);

makesocket:

  ETG_LOGDEBUG1("socketBeginMulticast, socket index =", s);

  EthernetServer::server_port[s] = 0;
  delayMicroseconds(250); // TODO: is this needed??
  W5100.writeSnMR(s, protocol);
  W5100.writeSnIR(s, 0xFF);

  if (port > 0)
  {
    W5100.writeSnPORT(s, port);
  }
  else
  {
    // if don't set the source port, set local_port number.
    if (++local_port < 49152)
      local_port = 49152;

    W5100.writeSnPORT(s, local_port);
  }

  // Calculate MAC address from Multicast IP Address
  byte mac[] = {  0x01, 0x00, 0x5E, 0x00, 0x00, 0x00 };
  mac[3] = ip[1] & 0x7F;
  mac[4] = ip[2];
  mac[5] = ip[3];
  W5100.writeSnDIPR(s, ip.raw_address());   //239.255.0.1
  W5100.writeSnDPORT(s, port);
  W5100.writeSnDHAR(s, mac);
  W5100.execCmdSn(s, Sock_OPEN);
  state[s].RX_RSR = 0;
  state[s].RX_RD  = W5100.readSnRX_RD(s); // always zero?
  state[s].RX_inc = 0;
  state[s].TX_FSR = 0;

  ETG_LOGDEBUG3("socketBeginMulticast, prot =", W5100.readSnMR(s), ", RX_RD =", state[s].RX_RD);

  W5100.endSPITransaction();

  return s;
}

////////////////////////////////////////

// Return the socket's status
//
uint8_t EthernetClass::socketStatus(uint8_t s)
{
  W5100.beginSPITransaction();
  uint8_t status = W5100.readSnSR(s);
  W5100.endSPITransaction();

  return status;
}

////////////////////////////////////////

// Immediately close.  If a TCP connection is established, the
// remote host is left unaware we closed.
//
void EthernetClass::socketClose(uint8_t s)
{
  W5100.beginSPITransaction();
  W5100.execCmdSn(s, Sock_CLOSE);
  W5100.endSPITransaction();
}

////////////////////////////////////////

// Place the socket in listening (server) mode
//
uint8_t EthernetClass::socketListen(uint8_t s)
{
  W5100.beginSPITransaction();

  if (W5100.readSnSR(s) != SnSR::INIT)
  {
    W5100.endSPITransaction();

    return 0;
  }

  W5100.execCmdSn(s, Sock_LISTEN);

  W5100.endSPITransaction();

  return 1;
}

////////////////////////////////////////

// establish a TCP connection in Active (client) mode.
//
void EthernetClass::socketConnect(uint8_t s, uint8_t * addr, uint16_t port)
{
  // set destination IP
  W5100.beginSPITransaction();
  W5100.writeSnDIPR(s, addr);
  W5100.writeSnDPORT(s, port);
  W5100.execCmdSn(s, Sock_CONNECT);
  W5100.endSPITransaction();
}

////////////////////////////////////////

// Gracefully disconnect a TCP connection.
//
void EthernetClass::socketDisconnect(uint8_t s)
{
  W5100.beginSPITransaction();
  W5100.execCmdSn(s, Sock_DISCON);
  W5100.endSPITransaction();
}

////////////////////////////////////////

/*****************************************/
/*    Socket Data Receive Functions      */
/*****************************************/


static uint16_t getSnRX_RSR(uint8_t s)
{
  uint16_t val, prev;

  prev = W5100.readSnRX_RSR(s);

  while (1)
  {
    val = W5100.readSnRX_RSR(s);

    if (val == prev)
    {
      return val;
    }

    prev = val;
  }
}

////////////////////////////////////////

static void read_data(uint8_t s, uint16_t src, uint8_t *dst, uint16_t len)
{
  uint16_t size;
  uint16_t src_mask;
  uint16_t src_ptr;

  ETG_LOGDEBUG3("read_data, len =", len, ", at =", src);

  src_mask = (uint16_t)src & W5100.SMASK;
  src_ptr = W5100.RBASE(s) + src_mask;

  if (W5100.hasOffsetAddressMapping() || src_mask + len <= W5100.SSIZE)
  {
    W5100.read(src_ptr, dst, len);
  }
  else
  {
    size = W5100.SSIZE - src_mask;
    W5100.read(src_ptr, dst, size);
    dst += size;
    W5100.read(W5100.RBASE(s), dst, len - size);
  }
}

////////////////////////////////////////

// Receive data.  Returns size, or -1 for no data, or 0 if connection closed
//
int EthernetClass::socketRecv(uint8_t s, uint8_t *buf, int16_t len)
{
  // Check how much data is available
  int ret = state[s].RX_RSR;

  W5100.beginSPITransaction();

  if (ret < len)
  {
    uint16_t rsr = getSnRX_RSR(s);
    ret = rsr - state[s].RX_inc;
    state[s].RX_RSR = ret;

    ETG_LOGDEBUG3("socketRecv, RX_RSR =", ret, ", RX_inc =", state[s].RX_inc);
  }

  if (ret == 0)
  {
    // No data available.
    uint8_t status = W5100.readSnSR(s);

    if ( status == SnSR::LISTEN || status == SnSR::CLOSED || status == SnSR::CLOSE_WAIT )
    {
      // The remote end has closed its side of the connection,
      // so this is the eof state
      ret = 0;
    }
    else
    {
      // The connection is still up, but there's no data waiting to be read
      ret = -1;
    }
  }
  else
  {
    if (ret > len)
      ret = len; // more data available than buffer length

    uint16_t ptr = state[s].RX_RD;

    if (buf)
      read_data(s, ptr, buf, ret);

    ptr += ret;
    state[s].RX_RD = ptr;
    state[s].RX_RSR -= ret;
    uint16_t inc = state[s].RX_inc + ret;

    if (inc >= 250 || state[s].RX_RSR == 0)
    {
      state[s].RX_inc = 0;
      W5100.writeSnRX_RD(s, ptr);
      W5100.execCmdSn(s, Sock_RECV);

      ETG_LOGDEBUG3("socketRecv, cmd RX_RD received =", state[s].RX_RD, ", RX_RSR remaining =", state[s].RX_RSR);

    }
    else
    {
      state[s].RX_inc = inc;
    }
  }

  W5100.endSPITransaction();

  ETG_LOGDEBUG1("socketRecv, ret =", ret);

  return ret;
}

////////////////////////////////////////

uint16_t EthernetClass::socketRecvAvailable(uint8_t s)
{
  uint16_t ret = state[s].RX_RSR;

  if (ret == 0)
  {
    W5100.beginSPITransaction();

    uint16_t rsr = getSnRX_RSR(s);

    W5100.endSPITransaction();

    ret = rsr - state[s].RX_inc;
    state[s].RX_RSR = ret;

    ETG_LOGDEBUG3("socketRecvAvailable, socket =", s, ", RX_RSR =", ret);
  }

  return ret;
}

////////////////////////////////////////

// get the first byte in the receive queue (no checking)
//
uint8_t EthernetClass::socketPeek(uint8_t s)
{
  uint8_t b;

  W5100.beginSPITransaction();

  uint16_t ptr = state[s].RX_RD;
  W5100.read((ptr & W5100.SMASK) + W5100.RBASE(s), &b, 1);

  W5100.endSPITransaction();

  return b;
}

////////////////////////////////////////

/*****************************************/
/*    Socket Data Transmit Functions     */
/*****************************************/

static uint16_t getSnTX_FSR(uint8_t s)
{
  uint16_t val, prev;

  prev = W5100.readSnTX_FSR(s);

  while (1)
  {
    val = W5100.readSnTX_FSR(s);

    if (val == prev)
    {
      state[s].TX_FSR = val;

      return val;
    }

    prev = val;
  }
}

////////////////////////////////////////

static void write_data(uint8_t s, uint16_t data_offset, const uint8_t *data, uint16_t len)
{
  uint16_t ptr = W5100.readSnTX_WR(s);
  ptr += data_offset;
  uint16_t offset = ptr & W5100.SMASK;
  uint16_t dstAddr = offset + W5100.SBASE(s);

  if (W5100.hasOffsetAddressMapping() || offset + len <= W5100.SSIZE)
  {
    W5100.write(dstAddr, data, len);
  }
  else
  {
    // Wrap around circular buffer
    uint16_t size = W5100.SSIZE - offset;
    W5100.write(dstAddr, data, size);
    W5100.write(W5100.SBASE(s), data + size, len - size);
  }

  ptr += len;
  W5100.writeSnTX_WR(s, ptr);
}

////////////////////////////////////////

/**
   @brief This function used to send the data in TCP mode
   @return  1 for success else 0.
*/
uint16_t EthernetClass::socketSend(uint8_t s, const uint8_t * buf, uint16_t len)
{
  uint8_t status = 0;
  uint16_t ret = 0;
  uint16_t freesize = 0;

  if (len > W5100.SSIZE)
  {
    ret = W5100.SSIZE; // check size not to exceed MAX size.
  }
  else
  {
    ret = len;
  }

  // if freebuf is available, start.
  do
  {
    W5100.beginSPITransaction();
    freesize = getSnTX_FSR(s);
    status = W5100.readSnSR(s);
    W5100.endSPITransaction();

    if ((status != SnSR::ESTABLISHED) && (status != SnSR::CLOSE_WAIT))
    {
      ret = 0;
      break;
    }

    yield();
  } while (freesize < ret);

  // copy data
  W5100.beginSPITransaction();

  write_data(s, 0, (uint8_t *)buf, ret);
  W5100.execCmdSn(s, Sock_SEND);

  /* +2008.01 bj */
  while ( (W5100.readSnIR(s) & SnIR::SEND_OK) != SnIR::SEND_OK )
  {
    /* m2008.01 [bj] : reduce code */
    if ( W5100.readSnSR(s) == SnSR::CLOSED )
    {
      W5100.endSPITransaction();
      return 0;
    }

    W5100.endSPITransaction();

    yield();

    W5100.beginSPITransaction();
  }

  /* +2008.01 bj */
  W5100.writeSnIR(s, SnIR::SEND_OK);
  W5100.endSPITransaction();

  return ret;
}

////////////////////////////////////////

uint16_t EthernetClass::socketSendAvailable(uint8_t s)
{
  uint8_t status = 0;
  uint16_t freesize = 0;

  W5100.beginSPITransaction();
  freesize = getSnTX_FSR(s);
  status = W5100.readSnSR(s);
  W5100.endSPITransaction();

  if ((status == SnSR::ESTABLISHED) || (status == SnSR::CLOSE_WAIT))
  {
    return freesize;
  }

  return 0;
}

////////////////////////////////////////

uint16_t EthernetClass::socketBufferData(uint8_t s, uint16_t offset, const uint8_t* buf, uint16_t len)
{
  ETG_LOGDEBUG3("socketBufferData, offset =", offset, ", len =", len);

  uint16_t ret = 0;

  W5100.beginSPITransaction();

  uint16_t txfree = getSnTX_FSR(s);

  if (len > txfree)
  {
    ret = txfree; // check size not to exceed MAX size.
  }
  else
  {
    ret = len;
  }

  write_data(s, offset, buf, ret);

  W5100.endSPITransaction();

  return ret;
}

////////////////////////////////////////

bool EthernetClass::socketStartUDP(uint8_t s, uint8_t* addr, uint16_t port)
{
  if ( ((addr[0] == 0x00) && (addr[1] == 0x00) && (addr[2] == 0x00) && (addr[3] == 0x00)) || ((port == 0x00)) )
  {
    return false;
  }

  W5100.beginSPITransaction();
  W5100.writeSnDIPR(s, addr);
  W5100.writeSnDPORT(s, port);
  W5100.endSPITransaction();

  return true;
}

////////////////////////////////////////

bool EthernetClass::socketSendUDP(uint8_t s)
{
  W5100.beginSPITransaction();

  W5100.execCmdSn(s, Sock_SEND);

  /* +2008.01 bj */
  while ( (W5100.readSnIR(s) & SnIR::SEND_OK) != SnIR::SEND_OK )
  {
    if (W5100.readSnIR(s) & SnIR::TIMEOUT)
    {
      /* +2008.01 [bj]: clear interrupt */
      W5100.writeSnIR(s, (SnIR::SEND_OK | SnIR::TIMEOUT));
      W5100.endSPITransaction();

      ETG_LOGINFO("socketSendUDP: timeout");

      return false;
    }

    W5100.endSPITransaction();

    yield();

    W5100.beginSPITransaction();
  }

  /* +2008.01 bj */
  W5100.writeSnIR(s, SnIR::SEND_OK);
  W5100.endSPITransaction();

  ETG_LOGDEBUG("socketSendUDP, OK");

  /* Sent ok */
  return true;
}

////////////////////////////////////////

#endif    // ETHERNET_SOCKET_GENERIC_IMPL_H
