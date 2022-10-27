/****************************************************************************************************************************
  defines.h

  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Generic
 ***************************************************************************************************************************************/

#ifndef defines_h
#define defines_h

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

// Default to use W5100. Must change to false for W5500, W5100S, for faster SPI clock
//#define USE_W5100                           true

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
#if defined(ETHERNET_USE_SAMD)
  #undef ETHERNET_USE_SAMD
#endif
#define ETHERNET_USE_SAMD      true
#endif

#if (defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || \
      defined(NRF52840_CLUE) || defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || \
      defined(NRF52840_LED_GLASSES) || defined(MDBT50Q_RX) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) || \
      defined(ARDUINO_Seeed_XIAO_nRF52840) || defined(ARDUINO_Seeed_XIAO_nRF52840_Sense) )
#if defined(ETHERNET_USE_NRF528XX)
  #undef ETHERNET_USE_NRF528XX
#endif
#define ETHERNET_USE_NRF528XX      true
#endif

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ETHERNET_USE_SAM_DUE)
    #undef ETHERNET_USE_SAM_DUE
  #endif
  #define ETHERNET_USE_SAM_DUE      true
#endif

#if ( defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || defined(ARDUINO_GENERIC_RP2040) )
  #if defined(ETHERNET_USE_RPIPICO)
    #undef ETHERNET_USE_RPIPICO
  #endif
  #define ETHERNET_USE_RPIPICO      true
#endif

#if defined(ETHERNET_USE_SAMD)
  // For SAMD
  // Default pin SS/CS,if no SS pin, use pin 10
  #if defined(PIN_SPI_MOSI)
    //#warning Using SS pin
    #define USE_THIS_SS_PIN       10    //SS
  #else
    #define USE_THIS_SS_PIN       10
  #endif

  #if ( defined(ARDUINO_SAMD_ZERO) && !defined(SEEED_XIAO_M0) )
    #define BOARD_TYPE      "SAMD Zero"

    // Default to use W5100. Must change to false for W5500, W5100S, for faster SPI clock
    // Must use true for SAMD21, such as Zero, SAMD_FEATHER_M0_EXPRESS, etc.
    #define USE_W5100                           true

    // Use this for ARDUINO_SAMD_ZERO, etc. if can't print to terminal with Serial.print
    #if defined(SERIAL_PORT_USBVIRTUAL)
      #define Serial          SERIAL_PORT_USBVIRTUAL

      #if (_ETG_LOGLEVEL_ > 3)
        #warning Using SAMD Zero SerialUSB
      #endif
    #endif

  #elif defined(ARDUINO_SAMD_MKR1000)
    #define BOARD_TYPE      "SAMD MKR1000"
  #elif defined(ARDUINO_SAMD_MKRWIFI1010)
    #define BOARD_TYPE      "SAMD MKRWIFI1010"
  #elif defined(ARDUINO_SAMD_NANO_33_IOT)
    #define BOARD_TYPE      "SAMD NANO_33_IOT"
  #elif defined(ARDUINO_SAMD_MKRFox1200)
    #define BOARD_TYPE      "SAMD MKRFox1200"
  #elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
    #define BOARD_TYPE      "SAMD MKRWAN13X0"
  #elif defined(ARDUINO_SAMD_MKRGSM1400)
    #define BOARD_TYPE      "SAMD MKRGSM1400"
  #elif defined(ARDUINO_SAMD_MKRNB1500)
    #define BOARD_TYPE      "SAMD MKRNB1500"
  #elif defined(ARDUINO_SAMD_MKRVIDOR4000)
    #define BOARD_TYPE      "SAMD MKRVIDOR4000"
  #elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
    #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
  #elif defined(ADAFRUIT_FEATHER_M0_EXPRESS)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_FEATHER_M0_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M0_EXPRESS)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_METRO_M0_EXPRESS"
  #elif defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_CIRCUITPLAYGROUND_M0"
  #elif defined(ADAFRUIT_GEMMA_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_GEMMA_M0"
  #elif defined(ADAFRUIT_TRINKET_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_TRINKET_M0"
  #elif defined(ADAFRUIT_ITSYBITSY_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_ITSYBITSY_M0"
  #elif defined(ARDUINO_SAMD_HALLOWING_M0)
    #define BOARD_TYPE      "SAMD21 ARDUINO_SAMD_HALLOWING_M0"
  #elif defined(ADAFRUIT_METRO_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_EXPRESS"
  #elif defined(ADAFRUIT_GRAND_CENTRAL_M4)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_GRAND_CENTRAL_M4"
  #elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_FEATHER_M4_EXPRESS"
  #elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_ITSYBITSY_M4_EXPRESS"
    #define USE_THIS_SS_PIN       10
  #elif defined(ADAFRUIT_TRELLIS_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_TRELLIS_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYPORTAL)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL"
  #elif defined(ADAFRUIT_PYPORTAL_M4_TITANO)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL_M4_TITANO"
  #elif defined(ADAFRUIT_PYBADGE_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_M4_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_AIRLIFT_LITE"
  #elif defined(ADAFRUIT_PYGAMER_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYBADGE_AIRLIFT_M4)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_AIRLIFT_M4"
  #elif defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_MONSTER_M4SK_EXPRESS"
  #elif defined(ADAFRUIT_HALLOWING_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_HALLOWING_M4_EXPRESS"
  #elif defined(SEEED_WIO_TERMINAL)
    #define BOARD_TYPE      "SAMD SEEED_WIO_TERMINAL"
  #elif defined(SEEED_FEMTO_M0)
    #define BOARD_TYPE      "SAMD SEEED_FEMTO_M0"
  #elif defined(SEEED_XIAO_M0)
    #define BOARD_TYPE      "SAMD SEEED_XIAO_M0"
    #ifdef USE_THIS_SS_PIN
      #undef USE_THIS_SS_PIN
    #endif
    #define USE_THIS_SS_PIN       A1

    #if (_ETG_LOGLEVEL_ > 3)
      #warning define SEEED_XIAO_M0 USE_THIS_SS_PIN == A1
    #endif
  #elif defined(Wio_Lite_MG126)
    #define BOARD_TYPE      "SAMD SEEED Wio_Lite_MG126"
  #elif defined(WIO_GPS_BOARD)
    #define BOARD_TYPE      "SAMD SEEED WIO_GPS_BOARD"
  #elif defined(SEEEDUINO_ZERO)
    #define BOARD_TYPE      "SAMD SEEEDUINO_ZERO"
  #elif defined(SEEEDUINO_LORAWAN)
    #define BOARD_TYPE      "SAMD SEEEDUINO_LORAWAN"
  #elif defined(SEEED_GROVE_UI_WIRELESS)
    #define BOARD_TYPE      "SAMD SEEED_GROVE_UI_WIRELESS"
  #elif defined(__SAMD21E18A__)
    #define BOARD_TYPE      "SAMD21E18A"
  #elif defined(__SAMD21G18A__)
    #define BOARD_TYPE      "SAMD21G18A"
  #elif defined(__SAMD51G19A__)
    #define BOARD_TYPE      "SAMD51G19A"
  #elif defined(__SAMD51J19A__)
    #define BOARD_TYPE      "SAMD51J19A"
  #elif defined(__SAMD51J20A__)
    #define BOARD_TYPE      "SAMD51J20A"
  #elif defined(__SAM3X8E__)
    #define BOARD_TYPE      "SAM3X8E"
  #elif defined(__CPU_ARC__)
    #define BOARD_TYPE      "CPU_ARC"
  #elif defined(__SAMD51__)
    #define BOARD_TYPE      "SAMD51"
  #else
    #define BOARD_TYPE      "SAMD Unknown"
  #endif

#elif (ETHERNET_USE_SAM_DUE)
  // Default pin 10 to SS/CS
  #define USE_THIS_SS_PIN       10
  #define BOARD_TYPE      "SAM DUE"

#elif (ETHERNET_USE_NRF528XX)
  // For Adafruit nRF52
  // Default pin SS/CS,if no SS pin, use pin 10
  #if defined(PIN_SPI_MOSI)
    #if (_ETG_LOGLEVEL_ > 3)
      #warning Using SS pin
    #endif
    #define USE_THIS_SS_PIN       SS
  #else
    #define USE_THIS_SS_PIN       10
  #endif

  #if defined(ARDUINO_Seeed_XIAO_nRF52840)
    #define BOARD_TYPE      "Seeed_XIAO_nRF52840"
  #elif defined(ARDUINO_Seeed_XIAO_nRF52840_Sense)
    #define BOARD_TYPE      "Seeed_XIAO_nRF52840_Sense"
  #elif defined(ARDUINO_SEEED_XIAO_NRF52840)
    #define BOARD_TYPE      "SEEED_XIAO_NRF52840"
  #elif defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE)
    #define BOARD_TYPE      "SEEED_XIAO_NRF52840_SENSE"
  #elif defined(NRF52840_FEATHER)
    #define BOARD_TYPE      "NRF52840_FEATHER"
  #elif defined(NRF52832_FEATHER)
    #define BOARD_TYPE      "NRF52832_FEATHER"
  #elif defined(NRF52840_FEATHER_SENSE)
    #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
  #elif defined(NRF52840_ITSYBITSY)
    #define BOARD_TYPE      "NRF52840_ITSYBITSY"
    #define USE_THIS_SS_PIN   10    // For other boards
  #elif defined(NRF52840_CIRCUITPLAY)
    #define BOARD_TYPE      "NRF52840_CIRCUITPLAY"
  #elif defined(NRF52840_CLUE)
    #define BOARD_TYPE      "NRF52840_CLUE"
  #elif defined(NRF52840_METRO)
    #define BOARD_TYPE      "NRF52840_METRO"
  #elif defined(NRF52840_PCA10056)
    #define BOARD_TYPE      "NRF52840_PCA10056"
  #elif defined(NINA_B302_ublox)
    #define BOARD_TYPE      "NINA_B302_ublox"
  #elif defined(NINA_B112_ublox)
    #define BOARD_TYPE      "NINA_B112_ublox"
  #elif defined(PARTICLE_XENON)
    #define BOARD_TYPE      "PARTICLE_XENON"
  #elif defined(ARDUINO_NRF52_ADAFRUIT)
    #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
  #else
    #define BOARD_TYPE      "nRF52 Unknown"
  #endif

#elif ( defined(CORE_TEENSY) )
  // Default pin 10 to SS/CS
  #define USE_THIS_SS_PIN       SS    //10

  #if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    #if defined(ARDUINO_TEENSY41)
      #define BOARD_TYPE      "TEENSY 4.1"
      // Use true for NativeEthernet Library, false if using other Ethernet libraries
      #define USE_NATIVE_ETHERNET     true
    #elif defined(ARDUINO_TEENSY40)
      #define BOARD_TYPE      "TEENSY 4.0"
    #else
      #define BOARD_TYPE      "TEENSY 4.x"
    #endif
  #elif defined(__MK66FX1M0__)
    #define BOARD_TYPE "Teensy 3.6"
  #elif defined(__MK64FX512__)
    #define BOARD_TYPE "Teensy 3.5"
  #elif defined(__MKL26Z64__)
    #define BOARD_TYPE "Teensy LC"
  #elif defined(__MK20DX256__)
    #define BOARD_TYPE "Teensy 3.2" // and Teensy 3.1 (obsolete)
  #elif defined(__MK20DX128__)
    #define BOARD_TYPE "Teensy 3.0"
  #elif defined(__AVR_AT90USB1286__)
    #error Teensy 2.0++ not supported yet
  #elif defined(__AVR_ATmega32U4__)
    #error Teensy 2.0 not supported yet
  #else
    // For Other Boards
    #define BOARD_TYPE      "Unknown Teensy Board"
  #endif

#elif ( defined(ESP8266) )
  // For ESP8266
  #if (_ETG_LOGLEVEL_ > 3)
    #warning Use ESP8266 architecture
  #endif
  #include <ESP8266mDNS.h>
  #define ETHERNET_USE_ESP8266
  #define BOARD_TYPE      "ESP8266"

#elif ( defined(ESP32) )
  // For ESP32
  #if (_ETG_LOGLEVEL_ > 3)
    #warning Use ESP32 architecture
  #endif
  #define ETHERNET_USE_ESP32
  #define BOARD_TYPE      "ESP32"

  #define W5500_RST_PORT   21

#elif ETHERNET_USE_RPIPICO

  // Default pin 17 to SS/CS
  #if defined(ARDUINO_ARCH_MBED)
    // For RPI Pico using newer Arduino Mbed RP2040 core
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17

    #define USE_THIS_SS_PIN         PIN_SPI_SS    //17

    #if defined(BOARD_NAME)
      #undef BOARD_NAME
    #endif

    #if defined(ARDUINO_RASPBERRY_PI_PICO)
      #define BOARD_TYPE      "MBED RASPBERRY_PI_PICO"
    #elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
      #define BOARD_TYPE      "MBED ADAFRUIT_FEATHER_RP2040"
    #elif defined(ARDUINO_GENERIC_RP2040)
      #define BOARD_TYPE      "MBED GENERIC_RP2040"
    #else
      #define BOARD_TYPE      "MBED Unknown RP2040"
    #endif

  #else
    // For RPI Pico using E. Philhower RP2040 core
    #if (USING_SPI2)
      // SCK: GPIO14,  MOSI: GPIO15, MISO: GPIO12, SS/CS: GPIO13 for SPI1
      #define USE_THIS_SS_PIN       PIN_SPI1_SS   //13
    #else
      // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17 for SPI0
      #define USE_THIS_SS_PIN       PIN_SPI0_SS   //17
    #endif

  #endif

  #define SS_PIN_DEFAULT        USE_THIS_SS_PIN

  // For RPI Pico
  #if (_ETG_LOGLEVEL_ > 3)
    #warning Use RPI-Pico RP2040 architecture
  #endif

#elif defined(DXCORE)

  // Default pin 10 to SS/CS
  #define USE_THIS_SS_PIN       SS

  #if defined(__AVR_AVR128DA48__)
    #define BOARD_TYPE            "Curiosity AVR_AVR128DA48"
  #elif defined(__AVR_AVR128DB48__)
    #define BOARD_TYPE            "Curiosity AVR_AVR128DB48"
  #endif

#else
  // For Mega
  // Default pin 10 to SS/CS
  #define USE_THIS_SS_PIN       10

  // Reduce size for Mega
  #define SENDCONTENT_P_BUFFER_SZ     512

  #define BOARD_TYPE            "AVR Mega"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include <SPI.h>

///////////////////////////////////////////////////////////

// W5100 chips can have up to 4 sockets.  W5200 & W5500 can have up to 8 sockets.
// Use EthernetLarge feature, Larger buffers, but reduced number of simultaneous connections/sockets (MAX_SOCK_NUM == 2)
#define ETHERNET_LARGE_BUFFERS

//////////////////////////////////////////////////////////

// For boards supporting multiple hardware / software SPI buses, such as STM32
// Tested OK with Nucleo144 F767ZI and L552ZE_Q so far
#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) || defined(STM32L5) )

// Be sure to use true only if necessary for your board, or compile error
#define USING_CUSTOM_SPI            true

#if ( USING_CUSTOM_SPI )
  // Currently test OK for F767ZI and L552ZE_Q
  #define USING_SPI2                  true

  #if (USING_SPI2)
    //#include <SPI.h>
    // For L552ZE-Q, F767ZI, but you can change the pins for any other boards
    // SCK: 23,  MOSI: 22, MISO: 25, SS/CS: 24 for SPI1
    #define CUR_PIN_MISO              25
    #define CUR_PIN_MOSI              22
    #define CUR_PIN_SCK               23
    #define CUR_PIN_SS                24

    #define SPI_NEW_INITIALIZED       true

    // Don't create the instance with CUR_PIN_SS, or Ethernet not working
    // To change for other boards' SPI libraries
    SPIClass SPI_New(CUR_PIN_MOSI, CUR_PIN_MISO, CUR_PIN_SCK);

    //#warning Using USE_THIS_SS_PIN = CUR_PIN_SS = 24

    #if defined(USE_THIS_SS_PIN)
      #undef USE_THIS_SS_PIN
    #endif
    #define USE_THIS_SS_PIN       CUR_PIN_SS    //24

  #endif

#endif

#endif

//////////////////////////////////////////////////////////

#include "Ethernet_Generic.h"

#if defined(ETHERNET_LARGE_BUFFERS)
  #define SHIELD_TYPE           "W5x00 using Ethernet_Generic Library with Large Buffer"
#else
  #define SHIELD_TYPE           "W5x00 using Ethernet_Generic Library"
#endif

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
