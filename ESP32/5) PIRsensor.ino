/***************************************************
   ESP32 + PIR SENSOR CONNECTION

   PIR Sensor (HC-SR501):
   VCC  -> 5V
   OUT  -> GPIO 27
   GND  -> GND

   NOTE:
   - PIR needs ~30–60 seconds to stabilize
   - Output HIGH when motion detected
****************************************************/

#define PIR_PIN 27    // GPIO connected to PIR OUT

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  Serial.println("PIR Sensor Initializing...");
  delay(30000);  // PIR stabilization time
  Serial.println("PIR Ready");
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    Serial.println("🚶 Motion Detected!");
  } else {
    Serial.println("No Motion");
  }

  delay(1000);
}
