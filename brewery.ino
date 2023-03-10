#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <uEEPROMLib.h>

#include <Arduino-progmem-menu.h>
#include "outputs/lcd-hd44780/LcdHd44780Output.h"
#include "inputs/analog-joystick/AnalogJoystick.h"

#include "./src/settings/recipe.h"
#include "./src/settings/settings.h"
#include "./src/settings/default-recipe.cpp"
#include "./src/settings/default-settings.cpp"
#include "./src/menu/recipe.h"
#include "./src/menu/settings.h"

#include "./src/display/index.h"
#include "./src/display/icons/index.h"
#include "./src/eeprom/index.h"


S_Recipe recipe1_settings;
S_Recipe recipe2_settings;
S_Recipe recipe3_settings;
S_Settings settings;

CRETE_RECIPE_MENU(recipe1_menu, recipe1_settings, 1);
CRETE_RECIPE_MENU(recipe2_menu, recipe2_settings, 2);
CRETE_RECIPE_MENU(recipe3_menu, recipe3_settings, 3);
CRETE_SETTINGS_MENU(settings_menu, settings);

MENU(appSettings, "", (0 | Menu::MENU_STYLE::NAME_HIDDEN_FOR_CHILD_LIST)
  ,SUBMENU(recipe1_menu)
  ,SUBMENU(recipe2_menu)
  ,SUBMENU(recipe3_menu)
  ,SUBMENU(settings_menu)
);


uEEPROMLib eeprom(0x50);

// Menu input and output
hd44780_I2Cexp lcd(0x3F);
Menu::AnalogJoystickInput menuInput(A3, A2, true);
Menu::LcdHd44780Output menuOutput(&lcd);


// All devices set-up
void setup() {
  lcd.begin(16, 2);
  loadSettings(
    eeprom,
    recipe1_settings,
    recipe2_settings,
    recipe3_settings,
    recipeDefaultSettings,
    settings,
    defaultSettings
  );

  lcd.init();
  lcd.backlight();
  lcd.noAutoscroll();

  loadIcons(lcd);
  
  printLoadingAnimation(lcd);
  delay(2000);
  clearDisplay(lcd);

  Menu::controller->init(&appSettingsMenu, &menuInput, &menuOutput);
}

// Update sensors and devices, display menu if visible, save settings on menu exit
void loop() {
  bool wasActive = appSettingsMenu.isActive;
  Menu::controller->update();

  if (!appSettingsMenu.isActive) {
    // save settings on menu exit
    if (wasActive) {
      saveSettings(
        eeprom,
        recipe1_settings,
        recipe2_settings,
        recipe3_settings,
        settings
      );
      clearDisplay(lcd);
    }

    printDemo(lcd);
    
    // printMashing(lcd, "#1");
    // printMashToBoil(lcd);
    // printBoiling(lcd);
    // printCooling(lcd);
    // printBoilToBrew(lcd);
    // printDone(lcd);
  }
}
