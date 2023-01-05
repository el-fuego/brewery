#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <Arduino-progmem-menu.h>
#include "../settings/settings.h"
#include "./constants.h"

// @display "Settings"
// 	1. Mesh motor
// 		Timeout 10m
// 		For 1m
// 		Every 1m
// 	2. Mesh pump
// 		Timeout 10m
// 		For 1m
// 		Every 1m
// 	3. Mesh filtration
// 		Time -10m
// 	4. Mesh -> Boil
// 		Time 5m
// 	5. Boil pump
// 		Timeout 10m
// 		For 1m
// 		Every 1m
// 	6. Boil -> Brew
// 		Time 5m
// VARIABLES:
//   {structName}.mesh_motor.timeout
//   {structName}.mesh_motor.every
//   {structName}.mesh_motor.duration
//   {structName}.mesh_pump.timeout
//   {structName}.mesh_pump.every
//   {structName}.mesh_pump.duration
//   {structName}.mesh_filtration.duration
//   {structName}.mesh_to_boil.duration
//   {structName}.boil_pump.timeout
//   {structName}.boil_pump.every
//   {structName}.boil_pump.duration
//   {structName}.boil_to_brew.duration
#define CRETE_SETTINGS_MENU(menuName, structName) \
  MENU(menuName## _mesh_motor, "1. Mesh motor", 0\
    ,NUMBER_FIELD(menuName## _mesh_motor_timeout,  "Timeout: ", structName .mesh_motor.timeout, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,NUMBER_FIELD(menuName## _mesh_motor_every,    "Every:   ", structName .mesh_motor.every, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,NUMBER_FIELD(menuName## _mesh_motor_duration, "For:     ", structName .mesh_motor.duration, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
  );\
  \
  MENU(menuName## _mesh_pump, "2. Mesh pump", 0\
    ,NUMBER_FIELD(menuName## _mesh_pump_timeout,  "Timeout: ", structName .mesh_pump.timeout, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,NUMBER_FIELD(menuName## _mesh_pump_every,    "Every:   ", structName .mesh_pump.every, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,NUMBER_FIELD(menuName## _mesh_pump_duration, "For:     ", structName .mesh_pump.duration, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
  );\
  \
  MENU(menuName## _mesh_filtration, "3. Mesh filter ", 0\
    ,NUMBER_FIELD(menuName## _mesh_filtration_duration, "Time: ", structName .mesh_filtration.duration, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,BLANK()\
  );\
  \
  MENU(menuName## _mesh_to_boil, "4. Mesh->Boil ", 0\
    ,NUMBER_FIELD(menuName## _mesh_to_boil_duration, "Time: ", structName .mesh_to_boil.duration, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,BLANK()\
  );\
  \
  MENU(menuName## _boil_pump, "5. Boil pump", 0\
    ,NUMBER_FIELD(menuName## _boil_pump_timeout,  "Timeout: ", structName .boil_pump.timeout, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,NUMBER_FIELD(menuName## _boil_pump_every,    "Every:   ", structName .boil_pump.every, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,NUMBER_FIELD(menuName## _boil_pump_duration, "For:     ", structName .boil_pump.duration, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
  );\
  \
  MENU(menuName## _boil_to_brew, "6. Boil->Brew ", 0\
    ,NUMBER_FIELD(menuName## _boil_to_brew_duration, "Time: ", structName .boil_to_brew.duration, Menu::to3Digits, "min", 0, MAX_TIME_MINUTES, 1)\
    ,BLANK()\
  );\
  \
  MENU(menuName, "Settings ", (Menu::MENU_STYLE::NAME_HIDDEN_FOR_CHILD_LIST)\
    ,SUBMENU(menuName## _mesh_motor)\
    ,SUBMENU(menuName## _mesh_pump)\
    ,SUBMENU(menuName## _mesh_filtration)\
    ,SUBMENU(menuName## _mesh_to_boil)\
    ,SUBMENU(menuName## _boil_pump)\
    ,SUBMENU(menuName## _boil_to_brew)\
  );

#endif
