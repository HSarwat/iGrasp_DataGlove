#include "FeatureExtraction.h" // Library for feature extraction
#define F42 A0

// This code is for communication between the app and the arduino

float Flex42[100];
float mean, rms, standev; 
char state;
int i = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // needs to be the same as bluetoosh, bluetooth datasheet says a different value, but the datasheet is wrong
}


// The current code is used to test the bluetooth
// Account for testing the communication
// Username: admin  --  Password: admin
void loop() {
  if(Serial.available() > 0){   // Checks whether data is comming from the app
    state = Serial.read();      // Read the data from the app
  }
  if (state == '1') {
    Flex42[i] = analogRead(F42);  // display sensor reading on phone
    i++;

    if(i==100){
      mean = MEAN(Flex42); // display the mean of every 100 readings
//    rms = RMS(Flex42);
//    standev = CalculateSD(Flex42);
    
      Serial.print(String(mean)); // Send mean to app
      state = '0';
      i = 0;
    }
  }
  else if (state == '2') {
    Flex42[i] = analogRead(F42);
    i++;
      if(i==100){
//      mean = MEAN(Flex42);
//      rms = RMS(Flex42);
        standev = CalculateSD(Flex42); //calculate standard deviation
    
      Serial.print(String(standev)); // send SD to app
      state = '0'; // state '0' means to stop sending to the app and keeps looping till app changes state
      i = 0;
    }
  }
}

// There is a problem with bluetooth delay, usually one or two values
// ie, if the code sends the values 100, 200 and 300, the phone will read 100 and 200
// and if another value is sent, the phone will read 300 and not the new value
