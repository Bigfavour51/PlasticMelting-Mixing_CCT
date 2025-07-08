#include <Arduino.h>
#include "UARTMaster.h"  // Include the slave header for accessing the shared variables



void setup() {
 uart_master_setup();  // Initialize UART communication
}

void loop() {
  uart_master_send();  // Send data to the slave and receive response
  delay(1000);          // Wait before sending the next message
}
