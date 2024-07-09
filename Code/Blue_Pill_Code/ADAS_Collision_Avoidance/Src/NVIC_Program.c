#include <stdint.h>
#include "Stm32F103xx.h"
#include "Bit_Math.h"
#include "error_typ.h"

#include "NVIC_interface.h"



uint8_t NVIC_EnableIRQ(NVIC_IREQn_t IREQ_NUM)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;

	if(IREQ_NUM <= NVIC_IRQ_FMPI2C1_Error)
	{

		/*calculate Register number*/
		Local_u8RegNum = (IREQ_NUM/32);

		/*calculate Bit number*/
		Local_u8BitNum = (IREQ_NUM%32);

		/*Enable interrupt*/
		NVIC -> ISER[Local_u8RegNum] = (1 << Local_u8BitNum);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8_t NVIC_DisableIRQ(NVIC_IREQn_t IREQ_NUM)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;

	if(IREQ_NUM <= NVIC_IRQ_FMPI2C1_Error)
	{
		/*calculate Register number*/
		Local_u8RegNum = (IREQ_NUM/32);

		/*calculate Bit number*/
		Local_u8BitNum = (IREQ_NUM%32);

		/*Disable interrupt*/
		NVIC -> ICER[Local_u8RegNum] = (1 << Local_u8BitNum);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8_t NVIC_SetPendingFlag(NVIC_IREQn_t IREQ_NUM)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;

	if(IREQ_NUM <= NVIC_IRQ_FMPI2C1_Error)
	{
		/*calculate Register number*/
		Local_u8RegNum = (IREQ_NUM/32);

		/*calculate Bit number*/
		Local_u8BitNum = (IREQ_NUM%32);

		/*changes interrupt state to pending*/
		NVIC -> ISPR[Local_u8RegNum] = (1 << Local_u8BitNum);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8_t NVIC_ClearPendingFlag(NVIC_IREQn_t IREQ_NUM)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;

	if(IREQ_NUM <= NVIC_IRQ_FMPI2C1_Error)
	{
		/*calculate Register number*/
		Local_u8RegNum = (IREQ_NUM/32);

		/*calculate Bit number*/
		Local_u8BitNum = (IREQ_NUM%32);

		/*removes pending state an interrupt*/
		NVIC -> ICPR[Local_u8RegNum] = (1 << Local_u8BitNum);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8_t NVIC_GetPendingFlag(NVIC_IREQn_t IREQ_NUM)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;
	uint8_t Local_u8ActiveFlag;

	if(IREQ_NUM <= NVIC_IRQ_FMPI2C1_Error)
	{
		/*calculate Register number*/
		Local_u8RegNum = (IREQ_NUM/32);

		/*calculate Bit number*/
		Local_u8BitNum = (IREQ_NUM%32);

		/*Get pending flag value*/
		Local_u8ActiveFlag = 1 & ((NVIC -> ISPR[Local_u8RegNum]) >> Local_u8BitNum);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8_t NVIC_SetGetActiveFlag(NVIC_IREQn_t IREQ_NUM)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;
	uint8_t Local_u8ActiveFlag;

	if(IREQ_NUM <= NVIC_IRQ_FMPI2C1_Error)
	{
		/*calculate Register number*/
		Local_u8RegNum = (IREQ_NUM/32);

		/*calculate Bit number*/
		Local_u8BitNum = (IREQ_NUM%32);

		/*Get pending flag value*/
		Local_u8ActiveFlag = 1 & ((NVIC -> IABR[Local_u8RegNum]) >> Local_u8BitNum);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8_t	NVIC_SetIRQPriority(NVIC_IREQn_t IREQ_NUM, uint8_t priority)
{
	uint8_t Local_u8ErrorState = OK;

	if(IREQ_NUM <= NVIC_IRQ_FMPI2C1_Error)
	{
		NVIC -> IPR[IREQ_NUM] &= ~(0xF0);
		NVIC -> IPR[IREQ_NUM] = (priority << 4);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

