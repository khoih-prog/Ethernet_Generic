/****************************************************************************************************************************
  Dhcp.h - Driver for W5x00

  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries

  Based on and modified from

  1) Ethernet Library         https://github.com/arduino-libraries/Ethernet
  2) EthernetLarge Library    https://github.com/OPEnSLab-OSU/EthernetLarge
  3) Ethernet2 Library        https://github.com/adafruit/Ethernet2
  4) Ethernet3 Library        https://github.com/sstaub/Ethernet3

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer

  Version: 2.7.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.0.0   K Hoang      31/03/2022 Initial porting and coding to support SPI2, debug, h-only library
  2.0.1   K Hoang      08/04/2022 Add support to SPI1 for RP2040 using arduino-pico core
  2.1.0   K Hoang      22/04/2022 Add support to WIZNet W5100S
  2.2.0   K Hoang      02/05/2022 Add support to custom SPI for any board, such as STM32
  2.3.0   K Hoang      03/05/2022 Add support to custom SPI for RP2040, Portenta_H7, etc. using Arduino-mbed core
  2.3.1   K Hoang      21/05/2022 Add setHostname() and related functions
  2.4.0   K Hoang      31/07/2022 Using raw_address() as default instead of private IPAddress data
  2.4.1   K Hoang      25/08/2022 Auto-select SPI SS/CS pin according to board package
  2.5.0   K Hoang      26/08/2022 Using raw_address() as default only for arduino-pico for compatibility
  2.5.1   K Hoang      01/09/2022 Slow SPI clock for old W5100 shield using SAMD Zero
  2.5.2   K Hoang      06/09/2022 Slow SPI clock only when necessary. Improve support for SAMD21
  2.6.0   K Hoang      11/09/2022 Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  2.6.1   K Hoang      23/09/2022 Fix bug for W5200
  2.6.2   K Hoang      26/10/2022 Add support to Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE using `mbed` or `nRF52` core
  2.7.0   K Hoang      14/11/2022 Fix severe limitation to permit sending larger data than 2/4/8/16K buffer
  2.7.1   K Hoang      15/11/2022 Auto-detect W5x00 and settings to set MAX_SIZE to send
 *****************************************************************************************************************************/

// DHCP Library v0.3 - April 25, 2009
// Author: Jordan Terrell - blog.jordanterrell.com

#ifndef Dhcp_h
#define Dhcp_h

/* DHCP state machine. */
#define STATE_DHCP_START        0
#define STATE_DHCP_DISCOVER     1
#define STATE_DHCP_REQUEST      2
#define STATE_DHCP_LEASED       3
#define STATE_DHCP_REREQUEST    4
#define STATE_DHCP_RELEASE      5

#define DHCP_FLAGSBROADCAST     0x8000

/* UDP port numbers for DHCP */
#define DHCP_SERVER_PORT        67  /* from server to client */
#define DHCP_CLIENT_PORT        68  /* from client to server */

/* DHCP message OP code */
#define DHCP_BOOTREQUEST        1
#define DHCP_BOOTREPLY          2

/* DHCP message type */
#define DHCP_DISCOVER           1
#define DHCP_OFFER              2
#define DHCP_REQUEST            3
#define DHCP_DECLINE            4
#define DHCP_ACK                5
#define DHCP_NAK                6
#define DHCP_RELEASE            7
#define DHCP_INFORM             8

#define DHCP_HTYPE10MB          1
#define DHCP_HTYPE100MB         2

#define DHCP_HLENETHERNET       6

#define DHCP_HOPS               0
#define DHCP_SECS               0

#define MAGIC_COOKIE            0x63825363
#define MAX_DHCP_OPT            16

#define HOST_NAME               "WIZnet"
#define DEFAULT_LEASE           (900) //default lease time in seconds

#define DHCP_CHECK_NONE         (0)
#define DHCP_CHECK_RENEW_FAIL   (1)
#define DHCP_CHECK_RENEW_OK     (2)
#define DHCP_CHECK_REBIND_FAIL  (3)
#define DHCP_CHECK_REBIND_OK    (4)

enum
{
  padOption                 = 0,
  subnetMask                = 1,
  timerOffset               = 2,
  routersOnSubnet           = 3,

  /* timeServer             = 4,
    nameServer              = 5,*/

  dns                       = 6,

  /*logServer               = 7,
    cookieServer            = 8,
    lprServer               = 9,
    impressServer           = 10,
    resourceLocationServer  = 11,*/

  hostName                  = 12,

  /*bootFileSize            = 13,
    meritDumpFile           = 14,*/

  domainName                = 15,

  /*swapServer              = 16,
    rootPath                = 17,
    extentionsPath          = 18,
    IPforwarding            = 19,
    nonLocalSourceRouting   = 20,
    policyFilter            = 21,
    maxDgramReasmSize       = 22,
    defaultIPTTL            = 23,
    pathMTUagingTimeout     = 24,
    pathMTUplateauTable     = 25,
    ifMTU                   = 26,
    allSubnetsLocal         = 27,
    broadcastAddr           = 28,
    performMaskDiscovery    = 29,
    maskSupplier            = 30,
    performRouterDiscovery  = 31,
    routerSolicitationAddr  = 32,
    staticRoute             = 33,
    trailerEncapsulation    = 34,
    arpCacheTimeout         = 35,
    ethernetEncapsulation   = 36,
    tcpDefaultTTL           = 37,
    tcpKeepaliveInterval    = 38,
    tcpKeepaliveGarbage     = 39,
    nisDomainName           = 40,
    nisServers              = 41,
    ntpServers              = 42,
    vendorSpecificInfo      = 43,
    netBIOSnameServer       = 44,
    netBIOSdgramDistServer  = 45,
    netBIOSnodeType         = 46,
    netBIOSscope            = 47,
    xFontServer             = 48,
    xDisplayManager         = 49,*/

  dhcpRequestedIPaddr       = 50,
  dhcpIPaddrLeaseTime       = 51,

  /*dhcpOptionOverload      = 52,*/

  dhcpMessageType           = 53,
  dhcpServerIdentifier      = 54,
  dhcpParamRequest          = 55,

  /*dhcpMsg                 = 56,
    dhcpMaxMsgSize          = 57,*/

  dhcpT1value               = 58,
  dhcpT2value               = 59,

  /*dhcpClassIdentifier     = 60,*/

  dhcpClientIdentifier      = 61,
  endOption                 = 255
};

typedef struct _RIP_MSG_FIXED
{
  uint8_t  op;
  uint8_t  htype;
  uint8_t  hlen;
  uint8_t  hops;
  uint32_t xid;
  uint16_t secs;
  uint16_t flags;
  uint8_t  ciaddr[4];
  uint8_t  yiaddr[4];
  uint8_t  siaddr[4];
  uint8_t  giaddr[4];
  uint8_t  chaddr[6];
} RIP_MSG_FIXED;

#endif
