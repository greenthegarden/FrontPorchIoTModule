#ifndef SENSORLIGHTIOTMODULE_SDCONFIG_H_
#define SENSORLIGHTIOTMODULE_SDCONFIG_H_


#include <SPI.h>
#include <SD.h>


const byte SDCARD_CS_PIN = 4;  // define SD Card chip select pin

//File configFile;

const char configFilename[] = "SensorLightIoTModule.cfg";

void readFile()
{
  File file;

  file = SD.open(configFilename);
  if (file) {
    // array for value data:
    while (file.available()) {       // read the settings file:
      byte i = 0;
      boolean paramEnd = false;

      while (!paramEnd) {        // while not at the end of the parameter keep reading:
        chtr = file.read();
        if (chtr != ':') {        // if the char from file is not a':' read it in:
          name[i] = chtr;
          i++;
        } else {
          paramEnd = true;                 // otherwise we have come to the end of our parmeter name:
        }
      }
      byte j = 0;
      boolean valueEnd = false;
      value[0] = '\0';                               // reset our array pointer:
      while (!valueEnd) {
        chtr = file.read();
        if (chtr != ',') {     // if the char from file is not a ',' read it in:
          value[j] = chtr;
          j++;
        } else {
          valueEnd = true;   // otherwise we have come to the end of our value:
        }
      }

      if (!strcmp(name, "ip0")) {
        ip[0] = atoi(value);          // assign value to ip0 first ip octet:
      }
      if (!strcmp(name, "ip1")) {
        ip[1] = atoi(value);          // assign value to ip1 first ip octet:
      }
      if (!strcmp(name, "ip2")) {
        ip[2] = atoi(value);          // assign value to ip2 first ip octet:
      }
      if (!strcmp(name, "ip3")) {
        ip[3] = atoi(value);          // assign value to ip4 first ip octet:

      }
    }
  }
}


#endif   /* SENSORLIGHTIOTMODULE_PIRCONFIG_H_ */

