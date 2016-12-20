//Kushal Jaligama

// Complementary Balance Filter Defines

// DT Means Sample Rate in milliseconds
// Time Constant: The Period of time in which accel averages in heavily, chosen: .1 secs
// CUTOFF FACTOR = TimeConstant/(TimeConstant+(DT/1000))
// Credits The Balance Filter --- S. Colton

//Sensor Stuff

#define CUTOFF_FACTOR 0.833//0.666
#define ACCEL_FACTOR 0.167//0.334 //1 - CUTOFF_FACTOR
#define DT 10 //Interval time (milliseconds)

unsigned long lastSensorTime;  // most recent PID update time in ms 

float accelXOffset = 0.0;
float accelYOffset = 0.0;
float accelZOffset = 0.0;

float accelX = 0.0;
float accelY = 0.0;
float accelZ = 0.0;

float gyroXOffset = 0.0;
float gyroYOffset = 0.0;
float gyroZOffset = 0.0;

float gyroX = 0.0;
float gyroY = 0.0;
float gyroZ = 0.0;

//Attitude Definitions
float pitch = 0.0;
float roll = 0.0;
float yaw = 0.0;

void i2c_write(int address, byte reg, byte data) {
  // Send output register address
  Wire.beginTransmission(address);
  Wire.write(reg);
  // Connect to device and send byte
  Wire.write(data); // low byte
  Wire.endTransmission();
}

void i2c_read(int address, byte reg, int count, byte* data) {
  int i = 0;

  // Send input register address
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  // Connect to device and request bytes
  Wire.beginTransmission(address);
  Wire.requestFrom(address,count);
  while(Wire.available()){ // slave may send less than requested 
    char c = Wire.read(); // receive a byte as character
    data[i] = c;
    i++;
  }
  Wire.endTransmission();
}

#define  ADXL345_ADDRESS (0xA6 >> 1)
//There are 6 data registers, they are sequential starting 
//with the LSB of X.  We'll read all 6 in a burst and won't
//address them individually
#define ADXL345_REGISTER_XLSB (0x32)

//Need to set power control bit to wake up the adxl345
#define ADXL_REGISTER_PWRCTL (0x2D)
#define ADXL_PWRCTL_MEASURE (1 << 3)
void init_accel() {
  byte data = 0;

  i2c_write(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE);

  //Check to see if it worked!
  i2c_read(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, 1, &data);
}

float accelerometer_data[3];

void read_accel() {
  byte bytes[6];
  memset(bytes,0,6);

  //read 6 bytes from the ADXL345
  i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);

  //now unpack the bytes
  for (int i=0;i<3;++i) {
    accelerometer_data[i] = ((int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8))*(.4); //(0.004) OR (0.0392)*(9.1836) instead??
  }
  if (accelerometer_data[0] >= 0){
    accelY = accelerometer_data[0] - accelXOffset;
  }
  else {
    accelY = accelerometer_data[0] + accelXOffset;
  }

  if (accelerometer_data[1] >= 0){
    accelX = accelerometer_data[1] - accelYOffset;
  }
  else {
    accelX = accelerometer_data[1] + accelYOffset;
  }

  if (accelerometer_data[2] >= 0){
    accelZ = accelerometer_data[2] - accelZOffset;
  }
  else {
    accelZ = accelerometer_data[2] + accelZOffset;
  }  
}

void accelOffset(){
  for(int i = 0; i < 500; i++){
    read_accel();
    accelXOffset += accelerometer_data[0];
    accelYOffset += accelerometer_data[1];
    accelZOffset += accelerometer_data[2];
  }

  accelXOffset /= 500;
  accelYOffset /= 500;
  accelZOffset /= 500;

  if (accelXOffset <0){
    accelXOffset *= -1;
  }
  if (accelYOffset <0){
    accelYOffset *= -1;
  }
  if (accelZOffset <0){
    accelZOffset *= -1;
  }
}

#define ITG3200_ADDRESS (0xD0 >> 1)
//request burst of 6 bytes from this address
#define ITG3200_REGISTER_XMSB (0x1D)
#define ITG3200_REGISTER_DLPF_FS (0x16)
#define ITG3200_FULLSCALE (0x03 << 3)
#define ITG3200_42HZ (0x03)

void init_gyro() {
  byte data = 0;

  //Set DLPF to 42 Hz (change it if you want) and
  //set the scale to "Full Scale"
  i2c_write(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, ITG3200_FULLSCALE | ITG3200_42HZ);

  //Sanity check! Make sure the register value is correct.
  i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, 1, &data);

}

float gyro_data[3];

void read_gyro() {
  byte bytes[6];
  memset(bytes,0,6);

  //read 6 bytes from the ITG3200
  i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_XMSB, 6, bytes);  //now unpack the bytes
  for (int i=0;i<3;++i) {
    gyro_data[i] = ((int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8))/(14.375);
  }
  if (gyro_data[0] >= 0){
    gyroX = gyro_data[0] - gyroXOffset;
  }
  else {
    gyroX = gyro_data[0] + gyroXOffset;
  }

  if (gyro_data[1] >= 0){
    gyroY = gyro_data[1] - gyroYOffset;
  }
  else {
    gyroY = gyro_data[1] + gyroYOffset;
  }

  if (gyro_data[2] >= 0){
    gyroZ = gyro_data[2] - gyroZOffset;
  }
  else {
    gyroZ = gyro_data[2] + gyroZOffset;
  }
}

void gyroOffset(){ //Basically Calibration
  for(int i = 0; i < 500; i++){
    read_gyro();
    gyroXOffset += gyro_data[0];
    gyroYOffset += gyro_data[1];
    gyroZOffset += gyro_data[2];
  }

  gyroXOffset /= 500;
  gyroYOffset /= 500;
  gyroZOffset /= 500;

  if (gyroXOffset <0){
    gyroXOffset *= -1;
  }
  if (gyroYOffset <0){
    gyroYOffset *= -1;
  }
  if (gyroZOffset <0){
    gyroZOffset *= -1;
  }
}

void calculateAttitude(){
  roll = (CUTOFF_FACTOR * (roll + gyroY * (DT/1000)))+ ((ACCEL_FACTOR) * accelX);
  pitch = (CUTOFF_FACTOR * (pitch + gyroX * (DT/1000))) + ((ACCEL_FACTOR) * accelY);
  yaw = (CUTOFF_FACTOR * (yaw + gyroZ * (DT/1000)))+ ((ACCEL_FACTOR) * accelZ);
}

//Functions that will be used in main
void sensorInit() {
  Wire.begin();
  Wire.flush();

  for(int i = 0; i < 3; i++) {
    accelerometer_data[i] = 0;
    gyro_data[i] = 0;
  }

  init_accel();
  init_gyro();

  accelOffset();
  gyroOffset();

  Serial.println("Calibration done");
}

void sensorRead() {
  if((millis() - lastSensorTime) >= DT) {
    read_gyro();

    if(flightMode = 1){ //If in attitude mode
      read_accel();
      calculateAttitude();
    }
    lastSensorTime = millis();
  }
}

void sendSensorToSerial(){
  Serial.println("GyroX: GyroY: GyroZ: || AccelX: AccelY: AccelZ: || Roll: Pitch: Yaw:");
  Serial.print(gyroX);
  Serial.print("   ");
  Serial.print(gyroY);
  Serial.print("   ");
  Serial.print(gyroZ);
  Serial.print("     ");
  Serial.print(accelX);
  Serial.print("   ");
  Serial.print(accelY);
  Serial.print("   ");
  Serial.print(accelZ);
  Serial.print("     ");
  Serial.print(roll);
  Serial.print("   ");
  Serial.print(pitch);
  Serial.print("   ");
  Serial.println(yaw);
}


