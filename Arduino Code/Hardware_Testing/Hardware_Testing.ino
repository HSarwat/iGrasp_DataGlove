#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "FLEX_interface.h"
#include "KickFiltersRT.h"

// This code is for hardware testing and extracting data directly to a PC
// Uncomment the function the subject is doing to extract the necessary data



// Real time low pass filter
KickFiltersRT<float> filtersRT;

// Connect the hardware as defined here
#define F43 A10
#define F42 A9
#define F34 A8
#define F32 A7
#define F31 A5
#define F29 A5
#define F24 A4
#define F21 A3
#define F13 A2
#define F6 A1
#define F5 A0
#define FSR1 A11
#define FSR2 A12
#define FSR3 A13
#define FSR4 A14
#define FSR5 A15


bool label=true;

//float t = 0;

MPU6050 Lgyro(0x68); // <-- use for AD0 LOW (0b1101000) - IMU1
MPU6050 Rgyro(0x69); // <-- use for AD0 HIGH (0b1101001) - IMU2

long LaccelX, LaccelY, LaccelZ, RaccelX, RaccelY, RaccelZ;
float LgForceX, LgForceY, LgForceZ, RgForceX, RgForceY, RgForceZ;

long LgyroX, LgyroY, LgyroZ, RgyroX, RgyroY, RgyroZ;
float LrotX, LrotY, LrotZ, RrotX, RrotY, RrotZ;


//int r0 = 0;
//int r1 = 0;
//int r2 = 0;


//int  bin [] = {0,1,2};//list of binary values


void setup() {
  Serial.begin(9600);
//  pinMode(s0, OUTPUT);
//  pinMode(s1, OUTPUT);
  Wire.begin(); // IMU code
  setupMPU(); // IMU code

}


void loop() {
//  prosup();         // Pronation - supination exercise, takes IMU data only
//  wave();           // Wave exercise
//  printData();      // Prints all the sensor readings on the serial monitor
//  logData();        // Logs all the sensor readings into a file, requires a python code that is available
//  grasp();          // Grasping exercise
//  pinch();          // Pinching exercise
//  delay(50);        // delay for 50ms
}

//////////////////////////////////////////////////////////


// IMU setup
void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission();              //Lgyro(0x68) (0b1101000) ADO GND LOW
  
  // IMU1 Offsets
  Lgyro.setXAccelOffset(-997.00);      
  Lgyro.setYAccelOffset(-1544.00);     
  Lgyro.setZAccelOffset(1315.00);      
  Lgyro.setXGyroOffset(79.00);         
  Lgyro.setYGyroOffset(-77.00);        
  Lgyro.setZGyroOffset(16.00);         
  
  
  Wire.beginTransmission(0b1101001); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101001); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101001); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission();                                                                             //Lgyro(0x69) (0b1101001)  ADO 5V HIGH
  
  // IMU2 Offsets
  Rgyro.setXAccelOffset(-3241.00);    // Set these for your MPU
  Rgyro.setYAccelOffset(-1203.00);        // Set these for your MPU
  Rgyro.setZAccelOffset(1015.00);      // Set these for your MPU
  Rgyro.setXGyroOffset(22.00);          // Set these for your MPU
  Rgyro.setYGyroOffset(51.00);        // Set these for your MPU
  Rgyro.setZGyroOffset(29.00);          // Set these for your MPU
}

//////////////////////////////////////////////////////////



void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  LaccelX = Wire.read()<<8|Wire.read(); //Store first two bytes into LaccelX
  LaccelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into LaccelY
  LaccelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into LaccelZ
  processAccelData();
  Wire.beginTransmission(0b1101001); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101001,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  RaccelX = Wire.read()<<8|Wire.read(); //Store first two bytes into LaccelX
  RaccelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into LaccelY
  RaccelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into LaccelZ
  processAccelData();
}

///////////////////////////////////////////////////////////

void processAccelData(){
  LgForceX = LaccelX / 16384.0;
  LgForceY = LaccelY / 16384.0; 
  LgForceZ = LaccelZ / 16384.0;
  RgForceX = RaccelX / 16384.0;
  RgForceY = RaccelY / 16384.0; 
  RgForceZ = RaccelZ / 16384.0;
}

//////////////////////////////////////////////////////////

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  LgyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into LaccelX
  LgyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into LaccelY
  LgyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into LaccelZ
  processGyroData();
  Wire.beginTransmission(0b1101001); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101001,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  RgyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into LaccelX
  RgyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into LaccelY
  RgyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into LaccelZ
  processGyroData();
}

//////////////////////////////////////////////////////////

void processGyroData() {
  LrotX = LgyroX / 131.0;
  LrotY = LgyroY / 131.0; 
  LrotZ = LgyroZ / 131.0;
  RrotX = RgyroX / 131.0;
  RrotY = RgyroY / 131.0; 
  RrotZ = RgyroZ / 131.0;
}

//////////////////////////////////////////////////////////

void printData() {
  recordAccelRegisters();
  recordGyroRegisters();

  Serial.print(" X:  "); Serial.print(RrotX);Serial.print("  ");Serial.print(LrotX);Serial.print("  ");
  Serial.print(RrotX-LrotX);
  Serial.print("\n Y:  ");Serial.print(RrotY);Serial.print("  ");Serial.print(LrotY);Serial.print("  ");
  Serial.print(RrotY-LrotY);
  Serial.print("\n Z:  ");Serial.print(RrotZ);Serial.print("  ");Serial.print(LrotZ);Serial.print("  ");
  Serial.print(RrotZ-LrotZ);
  Serial.print("\n");
  Serial.print("-------------------");
  Serial.print("\n F43: "); Serial.print(analogRead(F43)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F42,FLEX42));
  Serial.print("\t F42: "); Serial.print(analogRead(F42)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F42R,FLEX42R));
  Serial.print("\n F34: "); Serial.print(analogRead(F34)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F34,FLEX34));
  Serial.print("\t F32: "); Serial.print(analogRead(F32)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F32,FLEX32));
  Serial.print("\n F31: "); Serial.print(analogRead(F31)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F31,FLEX31));
  Serial.print("\t F29: "); Serial.print(analogRead(F29)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F29,FLEX29));
  Serial.print("\n F24: "); Serial.print(analogRead(F24)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F24,FLEX24));
  Serial.print("\t F21: "); Serial.print(analogRead(F21)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F21,FLEX21));
  Serial.print("\n F13: "); Serial.print(analogRead(F13)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F13,FLEX13));
  Serial.print("\t F6: "); Serial.print(analogRead(F6)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F6,FLEX6));Serial.print("    ");
  Serial.print("\n F5: "); Serial.print(analogRead(F5)); //Serial.print(", Angle: ");Serial.print(FLEX_Angle(F5,FLEX5));
//  Serial.print("\n FSR1: "); Serial.print(analogRead(FSR1));
//  Serial.print("\n FSR2: "); Serial.print(analogRead(FSR2));
//  Serial.print("\n FSR3: "); Serial.print(analogRead(FSR3));
  Serial.print("\n FSR4: "); Serial.print(analogRead(FSR4));
  Serial.print("\n FSR5: "); Serial.print(analogRead(FSR5));
  Serial.print("\n");
//  int count = 1; 
//  digitalWrite(s0, HIGH);
//  digitalWrite(s1, LOW);
//  Serial.print("\n FSR4: "); Serial.print(analogRead(MUX));
//  count = 2; 
//  digitalWrite(s0, LOW);
//  digitalWrite(s1, HIGH);
//  Serial.print("\n FSR5: "); Serial.print(analogRead(MUX));
//  Serial.print("\n");  
  delay(1000);
}

//////////////////////////////////////////////////////////

void logData() {
  recordAccelRegisters();
  recordGyroRegisters();

  while (label == true){
//    Serial.print("A1x,A1y,A1z,G1x,G1y,G1z,A2x,A2y,A2z,G2x,G2y,G2z,");
//    Serial.print("F43,Angle42,F42R,Angle42R,F34,Angle34,F32,Angle32,F43,Angle43,F31,Angle31,F29,Angle29,F24,Angle24,F21,Angle21,F13,Angle13,F6,Angle6,F5,Angle5");
    Serial.print("F43,F42,F34,F32,F31,F29,F24,F21,F13,F6,F5");
//    Serial.print("\n");
    label = false;  
  }
  Serial.print("\n");
  Serial.print(LgForceX); Serial.print(","); Serial.print(LgForceY); Serial.print(","); Serial.print(LgForceZ); Serial.print(",");
  Serial.print(LgyroX); Serial.print(","); Serial.print(LgyroY); Serial.print(","); Serial.print(LgyroZ); Serial.print(",");
  Serial.print(LaccelX); Serial.print(","); Serial.print(LaccelY); Serial.print(","); Serial.print(LaccelZ); Serial.print(",");
  Serial.print(LgyroX); Serial.print(","); Serial.print(LgyroY); Serial.print(","); Serial.print(LgyroZ);// Serial.print(",");
   
  Serial.print(analogRead(F43));//Serial.print(","); //Serial.print(FLEX_Angle(F42,FLEX42));
  Serial.print(","); Serial.print(analogRead(F42));//Serial.print(","); //Serial.print(FLEX_Angle(F42R,FLEX42R));
  Serial.print(","); Serial.print(analogRead(F34));//Serial.print(","); //Serial.print(FLEX_Angle(F34,FLEX34));
  Serial.print(","); Serial.print(analogRead(F32));//Serial.print(","); //Serial.print(FLEX_Angle(F32,FLEX32));
  Serial.print(","); Serial.print(analogRead(F31));//Serial.print(","); //Serial.print(FLEX_Angle(F31,FLEX31));
  Serial.print(","); Serial.print(analogRead(F29));//Serial.print(","); //Serial.print(FLEX_Angle(F29,FLEX29));
  Serial.print(","); Serial.print(analogRead(F24));//Serial.print(","); //Serial.print(FLEX_Angle(F24,FLEX24));
  Serial.print(","); Serial.print(analogRead(F21));//Serial.print(","); //Serial.print(FLEX_Angle(F21,FLEX21));
  Serial.print(","); Serial.print(analogRead(F13));//Serial.print(","); //Serial.print(FLEX_Angle(F13,FLEX13));
  Serial.print(","); Serial.print(analogRead(F6));//Serial.print(","); //Serial.print(FLEX_Angle(F6,FLEX6));
  Serial.print(","); Serial.print(analogRead(F5));//Serial.print(","); //Serial.print(FLEX_Angle(F5,FLEX5));
  Serial.print(","); Serial.print(analogRead(FSR1));
  Serial.print(","); Serial.print(analogRead(FSR2));
  Serial.print(","); Serial.print(analogRead(FSR3));
  Serial.print(","); Serial.print(analogRead(FSR4));
  Serial.print(","); Serial.print(analogRead(FSR5));
//  t += 0.1;
//  Serial.print(","); Serial.print(t); //Serial.print(FLEX_Angle(F5,FLEX5));
  
//  delay(00);

}

void pinch() {
  Serial.print(filtersRT.lowpass(analogRead(F43), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F42,FLEX42));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F43), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F42R,FLEX42R));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F43), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F34,FLEX34));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F43), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F32,FLEX32));
  Serial.print(","); Serial.print(analogRead(FSR4));
  Serial.print(","); Serial.print(analogRead(FSR5));
  Serial.print("\n");
}

void grasp() {
  Serial.print(filtersRT.lowpass(analogRead(F43), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F42,FLEX42));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F42), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F42R,FLEX42R));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F34), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F34,FLEX34));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F32), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F32,FLEX32));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F31), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F31,FLEX31));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F29), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F29,FLEX29));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F24), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F24,FLEX24));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F21), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F21,FLEX21));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F13), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F13,FLEX13));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F6), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F6,FLEX6));
  Serial.print("\n");
}

void wave() {
  recordAccelRegisters();
  recordGyroRegisters();
  Serial.print(LaccelX); Serial.print(","); Serial.print(LaccelY); Serial.print(","); Serial.print(LaccelZ); Serial.print(",");
  Serial.print(LgyroX); Serial.print(","); Serial.print(LgyroY); Serial.print(","); Serial.print(LgyroZ); Serial.print(",");
  Serial.print(RaccelX); Serial.print(","); Serial.print(RaccelY); Serial.print(","); Serial.print(RaccelZ); Serial.print(",");
  Serial.print(RgyroX); Serial.print(","); Serial.print(RgyroY); Serial.print(","); Serial.print(RgyroZ);// Serial.print(",");
//  Serial.print(","); Serial.print(analogRead(F5));
  Serial.print("\n");
}

void point() {
  Serial.print(filtersRT.lowpass(analogRead(F43), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F42,FLEX42));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F42), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F42R,FLEX42R));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F34), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F34,FLEX34));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F32), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F32,FLEX32));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F31), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F31,FLEX31));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F29), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F29,FLEX29));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F24), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F24,FLEX24));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F21), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F21,FLEX21));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F13), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F13,FLEX13));
  Serial.print(","); Serial.print(filtersRT.lowpass(analogRead(F6), 12, 10));//Serial.print(","); //Serial.print(FLEX_Angle(F6,FLEX6));
  Serial.print("\n");
}

void prosup() {
  recordAccelRegisters();
  recordGyroRegisters();
  Serial.print(LaccelX); Serial.print(","); Serial.print(LaccelY); Serial.print(","); Serial.print(LaccelZ); Serial.print(",");
  Serial.print(LgyroX); Serial.print(","); Serial.print(LgyroY); Serial.print(","); Serial.print(LgyroZ); Serial.print(",");
  Serial.print(RaccelX); Serial.print(","); Serial.print(RaccelY); Serial.print(","); Serial.print(RaccelZ); Serial.print(",");
  Serial.print(RgyroX); Serial.print(","); Serial.print(RgyroY); Serial.print(","); Serial.print(RgyroZ);// Serial.print(",");
  Serial.print("\n");
}
