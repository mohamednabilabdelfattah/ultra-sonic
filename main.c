/*
 * main.c
 *
 *  Created on: Oct 15, 2022
 *      Author: Mohamed Nabil
 */


/*******************************************************************************
 *             INCLUDES
 **************************************************************************** */
#include "GPIO/GPIO.h"
#include "ICU/ICU.h"
#include "LCD/lcd.h"
#include "ultrasonic/ultrasonic.h"
#include "std_types.h"
#include "avr/io.h"

/*******************************************************************************
 *             main function
 **************************************************************************** */

int main(void)
{
	/*init ultrasonic*/
	Ultrasonic_init();
	/*init lcd*/
	LCD_init();
	uint16 distance;
	while(1){
		distance = Ultrasonic_readDistance();
		LCD_displayStringRowColumn(0, 0,"Distance = ");
		LCD_intgerToString(distance+1);
	}
}
