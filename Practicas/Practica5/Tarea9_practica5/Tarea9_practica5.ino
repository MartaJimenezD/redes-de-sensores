#include <ArduinoJson.h>
#include <WiFi.h>
#include <ESP32_FTPClient.h>

const char* ssid = "Marta";
const char* password = "Marta2001";

char ftp_server[] = "155.210.150.77";
char ftp_user[] = "rsense";
char ftp_pass[] = "rsense";
char ftp_directory[] = "/rsense/809847";

// inicializacion FTP Client
ESP32_FTPClient ftp(ftp_server, ftp_user, ftp_pass, 5000, 2);

const unsigned long interval = 10000;  // Intervalo de tiempo entre cada lectura en milisegundos (10 segundos)
unsigned long previousMillis = 0;

void setup() {
  // inicializacion del puerto serie
  Serial.begin(9600);

  // Conexión a la red WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED TO WIFI");
}

void loop() {
  unsigned long currentMillis = millis();
  // comprobar la conexion al servidor FTP
  if (!ftp.isConnected()) {
    ftp.OpenConnection();
  }
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    guardar_subir_JSON();
  }
}

void guardar_subir_JSON() {
  // generacion del archivo JSON
  StaticJsonDocument<200> doc;  // documento JSON

  doc["bt"] = millis() / 1000;  // Marca de tiempo actual en segundos
  doc["n"] = "temperatua";
  doc["u"] = "ºC";
  doc["v"] = random(200, 300) / 10.0;  // generacion de los valores de temperatura

  String output;
  serializeJson(doc, output);
  Serial.println("Generacion JSON correcta");
  Serial.println(output);


  // envio del archivo JSON
  Serial.println("Conectando al servidor FTP...");

  // Si hay conexión al servidor FTP, se envian los ficheros json
  if (ftp.isConnected()) {
    Serial.println("Conectado al servidor FTP");
    //nombre del archivo 809847XX.json y le asigna una base de tiempos
    char fileName[32];
    sprintf(fileName, "809847_%lu.json", millis() / 1000);  // %lu para generar numeros de archivo distintos
    Serial.println(fileName);
    ftp.InitFile("Type A");  // Transferencia de archivo ASCII
    ftp.ChangeWorkDir(ftp_directory);  // Cambio al directorio deseado /rsense/809847
    ftp.NewFile(fileName);             // creo el archivo
    char json_char[output.length() + 1];
    output.toCharArray(json_char, output.length() + 1);  // Conversion json_char en array para poder escribir(formato deseado) 
    ftp.Write(json_char);  // Escribir en el archivo
    ftp.CloseFile();
    ftp.CloseConnection();

  } else {
    Serial.println("Error al conectar al servidor FTP");
  }
}
