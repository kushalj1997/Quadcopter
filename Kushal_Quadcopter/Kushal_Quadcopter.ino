// Kushal Jaligama

// It's quadcopter time.

#include <stdio.h>
#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <AQMath.h>
#include <GlobalDefined.h>
#include <Receiver.h>
#include <Receiver_MEGA.h>
#include <PID_v1.h>
#include <Kalman.h>

#include "Includes.h"

void setup() {
  // Begin Serial Comm
  Serial.begin(115200);
  Serial.flush();
  Serial.println("Serial Bus Started");
  Serial.println("Starting Up");

  // Start I2C Bus
  Wire.begin();
  Wire.flush();

  // Motors
  frontLeft = new Motor(3);
  frontRight = new Motor(9);
  rearRight = new Motor(10);
  rearLeft = new Motor(11);

  frontLeftCmd = 0;
  frontRightCmd = 0;
  rearRightCmd = 0;
  rearLeftCmd = 0;

  delay(1000);
  Serial.println("ESC's and Motors Ready");

  greenLED.on();

  // Get the PID gains from EEPROM
  pgain = readFloat(PADD);
  igain = readFloat(IADD);
  dgain = readFloat(DADD);

  rollPID = new PID(&IMUroll, &rollOutput, &rollTarget, pgain, igain, dgain, DIRECT);
  pitchPID = new PID(&IMUpitch, &pitchOutput, &pitchTarget, pgain, igain, dgain, DIRECT);
  yawPID = new PID(&IMUyaw, &yawOutput, &yawTarget, pgain, igain, dgain, DIRECT);

  // To Enable PID
  rollPID->SetMode(AUTOMATIC);
  rollPID->SetOutputLimits(-500, 500);
  pitchPID->SetMode(AUTOMATIC);
  pitchPID->SetOutputLimits(-500, 500);
  yawPID->SetMode(AUTOMATIC);
  yawPID->SetOutputLimits(-500, 500);

  Serial.println("PID ready");

  // Transmitter
  // Aeroquad Transmitter Code, uses interrupts
  initializeReceiver(6);
  receiverXmitFactor = 1.0;
  Serial.println("TX/RX Ready");

  // Initialize gyroscope and accelerometer
  IMU::init();
  Serial.println("IMU and Sensors Ready");

  // Make sure quad is disabled
  armed = false;
  Serial.println("Quadcopter Disabled");

  Serial.println("In Loop");
}

void loop() {

  currentTime = micros();
  deltaTime = currentTime - previousTime;

  // ================================================================
  // 100Hz task loop
  // ================================================================
  if (deltaTime >= 10000) {
    frameCounter++;
    process100HzTask();

    // ================================================================
    // 50Hz task loop
    // ================================================================

    if (frameCounter % 2 == 0) {  //  50 Hz tasks
      process50HzTask();
    }

    if (frameCounter % 10 == 0) { // 10 Hz tasks
      process10HzTask();
    }
    previousTime = currentTime;
  }
  if (frameCounter >= 500) {
    frameCounter = 0;
  }
}

void process100HzTask() {

  IMU::read(flightMode);
  IMUroll = IMU::getRoll();
  IMUpitch = IMU::getPitch();
  IMUyaw = IMU::getYaw();

  rollPID->Compute();
  pitchPID->Compute();
  yawPID->Compute();

  (armed) ? applyFlightMotorCommands() : killAllMotors();
}

void process50HzTask() {
  readReceiver();
  processReceiver();

  checkArmedStatus();
}

void process10HzTask() {
  updateLEDs();
  acceptSerialCommands();
  if (printSensorData)
    IMU::printData();
  if (printMotorData)
    printMotorOutputs();
  if (printPID)
    printPIDGains();
  if (printReceiverData) {
    printReceiverOutputs();
  }

}

void checkArmedStatus() {
  if (receiverCommand[THROTTLE] <= MINCOMMAND && rxCmd[ZAXIS] <= MINCOMMAND)
    armed = false;
  else if (receiverCommand[THROTTLE] <= MINCOMMAND && receiverCommand[ZAXIS] >= MAXCOMMAND)
    armed = true;
}

void applyFlightMotorCommands() {
  frontLeftCmd = rxCmd[THROTTLE] - pitchOutput + rollOutput - yawOutput;
  frontRightCmd = rxCmd[THROTTLE] - pitchOutput - rollOutput + yawOutput;
  rearRightCmd = rxCmd[THROTTLE] + pitchOutput - rollOutput - yawOutput;
  rearLeftCmd = rxCmd[THROTTLE] + pitchOutput + rollOutput + yawOutput;

  constrain(frontLeftCmd, MINCOMMAND, MAXCOMMAND);
  constrain(frontRightCmd, MINCOMMAND, MAXCOMMAND);
  constrain(rearRightCmd, MINCOMMAND, MAXCOMMAND);
  constrain(rearLeftCmd, MINCOMMAND, MAXCOMMAND);

  frontLeft->run(frontLeftCmd);
  frontRight->run(frontRightCmd);
  rearRight->run(rearRightCmd);
  rearLeft->run(rearLeftCmd);
}

void commandAllMotors(unsigned int speed) {
  frontLeft->run(speed);
  frontRight->run(speed);
  rearRight->run(speed);
  rearLeft->run(speed);
}

void killAllMotors() {
  frontLeft->kill();
  frontRight->kill();
  rearRight->kill();
  rearLeft->kill();
}

void processReceiver() {
  // Constrain the receiver to the min and max commands
  // Also map the receiver values to degrees
  // Check which flight mode we are in
  for (int i = 0; i < 6; i++) {
    mapTX(receiverCommand[i], 1074, 1874, 1000, 2000);
    rxCmd[i] = constrain(receiverCommand[i], TXMIN, TXMAX);
  }

  rollTarget = mapTX(rxCmd[XAXIS], TXMIN, TXMAX, -MAXANGLE, MAXANGLE);
  if (abs(rollTarget) <= 1) rollTarget = 0;
  pitchTarget = mapTX(rxCmd[YAXIS], TXMIN, TXMAX, -MAXANGLE, MAXANGLE);
  if (abs(pitchTarget) <= 1) pitchTarget = 0;
  yawTarget = mapTX(rxCmd[ZAXIS], TXMIN, TXMAX, -MAXANGLE, MAXANGLE);
  if (abs(yawTarget) <= 1) yawTarget = 0;

  lastFlightMode = flightMode;

  flightMode = (receiverCommand[MODE] > MIDCOMMAND) ? 1 : 0;
  if (flightMode != lastFlightMode)
    Serial.println("Switched!");
}

float mapTX(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void updateLEDs() {
  //Indicate Armed Status
  (armed) ? greenLED.on() : greenLED.off();
  (armed) ? redLED.off() : redLED.on();
}
