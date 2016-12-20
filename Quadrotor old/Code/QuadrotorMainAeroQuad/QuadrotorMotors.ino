#define MOTOR_PWM_Timer
#define NB_MOTOR_CONFIG FOUR_Motors
#include <Motors_PWM_Timer.h>  

#define MOTOR1 2
#define MOTOR2 3
#define MOTOR3 5
#define MOTOR4 6

#define KP 0.8
#define KI 0
#define KD .05

#define WINDUP_GUARD_GAIN 50.0
float iState = 0;
float lastValue = 0;

float pTerm, iTerm, dTerm;

#define MAXANGLE 30.0     // [deg]
#define MAXRATE 180.0     // [deg/s]

#define MOTORMAX 2000
#define MOTORMIN 1000

#define THROTTLE 1700

double pitchError = 0.0;
double rollError = 0.0;
double yawError = 0.0;

void printMotorOutputs(){
    Serial.println(motorCommand[0]);
    Serial.println(" ");
    Serial.println(motorCommand[1]);
    Serial.println(" ");
    Serial.println(motorCommand[2]);
    Serial.println(" ");
    Serial.println(motorCommand[3]);
    Serial.println("\n");
}
void setMotors(){
  PIDCorrection();
  for (int motorTrust = MOTORMIN; motorTrust < THROTTLE; motorTrust+=10) {
    sensorRead();
    PIDCorrection();
    motorCommand[0] = motorTrust - pitchError + rollError - yawError;
    motorCommand[1] = motorTrust - pitchError - rollError + yawError;
    motorCommand[2] = motorTrust + pitchError - rollError - yawError;
    motorCommand[3] = motorTrust + pitchError + rollError + yawError;
    writeMotors();
    delay(200);
  }
  for (int motorTrust = THROTTLE; motorTrust > MOTORMIN; motorTrust-=10) {
    sensorRead();
    PIDCorrection();
    motorCommand[0] = motorTrust - pitchError + rollError - yawError;
    motorCommand[1] = motorTrust - pitchError - rollError + yawError;
    motorCommand[2] = motorTrust + pitchError - rollError - yawError;
    motorCommand[3] = motorTrust + pitchError + rollError + yawError;
    writeMotors();
    delay(200);
  }

  for(int i = 0; i < 4; i++){
    if (motorCommand[i] > MOTORMAX) {
      motorCommand[i] = MOTORMAX;
    }
    if (motorCommand[i] < MOTORMIN) {
      motorCommand[i] = MOTORMIN;
    }
  }
}

void stopAllMotors(){
  motorCommand[0] = 1000;
  motorCommand[1] = 1000;
  motorCommand[2] = 1000;
  motorCommand[3] = 1000;
  writeMotors();
  digitalWrite(13, LOW);
}

void stabilize(){
  setMotors();
  printMotorOutputs();
}

void PIDCorrection(){
  
  // I need to add the algorithms similar to this: 
  
  // in the link, it uses both gyro and accelerometer for stabilization
  pitchError = updatePID(0, getPitch()*.8); 
  rollError = updatePID(0, getRoll()*.8);
  yawError =  updatePID(0, getGyroYaw()*.8); //KP*(0-getGyroYaw()) + KD*(getGyroYaw()/MAXRATE)
  
}
float updatePID(float setPoint, float processVariable)
{
  // this function has been taken from http://www.arduino.cc/playground/Main/BarebonesPIDForEspresso
  double result;
  float error;
  float windupGaurd;

  // determine how badly we are doing
  error = setPoint - processVariable;

  // the pTerm is the view from now, the KP judges 
  // how much we care about error we are this instant.
  pTerm = KP * error;

  // iState keeps changing over time; it's 
  // overall "performance" over time, or accumulated error
  iState += error;

  // to prevent the iTerm getting huge despite lots of 
  //  error, we use a "windup guard" 
  // (this happens when the machine is first turned on and
  // it cant help be cold despite its best efforts)

  // not necessary, but this makes windup guard values 
  // relative to the current KI
  windupGaurd = WINDUP_GUARD_GAIN / KI;  

  if (iState > windupGaurd) 
    iState = windupGaurd;
  else if (iState < -windupGaurd) 
    iState = -windupGaurd;
  iTerm = KI * iState;

  // the dTerm, the difference between the temperature now
  //  and our last reading, indicated the "speed," 
  // how quickly the temp is changing. (aka. Differential)
  dTerm = (KD* (processVariable - lastValue));

  // now that we've use lastValue, put the current temp in
  // our pocket until for the next round
  lastValue = processVariable;

  // the magic feedback bit
  return  -1*(pTerm + iTerm + dTerm);
}

