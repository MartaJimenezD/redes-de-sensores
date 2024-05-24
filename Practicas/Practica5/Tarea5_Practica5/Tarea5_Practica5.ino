#include <WiFi.h>
#include <WiFiClient.h>
#include "time.h"

const char* ssid = "Marta";
const char* password = "Marta2001";
const char* host = "172.20.10.3";  // Puedes usar la dirección IP o el nombre de dominio
const int puerto= 4096;
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;  //Zona horario UTC+1
const int daylightOffset_sec = 3600;
bool EnviarDatos = false;
String dato;
WiFiClient client;


void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  client.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


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

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  if (client.connect(host, puerto)) {
    Serial.println("Connected to server");
    // Realizar acciones adicionales después de la conexión exitosa
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
    }
  }

  if (client.available()) {
    Serial.println("Message from server:");
    dato = client.readStringUntil('\n');
    Serial.println(dato);
    if (dato == "start")
      EnviarDatos = true;
    if (dato == "stop")
      EnviarDatos = false;
  }

  // Enviar datos al servidor
  if (EnviarDatos) {
    printLocalTime();
  }
  delay(1000);
}
