#ifndef SETTINGS_SETTINGS_H
#define SETTINGS_SETTINGS_H

// 		Timeout 10m
// 		Every 1m
// 		For 1m
struct S_ScheduledIntervalWithDelay {
  unsigned int timeout;
  unsigned int duration;
  unsigned int every;
};

// 		Duration 1m
struct S_Duration {
  unsigned int duration;
};

// 	1. Mesh motor
// 	2. Mesh pump
// 	3. Mesh filtration
// 	4. Mesh -> Boil
//  5. Boil pump
// 	6. Boil -> Brew
struct S_Settings {
  unsigned int struct_version;
  S_ScheduledIntervalWithDelay mesh_motor;
  S_ScheduledIntervalWithDelay mesh_pump;
  S_Duration mesh_filtration;
  S_Duration mesh_to_boil;
  S_ScheduledIntervalWithDelay boil_pump;
  S_Duration boil_to_brew;
};

#endif
