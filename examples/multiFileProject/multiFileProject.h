/****************************************************************************************************************************
  multiFileProject.h
  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries
  
  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Generic
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

#define _TEENSY41_ASYNC_TCP_LOGLEVEL_       1

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include <Ethernet_Generic.hpp>         // https://github.com/khoih-prog/Ethernet_Generic

#include <EthernetClient.h>             // https://github.com/khoih-prog/Ethernet_Generic
#include <EthernetServer.h>             // https://github.com/khoih-prog/Ethernet_Generic
#include <EthernetUdp.h>                // https://github.com/khoih-prog/Ethernet_Generic
