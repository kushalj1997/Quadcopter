// Flight Stabilizer

// PID for AccroMode, Roll/Pitch, 250 Quad is P: 3, I: 45, D: 0.02
/*

  Accro Mode: Pitch and Roll
  P: 3.00 I: 35.00 D: 0.20

  Accro Mode: Yaw
  P: 2.00 I: 35.00 D: 0.00

*/

#include <PID_v1.h>

void initPID() {
  updateGains();
}

void stabilize() {
  if (!armed) {
    rollPID.ResetIntegral();
    pitchPID.ResetIntegral();
    yawPID.ResetIntegral();
  }

  if (autoLevel) {
    // Calculate theta outputs
    rollAutoLevel.Compute();
    pitchAutoLevel.Compute();
  } else {
    // Nesting of PID's is done here
    // Since auto level is off, we pass the command angle directly to the variable
    // Bypass the auto level PID
    rollTheta = RXrollAngleSet;
    pitchTheta = RXPitchAngleSet;
  }

  if (headingHold) {
    headingHoldControl.Compute();
  } else {
    // Nesting of PID's is done here
    // Since heading hold is off, we pass the command angle directly to the variable
    // Bypass the heading hold PID
    yawTheta = RXYawAngleSet;
  }

  // Calculate final omega outputs
  rollPID.Compute();
  pitchPID.Compute();
  yawPID.Compute();

  if (thrust < MINARM) {
    rollPID.ResetIntegral();
    pitchPID.ResetIntegral();
    yawPID.ResetIntegral();
  }

  motorCommand[0] = thrust + pitchOmega + rollOmega + yawOmega;
  motorCommand[1] = thrust + pitchOmega - rollOmega - yawOmega;
  motorCommand[2] = thrust - pitchOmega - rollOmega + yawOmega;
  motorCommand[3] = thrust - pitchOmega + rollOmega - yawOmega;

  for (int i = 0; i < 4; i++) {
    motorCommand[i] = constrain(motorCommand[i], MINARM, TOPTH);
  }

  (armed) ? writeMotors() : commandAllMotors(BOTTH);
}

void printMotorOutputs() {
  Serial.print(" FL: ");
  Serial.print(motorCommand[0]);
  Serial.print(" FR: ");
  Serial.print(motorCommand[1]);
  Serial.print(" RR: ");
  Serial.print(motorCommand[2]);
  Serial.print(" RL: ");
  Serial.print(motorCommand[3]);
  Serial.print(" \t Pitch Output: ");
  Serial.print(pitchOmega);
  Serial.print(" Roll Output: ");
  Serial.print(rollOmega);
  Serial.print(" Yaw Output: ");
  Serial.println(yawOmega);
}

void printPIDGains() {
  Serial.println();
  Serial.println("The PID Gains");
  Serial.println();

  Serial.println("Accro Mode: Pitch and Roll");
  Serial.print("P: ");
  Serial.print(accroP);
  Serial.print(" I: ");
  Serial.print(accroI);
  Serial.print(" D: ");
  Serial.println(accroD);

  Serial.println();

  Serial.println("Accro Mode: Yaw");
  Serial.print("P: ");
  Serial.print(yawP);
  Serial.print(" I: ");
  Serial.print(yawI);
  Serial.print(" D: ");
  Serial.println(yawD);

  Serial.println();

  Serial.println("Auto Level Mode: Pitch and Roll");
  Serial.print("P: ");
  Serial.print(autoLevelP);
  Serial.print(" I: ");
  Serial.print(autoLevelI);
  Serial.print(" D: ");
  Serial.println(autoLevelD);

  Serial.println();

  Serial.println("Heading Hold");
  Serial.print("P: ");
  Serial.print(headingP);
  Serial.print(" I: ");
  Serial.print(headingI);
  Serial.print(" D: ");
  Serial.println(headingD);

  Serial.println();
}
