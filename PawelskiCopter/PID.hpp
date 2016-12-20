//
//  PID.hpp
//  PawelskiCopter
//
//  Created by Kushal Jaligama on 1/22/16.
//  Copyright © 2016 Kushal Jaligama. All rights reserved.
//

#ifndef PID_hpp
#define PID_hpp

#include <stdio.h>
#include "System.hpp"

class PID {
public:
    PID(float P, float I, float D);
    void init();
    float compute(float setpoint, float processVariable);
    void resetIntegral();
private:
    float P, I, D;
    float pTerm, iTerm, dTerm;
    int currentTime, lastTime, timeChange, dT;
    float setpoint, processVariable, error, output;
};

#endif /* PID_hpp */
