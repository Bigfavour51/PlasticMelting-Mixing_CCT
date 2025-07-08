#ifndef __UARTMaster__
#define __UARTMaster__

#include <Arduino.h>

// === Constants ===
#define NUM_THRESHOLDS 5
#define RESPONSE_BUFFER_SIZE 64
#define MSG_HEADER '#' 
#define MSG_TERMINATOR '\n'


#define TXPIN 17
#define RXPIN 16
#define BAUDRATE 9600



extern float slaveValues[NUM_THRESHOLDS];

extern bool MotorSTART;
extern bool MotorSTOP;
extern bool MotorRev;
extern bool GasValve;
extern float Countdown;

extern float tempValue;
extern bool dangerAlert;
extern bool extraAlert;

void uart_master_send();
void uart_master_setup();

#endif
