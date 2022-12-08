#include "math-functions/math-stuff.h"

double transformThetaError(double error) {
  double temp = ((error + 180.0) / 360.0);
  double new_error = (temp - floor(temp)) * 360.0 - 180.0;

  return new_error;
}

double transformTheta(double sensor, double target) {
  while (sensor > target + 180.0 || sensor <= target - 180.0) {
    if (sensor > target + 180.0) {
      sensor -= 180.0;
    } else if (sensor <= target - 180.0) {
      sensor += 180.0;
    }
  }

  return sensor;
}

double dist(double x1, double y1, double x2, double y2) {
  double d = pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0);
  d = pow(d, 0.5);
  
  return d;
}

double rad (double a) {
  return a * M_PI / 180;
}

double degr (double a) {
  return a * 180 / M_PI;
}