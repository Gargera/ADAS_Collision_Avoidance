#ifndef  GPIO_INTERFACE_H_
#define  GPIO_INTERFACE_H_

#include "error_typ.h"

/*@PinVal_t*/
typedef enum{
	PIN_LOW=0,
	PIN_HIGH
}PinVal_t;
/*@Port_t*/
typedef enum{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,

}Port_t;

/*@Pin_t*/
typedef enum{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15

}Pin_t;
/*@Mode_t*/
typedef enum{
	INPUT_MODE=0,
	OUTPUT_MODE10MHZ,
	OUTPUT_MODE2MHZ,
	OUTPUT_MODE50MHZ,

}Mode_t;
/*@InputConf_t*/
typedef enum{
	ANALOG_MODE=0,
	FLOATING_INPUT,
	INPUT_PUPD,

}InputConf_t;
/*@OutputConf_t*/
typedef enum{
	GP_OUTPUT_PP=0,
	GP_OUTPUT_OD,
	AF_OUTPUT_PP,
	AF_OUTPUT_OD,

}OutputConf_t;

typedef enum{

	LOWER_SECTION,
	UPPER_SECTION

}PortSection_t;


/*
 * * * * * * * * * * * * * * * * *
 * * * PIN CONFIGURATIONS * *
 * * * * * * * * * * * * * * * * *
   TO PASS IT TO THE FUNCTION
         AS AN ARGUMENT
 * * * * * * * * * * * * * * * * *
 */
typedef struct{
	Port_t 			Port;
	Pin_t			PinNum;
	Mode_t			Mode;
	InputConf_t	    InputConf;
	OutputConf_t	OutputConf;

}PinConfig_t;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @fn GPIO_u8PinInit
 * @brief the function initiatizes the GPIO pin according to
 *  the input parameters
 * @param[in] Copy_PinConfig: the initialization value of pins
 * @retval Local_u8ErrorState
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  PinConfig:	Port, PinNum, Mode,
 *              Speed, OutputType,
 *              PullType, AltFunc
 */
uint8_t GPIO_u8PinInit(const PinConfig_t* Copy_PinConfig);
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                            GPIO SET PIN VALUE
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @fn GPIO_u8SetPinValue
 * @brief the function Set the GPIO pin value
 * @param[in] Port ,PinNum ,PinVal
 * @retval Local_u8ErrorState
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
uint8_t GPIO_u8SetPinValue(Port_t	Port , Pin_t	PinNum , PinVal_t PinVal);
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                            GPIO TOGGLE PIN VALUE
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @fn GPIO_u8TogglePinValue
 * @brief the function Toggle the GPIO pin value
 * @param[in] Port ,PinNum
 * @retval Local_u8ErrorState
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
uint8_t GPIO_u8TogglePinValue(Port_t	Port , Pin_t	PinNum );
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                            GPIO READ PIN VALUE
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @fn GPIO_u8ReadPinValue
 * @brief the function Read the GPIO pin value
 * @param[in] Port ,PinNum
 * @param[out] PinVal
 * @retval Local_u8ErrorState
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
uint8_t GPIO_u8ReadPinValue(Port_t	Port , Pin_t	PinNum , PinVal_t*	PinVal);

/*
 *@fn		: GPIO_Write4Bits
 *@brief	: to set 4 Consecutive bits with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: PinNum			(ENUM: @Pin_t)
 *@param	: Copy_u8Val		(uint8_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
uint8_t GPIO_Write4Bits(Port_t	Port , Pin_t	PinNum , uint8_t Copy_u8Val);

/*
 *@fn		: GPIO_Write8Bits
 *@brief	: to set 8 Consecutive bits with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: PinNum			(ENUM: @Pin_t)
 *@param	: Copy_u8Val		(uint8_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
uint8_t GPIO_Write8Bits(Port_t	Port , Pin_t PinNum , uint8_t Copy_u8Val);

/*
 *@fn		: GPIO_Write16Bits
 *@brief	: to set 16 Consecutive bits with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: PortSection		(ENUM: @PortSection_t)
 *@param	: Copy_u16Val		(uint16_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
uint8_t GPIO_Write16Bits(Port_t	Port , PortSection_t PortSection , uint16_t Copy_u16Val);

/*
 *@fn		: GPIO_Write16Bits
 *@brief	: to set 32 bits (whole the port) with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: Copy_u32Val		(uint32_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
uint8_t GPIO_WritePort(Port_t	Port , uint32_t Copy_u32Val);

#endif
