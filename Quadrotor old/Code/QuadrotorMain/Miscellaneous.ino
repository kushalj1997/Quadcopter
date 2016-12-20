//Kushal Jaligama

//These are misc functions that do a set of instructions so it's easier to read the main loop.

void led(bool a){
  if(a == true){
    digitalWrite(13, HIGH);
    ledStatus = true;
  }
  else if(a == false){
    digitalWrite(13, LOW);
    ledStatus = false;
  }
}

void startUp(){
  Serial.println("Starting up..");

  pinMode(13, OUTPUT); //LED
  led(true);
  initMotors();
  sensorInit();
  initReceiver();
  Serial.println("In Loop");
}

void startTimers(){
  lastSensorTime = lastPIDTime = lastReceiverTime = lastSerialTime = millis();
}

