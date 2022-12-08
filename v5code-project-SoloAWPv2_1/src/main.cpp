/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\saiko                                            */
/*    Created:      Tue Sep 27 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// cataDistance         distance      2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

#include "math-functions/math-stuff.h"
#include "autonomous/auton-func.h"

#include "robot-func/drive.h"
#include "robot-func/intake-roller.h"
#include "robot-func/cata.h"
#include "robot-func/pneumatic.h"
#include "robot-func/brain-func.h"

using namespace vex;

competition Competition;

bool RemoteControlCodeEnabled = true;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  cataMotor.setStopping(hold);
  intakerollerMotor.setStopping(coast);
  endgame.set(false);
  cataCylinders.set(false);

  LeftDriveSmart.setStopping(coast);
  RightDriveSmart.setStopping(coast);

  wait(50, msec);

  inertialSensor.calibrate();
  wait(50, msec);
  // waits for Inertial Sensor to calibrate 
  while (inertialSensor.isCalibrating()) {
    wait(100, msec);
  }

  wait(50, msec);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  // start catapult thread at beginning of autonomous
  
  thread cataThread = thread(cataCallback);

  LeftDriveSmart.setStopping(brake);
  RightDriveSmart.setStopping(brake);

  turn_func_error(90);

  // end catapult thread at the end of autonomous

  cataThread.interrupt();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// define variable for remote controller enable/disable


// define variables used for controlling motors based on controller inputs

void usercontrol(void) {
  // User control code here, inside the loop

  while(true) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    if(RemoteControlCodeEnabled) {
      brain_print();

      drive_func();

      // brake mode switch
      brake_switch();
      
      cata_func();

      intake_roller_func();

      // endgame activation code
      Controller1.ButtonR2.pressed(endgameActivation);

      // catapult cylinder activation code
      Controller1.ButtonUp.pressed(cataCylindersActivation);
    }

    // wait before repeating the process
    wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
