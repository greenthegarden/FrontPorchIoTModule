#ifndef SENSORLIGHTIOTMODULE_PIRCONFIG_H_
#define SENSORLIGHTIOTMODULE_PIRCONFIG_H_


const byte PIR_SENSOR_PIN             = 7;

unsigned long pirPreviousMillis       = 0UL;

const unsigned long PIR_READ_INTERVAL = 1UL * 1000UL;           // interval at which to take measurement (milliseconds)

boolean previousPirDetection          = false;

void publish_pir_status() {
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[7])));
  if(previousPirDetection) {
    DEBUG_LOG(1, "pir sensor detection");
    mqttClient.publish(progBuffer, "1");
  }
  else {
    DEBUG_LOG(1, "pir sensor NO detection");
    mqttClient.publish(progBuffer, "0");
  }
}

void read_pir_sensor() {
  boolean currentPirDetection;
  if(digitalRead(PIR_SENSOR_PIN) == HIGH)
    currentPirDetection = true;
  else
    currentPirDetection = false;
  if (currentPirDetection != previousPirDetection) {
    previousPirDetection = currentPirDetection;
    publish_pir_status();
  }
}


#endif   /* SENSORLIGHTIOTMODULE_PIRCONFIG_H_ */
