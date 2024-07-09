/*
 * UART_Project.c
 *
 *  Created on: Mar 8, 2024
 *      Author: Amina
 */
#include <stdint.h>
#include "error_typ.h"
#include "Stm32F103xx.h"
#include "Bit_Math.h"

#include "NVIC_Interface.h"
#include "USART_Interface.h"
#include "USART_Private.h"


/*pointer to function for USART1 for call back*/
void (*USART1_CallBack)(void);

/*pointer to function for USART2 for call back*/
void (*USART2_CallBack)(void);

/*pointer to function for USART3 for call back*/
void (*USART3_CallBack)(void);




void USART_Init(const USART_ConfigReg_t *USART_ConfigReg)
{
	USART_Reg_Def_t * USARTX=usart_num[USART_ConfigReg->number];

	switch (USART_ConfigReg->mode)
	{
	case Enable_RX: SET_BIT(USARTX->CR1,RE); break;
	case Enable_TX: SET_BIT(USARTX->CR1,TE); break;
	case Enable_TX_RX: SET_BIT(USARTX->CR1,RE); SET_BIT(USARTX->CR1,TE); break;
	default: break;
	}

	USARTX->CR1|=(USART_ConfigReg->word)<<M;

	USARTX->CR2&=~USART_STOP_MASK;
	USARTX->CR2|=(USART_ConfigReg->stop_bit)<<STOP;

	if(USART_ConfigReg->parity==0)
	{
		CLR_BIT(USARTX->CR1,PCE);
	}
	else
	{
		USARTX->CR1&=~USART_PARITY_MASK;
		USARTX->CR1|=(USART_ConfigReg->parity)<<PS;
	}

	USARTX->CR3&=~USART_HALFDUBLIX_MASK;
	USARTX->CR3|=(USART_ConfigReg->hd)<<HDSEL;
	SET_BIT(USARTX->CR1,RE);

	USARTX->CR2|=(USART_ConfigReg->clock)<<CLKEN;


}




void USART_BaudRate( const USART_ConfigReg_t *USART_ConfigReg  )
{
	USART_Reg_Def_t * USARTX=usart_num[USART_ConfigReg->number];

	uint8_t mantissa=52;
	uint8_t fraction=1;
	USARTX->BRR|=mantissa<<DIV_Mantissa;

	USARTX->BRR|=fraction;


}

void USART_Enable(USART_Number_t number, USART_Enable_t enable)
{
	USART_Reg_Def_t * USARTX=usart_num[number];
	switch (enable)
	{
	case Disable_USART: CLR_BIT(USARTX->CR1,UE); break;
	case Enable_USART: SET_BIT(USARTX->CR1,UE); break;
	default: break;
	}
}

uint8_t USART_u8ReadFlag(USART_Number_t number,USART_SR_t flag)
{
	USART_Reg_Def_t * USARTX=usart_num[number];
	return (uint8_t)READ_BIT(USARTX->SR, flag);

}

void USART_CTSE(USART_Number_t number)
{
	USART_Reg_Def_t * USARTX=usart_num[number];
	CLR_BIT(USARTX->CR3,CTSE);
}

void USART_RTSE(USART_Number_t number)
{
	USART_Reg_Def_t * USARTX=usart_num[number];
	CLR_BIT(USARTX->CR3,RTSE);
}

void USART_TX_Data(USART_Number_t number, uint8_t data)
{
	USART_Reg_Def_t * USARTX=usart_num[number];
	while(READ_BIT(USARTX->SR,TXE)!=TX_REG_EMPTY);
	USARTX->DR=data ;

	while(READ_BIT(USARTX->SR,TC)!=TX_COMPLETED);

}

uint8_t USART_RX_Data(USART_Number_t number)
{
	USART_Reg_Def_t * USARTX=usart_num[number];
	uint32_t LOC_TimeOut = 0 ;
	uint8_t data =0;
	while((READ_BIT(USARTX->SR,RXNE)!=RX_REG_READY )&& ( LOC_TimeOut < 160000UL ))
	{
		LOC_TimeOut++;
	}
	data =USARTX->DR;

	return data;
}

void USART_RxIT_Enable(USART_Number_t number, USART_Enable_t enable)
{
	USART_Reg_Def_t * USARTX=usart_num[number];
	switch (enable)
	{
	case Disable_USART: CLR_BIT(USARTX->CR1,RXNEIE); break;
	case Enable_USART: SET_BIT(USARTX->CR1,RXNEIE); break;
	default: break;
	}

}
/*
void USART_Interrupt_Enable(USART_Number_t number,NVIC_IREQn_t IREQ_NUM, USART_Enable_t enable)
{

	switch (enable)
	{
	case Disable_USART:
		NVIC_DisableIRQ(IREQ_NUM);
		NVIC_ClearPendingFlag(IREQ_NUM);

		USART_RxIT_Enable(number , Disable_USART) ;

		break;
	case Enable_USART:

		break;
	default: break;
	}
}
 */

void USART_voidClearFlags(USART_Number_t number)
{
	USART_Reg_Def_t * USARTX=usart_num[number];
	USARTX->SR = 0;
}

uint8_t USART_u8ReadDataRegister(USART_Number_t number)
{
	USART_Reg_Def_t * USARTX=usart_num[number];
	return USARTX -> DR;
}



void USART1_voidSetCallBack( void (*ptr) (void) )
{
	USART1_CallBack =ptr;
}

void USART2_voidSetCallBack( void (*ptr) (void) )
{
	USART2_CallBack = ptr;
}

void USART3_voidSetCallBack( void (*ptr) (void) )
{
	USART3_CallBack = ptr;
}


/*IRQ of USART1*/
void USART1_IRQHandler(void)
{
	usart_num[USART1]->SR = 0;
	if(USART1_CallBack!=NULL)
	{
		USART1_CallBack();
	}
}

/*IRQ of USART2*/
void USART2_IRQHandler(void)
{
	usart_num[USART2]->SR = 0;
	if(USART2_CallBack!=NULL)
	{
		USART2_CallBack();
	}
}

/*IRQ of USART3*/
void USART3_IRQHandler(void)
{

	usart_num[USART3]->SR = 0;
	if(USART3_CallBack!=NULL)
	{
		USART3_CallBack();
	}

}
