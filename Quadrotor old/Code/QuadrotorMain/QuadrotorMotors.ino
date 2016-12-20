//Kushal Jaligama

//Quadrotor Motor Function Definitions

/*
        CW  1....Front.....2 CCW
 ......***......
 ......***......
 ......***......
 CCW  4.....Back.....3  CW
 */

#define MOTOR1 3 //Front Left
#define MOTOR2 9 //Front Right
#define MOTOR3 10 //Rear Right
#define MOTOR4 11 //Rear Left

#define MAXANGLE 30.0     // [deg]
#define MAXRATE 180.0     // [deg/s]

#define ESCMAX 2000
#define ESCMIN 1000

#define MAXTHRUST 1850
#define MINTHRUST 1150

unsigned int motorThrust[4] = {
  1000, 1000, 1000, 1000};

float rollCommand = 0;
float pitchCommand = 0;
float yawCommand = 0;

#define PID_UPDATE_INTERVAL 1 // milliseconds

unsigned long lastPIDTime;  // most recent PID update time in ms 

Servo motors[4];

void initMotors() { //Initialize the motors

  motors[0].attach(MOTOR_FRONT_LEFT, ESCMIN, ESCMAX);
  motors[1].attach(MOTOR_FRONT_RIGHT, ESCMIN, ESCMAX);
  motors[2].attach(MOTOR_REAR_LEFT, ESCMIN, ESCMAX);
  motors[3].attach(MOTOR_REAR_RIGHT, ESCMIN, ESCMAX);

  stopAllMotors(); //For calibration purposes

    Serial.println("Motors Initialized");
}

void constrainMotors() { //Ensure all the motors don't exceed limits
  for (int i = 0; i < 4; i++) {
    if (motorThrust[i] > MAXTHRUST)
      motorThrust[i] = MAXTHRUST;
    if (motorThrust[i] < MINTHRUST)
      motorThrust[i] = MINTHRUST;
  }
}

void setThrusts() { //Use PID to calculate speed of each motor
  PIDControl();

  motorThrust[0] = THROTTLE + pitchCommand + rollCommand - yawCommand;  //Front Left
  motorThrust[1] = THROTTLE + pitchCommand - rollCommand + yawCommand;  //Front Right
  motorThrust[2] = THROTTLE - pitchCommand - rollCommand - yawCommand;  //Rear Right
  motorThrust[3] = THROTTLE - pitchCommand + rollCommand + yawCommand;  //Rear Left

  constrainMotors();
}

void writeMotors(int motor, int speed) { //This function writes to the motors themselves
  int fakeAngle = map(speed, ESCMIN, ESCMAX, 0, 180);
  motors[motor].write(fakeAngle);
}

void setSpeed(unsigned int thrust[4]) { //This function assigns each motor its speed
  for (int i = 0; i < 4; i++) {
    writeMotors(i, thrust[i]);
  }
}

void stopAllMotors() { //This funtion stops all motors
  for (int i = 0; i < 4; i++) {
    motorThrust[i] = ESCMIN;
    writeMotors(i, motorThrust[i]);
  }
}

void stabilize(boolean armed) { //Ensures that quadcopter is armed and lets motors be written to
  if (armed == true) {
    setThrusts();
    setSpeed(motorThrust);
  } 
  else {
    stopAllMotors();
    led(false);
  }
}

void PIDControl() { //Does PID calculations
  // This checks for rollover with millis()
  if (millis() < lastPIDTime) {
    lastPIDTime = 0;
  }

  if ((millis() - lastPIDTime) > PID_UPDATE_INTERVAL) {
    lastPIDTime += PID_UPDATE_INTERVAL;

    //led(!ledStatus);

    if (flightMode == 1) {
      rollCommand = computePID(rollTarget, roll);
      pitchCommand = computePID(pitchTarget, pitch);
      yawCommand = computePID(yawTarget, yaw);
    }
    else {
      rollCommand = computePID(rollTarget, gyroX);
      pitchCommand = computePID(pitchTarget, gyroY);
      yawCommand = computePID(yawTarget, gyroZ);
    }
  }
}

void sendMotorDataToSerial() { //Sends motor outputs to serial monitor
  Serial.println("Motor1: Motor2: Motor3: Motor4:");
  Serial.print(motorThrust[0]);
  Serial.print("    ");
  Serial.print(motorThrust[1]);
  Serial.print("    ");
  Serial.print(motorThrust[2]);
  Serial.print("    ");
  Serial.println(motorThrust[3]);
}

