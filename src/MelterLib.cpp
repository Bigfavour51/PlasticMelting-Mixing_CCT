#include "MelterLib.h"




plasticMelter::plasticMelter(int csPin, int sckPin, int misoPin, int mosiPin, int rxPin, int txPin, int buzzpin, int fwrel,
                  int stprel, int revrel, int gaspin) 
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

    thermocouple = new MAX6675(sckPin, csPin, misoPin);
}

plasticMelter::~plasticMelter() 
{
   delete thermocouple;
}

void plasticMelter::begin() 
{
    pinMode(csPin, OUTPUT);
    pinMode(sckPin, OUTPUT);
    pinMode(misoPin, INPUT);
    pinMode(mosiPin, OUTPUT);
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    pinMode(buzzpin, OUTPUT);
    pinMode(fwrel, OUTPUT);
    pinMode(stprel, OUTPUT);
    pinMode(revrel, OUTPUT);
    pinMode(gaspin, OUTPUT);

    digitalWrite(buzzpin, 0);
    digitalWrite(fwrel, 0);
    digitalWrite(fwrel, 0);
    digitalWrite(stprel, 0);
    digitalWrite(revrel, 0);
    digitalWrite(gaspin, 0);

}


void plasticMelter::TrigRelayON(int _dir)
{
    digitalWrite(_dir, 1);
}
void plasticMelter::TrigRelayOFF(int _dir)
{
    digitalWrite(_dir, 0);
}



























void plasticMelter::setTemperature(float temp) {
    // method implementation
}

void plasticMelter::startMelting() {
    // method implementation
}

bool plasticMelter::isMelting() {
    // method implementation
    return false;
}

float plasticMelter::getTemperature() {
    // method implementation
    return 0.0;
}

void plasticMelter::stopMelting() {
    // method implementation
}


