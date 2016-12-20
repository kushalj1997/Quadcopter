// Sensors

#include <Wire.h>
#include <I2Cdev.h>
#include <ITG3200.h> // Gyroscope
#include <ADXL345.h> // Accelerometer
#include <HMC5883L.h> // Compass
#include <BMP085.h> // Barometer

#define RAD2DEG 180/PI
#define DEG2RAD PI/180

float gyroPitch, gyroRoll, gyroYaw; // Gyroscope Variables
float accelRoll, accelPitch, accelDownG; //Accelerometer Variables
float temperature, altitude; // Barometer Variables

bool lastArmed = false;
float altitudeOffset = 0;

void initIMU() {
  Wire.begin();
  Serial.println("Initializing I2C devices...");
  initGyro();
  initAccel();
  initBaro();

  // insert other sensors

  delay(1000);
}

void readIMU() {
  readGyro();
  readAccel();
  readBaro();

  quadRoll = (autoLevel) ? (int) complementaryFilter(gyroRoll, accelRoll) : gyroRoll;
  quadPitch = (autoLevel) ? (int) complementaryFilter(gyroPitch, accelPitch) : gyroPitch;
  quadYaw = gyroYaw; // Add in the Magnetometer with Complementary Filter
//  if (armed != lastArmed) {
//    altitudeOffset = altitude;
//    lastArmed = armed;
//  }
  quadAltitude = altitude - altitudeOffset;

  // insert other sensors
}

void printIMUData() {
  Serial.print("Roll: ");
  Serial.print(quadRoll);
  Serial.print(" Pitch: ");
  Serial.print(quadPitch);
  Serial.print(" Yaw: ");
  Serial.print(quadYaw);
  Serial.print(" Altitude: ");
  Serial.println(quadAltitude);
}

float complementaryFilter(float rate, float angle) {
  return (0.99 * rate + 0.01 * angle);
}

// ------------------------------------------------------------------------

// Gyroscope

#define LSBTODEGS 14.375

ITG3200 gyro;
int16_t gx, gy, gz;

void initGyro() {
  gyro.initialize();

  // verify connection
  Serial.println(gyro.testConnection() ? "ITG3200 connection successful" : "ITG3200 connection failed");
}

void readGyro() {
  gyro.getRotation(&gx, &gy, &gz);
  gyroPitch = (gyroPitch * .8) + (.2 * (float)gx / LSBTODEGS);
  gyroRoll = (gyroRoll * .8) + (.2 * (float)gy / LSBTODEGS);
  gyroYaw = (gyroYaw * .8) + (.2 * (float)gz / LSBTODEGS);
}

void printGyroData() {
  Serial.print("Roll: ");
  Serial.print(gyroRoll);
  Serial.print(" Pitch: ");
  Serial.print(gyroPitch);
  Serial.print(" Yaw: ");
  Serial.println(gyroYaw);
}

// ------------------------------------------------------------------------

// Accelerometer

#define LSBTOGS 250 // 4mG/LSB

ADXL345 accel;
int16_t ax, ay, az;

void initAccel() {
  accel.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accel.testConnection() ? "ADXL345 connection successful" : "ADXL345 connection failed");
}

void readAccel() {
  accel.getAcceleration(&ax, &ay, &az);

  accelDownG = (float)az / LSBTOGS;
  accelPitch  = RAD2DEG * atan((float)-ay / sqrt(pow((float)ax, 2) + pow((float)az, 2)));
  accelRoll = RAD2DEG * atan((float)-ax / sqrt(pow((float)ay, 2) + pow((float)az, 2)));
}

void printAccelData() {
  Serial.print("Roll: ");
  Serial.print(accelRoll);
  Serial.print(" Pitch: ");
  Serial.print(accelPitch);
  Serial.print(" Down G's: ");
  Serial.println(accelDownG);
}

// ------------------------------------------------------------------------

// Compass

// ------------------------------------------------------------------------

// Barometer

BMP085 barometer;

float pressure;
int32_t lastTempMicros;
int32_t lastPressureMicros;
bool pressureModeSet = false;
bool tempModeSet = true;
bool tempWasRead = false;

void initBaro() {
  barometer.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(barometer.testConnection() ? "BMP085 connection successful" : "BMP085 connection failed");
}

void readBaro() {

  if (tempModeSet) {
    tempModeSet = false;
    lastTempMicros = millis();
    // request temperature
    barometer.setControl(BMP085_MODE_TEMPERATURE);
  }

  if (pressureModeSet) {
    pressureModeSet = false;
    lastPressureMicros = millis();
    // request pressure (3x oversampling mode, high detail, 23.5ms delay)
    barometer.setControl(BMP085_MODE_PRESSURE_3);
  }

  if (tempWasRead) {
    // wait appropriate time for conversion (23.5 ms delay)
    if (millis() - lastPressureMicros >= barometer.getMeasureDelayMicroseconds()) {
      // read calibrated pressure value in Pascals (Pa)
      pressure = barometer.getPressure();
      tempWasRead = false;
      tempModeSet = true;
    }
  } else {
    // wait appropriate time for conversion (4.5ms delay)
    if (millis() - lastTempMicros >= barometer.getMeasureDelayMicroseconds()) {
      // read calibrated temperature value in degrees Celsius
      temperature = barometer.getTemperatureC();
      tempWasRead = true;
      pressureModeSet = true;
    }
  }

  // calculate absolute altitude in meters based on known pressure
  // (may pass a second "sea level pressure" parameter here,
  // otherwise uses the standard value of 101325 Pa)
  altitude = barometer.getAltitude(pressure);
}

void printBaroData() {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" Pressure: ");
  Serial.print(pressure);
  Serial.print(" Altitude (Above Sea Level): ");
  Serial.println(altitude);
}
