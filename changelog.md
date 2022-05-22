## Ethernet_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/Ethernet_Generic.svg?)](https://www.ardu-badge.com/Ethernet_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Ethernet_Generic.svg)](http://github.com/khoih-prog/Ethernet_Generic/issues)

---
---

## Table of Contents


* [Changelog](#changelog)
	* [Releases v2.3.1](#releases-v231)
	* [Releases v2.3.0](#releases-v230)
	* [Releases v2.2.0](#releases-v220)
	* [Releases v2.1.0](#releases-v210)
	* [Releases v2.0.1](#releases-v201)
	* [Releases v2.0.0](#releases-v200)

---
---

## Changelog

### Releases v2.3.1

1. Add setHostname() and related DHCP functions. Check [Only 15 UDP packets / second with W5100S-EVB-Pico possible? #6](https://github.com/khoih-prog/Ethernet_Generic/discussions/6#discussioncomment-2793483)
2. Add example [SetDHCPHostName](examples/SetDHCPHostName) to demo the new feature
3. Update `Packages' Patches`

### Releases v2.3.0

1. Add support to custom SPI for RP2040, Nano_RP2040_Connect, Portenta_H7, etc. using [Arduino-mbed core](https://github.com/arduino/ArduinoCore-mbed)


### Releases v2.2.0

1. Add support to STM32 boards using [Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32)
2. Add support to any board with core supporting custom hardware / software `SPI`, for example STM32.


### Releases v2.1.0

1. Add support to WIZNet W5100S. Check [Wiznet W5100S #56](https://github.com/khoih-prog/EthernetWebServer/discussions/56)


### Releases v2.0.1

1. Add support to `SPI1` for `RP2040` using [`Earle Philhower's arduino-pico` core](https://github.com/earlephilhower/arduino-pico)
2. Add example [WebClientRepeating_RP2040_SPI1](examples/WebClientRepeating_RP2040_SPI1) to demo the new feature
3. Update `Packages' Patches`

### Releases v2.0.0

1. Initial porting and coding to merge, as many as possible, the features of the following libraries :

	- [Ethernet](https://github.com/arduino-libraries/Ethernet)
	- [EthernetLarge](https://github.com/OPEnSLab-OSU/EthernetLarge)
	- [Ethernet2](https://github.com/adafruit/Ethernet2)
	- [Ethernet3](https://github.com/sstaub/Ethernet3)
	
2. Add support to ESP32 SPI2
3. Convert to h-only library
4. Add debug feature
5. Optimize code to reduce compiled binary size
6. Add `Packages' Patches`


