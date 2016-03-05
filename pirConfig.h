#ifndef FRONTPORCHIOTMODULE_PIRCONFIG_H_
#define FRONTPORCHIOTMODULE_PIRCONFIG_H_


const byte PIR_SENSOR_PIN   = 7;

unsigned long pirPreviousMillis = 0;

const long pirInterval = 1 * 1000UL;           // interval at which to take measurement (milliseconds)

boolean pirDectionState = false;

void pirDetection() {
  if(digitalRead(PIR_SENSOR_PIN) == HIGH)
    pirDectionState = true;
  else
    pirDectionState = false;
}

void publish_pir_status();


#endif   /* FRONTPORCHIOTMODULE_PIRCONFIG_H_ */
