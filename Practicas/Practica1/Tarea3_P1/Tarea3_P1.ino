#include <timer.h>
#include <timerManager.h>

#include "timer.h"

// Create the timer instance
Timer timer;
int analogInPin = A0;  // Analog input pin that the potentiometer is attached to (10 bits)
int PWMpin = 2;
int sensorValue = 0;        // value read from the pot

void ADCCallback() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // analogRead values go from 0 to 1023 (10 bits), analogWrite values from 0 to 255 (8bits)
  analogWrite(PWMpin, sensorValue / 4); // duty de 0 a 255

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.println(sensorValue*3.3/1023); //10 bits 1023
}

void setup()
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  pinMode(PWMpin, OUTPUT);  // sets the pin as output
  
  // The timer will repeat every 500 ms
  timer.setInterval(1000); 

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