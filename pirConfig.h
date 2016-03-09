#ifndef FRONTPORCHIOTMODULE_PIRCONFIG_H_
#define FRONTPORCHIOTMODULE_PIRCONFIG_H_


const byte PIR_SENSOR_PIN   = 7;

unsigned long pirPreviousMillis = 0;

const long pirInterval = 1 * 1000UL;           // interval at which to take measurement (milliseconds)

void publish_pir_status()
{
  prog_buffer[0] = '\0';
  strcpy_P(prog_buffer, (char*)pgm_read_word(&(STATUS_TOPICS[7])));
  if(digitalRead(PIR_SENSOR_PIN) == HIGH) {
    DEBUG_LOG(1, "pir sensor detection");
    mqtt_client.publish(prog_buffer, "1");
  }
  else {
    DEBUG_LOG(1, "pir sensor NO detection");
    mqtt_client.publish(prog_buffer, "0");
  }
}


#endif   /* FRONTPORCHIOTMODULE_PIRCONFIG_H_ */
