/***************************************************
   ESP32 + DHT11 SENSOR CONNECTION

   DHT11:
   VCC  -> 3.3V or 5V
   DATA -> GPIO 4
   GND  -> GND

   NOTE:
   - Use 10kΩ pull-up resistor between DATA & VCC
****************************************************/

#include "DHT.h"

#define DHTPIN 4      // GPIO connected to DHT11 DATA
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("DHT11 Sensor Initialized");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C   ");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000);
}
