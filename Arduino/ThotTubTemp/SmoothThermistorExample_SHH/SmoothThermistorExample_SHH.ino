// include the SmoothThermistor library
#include <SmoothThermistor.h>
#include <Tuyav.h>

// create a SmoothThermistor instance, reading from analog pin 0 with a 4.7k pullup resistor

SmoothThermistor smoothThermistor(A0, 
                                  ADC_SIZE_10_BIT,
                                  4700,
                                  0.002108508173,
                                  0.000079792,
                                  0.0000006535076315,
                                  10,
                                  1);
int tubtempInt = 1023;
// if you have a different type of thermistor, you can override the default values
// example:
// SmoothThermistor smoothThermistor(A0,              // the analog pin to read from
void setup() {
  Seria.begin(9600);
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
  Serial.println(tubtemp);
  if(tubtemp > 0 && tubtemp < 70){
    tubtempInt = map(tubtemp, 0, 70, 0, 1022);
  }
  else{
    tubtempInt = 1023;
  }
  Serial.println(tubtempInt);
  //tuyav.SendUserValue(116,tubtemp);

  // pause for a second
  delay(1000);
}
