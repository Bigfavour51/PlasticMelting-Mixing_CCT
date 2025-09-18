#include "UARTMaster.h"
#include "MelterLib.h"

// === Global Variables ===
float slaveValues[NUM_THRESHOLDS];

 bool extractorCtrl = false;
 bool gasValve = false;
 bool heatCtrl = false;



void uart_master_setup() {
  Serial.begin(115200);
  Serial2.begin(BAUDRATE, SERIAL_8N1, RXPIN, TXPIN);
  delay(1000);
  Serial.println("MASTER READY");
}

void uart_master_send(float _tempValue, float _targetTemp, bool _sysStatus) {
  // Send data to slave
  String payload = "#" + String(',') + String(_tempValue) + "," +
                   String(_targetTemp) + "," + String(_sysStatus) + "\n";

                   //+ String(HourValue) + String(MinuteValue)
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

    if (idx == 3) {
      extractorCtrl = slaveValues[0];
      gasValve = slaveValues[1];
      heatCtrl = slaveValues[2];

      Serial.println("Parsed values from slave:");
      Serial.print("Extractor Control: "); Serial.println(extractorCtrl);
      Serial.print("Gas Valve: "); Serial.println(gasValve);
      Serial.print("Heat Control: "); Serial.println(heatCtrl);
    }
  }

  delay(1000);

  
}



