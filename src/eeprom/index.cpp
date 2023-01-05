#include <uEEPROMLib.h>
#include "../settings/recipe.h"
#include "../settings/settings.h"
#include "./index.h"

// Save settings at EEPROM
void saveSettings(
  uEEPROMLib &eeprom,
  S_Recipe &recipe1_settings,
  S_Recipe &recipe2_settings,
  S_Recipe &recipe3_settings,
  S_Settings &settings
) {
  unsigned int settingsSize = sizeof(settings);
  unsigned int recipeSize = sizeof(recipe1_settings);

  eeprom.eeprom_write( settingsSize, recipe1_settings );
  eeprom.eeprom_write( settingsSize + recipeSize, recipe2_settings );
  eeprom.eeprom_write( settingsSize + recipeSize*2, recipe3_settings );
  eeprom.eeprom_write( 0, settings );
}

// Load settings, stored at EEPROM
void loadSettings(
  uEEPROMLib &eeprom,
  S_Recipe &recipe1_settings,
  S_Recipe &recipe2_settings,
  S_Recipe &recipe3_settings,
  const S_Recipe &recipeDefaultSettings,
  S_Settings &settings,
  const S_Settings &defaultSettings
) {
  unsigned int settingsSize = sizeof(defaultSettings);
  unsigned int recipeSize = sizeof(recipeDefaultSettings);

  eeprom.eeprom_read( 0, &settings );

  if (settings.struct_version != defaultSettings.struct_version) {
    settings = defaultSettings;
    recipe1_settings = recipeDefaultSettings;
    recipe2_settings = recipeDefaultSettings;
    recipe3_settings = recipeDefaultSettings;
    
    saveSettings(
      eeprom,
      recipe1_settings,
      recipe2_settings,
      recipe3_settings,
      settings
    );
    return;
  }

  eeprom.eeprom_read( settingsSize, &recipeDefaultSettings );
  eeprom.eeprom_read( settingsSize + recipeSize, &recipeDefaultSettings );
  eeprom.eeprom_read( settingsSize + recipeSize*2, &recipeDefaultSettings );
}