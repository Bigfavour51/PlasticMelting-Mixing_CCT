#include <Arduino.h>
#include "MelterLib.h"  // Include the melter library header
#include "UARTMaster.h"  // Include the slave header for accessing the shared variables


//creating a plasticMelter instance
plasticMelter melter(CSPIN, SCKPIN, MISOPIN, MOSIPIN, RXPIN, TXPIN, BUZZPIN, FWREL, STPREL, REVREL, GASPIN, SCL, SDA);
unsigned long motorStartTime = 0;
bool isMotorRunning = false;


void setup() {
 uart_master_setup();  // Initialize UART communication
 melter.begin();        // Initialize the plastic melter
 setup_rtc();
}


void loop() 
{
  uart_master_send();  // Should be non-blocking ideally

  if (MotorSTART) { melter.startMotor();} else melter.stopMotor();
  if (GasValve){ melter.gasValveOn(); } else melter.gasValveOff();
  if (MotorRev){melter.reverseMotor();} else melter.stopMotor();
  
  // getTime();

}




