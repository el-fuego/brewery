#ifndef RECIPE_MENU_H
#define RECIPE_MENU_H

#include <Arduino-progmem-menu.h>
#include "../settings/recipe.h"
#include "./constants.h"


// @display "1. 45°C - 10min"
// @return MENU {menuName}_stage{stageIndex}
// VARIABLES:
//   {structPrefix}.stage{stageIndex}.temperature
//   {structPrefix}.stage{stageIndex}.duration
#define CRETE_MASHING_STAGE_SUBMENU(menuName, structPrefix, stageIndex) \
  MENU(menuName, "Stage #" #stageIndex, Menu::MENU_STYLE::HORIZONTAL_CHILD_LIST\
    ,NUMBER_FIELD(menuName## _temperature, "", structPrefix .temperature, Menu::to2Digits, "\337C - ", MIN_TEMPERATURE, MAX_TEMPERATURE, 1)\
    ,NUMBER_FIELD(menuName## _duration, "", structPrefix .duration, Menu::to2Digits, "min", 0, MAX_TIME_MINUTES, 1)\
  );\

// @display "1. Mashing"
//   1. 45°C - 10mim
//   2. 52°C - 10mim
//   3. 63°C - 50mim
//   4. 78°C - 5mim
#define CRETE_MASHING_SUBMENU(menuName, structPrefix) \
  CRETE_MASHING_STAGE_SUBMENU(menuName## _stage1, structPrefix .stage1, 1);\
  CRETE_MASHING_STAGE_SUBMENU(menuName## _stage2, structPrefix .stage2, 2);\
  CRETE_MASHING_STAGE_SUBMENU(menuName## _stage3, structPrefix .stage3, 3);\
  CRETE_MASHING_STAGE_SUBMENU(menuName## _stage4, structPrefix .stage4, 4);\
  \
  MENU(menuName, "1. Mashing ", 0\
    ,SUBMENU(menuName## _stage1)\
    ,SUBMENU(menuName## _stage2)\
    ,SUBMENU(menuName## _stage3)\
    ,SUBMENU(menuName## _stage4)\
  );

// @display "Cell 1 on 10min"
// VARIABLES:
//   {structPrefix}.time
#define CRETE_CELL_SUBMENU(menuName, structPrefix, cellIndex) \
  MENU(menuName, "Cell #" #cellIndex,  Menu::MENU_STYLE::HORIZONTAL_CHILD_LIST\
    ,NUMBER_FIELD(menuName## _time, "Open at ", structPrefix .time, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,BLANK()\
  );\

// @display "2. Boiling"
//   Temp: 98°C
//   Time: 70m
//   Cell 1 on 10m
//   Cell 2 on 60m
//   Cell 3 on 65m
// VARIABLES:
//   {structPrefix}.temperature
//   {structPrefix}.duration
#define CRETE_BOILING_SUBMENU(menuName, structPrefix)\
  CRETE_CELL_SUBMENU(menuName## _cell1, structPrefix .cell1, 1);\
  CRETE_CELL_SUBMENU(menuName## _cell2, structPrefix .cell2, 2);\
  CRETE_CELL_SUBMENU(menuName## _cell3, structPrefix .cell3, 3);\
  \
  MENU(menuName, "2. Boiling ", 0\
    ,NUMBER_FIELD(menuName## _temperature, "Temp: ", structPrefix .temperature, Menu::to2Digits, "\337C", MIN_TEMPERATURE, MAX_TEMPERATURE, 1)\
    ,NUMBER_FIELD(menuName## _duration,    "Time: ", structPrefix .duration, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,SUBMENU(menuName## _cell1)\
    ,SUBMENU(menuName## _cell2)\
    ,SUBMENU(menuName## _cell3)\
  );\

// @display "3. Cooling"
//   Temp: 24°C
//   Cell 4 on 10m
// VARIABLES:
//   {structPrefix}.temperature
//   {structPrefix}.duration
#define CRETE_COOLING_SUBMENU(menuName, structPrefix) \
  CRETE_CELL_SUBMENU(menuName## _cell4, structPrefix .cell4, 4);\
  \
  MENU(menuName, "3. Cooling ", 0\
    ,NUMBER_FIELD(menuName## _temperature, "End temp.: ", structPrefix .temperature, Menu::to2Digits, "\337C", MIN_TEMPERATURE, MAX_TEMPERATURE, 1)\
    ,SUBMENU(menuName## _cell4)\
  );


// @display "Recipe 1"
//   1. Mashing
//   2. Boiling
//   3. Cooling
#define CRETE_RECIPE_MENU(menuName, structName, recipeIndex) \
  CRETE_MASHING_SUBMENU(menuName## _mashing, structName .mashing);\
  CRETE_BOILING_SUBMENU(menuName## _boiling, structName .boiling);\
  CRETE_COOLING_SUBMENU(menuName## _cooling, structName .cooling);\
  \
  MENU(menuName, "Recipe #" #recipeIndex, (Menu::MENU_STYLE::NAME_HIDDEN_FOR_CHILD_LIST)\
    ,SUBMENU(menuName## _mashing)\
    ,SUBMENU(menuName## _boiling)\
    ,SUBMENU(menuName## _cooling)\
  );\

#endif
