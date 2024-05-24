#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "time.h"

// Reemplaza con tu SSID y contraseña
const char* ssid = "Marta";
const char* password = "Marta2001";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

AsyncWebServer server(80);

void setup(){
 Serial.begin(115200);

 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
 }
 Serial.println(WiFi.localIP());

 configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
       Serial.println("Fallo al obtener la hora");
       return;
    }
    String html = "<html><body>";
    html += "<h1>Hora actual: " + String(timeinfo.tm_hour) + ":" + String(timeinfo.tm_min) + ":" + String(timeinfo.tm_sec) + "</h1>";
    // colocar un elemento "boton" al HTML para resetear la hora actual 
    html += "<button onclick=\"location.href='/reset'\">Resetear hora</button>";
    // etiquetas para asegurar la estructura promia de HTML
    html += "</body></html>";
    request->send(200, "text/html", html);
 });

 server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    // Aquí puedes resetear la hora
    Serial.println("Hora reseteada a 00:00:00");
    // Asegúrate de resetear la hora en tu RTC o en tu variable de tiempo
    request->send(200, "text/html", "<h1>Hora reseteada a 00:00:00<h1>");
 });

 server.begin();
}

void loop(){
}
