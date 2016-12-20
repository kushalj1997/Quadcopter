//
//  Quadrotor.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#include "Quadrotor.h"

Quadrotor::Quadrotor() {
  // Motors
  frontLeft = new Motor(3);
  frontRight = new Motor(9);
  rearRight = new Motor(10);
  rearLeft = new Motor(11);

  // Transmitter
  // Aeroquad Transmitter Code, uses interrupts
//  initializeReceiver(6);
//  receiverXmitFactor = 1.0;

  // IMU (Inertial Measurement Unit)

  // PID's
  //  rollPID = new PID();
  //  pitchPID = new PID();
  //  yawPID = new PID();

  // Arm the quad
  armed = false;
}

void Quadrotor::stabilize() {
  IMU::read();
  //IMU::printGyroData();
  IMU::printAccelData();

//  readReceiver();
//
//  if (receiverCommand[THROTTLE] < MINCOMMAND && receiverCommand[ZAXIS] < MINCOMMAND) {
//    armed = false;
//  } else if (receiverCommand[THROTTLE] < MINCOMMAND && receiverCommand[ZAXIS] > MAXCOMMAND) {
//    armed = true;
//  }

  if (armed) {
//    frontLeft->run(receiverCommand[THROTTLE]);
//    frontRight->run(receiverCommand[THROTTLE]);
//    rearRight->run(receiverCommand[THROTTLE]);
//    rearLeft->run(receiverCommand[THROTTLE]);
  }
  else {
    killAllMotors();
  }
}

void Quadrotor::corrections() {

}

void Quadrotor::commandAllMotors(unsigned int speed) {
  frontLeft->run(speed);
  frontRight->run(speed);
  rearRight->run(speed);
  rearLeft->run(speed);
}

void Quadrotor::killAllMotors() {
  frontLeft->kill();
  frontRight->kill();
  rearRight->kill();
  rearLeft->kill();
}
