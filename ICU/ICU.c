/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: ICU.c
 *
 * Description: Source file for the AVR ICU driver
 *
 * Author: Mohamed Nabil
 *
 * Date created : 15/10/2022
 *
 *******************************************************************************/

#include "ICU.h"
#include "../GPIO/GPIO.h"
#include "../common_macros.h"
#include "../LCD/lcd.h"
#include "../std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>
/*******************************************************************************
 *                      Global Variables                                        *
 *******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;  /*the pointer of the callback function*/


/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void Icu_init(const Icu_ConfigType * Config_Ptr)
{
	/*enable interrupts*/
	SREG |= (1<<7);
	/*set the direction of the pin 5 in port D as input*/
	GPIO_setupPinDirection(PORTD_ID,PIN6_ID,PIN_INPUT);

	/*set the edge type*/
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<6);

	/*set the initial value of counting*/
	TCNT1 = 0;

	/*set the initial value of ICR1*/
	ICR1 = 0;

	/*set the clock*/
	TCCR1B = (TCCR1B&0xF8) | (Config_Ptr -> theClock);

	/*set the compare mode of timer1*/
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	/*enable the interrupt of the ICU*/
	TIMSK |= (LOGIC_HIGH << TICIE1);

}

/*
 * Description: Function to set the Call Back function address.
 */
void Icu_setCallBack(void(*a_ptr)(void)){
	/*initialize the global variable to passed value*/
	g_callBackPtr = a_ptr;
}

/*
 * Description: Function to set the required edge detection.
 */
void Icu_setEdgeDetectionType(const Icu_EdgeType edgeType)
{
	TCCR1B = (TCCR1B & 0xBF) | (edgeType <<6);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void){
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void){
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_DeInit(void){

	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}

ISR(TIMER1_CAPT_vect)
{

	/*will call the call back function*/
	if(g_callBackPtr!=NULL_PTR){
		(*g_callBackPtr)();
	}

}


