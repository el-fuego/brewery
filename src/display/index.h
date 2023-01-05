#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Arduino-progmem-menu.h>
#include <LiquidCrystal_I2C.h>

#include "./icons/constants.h"
#include "./constants.h"
#include "./helpers.h"

void printLoadingAnimation(LiquidCrystal_I2C &lcd);
void printMashing(LiquidCrystal_I2C &lcd, String stageName);
void printMashToBoil(LiquidCrystal_I2C &lcd);
void printBoiling(LiquidCrystal_I2C &lcd);
void printCooling(LiquidCrystal_I2C &lcd);
void printBoilToBrew(LiquidCrystal_I2C &lcd);
void printDone(LiquidCrystal_I2C &lcd);
void printDemo(LiquidCrystal_I2C &lcd);

#endif