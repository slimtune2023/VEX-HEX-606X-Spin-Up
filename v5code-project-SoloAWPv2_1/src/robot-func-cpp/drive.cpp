#include "vex.h"
#include "robot-func/drive.h"

int drive_state = 0;

int brake_state = 0;

bool ButtonLeftReleased = true;
bool ButtonAReleased = true;

int lim = 127;


double drive_param = 1.75;
double turn_param = 4.5;

double normal_turn_speed = 0.7;
double slow_turn_speed = 0.3;

double logarithmic_turn(double speed) {
  
  if (speed != 0.0) {
    double absS = std::abs(speed);
    double sign = speed / absS;
    
    double l_speed = sign * (pow(absS, turn_param) / pow(lim, turn_param - 1) + 2);

    return l_speed;
  }

  return 0.0;
}

double logarithmic_drive(double speed) {

  if (speed != 0.0) {
    double absS = std::abs(speed);
    double sign = speed / absS;
    double l_speed = sign * pow(absS, drive_param) / pow(lim, drive_param - 1);

    return l_speed;
  }

  return 0.0;
}

void drive_speed_switch() {
  // drive speed switch
  if (Controller1.ButtonLeft.pressing()) {
    ButtonLeftReleased = false;
  } else {
    if (!ButtonLeftReleased) {
      Controller1.rumble(".");

      ButtonLeftReleased = true;

      if (drive_state == 1) {
        drive_state = 0;
      } else {
        drive_state = 1;
      }
    }
  }
}

void brake_switch() {
  // brake mode switch
  if (Controller1.ButtonA.pressing()) {
    ButtonAReleased = false;
  } else {
    if (!ButtonAReleased) {
      Controller1.rumble(".");

      ButtonAReleased = true;

      if (brake_state == 1) {
        brake_state = 0;
        LeftDriveSmart.setStopping(coast);
        RightDriveSmart.setStopping(coast);
      } else {
        brake_state = 1;
        LeftDriveSmart.setStopping(hold);
        RightDriveSmart.setStopping(hold);
      }
    }
  }
}

void drive_func() {
  // calculate the drivetrain motor velocities from the controller joystick axies
  // left = Axis3 + Axis1
  // right = Axis3 - Axis1
  
  double turnSpeed = logarithmic_turn(Controller1.Axis1.position());
  double driveSpeed = logarithmic_drive(Controller1.Axis3.position()); // logarithmic_drive

  // drive speed switch
  drive_speed_switch();

  if (drive_state == 0) {
    turnSpeed = turnSpeed * normal_turn_speed;
  } else {
    turnSpeed = turnSpeed * slow_turn_speed;
  }

  int drivetrainLeftSideSpeed = driveSpeed - turnSpeed;
  int drivetrainRightSideSpeed = driveSpeed + turnSpeed;
  
  LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
  RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);

  RightDriveSmart.spin(forward);
  LeftDriveSmart.spin(forward);

}