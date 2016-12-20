//
//  PID.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 2/15/15.
//
//

#include "PID.h"

PID::PID(double kP, double kI, double kD){
    _kP = kP;
    _kI = kI;
    _kD = kD;
    _setpoint = _lastPV = _processVariable = _iSum = _lastTime = 0;
}

double PID::compute(double setPoint, double processVariable){
    float DT = (millis()-_lastTime)/1000;
    _lastTime = millis();
    
    _setpoint = setPoint;
    _processVariable = processVariable;
    
    // Error calculation, along with integral accumulation
    double error = _setpoint - _processVariable;
    _iSum += error*DT;
    
    // Derivative Kick Elimination
    double dPV = (_processVariable - _lastPV)/DT;
    _lastPV = _processVariable;
    
    // Put it all together
    double pterm = _kP*error;
    double iterm = _kI*_iSum;
    double dterm = _kD*dPV;
    
    return pterm + iterm - dterm;
}

void PID::setGains(double kP, double kI, double kD){
    _kP = kP;
    _kI = kI;
    _kD = kD;
}

double[] PID::getGains(){
    
}
