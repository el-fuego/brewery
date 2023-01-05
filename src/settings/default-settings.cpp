#ifndef DEFAULT_SETTINGS_SETTINGS_H
#define DEFAULT_SETTINGS_SETTINGS_H

#include "./settings.h"

const S_Settings defaultSettings = {
  1, // struct_version
  { // mesh_motor
    10, // timeout;
    1, // duration;
    1 // every;
  },
  { // mesh_pump
    10, // timeout;
    1, // duration;
    1 // every;
  },
  { // mesh_filtration
    10, // duration;
  },
  { // mesh_to_boil
    10, // duration;
  },
  { // boil_pump
    10, // timeout;
    1, // duration;
    1 // every;
  },
  { // boil_to_brew
    10, // duration;
  },
};

#endif

