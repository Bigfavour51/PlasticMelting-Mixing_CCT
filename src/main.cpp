#include <Arduino.h>
#include "MelterLib.h"  // Include the melter library header
#include "UARTMaster.h"  // Include the slave header for accessing the shared variables


//creating a plasticMelter instance
plasticMelter melter(CSPIN, SCKPIN, MISOPIN, MOSIPIN, RXPIN, TXPIN, BUZZPIN, FWREL, STPREL, REVREL, GASPIN);
unsigned long motorStartTime = 0;
bool isMotorRunning = false;


void setup() {
 uart_master_setup();  // Initialize UART communication
 melter.begin();        // Initialize the plastic melter
}


void loop() {
  uart_master_send();  // Should be non-blocking ideally

  if (MotorSTART && !isMotorRunning) {
    melter.TrigRelayON(FWREL);
    Serial.println("FWREL, ON");
    motorStartTime = millis();
    isMotorRunning = true;
  }

  if (isMotorRunning && (millis() - motorStartTime >= 4000)) {
    melter.TrigRelayOFF(FWREL);
    Serial.println("FWREL, OFF");
    isMotorRunning = false;
  }

//   Keep loop tight and responsive — no delay()!
}
