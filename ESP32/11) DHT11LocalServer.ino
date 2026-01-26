#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

/***************************************************
   ESP32 + DHT11 + LOCAL WEB SERVER

   DHT11:
   VCC  -> 3.3V / 5V
   DATA -> GPIO 4
   GND  -> GND

   Access Webpage:
   http://ESP32_IP_ADDRESS/
****************************************************/

// WiFi Credentials
const char* ssid = "WIFI_ID";
const char* password = "PASSWORD";

// DHT Setup
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Web Server on port 80
WebServer server(80);

void handleRoot() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  String html = "<html><head>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<title>ESP32 Sensor Data</title>";
  html += "</head><body>";
  html += "<h2>ESP32 Local Web Server</h2>";

  if (isnan(temp) || isnan(hum)) {
    html += "<p>Sensor Error</p>";
  } else {
    html += "<p><b>Temperature:</b> " + String(temp) + " °C</p>";
    html += "<p><b>Humidity:</b> " + String(hum) + " %</p>";
  }

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

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
