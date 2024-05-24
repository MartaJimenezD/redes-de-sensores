#include <ArduinoBLE.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214"; // UUID del servicio (identificador universal)
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214"; // UUID del campo característico

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("Inicialización BLE fallida");
    while (1);
  }

  BLE.setLocalName("Marta"); // se establece el nombre del dispositivo
  BLE.advertise(); // comienza el advertising
  Serial.println("Esperando una conexión BLE...");
}

void loop() {

}
