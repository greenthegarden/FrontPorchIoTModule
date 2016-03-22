#ifndef SENSORLIGHTIOTMODULE_ETHERNETCONFIG_H_
#define SENSORLIGHTIOTMODULE_ETHERNETCONFIG_H_


// Ethernet libraries
#include <SPI.h>
#include <Ethernet.h>


// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 90);

EthernetClient ethernetClient;

const unsigned long NETWORK_STARTUP_DELAY = 5000UL;

const byte ETHERNET_CS_PIN = 10;


#endif   /* SENSORLIGHTIOTMODULE_ETHERNETCONFIG_H_ */

