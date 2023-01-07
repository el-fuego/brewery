#ifndef DISPLAY_HELPERS_H
#define DISPLAY_HELPERS_H

#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <Arduino-progmem-menu.h>
#include "./constants.h"
#include "./icons/constants.h"

void printAnimatedBlinkingSymbol(hd44780_I2Cexp &lcd, char symbol, int positionIndex, int lineIndex, unsigned long &previousMillis);
void printAnimated(hd44780_I2Cexp &lcd, String text, unsigned long &previousMillis);
void printLogo(hd44780_I2Cexp &lcd);
void printTemperature(hd44780_I2Cexp &lcd, int temperature);
void printTimeLeft(hd44780_I2Cexp &lcd, int timeMinutes, int lineIndex = 0);
void clearDisplay(hd44780_I2Cexp &lcd);
void printStageNameAnimated(hd44780_I2Cexp &lcd, String stageName);
void printIcons(hd44780_I2Cexp &lcd, String icons);

#endif