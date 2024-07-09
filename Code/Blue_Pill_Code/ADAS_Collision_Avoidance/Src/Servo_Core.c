#include <stdint.h>
#include "Stm32F103xx.h"
#include "Bit_Math.h"

#include "GPIO_INTERFACE.h"
#include "RCC_Interface.h"
#include "Timer_interface.h"
#include "GPT_interface.h"

#include "Servo_Core.h"
#include "Project_Defines.h"
#include "Servo_Config.h"

extern const PinConfig_t SERVO1_PinConfig;

void servo_init(void)
{
	GPIO_u8PinInit(&SERVO1_PinConfig);

	GPT_u8InitPwmChannel(SERVO_TIMER, SERVO_CHANNEL);

}

void Servo_Motor_GENERATE(uint8_t Dgree)
{

	/*if(Dgree<0){Dgree=0;}
	if(Dgree>180){Dgree=180;}*/
	/* Dgree = (Dgree/15) + 5;*/
	GPT_u8SetPWM(SERVO_TIMER, SERVO_CHANNEL, 50, Dgree);

}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
