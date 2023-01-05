#ifndef RECIPE_SETTINGS_H
#define RECIPE_SETTINGS_H

// Recipe #1
// 	1. Mashing
// 		1. 45°C - 10mim
// 		2. 52°C - 10mim
// 		3. 63°C - 50mim
// 		4. 78°C - 5mim
struct S_MashingStage {
  unsigned int temperature;
  unsigned int duration;
};
struct S_Mashing {
  S_MashingStage stage1;
  S_MashingStage stage2;
  S_MashingStage stage3;
  S_MashingStage stage4;
};

// 	2. Boiling
// 		Temp: 98°C
// 		Time: 70m
// 		Cell 1 on 10m
// 		Cell 2 on 60m
// 		Cell 3 on 65m
struct S_Cell {
  unsigned int time;
};
struct S_Boiling {
  unsigned int temperature;
  unsigned int duration;
  S_Cell cell1;
  S_Cell cell2;
  S_Cell cell3;
};

// 	3. Cooling
// 		Temp: 24°C
// 		Cell 4 on 10m
struct S_Cooling {
  unsigned int temperature;
  S_Cell cell4;
};

struct S_Recipe {
  S_Mashing mashing;
  S_Boiling boiling;
  S_Cooling cooling;
};

#endif
