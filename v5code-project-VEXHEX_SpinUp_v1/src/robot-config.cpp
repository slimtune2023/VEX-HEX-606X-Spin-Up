#include "vex.h"
#include <cmath>

#include "autonomous/auton-func.h"

#include "robot-func/drive.h"
#include "robot-func/intake-roller.h"
#include "robot-func/cata.h"
#include "robot-func/pneumatic.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorA = motor(PORT18, ratio6_1, false);
motor leftMotorB = motor(PORT19, ratio6_1, true);
motor leftMotorC = motor(PORT20, ratio6_1, false);

motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);

motor rightMotorA = motor(PORT15, ratio6_1, true);
motor rightMotorB = motor(PORT16, ratio6_1, false);
motor rightMotorC = motor(PORT17, ratio6_1, true);

motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);

motor cataMotor = motor(PORT21, ratio6_1, false);
motor intakerollerMotor = motor(PORT14, ratio36_1, false);

drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 0.6667);
controller Controller1 = controller(primary);

digital_out endgame = digital_out(Brain.ThreeWirePort.A);
digital_out cataCylinders = digital_out(Brain.ThreeWirePort.B);

distance backDistance = distance(PORT1);
digital_in cataSwitch = digital_in(Brain.ThreeWirePort.C);

inertial inertialSensor = inertial(PORT12);
rotation rotationSensor = rotation(PORT13);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Left Motor 1 ");
  Brain.Screen.print(leftMotorA.temperature(celsius));
  Brain.Screen.newLine();
  Brain.Screen.print("Left Motor 2 ");
  Brain.Screen.print(leftMotorB.temperature(celsius));
  Brain.Screen.newLine();
  Brain.Screen.print("Left Motor 3 ");
  Brain.Screen.print(leftMotorC.temperature(celsius));
  Brain.Screen.newLine();
  Brain.Screen.print("Right Motor 1 ");
  Brain.Screen.print(rightMotorA.temperature(celsius));
  Brain.Screen.newLine();
  Brain.Screen.print("Right Motor 2 ");
  Brain.Screen.print(rightMotorB.temperature(celsius));
  Brain.Screen.newLine();
  Brain.Screen.print("Right Motor 3 ");
  Brain.Screen.print(rightMotorC.temperature(celsius));
  Brain.Screen.newLine();
  Brain.Screen.print("Intake ");
  Brain.Screen.print(intakerollerMotor.temperature(celsius));
  Brain.Screen.newLine();
  Brain.Screen.print("Cata ");
  Brain.Screen.print(cataMotor.temperature(celsius));
  Brain.Screen.newLine();
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  wait(100, msec);
  
}