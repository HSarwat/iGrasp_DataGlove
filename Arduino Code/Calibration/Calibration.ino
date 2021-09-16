#define F43 A10
#define F42 A9
#define F34 A8
#define F32 A7
#define F31 A6
#define F29 A5
#define F24 A4
#define F21 A3
#define F13 A2
#define F6 A1
//#define F5 A0


// Low pass filter
#include "KickFiltersRT.h"

KickFiltersRT<float> filtersRT;


// Find minimum value in 100 readings
int find_min(int Flex[100]){
  int min = Flex[0];
  for(int index = 1; index<100;index++){
    if(Flex[index]<min){
      min = Flex[index];
    }
  }
  return min;
}

// Find max value in 100 readings
int find_max(int Flex[100]){
  int max = Flex[0];
  for(int index = 1; index<100;index++){
    if(Flex[index]>max){
      max = Flex[index];
    }
  }
  return max;
}



int i=0;
int Flex43[100];
int Flex42[100];
int Flex34[100];
int Flex32[100];
int Flex31[100];
int Flex29[100];
int Flex24[100];
int Flex21[100];
int Flex13[100];
int Flex6[100];
//int Flex5[100];

void setup() {
  Serial.begin(9600);
//  pinMode(F43,INPUT);
//  pinMode(F42,INPUT);
//  pinMode(F34,INPUT);
//  pinMode(F32,INPUT);
//  pinMode(F31,INPUT);
//  pinMode(F29,INPUT);
//  pinMode(F24,INPUT);
//  pinMode(F21,INPUT);
//  pinMode(F13,INPUT);
//  pinMode(F6,INPUT);
}



// Close your fist and open them during void loop to find min and max value of every sensor
// Disconnect and reconnect USB after each trial
void loop() {
  if(i<100){
    Flex43[i] = filtersRT.lowpass(analogRead(F43), 12, 10);
    Flex42[i] = filtersRT.lowpass(analogRead(F42), 12, 10);
    Flex34[i] = filtersRT.lowpass(analogRead(F34), 12, 10);
    Flex32[i] = filtersRT.lowpass(analogRead(F32), 12, 10);
    Flex31[i] = filtersRT.lowpass(analogRead(F31), 12, 10);
    Flex29[i] = filtersRT.lowpass(analogRead(F29), 12, 10);
    Flex24[i] = filtersRT.lowpass(analogRead(F24), 12, 10);
    Flex21[i] = filtersRT.lowpass(analogRead(F21), 12, 10);
    Flex13[i] = filtersRT.lowpass(analogRead(F13), 12, 10);
    Flex6[i] = filtersRT.lowpass(analogRead(F6), 12, 10);
//    Flex5[i] = analogRead(F5);
//  Serial.print(Flex6[i]);
  }
  else if(i == 100){
    int max43 = find_max(Flex43);
    int min43 = find_min(Flex43);
    Serial.print("Min F43 = "); Serial.print(min43); Serial.print("\t");
    Serial.print("Max F43 = "); Serial.print(max43); Serial.print("\n");
    Serial.print("Min F42 = "); Serial.print(find_min(Flex42)); Serial.print("\t");
    Serial.print("Max F42 = "); Serial.print(find_max(Flex42)); Serial.print("\n");
    Serial.print("Min F34 = "); Serial.print(find_min(Flex34)); Serial.print("\t");
    Serial.print("Max F34 = "); Serial.print(find_max(Flex34)); Serial.print("\n");
    Serial.print("Min F32 = "); Serial.print(find_min(Flex32)); Serial.print("\t");
    Serial.print("Max F32 = "); Serial.print(find_max(Flex32)); Serial.print("\n");
    Serial.print("Min F31 = "); Serial.print(find_min(Flex31)); Serial.print("\t");
    Serial.print("Max F31 = "); Serial.print(find_max(Flex31)); Serial.print("\n");
    Serial.print("Min F29 = "); Serial.print(find_min(Flex29)); Serial.print("\t");
    Serial.print("Max F29 = "); Serial.print(find_max(Flex29)); Serial.print("\n");
    Serial.print("Min F24 = "); Serial.print(find_min(Flex24)); Serial.print("\t");
    Serial.print("Max F24 = "); Serial.print(find_max(Flex24)); Serial.print("\n");
    Serial.print("Min F21 = "); Serial.print(find_min(Flex21)); Serial.print("\t");
    Serial.print("Max F21 = "); Serial.print(find_max(Flex21)); Serial.print("\n");
    Serial.print("Min F13 = "); Serial.print(find_min(Flex13)); Serial.print("\t");
    Serial.print("Max F13 = "); Serial.print(find_max(Flex13)); Serial.print("\n");
    Serial.print("Min F6 = "); Serial.print(find_min(Flex6)); Serial.print("\t");
    Serial.print("Max F6 = "); Serial.print(find_max(Flex6)); Serial.print("\n");
//  Serial.print("Min F5 = "); Serial.print(find_min(Flex5)); Serial.print("\t");
//  Serial.print("Max F5 = "); Serial.print(find_max(Flex5)); Serial.print("\n");
  }
//  else{
//    Serial.print(find_min(Flex6));
//  }
  i+=1;
  delay(100);

}
