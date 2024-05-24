#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Configuración de la red Wi-Fi
char ssid[] = "Marta";
char password[] = "Marta2001";

// Configuración del servidor y el recurso MQTT
const char server[] = "io.adafruit.com";
const int port = 1883; // PUERTO MQTT
const char user[] = "809847";
// API Key de Adafruit
const char key[] = "pon aqui la IO KEY"; 
const char nombre_feed[] = "sensores";

WiFiClient wifiClient;
Adafruit_MQTT_Client mqttClient(&wifiClient, server, port, user, key);

Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqttClient, "809847/feeds/sensores");

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  mqttClient.connect();
}

void loop() {
  // Simplemente para este ejemplo, enviamos un valor constante.
  // Puedes cambiar esto para enviar cualquier dato que desees.
  // Por ejemplo, podrías leer un sensor y enviar sus datos.

  if (mqttClient.connected()) {
    Serial.println("Sending data to Adafruit...");
    feed.publish("8");
    Serial.println("dato enviado al feed");
  } else 
    Serial.println("no conectado a MQTT");
    mqttClient.disconnect();
    delay(5000);
    mqttClient.connect();
    

  delay(5000); // Espera 5 segundos antes de enviar otro dato
}
