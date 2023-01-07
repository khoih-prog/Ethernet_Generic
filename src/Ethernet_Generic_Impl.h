/****************************************************************************************************************************
  Ethernet_Generic_Impl.h - Driver for W5x00

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

#ifndef ETHERNET_GENERIC_IMPL_H
#define ETHERNET_GENERIC_IMPL_H

#include <Arduino.h>

#include "Ethernet_Generic_Debug.h"

#include "utility/w5100_Impl.h"

#include "Dhcp_Impl.h"

#include "EthernetClient_Impl.h"
#include "EthernetServer_Impl.h"
#include "EthernetUdp_Impl.h"
#include "socket_Impl.h"

IPAddress EthernetClass::_dnsServerAddress;
DhcpClass* EthernetClass::_dhcp = NULL;

/////////////////////////////////////////////////////////

// KH
void EthernetClass::setRstPin(uint8_t pinRST)
{
  _pinRST = pinRST;
  pinMode(_pinRST, OUTPUT);
  digitalWrite(_pinRST, HIGH);
}

void EthernetClass::setCsPin(uint8_t pinCS)
{
  _pinCS = pinCS;
  W5100.setSS(pinCS);

  ETG_LOGDEBUG3("Input pinCS = ", pinCS, "_pinCS = ", _pinCS);
}

/////////////////////////////////////////////////////////

void EthernetClass::initMaxSockNum(uint8_t maxSockNum)
{
  _maxSockNum = maxSockNum;
}

/////////////////////////////////////////////////////////

uint8_t EthernetClass::softreset()
{
  return W5100.softReset();
}

/////////////////////////////////////////////////////////

void EthernetClass::hardreset()
{
  if (_pinRST != 0)
  {
    digitalWrite(_pinRST, LOW);
    delay(1);
    digitalWrite(_pinRST, HIGH);
    delay(150);
  }
}

///////////////////////////////////////////////////////////////////////////////////

int EthernetClass::begin(uint8_t *mac, unsigned long timeout, unsigned long responseTimeout)
{
  static DhcpClass s_dhcp;
  _dhcp = &s_dhcp;

  ETG_LOGDEBUG1("begin: _pinCS = ", _pinCS);

  // Initialise the basic info
  if (W5100.init() == 0)
    return 0;

  W5100.beginSPITransaction();
  W5100.setMACAddress(mac);
  W5100.setIPAddress(IPAddress(0, 0, 0, 0).raw_address());
  W5100.endSPITransaction();

  if (strlen(_customHostname) != 0)
  {
    _dhcp->setCustomHostname(_customHostname);

    // Merge
    _hostName = _customHostname;
  }

  // Now try to get our config info from a DHCP server
  int ret = _dhcp->beginWithDHCP(mac, timeout, responseTimeout);

  if (ret == 1)
  {
    // We've successfully found a DHCP server and got our configuration
    // info, so set things accordingly
    W5100.beginSPITransaction();

    W5100.setIPAddress(_dhcp->getLocalIp().raw_address());
    W5100.setGatewayIp(_dhcp->getGatewayIp().raw_address());
    W5100.setSubnetMask(_dhcp->getSubnetMask().raw_address());
    W5100.endSPITransaction();

    _dnsServerAddress = _dhcp->getDnsServerIp();

    // From Ethernet2
    _dnsDomainName = _dhcp->getDnsDomainName();
    _hostName = _dhcp->getHostName();
    //////

    socketPortRand(micros());
  }

  return ret;
}

/////////////////////////////////////////////////////////

int EthernetClass::begin(uint8_t *mac, SPIClass *theSPI, unsigned long timeout, unsigned long responseTimeout)
{
  if (theSPI != nullptr)
  {
    ETG_LOGDEBUG("begin: Using new theSPI");
    pCUR_SPI = theSPI;
  }
  else
  {
    ETG_LOGDEBUG("begin: Using default SPI");
    pCUR_SPI = &SPI;
  }

  ETG_LOGHEXDEBUG1("begin: pCUR_SPI = 0x", (uint32_t) pCUR_SPI);

  return begin(mac, timeout, responseTimeout);
}

/////////////////////////////////////////////////////////

void EthernetClass::begin(uint8_t *mac, IPAddress ip)
{
  // Assume the DNS server will be the machine on the same network as the local IP
  // but with last octet being '1'
  IPAddress dns = ip;
  dns[3] = 1;
  begin(mac, ip, dns);
}

/////////////////////////////////////////////////////////

void EthernetClass::begin(uint8_t *mac, IPAddress ip, IPAddress dns)
{
  // Assume the gateway will be the machine on the same network as the local IP
  // but with last octet being '1'
  IPAddress gateway = ip;
  gateway[3] = 1;
  begin(mac, ip, dns, gateway);
}

/////////////////////////////////////////////////////////

void EthernetClass::begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway)
{
  IPAddress subnet(255, 255, 255, 0);
  begin(mac, ip, dns, gateway, subnet);
}

/////////////////////////////////////////////////////////

void EthernetClass::begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet)
{
  if (W5100.init() == 0)
    return;

  W5100.beginSPITransaction();
  W5100.setMACAddress(mac);

#if ( defined(ESP8266) || defined(ESP32)  )
  W5100.setIPAddress(&ip[0]);
  W5100.setGatewayIp(&gateway[0]);
  W5100.setSubnetMask(&subnet[0]);

#elif ARDUINO > 106 || TEENSYDUINO > 121

#if ( USING_RAW_ADDRESS || (defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED) ) )
  // KH
  // For new LwIp IPAddress code, such as arduino_pico core v2.3.0+
#if (_ETG_LOGLEVEL_ > 3)
#warning USING_RAW_ADDRESS
#endif

  W5100.setIPAddress(ip.raw_address());
  W5100.setGatewayIp(gateway.raw_address());
  W5100.setSubnetMask(subnet.raw_address());
#else
  // For core other than arduino-pico for compatibility
  W5100.setIPAddress(ip._address.bytes);
  W5100.setGatewayIp(gateway._address.bytes);
  W5100.setSubnetMask(subnet._address.bytes);
#endif
  //////

#else
  W5100.setIPAddress(ip._address);
  W5100.setGatewayIp(gateway._address);
  W5100.setSubnetMask(subnet._address);
#endif

  W5100.endSPITransaction();

  _dnsServerAddress = dns;
}

/////////////////////////////////////////////////////////

void EthernetClass::init(uint8_t sspin)
{
  W5100.setSS(sspin);
}

/////////////////////////////////////////////////////////

EthernetLinkStatus EthernetClass::linkStatus()
{
  switch (W5100.getLinkStatus())
  {
    case UNKNOWN:
      return Unknown;

    case LINK_ON:
      return LinkON;

    case LINK_OFF:
      return LinkOFF;

    default:
      return Unknown;
  }
}

/////////////////////////////////////////////////////////

EthernetHardwareStatus EthernetClass::hardwareStatus()
{
  switch (W5100.getChip())
  {
    case w5100:
      return EthernetW5100;

    case w5200:
      return EthernetW5200;

    case w5500:
      return EthernetW5500;

    case w5100s:
      return EthernetW5100S;

#if USING_W6100

    case w6100:
      return EthernetW6100;
#endif

    default:
      return EthernetNoHardware;
  }
}

/////////////////////////////////////////////////////////

int EthernetClass::maintain()
{
  int rc = DHCP_CHECK_NONE;

  if (_dhcp != NULL)
  {
    // we have a pointer to dhcp, use it
    rc = _dhcp->checkLease();

    switch (rc)
    {
      case DHCP_CHECK_NONE:
        //nothing done
        break;

      case DHCP_CHECK_RENEW_OK:
      case DHCP_CHECK_REBIND_OK:
        //we might have got a new IP.
        W5100.beginSPITransaction();
        W5100.setIPAddress(_dhcp->getLocalIp().raw_address());
        W5100.setGatewayIp(_dhcp->getGatewayIp().raw_address());
        W5100.setSubnetMask(_dhcp->getSubnetMask().raw_address());
        W5100.endSPITransaction();

        _dnsServerAddress = _dhcp->getDnsServerIp();

        // From Ethernet2
        _dnsDomainName = _dhcp->getDnsDomainName();
        _hostName = _dhcp->getHostName();
        //////

        break;

      default:
        //this is actually an error, it will retry though
        break;
    }
  }

  return rc;
}

/////////////////////////////////////////////////////////

void EthernetClass::MACAddress(uint8_t *mac_address)
{
  W5100.beginSPITransaction();
  W5100.getMACAddress(mac_address);
  W5100.endSPITransaction();
}

/////////////////////////////////////////////////////////

IPAddress EthernetClass::localIP()
{
  IPAddress ret;

  W5100.beginSPITransaction();
  W5100.getIPAddress(ret.raw_address());
  W5100.endSPITransaction();

  return ret;
}

/////////////////////////////////////////////////////////

IPAddress EthernetClass::subnetMask()
{
  IPAddress ret;

  W5100.beginSPITransaction();
  W5100.getSubnetMask(ret.raw_address());
  W5100.endSPITransaction();

  return ret;
}

/////////////////////////////////////////////////////////

IPAddress EthernetClass::gatewayIP()
{
  IPAddress ret;

  W5100.beginSPITransaction();
  W5100.getGatewayIp(ret.raw_address());
  W5100.endSPITransaction();

  return ret;
}

/////////////////////////////////////////////////////////

void EthernetClass::setMACAddress(const uint8_t *mac_address)
{
  W5100.beginSPITransaction();
  W5100.setMACAddress(mac_address);
  W5100.endSPITransaction();
}

/////////////////////////////////////////////////////////

void EthernetClass::setLocalIP(const IPAddress local_ip)
{
  IPAddress ip = local_ip;

  W5100.beginSPITransaction();
  W5100.setIPAddress(ip.raw_address());
  W5100.endSPITransaction();
}

/////////////////////////////////////////////////////////

void EthernetClass::setSubnetMask(const IPAddress subnet)
{
  IPAddress ip = subnet;

  W5100.beginSPITransaction();
  W5100.setSubnetMask(ip.raw_address());
  W5100.endSPITransaction();
}

/////////////////////////////////////////////////////////

void EthernetClass::setGatewayIP(const IPAddress gateway)
{
  IPAddress ip = gateway;

  W5100.beginSPITransaction();
  W5100.setGatewayIp(ip.raw_address());
  W5100.endSPITransaction();
}

/////////////////////////////////////////////////////////

void EthernetClass::setRetransmissionTimeout(uint16_t milliseconds)
{
  if (milliseconds > 6553)
    milliseconds = 6553;

  W5100.beginSPITransaction();
  W5100.setRetransmissionTime(milliseconds * 10);
  W5100.endSPITransaction();
}

/////////////////////////////////////////////////////////

void EthernetClass::setRetransmissionCount(uint8_t num)
{
  W5100.beginSPITransaction();
  W5100.setRetransmissionCount(num);
  W5100.endSPITransaction();
}

/////////////////////////////////////////////////////////

// w5100, w5200 or w5500
EthernetChip_t EthernetClass::getChip()
{
  return ( W5100.getChip() );
}

/////////////////////////////////////////////////////////

// w5100S
EthernetChip_t EthernetClass::getAltChip()
{
  return ( W5100.getAltChip() );
}

/////////////////////////////////////////
// From Ethernet3
/////////////////////////////////////////

void EthernetClass::setHostname(const char* hostname)
{
  memset(_customHostname, 0, HOSTNAME_SIZE);
  memcpy((void*) _customHostname, (void*) hostname,
         strlen(hostname) >= HOSTNAME_SIZE - 1 ? HOSTNAME_SIZE - 1 : strlen(hostname));

  // Merge
  _hostName = _customHostname;
}

// set Wake on LAN
void WoL(bool wol)
{
  W5100.WoL(wol);
};

/////////////////////////////////////////

// get the WoL state
bool WoL()
{
  return W5100.WoL();
}

/////////////////////////////////////////

void phyMode(phyMode_t mode)
{
  return W5100.phyMode(mode);
}

/////////////////////////////////////////

uint8_t EthernetClass::phyState()
{
  return W5100.phyState();
}

/////////////////////////////////////////

uint8_t EthernetClass::link()
{
  return W5100.link();
}

/////////////////////////////////////////

const char* EthernetClass::linkReport()
{
  return W5100.linkReport();
}

/////////////////////////////////////////

uint8_t EthernetClass::speed()
{
  return W5100.speed();
}

/////////////////////////////////////////

const char* EthernetClass::speedReport()
{
  return W5100.speedReport();
}

/////////////////////////////////////////

uint8_t EthernetClass::duplex()
{
  return W5100.duplex();
}

/////////////////////////////////////////

const char* EthernetClass::duplexReport()
{
  return W5100.duplexReport();
}

/////////////////////////////////////////
/////////////////////////////////////////

EthernetClass Ethernet;

#endif
