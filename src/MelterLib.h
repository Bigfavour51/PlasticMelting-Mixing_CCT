#ifndef MELTERLIB_H
#define MELTERLIB_H

#include <Arduino.h>
// #include <SoftwareSerial.h>
#include <MAX6675.h>
#include "UARTMaster.h"

// === Global Variables ===

#define FWREL 17
#define STPREL 16
#define REVREL 4
#define GASPIN 12
#define BUZZPIN 10

#define CSPIN 14
#define SCKPIN 23
#define MISOPIN 21
#define MOSIPIN 15


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