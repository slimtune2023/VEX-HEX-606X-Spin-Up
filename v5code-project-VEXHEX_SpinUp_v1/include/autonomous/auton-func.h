#ifndef _AUTON_

#define _AUTON_

#include "robot-config.h"
#include "vex.h"
#include <cmath>
#include "math-functions/math-stuff.h"
#include "autonomous/PID.h"

using namespace vex;

extern PID turnPID;
extern PID drivePID;
extern PID correctPID;

extern 

//
// ERROR BASED PID CONTROLS
//

void drive_func_error(double dist);
void turn_func_error(double angel);

//
// TIME BASED PID CONTROLS
//

void drive_func_time(double dist, int max_time);
void turn_func_time(double angel, int max_time);

//
// INTAKE FUNCTIONS
//

void start_intake();
void stop_intake_roller();
void start_roller();

void start_intake_thr();

//
// CATA FUNCTIONS
//

extern bool cataActivated;
extern bool prev_cata;
extern bool cataReady;

void cata_launch();
void cata_retract();
void cata_start();

int cataCallback();
void cata_launch_thr();

#endif // _AUTON_