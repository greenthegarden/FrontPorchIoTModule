#ifndef FRONTPORCHIOTMODULE_CONFIG_H_
#define FRONTPORCHIOTMODULE_CONFIG_H_


#include "debug.h"

// Macros
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


const byte BUFFER_SIZE            = 32;
char prog_buffer[BUFFER_SIZE];
char char_buffer[BUFFER_SIZE];

const int FLOAT_DECIMAL_PLACES    = 1;

const int BAUD_RATE               = 9600;


#include "ethernetConfig.h"
#include "mqttConfig.h"

#include <duinotech595.h>

const byte LATCH_PIN = 6;
const byte CLOCK_PIN = 5;
const byte DATA_PIN  = 4;

Duinotech595 duinotech595(LATCH_PIN, DATA_PIN, CLOCK_PIN);
//Duinotech595 duinotech595();

#include "pirConfig.h"

#include "dht22Config.h"

#endif   /* FRONTPORCHIOTMODULE_CONFIG_H_ */

