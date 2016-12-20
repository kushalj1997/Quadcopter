//Kushal Jaligama

//Receiver and Xbee/Serial Connections code

//Pins used on Arduino Pro Mini/Atmega 328p chip for receiver input
//ROLL, PITCH, YAW, THROTTLE, AUX1, AUX2
//2 	5      6     4 	      7     8


#define MOTOR_FRONT_LEFT 3
#define MOTOR_FRONT_RIGHT 9
#define MOTOR_REAR_LEFT 10
#define MOTOR_REAR_RIGHT 11

#define RECEIVERMIN 1070
#define RECEIVERMAX 1870
#define RECEIVERZERO 1470

#define SERIALDATADT 10

#define RECEIVERDT 20 //milliseconds

unsigned long lastSerialTime;
char c;

unsigned int channelValue = 1500;

bool armedMotors = false;

unsigned long lastReceiverTime;

unsigned long THROTTLE = 1000;
unsigned long YAW = 1000;
unsigned long ROLL = 1000;
unsigned long PITCH = 1000;
unsigned long AUX1 = 1000;
unsigned long AUX2 = 1000;

unsigned long receiverSerialPackets[6] = {
  1000, 1000, 1000, 1000, 1000, 1000}; //To send over Xbee

float rollTarget = 0.0;
float pitchTarget = 0.0;
float yawTarget = 0.0;

int flightMode = 0;

bool ledStatus = false;

void readReceiver(){
  if((millis() - lastReceiverTime) > RECEIVERDT) {
    THROTTLE = pulseIn(4, HIGH);
    ROLL = pulseIn(2, HIGH);
    PITCH = pulseIn(5, HIGH);
    YAW = pulseIn(6, HIGH);
    AUX1 = pulseIn(7, HIGH);
    AUX2 = pulseIn(8, HIGH);           

    armMotors();

    receiverSerialPackets[0] = THROTTLE;
    receiverSerialPackets[1] = ROLL;
    receiverSerialPackets[2] = PITCH;
    receiverSerialPackets[3] = YAW;
    receiverSerialPackets[4] = AUX1;
    receiverSerialPackets[5] = AUX2;

    processReceiverCommands();
    lastReceiverTime = millis();
  }
}

float mapReceiverToDegrees(unsigned long axis, int maximumAngle){
  float scalar = (RECEIVERMAX - RECEIVERZERO)/maximumAngle;
  int error = (int)(axis - RECEIVERZERO);
  return error/scalar;
}

void processReceiverCommands(){
  if(AUX1 > RECEIVERZERO){
    flightMode = 1; //Attitude Mode
    int maxAngle = 45; //Max angle 45 degrees

    rollTarget = mapReceiverToDegrees(ROLL, maxAngle);
    pitchTarget = (-1)*mapReceiverToDegrees(PITCH, maxAngle);
    yawTarget = mapReceiverToDegrees(YAW, maxAngle);
  }
  else if(AUX1 < RECEIVERZERO){
    flightMode = 0; //Rate Mode
    int maxRate = 30; //Max rate 15 deg/s

    rollTarget = mapReceiverToDegrees(ROLL, maxRate);
    pitchTarget = mapReceiverToDegrees(PITCH, maxRate);
    yawTarget = mapReceiverToDegrees(YAW, maxRate);
  }
}

void armMotors(){
  if(THROTTLE < RECEIVERMIN && YAW > RECEIVERMAX)
    armedMotors = true;
  else if(THROTTLE < RECEIVERMIN && YAW < RECEIVERMIN)
    armedMotors = false;
}
int serialCounter = 0;

void sendSerialData(){
  if((millis() - lastSerialTime) > SERIALDATADT) {
    c = Serial.read();
    switch(c){
    case 'c':
      Serial.println("Roll: Pitch: Yaw:   PID Command Outputs");
      Serial.print(rollCommand);
      Serial.print("  ");
      Serial.print(pitchCommand);
      Serial.print("   ");
      Serial.println(yawCommand);
    case 't':
      sendReceiverData();
    case 's':
      sendSensorToSerial();
    case 'm':
      sendMotorDataToSerial();
    case 'b':
      Serial.println("Roll: Pitch: Yaw:   Target Angles in Degrees");
      Serial.print(rollTarget);
      Serial.print("  ");
      Serial.print(pitchTarget);
      Serial.print("   ");
      Serial.println(yawTarget);
    case 'r':
      setPID(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
      Serial.println("PID gains have been reset to 0.0");
    case 'p':
      Serial.print("Flight Mode is: ");
      Serial.println(flightMode);
      Serial.println("The PID Constants Are:");
      Serial.print(getP());
      Serial.print("  ");
      Serial.print(getI());
      Serial.print("  ");
      Serial.println(getD());
    case 'g':
      Serial.println("Enter new P gain");
      if (Serial.read() != KP){
        KP = Serial.read(); 
      }
      Serial.print("P Gain is now: ");
      Serial.println(KP);

      Serial.println("Enter new I gain");
      if (Serial.read() != KI){
        KI = Serial.read(); 
      }
      Serial.print("I Gain is now: ");
      Serial.println(KI);

      Serial.println("Enter new D gain");
      if (Serial.read() != KD){
        KD = Serial.read(); 
      }
      Serial.print("D Gain is now: ");
      Serial.println(KD);
    case '?':
      Serial.println("Enter 't' for Receiver Data.");
      Serial.println("Enter 's' for Sensor Data.");
      Serial.println("Enter 'm' for Motor Data.");
      Serial.println("Enter 'r' to reset the PID gains.");
      Serial.println("Enter 'g' to set custom PID gains.");
      Serial.println("Enter 'b' to see the target angles in degrees.");
      Serial.println("Enter 'c' to see the command outputs from the PID algorithm.");
      Serial.println("Enter 'p' to see the PID constants.");
      Serial.println("Enter 'x' to stop Serial Data transmission.");

      break;
    default:
      Serial.println("Enter a letter for data, ? for help");
    }

  }
  lastSerialTime = millis();
}

void initReceiver(){
  pinMode(2, INPUT);
  for(int i = 4; i < 9; i++){
    pinMode(i, INPUT);
  }
  Serial.println("Receiver Initialized");
}

void sendReceiverData(){
  readReceiver();
  Serial.println("Throttle: Roll: Pitch: Yaw: AUX1: AUX2: FlightMode: ");
  Serial.print(receiverSerialPackets[0]);
  Serial.print("      ");
  Serial.print(receiverSerialPackets[1]);
  Serial.print("  ");
  Serial.print(receiverSerialPackets[2]);
  Serial.print("   ");
  Serial.print(receiverSerialPackets[3]);
  Serial.print(" ");
  Serial.print(receiverSerialPackets[4]);
  Serial.print("  ");
  Serial.print(receiverSerialPackets[5]);
  Serial.print("  ");
  Serial.println(flightMode);
}




