#include <stdint.h>

#include "Stm32F103xx.h"
#include "Bit_Math.h"
#include "error_typ.h"

#include "GPIO_prv.h"
#include "GPIO_INTERFACE.h"


/*
 * * * * * * * * * * * * * * * * *
          GPIO ARRAY
 * * * * * * * * * * * * * * * * *
 */
static GPIO_RegDef_t* GPIOx[GPIO_PERIPHERAL_NUM]= {  	GPIOA,
		GPIOB,
		GPIOC,
		GPIOD,
		GPIOE,
		GPIOF,
		GPIOG
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @fn GPIO_u8PinInit
 * @brief the function initiatizes the GPIO pin according to
 *  the input parameters
 * @param[in] Copy_PinConfig: the initialization value of pins
 * @retval Local_u8ErrorState
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  PinConfig:	Port, PinNum, Mode,
 *              OutputConfig, InputConfig
 */
uint8_t GPIO_u8PinInit(const PinConfig_t* PinConfig)
{
	uint8_t Local_ErrorState=OK;
	/*Check weather the pointer points to Null or Not*/
	if(PinConfig != NULL)
	{
		/*Check weather the configurations are valid or Not*/
		if((PinConfig->Port <= PORTG) && (PinConfig->PinNum <= PIN15) &&
				(PinConfig->Mode <= OUTPUT_MODE50MHZ) && (PinConfig->InputConf <= INPUT_PUPD )
				&& (PinConfig->OutputConf <=AF_OUTPUT_OD) )
		{
			/* * * * * Select GPIO Mode: Input, OUTPUT_MODE10MHZ, OUTPUT_MODE10MHZ, OUTPUT_MODE10MHZ * * * * */
			if(PinConfig->PinNum <= PIN7)
			{
				/*Pins from PIN0 to PIN7*/
				GPIOx[PinConfig->Port]->GPIOx_CRL&=~(CRL_MASK<<(CRL_PIN_ACCESS*PinConfig->PinNum)) ;
				GPIOx[PinConfig->Port]->GPIOx_CRL |= ( PinConfig->Mode <<(CRL_PIN_ACCESS*PinConfig->PinNum));

				/*Check weather the mode is input or output*/
				if(PinConfig->Mode == INPUT_MODE)
				{
					/*input*/
					GPIOx[PinConfig->Port]->GPIOx_CRL &=~(CRL_MASK<<(CNF_OFFSET+(CRL_PIN_ACCESS*PinConfig->PinNum))) ;
					GPIOx[PinConfig->Port]->GPIOx_CRL |= ( PinConfig->InputConf <<(CNF_OFFSET+(CRL_PIN_ACCESS*PinConfig->PinNum)));
				}else
				{
					/*output*/
					GPIOx[PinConfig->Port]->GPIOx_CRL &=~(CRL_MASK<<(CNF_OFFSET+(CRL_PIN_ACCESS*PinConfig->PinNum))) ;
					GPIOx[PinConfig->Port]->GPIOx_CRL |= ( PinConfig->OutputConf <<(CNF_OFFSET+(CRL_PIN_ACCESS*PinConfig->PinNum)));
				}

			}
			else
			{
				/*****from PIN8 to PIN15*****/
				GPIOx[PinConfig->Port]->GPIOx_CRH &=~(CRH_MASK<<(CRH_PIN_ACCESS*((PinConfig->PinNum)%H_FAC))) ;
				GPIOx[PinConfig->Port]->GPIOx_CRH |= ( PinConfig->Mode <<(CRH_PIN_ACCESS*((PinConfig->PinNum)%H_FAC)));

				/*Check weather the mode is input or output*/
				if(PinConfig->Mode == INPUT_MODE)
				{
					/*input*/
					GPIOx[PinConfig->Port]->GPIOx_CRH &=~(CRH_MASK<<( CNF_OFFSET+ (CRH_PIN_ACCESS*((PinConfig->PinNum) %H_FAC) ) ) ) ;
					GPIOx[PinConfig->Port]->GPIOx_CRH |= ( PinConfig->InputConf <<(CNF_OFFSET+( CRH_PIN_ACCESS* ( (PinConfig->PinNum) %H_FAC) ) ) );
				}else
				{
					/*output*/
					GPIOx[PinConfig->Port]->GPIOx_CRH &=~(CRH_MASK<<( CNF_OFFSET+ (CRH_PIN_ACCESS*((PinConfig->PinNum) %H_FAC) ) ) ) ;
					GPIOx[PinConfig->Port]->GPIOx_CRH |= ( PinConfig->OutputConf <<(CNF_OFFSET+( CRH_PIN_ACCESS* ( (PinConfig->PinNum) %H_FAC) ) ) );
				}
			}
		}
		else
		{
			Local_ErrorState=NOK;
		}

	}
	else
	{
		Local_ErrorState=NULL_POINTER;
	}
	return Local_ErrorState;
}

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
uint8_t GPIO_u8SetPinValue(Port_t	Port , Pin_t	PinNum , PinVal_t PinVal)
{
	uint8_t Local_ErrorState=OK;

	if((Port<=PORTG) && (PinNum<=PIN15))
	{
		if(PinVal == PIN_LOW)
		{
			GPIOx[Port]->GPIOx_ODR &=~ (CLEAR_BIT_VAL<<PinNum); /*CLEAR*/
		}
		else if(PinVal == PIN_HIGH)
		{
			GPIOx[Port]->GPIOx_ODR |= (SET_BIT_VAL<<PinNum);	/*SET*/
		}
		else
		{
			Local_ErrorState=NOK;
		}
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}
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
uint8_t GPIO_u8TogglePinValue(Port_t	Port , Pin_t	PinNum )
{
	uint8_t Local_ErrorState = OK;

	if((Port<=PORTG) && (PinNum<=PIN15))
	{

		GPIOx[Port]->GPIOx_ODR ^=(TOGGLE_BIT_VAL<<PinNum);

	}
	else
	{
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;
}
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
uint8_t GPIO_u8ReadPinValue(Port_t	Port , Pin_t	PinNum , PinVal_t*	PinVal)
{
	uint8_t Local_ErrorState=OK;

	if((Port<=PORTG) && (PinNum<=PIN15))
	{

		*PinVal = (((GPIOx[Port]->GPIOx_IDR)>>PinNum)&GET_BIT_VAL);

	}
	else
	{
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;
}

/*
 *@fn		: GPIO_Write4Bits
 *@brief	: to set 4 Consecutive bits with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: PinNum			(ENUM: @Pin_t)
 *@param	: Copy_u8Val		(uint8_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
uint8_t GPIO_Write4Bits(Port_t	Port , Pin_t	PinNum , uint8_t Copy_u8Val)
{
	uint8_t Local_ErrorState = OK;

	if((Port <= PORTG) && (Port >= PORTA)
			&& (PinNum <= PIN15) && (PinNum >= PIN1))
	{
		Copy_u8Val &= 0b00001111;
		GPIOx[Port]->GPIOx_ODR &=~ ( 0b1111 << PinNum);
		GPIOx[Port]->GPIOx_ODR |= ( Copy_u8Val << PinNum);
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}


/*
 *@fn		: GPIO_Write8Bits
 *@brief	: to set 8 Consecutive bits with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: PinNum			(ENUM: @Pin_t)
 *@param	: Copy_u8Val		(uint8_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
uint8_t GPIO_Write8Bits(Port_t	Port , Pin_t PinNum , uint8_t Copy_u8Val)
{
	uint8_t Local_ErrorState=OK;

	if((Port <= PORTG) && (Port >= PORTA)
			&& (PinNum <= PIN15) && (PinNum >= PIN1))
	{
		GPIOx[Port]->GPIOx_ODR &=~ ( 0b11111111 << PinNum);
		GPIOx[Port]->GPIOx_ODR |= ( Copy_u8Val << PinNum);
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}

/*
 *@fn		: GPIO_Write16Bits
 *@brief	: to set 16 Consecutive bits with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: PortSection		(ENUM: @PortSection_t)
 *@param	: Copy_u16Val		(uint16_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
uint8_t GPIO_Write16Bits(Port_t	Port , PortSection_t PortSection , uint16_t Copy_u16Val)
{
	uint8_t Local_ErrorState=OK;

	if((Port <= PORTG) && (Port >= PORTA))
	{
		if(PortSection == LOWER_SECTION)
		{
			GPIOx[Port]->GPIOx_ODR &=~  0xFFFF ;
			GPIOx[Port]->GPIOx_ODR |=  Copy_u16Val ;
		}
		else
		{
			GPIOx[Port]->GPIOx_ODR &=~ ( 0xFFFF << 8);
			GPIOx[Port]->GPIOx_ODR |= ( Copy_u16Val << 8);
		}
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}

/*
 *@fn		: GPIO_Write16Bits
 *@brief	: to set 32 bits (whole the port) with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: Copy_u32Val		(uint32_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
uint8_t GPIO_WritePort(Port_t	Port , uint32_t Copy_u32Val)
{
	uint8_t Local_ErrorState=OK;

	if((Port <= PORTG) && (Port >= PORTA))
	{
		GPIOx[Port]->GPIOx_ODR &=~ ( 0xFFFFFFFF);
		GPIOx[Port]->GPIOx_ODR |= ( Copy_u32Val );
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}
