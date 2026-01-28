#include <WiFi.h>
#include <WebServer.h>

/***************************************************
   ESP32 + MQ-2 + LOCAL WEB SERVER

   MQ-2:
   VCC -> 5V
   GND -> GND
   AO  -> GPIO 34

   Access Webpage:
   http://ESP32_IP_ADDRESS/
****************************************************/

// WiFi Credentials
const char* ssid = "KALPESH01";
const char* password = "00000000";

// MQ-2 Pin
#define MQ2_PIN 34

// Web Server on port 80
WebServer server(80);

void handleRoot() {
  int gasValue = analogRead(MQ2_PIN);

  String html = "<html><head>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<title>ESP32 Gas Monitor</title>";
  html += "</head><body>";
  html += "<h2>ESP32 MQ-2 Gas Sensor</h2>";

  html += "<p><b>Gas Value:</b> " + String(gasValue) + "</p>";

  if (gasValue > 2000) {
    html += "<p style='color:red;'><b>Gas Detected!</b></p>";
  } else {
    html += "<p style='color:green;'><b>Gas Level Normal</b></p>";
  }

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(MQ2_PIN, INPUT);

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

  // Start server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}
