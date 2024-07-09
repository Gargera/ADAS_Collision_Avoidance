/*
 * RCC_Program.c
 *
 *  Created on: Jun 15, 2024
 *      Author: Gargera
 */

#include <stdint.h>
#include "Bit_Math.h"
#include "Stm32F103xx.h"

#include "RCC_Interface.h"

void RCC_EnablePeripheral(RCC_Bus_t bus , uint8_t peripheral)
{
	switch (bus)
	{
	case AHB:  SET_BIT(RCC->AHBENR , peripheral);  break;

	case APB1: SET_BIT(RCC->APB1ENR , peripheral);  break;

	case APB2: SET_BIT(RCC->APB2ENR , peripheral);  break;

	default: break;
	}
}

void RCC_DisablePeripheral(RCC_Bus_t bus , uint8_t peripheral)
{
	switch (bus)
	{
	case AHB:  CLR_BIT(RCC->AHBENR , peripheral);  break;

	case APB1: CLR_BIT(RCC->APB1ENR , peripheral);  break;

	case APB2: CLR_BIT(RCC->APB2ENR , peripheral);  break;

	default: break;
	}
}
