//
//  PID.cpp
//  PawelskiCopter
//
//  Created by Kushal Jaligama on 1/22/16.
//  Copyright © 2016 Kushal Jaligama. All rights reserved.
//

#include "PID.hpp"

PID::PID(float P, float I, float D) {
    this->P = P;
    this->I = I;
    this->D = D;
    this->pTerm = this->iTerm = this->dTerm = 0;
    this->currentTime = this->lastTime =
    this->lastTime = this->dT = 0;
    this->setpoint = this->processVariable =
    this->error = this->output = 0;
}

void PID::init() {
    
}

float compute(float setpoint, float processVariable) {
    this->currentTime = systemTimer();
    this->timeChange = this->currentTime - this->lastTime;
    this->dT = this->timeChange/1000;
    if (this->timechange > 4) {
        this->setpoint = setpoint;
        this->processVariable = processVariable;
        this->error = this->setpoint - this->processVariable;
        this->pTerm = this->P * this->error;
        this->iTerm += error;
        this->dTerm = this->D * this->error;
        this->output = this->pTerm + this->iTerm*dT + this->dTerm/dt;
    }
    
    return this->output;
}

void resetIntegral() {
    this->iTerm = 0;
}