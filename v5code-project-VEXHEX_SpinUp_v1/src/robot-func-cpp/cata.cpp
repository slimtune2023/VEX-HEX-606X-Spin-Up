#include "vex.h"
#include "robot-func/cata.h"

bool cataStopped = true;

int prev_cata_value = 0;
int cur_cata_value = 0;

bool ButtonUpBoolean = true;

void cataCylindersActivation() {
  cataCylinders.set(ButtonUpBoolean);
  ButtonUpBoolean = !ButtonUpBoolean;
}

void cataShoot() {
  cataMotor.spin(reverse, 100, percent);
  wait(100, msec);
  cataMotor.stop();
}

void cata_func() {
  // catapult code
  if(Controller1.ButtonR1.pressing()) {
    // driver control to shoot catapult

    cataShoot();
  } else {
    // tells catapult to draw back automatically and stop when it reaches desired position

    cur_cata_value = cataSwitch.value();

    if(ButtonUpBoolean == true) {
      if(cataSwitch.value() == 1) {
        cataMotor.spin(reverse, 100, percent);
      } else if (cataSwitch.value() == 0 && prev_cata_value == 1) {
        cataMotor.stop();
        cataMotor.spinFor(reverse, 110, degrees);
        cataMotor.stop(hold);
      }
    } else if (ButtonUpBoolean == false) {
      if(cataSwitch.value() == 1) {
        cataMotor.spin(reverse, 60, percent);
      } else if (cataSwitch.value() == 0 && prev_cata_value == 1) {
        wait(6, msec);
        cataMotor.stop(hold);
      }
    }
    prev_cata_value = cur_cata_value;
  }
}