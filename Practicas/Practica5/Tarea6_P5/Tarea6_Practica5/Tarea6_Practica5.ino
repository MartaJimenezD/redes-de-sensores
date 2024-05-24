#include <WiFi.h>
#include <WiFiClient.h>
#include "time.h"

const char* ssid = "Marta";
const char* password = "Marta2001";
const char* host = "172.20.10.9";  // Pc: "172.20.10.9"     movil :"172.20.10.3";
const int puerto= 4096;
bool EnviarDatos = false;
String dato;
WiFiClient client;



void setup() {
  Serial.begin(9600);

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED to WIFI");


  if (client.connect(host, puerto)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("Connection failed");
  }
}




void loop() {

  if (!client.connected()) {
    Serial.println("Connection lost, reconnecting...");

    // Intentar reconectarse al servidor
    if (client.connect(host, puerto)) {
      Serial.println("Reconnected to server");
      // Realizar acciones adicionales después de la reconexión exitosa
    } else {
      Serial.println("Reconnection failed");
      delay(500);
    }
  }
  

  client.print(random(1,100));
  client.print(", ");
  client.print(random(1,100));
  client.print(", ");
  client.println(random(1,100));
  delay(1000);
}
