/***************************************************
   ESP32 + MQ-2 GAS SENSOR CONNECTION

   MQ-2 Sensor Module:
   VCC  -> 5V
   GND  -> GND
   AO   -> GPIO 34   (Analog Output)
   DO   -> Not used

   NOTE:
   - GPIO 34 is ADC input only
   - MQ-2 needs 5–10 minutes warm-up
****************************************************/

#define MQ2_PIN 34   // ESP32 analog input pin

void setup() {
  Serial.begin(9600);
  pinMode(MQ2_PIN, INPUT);
  Serial.println("MQ-2 Gas Sensor Initializing...");
}

void loop() {
  int gasValue = analogRead(MQ2_PIN);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // Simple threshold check
  if (gasValue > 2000) {
    Serial.println("⚠️ GAS DETECTED!");
  } else {
    Serial.println("Gas Level Normal");
  }

  delay(1000);
}
