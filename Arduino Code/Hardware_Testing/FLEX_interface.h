/****************************************************/
/* Author   : Hamdy Osama Mohamed                   */
/* Date     : 20/11/2020                             */
/* Version  : V01                                   */
/* File     : FLEX Driver                            */
/****************************************************/
#ifndef FLEX_INTERFACE_H
#define FLEX_INTERFACE_H

/*Function Prototypes*/
int FLEX_Pin_Reading(short FLEX_Pin);      					/*used to get average voltage reading from FLEX Sensor*/
float FLEX_Resistance(short FLEX_Pin);       					/*used to get Sensor Resistance value*/ 
float FLEX_Angle(short FLEX_Pin,short FLEX_Num);      /*used to get predicted Angle on sensor from model*/ 
 //Note About FLEX_Angle....
 // starts reading values above 9 degrees deflection 
 // requires giving the parameter FLEX_Num that represents the Flex sesnor used
 // check the back of the Flex Sensor and choose approriate Macro from below...

/*Interface Definitions:*/
//FLEX_Num Options
#define FLEX5       5
#define FLEX6       6
#define FLEX13     13
#define FLEX21     21
#define FLEX24     24
#define FLEX29     29
#define FLEX31     31
#define FLEX32     32
#define FLEX34     34
#define FLEX42     42
#define FLEX42R    44
#define FLEX43     43



#endif
