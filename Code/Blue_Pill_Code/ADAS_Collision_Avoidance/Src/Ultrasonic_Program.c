/*
 * Ultrasonic_Program.c
 *
 *  Created on: Apr 1, 2024
 *      Author: Gargera
 */

#include <stdint.h>
#include "Stm32F103xx.h"
#include "Bit_Math.h"

#include "Ultrasonic_Interface.h"
#include "Ultrasonic_Private.h"

#include "GPIO_INTERFACE.h"

#include "SYSTICK_interface.h"

extern PinConfig_t Ultrasonics_Echo_Pin;
extern PinConfig_t Front_Ultrasonic_Trig_Pin;
extern PinConfig_t Back_Ultrasonic_Trig_Pin;
//extern PinConfig_t Left_Ultrasonic_Trig_Pin;


/*
 * @fn		:	Ultrasonic_Init
 * @brief	:	Initializes the Ultrasonic
 * @param	:	void
 * @retval	:	void
 *
 * */
void Ultrasonic_Init (void)
{
	GPIO_u8PinInit(&Ultrasonics_Echo_Pin);

	SYSTICK_DelayMs(486);

	GPIO_u8PinInit(&Front_Ultrasonic_Trig_Pin);
	GPIO_u8PinInit(&Back_Ultrasonic_Trig_Pin);

	SYSTICK_DelayMs(1);
}


/*
 * @fn		:	Ultrasonic_readDistance
 * @brief	:	Calculates the distance
 * @param	:	Ultrasonic_Conf     (Ultrasonic_t*)
 * @retval	:	uint32_t
 *
 * */
uint32_t Ultrasonic_readDistance (Ultrasonic_t* Ultrasonic_Conf)
{
	uint32_t TicksNumber = 0 , Local_TimeoutCounter = 0;
	uint32_t Distance    = 0;

	/*trig pulse to trigger pin
	 * 3us low
	 * 10us high
	 * then low
	 */
	GPIO_u8SetPinValue(Ultrasonic_Conf->TrigPort , Ultrasonic_Conf->TrigPin , PIN_LOW);
	SYSTICK_DelayUs(TIME_FOR_LOW_PULSE);
	GPIO_u8SetPinValue(Ultrasonic_Conf->TrigPort , Ultrasonic_Conf->TrigPin , PIN_HIGH);
	SYSTICK_DelayUs(TIME_FOR_HIGH_PULSE);
	GPIO_u8SetPinValue(Ultrasonic_Conf->TrigPort , Ultrasonic_Conf->TrigPin , PIN_LOW);

	/*wait for generate 8 pulses (40KHZ)*/
	SYSTICK_DelayUs(TIME_FOR_EIGHT_PULSES) ;

	/*wait until generating rising edge for echo pin*/
	while (1){
		PinVal_t  PinVal = PIN_LOW;
		GPIO_u8ReadPinValue( Ultrasonic_Conf->EchoPort , Ultrasonic_Conf->EchoPin , &PinVal);
		if(PinVal == PIN_HIGH) break;
	}

	while (Local_TimeoutCounter < ULTRASONIC_TIMEOUT)
	{
		PinVal_t  PinVal = PIN_HIGH;
		GPIO_u8ReadPinValue( Ultrasonic_Conf->EchoPort , Ultrasonic_Conf->EchoPin , &PinVal);
		if(PinVal == PIN_LOW) break;

		Local_TimeoutCounter ++;

		/*each iteration take 4.9 us*/
		TicksNumber ++ ;
		SYSTICK_DelayUs(2) ;
	}

	if(Local_TimeoutCounter == ULTRASONIC_TIMEOUT){
		Distance = -1;
	}
	else{
	    Distance = (TicksNumber + 0) * TIME_OF_EACH_ITERATION_IN_MICRO * SPEED_OF_SIGNAL_CM_PER_U;
	    Distance = Distance / 2;
	}

	return Distance ;
}
