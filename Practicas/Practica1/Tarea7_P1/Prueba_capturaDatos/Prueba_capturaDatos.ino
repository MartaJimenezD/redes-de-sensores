#include <avr/pgmspace.h>
#include <Wire.h>
#include <Arduino_LSM9DS1.h>
#include <timer.h>
#include <timerManager.h>
#include "timer.h"


float vec_x_mag[5], vec_y_mag[5], vec_z_mag[5] = {};
float vec_x_acel[5], vec_y_acel[5], vec_z_acel[5] = {};
float vec_x_giro[5], vec_y_giro[5], vec_z_giro[5] = {};
float matriz_datos_Sensores[5][9];
int rows=5;
int cols=9;
float x_acel, y_acel, z_acel;
float x_mag, y_mag, z_mag;
float x_giro, y_giro, z_giro;
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
  while (!Serial);   
  // garantiza que hay algo al otro lado de la conexion USB
  Wire.begin();  // join i2c bus (address optional for writer)

  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  // los datos de los sensores se muestrean cada 200 ms
  timer.setInterval(200);
  timer.setCallback(SampleCallback);
  timer.start();
}

void loop() {
  if (flagTimer) {  //Interrupcion
    Serial.println(cont_timer);
    // captura de los valores del giroscopo
    if (IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(x_giro, y_giro, z_giro);
    }
    matriz_datos_Sensores[cont_timer][0] = x_giro;
    matriz_datos_Sensores[cont_timer][1] = y_giro;
    matriz_datos_Sensores[cont_timer][2] = z_giro;

    // captura de los valores del magnetometro
    if (IMU.magneticFieldAvailable()) {
      IMU.readMagneticField(x_mag, y_mag, z_mag);
    }
    matriz_datos_Sensores[cont_timer][3] = x_mag;
    matriz_datos_Sensores[cont_timer][4] = y_mag;
    matriz_datos_Sensores[cont_timer][5] = z_mag;

    // captura de los valores del acelerometro
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
    matriz_datos_Sensores[cont_timer][6] = degreesX;
    matriz_datos_Sensores[cont_timer][7] = degreesY;
    matriz_datos_Sensores[cont_timer][8] = degreesZ;

    //actualización del flag de la interrupcion
    cont_timer = cont_timer + 1;
    flagTimer = false;
  }

  if (cont_timer == 5) {
    Wire.beginTransmission(8);  // iniciar la transmision al dispositivo 8

    Wire.write((byte*)matriz_datos_Sensores, sizeof(float) * rows * cols);  // Envía la matriz como bytes
    // sends the given value
    Wire.endTransmission();  // stop transmitting
    
    cont_timer = 0;
  }
  timer.update();
}
