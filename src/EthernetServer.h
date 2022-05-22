/****************************************************************************************************************************
  EthernetServer.h

  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries
  
  Based on and modified from 
  
  1) Ethernet Library         https://github.com/arduino-libraries/Ethernet
  2) EthernetLarge Library    https://github.com/OPEnSLab-OSU/EthernetLarge
  3) Ethernet2 Library        https://github.com/adafruit/Ethernet2
  4) Ethernet3 Library        https://github.com/sstaub/Ethernet3
    
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  
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

// This file is in the public domain.  No copyright is claimed.

#include "Ethernet_Generic.hpp"
