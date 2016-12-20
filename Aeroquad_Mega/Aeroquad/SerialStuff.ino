//Serial Stuff

void initSerial() {
  Serial.begin(38400);
  Serial.println("Serial Communication Initialized");
  Serial.println("Enter ? to see Help Menu");
}

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

void updateGains() {
  accroP = readFloat(PADD);
  accroI = readFloat(IADD);
  accroD = readFloat(DADD);

  rollPID.SetTunings(accroP, accroI, accroD);
  pitchPID.SetTunings(accroP, accroI, accroD);

  yawP = readFloat(YAWP);
  yawI = readFloat(YAWI);
  yawD = readFloat(YAWD);

  yawPID.SetTunings(yawP, yawI, yawD);

  autoLevelP = readFloat(ALADDP);
  autoLevelI = readFloat(ALADDI);
  autoLevelD = readFloat(ALADDD);

  rollAutoLevel.SetTunings(autoLevelP, autoLevelI, autoLevelD);
  pitchAutoLevel.SetTunings(autoLevelP, autoLevelI, autoLevelD);

  headingP = readFloat(HEADINGP);
  headingI = readFloat(HEADINGI);
  headingD = readFloat(HEADINGD);

  headingHoldControl.SetTunings(headingP, headingI, headingD);
}

void checkSerialToggles() {
  if (printSensorData)
    printIMUData();
  if (printMotorData)
    printMotorOutputs();
  if (printPIDData) {
    printPIDGains();
    printPIDData = false;
  }
  if (printReceiverData) {
    printRXData();
  }
  if (printCommandAngles) {
    printProcessedRXData();
  }
}

void gainChangeHelper(char gain) {
  // Ask user which axis
  Serial.println("Which Axis? 0 for Accro Roll/Pitch, 1 for Accro Yaw, 2 for Auto Level Roll/Pitch, 3 for Heading Hold, 4 for Altitude Hold");

  int whichaxis;
  // Wait for user to choose
  while (!Serial.available());
  whichaxis = processSerialBuffer();

  // Determine which gain
  int whichgain;
  switch (gain) {
    case 'P':
      whichgain = 0;
      break;
    case 'I':
      whichgain = 1;
      break;
    case 'D':
      whichgain = 2;
      break;
    default:
      Serial.println("invalid gain passed through, CODING ERROR");
      break;
  }

  // Wait for user to type the new gain
  Serial.print("Enter the gain: ");
  while (!Serial.available());
  double usergain = processSerialBuffer();

  Serial.print("The ");
  Serial.print(gain);

  switch (whichaxis) {
    case 0:
      Serial.print(" gain for Accro Roll/Pitch is set to ");
      break;
    case 1:
      Serial.print(" gain for Accro Yaw is set to ");
      break;
    case 2:
      Serial.print(" gain for Auto Level Roll/Pitch is set to ");
      break;
    case 3:
      Serial.print(" gain for Heading Hold is set to ");
      break;
    case 4:
      Serial.print(" gain for Altitude Hold is set to ");
      break;
    default:
      Serial.print(" gain will not be written, invalid axis chosen!! The axis chosen was: ");
      Serial.println(whichaxis);
      Serial.print("The gain entered was: ");
      break;
  }
  Serial.println(usergain);

  // Put the gain into EEPROM and update PID instances
  writeFloat(usergain, gainArray[whichaxis][whichgain]);
  updateGains();
}

void acceptSerialCommands() {
  if (Serial.available()) {
    char c = Serial.read();
    switch (toupper(c)) {
      case 'A':
        override = !override;
        Serial.print("Override is ");
        (override) ? Serial.println("ON - BE CAREFUL") : Serial.println("OFF - CHECK TRANSMITTER TO SEE IF ARMED");
        break;
      case 'P':
        gainChangeHelper('P');
        break;
      case 'I':
        gainChangeHelper('I');
        break;
      case 'D':
        gainChangeHelper('D');
        break;
      case 'S':
        printSensorData = !printSensorData;
        break;
      case 'M':
        printMotorData = !printMotorData;
        break;
      case 'G':
        printPIDData = !printPIDData;
        break;
      case 'R':
        printReceiverData = !printReceiverData;
        break;
      case 'C':
        printCommandAngles = !printCommandAngles;
        break;
      case '?':
        Serial.println("HELP MENU:");
        Serial.println("Enter C to get the Commanded Angles/Rates");
        Serial.println("Enter R to get the Raw Transmitter Data");
        Serial.println("Enter G to get the PID Gains");
        Serial.println("Enter M to get the Motor Outputs");
        Serial.println("Enter S to get the Sensor Data");
        Serial.println("Enter P, I, or D to change the respective gains.");
        Serial.println();
        break;
      default:
        break;
    }
  }
}
