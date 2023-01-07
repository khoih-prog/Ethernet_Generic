/****************************************************************************************************************************
  w5100_Impl.h - Driver for W5x00

  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries

  Based on and modified from

  1) Ethernet Library         https://github.com/arduino-libraries/Ethernet
  2) EthernetLarge Library    https://github.com/OPEnSLab-OSU/EthernetLarge
  3) Ethernet2 Library        https://github.com/adafruit/Ethernet2
  4) Ethernet3 Library        https://github.com/sstaub/Ethernet3

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer

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

#ifndef W5100_IMPL_H_
#define W5100_IMPL_H_

#include <Arduino.h>
#include "Ethernet_Generic.hpp"

#if !defined(_ETG_LOGLEVEL_)
  #define _ETG_LOGLEVEL_       4
#endif

#include "Ethernet_Generic_Debug.h"

#include "w5100.h"

#define W5100_DEBUG                     1

/***************************************************/
/**            Default SS pin setting             **/
/***************************************************/

// If variant.h or other headers specifically define the
// default SS pin for ethernet, use it.
#if defined(PIN_SPI_SS_ETHERNET_LIB)

  #if !defined(SS_PIN_DEFAULT)
    #define SS_PIN_DEFAULT  PIN_SPI_SS_ETHERNET_LIB
  #endif

  #if (_ETG_LOGLEVEL_ > 3)
    #warning w5100_Impl.h : Use PIN_SPI_SS_ETHERNET_LIB defined, change SS_PIN_DEFAULT to PIN_SPI_SS_ETHERNET_LIB
  #endif

  ////////////////////////////////////////

  // MKR boards default to pin 5 for MKR ETH
  // Pins 8-10 are MOSI/SCK/MISO on MRK, so don't use pin 10
#elif defined(USE_ARDUINO_MKR_PIN_LAYOUT) || defined(ARDUINO_SAMD_MKRZERO) || defined(ARDUINO_SAMD_MKR1000) || \
  defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRWAN1300) || \
  defined(ARDUINO_SAMD_MKRVIDOR4000)

  #if !defined(SS_PIN_DEFAULT)
    #define SS_PIN_DEFAULT  5
  #endif

  #if (_ETG_LOGLEVEL_ > 3)
    #warning w5100_Impl.h : Use MKR, change SS_PIN_DEFAULT to 5
  #endif

  ////////////////////////////////////////

  // For boards using AVR, assume shields with SS on pin 10
  // will be used.  This allows for Arduino Mega (where
  // SS is pin 53) and Arduino Leonardo (where SS is pin 17)
  // to work by default with Arduino Ethernet Shield R2 & R3.
#elif defined(__AVR__)

  #if !defined(SS_PIN_DEFAULT)
    #define SS_PIN_DEFAULT  10
  #endif

  #if (_ETG_LOGLEVEL_ > 3)
    #warning w5100_Impl.h : Use __AVR__, change SS_PIN_DEFAULT to 10
  #endif

  ////////////////////////////////////////

  // If variant.h or other headers define these names
  // use them if none of the other cases match
#elif defined(PIN_SPI_SS)

  #if defined(__SAMD21G18A__)

    #if (_ETG_LOGLEVEL_ > 3)
      //10 - 2 (6 conflict) all not OK for Nano 33 IoT !!! SPI corrupted???
      #warning w5100_Impl.h : Use __SAMD21G18A__, change SS_PIN_DEFAULT to 10
    #endif

    #if !defined(SS_PIN_DEFAULT)
      #define SS_PIN_DEFAULT  10
    #endif

  #else

    #if !defined(SS_PIN_DEFAULT)
      #define SS_PIN_DEFAULT  PIN_SPI_SS
    #endif

    #if (_ETG_LOGLEVEL_ > 3)
      #warning w5100_Impl.h : Use PIN_SPI_SS defined, change SS_PIN_DEFAULT to PIN_SPI_SS
    #endif

  #endif

  ////////////////////////////////////////

#elif defined(CORE_SS0_PIN)

  #if !defined(SS_PIN_DEFAULT)
    #define SS_PIN_DEFAULT  CORE_SS0_PIN
  #endif

  #if (_ETG_LOGLEVEL_ > 3)
    #warning w5100_Impl.h : Use CORE_SS0_PIN defined, change SS_PIN_DEFAULT to CORE_SS0_PIN
  #endif

  ////////////////////////////////////////

  //KH for ESP32
#elif defined(ESP32)

  #if (_ETG_LOGLEVEL_ > 3)
    //pin SS already defined in ESP32 as pin 5, don't use this as conflict with SPIFFS, EEPROM, etc.
    // Use in GPIO22
    #warning w5100_Impl.h : Use ESP32, change SS_PIN_DEFAULT to GPIO22, MOSI(23), MISO(19), SCK(18)
  #endif

  #if !defined(SS_PIN_DEFAULT)
    #define SS_PIN_DEFAULT  22    //SS
  #endif

  ////////////////////////////////////////

  //KH for ESP8266
#elif defined(ESP8266)

  #if (_ETG_LOGLEVEL_ > 3)
    //pin SS already defined in ESP8266 as pin 15. Conflict => Move to pin GPIO4 (D2)
    #warning w5100_Impl.h : Use ESP8266, change SS_PIN_DEFAULT to SS(4), MOSI(13), MISO(12), SCK(14)
  #endif

  #if !defined(SS_PIN_DEFAULT)
    #define SS_PIN_DEFAULT  D2      // GPIO4, SS
  #endif

  ////////////////////////////////////////

  // As a final fallback, use pin 10
#else

  #if !defined(SS_PIN_DEFAULT)
    #define SS_PIN_DEFAULT  10
  #endif

  #if (_ETG_LOGLEVEL_ > 3)
    //KH
    #warning w5100_Impl.h : Use fallback, change SS_PIN_DEFAULT to 10
  #endif

#endif

////////////////////////////////////////

// W5100 controller instance
EthernetChip_t  W5100Class::chip    = noChip;

//KH
EthernetChip_t  W5100Class::altChip = noChip;
//////

uint8_t         W5100Class::CH_BASE_MSB;

#if USING_W6100
  uint16_t      W5100Class::CH_SIZE;
#endif

uint8_t         W5100Class::ss_pin = SS_PIN_DEFAULT;

#ifdef ETHERNET_LARGE_BUFFERS
  uint16_t W5100Class::SSIZE = 2048;
  uint16_t W5100Class::SMASK = 0x07FF;
#endif

////////////////////////////////////////

W5100Class W5100;

////////////////////////////////////////

#if (ETHERNET_GENERIC_USING_SPI2)

  #if(_ETG_LOGLEVEL_> 2)
    #warning ETHERNET_GENERIC_USING_SPI2 in w5100_Impl.h
  #endif

  #if defined(ESP32)
    SPIClass SPI2(HSPI);
    SPIClass* pCUR_SPI = &SPI2;
  #elif (ETHERNET_USE_RPIPICO && !defined(ARDUINO_ARCH_MBED))
    // For arduino-pico core
    // SPIClassRP2040(spi_inst_t *spi, pin_size_t rx, pin_size_t cs, pin_size_t sck, pin_size_t tx);
    SPIClass* pCUR_SPI = (SPIClass*) &SPI1;

    #define CUR_PIN_MISO      PIN_SPI1_MISO
    #define CUR_PIN_MOSI      PIN_SPI1_MOSI
    #define CUR_PIN_SCK       PIN_SPI1_SCK
    #define CUR_PIN_SS        PIN_SPI1_SS

  #elif (USING_CUSTOM_SPI)

    #if ( defined(CUR_PIN_MOSI) && defined(CUR_PIN_MISO) && defined(CUR_PIN_SCK) && defined(CUR_PIN_SS) )
      #if (SPI_NEW_INITIALIZED)
        #if(_ETG_LOGLEVEL_> 2)
          #warning ETHERNET_GENERIC_USING_SPI2 with SPI_NEW_INITIALIZED in w5100_Impl.h
        #endif
      #else
        #if(_ETG_LOGLEVEL_> 2)
          #warning ETHERNET_GENERIC_USING_SPI2 without SPI_NEW_INITIALIZED in w5100_Impl.h
        #endif

        #if defined(ARDUINO_ARCH_MBED)
          // Don't create the instance with CUR_PIN_SS, or Ethernet not working
          // Be careful, Mbed SPI ctor is so weird, reversing the order => MISO, MOSI, SCK
          //arduino::MbedSPI::MbedSPI(int miso, int mosi, int sck)
          SPIClass SPI_New(CUR_PIN_MISO, CUR_PIN_MOSI, CUR_PIN_SCK);
        #else
          // Don't create the instance with CUR_PIN_SS, or Ethernet not working
          SPIClass SPI_New(CUR_PIN_MOSI, CUR_PIN_MISO, CUR_PIN_SCK);
        #endif
      #endif

      SPIClass* pCUR_SPI = (SPIClass*) &SPI_New;

    #else
      #error You must define CUR_PIN_MOSI, CUR_PIN_MISO, CUR_PIN_SCK and CUR_PIN_SS
    #endif

  #endif

#else
  #if(_ETG_LOGLEVEL_> 2)
    #warning ETHERNET_GENERIC_USING_SPI in w5100_Impl.h
  #endif

  SPIClass* pCUR_SPI = &SPI;
#endif

////////////////////////////////////////

// pointers and bitmasks for optimized SS pin
#if defined(__AVR__)
  volatile uint8_t * W5100Class::ss_pin_reg;
  uint8_t W5100Class::ss_pin_mask;
#elif defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK66FX1M0__) || defined(__MK64FX512__)
  volatile uint8_t * W5100Class::ss_pin_reg;
#elif defined(__IMXRT1062__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(__MKL26Z64__)
  volatile uint8_t * W5100Class::ss_pin_reg;
  uint8_t W5100Class::ss_pin_mask;
#elif defined(__SAM3X8E__) || defined(__SAM3A8C__) || defined(__SAM3A4C__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(__PIC32MX__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(ARDUINO_ARCH_ESP8266)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(__SAMD21G18A__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;

  #if (_ETG_LOGLEVEL_ > 3)
    #warning w5100_Impl.h : Use __SAMD21G18A__
  #endif
#endif

////////////////////////////////////////

uint8_t W5100Class::init(uint8_t socketNumbers, uint8_t new_ss_pin)
{
  (void) socketNumbers;

  uint8_t i;

  if (initialized)
    return 1;

  // Many Ethernet shields have a CAT811 or similar reset chip
  // connected to W5100 or W5200 chips.  The W5200 will not work at
  // all, and may even drive its MISO pin, until given an active low
  // reset pulse!  The CAT811 has a 240 ms typical pulse length, and
  // a 400 ms worst case maximum pulse length.  MAX811 has a worst
  // case maximum 560 ms pulse length.  This delay is meant to wait
  // until the reset pulse is ended.  If your hardware has a shorter
  // reset time, this can be edited or removed.
  delay(560);

  //ETG_LOGWARN5("W5100 init, using SS_PIN_DEFAULT =", SS_PIN_DEFAULT, ", new ss_pin = ", new_ss_pin,
  //              ", W5100Class::ss_pin = ", W5100Class::ss_pin);
  ETG_LOGWARN5("W5100 init, using W5100Class::ss_pin = ", W5100Class::ss_pin, ", whereas new ss_pin = ", new_ss_pin,
               ", SS_PIN_DEFAULT =", SS_PIN_DEFAULT);

  CH_SIZE = 0x0100; // Default except W6100

  pCUR_SPI->begin();

  initSS();
  resetSS();

  // Removed from v2.6.1 for W5200. Tested OK with W5500, W5100S, W5100
  // Check https://github.com/khoih-prog/Ethernet_Generic/discussions/13
  //softReset();
  //////

  // From #define SPI_ETHERNET_SETTINGS SPISettings(14000000, MSBFIRST, SPI_MODE0)
  beginSPITransaction();

  // Attempt W5200 detection first, because W5200 does not properly
  // reset its SPI state when CS goes high (inactive).  Communication
  // from detecting the other chips can leave the W5200 in a state
  // where it won't recover, unless given a reset pulse.

  if (isW5200())
  {
    CH_BASE_MSB = 0x40;

#ifdef ETHERNET_LARGE_BUFFERS
#if MAX_SOCK_NUM <= 1
    SSIZE = 16384;
#elif MAX_SOCK_NUM <= 2
    SSIZE = 8192;
#elif MAX_SOCK_NUM <= 4
    SSIZE = 4096;
#else
    SSIZE = 2048;
#endif
    SMASK = SSIZE - 1;
#endif

    for (i = 0; i < MAX_SOCK_NUM; i++)
    {
      writeSnRX_SIZE(i, SSIZE >> 10);
      writeSnTX_SIZE(i, SSIZE >> 10);
    }

    for (; i < 8; i++)
    {
      writeSnRX_SIZE(i, 0);
      writeSnTX_SIZE(i, 0);
    }

    ETG_LOGWARN1("W5100::init: W5200, SSIZE =", SSIZE);

    // Try W5500 next.  WIZnet finally seems to have implemented
    // SPI well with this chip.  It appears to be very resilient,
    // so try it after the fragile W5200
  }
  else if (isW5500())
  {
    CH_BASE_MSB = 0x10;

#ifdef ETHERNET_LARGE_BUFFERS
#if MAX_SOCK_NUM <= 1
    SSIZE = 16384;
#elif MAX_SOCK_NUM <= 2
    SSIZE = 8192;
#elif MAX_SOCK_NUM <= 4
    SSIZE = 4096;
#else
    SSIZE = 2048;
#endif

    SMASK = SSIZE - 1;

    for (i = 0; i < MAX_SOCK_NUM; i++)
    {
      writeSnRX_SIZE(i, SSIZE >> 10);
      writeSnTX_SIZE(i, SSIZE >> 10);
    }

    for (; i < 8; i++)
    {
      writeSnRX_SIZE(i, 0);
      writeSnTX_SIZE(i, 0);
    }

#endif

    ETG_LOGWARN1("W5100::init: W5500, SSIZE =", SSIZE);

    // Try W5100 last.  This simple chip uses fixed 4 byte frames
    // for every 8 bit access.  Terribly inefficient, but so simple
    // it recovers from "hearing" unsuccessful W5100 or W5200
    // communication.  W5100 is also the only chip without a VERSIONR
    // register for identification, so we check this last.
  }
  else if (isW5100())
  {
    CH_BASE_MSB = 0x04;

#ifdef ETHERNET_LARGE_BUFFERS

#if MAX_SOCK_NUM <= 1
    SSIZE = 8192;
    writeTMSR(0x03);
    writeRMSR(0x03);
#else
    SSIZE = 4096;
    writeTMSR(0x0A);
    writeRMSR(0x0A);
#endif

    SMASK = SSIZE - 1;
#else

    writeTMSR(0x55);
    writeRMSR(0x55);
#endif

    ETG_LOGWARN1("W5100::init: W5100, SSIZE =", SSIZE);

    // No hardware seems to be present.  Or it could be a W5200
    // that's heard other SPI communication if its chip select
    // pin wasn't high when a SD card or other SPI chip was used.
  }
  else if (isW5100S())
  {
    CH_BASE_MSB = 0x04;

#ifdef ETHERNET_LARGE_BUFFERS

#if MAX_SOCK_NUM <= 1
    SSIZE = 8192;
    writeTMSR(0x03);
    writeRMSR(0x03);
#else
    SSIZE = 4096;
    writeTMSR(0x0A);
    writeRMSR(0x0A);
#endif

    SMASK = SSIZE - 1;
#else

    writeTMSR(0x55);
    writeRMSR(0x55);
#endif

    ETG_LOGWARN1("W5100::init: W5100S, SSIZE =", SSIZE);

    // Try W5500 next.  WIZnet finally seems to have implemented
    // SPI well with this chip.  It appears to be very resilient,
    // so try it after the fragile W5200
  }

  ////////////////////////////////////////

#if USING_W6100

  else if (isW6100())
  {
    CH_BASE_MSB = 0x60;
    CH_SIZE = 0x0400; // W6100

#ifdef ETHERNET_LARGE_BUFFERS

#if MAX_SOCK_NUM <= 1
    SSIZE = 16384;
#elif MAX_SOCK_NUM <= 2
    SSIZE = 8192;
#elif MAX_SOCK_NUM <= 4
    SSIZE = 4096;
#else
    SSIZE = 2048;
#endif

    SMASK = SSIZE - 1;

    for (i = 0; i < MAX_SOCK_NUM; i++)
    {
      writeSnRX_SIZE(i, SSIZE >> 10);
      writeSnTX_SIZE(i, SSIZE >> 10);
    }

    for (; i < 8; i++)
    {
      writeSnRX_SIZE(i, 0);
      writeSnTX_SIZE(i, 0);
    }

#endif
    // No hardware seems to be present.  Or it could be a W5200
    // that's heard other SPI communication if its chip select
    // pin wasn't high when a SD card or other SPI chip was used.
  }

#endif  // USING_W6100

  ////////////////////////////////////////

  else
  {
    ETG_LOGERROR("W5100::init: no chip :-(");

    chip = noChip;

    endSPITransaction();

    return 0; // no known chip is responding :-(
  }

  endSPITransaction();

  initialized = true;

  return 1; // successful init
}

////////////////////////////////////////

// Soft reset the WIZnet chip, by writing to its MR register reset bit
uint8_t W5100Class::softReset()
{
  uint16_t count = 0;

  ////////////////////////////////////////

#if USING_W6100

  ////////////////////////////////////////

  if (chip == w6100)
  {
    ETG_LOGDEBUG("W6100::softReset");

    writeCHPLCKR_W6100(W6100_CHPLCKR_UNLOCK);   // Unlock SYSR[CHPL]
    count = 0;

    do
    {
      // Wait Unlock Complete
      if (++count > 20)
      {
        // Check retry count
        return 0;               // Over Limit retry count
      }
    } while ((readSYSR_W6100() & W6100_SYSR_CHPL_LOCK) ^ W6100_SYSR_CHPL_ULOCK);  // Exit Wait Unlock Complete

    writeSYCR0(0x0);            // Software Reset

    do
    {
      // Wait Lock Complete
      if (++count > 20)
      {
        // Check retry count
        return 0;               // Over Limit retry count
      }

    } while ((readSYSR_W6100() & W6100_SYSR_CHPL_LOCK) ^ W6100_SYSR_CHPL_LOCK); // Exit Wait Lock Complete

    return 1;
  }
  else
  {

    ETG_LOGDEBUG("W5x00::softReset");

    // write to reset bit
    writeMR(0x80);

    // then wait for soft reset to complete
    do
    {
      uint8_t mr = readMR();

      ETG_LOGDEBUG1("W5x00::softReset, mr =", mr);

      if (mr == 0)
        return 1;

      delay(1);
    } while (++count < 20);

    return 0;
  }

  ////////////////////////////////////////

#else   // USING_W6100

  ////////////////////////////////////////

  ETG_LOGDEBUG("W5x00::softReset");

  // write to reset bit
  writeMR(0x80);

  // then wait for soft reset to complete
  do
  {
    uint8_t mr = readMR();

    ETG_LOGDEBUG1("W5x00::softReset, mr =", mr);

    if (mr == 0)
      return 1;

    delay(1);
  } while (++count < 20);

  return 0;

  ////////////////////////////////////////

#endif  // USING_W6100

  ////////////////////////////////////////

}

////////////////////////////////////////

#if USING_W6100

////////////////////////////////////////

uint8_t W5100Class::isW6100()
{
  chip = w6100;
  altChip = noChip;
  
  CH_BASE_MSB = 0x80;

  ETG_LOGDEBUG("isW6100: detect W6100 chip");

  if (!softReset())
    return 0;

  // Unlock
  writeCHPLCKR_W6100(W6100_CHPLCKR_UNLOCK);
  writeNETLCKR_W6100(W6100_NETLCKR_UNLOCK);
  writePHYLCKR_W6100(W6100_PHYLCKR_UNLOCK);

  // W6100 CIDR0
  // Version 97(dec) 0x61(hex)
  int ver = readVERSIONR_W6100();

  ETG_LOGDEBUG1("Version =", ver);

  if (ver != 97)
    return 0;

  ETG_LOGWARN("Chip is W6100");

  return 1;
}

////////////////////////////////////////

#endif    // USING_W6100

////////////////////////////////////////

uint8_t W5100Class::isW5100()
{
  chip = w5100;

  ETG_LOGDEBUG("isW5100: detect W5100 chip");

  if (!softReset())
    return 0;

  writeMR(0x10);

  if (readMR() != 0x10)
    return 0;

  writeMR(0x12);

  if (readMR() != 0x12)
    return 0;

  writeMR(0x00);

  if (readMR() != 0x00)
    return 0;

  ETG_LOGWARN("Chip is W5100");

  return 1;
}

////////////////////////////////////////

uint8_t W5100Class::isW5100S()
{
  chip = w5100s;  // Must use w5100s before softReset()

  // For other functions specific to W5100S, such as LinkStatus. etc
  altChip = w5100s;

  ETG_LOGDEBUG("isW5100S: detect W5100S chip");

  if (!softReset())
    return 0;

  chip = w5100;   // using w5100 after softReset() => read correct registers

  writeMR(0x13);

  if (readMR() != 0x13)
  {
    ETG_LOGDEBUG1("readMR (19) =", readMR());
    return 0;
  }

  writeMR(0x1B);

  if (readMR() != 0x1B)
  {
    ETG_LOGDEBUG1("readMR (27) =", readMR());
    return 0;
  }

  writeMR(0x03);

  if (readMR() != 0x03)
  {
    ETG_LOGDEBUG1("readMR (03) =", readMR());
    return 0;
  }

  int ver = readVERSIONR_W5100S();

  ETG_LOGDEBUG1("Version =", ver);

  if (ver != 81)
    return 0;

  ETG_LOGWARN("Chip is W5100S");

  return 1;
}

////////////////////////////////////////

uint8_t W5100Class::isW5200()
{
  chip = w5200;

  ETG_LOGDEBUG("isW5200: detect W5200 chip");

  if (!softReset())
    return 0;

  writeMR(0x08);

  if (readMR() != 0x08)
    return 0;

  writeMR(0x10);

  if (readMR() != 0x10)
    return 0;

  writeMR(0x00);

  if (readMR() != 0x00)
    return 0;

  int ver = readVERSIONR_W5200();

  ETG_LOGDEBUG1("Version =", ver);

  if (ver != 3)
    return 0;

  ETG_LOGWARN("Chip is W5200");

  return 1;
}

////////////////////////////////////////

uint8_t W5100Class::isW5500()
{
  chip = w5500;

  ETG_LOGDEBUG("isW5500: detect W5500 chip");

  if (!softReset())
    return 0;

  writeMR(0x08);

  if (readMR() != 0x08)
    return 0;

  writeMR(0x10);

  if (readMR() != 0x10)
    return 0;

  writeMR(0x00);

  if (readMR() != 0x00)
    return 0;

  int ver = readVERSIONR_W5500();

  ETG_LOGDEBUG1("Version =", ver);

  if (ver != 4)
    return 0;

  ETG_LOGWARN("Chip is W5500");

  return 1;
}

////////////////////////////////////////

W5100Linkstatus W5100Class::getLinkStatus()
{
  uint8_t phystatus;

  if (!initialized)
    return UNKNOWN;

  switch (chip)
  {
    case w5100s:
      beginSPITransaction();
      phystatus = readPHYCFGR_W5100S();
      endSPITransaction();

      if (phystatus & 0x01)
        return LINK_ON;

      return LINK_OFF;

    case w5200:
      beginSPITransaction();
      phystatus = readPSTATUS_W5200();
      endSPITransaction();

      if (phystatus & 0x20)
        return LINK_ON;

      return LINK_OFF;

    case w5500:
      beginSPITransaction();
      phystatus = readPHYCFGR_W5500();
      endSPITransaction();

      if (phystatus & 0x01)
        return LINK_ON;

      return LINK_OFF;

#if USING_W6100

    case w6100:
      beginSPITransaction();
      phystatus = readPHYCFGR_W6100();
      endSPITransaction();

      if (phystatus & 0x01)
        return LINK_ON;

      return LINK_OFF;

#endif    // USING_W6100

    default:
      return UNKNOWN;
  }
}

////////////////////////////////////////

uint16_t W5100Class::write(uint16_t addr, const uint8_t *buf, uint16_t len)
{
  uint8_t cmd[8];

  if (chip == w5100)
  {
    for (uint16_t i = 0; i < len; i++)
    {
      setSS();
      pCUR_SPI->transfer(0xF0);
      pCUR_SPI->transfer(addr >> 8);
      pCUR_SPI->transfer(addr & 0xFF);
      addr++;
      pCUR_SPI->transfer(buf[i]);
      resetSS();
    }
  }
  else if ( (chip == w5100s) )
  {
    setSS();
    cmd[0] = addr >> 8;
    cmd[1] = addr & 0xFF;
    cmd[2] = ((len >> 8) & 0x7F) | 0x80;
    cmd[3] = len & 0xFF;
    pCUR_SPI->transfer(cmd, 4);

#ifdef SPI_HAS_TRANSFER_BUF
    pCUR_SPI->transfer(buf, NULL, len);
#else

    // TODO: copy 8 bytes at a time to cmd[] and block transfer
    for (uint16_t i = 0; i < len; i++)
    {
      pCUR_SPI->transfer(buf[i]);
    }

#endif
    resetSS();
  }
  else if (chip == w5200)
  {
    setSS();
    cmd[0] = addr >> 8;
    cmd[1] = addr & 0xFF;
    cmd[2] = ((len >> 8) & 0x7F) | 0x80;
    cmd[3] = len & 0xFF;
    pCUR_SPI->transfer(cmd, 4);

#ifdef SPI_HAS_TRANSFER_BUF
    pCUR_SPI->transfer(buf, NULL, len);
#else

    // TODO: copy 8 bytes at a time to cmd[] and block transfer
    for (uint16_t i = 0; i < len; i++)
    {
      pCUR_SPI->transfer(buf[i]);
    }

#endif
    resetSS();
  }

  ////////////////////////////////////////

#if USING_W6100

  else if (chip == w6100)
  {
    // chip == w6100
    setSS();

    if (addr < CH_BASE())
    {
      // common registers

      cmd[0] = (addr >> 8) & 0x7F;
      cmd[1] = addr & 0xFF;
      cmd[2] = W6100_SPI_FRAME_CTL_BSB_BLK(0) | W6100_SPI_FRAME_CTL_BSB_COMM |
               W6100_SPI_FRAME_CTL_WD         | W6100_SPI_FRAME_CTL_OPM_VDM;
    }
    else if (addr < W6100_TX_BASE_ADDR)
    {
      // socket registers

      cmd[0] = (addr >> 8) & 0x3;
      cmd[1] = addr & 0xFF;
      cmd[2] = W6100_SPI_FRAME_CTL_BSB_BLK((addr >> 10) & 0x7) | W6100_SPI_FRAME_CTL_BSB_SOCK |
               W6100_SPI_FRAME_CTL_WD | W6100_SPI_FRAME_CTL_OPM_VDM;
    }
    else if (addr < W6100_RX_BASE_ADDR)
    {
      // transmit buffers

      cmd[0] = addr >> 8;
      cmd[1] = addr & 0xFF;

#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
      cmd[2] = 0;           // 16K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
      cmd[2] = ((addr >> 8) & 0x20);  // 8K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
      cmd[2] = ((addr >> 7) & 0x60);  // 4K buffers
#else
      cmd[2] = ((addr >> 6) & 0xE0);  // 2K buffers
#endif

      cmd[2] |= W6100_SPI_FRAME_CTL_BSB_BLK(0) |  W6100_SPI_FRAME_CTL_BSB_TXBF |
                W6100_SPI_FRAME_CTL_WD         |  W6100_SPI_FRAME_CTL_OPM_VDM;
    }
    else
    {
      // receive buffers

      cmd[0] = addr >> 8;
      cmd[1] = addr & 0xFF;

#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
      cmd[2] = 0;           // 16K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
      cmd[2] = ((addr >> 8) & 0x20);  // 8K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
      cmd[2] = ((addr >> 7) & 0x60);  // 4K buffers
#else
      cmd[2] = ((addr >> 6) & 0xE0);  // 2K buffers
#endif

      cmd[2] |= W6100_SPI_FRAME_CTL_BSB_BLK(0) | W6100_SPI_FRAME_CTL_BSB_RXBF |
                W6100_SPI_FRAME_CTL_WD         | W6100_SPI_FRAME_CTL_OPM_VDM;
    }

    if (len <= 5)
    {
      for (uint8_t i = 0; i < len; i++)
      {
        cmd[i + 3] = buf[i];
      }

      pCUR_SPI->transfer(cmd, len + 3);
    }
    else
    {
      pCUR_SPI->transfer(cmd, 3);

#ifdef SPI_HAS_TRANSFER_BUF
      pCUR_SPI->transfer(buf, NULL, len);
#else

      // TODO: copy 8 bytes at a time to cmd[] and block transfer
      for (uint16_t i = 0; i < len; i++)
      {
        pCUR_SPI->transfer(buf[i]);
      }

#endif
    }

    resetSS();
  }

#endif    // W6100

  ////////////////////////////////////////

  else
  {
    // chip == w5500
    setSS();

    if (addr < 0x100)
    {
      // common registers 00nn
      cmd[0] = 0;
      cmd[1] = addr & 0xFF;
      cmd[2] = 0x04;
    }
    else if (addr < 0x8000)
    {
      // socket registers  10nn, 11nn, 12nn, 13nn, etc
      cmd[0] = 0;
      cmd[1] = addr & 0xFF;
      cmd[2] = ((addr >> 3) & 0xE0) | 0x0C;
    }
    else if (addr < 0xC000)
    {
      // transmit buffers  8000-87FF, 8800-8FFF, 9000-97FF, etc
      //  10## #nnn nnnn nnnn
      cmd[0] = addr >> 8;
      cmd[1] = addr & 0xFF;

#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
      cmd[2] = 0x14;                       // 16K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
      cmd[2] = ((addr >> 8) & 0x20) | 0x14; // 8K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
      cmd[2] = ((addr >> 7) & 0x60) | 0x14; // 4K buffers
#else
      cmd[2] = ((addr >> 6) & 0xE0) | 0x14; // 2K buffers
#endif
    }
    else
    {
      // receive buffers
      cmd[0] = addr >> 8;
      cmd[1] = addr & 0xFF;
#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
      cmd[2] = 0x1C;                       // 16K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
      cmd[2] = ((addr >> 8) & 0x20) | 0x1C; // 8K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
      cmd[2] = ((addr >> 7) & 0x60) | 0x1C; // 4K buffers
#else
      cmd[2] = ((addr >> 6) & 0xE0) | 0x1C; // 2K buffers
#endif
    }

    if (len <= 5)
    {
      for (uint8_t i = 0; i < len; i++)
      {
        cmd[i + 3] = buf[i];
      }

      pCUR_SPI->transfer(cmd, len + 3);
    }
    else
    {
      pCUR_SPI->transfer(cmd, 3);
#ifdef SPI_HAS_TRANSFER_BUF
      pCUR_SPI->transfer(buf, NULL, len);
#else

      // TODO: copy 8 bytes at a time to cmd[] and block transfer
      for (uint16_t i = 0; i < len; i++)
      {
        pCUR_SPI->transfer(buf[i]);
      }

#endif
    }

    resetSS();
  }

  return len;
}

////////////////////////////////////////

uint16_t W5100Class::read(uint16_t addr, uint8_t *buf, uint16_t len)
{
  uint8_t cmd[4];

  if ( (chip == w5100))
  {
    for (uint16_t i = 0; i < len; i++)
    {
      setSS();

      pCUR_SPI->transfer(0x0F);
      pCUR_SPI->transfer(addr >> 8);
      pCUR_SPI->transfer(addr & 0xFF);
      addr++;
      buf[i] = pCUR_SPI->transfer(0);

      resetSS();
    }
  }
  else if ( (chip == w5100s) )
  {
    setSS();
    cmd[0] = addr >> 8;
    cmd[1] = addr & 0xFF;
    cmd[2] = (len >> 8) & 0x7F;
    cmd[3] = len & 0xFF;
    pCUR_SPI->transfer(cmd, 4);
    memset(buf, 0, len);
    pCUR_SPI->transfer(buf, len);

    resetSS();
  }
  else if (chip == w5200)
  {
    setSS();
    cmd[0] = addr >> 8;
    cmd[1] = addr & 0xFF;
    cmd[2] = (len >> 8) & 0x7F;
    cmd[3] = len & 0xFF;
    pCUR_SPI->transfer(cmd, 4);
    memset(buf, 0, len);
    pCUR_SPI->transfer(buf, len);

    resetSS();
  }


  ////////////////////////////////////////

#if USING_W6100

  else if (chip == w6100)
  {
    // chip == w6100
    setSS();

    if (addr < CH_BASE())
    {
      // common registers

      cmd[0] = (addr >> 8) & 0x7F;
      cmd[1] = addr & 0xFF;
      cmd[2] = W6100_SPI_FRAME_CTL_BSB_BLK(0) | W6100_SPI_FRAME_CTL_BSB_COMM |
               W6100_SPI_FRAME_CTL_RD         | W6100_SPI_FRAME_CTL_OPM_VDM;
    }
    else if (addr < W6100_TX_BASE_ADDR)
    {
      // socket registers

      cmd[0] = (addr >> 8) & 0x3;
      cmd[1] = addr & 0xFF;
      cmd[2] = W6100_SPI_FRAME_CTL_BSB_BLK((addr >> 10) & 0x7) |  W6100_SPI_FRAME_CTL_BSB_SOCK |
               W6100_SPI_FRAME_CTL_RD | W6100_SPI_FRAME_CTL_OPM_VDM;
    }
    else if (addr < W6100_RX_BASE_ADDR)
    {
      // transmit buffers

      cmd[0] = addr >> 8;
      cmd[1] = addr & 0xFF;

#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
      cmd[2] = 0;           // 16K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
      cmd[2] = ((addr >> 8) & 0x20);  // 8K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
      cmd[2] = ((addr >> 7) & 0x60);  // 4K buffers
#else
      cmd[2] = ((addr >> 6) & 0xE0);  // 2K buffers
#endif

      cmd[2] |= W6100_SPI_FRAME_CTL_BSB_BLK(0) | W6100_SPI_FRAME_CTL_BSB_TXBF |
                W6100_SPI_FRAME_CTL_RD         | W6100_SPI_FRAME_CTL_OPM_VDM;
    }
    else
    {
      // receive buffers

      cmd[0] = addr >> 8;
      cmd[1] = addr & 0xFF;

#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
      cmd[2] = 0;           // 16K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
      cmd[2] = ((addr >> 8) & 0x20);  // 8K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
      cmd[2] = ((addr >> 7) & 0x60);  // 4K buffers
#else
      cmd[2] = ((addr >> 6) & 0xE0);  // 2K buffers
#endif

      cmd[2] |= W6100_SPI_FRAME_CTL_BSB_BLK(0) | W6100_SPI_FRAME_CTL_BSB_RXBF |
                W6100_SPI_FRAME_CTL_RD         | W6100_SPI_FRAME_CTL_OPM_VDM;
    }

    pCUR_SPI->transfer(cmd, 3);
    memset(buf, 0, len);
    pCUR_SPI->transfer(buf, len);

    resetSS();
  }

#endif    // USING_W6100

  ////////////////////////////////////////

  else
  {
    // chip == w5500
    setSS();

    if (addr < 0x100)
    {
      // common registers 00nn
      cmd[0] = 0;
      cmd[1] = addr & 0xFF;
      cmd[2] = 0x00;
    }
    else if (addr < 0x8000)
    {
      // socket registers  10nn, 11nn, 12nn, 13nn, etc
      cmd[0] = 0;
      cmd[1] = addr & 0xFF;
      cmd[2] = ((addr >> 3) & 0xE0) | 0x08;
    }
    else if (addr < 0xC000)
    {
      // transmit buffers  8000-87FF, 8800-8FFF, 9000-97FF, etc
      //  10## #nnn nnnn nnnn
      cmd[0] = addr >> 8;
      cmd[1] = addr & 0xFF;

#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
      cmd[2] = 0x10;                       // 16K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
      cmd[2] = ((addr >> 8) & 0x20) | 0x10; // 8K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
      cmd[2] = ((addr >> 7) & 0x60) | 0x10; // 4K buffers
#else
      cmd[2] = ((addr >> 6) & 0xE0) | 0x10; // 2K buffers
#endif
    }
    else
    {
      // receive buffers
      cmd[0] = addr >> 8;
      cmd[1] = addr & 0xFF;
#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
      cmd[2] = 0x18;                       // 16K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
      cmd[2] = ((addr >> 8) & 0x20) | 0x18; // 8K buffers
#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
      cmd[2] = ((addr >> 7) & 0x60) | 0x18; // 4K buffers
#else
      cmd[2] = ((addr >> 6) & 0xE0) | 0x18; // 2K buffers
#endif
    }

    pCUR_SPI->transfer(cmd, 3);
    memset(buf, 0, len);
    pCUR_SPI->transfer(buf, len);
    resetSS();
  }

  return len;
}

////////////////////////////////////////

// From Ethernet3

void W5100Class::phyMode(phyMode_t mode)
{
  // Valid only for W5500
  if (chip != w5500)
    return;

  uint8_t val = getPHYCFGR();
  bitWrite(val, 6, 1);

  if (mode == HALF_DUPLEX_10)
  {
    bitWrite(val, 3, 0);
    bitWrite(val, 4, 0);
    bitWrite(val, 5, 0);
    setPHYCFGR(val);
  }
  else if (mode == FULL_DUPLEX_10)
  {
    bitWrite(val, 3, 1);
    bitWrite(val, 4, 0);
    bitWrite(val, 5, 0);
    setPHYCFGR(val);
  }
  else if (mode == HALF_DUPLEX_100)
  {
    bitWrite(val, 3, 0);
    bitWrite(val, 4, 1);
    bitWrite(val, 5, 0);
    setPHYCFGR(val);
  }
  else if (mode == FULL_DUPLEX_100)
  {
    bitWrite(val, 3, 1);
    bitWrite(val, 4, 1);
    bitWrite(val, 5, 0);
    setPHYCFGR(val);
  }
  else if (mode == FULL_DUPLEX_100_AUTONEG)
  {
    bitWrite(val, 3, 0);
    bitWrite(val, 4, 0);
    bitWrite(val, 5, 1);
    setPHYCFGR(val);
  }
  else if (mode == POWER_DOWN)
  {
    bitWrite(val, 3, 0);
    bitWrite(val, 4, 1);
    bitWrite(val, 5, 1);
    setPHYCFGR(val);
  }
  else if (mode == ALL_AUTONEG)
  {
    bitWrite(val, 3, 1);
    bitWrite(val, 4, 1);
    bitWrite(val, 5, 1);
    setPHYCFGR(val);
  }

  bitWrite(val, 7, 0);
  setPHYCFGR(val);
  bitWrite(val, 7, 1);
  setPHYCFGR(val);
}

////////////////////////////////////////

const char* W5100Class::linkReport()
{
  if (altChip == w5100s)
  {
    if (bitRead(readPSTATUS_W5100S(), 0) == 1)
      return "LINK";
    else
      return "NO LINK";
  }
  else if (chip == w5500)
  {
    if (bitRead(readPHYCFGR_W5500(), 0) == 1)
      return "LINK";
    else
      return "NO LINK";
  }

#if USING_W6100
  else if (chip == w6100)
  {
    if (bitRead(readPHYCFGR_W6100(), 0) == 1)
      return "LINK";
    else
      return "NO LINK";
  }

#endif

  return "NOT SUPPORTED";
}

////////////////////////////////////////

const char* W5100Class::speedReport()
{
  if (altChip == w5100s)
  {
    if (bitRead(readPSTATUS_W5100S(), 0) == 1)
    {
      if (bitRead(readPSTATUS_W5100S(), 1) == 1)
        return "10 MB";
      else
        return "100 MB";
    }

    return "NO LINK";
  }
  else if (chip == w5500)
  {
    if (bitRead(readPHYCFGR_W5500(), 0) == 1)
    {
      if (bitRead(readPHYCFGR_W5500(), 1) == 1)
        return "100 MB";
      else
        return "10 MB";
    }

    return "NO LINK";
  }

#if USING_W6100
	// Check https://docs.wiznet.io/img/products/w6100/w6100_ds_v105e.pdf, page 37
	// Inversed from W5x00
  else if (chip == w6100)
  {
    if (bitRead(readPHYCFGR_W6100(), 0) == 1)
    {
      if (bitRead(readPHYCFGR_W6100(), 1) == 0)
        return "100 MB";
      else
        return "10 MB";
    }

    return "NO LINK";
  }

#endif

  return "NOT SUPPORTED";
}

////////////////////////////////////////

const char* W5100Class::duplexReport()
{
  if (altChip == w5100s)
  {
    if (bitRead(readPSTATUS_W5100S(), 0) == 1)
    {
      if (bitRead(readPSTATUS_W5100S(), 2) == 1)
        return "HALF DUPLEX";
      else
        return "FULL DUPLEX";
    }

    return "NO LINK";
  }
  else if (chip == w5500)
  {
    if (bitRead(readPHYCFGR_W5500(), 0) == 1)
    {
      if (bitRead(readPHYCFGR_W5500(), 2) == 1)
        return "FULL DUPLEX";

      if (bitRead(getPHYCFGR(), 2) == 0)
        return "HALF DUPLEX";
    }

    return "NO LINK";
  }

#if USING_W6100
	// Check https://docs.wiznet.io/img/products/w6100/w6100_ds_v105e.pdf, page 37
	// Inversed from W5x00
  else if (chip == w6100)
  {
    if (bitRead(readPHYCFGR_W6100(), 0) == 1)
    {
      if (bitRead(readPHYCFGR_W6100(), 2) == 0)
        return "FULL DUPLEX";

      if (bitRead(getPHYCFGR(), 2) == 1)
        return "HALF DUPLEX";
    }

    return "NO LINK";
  }

#endif

  return "NOT SUPPORTED";
}

////////////////////////////////////////

#endif    // W5100_IMPL_H_
