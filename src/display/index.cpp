#include "./index.h"

unsigned long demoStartedAtMillis = 0;
int previousDemoStageIndex = 0;
int currentDemoStageIndex = 0;
bool isDonePrinted = false;

void printLoadingAnimation(hd44780_I2Cexp &lcd) {
  clearDisplay(lcd);
  printLogo(lcd);

  lcd.setCursor(0, 1);
  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + WATER_IN_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + MASHING_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + HEATING_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + COOLING_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + CIRCULATION_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + HOP_IN_ICON_STRING);

  delay(LCD_CHAR_ANIMATION_INTERVAL);
  lcd.print((String) " " + TRANSFER_ICON_STRING);
}

void printMashing(hd44780_I2Cexp &lcd, String stageName) {
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

void printMashToBoil(hd44780_I2Cexp &lcd) {
  // TODO get data from device
  printTimeLeft(lcd, 14, 1);

  printStageNameAnimated(lcd, (String) "Mash" + TRANSFER_ICON_STRING + TRANSFER_ICON_STRING + "Boil");
}

void printBoiling(hd44780_I2Cexp &lcd) {
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

void printCooling(hd44780_I2Cexp &lcd) {
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

void printBoilToBrew(hd44780_I2Cexp &lcd) {
  // TODO get data from device
  printTimeLeft(lcd, 8, 1);

  printStageNameAnimated(lcd, (String) "Boil" + TRANSFER_ICON_STRING + TRANSFER_ICON_STRING + "Brew");
}

void printDone(hd44780_I2Cexp &lcd) {
  if (isDonePrinted) {
    return;
  }
  isDonePrinted = true;
  printLogo(lcd);

  lcd.setCursor(0, 1);
  lcd.print("   Done!  ");
}

void printDemo(hd44780_I2Cexp &lcd) {
  if (demoStartedAtMillis == 0) {
    demoStartedAtMillis = millis();
  }
  unsigned long currentTimeLeft = (unsigned long) (millis() - demoStartedAtMillis) % (unsigned long) (DEMO_STAGE_INTERVAL*10);

  if (currentTimeLeft < DEMO_STAGE_INTERVAL) {
    if (currentDemoStageIndex != 1) {
      clearDisplay(lcd);
    }
    currentDemoStageIndex = 1;
    printMashing(lcd, "#1");

  } else if (currentTimeLeft < (unsigned long) DEMO_STAGE_INTERVAL*2) {
    if (currentDemoStageIndex != 2) {
      clearDisplay(lcd);
    }
    currentDemoStageIndex = 2;
    printMashing(lcd, "#2");

  } else if (currentTimeLeft < (unsigned long) DEMO_STAGE_INTERVAL*3) {
    if (currentDemoStageIndex != 3) {
      clearDisplay(lcd);
    }
    currentDemoStageIndex = 3;
    printMashing(lcd, "#3");

  } else if (currentTimeLeft < (unsigned long) DEMO_STAGE_INTERVAL*4) {
    if (currentDemoStageIndex != 4) {
      clearDisplay(lcd);
    }
    currentDemoStageIndex = 4;
    printMashing(lcd, "#4");

  } else if (currentTimeLeft < (unsigned long) DEMO_STAGE_INTERVAL*5) {
    if (currentDemoStageIndex != 5) {
      clearDisplay(lcd);
    }
    currentDemoStageIndex = 5;
    printMashToBoil(lcd);

  } else if (currentTimeLeft < (unsigned long) DEMO_STAGE_INTERVAL*6) {
    if (currentDemoStageIndex != 6) {
      clearDisplay(lcd);
    }
    currentDemoStageIndex = 6;
    printBoiling(lcd);

  } else if (currentTimeLeft < (unsigned long) DEMO_STAGE_INTERVAL*7) {
    if (currentDemoStageIndex != 7) {
      clearDisplay(lcd);
    }
    currentDemoStageIndex = 7;
    printCooling(lcd);

  } else if (currentTimeLeft < (unsigned long) DEMO_STAGE_INTERVAL*8) {
    if (currentDemoStageIndex != 8) {
      clearDisplay(lcd);
    }
    currentDemoStageIndex = 8;
    printBoilToBrew(lcd);

  } else if (currentTimeLeft < (unsigned long) DEMO_STAGE_INTERVAL*9) {
    if (currentDemoStageIndex != 9) {
      clearDisplay(lcd);
    }
    currentDemoStageIndex = 9;
    printDone(lcd);

  } else {
    isDonePrinted = false;
    demoStartedAtMillis = millis();
  }
}