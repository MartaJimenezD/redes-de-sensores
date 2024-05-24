#include <WiFi.h>
#include <ArduinoJson.h>

const unsigned long interval = 10000; // Intervalo de tiempo entre cada lectura en milisegundos (10 segundos)
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    float temperature = obtenerTemperatura();

    guardarJSON(temperature);
  }
}

float obtenerTemperatura() {
  // Generación de temperatura aleatoria entre 20°C y 30°C
  return random(2000, 3000) / 100.0;
}

void guardarJSON(float temperatura) {
  DynamicJsonDocument doc(256); // Tamaño del documento JSON

  doc["bt"] = time(nullptr); // Marca de tiempo actual
  JsonArray entries = doc.createNestedArray("e");
  JsonObject entry = entries.createNestedObject();
  entry["n"] = "temperature";
  entry["u"] = "Cel";
  entry["v"] = temperatura;

  String output;
  serializeJson(doc, output);

  // Guardar el JSON en un archivo (en este ejemplo, se envía por Serial)
  Serial.println(output);
}
