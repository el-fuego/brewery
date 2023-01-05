#ifndef DISPLAY_HELPERS_H
#define DISPLAY_HELPERS_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino-progmem-menu.h>
#include "./constants.h"
#include "./icons/constants.h"

void printAnimatedBlinkingSymbol(LiquidCrystal_I2C &lcd, char symbol, int positionIndex, int lineIndex, unsigned long &previousMillis);
void printAnimated(LiquidCrystal_I2C &lcd, String text, unsigned long &previousMillis);
void printLogo(LiquidCrystal_I2C &lcd);
void printTemperature(LiquidCrystal_I2C &lcd, int temperature);
void printTimeLeft(LiquidCrystal_I2C &lcd, int timeMinutes, int lineIndex = 0);
void clearDisplay(LiquidCrystal_I2C &lcd);
void printStageNameAnimated(LiquidCrystal_I2C &lcd, String stageName);
void printIcons(LiquidCrystal_I2C &lcd, String icons);

#endif