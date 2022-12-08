#include<cmath>
#include<autonomous/PID.h>

// PID::PID(double P, double I, double D, double maxP, double errorB) {
//   kP = P;
//   kI = I;
//   kD = D;
//   maxPower = std::abs(maxP);
//   errorBound = errorB;
// }

double PID::calculate(double error) {
  achievedTarget = false;
  double p = kP * error + kD * (error - prevError) + kI * totalError;

  if (std::abs(p) > maxPower) {
    p = maxPower * p / std::abs(p);
  }

  if (!((std::abs(p) == maxPower) && ((p / error) > 0))) {
    totalError += error;
  }

  prevError = error;

  if (std::abs(error) < errorBound) {
    totalError = 0.0;
    achievedTarget = true;
  }

  return p;
}

bool PID::atTarget() {
  return achievedTarget;
}

void PID::reset() {
  prevError = 0.0;
  totalError = 0.0;
  achievedTarget = false;
}

double PID::getErrorBound() {
  return errorBound;
}

void PID::setMax(double max) {
  maxPower = max;
}