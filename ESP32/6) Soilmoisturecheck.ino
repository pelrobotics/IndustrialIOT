/***************************************************
   ESP32 + SOIL MOISTURE SENSOR CONNECTION

   Soil Moisture Sensor Module:
   VCC  -> 3.3V or 5V
   GND  -> GND
   AO   -> GPIO 35   (Analog Output)
   DO   -> Not used

   NOTE:
   - GPIO 35 is ADC input only
   - Higher value = Dry soil
****************************************************/

#define SOIL_PIN 35   // ESP32 analog input pin

void setup() {
  Serial.begin(9600);
  pinMode(SOIL_PIN, INPUT);
  Serial.println("Soil Moisture Sensor Ready");
}

void loop() {
  int soilValue = analogRead(SOIL_PIN);

  Serial.print("Soil Moisture Value: ");
  Serial.println(soilValue);

  if (soilValue > 2500) {
    Serial.println("🌵 Soil is DRY");
  } else {
    Serial.println("💧 Soil is WET");
  }

  delay(1000);
}
