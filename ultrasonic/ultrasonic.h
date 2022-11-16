 /******************************************************************************
 *
 * Module: ultrasonic
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the ultrasonic driver
 *
 * Author: Mohamed Nabil
 *
 *******************************************************************************/


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/**********************************************************************************************************************
 * INCLUDES
 * ********************************************************************************************************************/
#include "../std_types.h"

/**********************************************************************************************************************
 * FUNCTION PROTOTYPES
 * ********************************************************************************************************************/

#define ULTRASONIC_TRIGGER_PORT PORTB_ID
#define ULTRASONIC_TRIGGER_PIN 5

/**********************************************************************************************************************
 * FUNCTION PROTOTYPES
 * ********************************************************************************************************************/

/*
 * function name: Ultrasonic_init
 * return type: void
 * params(in): None
 * params(in&out): None
 * params(out): None
 * desciption: this function to init the ultrasonic module
 * */
 void Ultrasonic_init(void);
 
 
/*
 * function name: Ultrasonic_Trigger
 * return type: void
 * params(in): None
 * params(in&out): None
 * params(out): None
 * desciption: this function to trigger the ultrasonic to start the process of the sending wave
 * */
 void Ultrasonic_Trigger(void);

/*
 * function name: Ultrasonic_readDistance
 * return type: uint16
 * params(in): None
 * params(in&out): None
 * params(out): None
 * desciption: this function to return the distance estimated by the module
 * */
uint16 Ultrasonic_readDistance(void);


/*
 * function name: Ultrasonic_edgeProcessing
 * return type: void
 * params(in): None
 * params(in&out): None
 * params(out): None
 * desciption: this function to calculate the high time of by the ICU module
 * */
 void Ultrasonic_edgeProcessing(void);
 
#endif


