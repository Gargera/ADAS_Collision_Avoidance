/*
 * Project_Config.c
 *
 *  Created on: Jun 25, 2024
 *      Author: Amina
 */


#include <stdint.h>
#include "Stm32F103xx.h"
#include "Bit_Math.h"

#include "GPIO_INTERFACE.h"

#include "USART_Interface.h"

#include "MotorDriver_Interface.h"

#include "Ultrasonic_Interface.h"

#include "Project_Defines.h"

const PinConfig_t uart1_tx_PinConfig={
		.Port=USART1_TX_P0RT,
		.PinNum=USART1_tx_pin,
		.Mode=OUTPUT_MODE2MHZ,
		.InputConf=FLOATING_INPUT,
		.OutputConf=AF_OUTPUT_PP,

};
const PinConfig_t uart1_rx_PinConfig={
		.Port=USART1_RX_P0RT,
		.PinNum=USART1_rx_pin,
		.Mode=INPUT_MODE,
		.InputConf=FLOATING_INPUT,
		.OutputConf=AF_OUTPUT_PP,

};


const USART_ConfigReg_t USART1_ConfigReg ={
		.number=USART1,
		.mode=Enable_TX_RX,
		.stop_bit=STOP_BITS_1,
		.word=WORD_LENGTH_8,
		.parity=noparity,
		.baudRate=9600,
		.hd=Disable_HD,
		.clock=CLOCK_Disable,

};



const PinConfig_t uart3_tx_PinConfig={
		.Port=USART3_TX_P0RT,
		.PinNum=USART3_tx_pin,
		.Mode=OUTPUT_MODE2MHZ,
		.InputConf=FLOATING_INPUT,
		.OutputConf=AF_OUTPUT_PP,

};
const PinConfig_t uart3_rx_PinConfig={
		.Port=USART3_RX_P0RT,
		.PinNum=USART3_rx_pin,
		.Mode=INPUT_MODE,
		.InputConf=FLOATING_INPUT,
		.OutputConf=AF_OUTPUT_PP,

};


const USART_ConfigReg_t USART3_ConfigReg ={
		.number=USART3,
		.mode=Enable_TX_RX,
		.stop_bit=STOP_BITS_1,
		.word=WORD_LENGTH_8,
		.parity=noparity,
		.baudRate=9600,
		.hd=Disable_HD,
		.clock=CLOCK_Disable,

};


const PinConfig_t SERVO1_PinConfig = ///Timer2PWMCh2PB3
{
		.Port=SERVO1_PWM_PORT,
		.PinNum=SERVO1_pin,
		.Mode=OUTPUT_MODE50MHZ,
		.InputConf=FLOATING_INPUT,
		.OutputConf=AF_OUTPUT_PP,

};

/*Timer 4 PWM Mode channel1  PB6*/
const	PinConfig_t motorA_pwm_PinConfig =///Timer4PWMCh1PB6
{
		.Port=MOTORA_PWM_PORT,
		.PinNum=MOTORA_PWM_pin,
		.Mode=OUTPUT_MODE50MHZ,
		.InputConf=FLOATING_INPUT,
		.OutputConf=AF_OUTPUT_PP,
};

/*Timer 4 PWM Mode channel2  PB7 */
const	PinConfig_t motorB_pwm_PinConfig =///Timer4PWMCh2PB7
{
		.Port=MOTORB_PWM_PORT,
		.PinNum=MOTORB_PWM_pin,
		.Mode=OUTPUT_MODE50MHZ,
		.InputConf=FLOATING_INPUT,
		.OutputConf=AF_OUTPUT_PP,

};

const PinConfig_t motor_in1_PinConfig =
{
		.Port=MOTORA_PORT,
		.PinNum=MOTORDRIVER_IN1,
		.Mode=OUTPUT_MODE50MHZ,
		.InputConf=FLOATING_INPUT,
		.OutputConf=GP_OUTPUT_PP,
};

const PinConfig_t motor_in2_PinConfig =
{
		.Port=MOTORA_PORT,
		.PinNum=MOTORDRIVER_IN2,
		.Mode=OUTPUT_MODE50MHZ,
		.InputConf=FLOATING_INPUT,
		.OutputConf=GP_OUTPUT_PP,

};

const PinConfig_t motor_in3_PinConfig =
{
		.Port=MOTORB_PORT,
		.PinNum=MOTORDRIVER_IN3,
		.Mode=OUTPUT_MODE50MHZ,
		.InputConf=FLOATING_INPUT,
		.OutputConf=GP_OUTPUT_PP,

};

const PinConfig_t motor_in4_PinConfig =
{
		.Port=MOTORB_PORT,
		.PinNum=MOTORDRIVER_IN4,
		.Mode=OUTPUT_MODE50MHZ,
		.InputConf=FLOATING_INPUT,
		.OutputConf=GP_OUTPUT_PP,

};

const PinConfig_t Front_Ultrasonic_Trig_Pin =
{
		.Port		=	ULTRASONIC_FRONT_TRIG_PORT,
		.PinNum		=	ULTRASONIC_FRONT_TRIG_PIN,
		.Mode       =   OUTPUT_MODE50MHZ,
		.OutputConf  =   GP_OUTPUT_PP
};

const PinConfig_t Back_Ultrasonic_Trig_Pin =
{
		.Port		=	ULTRASONIC_BACK_TRIG_PORT,
		.PinNum		=	ULTRASONIC_BACK_TRIG_PIN,
		.Mode       =   OUTPUT_MODE50MHZ,
		.OutputConf  =   GP_OUTPUT_PP
};


const PinConfig_t Ultrasonics_Echo_Pin =
{
		.Port		=	ULTRASONICS_ECHO_PORT,
		.PinNum		=	ULTRASONICS_ECHO_PIN,
		.Mode       =   INPUT_MODE,
		.InputConf  =   FLOATING_INPUT
};

const PinConfig_t Buzzer1_PinConfig =
{
		.Port		=	Buzzer1_PORT,
		.PinNum		=	Buzzer1_PIN,
		.Mode       =   OUTPUT_MODE50MHZ,
		.InputConf  =   FLOATING_INPUT,
		.OutputConf =   GP_OUTPUT_PP
};
