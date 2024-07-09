/*
 * Buzzer_Config.c
 *
 *  Created on: Jun 30, 2024
 *      Author: Gargera
 */

#include <stdint.h>

#include "GPIO_INTERFACE.h"

#include "Buzzer_Interface.h"

#include "Project_Defines.h"

Buzzer_t Buzzer1 =
{
		.BuzzerPort = Buzzer1_PORT,
		.BuzzerPin  = Buzzer1_PIN
};
