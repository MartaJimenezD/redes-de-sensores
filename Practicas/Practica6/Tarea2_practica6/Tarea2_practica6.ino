#include <Arduino.h>

// portTickType = tipo de datos utilizado para representar tiempo 
const portTickType tiempo1 = 100 / portTICK_RATE_MS; // constante que define la duracion de un tick en milisegundos 
const portTickType tiempo2 = 1000 / portTICK_RATE_MS;
const portTickType tiempo3 = 200 / portTICK_RATE_MS;

float vec_x_acel[10], vec_y_acel[10], vec_z_acel[10] = {};

void setup() {
  Serial.begin(112500); 
  delay (1000); 

  xTaskCreate (tarea1, "Tarea 1 muestrear aceleracion", 10000, NULL, 2, NULL); // parametro que se pasa a la funcion, prioridad, identificador de la tarea creada 
  xTaskCreate (tarea2, "Tarea 2 mandar datos", 10000, NULL, 1, NULL);
  xTaskCreate (tarea3, "Tarea 3 parpadeo LED", 10000, NULL, 0, NULL);

}

// muestrea la aceleracion cada 100ms 
void tarea1 (void * parameter){
  while (1){
    for (int i = 0; i < 10; i++){
      vec_x_acel[i] = random(1,100); 
      vec_y_acel[i] = random(1,100); 
      vec_z_acel[i] = random(1,100); 
      vTaskDelay (tiempo1); 

    }
    
  }

}

void tarea2 (void * parameter){

  while (1){
    for (int i = 0; i < 10; i++) {
      Serial.print("x: ");
      Serial.print(vec_x_acel[i]);
      Serial.print(" , y: ");
      Serial.print(vec_y_acel[i]);
      Serial.print(" , z: ");
      Serial.println(vec_z_acel[i]);
    }
    Serial.println();
    Serial.println();
    
    vTaskDelay (tiempo2); // ejecuta esta tarea cada 1000 milisegundos 
  }

}

void tarea3 (void * parameter){
  while (1){
    vTaskDelay (tiempo2);
    Serial.println("LED ON");
    vTaskDelay (tiempo3);
    Serial.println("LED OFF");
    
  }

}

void loop (){
  // las tareas se ejecutan en paralelo 
}


