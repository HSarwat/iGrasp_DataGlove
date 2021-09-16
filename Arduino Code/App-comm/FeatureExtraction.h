#ifndef FEATURE_EXTRACTION_H
#define FEATURE_EXTRACTION_H

#include <math.h>
#include "LinkedList.h"


/*Function Prototypes*/
float MEAN(float Flex[100]);
float RMS(float Flex[100]);
float CalculateSD(float Flex[100]);
float CalculateSMA(LinkedList<float> IMUx, LinkedList<float> IMUy, LinkedList<float> IMUz, int Ox, int Oy, int Oz, float freq);

#endif 