/****************************************************************************************************************************
  multiFileProject.ino
  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Generic
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#define ETHERNET_GENERIC_VERSION_MIN_TARGET      "Ethernet_Generic v2.6.2"
#define ETHERNET_GENERIC_VERSION_MIN             2006002

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <Ethernet_Generic.h>        // https://github.com/khoih-prog/Ethernet_Generic

void setup()
{
  SerialDebug.begin(115200);

  while (!Serial && millis() < 5000);

  delay(500);

  SerialDebug.println("\nStart multiFileProject");
  SerialDebug.println(ETHERNET_GENERIC_VERSION);

#if defined(ETHERNET_GENERIC_VERSION_MIN)

  if (ETHERNET_GENERIC_VERSION_INT < ETHERNET_GENERIC_VERSION_MIN)
  {
    SerialDebug.print("Warning. Must use this example on Version equal or later than : ");
    SerialDebug.println(ETHERNET_GENERIC_VERSION_MIN_TARGET);
  }

#endif

  SerialDebug.print("You're OK now");
}

void loop()
{
  // put your main code here, to run repeatedly:
}
