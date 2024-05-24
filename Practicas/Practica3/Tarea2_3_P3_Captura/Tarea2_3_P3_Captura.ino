#include <avr/pgmspace.h>
#include <Wire.h>
#include <Arduino_LSM9DS1.h>
#include <timer.h>
#include <timerManager.h>
#include "timer.h"


float vec_x_acel[5], vec_y_acel[5], vec_z_acel[5] = {};
float matriz_datos_Sensores[5][3];
int rows = 5;
int cols = 3;
float x_acel, y_acel, z_acel;
int degreesX = 0;
int degreesY = 0;
int degreesZ = 0;
int cont_timer = 0;
bool flagTimer = false;
Timer timer;

// interrupcion timer
void SampleCallback() {
  flagTimer = true;
}

void setup() {
  Serial.begin(9600);  // abre el puerto serie
  while (!Serial)
    ;
  // garantiza que hay algo al otro lado de la conexion USB
  Wire.begin();  // join i2c bus (address optional for writer)

  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }
  // los datos de los sensores se muestrean cada 200 ms
  timer.setInterval(200);
  timer.setCallback(SampleCallback);
  timer.start();
}

void loop() {
  if (flagTimer) {  //Interrupcion

    // captura de los valores del acelerometro
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(x_acel, y_acel, z_acel);
    }
    matriz_datos_Sensores[cont_timer][0] = x_acel;
    matriz_datos_Sensores[cont_timer][1] = y_acel;
    matriz_datos_Sensores[cont_timer][2] = z_acel;

    //actualización del flag de la interrupcion
    cont_timer = cont_timer + 1;
    flagTimer = false;
  }

  if (cont_timer == 5) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        Serial.print(matriz_datos_Sensores[i][j], 3);  // Imprime cada elemento de la matriz con 3 decimales
        Serial.print(";");
      }
      Serial.println();
    }

    cont_timer = 0;
  }

  timer.update();
}
