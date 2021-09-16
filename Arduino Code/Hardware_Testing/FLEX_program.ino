/****************************************************/
/* Author   : Hamdy Osama Mohamed                   */
/* Date     : 20/11/2020                             */
/* Version  : V01                                   */
/* File     : FLEX Driver                            */
/****************************************************/
#include "FLEX_interface.h"
#include "FLEX_config.h"
#include "FLEX_private.h"


/*Global Variables*/
float filtered_angle5=0;
float filtered_angle6=0;
float filtered_angle13=0;
float filtered_angle21=0;
float filtered_angle24=0;
float filtered_angle29=0;
float filtered_angle31=0;
float filtered_angle32=0;
float filtered_angle34=0;
float filtered_angle42=0;
float filtered_angle42R=0;
float filtered_angle43=0;
 
/*Function Implementation*/
int FLEX_Pin_Reading(short FLEX_Pin){
  long Sum=0;                                           /*used to store all pin readings addition*/
  if(NUMBER_OF_READINGS<=0){                           /*Check Configurations*/
    Serial.println("Wrong Number of Readings set in Configuration");
    return -1;                                         /*Error State*/ 
  }
  else {
    for (short i=0;i<NUMBER_OF_READINGS;i++){          /*Add all readings to help return average*/
      Sum+=analogRead(FLEX_Pin);
     // delay(1);
    }
  }
  return Sum/NUMBER_OF_READINGS;                       /*Return Average*/
}

float FLEX_Resistance(short FLEX_Pin){
  int Reading=FLEX_Pin_Reading(FLEX_Pin);              /*Get Average Pin Reading*/
  /*Calculate FLEX Resistance based on Voltage Divider Configuration*/
  if (CONSTANT_RESISTANCE>0){                          /*Check Configurations*/
    return ((CONSTANT_RESISTANCE*Reading)/float(1023-Reading)); // 300 instead of 1023
  }
  else{
    Serial.println("Wrong Constant resistance value set in Configuration");
    return -1;                                         /*Error State*/  
  }
}


float FLEX_Angle(short FLEX_Pin,short FLEX_Num){
  float angle;
  float filtered_angle;
  float resistance=FLEX_Resistance(FLEX_Pin);
  angle=Calculate_Angle(resistance,FLEX_Num);          //Start Calculating Angle based on sensor curve
  //return angle;
  if (angle>=9){                                        //Average Sensor Force Sensitivity
  filtered_angle=Filter_Angle(angle,FLEX_Num); //Low Pass Filter
  return filtered_angle;
  }
  angle=0; 
  filtered_angle=Filter_Angle(angle,FLEX_Num); //Low Pass Filter
  return filtered_angle;
}



static float Calculate_Angle(float FLEX_Resistance,short FLEX_Num){
	if (FLEX_Num==FLEX24)
		return (((-5.205*pow(10,-13)*pow(FLEX_Resistance,4))+(7.538*pow(10,-8)*pow(FLEX_Resistance,3))+(-0.001557*pow(FLEX_Resistance,2))+(0.7537*FLEX_Resistance)+0.3804)/(FLEX_Resistance+0.5678)); //Based on Force-Resistance Curve Fitting
	else if (FLEX_Num==FLEX29)
    return ((8.388*pow(10,-21)*pow(FLEX_Resistance,5))+(-1.655*pow(10,-15)*pow(FLEX_Resistance,4))+(1.265*pow(10,-10)*pow(FLEX_Resistance,3))+(-4.635*pow(10,-6)*pow(FLEX_Resistance,2))+(0.08214*FLEX_Resistance)-569.1);  
  else if (FLEX_Num==FLEX21)
    return (5.713*pow(10,-11)*pow(FLEX_Resistance,2.529));
  else if (FLEX_Num==FLEX42 ||FLEX_Num==FLEX34||FLEX_Num==FLEX5||FLEX_Num==FLEX43||FLEX_Num==FLEX32||FLEX_Num==FLEX6||FLEX_Num==FLEX13)
    return ((-4.645*pow(10,-9)*pow(FLEX_Resistance,2))+(0.003213*FLEX_Resistance)-90.89);
  else if (FLEX_Num==FLEX31)
    return ((1.825*pow(10,-12)*pow(FLEX_Resistance,3))+(-1.71*pow(10,-7)*pow(FLEX_Resistance,2))+(0.007142*FLEX_Resistance)-106.5);
	else if (FLEX_Num==FLEX42R)
    return ((2.269*pow(10,-16)*pow(FLEX_Resistance,4))+(-3.624*pow(10,-11)*pow(FLEX_Resistance,3))+(2.136*pow(10,-6)*pow(FLEX_Resistance,2))+(-0.0523*FLEX_Resistance)+448.7);

	else
		return -1;  //	ERROR STATE
}

static float Filter_Angle(float FLEX_Angle,short FLEX_Num){
  if (FLEX_Num==FLEX24){
    filtered_angle24=(0.5335*filtered_angle24 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle24;
  }
  else if (FLEX_Num==FLEX29){
    filtered_angle29=(0.5335*filtered_angle29 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle29;
  }
  else if (FLEX_Num==FLEX21){
    filtered_angle21=(0.5335*filtered_angle21 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle21;
  }
  else if (FLEX_Num==FLEX42){
    filtered_angle42=(0.5335*filtered_angle42 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle42;
  }
  else if (FLEX_Num==FLEX34){
    filtered_angle34=(0.5335*filtered_angle34 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle34;
  }
  else if (FLEX_Num==FLEX5){
    filtered_angle5=(0.5335*filtered_angle5 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle5;
  }
  else if (FLEX_Num==FLEX43){
    filtered_angle43=(0.5335*filtered_angle43 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle43;
  }
  else if (FLEX_Num==FLEX32){
    filtered_angle32=(0.5335*filtered_angle32 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle32;
  }
  else if (FLEX_Num==FLEX6){
    filtered_angle6=(0.5335*filtered_angle6 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle6;
  }
  else if (FLEX_Num==FLEX13){
    filtered_angle13=(0.5335*filtered_angle13 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle13;
  }
  else if (FLEX_Num==FLEX31){
    filtered_angle31=(0.5335*filtered_angle31 + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle31;
  }
  else if (FLEX_Num==FLEX42R){
    filtered_angle42R=(0.5335*filtered_angle42R + 0.4665*FLEX_Angle);    //Low Pass Filter
    return filtered_angle42R;
  }
  else{
    return -1; //ERROR STATE
  }
}
