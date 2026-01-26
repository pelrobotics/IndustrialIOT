/***************************************************
   ESP32 + MPU6050 CONNECTION (I2C)

   MPU6050:
   VCC -> 3.3V
   GND -> GND
   SDA -> GPIO 21
   SCL -> GPIO 22

   NOTE:
   - Uses accelerometer only
   - Vibration detected using acceleration change
****************************************************/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;
int16_t prev_ax = 0, prev_ay = 0, prev_az = 0;

int vibrationThreshold = 3000;   // Adjust experimentally

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);

  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection FAILED");
    while (1);
  }

  Serial.println("MPU6050 Ready");
}

void loop() {
  mpu.getAcceleration(&ax, &ay, &az);

  int diff = abs(ax - prev_ax) +
             abs(ay - prev_ay) +
             abs(az - prev_az);

  if (diff > vibrationThreshold) {
    Serial.println("⚠️ VIBRATION DETECTED!");
  } else {
    Serial.println("Normal Condition");
  }

  prev_ax = ax;
  prev_ay = ay;
  prev_az = az;

  delay(500);
}
