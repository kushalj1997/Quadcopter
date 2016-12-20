//
//  PID.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 2/15/15.
//
//

#ifndef __Kushal_Quadcopter__PID__
#define __Kushal_Quadcopter__PID__

#include <Arduino.h>
#include <stdio.h>

// PID Constants
#define MAXOUTPUT 1900
#define MINOUTPUT 1100
#define MAXRATE 15 // degrees/s
#define MAXANGLE 30 // degrees

class PID {
public:
    PID(double kP, double kI, double kD);
    double compute(double setPoint, double processVariable);
    void resetIntegralAccum();
    void setGains(double kP, double kI, double kD);
    double[] getGains();
private:
    double _kP, _kI, _kD;
    double _setpoint;
    double _processVariable, _lastPV;
    double _iSum;
    unsigned int _lastTime;
};


#endif /* defined(__Kushal_Quadcopter__PID__) */
