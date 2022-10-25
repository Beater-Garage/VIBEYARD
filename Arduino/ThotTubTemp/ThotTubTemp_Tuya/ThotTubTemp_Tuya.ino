/*
    --- TUYAV example program ---
    v1.0 by BN&PSI @ Velleman NV - feb 2020
    works with VMA354 Tuya IoT interface

    This example program shows you how to interface with the Tuya IoT interface board
    for the full manual, please visit https://www.vellemanformakers.com/product/VMA354

    Connections:
    VMA354    Arduino UNO           Arduino MEGA          Arduino Nano Every
    VCC       5V                    5V                    5V
    GND       GND                   GND                   GND
    TX        PIN2  (SWserial RX)   PIN19 (Serial1 RX1)   PIN RX0 (Serial1 RX0)
    RX        PIN3  (SWserial TX)   PIN18 (Serial1 TX1)   PIN TX1 (Serial1 TX1)
*/


//libraries
#include <Tuyav.h>
#include "global.h"
#include <SmoothThermistor.h>

//selection of Serial port
Tuyav tuyav(&Serial);

//Initialize Time for updating Arbitrary Values
unsigned long currentTime = 0;
unsigned long previousTime = 0;
int updateDelay = 5000;    //3 seconds by default. Min 1 second or you will overflow the serial communication!
// Initiate a thermistor with following properties:
SmoothThermistor smoothThermistor(A0,              // the analog pin to read from
                                  ADC_SIZE_10_BIT, // the ADC size
                                  2830,           // the nominal resistance
                                  4700,           // the series resistance
                                  4112,            // the beta coefficient of the thermistor
                                  25,              // the temperature for nominal resistance
                                  10);             // the number of samples to take for each measurement
float TempMeasurement = smoothThermistor.temperature();

void setup()
{
  //start serial for debugging
  Serial.begin(9600);
  Serial.println("Tuya Demo program");

  //define the TUYA pins
  // There are 3 digital inputs, 3 analog inputs, 5 digital output and 3 analog outputs available
  // If you do not use a pin, set the pin as PIN_UNUSED
  tuyav.setAnalogInputs(A0, PIN_UNUSED, PIN_UNUSED);                  //Set AnalogInputs

  //init the chip
  tuyav.initialize();
}

void loop()
{
  //Should be called continuously
  tuyav.tuyaUpdate();

  //check time
  currentTime = millis();

  //timer: run the code below every time the updateDelay has passed
  if (currentTime - previousTime > updateDelay)
  {
    
    Serial.print(F("Temperature = "));
    Serial.println(String(TempMeasurement));
    //set arbitrary values (9 are available - read only in the app)
    tuyav.setUserValue(AV1, "Temperature");
    tuyav.setAV2(String(TempMeasurement));
    tuyav.setAV3(F("V1.0"));
    String AV4msg = "Last update time:";
    tuyav.setUserValue(AV4, AV4msg);
    tuyav.setUserValue(AV5, String(currentTime - previousTime));
    tuyav.setAV6(F("ms ago"));
    tuyav.setUserValue(AV7, "Time since boot:");
    tuyav.setAV8(String(currentTime));
    tuyav.setAV9(F("ms"));
    previousTime = millis();   //now that everything has been done, the previous time is the current time (and not the var currentTime, because time has passed during this block of code)
  }
}
