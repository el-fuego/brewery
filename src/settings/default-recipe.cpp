#ifndef DEFAULT_RECIPE_SETTINGS_H
#define DEFAULT_RECIPE_SETTINGS_H

#include "./recipe.h"

const S_Recipe recipeDefaultSettings = {
  { // mashing
    { // stage1
      45, // temperature
      10 // duration
    },
    { // stage2
      52, // temperature
      10 // duration
    },
    { // stage3
      63, // temperature
      50 // duration
    },
    { // stage4
      78, // temperature
      5 // duration
    }
  },
  { // boiling
    98, // temperature
    70, // duration
    { // cell1
      10, // time
    },
    { // cell2
      60, // time
    },
    { // cell3
      65, // time
    }
  },
  { // cooling
    98, // temperature
    { // cell4
      0, // time
    }
  }
};

#endif
