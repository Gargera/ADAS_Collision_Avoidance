#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

typedef enum
{
	NVIC_IRQ_WWDG = 0,
	NVIC_IRQ_PVD,
	NVIC_IRQ_TAMPER,
	NVIC_IRQ_RTC,
	NVIC_IRQ_FLASH,
	NVIC_IRQ_RCC_,
	NVIC_IRQ_EXTI0,
	NVIC_IRQ_EXTI1,
	NVIC_IRQ_EXTI2,
	NVIC_IRQ_EXTI3,
	NVIC_IRQ_EXTI4,
	NVIC_IRQ_DMA1_Channel1,
	NVIC_IRQ_DMA1_Channel2,
	NVIC_IRQ_DMA1_Channel3,
	NVIC_IRQ_DMA1_Channel4,
	NVIC_IRQ_DMA1_Channel5,
	NVIC_IRQ_DMA1_Channel6,
	NVIC_IRQ_DMA1_Channel7,
	NVIC_IRQ_ADC1_2,
	NVIC_IRQ_CAN1_TX,
	NVIC_IRQ_CAN1_RX0,
	NVIC_IRQ_CAN1_RX1,
	NVIC_IRQ_CAN1_SCE,
	NVIC_IRQ_EXTI9_5,
	NVIC_IRQ_TIM1_BRK,
	NVIC_IRQ_TIM1_UP,
	NVIC_IRQ_TIM1_TRG_COM,
	NVIC_IRQ_TIM1_CC,
	NVIC_IRQ_TIM2,
	NVIC_IRQ_TIM3,
	NVIC_IRQ_TIM4,
	NVIC_IRQ_I2C1_EV,
	NVIC_IRQ_I2C1_ER,
	NVIC_IRQ_I2C2_EV,
	NVIC_IRQ_I2C2_ER,
	NVIC_IRQ_SPI1,
	NVIC_IRQ_SPI2,
	NVIC_IRQ_USART1,
	NVIC_IRQ_USART2,
	NVIC_IRQ_USART3,
	NVIC_IRQ_EXTI15_10,
	NVIC_IRQ_RTC_Alarm,
	NVIC_IRQ_OTG_FS_WKUP,
	NVIC_IRQ_TIM5=50,
	NVIC_IRQ_SPI3,
	NVIC_IRQ_UART4,
	NVIC_IRQ_UART5,
	NVIC_IRQ_TIM6,
	NVIC_IRQ_TIM7,
	NVIC_IRQ_DMA2_Channel1,
	NVIC_IRQ_DMA2_Channel2,
	NVIC_IRQ_DMA2_Channel3,
	NVIC_IRQ_DMA2_Channel4,
	NVIC_IRQ_DMA2_Channel5,
	NVIC_IRQ_ETH,
	NVIC_IRQ_ETH_WKUP,
	NVIC_IRQ_CAN2_TX,
	NVIC_IRQ_CAN2_RX0,
	NVIC_IRQ_CAN2_RX1,
	NVIC_IRQ_CAN2_SCE,
	NVIC_IRQ_OTG_FS,
	NVIC_IRQ_FMPI2C1_Error
}NVIC_IREQn_t;

/*
@fn NVIC_EnableIRQ
@brief enable peripheral interrupt using NVIC
@param[in] IREQ_NUM
@retval uint8_t
 */
uint8_t NVIC_EnableIRQ(NVIC_IREQn_t IREQ_NUM);

/*
@fn NVIC_DisableIRQ
@brief disable peripheral interrupt using NVIC
@param[in] IREQ_NUM
@retval uint8_t
 */
uint8_t NVIC_DisableIRQ(NVIC_IREQn_t IREQ_NUM);

/*
@fn NVIC_SetPendingFlag
@brief set the pending flag of the peripheral
@param[in] IREQ_NUM
@retval uint8_t
 */
uint8_t NVIC_SetPendingFlag(NVIC_IREQn_t IREQ_NUM);

/*
@fn NVIC_ClearPendingFlag
@brief clear the pending flag of the peripheral
@param[in] IREQ_NUM
@retval uint8_t
 */
uint8_t NVIC_ClearPendingFlag(NVIC_IREQn_t IREQ_NUM);

/*
@fn NVIC_GetPendingFlag
@brief get the pending flag value
@param[in] IREQ_NUM
@retval uint8_t
 */
uint8_t NVIC_GetPendingFlag(NVIC_IREQn_t IREQ_NUM);

/*
@fn NVIC_SetGetActiveFlag
@brief get the active flag value
@param[in] IRQ_Num
@retval uint8_t
 */
uint8_t NVIC_SetGetActiveFlag(NVIC_IREQn_t IREQ_NUM);

/*
@fn NVIC_SetIRQPriority
@brief set the priority group
@param[in] IREQ_NUM , priority
@retval uint8_t
 */
uint8_t	NVIC_SetIRQPriority(NVIC_IREQn_t IREQ_NUM, uint8_t priority);



#endif
