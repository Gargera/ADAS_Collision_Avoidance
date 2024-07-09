#ifndef MOTORDRIVER_MOTORDRIVER_CONFIG_H
#define MOTORDRIVER_MOTORDRIVER_CONFIG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "GPIO_INTERFACE.h"
#include "GPT_interface.h"


/*LEFT SIDE IN MY CAR*/
#define MOTORA_TIMER           TIMER_u8_4
#define MOTORA_TIMER_CC        GPT_u8_PWM_CHANNEL1


/* RIGHT SIDE IN MY CAR*/
#define MOTORB_TIMER           TIMER_u8_4
#define MOTORB_TIMER_CC        GPT_u8_PWM_CHANNEL2


#endif 

