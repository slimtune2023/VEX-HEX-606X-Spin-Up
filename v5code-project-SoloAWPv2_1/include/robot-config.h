using namespace vex;


// VEXcode device constructors

extern brain Brain;

extern motor leftMotorA;
extern motor leftMotorB;
extern motor leftMotorC;

extern motor rightMotorA;
extern motor rightMotorB;
extern motor rightMotorC;

extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

extern motor cataMotor;
extern motor intakerollerMotor;

extern drivetrain Drivetrain;
extern controller Controller1;

extern digital_out endgame;
extern digital_out cataCylinders;

extern distance backDistance;
extern digital_in cataSwitch;

extern inertial inertialSensor;
extern rotation rotationSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );