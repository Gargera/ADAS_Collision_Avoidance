/*
 * Project_Init.c
 *
 *  Created on: Jun 18, 2024
 *      Author: Gargera
 */

#include <stdint.h>

#include "RCC_Interface.h"

#include "GPIO_INTERFACE.h"

#include "SYSTICK_interface.h"

#include "USART_Interface.h"

#include "NVIC_Interface.h"

#include "Timer_interface.h"

#include "MotorDriver_Interface.h"

#include "Servo_Core.h"

#include "Project_Init.h"

#include "Project_Defines.h"

#include "Ultrasonic_Interface.h"

#include "Buzzer_Interface.h"


extern uint8_t G_u8DataFromBluetooth;
extern uint8_t G_u8DataFromRaspberrypi;

extern const PinConfig_t uart3_tx_PinConfig;
extern const PinConfig_t uart3_rx_PinConfig;
extern const USART_ConfigReg_t USART3_ConfigReg;

extern const PinConfig_t uart1_tx_PinConfig;
extern const PinConfig_t uart1_rx_PinConfig;
extern const USART_ConfigReg_t USART1_ConfigReg;


extern const PinConfig_t SERVO1_PinConfig;

void BluetoothData (void)
{
	//Received data from Bluetooth Module by USART
	G_u8DataFromBluetooth = USART_u8ReadDataRegister(USART3);


}
void RasberrypiData (void)
{
	//Received data from rasberry Module by USART
	G_u8DataFromRaspberrypi = USART_u8ReadDataRegister(USART1);

}

void init()
{


	RCC_EnablePeripheral(APB2 , GPIOAEN);
	RCC_EnablePeripheral(APB2 , GPIOBEN);
	RCC_EnablePeripheral(APB2 , GPIOCEN);
	RCC_EnablePeripheral(APB2 , GPIODEN);
	RCC_EnablePeripheral(APB2 , GPIOEEN);
	RCC_EnablePeripheral(APB2 , GPIOFEN);
	RCC_EnablePeripheral(APB2 , GPIOGEN);
	RCC_EnablePeripheral(APB2,TIM1EN);
	RCC_EnablePeripheral(APB1,TIM2EN);
	RCC_EnablePeripheral(APB1,TIM3EN);
	RCC_EnablePeripheral(APB1,TIM4EN);
	RCC_EnablePeripheral(APB1,USART3EN);
	RCC_EnablePeripheral(APB2,USART1EN);

	Motors_Init();

	servo_init();

	Buzzer_vInit();

	Ultrasonic_Init();

	GPIO_u8PinInit(&uart3_tx_PinConfig);
	GPIO_u8PinInit(&uart3_rx_PinConfig);
	GPIO_u8PinInit(&uart1_tx_PinConfig);
	GPIO_u8PinInit(&uart1_rx_PinConfig);


	/****uart_initializations with interrupt****/
	USART_Init(&USART3_ConfigReg);
	USART_BaudRate(&USART3_ConfigReg);
	NVIC_SetIRQPriority(NVIC_IRQ_USART3 , 0);
	NVIC_EnableIRQ(NVIC_IRQ_USART3);
	NVIC_SetPendingFlag(NVIC_IRQ_USART3);
	USART_RxIT_Enable(USART3 , Enable_USART) ;
	USART_Enable(USART3,Enable_USART);
	SYSTICK_DelayMs(300);
	USART3_voidSetCallBack(BluetoothData);


	USART_Init(&USART1_ConfigReg);
	USART_BaudRate(&USART1_ConfigReg);
	NVIC_SetIRQPriority(NVIC_IRQ_USART1 , 0);
	NVIC_EnableIRQ(NVIC_IRQ_USART1);
	NVIC_SetPendingFlag(NVIC_IRQ_USART1);
	USART_RxIT_Enable(USART1 , Enable_USART) ;
	USART_Enable(USART1,Enable_USART);
	SYSTICK_DelayMs(300);
	USART1_voidSetCallBack(RasberrypiData);
}
