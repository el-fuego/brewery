#include <uEEPROMLib.h>
#include "../settings/recipe.h"
#include "../settings/settings.h"

void saveSettings(
  uEEPROMLib &eeprom,
  S_Recipe &recipe1_settings,
  S_Recipe &recipe2_settings,
  S_Recipe &recipe3_settings,
  S_Settings &settings
);
void loadSettings(
  uEEPROMLib &eeprom,
  S_Recipe &recipe1_settings,
  S_Recipe &recipe2_settings,
  S_Recipe &recipe3_settings,
  const S_Recipe &recipeDefaultSettings,
  S_Settings &settings,
  const S_Settings &defaultSettings
);