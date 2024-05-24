#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include "config.h"  // Archivo de configuración con credenciales de Adafruit IO

// Inicialización de un cliente WiFi para comunicación TCP
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_SERVERPORT, IO_USERNAME, IO_KEY);

// Setup a feed for publishing.
AdafruitIO_Feed *feed = io.feed("sensores");

void setup()
{
  // Inicialización del puerto serie
  Serial.begin(115200);
  
  // Conexión a la red WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  // Espera a que la conexión sea correcta
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  // Muestro la dirección IP asignada
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Inicio de la conexion MQTT a io.arduino.com 
  io.connect();
  // se llama a la funcion MensajeFeed cada vez que se recibe un nuevo mensaje de adafruit io  
  feed->onMessage(MensajeFeed);

  // espera a que se realice la conexion con la comunicacion MQTT
  while(io.mqttStatus() < AIO_CONNECTED) {
    Serial.print("-");
    delay(500);
  }

  // comprobacion que envia el ultimo valor del feed una vez se ha realizado la comunicacion MQTT
   feed->get();

  // we are connected
  Serial.println("conectado mqtt");
  Serial.println(io.statusText()); 
}

void loop()
{
  // Procesamiento de mensajes y mantiene al cliente conectado 
  io.run();
}

// Función de callback para manejar mensajes entrantes del feed
void MensajeFeed(AdafruitIO_Data *data) {
  Serial.print("Nuevo mensaje en el feed: ");
  Serial.println(data->value());
}
