#ifndef SENSORLIGHTIOTMODULE_DHT22CONFIG_H_
#define SENSORLIGHTIOTMODULE_DHT22CONFIG_H_


#include <dht.h>                // DHT22 temperature/humidty sensor library


dht DHT;

const int DHT22_PIN                     = 10;

unsigned long dht22PreviousMillis       = 0UL;

const unsigned long DHT22_READ_INTERVAL = 5UL * 60UL * 1000UL;           // interval at which to take measurement (milliseconds)


// DHT22 status messages
const char DHT22_STATUS_OK[]        PROGMEM = "OK";
const char DHT22_CHECKSUM_ERROR[]   PROGMEM = "Checksum error";
const char DHT22_TIMEOUT_ERROR[]    PROGMEM = "Time out error";
const char DHT22_CONNECT_ERROR[]    PROGMEM = "Connect error";
const char DHT22_ACK_LOW_ERROR[]    PROGMEM = "Ack Low error";
const char DHT22_ACK_HIGH_ERROR[]   PROGMEM = "Ack High error";
const char DHT22_UNKNOWN_ERROR[]    PROGMEM = "Unknown error";

PGM_P const DHT22_STATUS_MESSAGES[] PROGMEM = { DHT22_STATUS_OK,        // idx = 0
                                                DHT22_CHECKSUM_ERROR,   // idx = 1
                                                DHT22_TIMEOUT_ERROR,    // idx = 2
                                                DHT22_CONNECT_ERROR,    // idx = 3
                                                DHT22_ACK_LOW_ERROR,    // idx = 4
                                                DHT22_ACK_HIGH_ERROR,   // idx = 5
                                                DHT22_UNKNOWN_ERROR,    // idx = 6
                                              };

void publish_temperature_measurement()
{
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[9])));
  DEBUG_LOG(3, "DHT22 temperature measurement: ");
  // value is stored in DHT object
  DEBUG_LOG(3, DHT.temperature);
  charBuffer[0] = '\0';
  dtostrf(DHT.temperature, 1, FLOAT_DECIMAL_PLACES, charBuffer);
  mqttClient.publish(progBuffer, charBuffer);
}

void publish_humidity_measurement()
{
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[10])));
  DEBUG_LOG(3, "DHT22 humidity measurement: ");
  // value is stored in DHT object
  DEBUG_LOG(3, DHT.humidity);
  charBuffer[0] = '\0';
  dtostrf(DHT.humidity, 1, FLOAT_DECIMAL_PLACES, charBuffer);
  mqttClient.publish(progBuffer, charBuffer);
}

void publish_dht22_measurement()
{
  // READ DATA
  int chk = DHT.read22(DHT22_PIN);

  DEBUG_LOG(1, "DHT22 read state");
  DEBUG_LOG(1, "  value: ");
  DEBUG_LOG(1, chk);
  DEBUG_LOG(1, "  string: ");

  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[8])));

  charBuffer[0] = '\0';
  switch (chk) {
    case DHTLIB_OK :
      DEBUG_LOG(3, "OK");
//      charBuffer[0] = '\0';
      strcpy_P(charBuffer, (char*)pgm_read_word(&(DHT22_STATUS_MESSAGES[0])));
//      mqttClient.publish(progBuffer, charBuffer);
      break;
    case DHTLIB_ERROR_CHECKSUM :
      DEBUG_LOG(3, "Checksum error");
//      charBuffer[0] = '\0';
      strcpy_P(charBuffer, (char*)pgm_read_word(&(DHT22_STATUS_MESSAGES[1])));
//      mqttClient.publish(progBuffer, charBuffer);
      break;
    case DHTLIB_ERROR_TIMEOUT :
      DEBUG_LOG(3, "Time out error,\t");
//      charBuffer[0] = '\0';
      strcpy_P(charBuffer, (char*)pgm_read_word(&(DHT22_STATUS_MESSAGES[2])));
//      mqttClient.publish(progBuffer, charBuffer);
      break;
    case DHTLIB_ERROR_CONNECT :
      DEBUG_LOG(3, "Connect error");
//      charBuffer[0] = '\0';
      strcpy_P(charBuffer, (char*)pgm_read_word(&(DHT22_STATUS_MESSAGES[3])));
//      mqttClient.publish(progBuffer, charBuffer);
      break;
    case DHTLIB_ERROR_ACK_L :
      DEBUG_LOG(3, "Ack Low error");
//      charBuffer[0] = '\0';
      strcpy_P(charBuffer, (char*)pgm_read_word(&(DHT22_STATUS_MESSAGES[4])));
//      mqttClient.publish(progBuffer, charBuffer);
      break;
    case DHTLIB_ERROR_ACK_H :
      DEBUG_LOG(3, "Ack High error");
//      charBuffer[0] = '\0';
      strcpy_P(charBuffer, (char*)pgm_read_word(&(DHT22_STATUS_MESSAGES[5])));
//      mqttClient.publish(prog_buffer, char_buffer);
      break;
    default :
      DEBUG_LOG(3, "Unknown error");
//      charBuffer[0] = '\0';
      strcpy_P(charBuffer, (char*)pgm_read_word(&(DHT22_STATUS_MESSAGES[6])));
//      mqttClient.publish(progBuffer, charBuffer);
      break;
  }
  mqttClient.publish(progBuffer, charBuffer);
  
  if (chk == DHTLIB_OK) {
    publish_temperature_measurement();
    publish_humidity_measurement();
  }
}


#endif  /* SENSORLIGHTIOTMODULE_DHT22CONFIG_H_ */

