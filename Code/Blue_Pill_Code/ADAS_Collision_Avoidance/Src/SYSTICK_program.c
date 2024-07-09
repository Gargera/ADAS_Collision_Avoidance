/*
 * SYSTICK_program.c
 *
 *  Created on: Jun 15, 2024
 *      Author: Eman
 */

#include <stdint.h>
#include "Stm32F103xx.h"
#include "Bit_Math.h"

#include "SYSTICK_private.h"
#include "SYSTICK_interface.h"



void SYSTICK_DelayMs(uint32_t Copy_u32TimeMs)
{

	/* Set the clock source for the SYSTICK timer */
	SYSTICK -> CSR |= (1 << CLKSOURCE);
	/*Reset the current SYSTICK counter value */
	SYSTICK -> CVR = INITIAL_LOAD_VAL;
	/* Set the reload value for the SYSTICK timer based on the desired delay time */
	SYSTICK -> RVR = (Copy_u32TimeMs * (SYSTEM_FREQUANCY/_10POW3));
	/* Enable the SYSTICK timer */
	SYSTICK -> CSR |= (1 << STKENABLE);
	/*   Busy waiting loop to wait for the COUNTFLAG to indicate that the timer has reached 0 */
	while( (((SYSTICK->CSR) >> COUNTFLAG) & NUM) != READY_FLAG)
	{
		/*nothing*/
	}
}

void SYSTICK_DelayUs(uint32_t Copy_u32TimeUs)
{
	/* Set the clock source for the SYSTICK timer */
	SYSTICK -> CSR |= (1 << CLKSOURCE);
	/* Set the reload value for the SYSTICK timer based on the desired delay time in microseconds */
	SYSTICK -> RVR = (Copy_u32TimeUs * (SYSTEM_FREQUANCY/_10POW6));
	/* Reset the current SYSTICK counter value */
	SYSTICK-> CVR = INITIAL_LOAD_VAL;
	/* Enable the SYSTICK timer */
	SYSTICK -> CSR |= (1 << STKENABLE);
	/* Busy waiting loop to wait for the COUNTFLAG to indicate that the timer has reached 0 */
	while( (((SYSTICK->CSR) >> COUNTFLAG) & NUM) != READY_FLAG)
	{
		/*nothing*/
	}
}
