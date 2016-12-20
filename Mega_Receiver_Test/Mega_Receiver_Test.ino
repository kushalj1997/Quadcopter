#include <PinChangeInt.h>

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

unsigned long throttle = 0;
unsigned long roll = 0;
unsigned long pitch = 0;
unsigned long yaw = 0;
unsigned long gear = 0;
unsigned long AUX1 = 0;

void setup() {
  // put your setup code here, to run once:
  PCintPort::attachInterrupt(A8, readRX, CHANGE);
  PCintPort::attachInterrupt(A9, readRX, CHANGE);
  PCintPort::attachInterrupt(A10, readRX, CHANGE);
  PCintPort::attachInterrupt(A11, readRX, CHANGE);
  PCintPort::attachInterrupt(A12, readRX, CHANGE);
  PCintPort::attachInterrupt(A13, readRX, CHANGE);

  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
    delay(100);
    printRXData();
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
  Serial.print(" AUX1: ");
  Serial.println(AUX1);
}
