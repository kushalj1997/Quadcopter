//---------------\\
#include <Wire.h>
#define MOTOR_PWM_Timer
#define NB_MOTOR_CONFIG FOUR_Motors
#include <Motors_PWM_Timer.h>
//---------------\\

void initMotors(NB_Motors motorConfig) {
  initializeMotors(motorConfig); 
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void initESC(){
  motorCommand[0] = 1000;
  motorCommand[1] = 1000;
  motorCommand[2] = 1000;
  motorCommand[3] = 1000;
  writeMotors();
}

void setup(){

  Serial.println("Bootup");
  initMotors(NB_MOTOR_CONFIG);
  initESC();
  delay(4000);
  digitalWrite(13, LOW);
  sensorInit();
  digitalWrite(13, HIGH);
  Serial.println("In Loop");
}

void loop(){
  if (millis() > 10000){
    stopAllMotors();
  }
  else if (Serial.read() - '0' >= 1){
      stopAllMotors();
      Serial.println("Waiting for thirty seconds to turn off quad!");    
      delay(30000); //Wait 30 seconds to turn off quad    
    }
  else{

    if (Serial.read() - '0' >= 1){
      stopAllMotors();
      Serial.println("Waiting for thirty seconds to turn off quad!");    
      delay(30000); //Wait 30 seconds to turn off quad    
    }
    /* else if (Serial.read() - '0' == 9){
     stopAllMotors();
     Serial.println("Waiting for 10 seconds to reset quad!");    
     delay(10000); //Wait 30 seconds to turn off quad    
     }*/
    stabilize();
  }

  delay(10);
}




