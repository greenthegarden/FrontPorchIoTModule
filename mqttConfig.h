#ifndef FRONTPORCHIOTMODULE_MQTTCONFIG_H_
#define FRONTPORCHIOTMODULE_MQTTCONFIG_H_


#include <PubSubClient.h>

// MQTT parameters
//byte mqtt_server_addr[]           = { 192, 168, 1, 30 };  // Airology
byte mqtt_server_addr[]           = { 192, 168, 1, 55 };  // Pi eth0 interface
char mqtt_client_id[]             = "porchlight";
const int MQTT_PORT               = 1883;
#define MQTT_MAX_PACKET_SIZE        168
#define MQTT_KEEPALIVE              300

long lastReconnectAttempt         = 0;
const char COMMAND_SEPARATOR      = ':';

char message[BUFFER_SIZE];


// Status topics

const char CONNECTED_STATUS[]  PROGMEM = "porchlight/status/connected";
const char IP_ADDR_STATUS[]    PROGMEM = "porchlight/status/ip_addr";
const char UPTIME_STATUS[]     PROGMEM = "porchlight/status/uptime";
const char MEMORY_STATUS[]     PROGMEM = "porchlight/status/memory";
const char TIME_STATUS[]       PROGMEM = "porchlight/status/time";
const char LED_STATUS[]        PROGMEM = "porchlight/status/led";
const char COLOUR_STATUS[]     PROGMEM = "porchlight/status/colour";
const char PIR_STATUS[]        PROGMEM = "porchlight/status/pir";
const char DHT22_STATUS[]      PROGMEM = "porchlight/status/dht22";
const char TEMPERATURE_STATUS[] PROGMEM = "porchlight/status/temperature";
const char HUMIDITY_STATUS[]   PROGMEM = "porchlight/status/humidity";

PGM_P const STATUS_TOPICS[]    PROGMEM = { CONNECTED_STATUS,    // idx = 0
                                           IP_ADDR_STATUS,      // idx = 1
                                           UPTIME_STATUS,       // idx = 2
                                           MEMORY_STATUS,       // idx = 3
                                           TIME_STATUS,         // idx = 4
                                           LED_STATUS,          // idx = 5
                                           COLOUR_STATUS,       // idx = 6
                                           PIR_STATUS,          // idx = 7
                                           DHT22_STATUS,        // idx = 8
                                           TEMPERATURE_STATUS,  // idx = 9
                                           HUMIDITY_STATUS,     // idx = 10
                                          };


// Control topics

const char LED_CONTROL[]       PROGMEM = "porchlight/control/led";

PGM_P const CONTROL_TOPICS[]   PROGMEM = { LED_CONTROL,         // idx = 0
                                          };


// callback function definition
void callback(char* topic, uint8_t* payload, unsigned int length);

PubSubClient   mqtt_client(mqtt_server_addr, MQTT_PORT, callback, ethernet_client);

void publish_connected()
{
  prog_buffer[0] = '\0';
  strcpy_P(prog_buffer, (char*)pgm_read_word(&(STATUS_TOPICS[0])));
  mqtt_client.publish(prog_buffer, "");
}

void publish_ip_address()
{
  prog_buffer[0] = '\0';
  strcpy_P(prog_buffer, (char*)pgm_read_word(&(STATUS_TOPICS[1])));
  mqtt_client.publish(prog_buffer, "192.168.1.90");
}

void publish_uptime()
{
  prog_buffer[0] = '\0';
  strcpy_P(prog_buffer, (char*)pgm_read_word(&(STATUS_TOPICS[2])));
  char_buffer[0] = '\0';
  ltoa(millis(), char_buffer, 10);
  mqtt_client.publish(prog_buffer, char_buffer);
}


#endif   /* FRONTPORCHIOTMODULE_MQTTCONFIG_H_ */
