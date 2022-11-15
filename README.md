## Ethernet_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/Ethernet_Generic.svg?)](https://www.ardu-badge.com/Ethernet_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Ethernet_Generic.svg)](http://github.com/khoih-prog/Ethernet_Generic/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>
<a href="https://profile-counter.glitch.me/khoih-prog/count.svg" title="Total khoih-prog Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog/count.svg" style="height: 30px;width: 200px;"></a>
<a href="https://profile-counter.glitch.me/khoih-prog-Ethernet_Generic/count.svg" title="Ethernet_Generic Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog-Ethernet_Generic/count.svg" style="height: 30px;width: 200px;"></a>

---
---

## Table of Contents

* [Important Note from v2.5.2](#Important-Note-from-v252)
* [Why do we need this Ethernet_Generic library](#why-do-we-need-this-Ethernet_Generic-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
* [Changelog](changelog.md) 
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
  * [12. For Seeeduino RP2040 boards](#12-For-Seeeduino-RP2040-boards)
  * [13. For Seeeduino nRF52840 boards](#13-For-Seeeduino-nRF52840-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. How to use EthernetLarge feature](#2-How-to-use-EthernetLarge-feature)
  * [3. How to select another CS/SS pin to use](#3-how-to-select-another-csss-pin-to-use)
  * [4. How to use W5x00 with ESP8266](#4-how-to-use-w5x00-with-esp8266)
* [Ethernet_Generic Library API](#Ethernet_Generic-Library-API) 
* [Configuration Notes](#configuration-notes)
  * [1. How to select which SPI to use](#1-How-to-select-which-SPI-to-use)
  	* [1.1. For boards other than STM32](#11-For-boards-other-than-STM32)
    * [1.2. For STM32 boards](#12-For-STM32-boards)
  * [2. How to use EthernetLarge feature](#2-How-to-use-EthernetLarge-feature)
  * [3. How to select another CS/SS pin to use](#3-How-to-select-another-CSSS-pin-to-use)
  * [4. How to use W5x00 with ESP8266](#4-How-to-use-W5x00-with-ESP8266)
  * [5. Important Note for AVRDx using Arduino IDE](#5-Important-Note-for-AVRDx-using-Arduino-IDE) **New**
* [Examples](#examples)
  * [ 1. multiFileProject](examples/multiFileProject)
  * [ 2. TelnetClient](examples/TelnetClient)
  * [ 3. UdpNTPClient](examples/UdpNTPClient)
  * [ 4. UdpSendReceive](examples/UdpSendReceive)
  * [ 5. WebClient](examples/WebClient)
  * [ 6. WebClient_ESP](examples/WebClient_ESP)
  * [ 7. WebClient_ESP_SPI2](examples/WebClient_ESP_SPI2)
  * [ 8. WebClientRepeating](examples/WebClientRepeating)
  * [ 9. WebClientRepeating_ESP](examples/WebClientRepeating_ESP)
  * [10. WebClientRepeating_ESP_SPI2](examples/WebClientRepeating_ESP_SPI2)
  * [11. WebServer](examples/WebServer)
  * [12. WebClientRepeating_RP2040_SPI1](examples/WebClientRepeating_RP2040_SPI1) **New**
  * [13. SetDHCPHostName](examples/SetDHCPHostName) **New**
  * [14. EthernetWebServer_BigData](examples/EthernetWebServer_BigData) **New**
* [Example WebClientRepeating](#example-WebClientRepeating)
  * [1. File WebClientRepeating.ino](#1-file-WebClientRepeatingino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. WebClientRepeating_ESP on ESP32_DEV](#1-WebClientRepeating_ESP-on-ESP32_DEV)
  * [ 2. WebClientRepeating_ESP_SPI2 on ESP32_DEV](#2-WebClientRepeating_ESP_SPI2-on-ESP32_DEV)
  * [ 3. WebClientRepeating on AVR Mega](#3-WebClientRepeating-on-AVR-Mega)
  * [ 4. WebClientRepeating on NRF52840_FEATHER](#4-WebClientRepeating-on-NRF52840_FEATHER)
  * [ 5. WebClientRepeating on SAM DUE](#5-WebClientRepeating-on-SAM-DUE)
  * [ 6. WebClientRepeating on SAMD](#6-WebClientRepeating-on-SAMD)
  * [ 7. WebClientRepeating on NUCLEO_F767ZI](#7-WebClientRepeating-on-NUCLEO_F767ZI)
  * [ 8. UdpNTPClient on AVR Mega](#8-UdpNTPClient-on-AVR-Mega)
  * [ 9. WebClient on MBED RASPBERRY_PI_PICO with Large Buffer](#9-WebClient-on-MBED-RASPBERRY_PI_PICO-with-Large-Buffer)
  * [10. WebClient on RASPBERRY_PI_PICO with Large Buffer](#10-WebClient-on-RASPBERRY_PI_PICO-with-Large-Buffer)
  * [11. WebClientRepeating_RP2040_SPI1 on RASPBERRY_PI_PICO with Large Buffer](#11-WebClientRepeating_RP2040_SPI1-on-RASPBERRY_PI_PICO-with-Large-Buffer)
  * [12. WebClient on MBED RASPBERRY_PI_PICO with W5100S using Ethernet_Generic Library with Large Buffer](#12-WebClient-on-MBED-RASPBERRY_PI_PICO-with-W5100S-using-Ethernet_Generic-Library-with-Large-Buffer)
  * [13. WebClientRepeating on NUCLEO_L552ZE_Q with W5x00 using Ethernet_Generic Library with Large Buffer](#13-WebClientRepeating-on-NUCLEO_L552ZE_Q-with-W5x00-using-Ethernet_Generic-Library-with-Large-Buffer)
  * [14. WebClientRepeating on NUCLEO_F767ZI with W5x00 using Ethernet_Generic Library with Large Buffer](#14-WebClientRepeating-on-NUCLEO_F767ZI-with-W5x00-using-Ethernet_Generic-Library-with-Large-Buffer)
  * [15. WebClientRepeating_RP2040_SPI1 on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library with Large Buffer](#15-WebClientRepeating_RP2040_SPI1-on-MBED-RASPBERRY_PI_PICO-with-W5x00-using-Ethernet_Generic-Library-with-Large-Buffer)
  * [16. SetDHCPHostName on WIZNET_5100S_EVB_PICO with W5x00 using Ethernet_Generic Library with Large Buffer](#16-SetDHCPHostName-on-WIZNET_5100S_EVB_PICO-with-W5x00-using-Ethernet_Generic-Library-with-Large-Buffer)
  * [17. WebClientRepeating on WIZNET_5500_EVB_PICO with W5x00 using Ethernet_Generic Library with Large Buffer](#17-WebClientRepeating-on-WIZNET_5500_EVB_PICO-with-W5x00-using-Ethernet_Generic-Library-with-Large-Buffer)
  * [18. WebClientRepeating on SAMD_FEATHER_M0_EXPRESS with W5x00 using Ethernet_Generic Library with Large Buffer](#18-WebClientRepeating-on-SAMD_FEATHER_M0_EXPRESS-with-W5x00-using-Ethernet_Generic-Library-with-Large-Buffer)
  * [19. UdpNTPClient on SAMD_ZERO with W5x00 using Ethernet_Generic Library with Large Buffer](#19-UdpNTPClient-on-SAMD_ZERO-with-W5x00-using-Ethernet_Generic-Library-with-Large-Buffer)
  * [20. WebClientRepeating on Curiosity AVR_AVR128DA48 with W5x00 using Ethernet_Generic Library with Large Buffer](#20-WebClientRepeating-on-Curiosity-AVR_AVR128DA48-with-W5x00-using-Ethernet_Generic-Library-with-Large-Buffer)
  * [21. EthernetWebServer_BigData on NRF52840_FEATHER](#21-EthernetWebServer_BigData-on-NRF52840_FEATHER)
  * [22. EthernetWebServer_BigData on RASPBERRY_PI_PICO](#22-EthernetWebServer_BigData-on-RASPBERRY_PI_PICO)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [Copyright](#copyright)


---
---

### Important Note from v2.5.2

The new [Ethernet_Generic v2.7.1+](https://github.com/khoih-prog/Ethernet_Generic/releases/tag/v2.7.0) fixes severe limitation to permit sending much larger data than total than **2/4/8/16K** buffer of **W5x00 Ethernet**.

---

To be safe for systems using old `W5100` shields, the **examples** are using `optional` conservative values for SPI clock speed of 14MHz and `SPI_MODE0`

For `SAMD21 M0`, such as `SAMD Zero`, SPI clock speed of 8MHz and `SPI_MODE0` are used.


```cpp
// Default to use W5100. Must change to false for W5500, W5100S, for faster SPI clock
//#define USE_W5100                           true
```

To use with shields different from `W5100`, such as `W5200, W5500, W5100S`, change to 

```cpp
// Default to use W5100. Must change to false for W5500, W5100S, for faster SPI clock
#define USE_W5100                           false
```

For Arduino SAMD21 Zero, in order to print to Terminal, use `SERIAL_PORT_USBVIRTUAL` == `SerialUSB`

```cpp
// Use this for ARDUINO_SAMD_ZERO, etc. if can't print to terminal with Serial.print
#if defined(SERIAL_PORT_USBVIRTUAL)
  #define Serial          SERIAL_PORT_USBVIRTUAL
  #warning Using SAMD Zero SerialUSB
#endif
```

---

### Why do we need this [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic)

#### Features

This [**Ethernet_Generic library**](https://github.com/khoih-prog/Ethernet_Generic) is a port and modification to merge, as many as possible, the features of the following libraries
1. [**Ethernet**](https://github.com/arduino-libraries/Ethernet)
2. [**EthernetLarge**](https://github.com/OPEnSLab-OSU/EthernetLarge)
3. [**Ethernet2**](https://github.com/adafruit/Ethernet2)
4. [**Ethernet3**](https://github.com/sstaub/Ethernet3)

for **AVR, Portenta_H7, Teensy, SAM DUE, Arduino SAMD21, Adafruit SAMD21/SAMD51, Adafruit nRF52, ESP32/ESP8266, STM32, RP2040-based, etc.** boards using Ethernet W5x00 shields. 

The `h-only` library now supports `SPI1/SPI2`, most of `EthernetLarge`, `Ethernet2` and `Ethernet3` features by simply changing definitions in the sketch.

---

#### Currently supported Boards

This [**Ethernet_Generic** library](https://github.com/khoih-prog/Ethernet_Generic) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 2. **SAM DUE**
 3. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 4. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC)**
 6. **AVR Mega1280, 2560, ADK.**
 7. ESP32, using **SPI or SPI2**
 8. ESP8266
 
 9. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) with SPI, SPI1, or custom SPI. **New**
10. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico) with SPI, SPI1 or custom SPI. **New**
11. **Portenta_H7** with SPI0, SPI1 or custom SPI. **New**
 
12. **Arduino UNO WiFi Rev2, AVR_NANO_EVERY, etc.**
  
13. **STM32F/L/H/G/WB/MP1 boards (with 32+K Flash) running W5x00 shields)** with SPI, SPI2 or custom SPI. **New**

- Nucleo-144
- Nucleo-64
- Discovery
- Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
- STM32L0, STM32L1, STM32L4
- STM32G0, STM32G4
- STM32H7
- STM32WB
- STM32MP1
- LoRa boards
- 3-D printer boards
- Generic Flight Controllers
- Midatronics boards

12. **Arduino AVR_Dx boards using DxCore**

- **AVRDA-based boards (AVR128DA, AVR64DA, AVR32DA, etc.)**

<p align="center">
    <img src="https://github.com/khoih-prog/Dx_TimerInterrupt/raw/main/pics/Curiosity_AVR128DA48.png">
</p>


- **AVRDB-based boards (AVR128DB, AVR64DB, AVR32DB, etc.)**

<p align="center">
    <img src="https://github.com/khoih-prog/Dx_TimerInterrupt/raw/main/pics/Curiosity_AVR128DB48.png">
</p>


13. **Seeeduino nRF52840-based boards such as XIAO_NRF52840 and XIAO_NRF52840_SENSE**, etc. using Seeed `mbed` or `nRF52` core


#### Currently supported Ethernet shields/modules

1. W5x00 shield /module such as W5100, W5200, W5500 and W5100S
2. W5100S shield /module, such as [**WIZnet Ethernet HAT**](https://docs.wiznet.io/Product/Open-Source-Hardware/wiznet_ethernet_hat) and [**W5100S-EVB-Pico**](https://docs.wiznet.io/Product/iEthernet/W5100S/w5100s-evb-pico)


---
---


## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino AVR core 1.8.6+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 3. [`Teensy core v1.57+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 4. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 5. [`Arduino SAMD core 1.8.13+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 6. [`Adafruit SAMD core 1.7.11+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 7. [`Seeeduino SAMD core 1.8.3+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 8. [`Adafruit nRF52 v1.3.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
 9. [`ESP32 Core 2.0.5+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
10. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/). To use ESP8266 core 2.7.1+ for LittleFS.
11. [`ArduinoCore-mbed mbed_rp2040, mbed_nano, mbed_portenta core 3.4.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) **Portenta_H7, RP2040-based boards, such as Nano_RP2040_Connect, RASPBERRY_PI_PICO**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
12. [`Earle Philhower's arduino-pico core v2.6.3+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
13. [`Arduino megaAVR core 1.8.7+`](https://github.com/arduino/ArduinoCore-megaavr/releases) for Arduino megaAVR boards such as **Arduino UNO WiFi Rev2, AVR_NANO_EVERY, etc.**
14. [`Arduino Core for STM32 v2.3.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
15. [`SpenceKonde DxCore core 1.4.10+`](https://github.com/SpenceKonde/DxCore) for Arduino AVRDx boards.  [![GitHub release](https://img.shields.io/github/release/SpenceKonde/DxCore.svg)](https://github.com/SpenceKonde/DxCore/releases/latest). Follow [**DxCore Installation**](https://github.com/SpenceKonde/DxCore/blob/master/Installation.md).
16. [`Seeeduino nRF52 core 1.0.0+`](https://github.com/Seeed-Studio/Adafruit_nRF52_Arduino) for Seeed nRF52840-based boards such as **Seeed_XIAO_NRF52840 and Seeed_XIAO_NRF52840_SENSE**. [![GitHub release](https://img.shields.io/github/release/Seeed-Studio/Adafruit_nRF52_Arduino.svg)](https://github.com/Seeed-Studio/Adafruit_nRF52_Arduino/releases/latest)
17. `Seeeduino mbed core 2.7.2+` for Seeed nRF52840-based boards such as **SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE**


---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `Ethernet_Generic`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Ethernet_Generic.svg?)](https://www.ardu-badge.com/Ethernet_Generic) for more detailed instructions.

### Manual Install

1. Navigate to [Ethernet_Generic](https://github.com/khoih-prog/Ethernet_Generic) page.
2. Download the latest release `Ethernet_Generic-main.zip`.
3. Extract the zip file to `Ethernet_Generic-main` directory 
4. Copy the whole `Ethernet_Generic-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Ethernet_Generic** library](https://registry.platformio.org/libraries/khoih-prog/Ethernet_Generic) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/Ethernet_Generic/installation). Search for Ethernet_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.11) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.11). 

Supposing the Adafruit SAMD core version is 1.7.11. These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.3) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3). 

Supposing the Seeeduino SAMD core version is 1.8.3. These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.3.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.4. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/ambd/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.9.0. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`


#### 12. For Seeeduino RP2040 boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino RP2040 (XIAO RP2040, Wio RP2040 Mini) boards***, you have to copy the whole [Seeeduino RP2040 Packages_Patches](Packages_Patches/Seeeduino/hardware/rp2040/2.7.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2). 

Supposing the Seeeduino RP2040 core version is 2.7.2. These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/variants/Seeed_XIAO_RP2040/pins_arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/variants/Seeed_XIAO_RP2040/pins_arduino.h`


---

#### 13. For Seeeduino nRF52840 boards

**To be able to compile and run on Xiao nRF52840 boards**, you have to copy the whole [nRF52 1.0.0](Packages_Patches/Seeeduino/hardware/nrf52/1.0.0) directory into Seeeduino nRF52 directory (~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0). 

Supposing the Seeeduino nRF52 version is 1.0.0. These files must be copied into the directory:

- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/platform.txt`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Print.h`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Print.cpp`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/platform.txt`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**


---
---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.


#### 2. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.19/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)


#### 3. For fixing ESP8266 compile error

To fix `ESP8266 compile error` such as

```
error: 'class EthernetClass' has no member named 'init'
Ethernet.init (USE_THIS_SS_PIN);
```

just rename the following file in ./arduino-1.8.19/hardware/esp8266com/esp8266/libraries/Ethernet directory

- From `Ethernet.h` to `Ethernet_ESP8266.h`

---
---

### Ethernet_Generic Library API

Have a look at the [Ethernet_Generic library's API](docs/api.md)


---
---

### Configuration Notes

#### 1. How to select which SPI to use

#### 1.1 For boards other than STM32 

To use standard SPI (or `SPI0` for `arduino-pico` core), check if 

```cpp
#define USING_SPI2              false
```

of comment out the following line, if exists


```cpp
//#define USING_SPI2              true
```

To use custom SPI (or `SPI1` for `arduino-pico` or `Arduino_mbed` core)


```cpp
#define USING_SPI2                          true

#if defined(ARDUINO_ARCH_MBED)

  #if defined(BOARD_NAME)
    #undef BOARD_NAME
  #endif

  #if defined(ARDUINO_RASPBERRY_PI_PICO) 
    #define BOARD_NAME      "MBED RASPBERRY_PI_PICO"
  #elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
    #define BOARD_NAME      "MBED ADAFRUIT_FEATHER_RP2040"
  #elif defined(ARDUINO_GENERIC_RP2040)
    #define BOARD_NAME      "MBED GENERIC_RP2040"
  #else
    #define BOARD_NAME      "MBED Unknown RP2040"
  #endif

  // For RPI Pico using Mbed RP2040 core
  #if (USING_SPI2)
    #define USING_CUSTOM_SPI          true
    
    // SCK: GPIO14,  MOSI: GPIO15, MISO: GPIO12, SS/CS: GPIO13 for SPI1
    #define CUR_PIN_MISO              12
    #define CUR_PIN_MOSI              15
    #define CUR_PIN_SCK               14
    #define CUR_PIN_SS                13

    #define SPI_NEW_INITIALIZED       true

    // Don't create the instance with CUR_PIN_SS, or Ethernet not working
    // To change for other boards' SPI libraries
    #define SPIClass      arduino::MbedSPI

    // Be careful, Mbed SPI ctor is so weird, reversing the order => MISO, MOSI, SCK
    //arduino::MbedSPI::MbedSPI(int miso, int mosi, int sck)
    SPIClass SPI_New(CUR_PIN_MISO, CUR_PIN_MOSI, CUR_PIN_SCK);
    
    //#warning Using USE_THIS_SS_PIN = CUR_PIN_SS = 13

    #if defined(USE_THIS_SS_PIN)
      #undef USE_THIS_SS_PIN
    #endif   
    #define USE_THIS_SS_PIN       CUR_PIN_SS    //13
     
  #else
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17 for SPI0
    #define USE_THIS_SS_PIN       PIN_SPI_SS    //17
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
#warning Use RPI-Pico RP2040 architecture with custom SPI or SPI1
```

Check and compare the examples 

- [WebClient_ESP](examples/WebClient_ESP) and [WebClient_ESP_SPI2](examples/WebClient_ESP_SPI2)
- [WebClientRepeating_RP2040_SPI1](examples/WebClientRepeating_RP2040_SPI1) and [WebClientRepeating](examples/WebClientRepeating)

---

#### 1.2 For STM32 boards


To use standard SPI, check if 

```cpp
#define USING_CUSTOM_SPI        false
#define USING_SPI2              false
```


To use SPI2 or any custom SPI


```cpp
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
```

---

#### 2. How to use EthernetLarge feature

To use `ETHERNET_LARGE_BUFFERS` feature, similar to the one provided by EthernetLarge library, just add to your sketch


```cpp
// W5100 chips can have up to 4 sockets.  W5200 & W5500 can have up to 8 sockets.
// Use EthernetLarge feature, Larger buffers, but reduced number of simultaneous connections/sockets (MAX_SOCK_NUM == 2)
#define ETHERNET_LARGE_BUFFERS
```


---

#### 3. How to select another CS/SS pin to use

The default CS/SS pin is GPIO4(D2) for ESP8266, GPIO22 for ESP32, pin 10 for all other boards.

If the default pin is not corect, the easiest way is to change is to select the CS/SS pin (e.g. 22) to use as follows:

```cpp
// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
#define USE_THIS_SS_PIN   22

...

Ethernet.init (USE_THIS_SS_PIN);
```

#### 4. How to use W5x00 with ESP8266

To avoid using the default but not-working Ethernet library of ESP8266, rename the Ethernet.h/cpp to Ethernet_ESP8266.h/cpp to avoid library conflict if you're using the Arduino Ethernet library. The Ethernet2, Ethernet3, EthernetLarge library can be used without conflict.

These pins are tested OK with ESP8266 and W5x00

```cpp
  // For ESP8266
  // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
  // Ethernet_Generic   X                 X            X            X            X        0
  // D2 is safe to used for Ethernet_Generic libs
  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);
```

#### 5. Important Note for AVRDx using Arduino IDE

With some Arduino IDE versions, such as v1.8.19, upload directly via USB to some boards, such as `Curiosity_AVR128DA48` or `Curiosity_AVR128DB48` can't be done without unknown-to-me fix. We'll get the following error when uploading

```
avrdude: Version 6.3-20201216
     Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
     Copyright (c) 2007-2014 Joerg Wunsch

     System wide configuration file is "/home/kh/.arduino15/packages/DxCore/hardware/megaavr/1.4.10/avrdude.conf"
     User configuration file is "/home/kh/.avrduderc"
     User configuration file does not exist or is not a regular file, skipping

     Using Port                    : usb
     Using Programmer              : curiosity_updi
avrdude: usbdev_open(): Found nEDBG CMSIS-DAP, serno: MCHP3280041800002682
avrdude: usbdev_open(): WARNING: failed to set configuration 1: Device or resource busy
avrdude: Found CMSIS-DAP compliant device, using EDBG protocol
avrdude: usbdev_send(): wrote -5 out of 912 bytes, err = Input/output error
avrdude: jtag3_edbg_prepare(): failed to send command to serial port

avrdude done.  Thank you.

the selected serial port 
 does not exist or your board is not connected
```

We can use drag-and-drop method to `drag-and-drop` the compiled **hex** file to `CURIOSITY` virtual drive. 

If `success`, The LED blinks **slowly** for 2 sec. The LED will blinks **rapidly** for 2 sec if `failure`


For example, to run [Change_Interval example](https://github.com/khoih-prog/Ethernet_Generic/tree/main/examples/Change_Interval), use Arduino IDE to compile, and get the `Change_Interval.ino.hex` file. For Ubuntu Linux, the file is stored in directory `/tmp/arduino_build_xxxxxx`


<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Generic/raw/main/pics/Change_Interval.png">
</p>


After drag-and-drop the `Change_Interval.ino.hex` into `CURIOSITY` virtual drive, the code will run immidiately if successfully loaded (LED blinks **slowly**)


<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Generic/raw/main/pics/CURIOSITY_drive.png">
</p>

##### How to connect W5x00 to AVDDx

This is example to demo how to connect W5x00 to Curiosity `AVR128DA48` or `AVR128DB48`

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Generic/raw/main/pics/Curiosity_Dx48_pinout.png">
</p>

|W5x00|<--->|AVRDx|
|:-:|:-:|:-:|
|MOSI|<--->|PA_4 = 4|
|MISO|<--->|PA_5 = 5|
|SCK|<--->|PA_6 = 6|
|SS|<--->|PA_7 = 7|
|GND|<--->|GND = 52|
|3.3V|<--->|VCC = 51|

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Generic/raw/main/pics/Curiosity_Dx48_wiring.png">
</p>


---
---

### Examples:

 1. [multiFileProject](examples/multiFileProject)
 2. [TelnetClient](examples/TelnetClient)
 3. [UdpNTPClient](examples/UdpNTPClient)
 4. [UdpSendReceive](examples/UdpSendReceive)
 5. [WebClient](examples/WebClient)
 6. [WebClient_ESP](examples/WebClient_ESP)
 7. [WebClient_ESP_SPI2](examples/WebClient_ESP_SPI2)
 8. [WebClientRepeating](examples/WebClientRepeating)
 9. [WebClientRepeating_ESP](examples/WebClientRepeating_ESP)
10. [WebClientRepeating_ESP_SPI2](examples/WebClientRepeating_ESP_SPI2)
11. [WebServer](examples/WebServer)
12. [WebClientRepeating_RP2040_SPI1](examples/WebClientRepeating_RP2040_SPI1) **New**
13. [SetDHCPHostName](examples/SetDHCPHostName) **New**
14. [EthernetWebServer_BigData](examples/EthernetWebServer_BigData) **New**
 
---
---

### Example [WebClientRepeating](examples/WebClientRepeating)

#### 1. File [WebClientRepeating.ino](examples/WebClientRepeating/WebClientRepeating.ino)

https://github.com/khoih-prog/Ethernet_Generic/blob/61ede0494d377d16177b119599542dfb55a35ff8/examples/WebClientRepeating/WebClientRepeating.ino#L15-L234


---

#### 2. File [defines.h](examples/WebClientRepeating/defines.h)

https://github.com/khoih-prog/Ethernet_Generic/blob/61ede0494d377d16177b119599542dfb55a35ff8/examples/WebClientRepeating/defines.h#L10-L466

---
---

### Debug Terminal Output Samples

#### 1. WebClientRepeating_ESP on ESP32_DEV

The following are debug terminal output when running example [WebClientRepeating_ESP](examples/WebClientRepeating_ESP) on ESP32_DEV with `W5500` using Ethernet_Generic Library

```
Starting WebClientRepeating_ESP on ESP32_DEV with W5x00 using Ethernet_Generic Library on SPI
Ethernet_Generic v2.7.1
=========================
Currently Used SPI pinout:
MOSI:23
MISO:19
SCK:18
SS:5
=========================
Using mac index = 19
Connected! IP address: 192.168.2.95
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Starting connection to server...

Connecting...
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;; 
```

---

#### 2. WebClientRepeating_ESP_SPI2 on ESP32_DEV

The following are debug terminal output when running example [WebClientRepeating_ESP_SPI2](examples/WebClientRepeating_ESP_SPI2) on ESP32_DEV with `W5500` using Ethernet_Generic Library

```
Starting WebClientRepeating_ESP_SPI2 on ESP32_DEV with W5x00 using Ethernet_Generic Library on SPI2
Ethernet_Generic v2.7.1
=========================
Currently Used SPI pinout:
MOSI:13
MISO:12
SCK:14
SS:5
=========================
Using mac index = 19
Connected! IP address: 192.168.2.95
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Starting connection to server...

Connecting...
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;; 
```


---

#### 3. WebClientRepeating on AVR Mega

The following are debug terminal output when running example [WebClientRepeating](examples/WebClientRepeating) on AVR Mega with `W5100` using Ethernet_Generic Library

```
Starting WebClientRepeating on AVR Mega with W5x00 using Ethernet_Generic Library
Ethernet_Generic v2.7.1
=========================
Currently Used SPI pinout:
MOSI:51
MISO:50
SCK:52
SS:53
=========================
Using mac index = 2
Connected! IP address: 192.168.2.85

Connecting...
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;; 
```

---

#### 4. WebClientRepeating on NRF52840_FEATHER

The following are debug terminal output when running example [WebClientRepeating](examples/WebClientRepeating) on NRF52840_FEATHER with `W5500` using Ethernet_Generic Library

```
Starting WebClientRepeating on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library
Ethernet_Generic v2.7.1
=========================
Currently Used SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
=========================
Using mac index = 12
Connected! IP address: 192.168.2.115
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Connecting...
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;; 
```

---

#### 5. WebClientRepeating on SAM DUE

The following are debug terminal output when running example [WebClientRepeating](examples/WebClientRepeating) on AVR Mega with `W5100` using Ethernet_Generic Library


```
Starting WebClientRepeating on SAM DUE with W5x00 using Ethernet_Generic Library
Ethernet_Generic v2.7.1
=========================
Currently Used SPI pinout:
MOSI:75
MISO:74
SCK:76
SS:10
=========================
Using mac index = 2
Connected! IP address: 192.168.2.85

Connecting...
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;; 

```

---


#### 6. WebClientRepeating on SAMD

The following are debug terminal output when running example [WebClientRepeating](examples/WebClientRepeating) on SAMD51 ITSYBITSY_M4 with `W5500` using Ethernet_Generic Library

```
Starting WebClientRepeating on ITSYBITSY_M4 with W5x00 using Ethernet_Generic Library
Ethernet_Generic v2.7.1
=========================
Currently Used SPI pinout:
MOSI:25
MISO:23
SCK:24
SS:16
=========================
Using mac index = 0
Connected! IP address: 192.168.2.102
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Connecting...
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;  
```


---

#### 7. WebClientRepeating on NUCLEO_F767ZI

The following are debug terminal output when running example [WebClientRepeating](examples/WebClientRepeating) on STM32F7 NUCLEO_F767ZI with `W5500` using Ethernet_Generic Library

```
Starting WebClientRepeating on NUCLEO_F767ZI with W5x00 using Ethernet_Generic Library
Ethernet_Generic v2.7.1
=========================
Currently Used SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
=========================
Using mac index = 5
Connected! IP address: 192.168.2.94
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Connecting...
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;; 
```

---

#### 8. UdpNTPClient on AVR Mega


The following are debug terminal output when running example [UdpNTPClient](examples/UdpNTPClient) on AVR Mega with `W5100` using Ethernet_Generic Library


```
Start UdpNTPClient on AVR Mega with W5x00 using Ethernet_Generic Library
Ethernet_Generic v2.7.1
=========================
Currently Used SPI pinout:
MOSI:51
MISO:50
SCK:52
SS:53
=========================
Using mac index = 2
Connected! IP address: 192.168.2.103
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

UDP Packet received, size 48
From 132.163.97.3, port 123
Seconds since Jan 1 1900 = 3872943720
Unix time = 1663954920
The UTC time is 17:42:00
UDP Packet received, size 48
From 132.163.97.3, port 123
Seconds since Jan 1 1900 = 3872943732
Unix time = 1663954932
The UTC time is 17:42:12
```

---

#### 9. WebClient on MBED RASPBERRY_PI_PICO with Large Buffer

The following are debug terminal output when running example [WebClient](examples/WebClient) on MBED RASPBERRY_PI_PICO with `W5500` using Ethernet_Generic Library and [`ArduinoCore-mbed mbed_rp2040 core`](https://github.com/arduino/ArduinoCore-mbed)

```
Starting WebClient on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
Using mac index = 16
Connected! IP address: 192.168.2.80
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Starting connection to server...
Connected to server
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;; 

Disconnecting from server...
```

---


#### 10. WebClient on RASPBERRY_PI_PICO with Large Buffer

The following are debug terminal output when running example [WebClient](examples/WebClient) on RASPBERRY_PI_PICO with `W5500` using Ethernet_Generic Library and [`Earle Philhower's arduino-pico core`](https://github.com/earlephilhower/arduino-pico)


```
Starting WebClient on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
Using mac index = 3
Connected! IP address: 192.168.2.79
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Starting connection to server...
Connected to server
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;; 

Disconnecting from server...
```

---


#### 11. WebClientRepeating_RP2040_SPI1 on RASPBERRY_PI_PICO with Large Buffer

The following are debug terminal output when running example [WebClientRepeating_RP2040_SPI1](examples/WebClientRepeating_RP2040_SPI1) on RASPBERRY_PI_PICO with `W5500` using Ethernet_Generic Library and [`Earle Philhower's arduino-pico core`](https://github.com/earlephilhower/arduino-pico) on SPI1


```
Starting WebClientRepeating_RP2040_SPI1 on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
[ETG] Default SPI pinout:
[ETG] MOSI: 15
[ETG] MISO: 12
[ETG] SCK: 14
[ETG] SS: 13
[ETG] =========================
[ETG] RPIPICO setCsPin: 13
[ETG] W5100 init, using W5100Class::ss_pin =  13 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 13
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
[ETG] Currently Used SPI pinout:
[ETG] MOSI: 15
[ETG] MISO: 12
[ETG] SCK: 14
[ETG] SS: 13
[ETG] =========================
Using mac index = 3
Connected! IP address: 192.168.2.131
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Connecting...
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;; 
```

---

#### 12. WebClient on MBED RASPBERRY_PI_PICO with W5100S using Ethernet_Generic Library with Large Buffer

The following are debug terminal output when running example [WebClient](examples/WebClient) on MBED RASPBERRY_PI_PICO with `W5100S` using Ethernet_Generic Library and [`ArduinoCore-mbed mbed_rp2040` core](https://github.com/arduino/ArduinoCore-mbed)


```
Starting WebClient on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
[ETG] Default SPI pinout:
[ETG] MOSI: 19
[ETG] MISO: 16
[ETG] SCK: 18
[ETG] SS: 17
[ETG] =========================
[ETG] RPIPICO setCsPin: 17
[ETG] W5100 init, using W5100Class::ss_pin =  17 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 17
[ETG] Chip is W5100S
[ETG] W5100::init: W5100S, SSIZE = 4096
[ETG] Currently Used SPI pinout:
[ETG] MOSI: 19
[ETG] MISO: 16
[ETG] SCK: 18
[ETG] SS: 17
[ETG] =========================
Using mac index = 17
Connected! IP address: 192.168.2.88
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Starting connection to server...
Connected to server
HTTP/1.1 200 OK
Date: Fri, 22 Apr 2022 04:37:41 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: eyzCHdMGO11oeA4A8jYZfiE5/zVEIlz5SuzB0BSTmsUOjQOUFLa6lLPADcCDm2MWQ7BbsMLKea8=
x-amz-request-id: 15FHQXHJTE3MEDVP
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=lhmJUs%2BVz3Zq1TMuCZTZkuD3wJ1dmhMj6tmnJ95tFD0uo987KgvfB2FPAPnGfxkAgBhaTiof5icCjHVgfrTyqjU%2B5ItAVB5DOsFwKC5e9e9napQPbZ1hEZ4pMgfVNSs%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 6ffbaa64387ba235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

Disconnecting from server...

```

---

#### 13. WebClientRepeating on NUCLEO_L552ZE_Q with W5x00 using Ethernet_Generic Library with Large Buffer

The following are debug terminal output when running example [WebClientRepeating](examples/WebClientRepeating) on STM32L7 NUCLEO_L552ZE_Q with `W5500` using Ethernet_Generic Library and SPI2

```
Starting WebClientRepeating on NUCLEO_L552ZE_Q with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
[ETG] Default SPI pinout:
[ETG] MOSI: 22
[ETG] MISO: 25
[ETG] SCK: 23
[ETG] SS: 24
[ETG] =========================
[ETG] Board : NUCLEO_L552ZE_Q , setCsPin: 24
[ETG] W5100 init, using W5100Class::ss_pin =  24 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 10
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
[ETG] Currently Used SPI pinout:
[ETG] MOSI: 22
[ETG] MISO: 25
[ETG] SCK: 23
[ETG] SS: 24
[ETG] =========================
Using mac index = 2
Connected! IP address: 192.168.2.87
Connecting...
HTTP/1.1 200 OK
Date: Tue, 03 May 2022 03:29:23 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: hTDsnSDzBDuANGakAC6oWpB9/CLTHr2x+mYr7lUEkbepdyX1tr5mmHVc2xf6kGIvPzIHqflvQ9U=
x-amz-request-id: 4KV3147AHPAJPRT1
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=KNDyM3NWal0%2FUwycKJT6Be7UpuQlz3ErhhxwurP0LXda2puk5nEzHpOP%2Budp4MtSJAfA%2FPVM8Uc2IUFDQPnemvpzPo7ocsFH22%2Fw3GQfQ4AjOuJpMhO4TddqfQl1qT4%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 7055e97729bba228-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   
```

---

#### 14. WebClientRepeating on NUCLEO_F767ZI with W5x00 using Ethernet_Generic Library with Large Buffer

The following are debug terminal output when running example [WebClientRepeating](examples/WebClientRepeating) on NUCLEO_F767ZI with `W5500` using Ethernet_Generic Library and SPI2


```
Start WebClientRepeating on NUCLEO_F767ZI with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
[ETG] Default SPI pinout:
[ETG] MOSI: 22
[ETG] MISO: 25
[ETG] SCK: 23
[ETG] SS: 24
[ETG] =========================
[ETG] Board : NUCLEO_F767ZI , setCsPin: 24
[ETG] W5100 init, using W5100Class::ss_pin =  24 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 10
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
[ETG] Currently Used SPI pinout:
[ETG] MOSI: 22
[ETG] MISO: 25
[ETG] SCK: 23
[ETG] SS: 24
[ETG] =========================
Connected! IP address: 192.168.2.123
Connecting...
HTTP/1.1 200 OK
Date: Tue, 03 May 2022 02:21:30 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: 3UTJOk8AtRD5jCq+6bBOdAUucpho+KMM4ra+5/evX48oAT9NyZiaJbPNw5DOAr+amoxXbxbowX0=
x-amz-request-id: RB5W2BTZZ19E49PA
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=GhwgztuLVJJhJBZt6cqr%2BYWDLWUzEcRPjVVpSU3Sz9KSRzj4q4DK9bvi1B2BSl7uxytKSSxOFBnKeekqPJw9LvpyYpYvHuOVcxatw924HWhtyK1OCApzLxZRLmobotQ%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 705586061d4354d9-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

```

---

#### 15. WebClientRepeating_RP2040_SPI1 on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library with Large Buffer

The following are debug terminal output when running example [WebClientRepeating_RP2040_SPI1](examples/WebClientRepeating_RP2040_SPI1) on MBED RASPBERRY_PI_PICO with `W5500` using Ethernet_Generic Library and SPI2

```
Starting WebClientRepeating_RP2040_SPI1 on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
[ETG] Default SPI pinout:
[ETG] MOSI: 15
[ETG] MISO: 12
[ETG] SCK: 14
[ETG] SS: 13
[ETG] =========================
[ETG] RPIPICO setCsPin: 13
[ETG] W5100 init, using W5100Class::ss_pin =  13 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 13
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
[ETG] Currently Used SPI pinout:
[ETG] MOSI: 15
[ETG] MISO: 12
[ETG] SCK: 14
[ETG] SS: 13
[ETG] =========================
Using mac index = 18
Connected! IP address: 192.168.2.85
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Connecting...
HTTP/1.1 200 OK
Date: Wed, 04 May 2022 02:52:56 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: 8vpqIozCfHQtWmljz3zKcVb5oa2m61jwYMh4PaSUwllVqFPdlotFeMd8kbtXto0B1tOusMAUwRI=
x-amz-request-id: 625R5E0MEMACW8E3
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=PtWJxKSeTy2pn3lC8%2FpwyFTn96Mj1T%2B%2FKoMsFHN4IUM4loCow6T01wiMe%2BJzJMIHZS2np%2F8CCNhjwRu%2FwSpDwtwl%2FoD7YPSnSCxjiAChJ7n%2FZq2yn1s5yBTBQf6op8M%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 705df1758fde3fde-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   
```

---

#### 16. SetDHCPHostName on WIZNET_5100S_EVB_PICO with W5x00 using Ethernet_Generic Library with Large Buffer

The following are debug terminal output when running example [SetDHCPHostName](examples/SetDHCPHostName) on `WIZNET_5100S_EVB_PICO` using Ethernet_Generic Library

```
Starting SetDHCPHostName on WIZNET_5100S_EVB_PICO with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
[ETG] Default SPI pinout:
[ETG] MOSI: 19
[ETG] MISO: 16
[ETG] SCK: 18
[ETG] SS: 17
[ETG] =========================
[ETG] RPIPICO setCsPin: 17
[ETG] W5100 init, using W5100Class::ss_pin =  17 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 17
[ETG] Chip is W5100S
[ETG] W5100::init: W5100S, SSIZE = 4096
[ETG] Currently Used SPI pinout:
[ETG] MOSI: 19
[ETG] MISO: 16
[ETG] SCK: 18
[ETG] SS: 17
[ETG] =========================
Using mac index = 17
Connected! IP address: 192.168.2.98
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK
DHCP Hostname is My_DHCP_Hostname
Starting connection to server...
Connected to server
HTTP/1.1 200 OK
Date: Sun, 22 May 2022 01:56:04 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: PzD3TI9iv90Zgv2w4dkO6t3B3xqYTuzuQ7S4x0ntfh/kwAnfQB91Oy5vdDVGVDmgT/Fp4OINTek=
x-amz-request-id: 6X1JX84H404JB3W1
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=btLLf3QoHqeorybriPRvjpJ4AyTDTrpLXlUxd45QgIcQ8TzbUOn8KjWbdQFI5GoP93Gl%2FeBHdiN2x8%2F1oyr%2F0xmd0%2BlnSku6%2FpLKd7kImCAuP82E5T1gsvST5%2F4uGdI%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 70f1eee839ceb683-YWG
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

Disconnecting from server...
DHCP Hostname is My_DHCP_Hostname
DHCP Hostname is My_DHCP_Hostname
DHCP Hostname is My_DHCP_Hostname
DHCP Hostname is My_DHCP_Hostname
DHCP Hostname is My_DHCP_Hostname
```


---

#### 17. WebClientRepeating on WIZNET_5500_EVB_PICO with W5x00 using Ethernet_Generic Library with Large Buffer

The following are debug terminal output when running example [WebClientRepeating](examples/WebClientRepeating) on WIZNET_5500_EVB_PICO with `W5500` using Ethernet_Generic Library


```
Starting WebClientRepeating on WIZNET_5500_EVB_PICO with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
[ETG] Default SPI pinout:
[ETG] MOSI: 19
[ETG] MISO: 16
[ETG] SCK: 18
[ETG] SS: 17
[ETG] =========================
[ETG] RPIPICO setCsPin: 17
[ETG] W5100 init, using W5100Class::ss_pin =  17 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 17
[ETG] Chip is W5100S
[ETG] W5100::init: W5100S, SSIZE = 4096
[ETG] Currently Used SPI pinout:
[ETG] MOSI: 19
[ETG] MISO: 16
[ETG] SCK: 18
[ETG] SS: 17
[ETG] =========================
Using mac index = 9
Connected! IP address: 192.168.2.108
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Connecting...
HTTP/1.1 200 OK
Date: Fri, 26 Aug 2022 04:28:38 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: nHvgtCAdSM584rGWmHFDvNKKqCalbGNqpK7Az8aWyn0tGDntsYlgfz23E/yLIjPgo6extUNtVMQ=
x-amz-request-id: EMY2W56TAXGE51AK
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=3IGQ77WJ7HsiGxMhF8hE%2FJmzexw7%2F%2BDt0pa0BJdjpeNx6zkNWGYgf6z3Gb3Y3nz5XAj%2BI%2B63SFBy7vHVqZiJqC8mgdLHb86wBjJR1R1UR86av2w2dIxuwYWE93dU3Mw%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 7409d2643971b653-YWG
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   
```


---

#### 18. WebClientRepeating on SAMD_FEATHER_M0_EXPRESS with W5x00 using Ethernet_Generic Library with Large Buffer

The following are debug terminal output when running example [WebClientRepeating](examples/WebClientRepeating) on SAMD_FEATHER_M0_EXPRESS with `W5100` using Ethernet_Generic Library

```
Starting WebClientRepeating on SAMD_FEATHER_M0_EXPRESS with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
[ETG] Default SPI pinout:
[ETG] MOSI: 29
[ETG] MISO: 28
[ETG] SCK: 30
[ETG] SS: 16
[ETG] =========================
[ETG] Board : SAMD_FEATHER_M0_EXPRESS , setCsPin: 10
[ETG] W5100 init, using W5100Class::ss_pin =  10 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 10
[ETG] Chip is W5100
[ETG] W5100::init: W5100, SSIZE = 4096
[ETG] Currently Used SPI pinout:
[ETG] MOSI: 29
[ETG] MISO: 28
[ETG] SCK: 30
[ETG] SS: 16
[ETG] =========================
Using mac index = 2
Connected! IP address: 192.168.2.92

Connecting...
HTTP/1.1 200 OK
Date: Wed, 07 Sep 2022 01:46:11 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: BTad8l9echSPfK+UZ89JLi7k90PfLbPiqR5AXKRwoTPOYs7iAGyDNDmHDaTaJ5XLng1AvnksT70=
x-amz-request-id: YZDVW5Y862935MHG
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=%2FkVVD%2BXT6K%2FwNfo3r9X7bkZegwlGYeVugF%2F%2B%2FFkhwRYpx145mMEIvXcTm8DivuAGhd%2Bn3GsUVg7HRHNhLtuboYgTI6vT4Yyjjz1gLbR9tHux8rJVconVHxQPWQ14CwA%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 746bc4ec6b04b665-YWG
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

```

---


#### 19. UdpNTPClient on SAMD_ZERO with W5x00 using Ethernet_Generic Library with Large Buffer

The following are debug terminal output when running example [UdpNTPClient](examples/UdpNTPClient) on SAMD_ZERO with `W5100` using Ethernet_Generic Library

```
Start UdpNTPClient on SAMD_ZERO with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
[ETG] Default SPI pinout:
[ETG] MOSI: 23
[ETG] MISO: 22
[ETG] SCK: 24
[ETG] SS: 16
[ETG] =========================
[ETG] Board : SAMD_ZERO , setCsPin: 10
[ETG] W5100 init, using W5100Class::ss_pin =  10 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 10
[ETG] Chip is W5100
[ETG] W5100::init: W5100, SSIZE = 4096
[ETG] Currently Used SPI pinout:
[ETG] MOSI: 23
[ETG] MISO: 22
[ETG] SCK: 24
[ETG] SS: 16
[ETG] =========================
Using mac index = 2
Connected! IP address: 192.168.2.92
UDP Packet received, size 48
From 132.163.97.3, port 123
Seconds since Jan 1 1900 = 3872943852
Unix time = 1663955052
The UTC time is 17:44:12
UDP Packet received, size 48
From 132.163.97.3, port 123
Seconds since Jan 1 1900 = 3872943864
Unix time = 1663955064
The UTC time is 17:44:24
UDP Packet received, size 48
From 132.163.97.3, port 123
Seconds since Jan 1 1900 = 3872943876
Unix time = 1663955076
The UTC time is 17:44:36
```

---

#### 20. WebClientRepeating on Curiosity AVR_AVR128DA48 with W5x00 using Ethernet_Generic Library with Large Buffer

The following are debug terminal output when running example [UdpNTPClient](examples/UdpNTPClient) on Curiosity `AVR_AVR128DA48` with `W5100` using Ethernet_Generic Library

```
Starting WebClientRepeating on Curiosity AVR_AVR128DA48 with W5x00 using Ethernet_Generic Library with Large Buffer
Ethernet_Generic v2.7.1
[ETG] Default SPI pinout:
[ETG] MOSI: 4
[ETG] MISO: 5
[ETG] SCK: 6
[ETG] SS: 7
[ETG] =========================
[ETG] Board : Curiosity AVR_AVR128DA48 , setCsPin: 7
[ETG] W5100 init, using W5100Class::ss_pin =  7 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 10
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
[ETG] Currently Used SPI pinout:
[ETG] MOSI: 4
[ETG] MISO: 5
[ETG] SCK: 6
[ETG] SS: 7
[ETG] =========================
Using mac index = 2
Connected! IP address: 192.168.2.92
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK

Connecting...
HTTP/1.1 200 OK
Date: Sun, 11 Sep 2022 19:24:38 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: wjRb+0d4738DLS5A3ojIx4s82EcxuOx52R9dmxO3jEzd7LY+M99iWiFTqlgqyMLa5GhpTMLlXFw=
x-amz-request-id: X91JFDNN58RRSXMC
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=Oun0NIXChiT17Q1H0zK4VhpgjNjiyc%2F14Eye9RgmXLVOSKMIJ0rT3kKjQUKNukau6UFCcTHHnMRwU%2FZo74yXc09Kc4GI8rn%2BCKYz6O7e%2Bp03Jm3u%2FtO4Nqskkgc5EP4%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 7492c8e3fd18a235-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;
```


---

#### 21. [EthernetWebServer_BigData](examples/EthernetWebServer_BigData) on NRF52840_FEATHER

The following is debug terminal output when running example [EthernetWebServer_BigData](examples/EthernetWebServer_BigData) on `NRF52840_FEATHER` board, using W5500 Ethernet with this [Ethernet_Generic Library](https://github.com/khoih-prog/Ethernet_Generic), to demo how to send much larger data than total 8K

##### MULTIPLY_FACTOR = 3.0f

```
Start EthernetWebServer_BigData on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library on SPI0/SPI
EthernetWebServer v2.3.0
[ETG] W5100 init, using W5100Class::ss_pin =  5 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 10
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
Using mac index = 14
Connected! IP address: 192.168.2.135
String Len = 23712
[ETG] EthernetClient::write: chip =  55
[ETG] EthernetClient::write: size =  86 , MAX_SIZE = 8192
[ETG] EthernetClient::write: written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: Done, written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: chip =  55
[ETG] EthernetClient::write: size =  23712 , MAX_SIZE = 8192
[ETG] EthernetClient::write: written =  8192 , totalBytesSent = 8192
[ETG] EthernetClient::write: Partially Done, written =  8192 , bytesRemaining = 15520
[ETG] EthernetClient::write: written =  8192 , totalBytesSent = 16384
[ETG] EthernetClient::write: Partially Done, written =  8192 , bytesRemaining = 7328
[ETG] EthernetClient::write: written =  7328 , totalBytesSent = 23712
[ETG] EthernetClient::write: Done, written =  7328 , totalBytesSent = 23712
[ETG] EthernetClient::write: chip =  55
[ETG] EthernetClient::write: size =  91 , MAX_SIZE = 8192
[ETG] EthernetClient::write: written =  91 , totalBytesSent = 91
[ETG] EthernetClient::write: Done, written =  91 , totalBytesSent = 91
[ETG] EthernetClient::write: To write, size =  59
[ETG] EthernetClient::write: written =  59 , totalBytesSent = 59
[ETG] EthernetClient::write: Done, written =  59 , totalBytesSent = 59
String Len = 23712
[ETG] EthernetClient::write: chip =  55
[ETG] EthernetClient::write: size =  86 , MAX_SIZE = 8192
[ETG] EthernetClient::write: written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: Done, written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: chip =  55
[ETG] EthernetClient::write: size =  23712 , MAX_SIZE = 8192
[ETG] EthernetClient::write: written =  8192 , totalBytesSent = 8192
[ETG] EthernetClient::write: Partially Done, written =  8192 , bytesRemaining = 15520
[ETG] EthernetClient::write: written =  8192 , totalBytesSent = 16384
[ETG] EthernetClient::write: Partially Done, written =  8192 , bytesRemaining = 7328
[ETG] EthernetClient::write: written =  7328 , totalBytesSent = 23712
[ETG] EthernetClient::write: Done, written =  7328 , totalBytesSent = 23712
```

---

#### 22. [EthernetWebServer_BigData](examples/EthernetWebServer_BigData) on RASPBERRY_PI_PICO

The following is debug terminal output when running example [EthernetWebServer_BigData](examples/EthernetWebServer_BigData) on `WIZNET_5100S_EVB_PICO` board, using W5100S Ethernet with this [Ethernet_Generic Library](https://github.com/khoih-prog/Ethernet_Generic), to demo how to send much larger data than total 8K

##### MULTIPLY_FACTOR = 3.0f


```
Start EthernetWebServer_BigData on WIZNET_5100S_EVB_PICO with W5x00 using Ethernet_Generic Library on SPI0/SPI
EthernetWebServer v2.3.0
[ETG] W5100 init, using W5100Class::ss_pin =  17 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 17
[ETG] Chip is W5100S
[ETG] W5100::init: W5100S, SSIZE = 4096
Using mac index = 7
Connected! IP address: 192.168.2.111
String Len = 23722
[ETG] EthernetClient::write: chip =  51
[ETG] EthernetClient::write: size =  86 , MAX_SIZE = 4096
[ETG] EthernetClient::write: written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: Done, written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: chip =  51
[ETG] EthernetClient::write: size =  23722 , MAX_SIZE = 4096
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 4096
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 19626
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 8192
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 15530
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 12288
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 11434
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 16384
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 7338
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 20480
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 3242
[ETG] EthernetClient::write: written =  3242 , totalBytesSent = 23722
[ETG] EthernetClient::write: Done, written =  3242 , totalBytesSent = 23722
String Len = 23722
[ETG] EthernetClient::write: chip =  51
[ETG] EthernetClient::write: size =  86 , MAX_SIZE = 4096
[ETG] EthernetClient::write: written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: Done, written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: chip =  51
[ETG] EthernetClient::write: size =  23722 , MAX_SIZE = 4096
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 4096
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 19626
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 8192
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 15530
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 12288
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 11434
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 16384
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 7338
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 20480
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 3242
[ETG] EthernetClient::write: written =  3242 , totalBytesSent = 23722
[ETG] EthernetClient::write: Done, written =  3242 , totalBytesSent = 23722
```


---
---

### Debug

Debug is enabled by default on Serial. Debug Level from 0 to 4. To disable, change the _ETHERNET_WEBSERVER_LOGLEVEL_ to 0

```cpp
// Use this to output debug msgs to SerialDebug
#define DEBUG_ETHERNET_GENERIC_PORT         SerialDebug
// Use 0 to disable all output debug msgs
// Debug Level from 0 to 4
#define _ETG_LOGLEVEL_                      2
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, applying Libraries' Patches, Packages' Patches or this library latest version.

---
---

### Issues ###

Submit issues to: [Ethernet_Generic issues](https://github.com/khoih-prog/Ethernet_Generic/issues)

---

### TO DO

1. Bug Searching and Killing
2. Support more types of Ethernet shields.
3. New W5x00-type library based on LwIP to support Async. operations


### DONE

 1. Merge features of the following libraries
	- [Ethernet](https://github.com/arduino-libraries/Ethernet)
	- [EthernetLarge](https://github.com/OPEnSLab-OSU/EthernetLarge)
	- [Ethernet2](https://github.com/adafruit/Ethernet2)
	- [Ethernet3](https://github.com/sstaub/Ethernet3)
 2. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)**
 3. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**.
 4. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
 5. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**.
 6. Add support to SAM DUE.
 7. Add support to ESP32 and ESP8266
 8. Add support to Seeeduino SAMD21/SAMD51: LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, Wio Terminal, Grove UI Wireless
 9. Add support to RP2040-based boards such as RASPBERRY_PI_PICO, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)
10. Add support to RP2040-based boards such as RASPBERRY_PI_PICO, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico)
11. Add support to Teensy
12. Add support to **Portenta_H7 boards**
13. Add SPI2 support for ESP32
14. Optimize library code to reduce size
15. Add many more functions
16. Add support to `SPI1` for RP2040-based boards using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico)
17. Add support to WIZNet W5100S, including [**WIZnet Ethernet HAT**](https://docs.wiznet.io/Product/Open-Source-Hardware/wiznet_ethernet_hat) and [**W5100S-EVB-Pico**](https://docs.wiznet.io/Product/iEthernet/W5100S/w5100s-evb-pico)
18. Add support to STM32 boards using [Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32)
19. Add support to any board with core supporting custom hardware / software `SPI`, for example STM32.
20. Add support to custom SPI for RP2040, Nano_RP2040_Connect, Portenta_H7, etc. using [Arduino-mbed core](https://github.com/arduino/ArduinoCore-mbed)
21. Add setHostname() and related DHCP functions
22. Using `raw_address()` instead of `private IPAddress` data, as default only for [arduino-pico core](https://github.com/earlephilhower/arduino-pico) for compatibility
23. Auto-select SPI(s) `SS/CS` pins according to board package if available
24. Slow SPI clock to `8MHz` and select `SPI_MODE0` for old W5100 shield using SAMD Zero
25. Default to `W5100` to be safe. To change if using `W5200, W5500, W5100s` or testing faster SPI clock speeds
26. Slow SPI clock only when necessary (such as for W5100, SAMD21 Zero, etc.)
27. Use correct Debug Terminal `Serial` for so-called **SAMD21 Zero** boards from Arduino as well as Adafruit
28. Add support to AVR_Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using [**DxCore**](https://github.com/SpenceKonde/DxCore)
29. Add support to Seeeduino nRF52840-based boards such as **SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE**, etc. using Seeed `mbed` or `nRF52` core
30. Add astyle using `allman` style. Restyle the library
31. Update `Packages' Patches` to add Seeeduino `nRF52` core
32. Fix severe limitation to permit sending larger data than 2/4/8/16K buffer
33. Add examples [EthernetWebServer_BigData](https://github.com/khoih-prog/Ethernet_Generic/tree/main/examples/EthernetWebServer_BigData) to demo how to send larger data than 2/4/8/16K buffer
34. Auto-detect `W5x00` and settings (`ETHERNET_LARGE_BUFFERS`, `MAX_SOCK_NUM`) to set `MAX_SIZE` to send


---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Based on and modified from 
	- [Ethernet](https://github.com/arduino-libraries/Ethernet)
	- [EthernetLarge](https://github.com/OPEnSLab-OSU/EthernetLarge)
	- [Ethernet2](https://github.com/adafruit/Ethernet2)
	- [Ethernet3](https://github.com/sstaub/Ethernet3)
2. [Paul Stoffregen](https://github.com/PaulStoffregen) for [Ethernet](https://github.com/arduino-libraries/Ethernet) library
3. [OPEnSLab-OSU](https://github.com/OPEnSLab-OSU) for [EthernetLarge](hhttps://github.com/OPEnSLab-OSU/EthernetLarge) library
4. [Adafruit](https://github.com/adafruit) for [Ethernet2](https://github.com/adafruit/Ethernet2) library
5. [Stefan Staub](https://github.com/sstaub) for [Ethernet3](https://github.com/sstaub/Ethernet3) library
6. [proasnet](https://github.com/proasnet) to report issue [AdvancedWebServer example give me wrong ip HTTP EthernetWebServer is @ IP : 0.0.0.0 #62](https://github.com/khoih-prog/EthernetWebServer/issues/62) leading to version v2.5.1 to fix the issue with `SAMD Zero` and `W5100` shield
7. [victorsonntag](https://github.com/victorsonntag) to report issue [ESP32 - Wiznet W5200 problem #13](https://github.com/khoih-prog/Ethernet_Generic/discussions/13) leading to version v2.6.1 to fix the issue with `Wiznet W5200 / wiz820io` shield
8. [Andrew Young](https://github.com/vaelen) to report issue ['ETHERNET_SERVER_SEND_MAX_SIZE' was not declared in this scope #16](https://github.com/khoih-prog/Ethernet_Generic/issues/16) leading to version v2.7.1 to fix the issue when not using `ETHERNET_LARGE_BUFFERS`

Many thanks to so many authors as listed in [AUTHORS](AUTHORS)

<table>
  <tr>
    <td align="center"><a href="https://github.com/PaulStoffregen"><img src="https://github.com/PaulStoffregen.png" width="100px;" alt="PaulStoffregen"/><br /><sub><b>⭐️⭐️ Paul Stoffregen</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/OPEnSLab-OSU"><img src="https://github.com/OPEnSLab-OSU.png" width="100px;" alt="OPEnSLab-OSU"/><br /><sub><b>⭐️ OPEnSLab-OSU</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/adafruit"><img src="https://github.com/adafruit.png" width="100px;" alt="adafruit"/><br /><sub><b>⭐️ Adafruit</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/sstaub"><img src="https://github.com/sstaub.png" width="100px;" alt="sstaub"/><br /><sub><b>⭐️ Stefan Staub</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/proasnet"><img src="https://github.com/proasnet.png" width="100px;" alt="proasnet"/><br /><sub><b>proasnet</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/victorsonntag"><img src="https://github.com/victorsonntag.png" width="100px;" alt="victorsonntag"/><br /><sub><b>victorsonntag</b></sub></a><br /></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/vaelen"><img src="https://github.com/vaelen.png" width="100px;" alt="vaelen"/><br /><sub><b>Andrew Young</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

## Copyright

Copyright (c) 2009- Arduino LLC. All right reserved.

Copyright 2022- Khoi Hoang


