#include <timer.h>
#include <timerManager.h>

#include "timer.h"

// Create the timer instance
Timer timer;
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot

void ADCCallback() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.println(sensorValue*3.3/1023);
}

void setup()
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  
  // The timer will repeat every 10000 ms
  timer.setInterval(10000); 

  // The function to be called
  timer.setCallback(ADCCallback);

  // Start the timer
  timer.start();
}

void loop()
{
  //Update the timer
  timer.update();
}
