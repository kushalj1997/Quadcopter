#include <Wire.h>
#include <Arduino.h>
#include <I2Cdev.h>
#include "IMU.h"

void setup() {
  Wire.begin();
  Serial.begin(57600);
  IMU::init();
}

void loop() {
    IMU::read();
    IMU::printGyroData();
}
