/***************************************************
   ESP32 + MPU6050 CONNECTION (I2C)

   MPU6050:
   VCC -> 3.3V
   GND -> GND
   SDA -> GPIO 21
   SCL -> GPIO 22

   OUTPUT:
   - Acceleration values on Serial Monitor
****************************************************/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);

  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  Serial.println("MPU6050 Ready");
}

void loop() {
  mpu.getAcceleration(&ax, &ay, &az);

  Serial.print("AX: ");
  Serial.print(ax);
  Serial.print("  AY: ");
  Serial.print(ay);
  Serial.print("  AZ: ");
  Serial.println(az);

  delay(500);
}
