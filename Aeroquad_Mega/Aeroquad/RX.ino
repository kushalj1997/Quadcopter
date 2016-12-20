// RX

#include <PinChangeInt.h>

// Transmitter max values
#define TXMIN 1076
#define TXMID 1476
#define TXMAX 1876

float ch1, ch2, ch3, ch4, ch5;         // RC channel inputs

unsigned long throttleTimer = micros();
unsigned long rollTimer = micros();
unsigned long pitchTimer = micros();
unsigned long yawTimer = micros();
unsigned long gearTimer = micros();
unsigned long AUX1Timer = micros();

uint8_t lastThrottleState = 0;
uint8_t lastRollState = 0;
uint8_t lastPitchState = 0;
uint8_t lastYawState = 0;
uint8_t lastGearState = 0;
uint8_t lastAUX1State = 0;

unsigned int throttle = 0;
unsigned int roll = 0;
unsigned int pitch = 0;
unsigned int yaw = 0;
unsigned int gear = 0;
unsigned int AUX1 = 0;

void initRX() {
  PCintPort::attachInterrupt(A8, readRX, CHANGE);
  PCintPort::attachInterrupt(A9, readRX, CHANGE);
  PCintPort::attachInterrupt(A10, readRX, CHANGE);
  PCintPort::attachInterrupt(A11, readRX, CHANGE);
  PCintPort::attachInterrupt(A12, readRX, CHANGE);
  PCintPort::attachInterrupt(A13, readRX, CHANGE);

  Serial.println("RX initialized");
}

void readRX() {
  if (lastThrottleState == 0 && (PINK & B00000001) ) {
    lastThrottleState = 1;
    throttleTimer = micros();
  } else if (lastThrottleState == 1 && !(PINK & B00000001) ) {
    lastThrottleState = 0;
    throttle = micros() - throttleTimer;
  }

  if (lastRollState == 0 && (PINK & B00000010) ) {
    lastRollState = 1;
    rollTimer = micros();
  } else if (lastRollState == 1 && !(PINK & B00000010) ) {
    lastRollState = 0;
    roll = micros() - rollTimer;
  }

  if (lastPitchState == 0 && (PINK & B00000100) ) {
    lastPitchState = 1;
    pitchTimer = micros();
  } else if (lastPitchState == 1 && !(PINK & B00000100) ) {
    lastPitchState = 0;
    pitch = micros() - pitchTimer;
  }
  if (lastYawState == 0 && (PINK & B00001000) ) {
    lastYawState = 1;
    yawTimer = micros();
  } else if (lastYawState == 1 && !(PINK & B00001000) ) {
    lastYawState = 0;
    yaw = micros() - yawTimer;
  }
  if (lastGearState == 0 && (PINK & B00010000) ) {
    lastGearState = 1;
    gearTimer = micros();
  } else if (lastGearState == 1 && !(PINK & B00010000) ) {
    lastGearState = 0;
    gear = micros() - gearTimer;
  }
  if (lastAUX1State == 0 && (PINK & B00100000) ) {
    lastAUX1State = 1;
    AUX1Timer = micros();
  } else if (lastAUX1State == 1 && !(PINK & B00100000) ) {
    lastAUX1State = 0;
    AUX1 = micros() - AUX1Timer;
  }
}

int TOPTHAngle = 0;

void checkArmed() {
  if (override) {
    armed = true;
  } else {
    if (throttle <= MINARM && yaw <= 1160)
      armed = false;
    else if (throttle <= MINARM && yaw >= 1860)
      armed = true;
  }

}

#define SENSITIVITY .75

void processRXData() {
  checkArmed();

  flapSwitch = (AUX1 < MIDTH) ? 0 : 1;
  autoLevel = flapSwitch;
  TOPTHAngle = (autoLevel) ? 25 : 100;
  thrust = constrain(map(throttle, 1032, 1856, BOTTH, TOPTH), BOTTH, TOPTH);
  RXPitchAngleSet = SENSITIVITY * -constrain(deadBand(map(pitch, 1148, 1902, -TOPTHAngle, TOPTHAngle)) , -TOPTHAngle, TOPTHAngle);
  RXrollAngleSet = SENSITIVITY * constrain(deadBand(map(roll, 1060, 1956, -TOPTHAngle, TOPTHAngle)) , -TOPTHAngle, TOPTHAngle);
  RXYawAngleSet = SENSITIVITY * -constrain(deadBand(map(yaw, 1056, 1932, -TOPTHAngle, TOPTHAngle)) , -TOPTHAngle, TOPTHAngle);
  gearSwitch = (gear < MIDTH) ? 0 : 1;
}

#define DEADBAND 6

float deadBand(float x) {
  if (abs(x) < DEADBAND) {
    return 0;
  } else {
    if (x < 0) {
      x = TOPTHAngle * (x + DEADBAND) / (TOPTHAngle - DEADBAND);
      return x;
    } else {
      x = TOPTHAngle  * (x - DEADBAND) / (TOPTHAngle - DEADBAND);
      return x;
    }
  }
}

void printRXData() {
  Serial.print("Throttle: ");
  Serial.print(throttle);
  Serial.print(" Roll: ");
  Serial.print(roll);
  Serial.print(" Pitch: ");
  Serial.print(pitch);
  Serial.print(" Yaw: ");
  Serial.print(yaw);
  Serial.print(" Gear: ");
  Serial.print(gear);
  Serial.print(" Flap: ");
  Serial.println(AUX1);
}

void printProcessedRXData() {
  Serial.print("Thrust: ");
  Serial.print(thrust);
  Serial.print(" Pitch Angle: ");
  Serial.print(RXPitchAngleSet);
  Serial.print(" Roll Angle: ");
  Serial.print(RXrollAngleSet);
  Serial.print(" Yaw Angle: ");
  Serial.print(RXYawAngleSet);
  Serial.print(" Gear Switch: ");
  Serial.print(gearSwitch);
  Serial.print(" Flap Switch: ");
  Serial.println(flapSwitch);
}

