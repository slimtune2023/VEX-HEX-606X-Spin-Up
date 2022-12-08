#include "vex.h"
#include "robot-func/brain-func.h"
#include <string>
#include <string.h>
#include <iostream>

char motor_names[8][13] = {"leftMotorA: ", "leftMotorB: ", "leftMotorC: ", "rightMotorA:", "rightMotorB:", "rightMotorC:", "cataMotor:  ", "intakeMotor:"};
motor motors[8] = {leftMotorA, leftMotorB, leftMotorC, rightMotorA, rightMotorB, rightMotorC, cataMotor, intakerollerMotor};

int len = sizeof(motor_names)/sizeof(motor_names[0]);

void brain_print() {
  Brain.Screen.clearScreen();

  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Motor Name");

  Brain.Screen.setCursor(1, 15);
  Brain.Screen.print("Temp");

  Brain.Screen.setCursor(1, 22);
  Brain.Screen.print("RPM");

  Brain.Screen.setCursor(1, 30);
  Brain.Screen.print("Watts");
  
  for (int i=2; i < len+2; i++) {
    int index = i - 2;

    Brain.Screen.setCursor(i, 1);
    Brain.Screen.print(motor_names[index]);

    Brain.Screen.setCursor(i, 15);
    Brain.Screen.print(motors[index].temperature());

    Brain.Screen.setCursor(i, 22);
    Brain.Screen.print(motors[index].velocity(rpm));

    Brain.Screen.setCursor(i, 30);
    Brain.Screen.print(motors[index].power());
  }

  Brain.Screen.setCursor(len+2, 1);
  Brain.Screen.print("Heading angle: ");

  Brain.Screen.setCursor(len+2, 18);
  Brain.Screen.print(inertialSensor.heading(degrees));
  
}