#include "vex.h"
#include "autonomous/auton-func.h"

PID turnPID = PID(0.07, 0.0, 0, 7.0, 1.0);
PID drivePID = PID(0.02, 0.0, 0.0, 5.0, 0.5);
PID correctPID = PID(0.0, 0.0, 0.0, 2.0, 0.0);

double min_speed_turn = 0.1;
double error_bound_turn = 5.0;

//
// ERROR BASED PID CONTROLS
//

// drive forward/backward for a certain distance
// dist is the distance (can be negative to go backwards)
void drive_func_error(double dist) {
  LeftDriveSmart.resetRotation();
  RightDriveSmart.resetRotation();
  inertialSensor.resetRotation();

  double wheel_diameter = 3.25;
  double wheel_encoder_target = dist / (M_PI * wheel_diameter) * 360 * 1.5;

  while (!drivePID.atTarget()) {

    double cur_wheel_position = (LeftDriveSmart.rotation(degrees) + RightDriveSmart.rotation(degrees)) / 2.0;

    double error_drive = wheel_encoder_target - cur_wheel_position;
    double error_turn = - inertialSensor.rotation(degrees);

    double drive_pwr = -drivePID.calculate(error_drive);
    double turn_pwr = correctPID.calculate(transformThetaError(error_turn));

    LeftDriveSmart.spin(forward, drive_pwr - turn_pwr, volt);
    RightDriveSmart.spin(forward, drive_pwr + turn_pwr, volt);
    

    wait(10, msec);
  }

  drivePID.reset();
  correctPID.reset();
  wait(10, msec);
}

// turn left/right a certain angle
// angel is the angle (can be negative for other direction)
// this turn angle is from the current position, so it is a relative angle NOT an absolute angle

void turn_func_error(double target) {
  inertialSensor.resetRotation();

  while (!turnPID.atTarget()) {
    double sensor = inertialSensor.rotation(degrees);
    double error = target - sensor;
    double t_error = transformThetaError(error);

    double turn_pwr;

    if ((t_error < 0.0) && (t_error > -error_bound_turn)) {
      turn_pwr = min_speed_turn;
    } else if ((t_error > 0.0) && (t_error < error_bound_turn)) {
      turn_pwr = -min_speed_turn;
    } else {
      turn_pwr = turnPID.calculate(t_error);
    }

    LeftDriveSmart.spin(forward, turn_pwr, volt);
    RightDriveSmart.spin(forward, -turn_pwr, volt);
    
    wait(10, msec);
  }

  turnPID.reset();
  wait(10, msec);
}

//
// TIME BASED PID CONTROLS
//

// drive forward/backward for a certain distance
// dist is the distance (can be negative to go backwards)
void drive_func_time(double dist, int max_time) {
  LeftDriveSmart.resetRotation();
  RightDriveSmart.resetRotation();
  inertialSensor.resetRotation();
  int t = 0;

  double wheel_diameter = 3.25;
  double wheel_encoder_target = dist / (M_PI * wheel_diameter) * 360 * 1.5;

  while (t < max_time) {

    double cur_wheel_position = (LeftDriveSmart.rotation(degrees) + RightDriveSmart.rotation(degrees)) / 2.0;

    double error_drive = wheel_encoder_target - cur_wheel_position;
    double error_turn = - inertialSensor.rotation(degrees);

    double drive_pwr = -drivePID.calculate(error_drive);
    double turn_pwr = correctPID.calculate(transformThetaError(error_turn));

    LeftDriveSmart.spin(forward, drive_pwr - turn_pwr, volt);
    RightDriveSmart.spin(forward, drive_pwr + turn_pwr, volt);
    
    t = t + 1;

    wait(10, msec);
  }

  drivePID.reset();
  correctPID.reset();
  Drivetrain.stop();
}

// turn left/right a certain angle
// angel is the angle (can be negative for other direction)
// this turn angle is from the current position, so it is a relative angle NOT an absolute angle

void turn_func_time(double target, int max_time) {
  inertialSensor.resetRotation();
  int t = 0;

  while (t < max_time) {
    double sensor = inertialSensor.rotation(degrees);
    double error = target - sensor;

    double turn_pwr = turnPID.calculate(transformThetaError(error));

    LeftDriveSmart.spin(forward, turn_pwr, volt);
    RightDriveSmart.spin(forward, -turn_pwr, volt);
    
    t = t + 1;
    wait(10, msec);
  }
  
  turnPID.reset();
  Drivetrain.stop();
}

//
// INTAKE FUNCTIONS
//

void start_intake() {
  intakerollerMotor.spin(forward, 80, percent);
}

void stop_intake_roller() {
  intakerollerMotor.stop();
}

void start_roller() {
  intakerollerMotor.spin(reverse, 100, percent);
}

void start_intake_thr() {
  waitUntil(cataReady == true);
  intakerollerMotor.spin(forward, 80, percent);
}

//
// CATA FUNCTIONS
//

void cata_launch() {
  cataMotor.spin(reverse, 100, percent);
  wait(100, msec);
  cataMotor.stop();
}

void cata_retract() {
  while (cataSwitch.value() == 1) {
    cataMotor.spin(reverse, 100, percent);
    // wait(10, msec);
  }

  cataMotor.stop();
  cataMotor.spinFor(reverse, 110, degrees);
  cataMotor.stop(hold);
}

void cata_start() {
  cataMotor.startRotateFor(reverse, 25, degrees);
}

bool cataActivated = false;
bool cataReady = true;
bool prev_cata = false;

int cataCallback() {
  while (true) {
    bool cur_cata = cataSwitch.value();

    if (cataActivated == true) {
      cataReady = false;
      cataMotor.spin(reverse, 100, percent);
      wait(200, msec);
      cataActivated = false;
    } else {
      if(cur_cata == 1) {
        cataMotor.spin(reverse, 60, percent);
      } else if (cur_cata == 0 && prev_cata == 1) {
        cataMotor.stop();
        cataMotor.spinFor(reverse, 50, degrees);
        cataMotor.stop(hold);
        cataReady = true;
      }
    }

    prev_cata = cur_cata;

    this_thread::sleep_for(10);
  }

  return 0;
}

void cata_launch_thr() {
  cataActivated = true;
}