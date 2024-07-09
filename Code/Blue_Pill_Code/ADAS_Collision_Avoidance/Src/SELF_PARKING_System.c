/*
 * SELF_PARKING_System.C
 *
 *  Created on: Jun 10, 2024
 *      Author: Amina & Doha & Esraa
 */

#include <stdint.h>

#include "SELF_PARKING_System.h"

#include "Project_Defines.h"

#include "Ultrasonic_Interface.h"

#include "MotorDriver_Interface.h"

#include "SYSTICK_interface.h"

#include "Servo_Core.h"


extern uint8_t Move;
extern uint8_t Current_Speed;

extern Ultrasonic_t Ultrasonic_BackConf;
extern Ultrasonic_t Ultrasonic_FrontConf;

uint32_t front_ultrasonic_distance = 0 , back_ultrasonic_distance = 0/*,front2_ultrasonic_distance = 0*/;

uint8_t PARKING_SAFE , status = 0,parking_speed=0;


void SELF_PARKING()
{
	parking_speed=PARKING_SPEED;

	/*must be sure he is in the right position*/

	/*Back right*/

	PARKING_SAFE=1;
	uint8_t x=0;
	Servo_Motor_GENERATE(0);

	while(x<MAX_ANGLE)
	{
		Servo_Motor_GENERATE(x);
		SYSTICK_DelayMs(50);
		x++;

	}

	SYSTICK_DelayMs(500);
	MOTORS_Backward_Right(parking_speed);

	while(PARKING_SAFE==1)
	{

		back_ultrasonic_distance  = Ultrasonic_readDistance (& Ultrasonic_BackConf);
		if(back_ultrasonic_distance<=P_FORWARD_DISTANCE)
		{
			MOTORS_Stop();
			PARKING_SAFE=0;
		}


	}



	SYSTICK_DelayMs(1000);
	SYSTICK_DelayMs(1000);

	Servo_Motor_GENERATE(0);
	x=0;
	while(x<MIN_ANGLE)
	{
		Servo_Motor_GENERATE(x);
		SYSTICK_DelayMs(50);
		x++;

	}

	SYSTICK_DelayMs(1000);
	PARKING_SAFE=1;
	MOTORS_Backward_Left(parking_speed);



	while(PARKING_SAFE==1){

		back_ultrasonic_distance  = Ultrasonic_readDistance (& Ultrasonic_BackConf);
		if(back_ultrasonic_distance<=P_MIN_SAFE_DISTANCE)
		{
			MOTORS_Stop();
			PARKING_SAFE=0;

		}

	}



	/*forward*/
	SYSTICK_DelayMs(1000);
	PARKING_SAFE=1;
	front_ultrasonic_distance= Ultrasonic_readDistance (&Ultrasonic_BackConf);

	if(front_ultrasonic_distance>P_FORWARD_DISTANCE)
	{
		MOTORS_Forward(parking_speed-15);
	}
	while(front_ultrasonic_distance>=P_FORWARD_DISTANCE)
	{
		front_ultrasonic_distance  = Ultrasonic_readDistance (& Ultrasonic_FrontConf);
	}
	MOTORS_Stop();



}
























/*
void SELF_PARKING()
{
	PARKING_SAFE = 1;

	MOTORS_Backward_Right(PARKING_SPEED);
	SYSTICK_DelayMs(500);

	while(PARKING_SAFE == 1){

		for( uint8_t i = MIN_ANGLE ; i <= MAX_ANGLE ; i += ANGLE_STEP)
		{
			Servo_Motor_GENERATE( i );
			front_ultrasonic_distance = Ultrasonic_readDistance(&Ultrasonic_FrontConf);
			back_ultrasonic_distance = Ultrasonic_readDistance(&Ultrasonic_BackConf);
			if(PARKING_SAFE == 0 || front_ultrasonic_distance <= P_MIN_SAFE_DISTANCE || back_ultrasonic_distance <= P_MIN_SAFE_DISTANCE)
			{
				MOTORS_Stop();
				PARKING_SAFE=0;
				break;
			}
			SYSTICK_DelayMs(10);
		}


		for(int i = MAX_ANGLE ; i >= MIN_ANGLE ; i -= ANGLE_STEP)
		{
			Servo_Motor_GENERATE(i);
			front_ultrasonic_distance  = Ultrasonic_readDistance(&Ultrasonic_FrontConf);
			back_ultrasonic_distance = Ultrasonic_readDistance(&Ultrasonic_BackConf);
			if(PARKING_SAFE == 0 || front_ultrasonic_distance <= P_MIN_SAFE_DISTANCE || back_ultrasonic_distance <= P_MIN_SAFE_DISTANCE)
			{
				MOTORS_Stop();
				PARKING_SAFE=0;
				break;
			}
		}
	}
	SYSTICK_DelayMs(1000);
	SYSTICK_DelayMs(1000);

	PARKING_SAFE = 1;
	MOTORS_Backward_Left(PARKING_SPEED);


	while(PARKING_SAFE == 1)
	{
		for(uint8_t i = MIN_ANGLE ; i <= MAX_ANGLE ; i += ANGLE_STEP)
		{
			Servo_Motor_GENERATE( i );
			front_ultrasonic_distance  = Ultrasonic_readDistance(&Ultrasonic_FrontConf);
			back_ultrasonic_distance = Ultrasonic_readDistance(&Ultrasonic_BackConf);
			if(PARKING_SAFE == 0 || front_ultrasonic_distance <= P_MIN_SAFE_DISTANCE || back_ultrasonic_distance <= P_MIN_SAFE_DISTANCE)
			{
				MOTORS_Stop();
				PARKING_SAFE=0;
				break;
			}
			SYSTICK_DelayMs(10);
		}


		for(int i = MAX_ANGLE ; i >= MIN_ANGLE ; i -= ANGLE_STEP)
		{
			Servo_Motor_GENERATE(i);
			front_ultrasonic_distance  = Ultrasonic_readDistance(&Ultrasonic_FrontConf);
			back_ultrasonic_distance = Ultrasonic_readDistance(&Ultrasonic_BackConf);
			if(PARKING_SAFE == 0 || front_ultrasonic_distance <= P_MIN_SAFE_DISTANCE || back_ultrasonic_distance <= P_MIN_SAFE_DISTANCE)
			{
				MOTORS_Stop();
				PARKING_SAFE=0;
				break;
			}
		}
	}



	SYSTICK_DelayMs(1000);
	SYSTICK_DelayMs(1000);

	PARKING_SAFE = 1;

	Servo_Motor_GENERATE(MIN_ANGLE);

	MOTORS_Forward(PARKING_SPEED);

	while(front_ultrasonic_distance >= P_FORWARD_DISTANCE)
	{
		front_ultrasonic_distance  = Ultrasonic_readDistance(&Ultrasonic_FrontConf);
		//back_ultrasonic_distance= Ultrasonic_readDistance (&Ultrasonic_BackConf);
	}
	MOTORS_Stop();
}

 */

/*PARKING_SAFE=0;

	while(PARKING_SAFE==0&&status<2){
		if(status==0&&PARKING_SAFE==0)
		{
			MOTORS_Back_Right(PARKING_SPEED);
			status=1;

		}
		else if(PARKING_SAFE==1&&status==1)

		{
			SYSTICK_DelayMs(1000);
			SYSTICK_DelayMs(1000);
			MOTORS_Back_Left(PARKING_SPEED);
			PARKING_SAFE=0;
			status=2;
		}
		if(PARKING_SAFE==0)
		{
			for( uint8_t i=MIN_ANGLE;i<=MAX_ANGLE;i+=ANGLE_STEP)
			{

				Servo_Motor_GENERATE( i );
				front_ultrasonic_distance  = Ultrasonic_readDistance (& Ultrasonic_FrontConf);
				back_ultrasonic_distance= Ultrasonic_readDistance (&Ultrasonic_BackConf);
				if(front_ultrasonic_distance<=P_MIN_SAFE_DISTANCE||back_ultrasonic_distance<=P_MIN_SAFE_DISTANCE)
				{
					MOTORS_Stop();
					PARKING_SAFE=1;

					break;
				}
				SYSTICK_DelayMs(10);


			}
		}
		if(PARKING_SAFE==0)
		{
			for(int i=MAX_ANGLE;i>=MIN_ANGLE;i-=ANGLE_STEP)
			{
				Servo_Motor_GENERATE(i);
				front_ultrasonic_distance  = Ultrasonic_readDistance (& Ultrasonic_FrontConf);
				back_ultrasonic_distance= Ultrasonic_readDistance (&Ultrasonic_BackConf);
				if(front_ultrasonic_distance<=P_MIN_SAFE_DISTANCE||back_ultrasonic_distance<=P_MIN_SAFE_DISTANCE)
				{
					MOTORS_Stop();
					PARKING_SAFE++;
					break;

				}

			}
		}



	}

 */
