//
//  Motor.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#include "Motor.h"

Motor::Motor(int pin) {
  ESC.attach(pin, 1000, 2000);
  kill();
}

void Motor::run(int speed) {
  //unsigned int pulseWidth = map(speed, 1, 100, 1100, 2000);
  float output = constrain(speed, 1100, 1500);
  ESC.writeMicroseconds(output);
}

void Motor::kill() {
  ESC.writeMicroseconds(1000);
}
