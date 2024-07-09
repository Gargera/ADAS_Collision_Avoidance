#include <stdint.h>
#include "error_typ.h"
#include "Bit_Math.h"
#include "Stm32f103xx.h"

#include "GPT_interface.h"
#include "GPT_private.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static fptr_t Global_pfArr[3] = {NULL,NULL,NULL};

static GPT_RegDef_t * GPT_Astr[3] = {TIMER2,TIMER3,TIMER4};


channel_Types GLOBAL_Channel_Selected;
/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:		GPT_u8Init
 ********************************************************************************/
uint8_t GPT_u8Init(uint8_t Copy_u8TimerNumber , uint8_t Copy_u8Direction , uint16_t Copy_u16Prescaler)
{
	uint8_t Local_u8ErrorState = OK;

	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		GPT_Astr[Copy_u8TimerNumber]->CR1 = 0;
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,7); /* Auto reload pre-load enable */
		GPT_Astr[Copy_u8TimerNumber]->CR1 |= ((Copy_u8Direction & 0b1) << 4); /* Set the direction up or down */
		GPT_Astr[Copy_u8TimerNumber]->PSC = ( Copy_u16Prescaler - 1 ) ;
		GPT_Astr[Copy_u8TimerNumber]->ARR = 0xFFFF;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
 * Function Name:		GPT_u8SetBusyWait
 ********************************************************************************/
uint8_t GPT_u8SetBusyWait(uint8_t Copy_u8TimerNumber , uint16_t Copy_u32NumOfTicks)
{
	uint8_t Local_u8ErrorState = OK;

	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->DIER,0); /* Disable the interrupt */
		GPT_Astr[Copy_u8TimerNumber]->ARR = (Copy_u32NumOfTicks & 0xFFFF);
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable The timer */
		while(GET_BIT(GPT_Astr[Copy_u8TimerNumber]->SR,0) == 0); /* Wait until update occurs */
		CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->SR,0); /* Clear the update flag */
		CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Disable The timer */
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
 * Function Name:		GPT_u8SetIntervalPeriodic
 ********************************************************************************/
uint8_t GPT_u8SetIntervalPeriodic(uint8_t Copy_u8TimerNumber , uint16_t Copy_u32NumOfTicks , void(*Copy_pf)(void))
{
	uint8_t Local_u8ErrorState = OK;

	if(Copy_pf != NULL && Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		Global_pfArr[Copy_u8TimerNumber] = Copy_pf;
		GPT_Astr[Copy_u8TimerNumber]->ARR = (Copy_u32NumOfTicks & 0xFFFF);
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->DIER,0); /* Enable the interrupt */
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable The timer */
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
 * Function Name:		GPT_u8InitPwmChannel
 ********************************************************************************/
uint8_t GPT_u8InitPwmChannel(uint8_t Copy_u8TimerNumber , uint8_t Copy_u8PwmChannel)
{
	uint8_t Local_u8ErrorState = OK;

	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		switch(Copy_u8PwmChannel)
		{
		case GPT_u8_PWM_CHANNEL1:
			GPT_Astr[Copy_u8TimerNumber]->CCMR1 &= ~(0b11); /* Channel is output compare */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR1,3); /* Output compare preload enable */
			GPT_Astr[Copy_u8TimerNumber]->CCMR1 |= (0b11 << 5); /* PWM mode 1 */
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR1,4); /* PWM mode 1 */
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,1); /* high output polarity */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,0); /* Output enable */
			break;

		case GPT_u8_PWM_CHANNEL2:
			GPT_Astr[Copy_u8TimerNumber]->CCMR1 &= ~(0b11<<8);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR1,11);
			GPT_Astr[Copy_u8TimerNumber]->CCMR1 |= (0b11 << 13);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR1,12);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,5);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,4);
			break;

		case GPT_u8_PWM_CHANNEL3:
			GPT_Astr[Copy_u8TimerNumber]->CCMR2 &= ~(0b11);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR2,3);
			GPT_Astr[Copy_u8TimerNumber]->CCMR2 |= (0b11 << 5);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR2,4);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,9);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,8);
			break;

		case GPT_u8_PWM_CHANNEL4:
			GPT_Astr[Copy_u8TimerNumber]->CCMR2 &= ~(0b11<<8);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR2,11);
			GPT_Astr[Copy_u8TimerNumber]->CCMR2 |= (0b11 << 13);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR2,12);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,13);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,12);
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
 * Function Name:		GPT_u8SetPWM
 ********************************************************************************/
uint8_t GPT_u8SetPWM(uint8_t Copy_u8TimerNumber , uint8_t Copy_u8PwmChannel , uint8_t Copy_u8PwmFrequency , float Copy_u8PwmDutyCycle)
{
	uint8_t Local_u8ErrorState = OK;
	uint16_t Local_u16ReloadValue;
	uint16_t Local_u16CompareValue;

	if(Copy_u8PwmDutyCycle >= 0 && Copy_u8PwmDutyCycle <= 100 && Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		switch(Copy_u8PwmChannel)
		{
		case GPT_u8_PWM_CHANNEL1:
			//Local_u16ReloadValue = ((F_CPU/(GPT_Astr[Copy_u8TimerNumber]->PSC+1))/Copy_u8PwmFrequency);
			Local_u16ReloadValue=65535;

			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			GPT_Astr[Copy_u8TimerNumber]->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			GPT_Astr[Copy_u8TimerNumber]->CCR1 = Local_u16CompareValue; /* Setup Duty Cycle */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable the timer */
			break;

		case GPT_u8_PWM_CHANNEL2:
			//Local_u16ReloadValue = ((F_CPU/(GPT_Astr[Copy_u8TimerNumber]->PSC+1))/Copy_u8PwmFrequency);
			Local_u16ReloadValue=65535;

			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;

			GPT_Astr[Copy_u8TimerNumber]->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			GPT_Astr[Copy_u8TimerNumber]->CCR2 = Local_u16CompareValue; /* Setup Duty Cycle */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable the timer */
			break;

		case GPT_u8_PWM_CHANNEL3:
			//	Local_u16ReloadValue = ((F_CPU/(GPT_Astr[Copy_u8TimerNumber]->PSC+1))/Copy_u8PwmFrequency);
			Local_u16ReloadValue=65535;
			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			GPT_Astr[Copy_u8TimerNumber]->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			GPT_Astr[Copy_u8TimerNumber]->CCR3 = Local_u16CompareValue; /* Setup Duty Cycle */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable the timer */
			break;

		case GPT_u8_PWM_CHANNEL4:
			//	Local_u16ReloadValue = ((F_CPU/(GPT_Astr[Copy_u8TimerNumber]->PSC+1))/Copy_u8PwmFrequency);
			Local_u16ReloadValue=65535;
			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			GPT_Astr[Copy_u8TimerNumber]->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			GPT_Astr[Copy_u8TimerNumber]->CCR4 = Local_u16CompareValue; /* Setup Duty Cycle */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable the timer */
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
 * Function Name:		GPT_u8Stop
 ********************************************************************************/
uint8_t GPT_u8Stop(uint8_t Copy_u8TimerNumber)
{
	uint8_t Local_u8ErrorState = OK;

	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		GPT_Astr[Copy_u8TimerNumber]->CR1 = 0;
		GPT_Astr[Copy_u8TimerNumber]->ARR = 0;
		GPT_Astr[Copy_u8TimerNumber]->PSC = 0;
		CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->DIER,0); /* Disable the interrupt */
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->EGR,0);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}


void TIMER_VoidICUInit(ICU_Types *ICU_Values)
{

	if(ICU_Values->Timer_NUM >= 2 && ICU_Values->Timer_NUM <= 4)
	{
		ICU_Values->Timer_NUM -= 2;

		if((ICU_Values->channel_selected)==CC1)
		{

			/*select the channel and storage place*/
			GPT_Astr[ICU_Values->Timer_NUM]->CCMR1 |=((ICU_Values->CC_Types)<<CC1S);

			/*select edge you want to detect rising or falling*/
			GPT_Astr[ICU_Values->Timer_NUM]->CCER |=((ICU_Values->Edge_polarity)<<CC1P);

			/*Capture enabled*/
			SET_BIT(GPT_Astr[ICU_Values->Timer_NUM]->CCER,CC1E);

		}else if((ICU_Values->channel_selected)==CC2)
		{
			GPT_Astr[ICU_Values->Timer_NUM]->CCMR1 |= ((ICU_Values->CC_Types)<<CC2S);

			SET_BIT(GPT_Astr[ICU_Values->Timer_NUM]->CCER,CC2E);

			GPT_Astr[ICU_Values->Timer_NUM]->CCER |= ((ICU_Values->Edge_polarity)<<CC2P);
		}else if(ICU_Values->channel_selected==CC3)
		{
			GPT_Astr[ICU_Values->Timer_NUM]->CCMR2 |=((ICU_Values->CC_Types)<<CC3S);
			GPT_Astr[ICU_Values->Timer_NUM]->CCER |=((ICU_Values->Edge_polarity)<<CC3P);
			SET_BIT(GPT_Astr[ICU_Values->Timer_NUM]->CCER,CC3E);

		}else if(ICU_Values->channel_selected==CC3)
		{
			GPT_Astr[ICU_Values->Timer_NUM]->CCMR2 |= ((ICU_Values->CC_Types)<<CC4S);
			GPT_Astr[ICU_Values->Timer_NUM]->CCER |= ((ICU_Values->Edge_polarity)<<CC4P);
			SET_BIT(GPT_Astr[ICU_Values->Timer_NUM]->CCER,CC4E);
		}


		/*assign channel selected to global variable for interrupt function*/
		GLOBAL_Channel_Selected=(ICU_Values->channel_selected);
	}
}
void Timer_start(uint8_t Copy_u8TimerNumber)
{
	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1 ,CEN);
	}
}

void Timer_stop(uint8_t Copy_u8TimerNumber)
{
	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1 ,CEN);
	}
}
void Timer_VoidEmptyCounterRegister(uint8_t Copy_u8TimerNumber)
{
	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		GPT_Astr[Copy_u8TimerNumber]->CNT = 0;
	}
}

void Timer_VoidIcuTriggerEdge(uint8_t Copy_u8TimerNumber,Edge_Types Edge_polarity,channel_Types CC)
{
	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		if(CC==CC1)
		{
			GPT_Astr[Copy_u8TimerNumber]->CCER &= ~(CC1P_MSK);
			GPT_Astr[Copy_u8TimerNumber]->CCER |=(Edge_polarity <<CC1P );
		}else if(CC==CC2)
		{
			GPT_Astr[Copy_u8TimerNumber]->CCER &= ~(CC2P_MSK);
			GPT_Astr[Copy_u8TimerNumber]->CCER |=(Edge_polarity<< CC2P);
		}else if(CC==CC3)
		{
			GPT_Astr[Copy_u8TimerNumber]->CCER &= ~(CC3P_MSK);
			GPT_Astr[Copy_u8TimerNumber]->CCER |=(Edge_polarity<< CC3P);
		}else if(CC==CC4)
		{
			GPT_Astr[Copy_u8TimerNumber]->CCER &= ~(CC4P_MSK);
			GPT_Astr[Copy_u8TimerNumber]->CCER |=(Edge_polarity<< CC4P);
		}
	}
}
uint16_t TIMER_U16IcuGetCaptureValue(uint8_t Copy_u8TimerNumber,channel_Types CC)
{
	uint16_t Capture_Value=0;
	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		switch(CC)
		{
		case CC1: Capture_Value=GPT_Astr[Copy_u8TimerNumber]->CCR1;break;
		case CC2: Capture_Value=GPT_Astr[Copy_u8TimerNumber]->CCR2;break;
		case CC3: Capture_Value=GPT_Astr[Copy_u8TimerNumber]->CCR3;break;
		case CC4: Capture_Value=GPT_Astr[Copy_u8TimerNumber]->CCR4;break;
		}
	}
	return Capture_Value;
}



uint8_t Timer_U8IcuGetCaptureFlag(uint8_t Copy_u8TimerNumber,channel_Types CC)
{
	uint16_t Capture_Flag=0;
	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		switch(CC)
		{
		case CC1: Capture_Flag=GET_BIT((GPT_Astr[Copy_u8TimerNumber]->SR),CC1);break;
		case CC2: Capture_Flag=GET_BIT((GPT_Astr[Copy_u8TimerNumber]->SR),CC2);break;
		case CC3: Capture_Flag=GET_BIT((GPT_Astr[Copy_u8TimerNumber]->SR),CC3);break;
		case CC4: Capture_Flag=GET_BIT((GPT_Astr[Copy_u8TimerNumber]->SR),CC4);break;
		}
	}
	return Capture_Flag;

}


void TIMER_VoidIcuInterruptEnable(uint8_t Copy_u8TimerNumber)
{
	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;

		GPT_Astr[Copy_u8TimerNumber]->DIER |= (1<<GLOBAL_Channel_Selected);
	}
}


void Timer_VoidClearFlag(uint8_t Copy_u8TimerNumber)
{
	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;

		CLR_BIT((GPT_Astr[Copy_u8TimerNumber]->SR),0);
	}
}

void TIMER_VoidIcuInterruptDisable(uint8_t Copy_u8TimerNumber)
{
	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;

		GPT_Astr[Copy_u8TimerNumber]->DIER &= (~(1<<GLOBAL_Channel_Selected));
	}

}


void Timer_VoidTimeEventGenerationSet(uint8_t Copy_u8TimerNumber)
{
	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;

		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->EGR,0);
	}
}
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
void TIM2_IRQHandler(void)
{
	if(Global_pfArr[0] != NULL)
	{
		Global_pfArr[0]();
	}
	CLR_BIT(TIMER2->SR,0); /* Clear the update flag */
}

void TIM3_IRQHandler(void)
{
	if(Global_pfArr[1] != NULL)
	{
		Global_pfArr[1]();
	}
	CLR_BIT(TIMER3->SR,0); /* Clear the update flag */
}

void TIM4_IRQHandler(void)
{
	if(Global_pfArr[2] != NULL)
	{
		Global_pfArr[2]();
	}
	CLR_BIT(TIMER4->SR,0); /* Clear the update flag */
}
