#include <Arduino.h>

// portTickType = tipo de datos utilizado para representar tiempo 
const portTickType tiempo1 = 200 / portTICK_RATE_MS; // constante que define la duracion de un tick en milisegundos 
const portTickType tiempo2 = 1000 / portTICK_RATE_MS;
#define LED_BUILTIN 33 

void setup() {
  Serial.begin(112500); 
  delay (1000); 

  xTaskCreate (tarea1, "Tarea 1 parpadeo LED", 10000, NULL, 1, NULL); // parametro que se pasa a la funcion, prioridad, identificador de la tarea creada 
  xTaskCreate (tarea2, "Tarea 1 HOLA MUNDO", 10000, NULL, 1, NULL);

}

void tarea1 (void * parameter){
  while (1){
    Serial.println("LED ON"); 
    vTaskDelay (tiempo1); 
    Serial.println("LED OFF"); 
    vTaskDelay (tiempo1); 
  }
  vTaskDelete( NULL );
}

void tarea2 (void * parameter){

  while (1){
    Serial.println("Hola Mundo"); 
    vTaskDelay (tiempo2); // ejecuta esta tarea cada 1000 milisegundos 
  }
  vTaskDelete( NULL );
}

void loop (){
  // las tareas se ejecutan en paralelo 
}








