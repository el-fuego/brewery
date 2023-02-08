#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <uEEPROMLib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <Arduino-progmem-menu.h>
#include "outputs/lcd-hd44780/LcdHd44780Output.h"
#include "inputs/analog-joystick/AnalogJoystick.h"

#include <Arduino-devices.h>
#include "sensors/clocks/DS3231.h"
#include "sensors/temperature-and-humidity/DallasTemperature.h"
#include "devices/outputs/PCA9685.h"
#include "devices/outputs/Null.h"
#include "devices/switch-by-time/ClockTimeIntervalSwitch.h"
#include "devices/switch-by-time/ScheduleIntervalSwitch.h"
#include "devices/switch-by-level/TurnOnWhenHigher.h"
#include "devices/switch-by-level/TurnOnWhenLower.h"

#include "./src/settings/recipe.h"
#include "./src/settings/settings.h"
#include "./src/settings/default-recipe.cpp"
#include "./src/settings/default-settings.cpp"
#include "./src/menu/recipe.h"
#include "./src/menu/settings.h"

#include "./src/display/index.h"
#include "./src/display/icons/index.h"
#include "./src/eeprom/index.h"


#define EEPROM_ADDRESS_I2C 0x50
#define PIN_EXPANDER_ADDRESS_I2C 0x41
#define LCD_ADDRESS_I2C 0x3F
#define TEMPERATURES_PIN 1
#define JOYSTICK_PIN_X A3
#define JOYSTICK_PIN_Y A2
#define MASH_HEATER_ON_PIN_EXPANDER_PIN 13
#define BOIL_HEATER_ON_PIN_EXPANDER_PIN 12
#define BOIL_COOLER_ON_PIN_EXPANDER_PIN 11

#define DO_NOTHING_TEMPERATURE 0

// TODO: pass right temperature sensor *address*
DeviceAddress meshingTemperatureSensorAddress = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };
// TODO: pass right temperature sensor *address*
DeviceAddress boilingTemperatureSensorAddress = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };

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



// DEVICES
uEEPROMLib eeprom(EEPROM_ADDRESS_I2C);


// Sensors
// TODO: use DS1307 sensor
DS3231_Sensor clock;
OneWire oneWire(TEMPERATURES_PIN);
DallasTemperature_Sensor meshingTemperatureSensor(&oneWire, meshingTemperatureSensorAddress);
DallasTemperature_Sensor boilingTemperatureSensor(&oneWire, boilingTemperatureSensorAddress);


// Output
// TODO: use PCF8575
PCA9685_Output *pinExpander = new PCA9685_Output(PIN_EXPANDER_ADDRESS_I2C);
NullOutput *nullOutput;

// TODO meshMotor
// ScheduleIntervalSwitch meshMotor(pinExpander, 1, settings.mesh_motor.duration, settings.mesh_motor.every);

// TODO hopMotor DRV8825


// TODO Pumps
ScheduleIntervalSwitch mashPump(pinExpander, 0, settings.mesh_pump.duration, settings.mesh_pump.every);
ScheduleIntervalSwitch boilPump(pinExpander, 10, settings.boil_pump.duration, settings.boil_pump.every);

// Heaters and cooler
TurnOnWhenLower meshingHeater(pinExpander, (unsigned char)MASH_HEATER_ON_PIN_EXPANDER_PIN, DO_NOTHING_TEMPERATURE, meshingTemperatureSensor.temperature);
TurnOnWhenLower boilingHeater(pinExpander, (unsigned char)BOIL_HEATER_ON_PIN_EXPANDER_PIN, DO_NOTHING_TEMPERATURE, boilingTemperatureSensor.temperature);
TurnOnWhenHigher boilingCooler(pinExpander, (unsigned char)BOIL_COOLER_ON_PIN_EXPANDER_PIN, DO_NOTHING_TEMPERATURE, boilingTemperatureSensor.temperature);

// Menu input and output
hd44780_I2Cexp lcd(LCD_ADDRESS_I2C);
Menu::AnalogJoystickInput menuInput(JOYSTICK_PIN_X, JOYSTICK_PIN_Y, true);
Menu::LcdHd44780Output menuOutput(&lcd);


// Controllers
ClockTimeIntervalSwitch* createClockTimeIntervalSwitch(unsigned int startAtMinutes, unsigned int duration) {
  unsigned int endAtMinutes = startAtMinutes + duration;
  return new ClockTimeIntervalSwitch( nullOutput, 0, startAtMinutes, endAtMinutes);
}

void (*currentStageCallback)() = &mashingStage1Update;
void (*previousStageCallback)() = &mashingStage1Update;
unsigned int currentBoilingCell = 0;
ClockTimeIntervalSwitch *currentClockTimeIntervalSwitch = 0;
S_Recipe *selectedRecipeSettings = &recipe1_settings;

void initStageCallback(unsigned int startAt, unsigned int duration) {
  if (previousStageCallback != currentStageCallback) {
     ClockTimeIntervalSwitch *previousClockTimeIntervalSwitch = currentClockTimeIntervalSwitch;
     currentClockTimeIntervalSwitch = createClockTimeIntervalSwitch( startAt, duration );

     previousStageCallback = currentStageCallback;
  }
}

void setNextStageCallback(void (*nextStageCallback)()) {
  if (currentClockTimeIntervalSwitch->isEnabled == false) {
    currentStageCallback = nextStageCallback;
  }
}

void mashingStageUpdate(unsigned int startAt, S_MashingStage *stageSettings, void (*nextStageCallback)()){
  initStageCallback(startAt, stageSettings->duration);
  if (meshingHeater.demandedValue != stageSettings->temperature) {
    meshingHeater.demandedValue = stageSettings->temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  meshingTemperatureSensor.update();
  meshingHeater.update();

  setNextStageCallback(nextStageCallback);
}

void mashingStage1Update() {
  initStageCallback(0, selectedRecipeSettings->mashing.stage1.duration);
  if (meshingHeater.demandedValue != selectedRecipeSettings->mashing.stage1.temperature) {
    meshingHeater.demandedValue = selectedRecipeSettings->mashing.stage1.temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  meshingTemperatureSensor.update();
  meshingHeater.update();

  setNextStageCallback(mashingStage2Update);
}

void mashingStage2Update() {
  initStageCallback(currentClockTimeIntervalSwitch->toMinutes, selectedRecipeSettings->mashing.stage2.duration);
  if (meshingHeater.demandedValue != selectedRecipeSettings->mashing.stage2.temperature) {
    meshingHeater.demandedValue = selectedRecipeSettings->mashing.stage2.temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  meshingTemperatureSensor.update();
  meshingHeater.update();

  setNextStageCallback(mashingStage3Update);
}

void mashingStage3Update() {
  initStageCallback(currentClockTimeIntervalSwitch->toMinutes, selectedRecipeSettings->mashing.stage3.duration);
  if (meshingHeater.demandedValue != selectedRecipeSettings->mashing.stage3.temperature) {
    meshingHeater.demandedValue = selectedRecipeSettings->mashing.stage3.temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  meshingTemperatureSensor.update();
  meshingHeater.update();

  setNextStageCallback(mashingStage4Update);
}

void mashingStage4Update() {
  initStageCallback(currentClockTimeIntervalSwitch->toMinutes, selectedRecipeSettings->mashing.stage4.duration);
  if (meshingHeater.demandedValue != selectedRecipeSettings->mashing.stage4.temperature) {
    meshingHeater.demandedValue = selectedRecipeSettings->mashing.stage4.temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  meshingTemperatureSensor.update();
  meshingHeater.update();

  setNextStageCallback(mashingFiltrationUpdate);
}

void mashingFiltrationUpdate() {
  initStageCallback(currentClockTimeIntervalSwitch->toMinutes, settings.mesh_filtration.duration);
  if (meshingHeater.demandedValue != selectedRecipeSettings->mashing.stage4.temperature) {
    meshingHeater.demandedValue = selectedRecipeSettings->mashing.stage4.temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  meshingTemperatureSensor.update();
  meshingHeater.update();

  setNextStageCallback(masherToBoilerUpdate);
}

void masherToBoilerUpdate() {
  // Turn off mashing heater
  meshingHeater.demandedValue = DO_NOTHING_TEMPERATURE;
  pinExpander->write(MASH_HEATER_ON_PIN_EXPANDER_PIN, false);

  // Init step
  initStageCallback(currentClockTimeIntervalSwitch->toMinutes, settings.mesh_to_boil.duration);
  if (boilingHeater.demandedValue != selectedRecipeSettings->boiling.temperature) {
    boilingHeater.demandedValue = selectedRecipeSettings->boiling.temperature;
  }

  // Update sensors
  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  boilingTemperatureSensor.update();
  boilingHeater.update();

  // set next callback on stage end time
  setNextStageCallback(boilingToCell1Update);
}

void boilingToCell1Update() {
  initStageCallback(currentClockTimeIntervalSwitch->toMinutes, &selectedRecipeSettings->boiling.cell1.time );
  if (boilingHeater.demandedValue != selectedRecipeSettings->boiling.temperature) {
    boilingHeater.demandedValue = selectedRecipeSettings->boiling.temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  boilingTemperatureSensor.update();
  boilingHeater.update();

  setNextStageCallback(boilingToCell2Update);
}

void boilingToCell2Update() {
  initStageCallback(currentClockTimeIntervalSwitch->fromMinutes, &selectedRecipeSettings->boiling.cell2.time );
  if (boilingHeater.demandedValue != selectedRecipeSettings->boiling.temperature) {
    boilingHeater.demandedValue = selectedRecipeSettings->boiling.temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  boilingTemperatureSensor.update();
  boilingHeater.update();

  if (currentBoilingCell != 1) {
    // TODO: Rotate hopMotor to cell 1
    currentBoilingCell = 1;
  }

  setNextStageCallback(boilingToCell3Update);
}

void boilingToCell3Update() {
  initStageCallback(currentClockTimeIntervalSwitch->fromMinutes, &selectedRecipeSettings->boiling.cell3.time );
  if (boilingHeater.demandedValue != selectedRecipeSettings->boiling.temperature) {
    boilingHeater.demandedValue = selectedRecipeSettings->boiling.temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  boilingTemperatureSensor.update();
  boilingHeater.update();

  if (currentBoilingCell != 2) {
    // TODO: Rotate hopMotor to cell 2
    currentBoilingCell = 2;
  }

  setNextStageCallback(boilingAfterCell3Update);
}

void boilingAfterCell3Update() {
  initStageCallback(currentClockTimeIntervalSwitch->fromMinutes, &selectedRecipeSettings->boiling.duration );
  if (boilingHeater.demandedValue != selectedRecipeSettings->boiling.temperature) {
    boilingHeater.demandedValue = selectedRecipeSettings->boiling.temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  boilingTemperatureSensor.update();
  boilingHeater.update();

  if (currentBoilingCell != 3) {
    // TODO: Rotate hopMotor to cell 3
    currentBoilingCell = 3;
  }

  setNextStageCallback(coolingUpdate);
}

void coolingUpdate() {
  // Turn off boiling heater
  boilingHeater.demandedValue = DO_NOTHING_TEMPERATURE;
  pinExpander->write(BOIL_HEATER_ON_PIN_EXPANDER_PIN, false);

  if (currentBoilingCell != 0) {
    // TODO: Rotate hopMotor to initial cell
    currentBoilingCell = 0;
  }

  initStageCallback(currentClockTimeIntervalSwitch->toMinutes, 60);
  if (boilingHeater.demandedValue != selectedRecipeSettings->cooling.temperature) {
    boilingHeater.demandedValue = selectedRecipeSettings->cooling.temperature;
  }

  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  boilingTemperatureSensor.update();
  boilingCooler.update();
  
  setNextStageCallback(boilerToBrewUpdate);
}

void boilerToBrewUpdate() {
  // Turn off boiling cooler
  boilingCooler.demandedValue = DO_NOTHING_TEMPERATURE;
  pinExpander->write(BOIL_COOLER_ON_PIN_EXPANDER_PIN, false);

  initStageCallback(currentClockTimeIntervalSwitch->toMinutes, settings.boil_to_brew.duration);
  currentClockTimeIntervalSwitch->update(clock.getIntTime());
  boilingTemperatureSensor.update();

  setNextStageCallback(done);
}

void done() {
  printDone(&lcd);

  // TODO: press any key to reload/reset
}



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
    // mashPump.update(clock.toEpochMinutes());

    currentStageCallback();
    
    // printMashing(lcd, "#1");
    // printMashToBoil(lcd);
    // printBoiling(lcd);
    // printCooling(lcd);
    // printBoilToBrew(lcd);
    // printDone(lcd);
  }
}
