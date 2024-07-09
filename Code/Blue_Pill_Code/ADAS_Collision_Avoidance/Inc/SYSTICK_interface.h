/*
 * SYSTICK_interface.h
 *
 *  Created on: Jun 15, 2024
 *      Author: Eman
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

#define READY_FLAG              1
#define INITIAL_LOAD_VAL        0
#define NUM			0x01


typedef enum{
	STKENABLE=0,
	TICKINT,
	CLKSOURCE,
	COUNTFLAG=16
}CSR_t;




/* delay for no of millisec */
void SYSTICK_DelayMs(uint32_t Copy_u32TimeMs);

/* delay for no of microsec */
void SYSTICK_DelayUs(uint32_t Copy_u32TimeUs);



#endif /* SYSTICK_INTERFACE_H_ */
