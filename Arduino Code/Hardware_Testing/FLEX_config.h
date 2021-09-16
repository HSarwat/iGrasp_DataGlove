/****************************************************/
/* Author   : Hamdy Osama Mohamed                   */
/* Date     : 20/11/2020                             */
/* Version  : V01                                   */
/* File     : FLEX Driver                            */
/****************************************************/
#ifndef FLEX_CONFIG_H
#define FLEX_CONFIG_H

/*Driver Configuration*/
//Choose number of sensor readings to take average on
/*Options: Write positive number to determine # of readings
           Default Value = 10     range (1:255)
           Note that larger # of readings will cause slower system
 */
 #define NUMBER_OF_READINGS    40

//Choose Resistance Value in Voltage divider configuration (Vanalog to Ground)
/*Options: Write Value of Resistance in Ohms
           Default Value of 10KOHM =   10000           
*/
 #define CONSTANT_RESISTANCE   50000

#endif
