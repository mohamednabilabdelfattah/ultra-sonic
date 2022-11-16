/******************************************************************************
 *
 * Module: ultrasonic
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the ultrasonic driver
 *
 * Author: Mohamed Nabil
 *
 *******************************************************************************/


/*******************************************************************************
 *                               INCLUDES                                      *
 *******************************************************************************/

#include "ultrasonic.h"
#include "../ICU/ICU.h"
#include "../GPIO/GPIO.h"
#include "../LCD/lcd.h"
#include "../common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */
#include <util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile uint16 g_time1,g_time2,g_time3;/*the times readen by the ICU to estimate the distance*/
static volatile uint8 g_count ;/*the count of calls of the callback function*/
static volatile uint8 g_flag = LOGIC_LOW;
volatile uint8 x = 0;
/*******************************************************************************
 *                           FUNCTIONS DEFINITIONS                             *
 *******************************************************************************/

/*
 * function name: Ultrasonic_init
 * return type: void
 * params(in): None
 * params(in&out): None
 * params(out): None
 * desciption: this function to init the ultrasonic module
 * */
void Ultrasonic_init(void)
{
	/*init the ICU*/
	Icu_ConfigType conf;
	conf.theClock = F_CPU_8;
	conf.edge = RISING;
	Icu_init(&conf);

	/*set the callback of the ICU*/
	Icu_setCallBack(Ultrasonic_edgeProcessing);

	/*set the type of the trigger pin as output*/
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,PIN_OUTPUT);

}


/*
 * function name: Ultrasonic_Trigger
 * return type: void
 * params(in): None
 * params(in&out): None
 * params(out): None
 * desciption: this function to trigger the ultrasonic to start the process of the sending wave
 * */
void Ultrasonic_Trigger(void){
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOGIC_LOW);
}

/*
 * function name: Ultrasonic_readDistance
 * return type: uint16
 * params(in): None
 * params(in&out): None
 * params(out): None
 * desciption: this function to return the distance estimated by the module
 * */
uint16 Ultrasonic_readDistance(void){
	/*start the process of the reading by triggering the ultrasonic sensor*/
	Ultrasonic_Trigger();
	g_count = 0;
	g_flag = LOGIC_LOW;
	Icu_setEdgeDetectionType(RISING);
	/*wait till the flag to set to read the times*/
	while(g_flag==LOGIC_LOW);
	/*then use the times to read the distance*/
	return (uint16)(g_time1/58);
}


/*
 * function name: Ultrasonic_edgeProcessing
 * return type: void
 * params(in): None
 * params(in&out): None
 * params(out): None
 * desciption: this function to calculate the high time of by the ICU module
 * */
void Ultrasonic_edgeProcessing(void){
	switch(g_count){
	case 0:
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
		g_count++;
		break;
	case 1:
		g_time1 = Icu_getInputCaptureValue();
		g_flag = LOGIC_HIGH;
		break;
	}
}

