#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include "error_typ.h"
/*******************************************************************************
 *                        		Definitions                                    *
 *******************************************************************************/

/*******************************************************************************
 *                 	     		Advanced Timers                               *
 *******************************************************************************/
#define TIMER_u8_1								1

/*******************************************************************************
 *                 	     		Counting Direction	                           *
 *******************************************************************************/
#define TIMER1_u8_COUNT_UP					0
#define TIMER1_u8_COUNT_DOWN				1

/*******************************************************************************
 *                 	     		Pwm Channels		                           *
 *******************************************************************************/
#define TIMER1_u8_PWM_CHANNEL1					0
#define TIMER1_u8_PWM_CHANNEL2					1
#define TIMER1_u8_PWM_CHANNEL3					2
#define TIMER1_u8_PWM_CHANNEL4					3

/*******************************************************************************
 *                    		  Functions Prototypes                             *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:		TIMER1_u8Init
 * Description:			Function to initialize timer1
 * Parameters (in):    	Timer direction (up or down) and the prescaler
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t TIMER1_u8Init(uint8_t Copy_u8Direction , uint16_t Copy_u16Prescaler);

/*******************************************************************************
 * Function Name:		TIMER1_u8SetBusyWait
 * Description:			Function to create delay with the timer 1
 * Parameters (in):    	Number of ticks and the repetition number
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t TIMER1_u8SetBusyWait(uint16_t Copy_u32NumOfTicks , uint8_t Copy_u8RepetitionNumebr);

/*******************************************************************************
 * Function Name:		TIMER1_u8SetIntervalPeriodic
 * Description:			Number of ticks, repetition number and pointer to function to act as ISR
 * Parameters (in):    	void
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t TIMER1_u8SetIntervalPeriodic(uint16_t Copy_u32NumOfTicks , uint8_t Copy_u8RepetitionNumebr , void(*Copy_pf)(void));

/*******************************************************************************
 * Function Name:		TIMER1_u8InitPwmChannel
 * Description:			Function to initialize PWM channel
 * Parameters (in):    	Channel Number
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t TIMER1_u8InitPwmChannel(uint8_t Copy_u8PwmChannel);

/*******************************************************************************
 * Function Name:		TIMER1_u8SetPWM
 * Description:			Function to create PWM with the timer 1
 * Parameters (in):    	Frequency , duty cycle and channel number
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t TIMER1_u8SetPWM(uint8_t Copy_u8PwmChannel , uint8_t Copy_u8PwmFrequency , float Copy_u8PwmDutyCycle);

/*******************************************************************************
 * Function Name:		TIMER1_u8Stop
 * Description:			Function to stop and disable the timer
 * Parameters (in):    	void
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t TIMER1_u8Stop(void);

#endif
