/***************************************************
   ESP32 PIN CONNECTION DIAGRAM

   LED:
   LED +  -> GPIO 2  (via 220Ω resistor)
   LED -  -> GND

   PUSH BUTTONS:
   ON Button:
     One leg -> GPIO 18
     Other   -> GND

   OFF Button:
     One leg -> GPIO 19
     Other   -> GND

   NOTE:
   - Buttons use INPUT_PULLUP
   - Button pressed = LOW
****************************************************/

#define LED_PIN     2     // GPIO for LED
#define ON_BUTTON   18    // GPIO for ON button
#define OFF_BUTTON  19    // GPIO for OFF button

void setup() {
  pinMode(LED_PIN, OUTPUT);

  pinMode(ON_BUTTON, INPUT_PULLUP);
  pinMode(OFF_BUTTON, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);   // LED OFF initially
}

void loop() {

  // If ON button is pressed
  if (digitalRead(ON_BUTTON) == LOW) {
    digitalWrite(LED_PIN, HIGH);   // Turn LED ON
    delay(200);                    // Debounce delay
  }

  // If OFF button is pressed
  if (digitalRead(OFF_BUTTON) == LOW) {
    digitalWrite(LED_PIN, LOW);    // Turn LED OFF
    delay(200);                    // Debounce delay
  }
}
