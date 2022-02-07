#include "HX711.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
HX711 scale;

#define calibration_factor -25300.0
#define zero_factor -31452.0
#define keg_weight 4117.0 // grams

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

float weight;
float poured_volume;

void setup() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.set_offset(zero_factor);

  lcd.init();
  lcd.backlight();
}

void loop() {
  poured_volume = 12.0;

  weight = scale.get_units(10);
  weight = weight*1000;
  if (weight < 5) {
    weight = 0;
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Volume:");
  lcd.setCursor(8, 0);
  lcd.print((weight-keg_weight)/1000,2);
  lcd.print(" L");
  lcd.setCursor(0,1);
  lcd.print("Poured:");
  lcd.setCursor(8, 1);
  lcd.print(poured_volume,2);
  lcd.print(" L");
  delay(100);
}