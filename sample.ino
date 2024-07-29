#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "Sjie";
const char* password = "sjie2002";

// Create an instance of the server on port 80
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "Hello, world!");
  });

  server.on("/control", HTTP_POST, []() {
    String action = server.arg("action");
    // Perform actions based on the 'action' parameter
    server.send(200, "text/plain", "Action received: " + action);
  });

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}
