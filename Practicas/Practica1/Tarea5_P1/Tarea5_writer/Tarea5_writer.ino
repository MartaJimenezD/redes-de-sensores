#include <Wire.h>

void setup() {
  Serial.begin(9600); // abre el puerto serie 
  while (!Serial); // garantiza que hay algo al otro lado de la conexion USB
  Wire.begin(); // join i2c bus (address optional for writer)
}

void loop() {
  Serial.print("Enter 0 to turn off led, enter 1 to turn it on ");
  char ledVal[0]; // mantiene el valor escrito en el monitor serie
  readSerial(ledVal);
  Serial.println(ledVal);
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(ledVal);        // sends the given value
  Wire.endTransmission();    // stop transmitting
  delay(500);
}

int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}
