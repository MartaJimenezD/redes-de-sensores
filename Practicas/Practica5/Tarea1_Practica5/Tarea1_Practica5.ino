#include <ESPping.h>
#include <ping32.h>
#include <WiFi.h>

const char* ssid = "Marta";
const char* password = "Marta2001";




void setup() {

  Serial.begin(9600);
  Serial.println("Procedo a hacer el begin");
  // Conexión a WiFi
  WiFi.begin(ssid, password);
  Serial.println("He hecho el begin");

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a la red WiFi");

  // Una vez conectado, imprime la dirección IP
  Serial.print("Direccion IP asignada: ");
  Serial.println(WiFi.localIP());

  // Realizar ping a Google
  Serial.println("Haciendo ping a google.com (8.8.8.8)...");
  if (Ping.ping("www.google.com")) {
    Serial.println("Ping exitoso!");
  } else {
    Serial.println("Ping fallido.");
  }
}





void loop() {
  // put your main code here, to run repeatedly:
}
