/*
 * Buzzer_Program.c
 *
 *  Created on: Jun 30, 2024
 *      Author: Gargera
 */

#include <stdint.h>
#include "Stm32F103xx.h"
#include "Bit_Math.h"

#include "Buzzer_Interface.h"

#include "GPIO_INTERFACE.h"

#include "Project_Defines.h"

extern PinConfig_t Buzzer1_PinConfig;

/*
 * @fn		:	Buzzer_vInit
 * @brief	:	Initializes the Buzzer
 * @param	:	void
 * @retval	:	void
 */
void Buzzer_vInit(void)
{
	GPIO_u8PinInit(&Buzzer1_PinConfig);
}

/*
 * @fn		:	Buzzer_vTurnOn
 * @brief	:	Turn on the Buzzer
 * @param	:	Buzzer_Conf     (Buzzer_t*)
 * @retval	:	void
 */
void Buzzer_vTurnOn(Buzzer_t* Buzzer_Conf)
{
	GPIO_u8SetPinValue(Buzzer_Conf->BuzzerPort , Buzzer_Conf->BuzzerPin , PIN_HIGH);
}

/*
 * @fn		:	Buzzer_vTurnOff
 * @brief	:	Turn off the Buzzer
 * @param	:	Buzzer_Conf     (Buzzer_t*)
 * @retval	:	void
 */
void Buzzer_vTurnOff(Buzzer_t* Buzzer_Conf)
{
	GPIO_u8SetPinValue(Buzzer_Conf->BuzzerPort , Buzzer_Conf->BuzzerPin , PIN_LOW);
}

/*
 * @fn		:	Buzzer_vToggle
 * @brief	:	Toggle the Buzzer
 * @param	:	Buzzer_Conf     (Buzzer_t*)
 * @retval	:	void
 */
void Buzzer_vToggle(Buzzer_t* Buzzer_Conf)
{
	GPIO_u8TogglePinValue(Buzzer_Conf->BuzzerPort , Buzzer_Conf->BuzzerPin);
}

/*
 * @fn		:	Buzzer_ReadStatues
 * @brief	:	Read the Buzzer Statues
 * @param	:	Buzzer_Conf     (Buzzer_t*)
 * @retval	:	uint8_t
 */
uint8_t Buzzer_ReadStatues(Buzzer_t* Buzzer_Conf)
{
	PinVal_t PinVal;
	GPIO_u8ReadPinValue(Buzzer_Conf->BuzzerPort , Buzzer_Conf->BuzzerPin , &PinVal);
	return PinVal;
}
