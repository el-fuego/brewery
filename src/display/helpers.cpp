#include "./helpers.h"

int previousTemperature = NULL;
int previousTimeMinutes = NULL;
String previousIcons;
unsigned long previousStageNamePrintedAtMillis = 0;
unsigned long previousTimeDotsPrintedAtMillis = 0;
char currentAnimatedBlinkingSymbol = ' ';

void printAnimatedBlinkingSymbol(hd44780_I2Cexp &lcd, char symbol, int positionIndex, int lineIndex, unsigned long &previousMillis) {
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

void printAnimated(hd44780_I2Cexp &lcd, String text, unsigned long &previousMillis) {
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

void printLogo(hd44780_I2Cexp &lcd) {
  lcd.setCursor(0, 0);
  delay(LCD_SET_POSITION_DELAY);
  lcd.print((String) TRANSFER_ICON_STRING + TRANSFER_ICON_STRING + "Let it brew!" + TRANSFER_ICON_STRING + TRANSFER_ICON_STRING);
}

void printTemperature(hd44780_I2Cexp &lcd, int temperature) {
  if (previousTemperature == temperature) {
    return;
  }
  previousTemperature = temperature;

  lcd.setCursor(12, 1);
  delay(LCD_SET_POSITION_DELAY);
  lcd.print(temperature);
  lcd.print((String) DEGREE_STRING + "C");
}

void printTimeLeft(hd44780_I2Cexp &lcd, int timeMinutes, int lineIndex = 0) {
  printAnimatedBlinkingSymbol(lcd, ':', 13, lineIndex, previousTimeDotsPrintedAtMillis);

  if (previousTimeMinutes == timeMinutes) {
    return;
  }
  previousTimeMinutes = timeMinutes;

  lcd.setCursor(11, lineIndex);
  delay(LCD_SET_POSITION_DELAY);
  lcd.print(Menu::toTime24(timeMinutes));
}

void printStageNameAnimated(hd44780_I2Cexp &lcd, String stageName) {
  lcd.home();
  printAnimated(lcd, (String) stageName + DOTS, previousStageNamePrintedAtMillis);
}

void printIcons(hd44780_I2Cexp &lcd, String icons) {
  if (previousIcons == icons) {
    return;
  }
  previousIcons = icons;

  lcd.setCursor(1, 1);
  delay(LCD_SET_POSITION_DELAY);
  lcd.print(icons);
}

void clearDisplay(hd44780_I2Cexp &lcd) {
  lcd.clear();
  previousTemperature = NULL;
  previousTimeMinutes = NULL;
  previousIcons = "";
  previousStageNamePrintedAtMillis = 0;
}