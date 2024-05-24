#include <Arduino_LSM9DS1.h>
#include <timer.h>
#include <timerManager.h>
#include "timer.h"

float vec_x_mag[5], vec_y_mag[5], vec_z_mag[5] = {};
float vec_x_acel[5], vec_y_acel[5], vec_z_acel[5] = {};
float vec_x_giro[5], vec_y_giro[5], vec_z_giro[5] = {};
float x_acel, y_acel, z_acel;
float x_mag, y_mag, z_mag;
float x_giro, y_giro, z_giro;
int degreesX = 0;
int degreesY = 0;
int degreesZ = 0;
int cont_timer = 0;
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

  timer.setInterval(1000);
  timer.setCallback(SampleCallback);
  timer.start();
}

void loop() {

  if (flagTimer) {  //Interrupcion

    if (IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(x_giro, y_giro, z_giro);
    }
    vec_x_giro[cont_timer] = x_giro;
    vec_y_giro[cont_timer] = y_giro;
    vec_z_giro[cont_timer] = z_giro;



    if (IMU.magneticFieldAvailable()) {
      IMU.readMagneticField(x_mag, y_mag, z_mag);
    }
    vec_x_mag[cont_timer] = x_mag;
    vec_y_mag[cont_timer] = y_mag;
    vec_z_mag[cont_timer] = z_mag;


    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(x_acel, y_acel, z_acel);
    }
    if (x_acel > 0.1) {
      x_acel = 100 * x_acel;
      degreesX = map(x_acel, 0, 97, 0, 90);
    }
    if (x_acel < -0.1) {
      x_acel = 100 * x_acel;
      degreesX = map(x_acel, 0, -100, 0, 90);
    }
    if (y_acel > 0.1) {
      y_acel = 100 * y_acel;
      degreesY = map(y_acel, 0, 97, 0, 90);
    }
    if (y_acel < -0.1) {
      y_acel = 100 * y_acel;
      degreesY = map(y_acel, 0, -100, 0, 90);
    }
    if (z_acel > 0.1) {
      z_acel = 100 * z_acel;
      degreesZ = map(z_acel, 0, 97, 0, 90);
    }
    if (z_acel < -0.1) {
      z_acel = 100 * z_acel;
      degreesZ = map(z_acel, 0, -100, 0, 90);
    }
    vec_x_acel[cont_timer] = degreesX;
    vec_y_acel[cont_timer] = degreesY;
    vec_z_acel[cont_timer] = degreesZ;

    cont_timer = cont_timer + 1;
    flagTimer = false;
  }


  if (cont_timer == 5) {
    Serial.println("magnetometro (uT)                        acelerometro                                                        giroscopo ");
    for (int i = 0; i < 5; i++) {
      Serial.print("x: ");
      Serial.print(vec_x_mag[i]);
      Serial.print(" , y: ");
      Serial.print(vec_y_mag[i]);
      Serial.print(" , z: ");
      Serial.print(vec_z_mag[i]);

      Serial.print("        degreesX: ");
      Serial.print(vec_x_acel[i]);
      Serial.print(" , degreesY: ");
      Serial.print(vec_y_acel[i]);
      Serial.print(" , degreesZ: ");
      Serial.print(vec_z_acel[i]);

      Serial.print("        x: ");
      Serial.print(vec_x_giro[i]);
      Serial.print(" , y: ");
      Serial.print(vec_y_giro[i]);
      Serial.print(" , z: ");
      Serial.println(vec_z_giro[i]);
    }
    cont_timer = 0;
  }

  timer.update();
}
