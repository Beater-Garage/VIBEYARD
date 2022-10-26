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
#include "Tuyav.h"
#include "global.h"
#include <SmoothThermistor.h>

//selection of Serial port
#if defined(ARDUINO_AVR_UNO)    //Arduino UNO board: use SoftwareSerial with pins you select, see https://www.arduino.cc/en/Reference/softwareSerial
SoftwareSerial mySWserial(2,3); //RX,TX (2 and 3 are recommended)
Tuyav tuyav(&mySWserial);         
#else                           //Arduino Mega board: User can choose HardwareSerial: Serial1/Serial2/Serial3
  Tuyav tuyav(&Serial);        //Serial1 is pin 18/19 on a Arduino Mega
#endif

//Debug variable for any serial output
int debug = FALSE;
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

void setup()
{
  //start serial for debugging
  Serial.begin(9600);
  if(debug){
    Serial.println("Tuya Demo program");
  }

  //define the TUYA pins
  // There are 3 digital inputs, 3 analog inputs, 5 digital output and 3 analog outputs available
  // If you do not use a pin, set the pin as PIN_UNUSED
  //tuyav.setAnalogInputs(A0, PIN_UNUSED, PIN_UNUSED);                  //Set AnalogInputs

  //init the chip
  tuyav.initialize();
}

void loop()
{
  float TempMeasurement = smoothThermistor.temperature();
  //Should be called continuously
  tuyav.tuyaUpdate();

  //check time
  currentTime = millis();

  //timer: run the code below every time the updateDelay has passed
  if (currentTime - previousTime > updateDelay)
  {
    if(debug){
    Serial.print(F("Temperature = "));
    Serial.println(TempMeasurement);
    }
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
