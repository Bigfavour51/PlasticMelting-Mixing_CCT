#include "UARTMaster.h"

// === Global Variables ===
float slaveValues[NUM_THRESHOLDS];

bool MotorSTART = false;
bool MotorSTOP = false;
bool MotorRev = false;
bool GasValve = false;
float Countdown = 0.0;

float tempValue = 30.0;
bool dangerAlert = false;
bool extraAlert = false;


void uart_master_setup() {
  Serial.begin(115200);
  Serial2.begin(BAUDRATE, SERIAL_8N1, RXPIN, TXPIN);
  delay(1000);
  Serial.println("MASTER READY");
}

void uart_master_send() {
  // Send data to slave
  String payload = "#" + String(',') + String(tempValue) + "," +
                   String(dangerAlert) + "," + String(extraAlert) + "\n";

  Serial2.print(payload);
  Serial.print("Sent to slave: ");
  Serial.println(payload);

  // Wait for response
  String response = "";
  unsigned long start = millis();
  while (millis() - start < 1000) {
    while (Serial2.available()) {
      char c = Serial2.read();
      response += c;
    }
    if (response.endsWith("\n")) break;
  }

  if (response.length()) {
    Serial.print("Received from slave: ");
    Serial.println(response);

    response.trim();
    if (response.charAt(0) == '#') response.remove(0, 1);
    if (response.charAt(0) == ',') response.remove(0, 1);

    char buf[64];
    response.toCharArray(buf, sizeof(buf));
    char *token = strtok(buf, ",");
    int idx = 0;
    float slaveValues[5];

    while (token && idx < 5) {
      slaveValues[idx++] = atof(token);
      token = strtok(NULL, ",");
    }

    if (idx == 5) {
      MotorSTART = slaveValues[0];
      MotorSTOP  = slaveValues[1];
      MotorRev   = slaveValues[2];
      GasValve   = slaveValues[3];
      Countdown  = slaveValues[4];

      Serial.println("Parsed values from slave:");
      Serial.print("MotorSTART: "); Serial.println(MotorSTART);
      Serial.print("MotorSTOP : "); Serial.println(MotorSTOP);
      Serial.print("MotorRev  : "); Serial.println(MotorRev);
      Serial.print("GasValve  : "); Serial.println(GasValve);
      Serial.print("Countdown : "); Serial.println(Countdown);
    }
  }

  delay(1000);

  
}



