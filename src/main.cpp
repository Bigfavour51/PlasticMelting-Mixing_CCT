#include <Arduino.h>
#include <MelterLib.h>
#include <Adafruit_MAX31865.h>

// SPI pins for ESP32 hardware SPI
#define MAX31865_CS   5   // Chip Select
#define MAX31865_MOSI 23
#define MAX31865_MISO 19
#define MAX31865_SCK  18

Adafruit_MAX31865 max31865 = Adafruit_MAX31865(MAX31865_CS, MAX31865_MOSI,
                                               MAX31865_MISO, MAX31865_SCK);
plasticMelter melter(CSPIN, SCKPIN, MISOPIN, MOSIPIN, RXPIN, TXPIN, BUZZPIN, FWREL, STPREL, REVREL, GASPIN, SCL, SDA);



void setup() {
  Serial.begin(115200);
  max31865.begin(MAX31865_3WIRE);  
  uart_master_setup();  // Initialize UART communication
  melter.begin();        // Initialize the plastic melter
  Serial.println("MAX31865 PT1000 (3-Wire) on ESP32");
  // Options: MAX31865_2WIRE, MAX31865_3WIRE, MAX31865_4WIRE
  delay(1000);
}

void loop() 
{
  float Tempvalue = getTemperature();
  bool targetTemp = targetTemperatureReached();// Example target temperature1
  uart_master_send(Tempvalue,targetTemperature, heaterstatus);  // Send data to slave

   if(gasValve ) {melter.gasValveOn(); } else {melter.gasValveOff(); }
   if(extractorCtrl) {melter.extractorOn(); } else {melter.extractorOff(); }
   if(heatCtrl) {melter.gasValveOff(); heaterstatus = true; } else { heaterstatus = false; }



  delay(50);
}


float getTemperature() {
  uint16_t rtd = max31865.readRTD();
  float ratio = rtd / 32768.0;
  float resistance = ratio * 4300.0;  // Use 430Ω if your board uses that reference
  curTemperature= max31865.temperature(100.0, 430.0); // PT1000 & 430Ω ref
  return curTemperature;
}

bool targetTemperatureReached()
{
  return (curTemperature >= targetTemperature) ? true : false;
}

