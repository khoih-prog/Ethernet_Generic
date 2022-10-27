/****************************************************************************************************************************
  TelnetClient.ino - Simple Arduino web server sample for Ethernet shield

  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Generic
 *****************************************************************************************************************************/
/*
  Telnet client
  created 14 Sep 2010
  modified 9 Apr 2012
  by Tom Igoe
*/

#include "defines.h"

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 23 is default for telnet;
// if you're using Processing's ChatServer, use port 10002):
EthernetClient client;

// Enter the IP address of the server you're connecting to:
IPAddress server(192, 168, 2, 30);

#define TELNET_PORT     23

void setup()
{
  SerialDebug.begin(115200);

  while (!Serial && millis() < 5000);

  delay(500);

  SerialDebug.print("\nStarting TelnetClient on ");
  SerialDebug.print(BOARD_NAME);
  SerialDebug.print(F(" with "));
  SerialDebug.println(SHIELD_TYPE);
  SerialDebug.println(ETHERNET_GENERIC_VERSION);

#if (USING_SPI2)
#if defined(CUR_PIN_MISO)
  ETG_LOGWARN(F("Default SPI pinout:"));
  ETG_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
  ETG_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
  ETG_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
  ETG_LOGWARN1(F("SS:"),   CUR_PIN_SS);
  ETG_LOGWARN(F("========================="));
#endif
#else
  ETG_LOGWARN(F("Default SPI pinout:"));
  ETG_LOGWARN1(F("MOSI:"), MOSI);
  ETG_LOGWARN1(F("MISO:"), MISO);
  ETG_LOGWARN1(F("SCK:"),  SCK);
  ETG_LOGWARN1(F("SS:"),   SS);
  ETG_LOGWARN(F("========================="));
#endif

#if defined(ESP8266)
  // For ESP8266, change for other boards if necessary
#ifndef USE_THIS_SS_PIN
#define USE_THIS_SS_PIN   D2    // For ESP8266
#endif

  ETG_LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);

  // For ESP8266
  // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
  // Ethernet_Generic   X                 X            X            X            X        0
  // D2 is safe to used for Ethernet_Generic libs
  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

#elif defined(ESP32)

  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

#ifndef USE_THIS_SS_PIN
#define USE_THIS_SS_PIN   5   //22    // For ESP32
#endif

  ETG_LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);

  // Must use library patch for Ethernet, EthernetLarge libraries
  // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
  // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3

  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

#elif ETHERNET_USE_RPIPICO

  pinMode(USE_THIS_SS_PIN, OUTPUT);
  digitalWrite(USE_THIS_SS_PIN, HIGH);

  // ETHERNET_USE_RPIPICO, use default SS = 5 or 17
#ifndef USE_THIS_SS_PIN
#if defined(ARDUINO_ARCH_MBED)
#define USE_THIS_SS_PIN   17     // For Arduino Mbed core
#else
#define USE_THIS_SS_PIN   17    // For E.Philhower core
#endif
#endif

  ETG_LOGWARN1(F("RPIPICO setCsPin:"), USE_THIS_SS_PIN);

  // Must use library patch for Ethernet, EthernetLarge libraries
  // For RPI Pico using Arduino Mbed RP2040 core
  // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
  // For RPI Pico using E. Philhower RP2040 core
  // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
  // Default pin 5/17 to SS/CS

  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

#else   //defined(ESP8266)
  // unknown board, do nothing, use default SS = 10
#ifndef USE_THIS_SS_PIN
#define USE_THIS_SS_PIN   10    // For other boards
#endif

#if defined(BOARD_NAME)
  ETG_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);
#else
  ETG_LOGWARN1(F("Unknown board setCsPin:"), USE_THIS_SS_PIN);
#endif

  // For other boards, to change if necessary
  Ethernet.init (USE_THIS_SS_PIN);

#endif    // defined(ESP8266)

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  //SPIClass SPI2(HSPI);
  //Ethernet.begin(mac[index], &SPI2);

  // Just info to know how to connect correctly
  // To change for other SPI
#if defined(CUR_PIN_MISO)
  ETG_LOGWARN(F("Currently Used SPI pinout:"));
  ETG_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
  ETG_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
  ETG_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
  ETG_LOGWARN1(F("SS:"),   CUR_PIN_SS);
  ETG_LOGWARN(F("========================="));
#else
  ETG_LOGWARN(F("Currently Used SPI pinout:"));
  ETG_LOGWARN1(F("MOSI:"), MOSI);
  ETG_LOGWARN1(F("MISO:"), MISO);
  ETG_LOGWARN1(F("SCK:"),  SCK);
  ETG_LOGWARN1(F("SS:"),   SS);
  ETG_LOGWARN(F("========================="));
#endif

  SerialDebug.print(F("Using mac index = "));
  SerialDebug.println(index);

  SerialDebug.print(F("Connected! IP address: "));
  SerialDebug.println(Ethernet.localIP());

  if ( (Ethernet.getChip() == w5500) || (Ethernet.getAltChip() == w5100s) )
  {
    SerialDebug.print(F("Speed: "));
    SerialDebug.print(Ethernet.speedReport());
    SerialDebug.print(F(", Duplex: "));
    SerialDebug.print(Ethernet.duplexReport());
    SerialDebug.print(F(", Link status: "));
    SerialDebug.println(Ethernet.linkReport());
  }

  // give the Ethernet shield a second to initialize:
  delay(1000);
  SerialDebug.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, TELNET_PORT))
  {
    SerialDebug.println("connected");
  }
  else
  {
    // if you didn't get a connection to the server:
    SerialDebug.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available())
  {
    char c = client.read();
    SerialDebug.print(c);
  }

  // as long as there are bytes in the serial queue,
  // read them and send them out the socket if it's open:
  while (SerialDebug.available() > 0)
  {
    char inChar = SerialDebug.read();

    if (client.connected())
    {
      client.print(inChar);
    }
  }

  // if the server's disconnected, stop the client:
  if (!client.connected())
  {
    SerialDebug.println();
    SerialDebug.println("disconnecting.");
    client.stop();

    // do nothing:
    while (true)
    {
      delay(1);
    }
  }
}
