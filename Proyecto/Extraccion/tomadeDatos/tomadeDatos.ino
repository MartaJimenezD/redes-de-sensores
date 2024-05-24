#include <Arduino_LSM9DS1.h>
#include <timer.h>
#include <timerManager.h>
#include "timer.h"

float x_acel, y_acel, z_acel;
float x_mag, y_mag, z_mag;
float x_giro, y_giro, z_giro;
int degreesX = 0;
int degreesY = 0;
int degreesZ = 0;
bool flagTimer = false;
Timer timer;

void SampleCallback() {
  flagTimer = true;
}

void setup() {
  
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }
  // muestreo cada 2 ms (500 Hz)
  timer.setInterval(2);
  timer.setCallback(SampleCallback);
  timer.start();
}

void loop() {

  if (flagTimer) {  //Interrupcion

    if (IMU.gyroscopeAvailable()) { // unidades grados por segundo
      IMU.readGyroscope(x_giro, y_giro, z_giro);
    }

    if (IMU.magneticFieldAvailable()) { // unidades uTeslas
      IMU.readMagneticField(x_mag, y_mag, z_mag);
    }

    if (IMU.accelerationAvailable()) { // unidades G's
      IMU.readAcceleration(x_acel, y_acel, z_acel);
    }

    flagTimer = false;
  }

      Serial.print("S");
      Serial.print(" ");
      Serial.print(x_mag);
      Serial.print(" ");
      Serial.print(y_mag);
      Serial.print(" ");
      Serial.print(z_mag);
      Serial.print(" ");
      Serial.print(x_acel);
      Serial.print(" ");
      Serial.print(y_acel);
      Serial.print(" ");
      Serial.print(z_acel);
      Serial.print(" ");
      Serial.print(x_giro);
      Serial.print(" ");
      Serial.print(y_giro);
      Serial.print(" ");
      Serial.println(z_giro);

  timer.update();
}
