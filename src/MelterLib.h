#ifndef MELTERLIB_H
#define MELTERLIB_H

#include <Arduino.h>
#include <Adafruit_MAX31865.h>
#include "UARTMaster.h"
#include <Wire.h>


// === Global Variables ===

#define FWREL 4
#define STPREL 12
#define REVREL 27
#define GASPIN 12
#define BUZZPIN 13
#define ExtractorPIN 14

// #define buzzpin 13
// #define gaspin 12
// #define exppin 14

#define CSPIN 33
#define SCKPIN 34
#define MISOPIN 35
#define MOSIPIN 36

#define SCL 22
#define SDA 21


#define Relay_ON LOW
#define Relay_OFF HIGH

#define targetTemperature 100.0

class plasticMelter {
public:
    plasticMelter(int csPin, int sckPin, int misoPin, int mosiPin, int rxPin, int txPin, int buzzpin, int fwrel,
                  int stprel, int revrel, int gaspin, int scl, int sda );

    ~plasticMelter();

    void begin();
    float getTemperature();
    void startMotor();
    void stopMotor();
    void reverseMotor();
    void gasValveOn();
    void gasValveOff();
    void buzzOn();
    void buzzOff();
    bool isMelting() ;
    bool targetTemperatureReached();
    bool isMotorRunning();
    void extractorOn();
    void extractorOff();
    void isOperationComplete();
    

    void TrigRelayON(int _dir);
    void TrigRelayOFF(int _dir);
    
    
private:
   Adafruit_MAX31865* thermocouple = nullptr;
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
    float currentTemperature;
    bool MotorRunning;

   
};

float  getTemperature();
extern int minutevalue;
extern int hourvalue; 
extern float curTemperature ;
bool targetTemperatureReached();
extern float temperature;
extern bool heaterstatus;



#define MAX31865_CS   5   // Chip Select
#define MAX31865_MOSI 23
#define MAX31865_MISO 19
#define MAX31865_SCK  18


#endif 