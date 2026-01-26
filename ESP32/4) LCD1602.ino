/***************************************************
   ESP32 + LCD1602 (I2C) CONNECTION

   LCD I2C Module:
   VCC -> 5V
   GND -> GND
   SDA -> GPIO 21
   SCL -> GPIO 22

   I2C Address (commonly):
   0x27 or 0x3F
****************************************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Change address if required (0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin(21, 22);   // SDA, SCL
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("ESP32 LCD I2C");
  lcd.setCursor(0, 1);
  lcd.print("Hello World!");
}

void loop() {
  // Nothing to repeat
}
