#include "config.h"

boolean mqtt_connect()
{
  DEBUG_LOG(1, "connecting to broker");
  if (mqtt_client.connect(mqtt_client_id)) {
    DEBUG_LOG(1, "  connected");
    publish_connected();
    publish_ip_address();
    // subscribe to topics (should have list)
    mqtt_client.subscribe("porchlight/control/#");
  }
  return mqtt_client.connected();
}

void callback(char* topic, uint8_t* payload, unsigned int payload_length)
{
  // handle message arrived
  /* topic = part of the variable header:has topic name of the topic where the publish received
       NOTE: variable header does not contain the 2 bytes with the
            publish msg ID
      payload = pointer to the first item of the buffer array that
                contains the message tha was published
               EXAMPLE of payload: lights,1
      length = the length of the payload, until which index of payload
  */

  DEBUG_LOG(1, "Payload length is");
  DEBUG_LOG(1, payload_length);

  // Copy the payload to the new buffer
  char* message = (char*)malloc((sizeof(char) * payload_length) + 1); // get the size of the bytes and store in memory
  memcpy(message, payload, payload_length * sizeof(char));        // copy the memory
  message[payload_length * sizeof(char)] = '\0';                  // add terminating character

  DEBUG_LOG(1, "Message with topic");
  DEBUG_LOG(1, topic);
  DEBUG_LOG(1, "arrived with payload");
  DEBUG_LOG(1, message);

  byte topic_idx = 0;
  boolean control_topic_found = false;

  // find if topic is matched
  for (byte i = 0; i < ARRAY_SIZE(CONTROL_TOPICS); i++) {
    prog_buffer[0] = '\0';
    strcpy_P(prog_buffer, (PGM_P)pgm_read_word(&(CONTROL_TOPICS[i])));
    if (strcmp(topic, prog_buffer) == 0) {
      topic_idx = i;
      control_topic_found = true;
      break;
    }
  }

  if (control_topic_found) {

    DEBUG_LOG(1, "Control topic index");
    DEBUG_LOG(1, topic_idx);

    //switch to case statements
    if (topic_idx == 0) {  // topic is LED_CONTROL
      DEBUG_LOG(1, "LED_CONTROL topic arrived");
      if (strcmp(message, "OFF") == 0)
        duinotech595.off();
      else if (strcmp(message, "GREEN") == 0)
        duinotech595.green();
      else if (strcmp(message, "RED") == 0)
        duinotech595.red();
      else if (strcmp(message, "BLUE") == 0)
        duinotech595.blue();
      else if (strcmp(message, "WHITE") == 0)
        duinotech595.white();
      else if (strcmp(message, "ON") == 0)
        duinotech595.on();
      else {
        DEBUG_LOG(1, "Unknown message arrived");
      }
    } else {  // unknown control topic has arrived - ignore!!
      DEBUG_LOG(1, "Unknown control topic arrived");
    }
  }

  // free memory assigned to message
  free(message);
}

/*--------------------------------------------------------------------------------------
  setup()
  Called by the Arduino framework once, before the main loop begins
  --------------------------------------------------------------------------------------*/
void setup()
{
#if DEBUG_LEVEL > 0
  Serial.begin(BAUD_RATE);
#endif

  // set up for Duinotech 595
  duinotech595.init();
  duinotech595.sequenceTest();  

  // Configure Ethernet
  Ethernet.begin(mac, ip);
  delay(1500);
  if (mqtt_client.connected())
    duinotech595.blinkOk(3);
  else
    duinotech595.blinkError(5);

  // set up for PIR sensor
  pinMode(PIR_SENSOR_PIN, INPUT);

  // set up for DHT22 sensor
}

/*--------------------------------------------------------------------------------------
  loop()
  Arduino main loop
  --------------------------------------------------------------------------------------*/
void loop()
{
  unsigned long currentMillis = millis();

  if (!mqtt_client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > reconnectInterval) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (mqtt_connect()) {
        lastReconnectAttempt = 0;
      }
      else {
        duinotech595.blinkError(2);
      }
    }
  } else {
    // Client connected
    mqtt_client.loop();
  }

  if (currentMillis - pirPreviousMillis >= pirInterval) {
    pirPreviousMillis = currentMillis;
    publish_pir_status();
  }
  
  if (currentMillis - dht22PreviousMillis >= dht22Interval) {
    dht22PreviousMillis = currentMillis;
    publish_dht22_measurement();
  }
}

