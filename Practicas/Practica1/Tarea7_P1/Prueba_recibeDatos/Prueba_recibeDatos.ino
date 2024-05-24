#include <timer.h>
#include <timerManager.h>

#include <Wire.h>


float matriz_datos_Sensores[5][9];
int rows = 5;
int cols = 9;
Timer timer;

void SampleCallback() {
  digitalWrite(LED_BUILTIN,LOW);
  timer.stop();
}


void receiveEvent(int howMany) {
  Serial.println("recibe"); 
  while (Wire.available() < sizeof(float) * rows * cols) {
    // Espera hasta que todos los bytes se reciban
  }
  digitalWrite(LED_BUILTIN,HIGH);
  timer.start();
  Wire.readBytes((byte*)matriz_datos_Sensores, sizeof(float) * rows * cols);
  Serial.println("magnetometro (uT)                        acelerometro                             giroscopo                            ");
  Serial.println("X             Y              Z           X             Y              Z           X             Y              Z       ");
  
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Serial.print(matriz_datos_Sensores[i][j], 3);  // Imprime cada elemento de la matriz con 3 decimales
      Serial.print('\t');
    }
    Serial.println();
  }
}



void setup() {
  Wire.begin(8);                 // inicializacion de la libreria, placa de lectura dirección = 8 (identificacion del dispositivo por la placa de escritura)
  Wire.onReceive(receiveEvent);  // function that executes whenever data is received from writer
  Serial.begin(9600);
  timer.setInterval(1000);
  timer.setCallback(SampleCallback);
}

void loop() {
  timer.update();
}
