#ifndef FRONTPORCHIOTMODULE_PIRCONFIG_H_
#define FRONTPORCHIOTMODULE_PIRCONFIG_H_


const byte PIR_SENSOR_PIN   = 7;

unsigned long pirPreviousMillis = 0;

const unsigned long pirInterval = 1 * 1000UL;           // interval at which to take measurement (milliseconds)

boolean previousPirDetection = false;

void publish_pir_status()
{
  prog_buffer[0] = '\0';
  strcpy_P(prog_buffer, (char*)pgm_read_word(&(STATUS_TOPICS[7])));
  if(previousPirDetection) {
    DEBUG_LOG(1, "pir sensor detection");
    mqttClient.publish(prog_buffer, "1");
  }
  else {
    DEBUG_LOG(1, "pir sensor NO detection");
    mqttClient.publish(prog_buffer, "0");
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


#endif   /* FRONTPORCHIOTMODULE_PIRCONFIG_H_ */
