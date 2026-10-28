#include <ArduinoWebsockets.h>
#include <WiFi.h>

const char* ssid = "WiFiDIlan";
const char* password = "BelaHermosa";
const char* websockets_server = "ws://192.168.10.10:3002";

using namespace websockets;
WebsocketsClient client;

void onMessageCallback(WebsocketsMessage message) {
  Serial.print("Mensaje recibido: ");
  Serial.println(message.data());
  if (message.data() == "Hola") {
    digitalWrite(2, HIGH);
  }
  if (message.data() == "Adios") {
    digitalWrite(2, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("WiFi conectado");

  client.onMessage(onMessageCallback); // Configura la función que recibe mensajes
  client.connect(websockets_server);   // Se conecta al servidor
  client.send("Hola desde ESP32");     // Envía un mensaje
}

void loop() {
  if (!client.available()) {
    Serial.println("Reconectando...");
    client.connect(websockets_server);
    delay(2000);
  }
  client.poll(); // Mantiene viva la conexión y procesa mensajes entrantes
  
}