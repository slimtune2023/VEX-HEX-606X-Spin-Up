#ifndef _PID_


#define _PID_

class PID {

  public:
    PID(double P, double I, double D, double maxP, double errorB) : kP(P), kI(I), kD(D), maxPower(maxP > 0 ? maxP : -maxP), errorBound(errorB) {};
    double calculate(double error);
    bool atTarget();
    void reset();
    double getErrorBound();
    void setMax(double max);
  
  private:
    double kP;
    double kD;
    double kI;

    double maxPower;

    double prevError = 0.0;
    double totalError = 0.0;

    double errorBound;
    bool achievedTarget = false;

};

#endif // _PID_