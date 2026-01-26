#include <WiFi.h>
#include <ThingSpeak.h>

/***************************************************
   ESP32 + MQ-2 GAS SENSOR CONNECTION

   MQ-2:
   VCC -> 5V
   GND -> GND
   AO  -> GPIO 34

****************************************************/

// WiFi Credentials
const char* ssid = "WIFI ID";
const char* password = "PASSWORD";

// ThingSpeak Credentials
unsigned long channelID = ID;          // Your Channel ID
const char* apiKey = "WRITE API KEY";   // Your Write API Key

WiFiClient client;

// MQ-2 Sensor Pin
#define MQ2_PIN 34   // Analog pin

void setup() {
  Serial.begin(115200);
  pinMode(MQ2_PIN, INPUT);

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nWiFi Connected!");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  Serial.println("MQ-2 Sensor Ready (Warm-up required)");
}

void loop() {
  // Read MQ-2 sensor value
  int gasValue = analogRead(MQ2_PIN);

  // Print value to Serial Monitor
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  // Send data to ThingSpeak
  ThingSpeak.setField(1, gasValue);

  int status = ThingSpeak.writeFields(channelID, apiKey);

  if (status == 200) {
    Serial.println("Data Sent to ThingSpeak!");
  } else {
    Serial.print("Failed to send data. Error Code: ");
    Serial.println(status);
  }

  delay(15000); // ThingSpeak minimum delay
}
