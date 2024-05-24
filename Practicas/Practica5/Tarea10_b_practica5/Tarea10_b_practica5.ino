#include <SPI.h>
#include <WiFi.h>
#include <ArduinoHttpClient.h>

// Configuración de la red Wi-Fi
char ssid[] = "Marta";
char password[] = "Marta2001";

// Configuración del servidor y el recurso HTTP
const char server[] = "io.adafruit.com";
const int port = 80; // Puerto HTTP
const char path[] = "/api/v2/809847/feeds/sensores/data";

// API Key de Adafruit
const char apiKey[] = "aio_Uayg39AGbf1bUThi6CZDS7f4STGm";

// Datos que quieres enviar
const char postData[] = "{\"value\": 123}";

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, port);

void setup() {
  Serial.begin(9600);

  // Conexión a la red Wi-Fi
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a la red Wi-Fi");

  delay(1000);
}

void loop() {
  // Realizar la solicitud HTTP POST
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Enviando datos a Adafruit... ");
    if (client.post(path, postData, apiKey)) {
      int statusCode = client.responseStatusCode();
      Serial.print("Código de estado HTTP: ");
      Serial.println(statusCode);
      
      String response = client.responseBody();
      Serial.print("Respuesta del servidor: ");
      Serial.println(response);
    } else {
      Serial.println("Error al enviar los datos.");
    }

    client.stop();
  }

  delay(5000); // Esperar 5 segundos antes de enviar otro dato
}
