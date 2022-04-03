/****************************************************************************************************************************
  multiFileProject.ino
  Ethernet_Generic is a library for the W5x00 Ethernet shields trying to merge the good features of
  previous Ethernet libraries
  
  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Generic
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#define ETHERNET_GENERIC_VERSION_MIN_TARGET      "Ethernet_Generic v2.0.0"
#define ETHERNET_GENERIC_VERSION_MIN             2000000

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <Ethernet_Generic.h>        // https://github.com/khoih-prog/Ethernet_Generic

void setup() 
{
  Serial.begin(115200);
  while (!Serial);

  delay(500);
  
  Serial.println("\nStart multiFileProject");
  Serial.println(ETHERNET_GENERIC_VERSION);

#if defined(ETHERNET_GENERIC_VERSION_MIN)
  if (ETHERNET_GENERIC_VERSION_INT < ETHERNET_GENERIC_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(ETHERNET_GENERIC_VERSION_MIN_TARGET);
  }
#endif

  Serial.print("You're OK now");
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
