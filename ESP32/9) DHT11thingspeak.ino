/***************************************************
   ESP32 + DHT11 SENSOR CONNECTION

   DHT11:
   VCC  -> 3.3V or 5V
   DATA -> GPIO 4
   GND  -> GND

   NOTE:
   - Use 10kΩ pull-up resistor between DATA & VCC
****************************************************/
#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>
// WiFi Credentials
const char* ssid = "WIFI ID";     
const char* password = "PASSWORD"; 
// ThingSpeak Credentials
unsigned long channelID = ID;   // Replace with your ThingSpeak Channel ID
const char* apiKey = "WRITE API KEY"; // Replace with your ThingSpeak Write API Key
WiFiClient client;
// DHT11 Sensor Setup
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  dht.begin();
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
}
void loop() {
  // Read temperature & humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Print readings to Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("°C  Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  // Send data to ThingSpeak
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  int status = ThingSpeak.writeFields(channelID, apiKey);
  if (status == 200) {
    Serial.println("Data Sent to ThingSpeak!");
  } else {
    Serial.print("Failed to send data. Error Code: ");
    Serial.println(status);
  }
  delay(15000); // ThingSpeak allows updates every 15 seconds
}
