#include "vex.h"
#include "robot-func/intake-roller.h"

bool intakerollerStopped = true;
bool rollerActivated = false;

void intake_roller_func() {
  int rollerJoystick = Controller1.Axis2.position();
  
  // check if the value is inside of the deadband range
  if (rollerJoystick > 60) {
    rollerActivated = rollerJoystick;
    intakerollerMotor.spin(reverse, rollerJoystick/2 + 15, percent);
    rollerActivated = true;

  } else {
    rollerActivated = false;

    if (Controller1.ButtonL1.pressing()) {
      intakerollerMotor.spin(forward, 80, percent);
      intakerollerStopped = false;
    } else if (Controller1.ButtonL2.pressing()) {
      intakerollerMotor.spin(reverse, 100, percent);
      intakerollerStopped = false;
    } else if (!intakerollerStopped) {
      intakerollerMotor.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      intakerollerStopped = true;
    } else {
      intakerollerMotor.stop();
    }
  }
}