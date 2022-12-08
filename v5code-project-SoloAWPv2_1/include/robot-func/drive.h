#include "robot-config.h"
#include "vex.h"
#include <cmath>
#include "math-functions/math-stuff.h"

// 0 - normal
// 1 - slow
extern int drive_state;

// 0 - coast
// 1 - hold
extern int brake_state;

extern bool ButtonLeftReleased;
extern bool ButtonAReleased;

extern int lim;


extern double drive_param;
extern double turn_param;


extern double normal_turn_speed;
extern double slow_turn_speed;

// basic logarithmic drive function
double logarithmic_drive(double speed);

// basic logarithmic turn function
double logarithmic_turn(double speed);

void drive_speed_switch();
void brake_switch();

void drive_func();