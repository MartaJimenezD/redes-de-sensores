#include <WiFi.h>
#include <WiFiClient.h>
#include "time.h"

const char* ssid = "Marta";
const char* password = "Marta2001";
const char* host = "172.20.10.3";  // Puedes usar la dirección IP o el nombre de dominio

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;  //Zona horario UTC+1
const int daylightOffset_sec = 3600;
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
  Serial.println(" CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  
}

void loop() {

  if (!client.connect(host, 4096)) {
    Serial.println("Connection failed");
    delay(5000);
    return;
  }

  if (client.connect(host, 4096)) {
    Serial.println("Connected to server");

    // Enviar datos al servidor
    printLocalTime();
    delay(1000);
  } else {
    Serial.println("Connection failed");
    delay(5000);
    return;
  }

}
