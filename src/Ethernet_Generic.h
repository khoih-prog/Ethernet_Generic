/****************************************************************************************************************************
  Ethernet_Generic.h - Driver for W5x00

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
  
  Version: 2.3.1
    
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.0.0   K Hoang      31/03/2022 Initial porting and coding to support SPI2, debug, h-only library
  2.0.1   K Hoang      08/04/2022 Add support to SPI1 for RP2040 using arduino-pico core
  2.1.0   K Hoang      22/04/2022 Add support to WIZNet W5100S
  2.2.0   K Hoang      02/05/2022 Add support to custom SPI for any board, such as STM32
  2.3.0   K Hoang      03/05/2022 Add support to custom SPI for RP2040, Portenta_H7, etc. using Arduino-mbed core
  2.3.1   K Hoang      21/05/2022 Add setHostname() and related functions
 *****************************************************************************************************************************/

#pragma once

#ifndef ETHERNET_GENERIC_H
#define ETHERNET_GENERIC_H


/////////////////////////////////////////////////////////

#define ETHERNET_GENERIC_VERSION            "Ethernet_Generic v2.3.1"

#define ETHERNET_GENERIC_VERSION_MAJOR      2
#define ETHERNET_GENERIC_VERSION_MINOR      3
#define ETHERNET_GENERIC_VERSION_PATCH      1

#define ETHERNET_GENERIC_VERSION_INT        2003001

/////////////////////////////////////////////////////////

#if (USING_SPI2 || USING_CUSTOM_SPI)
  #define ETHERNET_GENERIC_USING_SPI2     true
  
  #if(_ETG_LOGLEVEL_> 3)
    #warning ETHERNET_GENERIC_USING_SPI2 in Ethernet_Generic.h
  #endif
#else
  #define ETHERNET_GENERIC_USING_SPI2     false
  
  #if(_ETG_LOGLEVEL_> 3)
    #warning ETHERNET_GENERIC_USING_SPI in Ethernet_Generic.h
  #endif
#endif

/////////////////////////////////////////////////////////

#include "Ethernet_Generic.hpp"
#include "Ethernet_Generic_Impl.h"

/////////////////////////////////////////////////////////

#endif    // ETHERNET_GENERIC_H
