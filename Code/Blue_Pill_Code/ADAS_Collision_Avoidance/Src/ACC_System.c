/*
 * ACC_System.c
 *
 *  Created on: Jun 20, 2024
 *      Author: Eman & Toqa
 */

#include <stdint.h>

#include "ACC_System.h"

#include "Project_Defines.h"

#include "Ultrasonic_Interface.h"

#include "MotorDriver_Interface.h"

#include "SYSTICK_interface.h"

#include "USART_Interface.h"

uint32_t Ultrasonic_Distance_value = 0;

extern uint8_t Move;
extern uint8_t Current_Speed;

extern Ultrasonic_t Ultrasonic_FrontConf;
extern uint8_t G_u8DataFromRaspberrypi;



void ACC(void)
{
	Ultrasonic_Distance_value =	Ultrasonic_readDistance(&Ultrasonic_FrontConf);
	uint8_t SpeedFromFrontCar = G_u8DataFromRaspberrypi;

	if (Ultrasonic_Distance_value < SAFE_DISTANCE)
	{
		Current_Speed = SpeedFromFrontCar  ;
		MOTORS_Forward(Current_Speed);
	}

	else if (Ultrasonic_Distance_value >= SAFE_DISTANCE)
	{
		Current_Speed = MAX_SPEED;
		MOTORS_Forward(Current_Speed);
	}
	else{}

	SYSTICK_DelayMs(100);
}
