
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include <stdint.h>
/**
 * @headerfile MCAL_GPIO_Interface.h
 * @brief Header file that contains the interface for GPIO operations.
 */
#include "GPIO_INTERFACE.h"
/**
 * @headerfile RCC_Interface.h
 * @brief Header file that contains the interface for RCC operations.
 */
#include "RCC_Interface.h"


/**
 * @headerfile MCAL_TIM_Interface.h
 * @brief Header file that contains the interface for timer operations.
 */

#include "Timer_interface.h"

/**
 * @headerfile MotorDriver_Interface.h
 * @brief Header file that contains the interface for the motor driver.
 */
#include "MotorDriver_Interface.h"

/**
 * @headerfile MotorDriver_Config.h
 * @brief Header file that contains the configuration for the motor driver.
 */

#include "MotorDriver_Config.h"

#include "Project_Defines.h"

extern PinConfig_t motor_in1_PinConfig;
extern PinConfig_t motor_in2_PinConfig;
extern PinConfig_t motor_in3_PinConfig;
extern PinConfig_t motor_in4_PinConfig;
extern PinConfig_t motorA_pwm_PinConfig;
extern PinConfig_t motorB_pwm_PinConfig;


/******************************************************************************
 * \Syntax          : void Motors_Init(void)

 * \Description     :   This function initializes the motor driver.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : void
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/


void Motors_Init(void)
{
	GPIO_u8PinInit(&motor_in1_PinConfig);
	GPIO_u8PinInit(&motor_in2_PinConfig);
	GPIO_u8PinInit(&motor_in3_PinConfig);
	GPIO_u8PinInit(&motor_in4_PinConfig);

	GPIO_u8PinInit(&motorA_pwm_PinConfig);
	GPIO_u8PinInit(&motorB_pwm_PinConfig);

	GPT_u8InitPwmChannel(MOTORA_TIMER, MOTORA_TIMER_CC);
	GPT_u8InitPwmChannel(MOTORB_TIMER, MOTORB_TIMER_CC);

	MOTORS_Stop();
}



void MOTORS_Forward(uint8_t speed)
{
	Motor1_Forward();
	Motor2_Forward();
	Motors_Speed(speed);
}


void MOTORS_Backward(uint8_t speed)
{
	Motor1_Back();
	Motor2_Back();
	Motors_Speed(speed);
}

void Motors_Speed(uint8_t speed)
{
	Motor1_Speed(speed);
	Motor2_Speed(speed);
}

void MOTORS_Forward_Left(uint8_t speed)
{
	Motor2_Stop();
	Motor1_Forward();
	Motor1_Speed(speed);
}

void MOTORS_Forward_Right(uint8_t speed)
{
	Motor1_Stop();
	Motor2_Forward();
	Motor2_Speed(speed);
}


void MOTORS_Backward_Right(uint8_t speed)
{
	Motor1_Stop();
	Motor2_Back();
	Motor2_Speed(speed);
}

void MOTORS_Backward_Left(uint8_t speed)
{
	Motor1_Back();
	Motor2_Stop();
	Motor1_Speed(speed);
}

void MOTORS_Stop(void)
{
	Motor1_Stop();
	Motor2_Stop();
}


void Motor1_Forward(void)
{
	GPIO_u8SetPinValue(MOTORA_PORT, MOTORDRIVER_IN1, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORA_PORT, MOTORDRIVER_IN2, PIN_LOW);
}

void Motor2_Forward(void)
{
	GPIO_u8SetPinValue(MOTORB_PORT, MOTORDRIVER_IN3, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORB_PORT, MOTORDRIVER_IN4, PIN_LOW);
}

void Motor1_Back(void)
{
	GPIO_u8SetPinValue(MOTORA_PORT, MOTORDRIVER_IN1, PIN_LOW);
	GPIO_u8SetPinValue(MOTORA_PORT, MOTORDRIVER_IN2, PIN_HIGH);
}

void Motor2_Back(void)
{
	GPIO_u8SetPinValue(MOTORB_PORT, MOTORDRIVER_IN3, PIN_LOW);
	GPIO_u8SetPinValue(MOTORB_PORT, MOTORDRIVER_IN4, PIN_HIGH);
}

void Motor1_Stop(void)
{
	GPIO_u8SetPinValue(MOTORA_PORT, MOTORDRIVER_IN1, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORA_PORT, MOTORDRIVER_IN2, PIN_HIGH);
}

void Motor2_Stop(void)
{
	GPIO_u8SetPinValue(MOTORB_PORT, MOTORDRIVER_IN3, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORB_PORT, MOTORDRIVER_IN4, PIN_HIGH);
}

void Motor1_Speed(uint8_t speed)
{
	GPT_u8SetPWM(MOTORA_TIMER, MOTORA_TIMER_CC, 50, speed);
}

void Motor2_Speed(uint8_t speed)
{
	GPT_u8SetPWM(MOTORB_TIMER, MOTORB_TIMER_CC, 50, speed);
}


