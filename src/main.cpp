#include "HX711.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
HX711 scale;

#define calibration_factor -25300.0
#define zero_factor -31452.0

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

float weight;

void setup() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Weight [g]:");
}

void loop() {
  weight = scale.get_units();
  weight = weight*1000;
  if (weight < 5) {
    weight = 0;
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Weight [g]:");
  lcd.setCursor(0, 1);
  lcd.print(weight,0);
  delay(1000);
}