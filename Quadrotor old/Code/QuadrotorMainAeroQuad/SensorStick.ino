#include <Wire.h>

// Complementary Balance Filter Defines
//DT Means Sample Rate in milliseconds
// Time Constant: The Period of time in which accel averages in heavily, chosen: .1 secs
// CUTOFF FACTOR = TimeConstant/(TimeConstant+(DT/1000))
// Credits The Balance Filter --- S. Colton
#define CUTOFF_FACTOR 0.833//0.666
#define ACCEL_FACTOR 0.167//0.334 //1 - CUTOFF_FACTOR
#define DT 10

double pitch = 0;
double roll = 0;
double yaw = 0;

double accelXOffset = 0;
double accelYOffset = 0;
double accelZOffset = 0;

double accelX = 0;
double accelY = 0;
double accelZ = 0;

double gyroXOffset = 0;
double gyroYOffset = 0;
double gyroZOffset = 0;

double gyroX = 0;
double gyroY = 0;
double gyroZ = 0;

//Sensor Stuff

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
  Serial.println((unsigned int)data);
}

double accelerometer_data[3];

void read_accel() {
  byte bytes[6];
  memset(bytes,0,6);

  //read 6 bytes from the ADXL345
  i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);

  //now unpack the bytes
  for (int i=0;i<3;++i) {
    accelerometer_data[i] = ((int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8))*(.4); //(0.004) OR (0.0392)*(9.1836) instead??
  }
  if (accelerometer_data[0] >= 0){accelX = accelerometer_data[0] - accelXOffset;}
    else {accelX = accelerometer_data[0] + accelXOffset;}
    
    if (accelerometer_data[1] >= 0){accelY = accelerometer_data[1] - accelYOffset;}
    else {accelY = accelerometer_data[1] + accelYOffset;}
   
    if (accelerometer_data[2] >= 0){accelZ = accelerometer_data[2] - accelZOffset;}
    else {accelZ = accelerometer_data[2] + accelZOffset;}  
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
  if (accelXOffset <0){accelXOffset *= -1;}
  if (accelYOffset <0){accelYOffset *= -1;}
  if (accelZOffset <0){accelZOffset *= -1;}
  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
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

  Serial.println((unsigned int)data);
}

double gyro_data[3];

void read_gyro() {
  byte bytes[6];
  memset(bytes,0,6);

  //read 6 bytes from the ITG3200
  i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_XMSB, 6, bytes);  //now unpack the bytes
  for (int i=0;i<3;++i) {
    gyro_data[i] = ((int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8))/(14.375);
  }
   if (gyro_data[0] >= 0){gyroX = gyro_data[0] - gyroXOffset;}
    else {gyroX = gyro_data[0] + gyroXOffset;}
    
    if (gyro_data[1] >= 0){gyroY = gyro_data[1] - gyroYOffset;}
    else {gyroY = gyro_data[1] + gyroYOffset;}
    
    if (gyro_data[2] >= 0){gyroZ = gyro_data[2] - gyroZOffset;}
    else {gyroZ = gyro_data[2] + gyroZOffset;}
}

void gyroOffset(){
  for(int i = 0; i < 500; i++){
    read_gyro();
    gyroXOffset += gyro_data[0];
    gyroYOffset += gyro_data[1];
    gyroZOffset += gyro_data[2];
  }

  gyroXOffset /= 500;
  gyroYOffset /= 500;
  gyroZOffset /= 500;
  if (gyroXOffset <0){gyroXOffset *= -1;}
  if (gyroYOffset <0){gyroYOffset *= -1;}
  if (gyroZOffset <0){gyroZOffset *= -1;}
  
  pinMode(31, OUTPUT);
  digitalWrite(31, HIGH);
}

#define HMC5843_ADDRESS (0x3C >> 1)
//First data address of 6 is XMSB.  Also need to set a configuration register for
//continuous measurement
#define HMC5843_REGISTER_XMSB (0x03)
#define HMC5843_REGISTER_MEASMODE (0x02)
#define HMC5843_MEASMODE_CONT (0x00)

void init_mag() {
  byte data = 0;
  //set up continuous measurement
  i2c_write(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, HMC5843_MEASMODE_CONT);

  //Sanity check, make sure the register value is correct.
  i2c_read(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, 1, &data);
  Serial.println((unsigned int)data);
}

double magnetometer_data[3];
void read_mag() {
  byte bytes[6];
  memset(bytes,0,6);

  //read 6 bytes from the HMC5843
  i2c_read(HMC5843_ADDRESS, HMC5843_REGISTER_XMSB, 6, bytes);

  //now unpack the bytes
  for (int i=0;i<3;++i) {
    magnetometer_data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
  }
}

void sensorInit() {
  Wire.begin();
  Serial.begin(57600);
  
  for(int i = 0; i < 3; ++i) {
    accelerometer_data[i] = magnetometer_data[i] = gyro_data[i] = 0;
  }

  init_accel();
  init_gyro();
  //init_mag();
  
  accelOffset();
  gyroOffset();
    

  }
  
double getPitch(){
  pitch = ( CUTOFF_FACTOR * (pitch + gyroX * (DT/1000)) )+ (ACCEL_FACTOR) * accelY;
  return pitch;
}

double getGyroPitch(){
  return gyroX;
}

double getRoll(){
  roll = ( CUTOFF_FACTOR * (roll + gyroY * (DT/1000)) )+ (ACCEL_FACTOR) * accelX;
  roll *= -1;
  return roll;
}

double getGyroRoll(){
  return gyroY;
}

/*
double getYaw(){
  yaw = ( CUTOFF_FACTOR * (yaw + gyroZ * (DT/1000)) )+ (ACCEL_FACTOR) * accelZ;
  return yaw;
}
*/

double getGyroYaw(){
  return gyroZ;
}

void sensorRead() {
    read_accel();   
    /*
    Serial.print("ACCEL: ");
    Serial.print(accelX);
    Serial.print("\t");
    Serial.print(accelY);
    Serial.print("\t");
    Serial.print(accelZ);
    Serial.print("\n");
    */      
    read_gyro();        
    /*
    Serial.print("GYRO: ");
    Serial.print(gyroX);
    Serial.print("\t");
    Serial.print(gyroY);
    Serial.print("\t");
    Serial.print(gyroZ);
    Serial.print("\n");
        
    Serial.print("PITCH: ");
    Serial.print(getPitch());
    Serial.print("\n");       
    
    Serial.print("ROLL: ");
    Serial.print(getRoll());
    Serial.print("\n");
    
    Serial.print("YAW: ");
    Serial.print(getGyroYaw());
    Serial.print("\n");
    */
    
    
/* Comment out Magnetometer for now 
   read_mag();

    Serial.print("MAG: ");
    Serial.print(magnetometer_data[0]);
    Serial.print(",");
    Serial.print(magnetometer_data[1]);
    Serial.print(",");
    Serial.print(magnetometer_data[2]);
    Serial.print("\n");
*/
  }
