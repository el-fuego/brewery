#include <LiquidCrystal_I2C.h>
#include "./constants.h"
#include "./icons.cpp"

void loadIcons(LiquidCrystal_I2C &lcd) {
  lcd.createChar(WATER_IN_ICON_INDEX, waterInIcon);
  lcd.createChar(MASHING_ICON_INDEX, mashingIcon);
  lcd.createChar(HEATING_ICON_INDEX, heatingIcon);
  lcd.createChar(COOLING_ICON_INDEX, coolingIcon);
  lcd.createChar(CIRCULATION_ICON_INDEX, circulationIcon);
  lcd.createChar(TRANSFER_ICON_INDEX, transferIcon);
  lcd.createChar(HOP_IN_ICON_INDEX, hopInIcon);
}
