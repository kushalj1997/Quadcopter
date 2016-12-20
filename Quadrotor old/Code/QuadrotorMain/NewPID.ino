//Kushal Jaligama

//PID Control Code

#define PGAIN_ADR 0
#define IGAIN_ADR 4
#define DGAIN_ADR 8

#define PAGAIN_ADR 12
#define IAGAIN_ADR 16
#define DAGAIN_ADR 20

//Accel and Gyro Mode
float KPA = 1;
float KIA = 0.0;
float KDA = 0.0;

//Gyro Mode
float KP = 1;
float KI = 0.0;
float KD = 0.1;

unsigned long lastTime;

float errSum, lastErr;

float computePID(float setpoint, float processVariable)
{
  /*How long since we last calculated*/
  unsigned long now = millis();
  float timeChange = (float)(now - lastTime);

  /*Compute all the working error variables*/
  float error = setpoint - processVariable;
  errSum += (error * timeChange);
  float dErr = (error - lastErr) / timeChange;

  /*Compute PID Output*/
  return getP()*error + getI()*errSum + getD()*dErr;

  /*Remember some variables for next time*/
  lastErr = error;
  lastTime = now;
}

void setPID(float p, float i, float d, float pa, float ia, float da) {
  // set the PID gains and store to eeprom
  KP = p;
  KI = i;
  KD = d;
  writeFloat(p, PGAIN_ADR);
  writeFloat(i, IGAIN_ADR);
  writeFloat(d, DGAIN_ADR);
  KPA = pa;
  KIA = ia;
  KDA = da;
  writeFloat(p, PAGAIN_ADR);
  writeFloat(i, IAGAIN_ADR);
  writeFloat(d, DAGAIN_ADR);
}


float getP() {
  // get the P gain
  if (flightMode == 1) 
    return KPA;
  else
    return KP;
}
float getI() {
  // get the I gain
  if (flightMode == 1)
    return KIA;
  else
    return KI;
}
float getD() {
  // get the D gain
  if (flightMode == 1)
    return KDA;
  else
    return KD;
}

