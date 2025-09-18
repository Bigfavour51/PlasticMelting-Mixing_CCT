#include "MelterLib.h"
#include "UARTMaster.h"
#include <SPI.h>



float curTemperature = 0.0;
bool heaterstatus = false;

plasticMelter::plasticMelter(int csPin, int sckPin, int misoPin, int mosiPin, int rxPin, int txPin, int buzzpin, int fwrel,
                  int stprel, int revrel, int gaspin, int scl, int sda) 
{
    this->csPin = csPin;
    this->sckPin = sckPin;
    this->misoPin = misoPin;
    this->mosiPin = mosiPin;
    this->rxPin = rxPin;
    this->txPin = txPin;
    this->buzzpin = buzzpin;
    this->fwrel = fwrel;
    this->stprel = stprel;
    this->revrel = revrel;
    this->gaspin = gaspin;
    this->scl = scl;
    this->sda = sda;

    // Adafruit_MAX31865 max31865 = Adafruit_MAX31865(csPin, mosiPin, misoPin, sckPin);
    // this->thermocouple = &max31865;

}
plasticMelter::~plasticMelter() 
{
    // if (thermocouple) {
    //     delete thermocouple;
    //     thermocouple = nullptr;
    // }
}

void plasticMelter::begin() 
{
    pinMode(buzzpin, OUTPUT);
    pinMode(fwrel, OUTPUT);
    pinMode(stprel, OUTPUT);
    pinMode(revrel, OUTPUT);
    pinMode(gaspin, OUTPUT);
    pinMode(ExtractorPIN, OUTPUT);
   

    digitalWrite(buzzpin, LOW);
    digitalWrite(fwrel, Relay_OFF);
    digitalWrite(stprel, Relay_OFF);
    digitalWrite(revrel, Relay_OFF);
    digitalWrite(gaspin, Relay_OFF);
    digitalWrite(ExtractorPIN, Relay_OFF);


    if (thermocouple) {
        thermocouple->begin(MAX31865_3WIRE);  // Initialize the MAX31865 for 3-wire RTD
    }

 
}

void plasticMelter::TrigRelayON(int _dir){digitalWrite(_dir, 1);}
void plasticMelter::TrigRelayOFF(int _dir){digitalWrite(_dir, 0);}


float plasticMelter::getTemperature()
{
    uint16_t rtd = thermocouple->readRTD();
   float ratio = rtd / 32768.0;
   float resistance = ratio * 430.0;  // Use 430Ω if your board uses that reference
   float currentTemperature = thermocouple->temperature(100.0, 430.0); // PT1000 & 430Ω ref
   return currentTemperature;

}

bool plasticMelter :: targetTemperatureReached()
{
  return (currentTemperature >= targetTemperature) ? true : false;
}

void plasticMelter::gasValveOn() {
    digitalWrite(gaspin, Relay_ON);
}

void plasticMelter::gasValveOff() {
    digitalWrite(gaspin, Relay_OFF);
}

void plasticMelter::extractorOn() {
    digitalWrite(ExtractorPIN, Relay_ON);
}

void plasticMelter::extractorOff() {
    digitalWrite(ExtractorPIN, Relay_OFF);
}

void plasticMelter::buzzOn() {
    digitalWrite(buzzpin, Relay_ON);
    delay(2000);
    digitalWrite(buzzpin, Relay_OFF);
}

void plasticMelter::buzzOff() {
    digitalWrite(buzzpin, Relay_OFF);
}

bool plasticMelter::isMotorRunning() 
{
    MotorRunning = false;
    if (digitalRead(fwrel) == Relay_ON || digitalRead(revrel) == Relay_ON) {
        return MotorRunning = true;
    }
    else
    return MotorRunning = false;
}

bool plasticMelter::isMelting() 
{
    melting = false;
    if (digitalRead(fwrel) == Relay_ON || digitalRead(revrel) == Relay_ON  && digitalRead(gaspin) == Relay_ON) 
    {
        return melting = true;
    }
    else
    return melting = false;
}

void plasticMelter::startMotor() {
    digitalWrite(fwrel, Relay_ON);
    digitalWrite(stprel, Relay_OFF);
    digitalWrite(revrel, Relay_OFF);
    for (int i = 0; i < 3; i++) {
        digitalWrite(buzzpin, Relay_ON);
        delay(200);
        digitalWrite(buzzpin, Relay_OFF);
        delay(200);
    }

}

void plasticMelter::stopMotor() {
    digitalWrite(fwrel, Relay_OFF);
    digitalWrite(stprel, Relay_OFF);
    digitalWrite(revrel, Relay_OFF);

}

void plasticMelter::reverseMotor() {
    digitalWrite(fwrel, Relay_OFF);
    digitalWrite(stprel, Relay_OFF);
    digitalWrite(revrel, Relay_ON);
    
    for (int i = 0; i < 3; i++) {
        digitalWrite(buzzpin, Relay_ON);
        delay(200);
        digitalWrite(buzzpin, Relay_OFF);
        delay(200);
    }
}



