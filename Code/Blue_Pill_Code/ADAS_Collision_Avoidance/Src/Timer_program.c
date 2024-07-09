#include <stdint.h>
#include "Stm32F103xx.h"
#include "error_typ.h"
#include "Bit_Math.h"

#include "RCC_Interface.h"
#include "GPIO_INTERFACE.h"

#include "Timer_interface.h"
#include "Timer_private.h"
#include "Timer_config.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* to store the address of the function to be the ISR */
static void (*TIMER1_Pf)(void) = NULL;

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:		TIMER1_u8SetBusyWait
 ********************************************************************************/
uint8_t TIMER1_u8Init(uint8_t Copy_u8Direction , uint16_t Copy_u16Prescaler)
{
	uint8_t Local_u8ErrorState = OK;

	TIMER1->CR1 = 0;
	SET_BIT(TIMER1->CR1,7); /* Auto reload pre-load enable */
	TIMER1->CR1 |= ((Copy_u8Direction & 0b1) << 4); /* Set the direction up or down */
	TIMER1->PSC = ( Copy_u16Prescaler - 1 ) ;

	return Local_u8ErrorState;
}

/*******************************************************************************
 * Function Name:		TIMER1_u8SetBusyWait
 ********************************************************************************/
uint8_t TIMER1_u8SetBusyWait(uint16_t Copy_u32NumOfTicks , uint8_t Copy_u8RepetitionNumebr)
{
	uint8_t Local_u8ErrorState = OK;

	CLR_BIT(TIMER1->DIER,0); /* Disable the interrupt */
	TIMER1->ARR = (Copy_u32NumOfTicks & 0xFFFF);
	TIMER1->RCR = ((Copy_u8RepetitionNumebr - 1) & 0xFF);
	SET_BIT(TIMER1->CR1,0); /* Enable The timer */
	while(GET_BIT(TIMER1->SR,0) == 0); /* Wait until update occurs */
	CLR_BIT(TIMER1->SR,0); /* Clear the update flag */
	CLR_BIT(TIMER1->CR1,0); /* Disable The timer */

	return Local_u8ErrorState;
}

/*******************************************************************************
 * Function Name:		TIMER1_u8SetIntervalPeriodic
 ********************************************************************************/
uint8_t TIMER1_u8SetIntervalPeriodic(uint16_t Copy_u32NumOfTicks , uint8_t Copy_u8RepetitionNumebr , void(*Copy_pf)(void))
{
	uint8_t Local_u8ErrorState = OK;

	if(Copy_pf != NULL)
	{
		TIMER1_Pf = Copy_pf;
		TIMER1->ARR = (Copy_u32NumOfTicks & 0xFFFF);
		TIMER1->RCR = ((Copy_u8RepetitionNumebr - 1) & 0xFF);
		SET_BIT(TIMER1->DIER,0); /* Enable the interrupt */
		SET_BIT(TIMER1->CR1,0); /* Enable The timer */
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
 * Function Name:		TIMER1_u8InitPwmChannel
 ********************************************************************************/
uint8_t TIMER1_u8InitPwmChannel(uint8_t Copy_u8PwmChannel)
{
	uint8_t Local_u8ErrorState = OK;

	switch(Copy_u8PwmChannel)
	{
	case TIMER1_u8_PWM_CHANNEL1:
		TIMER1->CCMR1 &= ~(0b11); /* Channel is output compare */
		SET_BIT(TIMER1->CCMR1,3); /* Output compare preload enable */
		TIMER1->CCMR1 |= (0b11 << 5); /* PWM mode 1 */
		CLR_BIT(TIMER1->CCMR1,4); /* PWM mode 1 */
		CLR_BIT(TIMER1->CCER,1); /* high output polarity */
		SET_BIT(TIMER1->CCER,0); /* Output enable */
		break;

	case TIMER1_u8_PWM_CHANNEL2:
		TIMER1->CCMR1 &= ~(0b11<<8);
		SET_BIT(TIMER1->CCMR1,11);
		TIMER1->CCMR1 |= (0b11 << 13);
		CLR_BIT(TIMER1->CCMR1,12);
		CLR_BIT(TIMER1->CCER,5);
		SET_BIT(TIMER1->CCER,4);
		break;

	case TIMER1_u8_PWM_CHANNEL3:
		TIMER1->CCMR2 &= ~(0b11);
		SET_BIT(TIMER1->CCMR2,3);
		TIMER1->CCMR2 |= (0b11 << 5);
		CLR_BIT(TIMER1->CCMR2,4);
		CLR_BIT(TIMER1->CCER,9);
		SET_BIT(TIMER1->CCER,8);
		break;

	case TIMER1_u8_PWM_CHANNEL4:
		TIMER1->CCMR2 &= ~(0b11<<8);
		SET_BIT(TIMER1->CCMR2,11);
		TIMER1->CCMR2 |= (0b11 << 13);
		CLR_BIT(TIMER1->CCMR2,12);
		CLR_BIT(TIMER1->CCER,13);
		SET_BIT(TIMER1->CCER,12);
		break;

	default:
		Local_u8ErrorState = NOK;
		break;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
 * Function Name:		TIMER1_u8SetPWM
 ********************************************************************************/
uint8_t TIMER1_u8SetPWM(uint8_t Copy_u8PwmChannel , uint8_t Copy_u8PwmFrequency , float Copy_u8PwmDutyCycle)
{
	uint8_t Local_u8ErrorState = OK;
	uint16_t Local_u16ReloadValue;
	uint16_t Local_u16CompareValue;
	if(Copy_u8PwmDutyCycle >= 0 && Copy_u8PwmDutyCycle <= 100)
	{
		switch(Copy_u8PwmChannel)
		{
		case TIMER1_u8_PWM_CHANNEL1:
			//Local_u16ReloadValue = ((F_CPU/(TIMER1->PSC+1))/Copy_u8PwmFrequency);
			Local_u16ReloadValue=65535;
			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			TIMER1->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			TIMER1->CCR1 = Local_u16CompareValue; /* Setup Duty Cycle */

			SET_BIT(TIMER1->BDTR,15); /* Enable MOE */
			SET_BIT(TIMER1->CR1,0); /* Enable the timer */
			break;

		case TIMER1_u8_PWM_CHANNEL2:
			Local_u16ReloadValue = ((F_CPU/(TIMER1->PSC+1))/Copy_u8PwmFrequency);
			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			TIMER1->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			TIMER1->CCR2 = Local_u16CompareValue; /* Setup Duty Cycle */

			SET_BIT(TIMER1->BDTR,15); /* Enable MOE */
			SET_BIT(TIMER1->CR1,0); /* Enable the timer */
			break;

		case TIMER1_u8_PWM_CHANNEL3:
			Local_u16ReloadValue = ((F_CPU/(TIMER1->PSC+1))/Copy_u8PwmFrequency);
			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			TIMER1->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			TIMER1->CCR3 = Local_u16CompareValue; /* Setup Duty Cycle */

			SET_BIT(TIMER1->BDTR,15); /* Enable MOE */
			SET_BIT(TIMER1->CR1,0); /* Enable the timer */
			break;

		case TIMER1_u8_PWM_CHANNEL4:
			Local_u16ReloadValue = ((F_CPU/(TIMER1->PSC+1))/Copy_u8PwmFrequency);
			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			TIMER1->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			TIMER1->CCR4 = Local_u16CompareValue; /* Setup Duty Cycle */

			SET_BIT(TIMER1->BDTR,15); /* Enable MOE */
			SET_BIT(TIMER1->CR1,0); /* Enable the timer */
			break;
		default:
			Local_u8ErrorState = NOK;
			break;
		}

	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
 * Function Name:		TIMER1_u8Stop
 ********************************************************************************/
uint8_t TIMER1_u8Stop(void)
{
	uint8_t Local_u8ErrorState = OK;

	TIMER1->CR1 = 0;
	TIMER1->ARR = 0;
	TIMER1->RCR = 0;
	TIMER1->PSC = 0;
	CLR_BIT(TIMER1->DIER,0); /* Disable the interrupt */
	SET_BIT(TIMER1->EGR,0);

	return Local_u8ErrorState;
}


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
void TIM1_UP_IRQHandler(void)
{
	if(TIMER1_Pf != NULL)
	{
		TIMER1_Pf();
	}
	CLR_BIT(TIMER1->SR,0); /* Clear the update flag */
}
