//Kushal Jaligama

//Rate Mode uses only Gyro rates for stabilization (acrobatic mode) (flightMode = 0)
//Attitude Mode uses Gyro and Accel for stabilization (flightMode = 1)

//Set P, I, D gains in Variables.h

//---------------//
#include <avr/EEPROM.h>
#include <Wire.h>
#include <Servo.h>
//---------------//

void setup() {
  Serial.begin(115200);
  Serial.flush();
  startUp();
  startTimers();
}

void loop() {
  sensorRead();
  readReceiver();
  stabilize();
  sendSerialData();
  delay(10);
}
