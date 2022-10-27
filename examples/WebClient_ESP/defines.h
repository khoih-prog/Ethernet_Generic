/****************************************************************************************************************************
  defines.h

  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Generic
 ***************************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#if !( defined( ESP32 ) || defined(ESP8266) )
  #error This code is designed to run on ESP32 / ESP8266 platform! Please check your Tools->Board setting.
#endif

#define DEBUG_ETHERNET_GENERIC_PORT         Serial

// Debug Level from 0 to 4
#define _ETG_LOGLEVEL_                      2

// Default to use W5100. Must change to false for W5500, W5100S, for faster SPI clock
//#define USE_W5100                           true

#if ( defined(ESP8266) )
  // For ESP8266
  #include <ESP8266mDNS.h>
  #define ETHERNET_USE_ESP8266
  #define BOARD_TYPE      "ESP8266"

#elif ( defined(ESP32) )
  // For ESP32
  #define ETHERNET_USE_ESP32
  #define BOARD_TYPE      "ESP32"

  #define W5500_RST_PORT   21

#endif

#include <SPI.h>

#if defined( ESP32 )

  #include <soc/spi_pins.h>

  #define USING_SPI2              false

  #if USING_SPI2
    #define PIN_MISO          HSPI_IOMUX_PIN_NUM_MISO
    #define PIN_MOSI          HSPI_IOMUX_PIN_NUM_MOSI
    #define PIN_SCK           HSPI_IOMUX_PIN_NUM_CLK
    #define PIN_SS            HSPI_IOMUX_PIN_NUM_CS

    #define SHIELD_TYPE       "W5x00 using Ethernet_Generic Library on SPI2"

  #else

    #define PIN_MISO          MISO
    #define PIN_MOSI          MOSI
    #define PIN_SCK           SCK
    #define PIN_SS            SS

    #define SHIELD_TYPE       "W5x00 using Ethernet_Generic Library on SPI"

  #endif

#else

  #if USING_SPI2
    // To
    #define PIN_MISO          MISO
    #define PIN_MOSI          MOSI
    #define PIN_SCK           SCK
    #define PIN_SS            SS

    #define SHIELD_TYPE       "W5x00 using Ethernet_Generic Library on SPI2"

  #else

    #define PIN_MISO          MISO
    #define PIN_MOSI          MOSI
    #define PIN_SCK           SCK
    #define PIN_SS            SS

    #define SHIELD_TYPE       "W5x00 using Ethernet_Generic Library on SPI"

  #endif

#endif


///////////////////////////////////////////////////////////

// W5100 chips can have up to 4 sockets.  W5200 & W5500 can have up to 8 sockets.
// Use EthernetLarge feature, Larger buffers, but reduced number of simultaneous connections/sockets (MAX_SOCK_NUM == 2)
#define ETHERNET_LARGE_BUFFERS

//////////////////////////////////////////////////////////

#include "Ethernet_Generic.h"

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 222);

// Google DNS Server IP
IPAddress myDns(8, 8, 8, 8);

#endif    //defines_h
