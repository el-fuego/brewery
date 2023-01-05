#include <Arduino.h>

const unsigned char mashingIcon[8] = {
  B00100,
  B00100,
  B00010,
  B00100,
  B01000,
  B00100,
  B11111,
  B01110
};

const unsigned char coolingIcon[8] = {
  B10000,
  B11000,
  B10010,
  B01010,
  B00010,
  B00111,
  B00010,
  B00000
};

const unsigned char heatingIcon[8] = {
  B00000,
  B00010,
  B00111,
  B00010,
  B10010,
  B11010,
  B10000,
  B01000
};

const unsigned char circulationIcon[8] = {
  0b00100,
  0b00000,
  0b01010,
  0b00000,
  0b10101,
  0b00000,
  0b11111,
  0b01110
};

const unsigned char transferIcon[8] = {
  B00000,
  B10100,
  B01010,
  B00101,
  B01010,
  B10100,
  B00000,
  B00000
};

const unsigned char waterInIcon[8] = {
  B00100,
  B00100,
  B00100,
  B01110,
  B00100,
  B00000,
  B11111,
  B01110
};

const unsigned char hopInIcon[8] = {
  B01010,
  B01110,
  B00100,
  B01110,
  B10111,
  B11101,
  B10111,
  B01110
};
