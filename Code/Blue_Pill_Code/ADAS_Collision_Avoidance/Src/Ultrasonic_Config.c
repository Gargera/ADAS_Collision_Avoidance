/*
 * Ultrasonic_Config.c
 *
 *  Created on: Apr 1, 2024
 *      Author: Gargera
 */

#include <stdint.h>
#include "Stm32F103xx.h"
#include "Bit_Math.h"

#include "GPIO_INTERFACE.h"
#include "Ultrasonic_Interface.h"
#include "Project_Defines.h"


Ultrasonic_t Ultrasonic_FrontConf =
{
		.TrigPort = ULTRASONIC_FRONT_TRIG_PORT,
		.TrigPin  = ULTRASONIC_FRONT_TRIG_PIN,
		.EchoPort = ULTRASONICS_ECHO_PORT,
		.EchoPin  = ULTRASONICS_ECHO_PIN
};
Ultrasonic_t Ultrasonic_BackConf =
{
		.TrigPort = ULTRASONIC_BACK_TRIG_PORT,
		.TrigPin  = ULTRASONIC_BACK_TRIG_PIN,
		.EchoPort = ULTRASONICS_ECHO_PORT,
		.EchoPin  = ULTRASONICS_ECHO_PIN
};
