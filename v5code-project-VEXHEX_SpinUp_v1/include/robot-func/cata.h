#include "robot-config.h"
#include "vex.h"
#include <cmath>
#include "math-functions/math-stuff.h"

extern bool cataStopped;

extern int prev_cata_value;
extern int cur_cata_value;

extern bool ButtonUpBoolean;

void cataCylindersActivation();
void cataShoot();

void cata_func();