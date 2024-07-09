/*
 * UART_Private.h
 *
 *  Created on: Mar 8, 2024
 *      Author: Amina-PC
 */

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define USART_FREQUENCY            8000000UL
#define USART_STOP_MASK            (0b11<<STOP)

#define USART_DIV_MASK        (0b1111111111111111)

#define USART_PARITY_MASK          (0b11<<PS) //<<9
#define USART_HALFDUBLIX_MASK      (0b1<<HDSEL)
#define USART_DATA_7BIT_MASK      (0b11<<7)
#define USART_DATA_8BIT_MASK      (0b11<<8)
#define USART_DATA_9BIT_MASK      (0b11<<9)

#define USART_PERIPHERALS_NUMBER   3
#define TX_REG_EMPTY               1U
#define TX_COMPLETED               1U
#define RX_REG_READY               1U

USART_Reg_Def_t * usart_num[USART_PERIPHERALS_NUMBER]={USART_USART1,USART_USART2,USART_USART3};





#endif /* USART_PRIVATE_H_ */
