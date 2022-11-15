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


* [Changelog](#changelog)
	* [Releases v2.7.1](#releases-v271)
	* [Releases v2.7.0](#releases-v270)
	* [Releases v2.6.2](#releases-v262)
	* [Releases v2.6.1](#releases-v261)
	* [Releases v2.6.0](#releases-v260)
	* [Releases v2.5.2](#releases-v252)
	* [Releases v2.5.1](#releases-v251)
	* [Releases v2.5.0](#releases-v250)
	* [Releases v2.4.1](#releases-v241)
	* [Releases v2.4.0](#releases-v240)
	* [Releases v2.3.1](#releases-v231)
	* [Releases v2.3.0](#releases-v230)
	* [Releases v2.2.0](#releases-v220)
	* [Releases v2.1.0](#releases-v210)
	* [Releases v2.0.1](#releases-v201)
	* [Releases v2.0.0](#releases-v200)

---
---

## Changelog

### Releases v2.7.1

1. Auto-detect `W5x00` and settings (`ETHERNET_LARGE_BUFFERS`, `MAX_SOCK_NUM`) to set `MAX_SIZE` to send. Check ['ETHERNET_SERVER_SEND_MAX_SIZE' was not declared in this scope #16](https://github.com/khoih-prog/Ethernet_Generic/issues/16)


### Releases v2.7.0

1. Fix severe limitation to permit sending larger data than 2/4/8/16K buffer
2. Add examples [EthernetWebServer_BigData](https://github.com/khoih-prog/Ethernet_Generic/tree/main/examples/EthernetWebServer_BigData) to demo how to send larger data than 2/4/8/16K buffer
3. Optimize code
4. Clean up
5. Update `Packages' Patches`

### Releases v2.6.2

1. Add support to Seeeduino nRF52840-based boards such as **Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE**, etc. using Seeed `mbed` or `nRF52` core
2. Add astyle using `allman` style. Restyle the library
3. Update `Packages' Patches` to add Seeeduino `nRF52` core

### Releases v2.6.1

1. Fix bug for `Wiznet W5200 / wiz820io`. Check [ESP32 - Wiznet W5200 problem #13](https://github.com/khoih-prog/Ethernet_Generic/discussions/13)
2. Update `Packages' Patches`

### Releases v2.6.0

1. Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using [DxCore](https://github.com/SpenceKonde/DxCore)


### Releases v2.5.2

1. Slow SPI clock only when necessary (such as for W5100, SAMD21 Zero, etc.)
2. Use correct Debug Terminal `Serial` for so-called **SAMD21 Zero** boards from Arduino as well as Adafruit


### Releases v2.5.1

1. Slow SPI clock to `8MHz` and select `SPI_MODE0` for old W5100 shield using SAMD Zero. Check [AdvancedWebServer example give me wrong ip HTTP EthernetWebServer is @ IP : 0.0.0.0 #62](https://github.com/khoih-prog/EthernetWebServer/issues/62)
2. Default to `W5100` to be safe. To change if using `W5200, W5500, W5100s` or testing faster SPI clock speeds


### Releases v2.5.0

1. Using `raw_address()` as default only for arduino-pico core for compatibility with remaining cores
2. Sync with [Ethernet library v2.0.1](https://github.com/arduino-libraries/Ethernet/releases/tag/2.0.1)
3. Add [Ethernet_Generic Library API](https://github.com/khoih-prog/Ethernet_Generic/blob/main/docs/api.md)


### Releases v2.4.1

1. Auto-select SPI(s) `SS/CS` pins according to board package if available
2. Update `Packages' Patches`

### Releases v2.4.0

1. Using raw_address() as default instead of private IPAddress data
2. Add missing `LibraryPatches` for ESP32
3. Update `Packages' Patches`

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


