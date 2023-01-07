#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Arduino-progmem-menu.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "./icons/constants.h"
#include "./constants.h"
#include "./helpers.h"

void printLoadingAnimation(hd44780_I2Cexp &lcd);
void printMashing(hd44780_I2Cexp &lcd, String stageName);
void printMashToBoil(hd44780_I2Cexp &lcd);
void printBoiling(hd44780_I2Cexp &lcd);
void printCooling(hd44780_I2Cexp &lcd);
void printBoilToBrew(hd44780_I2Cexp &lcd);
void printDone(hd44780_I2Cexp &lcd);
void printDemo(hd44780_I2Cexp &lcd);

#endif