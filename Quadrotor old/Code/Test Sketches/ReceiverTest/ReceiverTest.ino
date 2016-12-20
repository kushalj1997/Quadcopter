//Receiver test sketch

unsigned long THROTTLE = 1000;
unsigned long YAW = 1000;
unsigned long ROLL = 1000;
unsigned long PITCH = 1000;
unsigned long AUX1 = 1000;
unsigned long AUX2 = 1000;

unsigned long receiverSerialPackets[6] = {
  1000, 1000, 1000, 1000, 1000, 1000};

void setup(){
  initReceiver();
  Serial.begin(115200);
}

void loop(){
  readReceiver();
  Serial.println("Throttle: Roll: Pitch: Yaw: AUX1: AUX2:");
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
  Serial.println(receiverSerialPackets[5]);
}


void initReceiver(){
  pinMode(2, INPUT);
  for(int i = 4; i < 9; i++){
    pinMode(i, INPUT);
  }
}
void readReceiver(){
  THROTTLE = pulseIn(4, HIGH);
  ROLL = pulseIn(2, HIGH);
  PITCH = pulseIn(5, HIGH);
  YAW = pulseIn(6, HIGH);
  AUX1 = pulseIn(7, HIGH);
  AUX2 = pulseIn(8, HIGH);           

  receiverSerialPackets[0] = THROTTLE;
  receiverSerialPackets[1] = ROLL;
  receiverSerialPackets[2] = PITCH;
  receiverSerialPackets[3] = YAW;
  receiverSerialPackets[4] = AUX1;
  receiverSerialPackets[5] = AUX2;
}


