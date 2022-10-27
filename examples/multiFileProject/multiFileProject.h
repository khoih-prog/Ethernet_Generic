/****************************************************************************************************************************
  multiFileProject.h
  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Generic
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

#if defined(__AVR_AVR128DA48__)
  #define SerialDebug   Serial1
#elif defined(__AVR_AVR128DB48__)
  #define SerialDebug   Serial3
#else
  // standard Serial
  #define SerialDebug   Serial
#endif

#define DEBUG_ETHERNET_GENERIC_PORT         SerialDebug

// Debug Level from 0 to 4
#define _ETG_LOGLEVEL_                      2

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include <Ethernet_Generic.hpp>         // https://github.com/khoih-prog/Ethernet_Generic

#include <EthernetClient.h>             // https://github.com/khoih-prog/Ethernet_Generic
#include <EthernetServer.h>             // https://github.com/khoih-prog/Ethernet_Generic
#include <EthernetUdp.h>                // https://github.com/khoih-prog/Ethernet_Generic
