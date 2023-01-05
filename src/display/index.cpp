#include <Arduino.h>
#include <Arduino-progmem-menu.h>
#include <LiquidCrystal_I2C.h>

#include "./icons/constants.h"
#include "./constants.h"
#include "./helpers.h"
#include "./index.h"

void printLoadingAnimation(LiquidCrystal_I2C &lcd) {
  clearDisplay(lcd);
  printLogo(lcd);

  lcd.setCursor(1, 1);
  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + WATER_IN_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + MASHING_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) "" + HEATING_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + COOLING_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + CIRCULATION_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + HOP_IN_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + TRANSFER_ICON_STRING);
}

void printMashing(LiquidCrystal_I2C &lcd, String stageName) {
  String icons = "";

  // TODO get data from devices
  if (true) {
    icons = icons + WATER_IN_ICON_STRING + " ";
  }
  if (true) {
    icons = icons + MASHING_ICON_STRING + " ";
  }
  if (true) {
    icons = icons + HEATING_ICON_STRING + " ";
  }
  if (true) {
    icons = icons + CIRCULATION_ICON_STRING + " ";
  }
  printIcons(lcd, icons);
  printTemperature(lcd, 45);
  printTimeLeft(lcd, 118);

  printStageNameAnimated(lcd, "Mash " + stageName);
}

void printMashToBoil(LiquidCrystal_I2C &lcd) {
  // TODO get data from device
  printTimeLeft(lcd, 14, 1);

  printStageNameAnimated(lcd, (String) "Mash" + TRANSFER_ICON_STRING + TRANSFER_ICON_STRING + "Boil");
}

void printBoiling(LiquidCrystal_I2C &lcd) {
  String icons = "";

  // TODO get data from devices
  if (true) {
    icons = icons + HEATING_ICON_STRING + " ";
  }
  if (true) {
    icons = icons + CIRCULATION_ICON_STRING + " ";
  }
  for (int i = 0; i < 3; i++) {
    icons = icons + HOP_IN_ICON_STRING;
  }
  printIcons(lcd, icons);
  printTimeLeft(lcd, 67);
  printTemperature(lcd, 98);

  printStageNameAnimated(lcd, "Boiling");
}

void printCooling(LiquidCrystal_I2C &lcd) {
  String icons = "";

  // TODO get data from devices
  if (true) {
    icons = icons + COOLING_ICON_STRING + " ";
  }
  if (true) {
    icons = icons + CIRCULATION_ICON_STRING + " ";
  }
  printIcons(lcd, icons);
  printTemperature(lcd, 24);

  printStageNameAnimated(lcd, "Cooling");
}

void printBoilToBrew(LiquidCrystal_I2C &lcd) {
  // TODO get data from device
  printTimeLeft(lcd, 8, 1);

  printStageNameAnimated(lcd, (String) "Boil" + TRANSFER_ICON_STRING + TRANSFER_ICON_STRING + "Brew");
}

void printDone(LiquidCrystal_I2C &lcd) {
  clearDisplay(lcd);
  printLogo(lcd);

  lcd.setCursor(0, 1);
  lcd.print("   Done!  ");
}
