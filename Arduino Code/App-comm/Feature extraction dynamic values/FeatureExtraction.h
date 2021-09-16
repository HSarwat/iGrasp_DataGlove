#ifndef FEATURE_EXTRACTION_H
#define FEATURE_EXTRACTION_H

#include "LinkedList.h"

/*Function Prototypes*/
float MEAN(LinkedList<float> Flex);
float RMS(LinkedList<float> Flex);
float CalculateSD(LinkedList<float> Flex);
float CalculateSMA(LinkedList<float> IMUx, LinkedList<float> IMUy, LinkedList<float> IMUz, int Ox, int Oy, int Oz, float freq);