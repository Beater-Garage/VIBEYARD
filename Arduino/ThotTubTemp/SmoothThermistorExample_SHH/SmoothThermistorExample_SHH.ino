// include the SmoothThermistor library
#include <SmoothThermistor.h>
//#include <Tuyav.h>

//selection of Serial port
/*#if defined(ARDUINO_AVR_UNO)    //Arduino UNO board: use SoftwareSerial with pins you select, see https://www.arduino.cc/en/Reference/softwareSerial
SoftwareSerial mySWserial(2,3); //RX,TX (2 and 3 are recommended)
Tuyav tuyav(&mySWserial);         
#else                           //Arduino Mega board: User can choose HardwareSerial: Serial1/Serial2/Serial3
  Tuyav tuyav(&Serial1);        //Serial1 is pin 18/19 on a Arduino Mega or pin TX1/RX0 on a Arduino Nano Every
#endif
*/
// create a SmoothThermistor instance, reading from analog pin 0 with a 4.7k pullup resistor
SmoothThermistor smoothThermistor(A0,                   // the analog pin to read from
                                ADC_SIZE_10_BIT,     // the ADC size
                                4700,               // the series resistance
                                0.001467817056,        // the A coefficient of the thermistor
                                0.0002309070221,           // the B coefficient of the thermistor
                                0.0000001014624924,    // the C coefficient of the thermistor
                                10,                  // the number of samples to take for each measurement
                                false);          // TRUE to make output in fahrenheit
int tubtempInt = 1023;
// if you have a different type of thermistor, you can override the default values
// example
// SmoothThermistor smoothThermistor(A0,              // the analog pin to read from
void setup() {
  Serial.begin(9600);
  smoothThermistor.useAREF(false);
}

//temp in degrees (float)
//Range 0C-70C
//if temp >0 && <70, map 0-1022
//else output = 1023


void loop() {

  // print the temperature
  int tubtemp = smoothThermistor.temperature();
  Serial.print("Temperature = ");
  Serial.println(smoothThermistor.temperature());
  Serial.println(analogRead(A0));
  if(tubtemp > 0 && tubtemp < 70){
    tubtempInt = map(tubtemp, 0, 70, 1, 1023);
  }
  else{
    tubtempInt = 0;
  }
  Serial.println(tubtempInt);
  //tuyav.sendUserValue(116,tubtempInt);

  // pause for a second
  delay(1000);
}
