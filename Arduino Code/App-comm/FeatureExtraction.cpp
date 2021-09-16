#include "LinkedList.h"
#include "FeatureExtraction.h"
#include <math.h>

// This library is implemented using a fixed number of readings N,
// where N = no. of samples gathered during 5 seconds
// It can also be implemented using a linkedlist (check folder 'Feature extraction dynamic values')
// An example of linkedlist is in the SMA function


// Root mean Square of the readings
float RMS(float Flex[100]){
  // int listsize = Flex.size();
  float sum = 0;
  for (int i = 0; i < 100; i++)
    sum += pow(Flex[i], 2);
  return sqrt(sum/100);
}

// Mean of the readings
float MEAN(float Flex[100]){
  // int listsize = Flex.size();
  float sum = 0;
  for (int i = 0; i < 100; i++)
    sum += Flex[i];
  return sum/100;
}

// Standard deviation of the readings
float CalculateSD(float Flex[100]){
  // int listsize = 100 // Flex.size();
  float sum = 0,
  standardDeviation = 0;
  float mean = MEAN(Flex);
  for (int i = 0; i < 100; i++)
    standardDeviation += pow(Flex[i]- mean, 2);
  return sqrt(standardDeviation/100);
}

// Signal magnitude area of either the acc or gyro
float CalculateSMA(LinkedList<float> IMUx, LinkedList<float> IMUy, LinkedList<float> IMUz, int Ox, int Oy, int Oz, float freq){
  int listsize = IMUx.size();
  float SMA = 0.0;
  for (int i = 1; i < listsize; i++)
    SMA += ((IMUx.get(i)+IMUx.get(i-1)-2*Ox)+(IMUy.get(i)+IMUy.get(i-1)-2*Oy)+(IMUz.get(i)+IMUz.get(i-1)-2*Oz))*0.5*(1/freq);
  return SMA;
}
