#include "LinkedList.h"
#include "FeatureExtraction.h"


float RMS(LinkedList<float> Flex){
  int listsize = Flex.size();
  float sum = 0;
  for (int i = 0; i < listsize; i++)
    sum += pow(Flex.get(i), 2);
  return sqrt(sum/listsize);
}

float MEAN(LinkedList<float> Flex){
  int listsize = Flex.size();
  float sum = 0;
  for (int i = 0; i < listsize; i++)
    sum += Flex.get(i);
  return sum/listsize;
}

float CalculateSD(LinkedList<float> Flex){
  int listsize = Flex.size();
  float sum = 0.0,
  standardDeviation = 0.0;
  float mean = MEAN(Flex);
  for (int i = 0; i < listsize; i++)
    standardDeviation += pow(Flex.get(i)- mean, 2);
  return sqrt(standardDeviation/listsize);
}

float CalculateSMA(LinkedList<float> IMUx, LinkedList<float> IMUy, LinkedList<float> IMUz, int Ox, int Oy, int Oz, float freq){
  int listsize = IMUx.size();
  float SMA = 0.0;
  for (int i = 1; i < listsize; i++)
    SMA += ((IMUx.get(i)+IMUx.get(i-1)-2*Ox)+(IMUy.get(i)+IMUy.get(i-1)-2*Oy)+(IMUz.get(i)+IMUz.get(i-1)-2*Oz))*0.5*(1/freq);
  return SMA;
}