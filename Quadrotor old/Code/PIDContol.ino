//Kushal Jaligama

//I have modified this from http://playground.arduino.cc/Main/BarebonesPIDForEspresso#pid

// PID control code
// Tim Hirzel
// December 2007

// This is a module that implements a PID control loop
// initialize it with 3 values: p,i,d
// and then tune the feedback loop with the setP etc funcs
//
// this was written based on a great PID by Tim Wescott:
// http://www.embedded.com/2000/0010/0010feat3.htm
//
//
// All code released under
// Creative Commons Attribution-Noncommercial-Share Alike 3.0 

//I have modified this from http://playground.arduino.cc/Main/BarebonesPIDForEspresso#pid

// These are addresses into EEPROM memory.  The values to be stores are floats which 
// need 4 bytes each.  Thus 0,4,8,12,...

float updatePID(float targetTemp, float curTemp)
{
  // these local variables can be factored out if memory is an issue, 
  // but they make it more readable
  float result;
  float error;
  float windupGaurd;

  // determine how badly we are doing
  error = targetTemp - curTemp;

  // the pTerm is the view from now, the getP() judges 
  // how much we care about error we are this instant.
  pTerm = getP() * error;

  // iState keeps changing over time; it's 
  // overall "performance" over time, or accumulated error
  iState += error;

  // to prevent the iTerm getting huge despite lots of 
  //  error, we use a "windup guard" 
  // (this happens when the machine is first turned on and
  // it cant help be cold despite its best efforts)

  // not necessary, but this makes windup guard values 
  // relative to the current getP()
  windupGaurd = WINDUP_GUARD_GAIN / getP();  

  if (iState > windupGaurd) 
    iState = windupGaurd;
  else if (iState < -windupGaurd) 
    iState = -windupGaurd;
  iTerm = getI() * iState;

  // the dTerm, the difference between the temperature now
  //  and our last reading, indicated the "speed," 
  // how quickly the temp is changing. (aka. Differential)
  dTerm = (getD()* (curTemp - lastTemp));

  // now that we've use lastTemp, put the current temp in
  // our pocket until for the next round
  lastTemp = curTemp;

  // the magic feedback bit
  return  pTerm + iTerm - dTerm;
}



// END PID
