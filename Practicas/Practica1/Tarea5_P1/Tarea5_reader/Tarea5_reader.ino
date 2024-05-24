#include <Wire.h>

void setup() {
  Wire.begin(8);                // inicializacion de la libreria, placa de lectura dirección = 8 (identificacion del dispositivo por la placa de escritura)
  Wire.onReceive(receiveEvent); // function that executes whenever data is received from writer
}



void receiveEvent(int howMany) {
   char c = Wire.read(); // receive a character
   if(c == '0'){
     digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
   }
   if(c == '1'){
     digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
   }
}





void loop() {

}