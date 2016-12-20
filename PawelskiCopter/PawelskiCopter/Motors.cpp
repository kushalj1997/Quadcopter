//
//  Motors.cpp
//  PawelskiCopter
//
//  Created by Kushal Jaligama on 1/28/16.
//  Copyright © 2016 Kushal Jaligama. All rights reserved.
//

#include "Motors.hpp"

void writeMotors(float throttle, float rollCorrection,
                 float pitchCorrection, float yawCorrection) {
    
    // Not sure which hardware pins used for motors yet
    // Have to wait for hardware to do this, but the math is ready
    // PWM
    
    // m1 = front left
    // m2 = front right
    // m3 = back left
    // m4 = back right
    
    // motor 1 = throttle + rollCorrection + pitchCorrection + yawCorrection;
    // motor 2 = throttle - rollCorrection + pitchCorrection - yawCorrection;
    // motor 3 = throttle + rollCorrection - pitchCorrection - yawCorrection;
    // motor 4 = throttle - rollCorrection - pitchCorrection + yawCorrection;
}