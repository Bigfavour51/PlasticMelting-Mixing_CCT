#ifndef __UARTMaster__
#define __UARTMaster__

#include <Arduino.h>
#include "MelterLib.h"

// === Constants ===
#define NUM_THRESHOLDS 3
#define RESPONSE_BUFFER_SIZE 64
#define MSG_HEADER '#' 
#define MSG_TERMINATOR '\n'


#define TXPIN 17
#define RXPIN 16
#define BAUDRATE 9600



extern float slaveValues[NUM_THRESHOLDS];

extern bool extractorCtrl;
extern bool gasValve;
extern bool heatCtrl;


void uart_master_send(float _tempValue, float _targetTemp, bool _sysStatus);
void uart_master_setup();

#endif
