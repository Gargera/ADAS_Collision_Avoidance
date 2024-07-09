#ifndef GPT_INTERFACE_H_
#define GPT_INTERFACE_H_


#define TIMER_u8_2								2
#define TIMER_u8_3								3
#define TIMER_u8_4								4

/*******************************************************************************
 *                 	     		Counting Direction	                           *
 *******************************************************************************/
#define GPT_u8_COUNT_UP					0
#define GPT_u8_COUNT_DOWN				1

/*******************************************************************************
 *                 	     		Pwm Channels		                           *
 *******************************************************************************/
#define GPT_u8_PWM_CHANNEL1					0
#define GPT_u8_PWM_CHANNEL2					1
#define GPT_u8_PWM_CHANNEL3					2
#define GPT_u8_PWM_CHANNEL4					3


/*************************TIMER CONFIG PARA DATA TYPE START*****************************/
typedef enum{
	No_prescaler=0,
	Prescaler_div_2=1,
	Prescaler_div_4=2,
	Reserved3=3
}Clock_Types;

typedef enum{
	Auto_reload_preload_disabled=0,
	Auto_reload_preload_enabled=1
} Auto_reload_preload_Types;

typedef enum{
	Edge_aligned=0,
	Center_aligned_mode_1 =1,
	Center_aligned_mode_2 =2,
	Center_aligned_mode_3 =3
}Center_aligned_mode_Types;


typedef enum{
	upcounter=0,
	downcounter=1,
}Direction_Types;


typedef enum{
	One_pulse_mode_disabled=0,
	One_pulse_mode_enabled=1
}One_pulse_Types;


typedef enum{

	Update_request_source_enabled=0,
	Update_request_source_disabled=1
}Update_request_source_Types;

typedef enum{
	Up_Counter_enable=0,
	Down_Counter_enable=1
} Counter_enable_Types;

/*************************ICU CONFIG PARA DATA TYPE START*****************************/
typedef enum{
	CC_INPUT_TI2	=1,
	CC_INPUT_TI1	=2,
	CC_Input_TRC	=3
}CC_channel_types;

typedef enum{
	CC1=1,
	CC2=2,
	CC3=3,
	CC4=4
}channel_Types;

typedef enum{
	RISING_EDGE=0,
	FALLING_EDGE=1
}Edge_Types;

typedef struct{
	uint8_t Timer_NUM ;
	CC_channel_types CC_Types;
	channel_Types channel_selected;
	Edge_Types Edge_polarity;
}ICU_Types;
/*************************ICU CONFIG PARA DATA TYPE END*****************************/

/*******************************************************************************
 *                    		  Functions Prototypes                             *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:		GPT_u8Init
 * Description:			Function to initialize GPT
 * Parameters (in):    	Timer number, Timer direction (up or down) and the prescaler
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t GPT_u8Init(uint8_t Copy_u8TimerNumber , uint8_t Copy_u8Direction , uint16_t Copy_u16Prescaler);

/*******************************************************************************
 * Function Name:		GPT_u8SetBusyWait
 * Description:			Function to create delay with the timer 1
 * Parameters (in):    	Timer number and number of ticks
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t GPT_u8SetBusyWait(uint8_t Copy_u8TimerNumber , uint16_t Copy_u32NumOfTicks);

/*******************************************************************************
 * Function Name:		GPT_u8SetIntervalPeriodic
 * Description:			Timer number , Number of ticks and pointer to function to act as ISR
 * Parameters (in):    	void
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t GPT_u8SetIntervalPeriodic(uint8_t Copy_u8TimerNumber , uint16_t Copy_u32NumOfTicks , void(*Copy_pf)(void));

/*******************************************************************************
 * Function Name:		GPT_u8InitPwmChannel
 * Description:			Function to initialize PWM channel
 * Parameters (in):    	Channel Number
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t GPT_u8InitPwmChannel(uint8_t Copy_u8TimerNumber , uint8_t Copy_u8PwmChannel);

/*******************************************************************************
 * Function Name:		GPT_u8SetPWM
 * Description:			Function to create PWM with the timer 1
 * Parameters (in):    	Frequency , duty cycle and channel number
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t GPT_u8SetPWM(uint8_t Copy_u8TimerNumber , uint8_t Copy_u8PwmChannel , uint8_t Copy_u8PwmFrequency , float Copy_u8PwmDutyCycle);

/*******************************************************************************
 * Function Name:		GPT_u8Stop
 * Description:			Function to stop and disable the timer
 * Parameters (in):    	void
 * Parameters (out):   	u8
 * Return value:      	OK or Error
 ********************************************************************************/
uint8_t GPT_u8Stop(uint8_t Copy_u8TimerNumber);


void TIMER_VoidICUInit(ICU_Types *ICU_Values);

void Timer_start(uint8_t Copy_u8TimerNumber);

void Timer_stop(uint8_t Copy_u8TimerNumber);

void Timer_VoidEmptyCounterRegister(uint8_t Copy_u8TimerNumber);

void Timer_VoidIcuTriggerEdge(uint8_t Copy_u8TimerNumber,Edge_Types Edge_polarity,channel_Types CC);

uint16_t TIMER_U16IcuGetCaptureValue(uint8_t Copy_u8TimerNumber,channel_Types CC);

uint8_t Timer_U8IcuGetCaptureFlag(uint8_t Copy_u8TimerNumber,channel_Types CC);

void TIMER_VoidIcuInterruptEnable(uint8_t Copy_u8TimerNumber);

void Timer_VoidClearFlag(uint8_t Copy_u8TimerNumber);

void TIMER_VoidIcuInterruptDisable(uint8_t Copy_u8TimerNumber);


void Timer_VoidTimeEventGenerationSet(uint8_t Copy_u8TimerNumber);

#endif /* GPT_INTERFACE_H_ */
