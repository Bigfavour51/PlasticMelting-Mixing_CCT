#ifndef MELTERLIB_H
#define MELTERLIB_H

#include <Arduino.h>
// #include <SoftwareSerial.h>
#include <MAX6675.h>
#include "UARTMaster.h"
#include <RTClib.h>
// #include <SPI.h>

// === Global Variables ===

#define FWREL 4
#define STPREL 12
#define REVREL 27
#define GASPIN 15
#define BUZZPIN 10

#define CSPIN 5
#define SCKPIN 18
#define MISOPIN 19
#define MOSIPIN 23

#define SCL 22
#define SDA 21


#define Relay_ON LOW
#define Relay_OFF HIGH


class plasticMelter {
public:
    plasticMelter(int csPin, int sckPin, int misoPin, int mosiPin, int rxPin, int txPin, int buzzpin, int fwrel,
                  int stprel, int revrel, int gaspin, int scl, int sda );

    ~plasticMelter();

    void begin();
    void setTemperature(float temperature);
    float getTemperature();
    void startMotor();
    void stopMotor();
    void reverseMotor();
    void gasValveOn();
    void gasValveOff();
    void buzzOn();
    void buzzOff();
    bool isMelting() ;
    bool isMotorRunning();
    int getTime();

    void TrigRelayON(int _dir);
    void TrigRelayOFF(int _dir);
    
    
private:
    MAX6675* thermocouple = nullptr;
    RTC_DS1307* rtc = nullptr;
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
    int scl;
    int sda;
    float targetTemperature;
    void updateTemperature();
    bool MotorRunning;
   
};



#endif 