//
//  LED.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#include "LED.h"
#include <Arduino.h>

LED::LED(int pin) {
  LedPin = pin;
  pinMode(LedPin, OUTPUT);
  isOn = false;
}

void LED::on() {
  isOn = true;
  digitalWrite(LedPin, HIGH);
}
void LED::off() {
  isOn = false;
  digitalWrite(LedPin, LOW);
}

boolean LED::state() {
  return isOn;
}
