/****************************************************/
/* Author   : Hamdy Osama Mohamed                   */
/* Date     : 20/11/2020                             */
/* Version  : V01                                   */
/* File     : FLEX Driver                            */
/****************************************************/
#ifndef FSR_PRIVATE_H
#define FSR_PRIVATE_H

static float Calculate_Angle(float FLEX_Resistance,short FLEX_Num);      //used to calculate force based on specific sensor curve fitting
static float Filter_Angle(float FLEX_Angle,short FLEX_Num);              //used to increment filtered force variable based on specific sensor


#endif
