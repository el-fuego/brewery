#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino-progmem-menu.h>
#include "./constants.h"
#include "./helpers.h"
#include "./icons/constants.h"

int previousTemperature = NULL;
int previousTimeMinutes = NULL;
String previousIcons;
unsigned long previousStageNamePrintedAtMillis = 0;
unsigned long previousTimeDotsPrintedAtMillis = 0;
char currentAnimatedBlinkingSymbol = ' ';

void printAnimatedBlinkingSymbol(LiquidCrystal_I2C &lcd, char symbol, int positionIndex, int lineIndex, unsigned long &previousMillis) {
	unsigned long currentMillis = millis();

  lcd.setCursor(positionIndex, lineIndex);
  delay(LCD_SET_POSITION_DELAY);

  if ((unsigned long) (currentMillis - previousMillis) > TIME_ANIMATION_INTERVAL) {
    previousMillis = currentMillis;

    if (currentAnimatedBlinkingSymbol != symbol) {
      lcd.print(symbol);
      currentAnimatedBlinkingSymbol = symbol;
    }
  } else {
    if (currentAnimatedBlinkingSymbol != ' ') {
      lcd.print(' ');
      currentAnimatedBlinkingSymbol = ' ';
    }
  }
}

void printAnimated(LiquidCrystal_I2C &lcd, String text, unsigned long &previousMillis) {
	unsigned long currentMillis = millis();

  if ((unsigned long) (currentMillis - previousMillis) > LCD_ANIMATION_INTERVAL) {
    previousMillis = currentMillis;
  }

	for (unsigned int i = 0; i < text.length(); i++) {
    delay(LCD_CHAR_ANIMATION_DELAY);
		if (currentMillis - previousMillis > i * LCD_CHAR_ANIMATION_INTERVAL) {
			lcd.print(text.charAt(i));
		} else {
			lcd.print(" ");
    }
	}
}

void printLogo(LiquidCrystal_I2C &lcd) {
  lcd.setCursor(0, 0);
  delay(LCD_SET_POSITION_DELAY);
  lcd.print((String) TRANSFER_ICON_STRING + TRANSFER_ICON_STRING + "Let it brew!" + TRANSFER_ICON_STRING + TRANSFER_ICON_STRING);
}

void printTemperature(LiquidCrystal_I2C &lcd, int temperature) {
  if (previousTemperature == temperature) {
    return;
  }
  previousTemperature = temperature;

  lcd.setCursor(12, 1);
  delay(LCD_SET_POSITION_DELAY);
  lcd.print(temperature);
  lcd.print((String) DEGREE_STRING + "C");
}

void printTimeLeft(LiquidCrystal_I2C &lcd, int timeMinutes, int lineIndex = 0) {
  printAnimatedBlinkingSymbol(lcd, ':', 13, lineIndex, previousTimeDotsPrintedAtMillis);

  if (previousTimeMinutes == timeMinutes) {
    return;
  }
  previousTimeMinutes = timeMinutes;

  lcd.setCursor(11, lineIndex);
  delay(LCD_SET_POSITION_DELAY);
  lcd.print(Menu::toTime24(timeMinutes));
}

void printStageNameAnimated(LiquidCrystal_I2C &lcd, String stageName) {
  lcd.home();
  printAnimated(lcd, (String) stageName + DOTS, previousStageNamePrintedAtMillis);
}

void printIcons(LiquidCrystal_I2C &lcd, String icons) {
  if (previousIcons == icons) {
    return;
  }
  previousIcons = icons;

  lcd.setCursor(1, 1);
  delay(LCD_SET_POSITION_DELAY);
  lcd.print(icons);
}

void clearDisplay(LiquidCrystal_I2C &lcd) {
  lcd.clear();
  previousTemperature = NULL;
  previousTimeMinutes = NULL;
  previousIcons = "";
  previousStageNamePrintedAtMillis = 0;
}