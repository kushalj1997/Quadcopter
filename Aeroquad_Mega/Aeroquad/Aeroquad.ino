#include <Arduino.h>
#include "Globals.h"

unsigned long oneHz = 0;
unsigned long tenHz = 0;
unsigned long hundHz = 0;
unsigned long twoFiftyHz = 0;
unsigned long loopTime = 0;

void setup() {
  // put your setup code here, to run once:
  initMotors();
  initPID();
  initSerial();
  initLEDs();
  initIMU();
  initRX();
  Serial.println("All Initialized, in loop");
  Serial.println();
}

void loop() {
  // Max Speed

  // --------------------------------------- \\
  
  // 250 Hz
  if (millis() - twoFiftyHz >= 4) {
    readIMU();
    stabilize(); // PID Loops are internally run at 100 Hz
  }

  // 100 Hz
  if (millis() - hundHz >= 10) {
    processRXData();
    processLEDs();

    hundHz = millis();
  }

  // 10 Hz
  if (millis() - tenHz >= 100) {

    acceptSerialCommands();
    checkSerialToggles();

    debugLoop();

    tenHz = millis();
  }

  // 1 Hz
  if (millis() - oneHz >= 1000) {

    oneHz = millis();
  }

   // --------------------------------------- \\
}

void debugLoop() {
  //  printGyroData();
  //  printAccelData();
  //  printBaroData();
  //  printRXData();
  //  printProcessedRXData();
  //  printMotorOutputs();
  //  printPIaccroDs();
}
