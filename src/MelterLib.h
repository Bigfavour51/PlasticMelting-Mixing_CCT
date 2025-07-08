#ifndef MELTERLIB_H
#define MELTERLIB_H

#include <Arduino.h>
// #include <SoftwareSerial.h>
#include <MAX6675.h>
#include "UARTMaster.h"

// === Global Variables ===

#define FWREL 13
#define STPREL 12
#define REVREL 10
#define GASPIN 14
#define BUZZPIN 11

#define CSPIN 5
#define SCKPIN 18
#define MISOPIN 19
#define MOSIPIN 23


class plasticMelter {
public:
    plasticMelter(int csPin, int sckPin, int misoPin, int mosiPin, int rxPin, int txPin, int buzzpin, int fwrel,
                  int stprel, int revrel, int gaspin);

    ~plasticMelter();

    void begin();
    void setTemperature(float temperature);
    float getTemperature();
    void startMelting();
    void stopMelting();
    bool isMelting();

    void TrigRelayON(int _dir);
    void TrigRelayOFF(int _dir);
    bool CydBtnChecker();
    
private:
    MAX6675 *thermocouple;
    // SoftwareSerial *serial;
    int csPin;
    int sckPin;
    int misoPin;
    int mosiPin;
    int rxPin;
    int txPin;
    int buzzpin;
    int fwrel;
    int stprel;
    int revrel;
    int gaspin;
    bool melting;
    float targetTemperature;
    void updateTemperature();
   
};



#endif 