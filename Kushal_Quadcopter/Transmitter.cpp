//
//  Transmitter.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#include "Transmitter.h"

Transmitter::Transmitter() {
  pinMode(2, INPUT);
  for (int i = 4; i <= 8; i++) {
    pinMode(i, INPUT);
  }
  throttle = roll = pitch = yaw = gear = flap = 0;
  armed = false;
}

void Transmitter::read() {
  throttle = getRaw(THROTTLEPIN);
  roll = getRaw(ROLLPIN);
  pitch = getRaw(PITCHPIN);
  yaw = getRaw(YAWPIN);

  (getRaw(GEARPIN) > TRANSMITTERZERO) ? gear = 1 : gear = 0;
  (getRaw(FLAPPIN) > TRANSMITTERZERO) ? flap = 1 : flap = 0;
}

float Transmitter::getThrottle() {
  return throttle;
}

float Transmitter::getRoll() {
  return mapReceiverToDegrees(roll);
}

float Transmitter::getPitch() {
  return mapReceiverToDegrees(pitch);
}

float Transmitter::getYaw() {
  return mapReceiverToDegrees(yaw);
}

short Transmitter::getGear() {
  return gear;
}

short Transmitter::getFlap() {
  return flap;
}

//bool Transmitter::isArmed() {
//  if (throttle < TRANSMITTERMIN && yaw > TRANSMITTERMAX) {
//    armed = true;
//  }
//  else if (throttle < TRANSMITTERMIN && yaw < TRANSMITTERMIN) {
//    armed = false;
//  }
//  return armed;
//}

float Transmitter::mapReceiverToDegrees(unsigned int axis) {
  unsigned int newAxis = constrain(axis, TRANSMITTERMIN, TRANSMITTERMAX);
  float scalar = (TRANSMITTERMAX - TRANSMITTERZERO) / MAXDEGS;
  float error = (newAxis - TRANSMITTERZERO);
  return error / scalar;
}

unsigned int Transmitter::getRaw(int pin) {
  if (digitalRead(pin)) {
    unsigned long start = micros();
    while (digitalRead(pin)) {

    }
    unsigned long out = start - micros();
    return out;
  }
}

void Transmitter::printData() {
  Serial.print("Throttle: ");
  Serial.println(getThrottle());
}
