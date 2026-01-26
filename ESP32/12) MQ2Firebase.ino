#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

/***************************************************
   ESP32 + MQ-2 + Firebase RTDB

   MQ-2:
   VCC -> 5V
   GND -> GND
   AO  -> GPIO 34
****************************************************/

// Wi-Fi Credentials
#define WIFI_SSID "WifiId"
#define WIFI_PASSWORD "Wifipass"

// Firebase Credentials
#define API_KEY "aoikey"
#define DATABASE_URL "databaseurl/"

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

// MQ-2 Pin
#define MQ2_PIN 34

void setup() {
  Serial.begin(115200);

  pinMode(MQ2_PIN, INPUT);

  // WiFi connect
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // Firebase config
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase SignUp OK");
    signupOK = true;
  } else {
    Serial.println("Firebase SignUp FAILED");
  }

  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("MQ-2 Sensor Ready (Warm-up needed)");
}

void loop() {
  if (Firebase.ready() && signupOK &&
      (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {

    sendDataPrevMillis = millis();

    int gasValue = analogRead(MQ2_PIN);

    Serial.print("Gas Value: ");
    Serial.println(gasValue);

    // Send Gas value to Firebase
    if (Firebase.RTDB.setInt(&fbdo, "MQ2/GasValue", gasValue)) {
      Serial.println("PASSED: Gas value sent");
    } else {
      Serial.println("FAILED: Gas value");
      Serial.println(fbdo.errorReason());
    }
  }
}
