//
//  SerialFunctions.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/11/15.
//
//

#ifndef Kushal_Quadcopter_SerialFunctions_h
#define Kushal_Quadcopter_SerialFunctions_h

#include "Variables.h"

float processSerialBuffer() {
  char inData[10];
  uint8_t index = 0;
  while (Serial.available()) {
    delay(5);
    char aChar = Serial.read();
    inData[index++] = aChar; // Add the character to the array
  }
  inData[index] = '\0'; // NULL terminate the array
  Serial.println(inData);
  return atof(inData);
}

boolean printReceiverData = false;

void togglePrintReceiverData() {
  printReceiverData = !printReceiverData;
}

void updateGains() {
  pgain = readFloat(PADD);
  igain = readFloat(IADD);
  dgain = readFloat(DADD);
  rollPID->SetTunings(pgain, igain, dgain);
  pitchPID->SetTunings(pgain, igain, dgain);
  yawPID->SetTunings(0, 0, 0);
}

void printReceiverOutputs() {
  Serial.print("Throttle: ");
  Serial.print(rxCmd[THROTTLE]); // Throttle
  Serial.print(" Yaw: ");
  Serial.print(rxCmd[ZAXIS]); // Yaw
  Serial.print(" Roll: ");
  Serial.print(rxCmd[XAXIS]); // Roll
  Serial.print(" Pitch: ");
  Serial.print(rxCmd[YAXIS]); // Pitch
  Serial.print(" Mode: ");
  Serial.print(rxCmd[MODE]); // Mode
  Serial.print(" AUX1: ");
  Serial.println(rxCmd[AUX1]); // Auxillary
}

boolean printSensorData = false;

void togglePrintSensorData() {
  printSensorData = !printSensorData;
}

boolean printMotorData = false;

void togglePrintMotorData() {
  printMotorData = !printMotorData;
}

void printMotorOutputs() {
  Serial.print(frontLeftCmd);
  Serial.print(" --- ");
  Serial.print(frontRightCmd);
  Serial.print(" --- ");
  Serial.print(rearRightCmd);
  Serial.print(" --- ");
  Serial.println(rearLeftCmd);
}

boolean printPID = false;

void togglePIDGains() {
  printPID = !printPID;
}

void printPIDGains() {
  Serial.print("P: ");
  Serial.print(pgain);
  Serial.print(" I: ");
  Serial.print(igain);
  Serial.print(" D: ");
  Serial.println(dgain);
}

void acceptSerialCommands() {
  // Serial.println("Waiting for gains");
  if (Serial.available()) {
    char c = Serial.read();
    switch (tolower(c)) {
        static boolean printSensor = false;
      case 'p':
        Serial.println("Enter the P gain");
        while (!Serial.available());
        writeFloat(processSerialBuffer(), PADD);
        updateGains();
        Serial.println("The P gain has been written");
        break;
      case 'i':
        Serial.println("Enter the I gain");
        while (!Serial.available());
        writeFloat(processSerialBuffer(), IADD);
        updateGains();
        Serial.println("The I gain has been written");
        break;
      case 'd':
        Serial.println("Enter the D gain");
        while (!Serial.available());
        writeFloat(processSerialBuffer(), DADD);
        updateGains();
        Serial.println("The D gain has been written");
        break;
      case 's':
        togglePrintSensorData();
        break;
      case 'm':
        togglePrintMotorData();
        break;
      case 'g':
        togglePIDGains();
        break;
      case 'r':
        togglePrintReceiverData();
        break;
      default:
        break;
    }
  }
}

#endif
