#include <timer.h>
#include <timerManager.h>
#include "timer.h"

Timer timer;
int analogInPin = A0;  // Analog input pin that the potentiometer is attached to (10 bits)
int PWMpin = 2;
int sensorValue = 0;        // value read from the pot
String readString;

void ADCCallback() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  
  // print the results to the Serial Monitor:
  Serial.print("ADC = ");
  Serial.println(sensorValue*3.3/1023); //10 bits 1023
}

void setup() {
 // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  pinMode(PWMpin, OUTPUT);  // sets the pin as output

  // The function to be called
  timer.setCallback(ADCCallback);

}

void loop() {

  while (Serial.available()) {
    delay(2);  //delay to allow byte to arrive in input buffer
    readString = Serial.readStringUntil('\n');
  }

  if (readString.equals("ADC")) {
    sensorValue = analogRead(analogInPin);
    Serial.print("ADC = ");
    Serial.println(sensorValue*3.3/1023); // 0 a 3.3
    readString = "";
  } 

  if (readString.startsWith("ADC(")) {
    timer.stop();
    char numADC = readString[4];
    int xADC = String(numADC).toInt();
    if(xADC > 0){
      timer.setInterval(xADC * 1000);
      timer.start();
    }
    readString = "";
  } 
  
  if (readString.startsWith("PWM(")) {
    timer.stop();
    char numPWM = readString[4];
    int dutyPWM = String(numPWM).toInt();
    analogWrite(PWMpin, dutyPWM*255/9 ); //Duty de 0 a 255
    readString = "";
  }   
  
  timer.update();


}