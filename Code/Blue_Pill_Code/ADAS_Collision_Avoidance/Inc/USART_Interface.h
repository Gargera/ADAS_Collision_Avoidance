/*
 * UART_Interface.h
 *
 *  Created on: Mar 8, 2024
 *      Author: Amina
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


//#include "USART_Private.h"
typedef enum{
	USART1=0,
	USART2,
	USART3,

}USART_Number_t;

typedef enum{
	WORD_LENGTH_8=0,
	WORD_LENGTH_9
}USART_WordLength_t;


typedef enum{
	STOP_BITS_1=0,
	STOP_BITS_05, //0.5
	STOP_BITS_2,
	STOP_BITS_15, //1.5

}USART_StopBit_t;

typedef enum{
	noparity=0,
	enableParity_even=0b10,
	enableParity_odd=0b11
}USART_Parity_t;

typedef enum{
	Enable_RX=0b01,
	Enable_TX=0b10,
	Enable_TX_RX=0b11
}USART_Mode_t;

typedef enum{
	Disable_HD=0,
	Enable_HD
}USART_HalfDublix_t;

typedef enum{
	Disable_USART=0,
	Enable_USART
}USART_Enable_t;

typedef enum{

	CLOCK_Disable=0,			/*Asynchronous*/
	CLOCK_Enable				/*Synchronous*/

}USART_Clock_t;


typedef enum{
	PE=0,
	FE,
	NF,
	ORE,
	IDLE,
	RXNE,
	TC,
	TXE,
	LBD,
	CTS
}USART_SR_t;

typedef enum{
	DR=0  //[0:8] 9bits
}USART_DR_t;

typedef enum{
	DIV_Fraction=0,  //[0:3] 4bits
	DIV_Mantissa=4   //[4:15] 12bits

}USART_BRR_t;

typedef enum{
	SBK=0,
	RWU,
	RE,
	TE,
	IDLEIE,
	RXNEIE,
	TCIE,
	TXEIE,
	PEIE,
	PS,
	PCE,
	WAKE,
	M,
	UE,
	RESERVED,

}USART_CR1_t;

typedef enum{
	ADD=0, //[0:3] 4bits
	RESERVED1,
	LBDL=5,
	LBDIE,
	RESERVED2,
	LBCL=8,
	CPHA,
	CPOL,
	CLKEN,
	STOP,  //[12:13] 2bits
	LINEN=14
}USART_CR2_t;

typedef enum{
	EIE,
	IREN,
	IRLP,
	HDSEL,
	NACK,
	SCEN,
	DMAR,
	DMAT,
	RTSE,
	CTSE,
	CTSIE,

}USART_CR3_t;

typedef enum{
	PSC=0, //[0:7] 8bits
	GT=8  //[8:15] 8bits
}USART_GTPR_t;


typedef struct {
	USART_Number_t number;
	USART_Mode_t mode;
	USART_StopBit_t stop_bit;
	USART_WordLength_t word;
	USART_Parity_t parity ;
	uint32_t baudRate;
	USART_HalfDublix_t hd;
	USART_Clock_t clock;

}USART_ConfigReg_t;









void USART_Init(const USART_ConfigReg_t *USART_ConfigReg);
void USART_BaudRate( const USART_ConfigReg_t *USART_ConfigReg);
void USART_Enable(USART_Number_t number, USART_Enable_t enable);
uint8_t USART_u8ReadFlag(USART_Number_t number,USART_SR_t flag);
void USART_CTSE(USART_Number_t number);
void USART_RTSE(USART_Number_t number);
void USART_TX_Data(USART_Number_t number, uint8_t data);
uint8_t USART_RX_Data(USART_Number_t number);

//void USART_Interrupt_Enable(USART_Number_t number,NVIC_IREQn_t IREQ_NUM, USART_Enable_t enable);


/*
	Function Name        : USART_RxIT_Enable
	Function Returns     : void
	Function Arguments   : USART_Number_t *USARTx, Enable_t enable
	Function Description : choose to enable RX interrupt or disable
 */
void USART_RxIT_Enable(USART_Number_t number, USART_Enable_t enable);

/*
	Function Name        : USART_vClearFlags
	Function Returns     : void
	Function Arguments   : USART_Number_t *USARTx
	Function Description : clear all flags after RX interrupted
 */
void USART_vClearFlags(USART_Number_t number);

/*
	Function Name        : USART_u8ReadDataRegister
	Function Returns     : u8
	Function Arguments   : USART_Number_t *USARTx
	Function Description : receive one byte Asynchronous
 */
uint8_t USART_u8ReadDataRegister(USART_Number_t number);

/*
	Function Name        : USART1_vSetCallBack
	Function Returns     : void
	Function Arguments   : void (*ptr) (void)
	Function Description : set call back function for USART1
 */
void USART1_voidSetCallBack( void (*ptr) (void) ) ;

/*
	Function Name        : USART2_vSetCallBack
	Function Returns     : void
	Function Arguments   : void (*ptr) (void)
	Function Description : set call back function for USART2
 */
void USART2_voidSetCallBack( void (*ptr) (void) ) ;

/*
	Function Name        : USART3_vSetCallBack
	Function Returns     : void
	Function Arguments   : void (*ptr) (void)
	Function Description : set call back function for USART3
 */
void USART3_voidSetCallBack( void (*ptr) (void) ) ;


#endif /* USART_INTERFACE_H_ */
