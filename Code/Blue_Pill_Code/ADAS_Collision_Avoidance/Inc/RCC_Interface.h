/*
 * RCC_Interface.h
 *
 *  Created on: Jun 15, 2024
 *      Author: Gargera
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/*RCC Bus Type*/
typedef enum
{
	AHB,
	APB1,
	APB2
}RCC_Bus_t;

/*@AHBPeriperals_t*/
typedef enum
{
	DMA1,
	DMA2,
	SRAM,
	FLITF=4,
	CRC=6,
	FSMC=8,
	SDIO=10

}AHBPeriperals_t;

/*@APB1Peripherals_t*/
typedef enum
{
	TIM2EN,
	TIM3EN,
	TIM4EN,
	TIM5EN,
	TIM6EN,
	TIM7EN,
	TIM12EN,
	TIM13EN,
	TIM14EN,
	WWDGEN=11,
	SPI2EN=14,
	SPI3EN,
	USART2EN=17,
	USART3EN,
	UART4EN,
	UART5EN,
	I2C1EN,
	I2C2EN,
	USBEN,
	CANEN=25,
	BKPEN=27,
	PWREN,
	DACEN

}APB1Peripherals_t;

/*@APB2Peripherals_t*/
typedef enum
{
	AFIOEN,
	GPIOAEN=2,
	GPIOBEN,
	GPIOCEN,
	GPIODEN,
	GPIOEEN,
	GPIOFEN,
	GPIOGEN,
	ADC1EN,
	ADC2EN,
	TIM1EN,
	SPI1EN,
	TIM8EN,
	USART1EN,
	ADC3EN,
	TIM9EN=19,
	TIM10EN,
	TIM11EN

}APB2Peripherals_t;

/*
 * @fn:		RCC_EnablePeripheral
 * @brief:	Enable clock for peripheral
 * @param:	Peripheral		(uint8_t)
 * @retval:	void
 * */
void RCC_EnablePeripheral(RCC_Bus_t bus , uint8_t peripheral);

/*
 * @fn:		RCC_DisablePeripheral
 * @brief:	Disable clock for peripheral
 * @param:	Peripheral		(uint8_t)
 * @retval:	void
 * */
void RCC_DisablePeripheral(RCC_Bus_t bus , uint8_t peripheral);

#endif /* RCC_INTERFACE_H_ */
