#include <WiFi.h>
#include <WebServer.h>

/***************************************************
   ESP32 + IR SENSOR + SMART PARKING

   IR Sensor:
   VCC -> 3.3V / 5V
   GND -> GND
   OUT -> GPIO 27

   Access Webpage:
   http://ESP32_IP_ADDRESS/
****************************************************/

// WiFi Credentials
const char* ssid = "SVERI";
const char* password = "";

// IR Sensor Pin
#define IR_PIN 27

// Web Server on port 80
WebServer server(80);

void handleRoot() {
  int irStatus = digitalRead(IR_PIN);

  String html = "<html><head>";
  html += "<meta http-equiv='refresh' content='3'>";
  html += "<title>Smart Parking</title>";
  html += "</head><body>";
  html += "<h2>ESP32 Smart Parking System</h2>";

  if (irStatus == LOW) {
    html += "<p style='color:red; font-size:20px;'><b>🚗 Parking Slot: OCCUPIED</b></p>";
  } else {
    html += "<p style='color:green; font-size:20px;'><b>🅿️ Parking Slot: AVAILABLE</b></p>";
  }

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Start web server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}
