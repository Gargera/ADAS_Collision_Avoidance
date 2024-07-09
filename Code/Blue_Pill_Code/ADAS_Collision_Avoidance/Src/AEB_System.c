/*
 * AEB_System.c
 *
 *  Created on: Jun 18, 2024
 *      Author: Gargera & Menna
 */

#include <stdint.h>

#include "AEB_System.h"

#include "Project_Defines.h"

#include "Ultrasonic_Interface.h"

#include "MotorDriver_Interface.h"

#include "Buzzer_Interface.h"

#include "SYSTICK_interface.h"

extern uint8_t Move;
extern uint8_t Current_Speed;

extern uint8_t Buzzer_ON;

extern Ultrasonic_t Ultrasonic_BackConf;
extern Ultrasonic_t Ultrasonic_FrontConf;

extern Buzzer_t Buzzer1;

extern uint8_t G_u8DataFromBluetooth;

uint32_t Distance_From_Ultrasonic = 0;

void AEB()
{
	if(Move == MOVE_FORWARD || Move == MOVE_LEFT_FORWARD || Move == MOVE_RIGHT_FORWARD)
	{
		Distance_From_Ultrasonic = Ultrasonic_readDistance(&Ultrasonic_FrontConf);
	}
	else
	{
		Distance_From_Ultrasonic = Ultrasonic_readDistance(&Ultrasonic_BackConf);
	}


	if(Distance_From_Ultrasonic < MINIMUM_DISTANCE)
	{
		MOTORS_Stop();
		Current_Speed = 0;
		Buzzer_vTurnOff(&Buzzer1);
		Buzzer_ON = 0;
	}
	else if(Distance_From_Ultrasonic <= MAXIMUM_DISTANCE) //Buzzer ON , Warning
	{
		if(!Buzzer_ON && Current_Speed != 0)
		{
			Buzzer_ON = 1;
			Buzzer_vTurnOn(&Buzzer1);
		}
		else if(Buzzer_ON && Current_Speed == 0)
		{
			Buzzer_ON = 0;
			Buzzer_vTurnOff(&Buzzer1);
		}
		else{}

		//apply 40% speed if the current speed above 40%
		if(Current_Speed > SPEED_40)
		{
			Current_Speed = SPEED_40;
			G_u8DataFromBluetooth = Move;
		}
		else{}
	}
	else
	{
		if(Buzzer_ON)
		{
			Buzzer_ON = 0;
			Buzzer_vTurnOff(&Buzzer1);
		}
		else{};
	}
}
