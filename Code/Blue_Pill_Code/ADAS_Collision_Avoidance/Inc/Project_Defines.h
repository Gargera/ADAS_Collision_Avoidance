/*
 * Project_Defines.h
 *
 *  Created on: Jun 18, 2024
 *      Author: Gargera
 */

#ifndef PROJECT_DEFINES_H_
#define PROJECT_DEFINES_H_

#define MOVE_FORWARD                    'F'
#define MOVE_BACKWARD                   'B'
#define MOVE_RIGHT_FORWARD              'R'
#define MOVE_LEFT_FORWARD               'L'
#define MOVE_LEFT_BACKWARD              'l'
#define MOVE_RIGHT_BACKWARD             'r'
#define STOP_CAR                        'S'

#define AEB_SYSTEM                      'A' //DEFAULT SYSTEM
#define ACC_SYSTEM                      'C'
#define SELF_PARKING_SYSTEM             'P'

#define SPEED_10                        '1'
#define SPEED_20                        '2'
#define SPEED_30                        '3'
#define SPEED_40                        '4'
#define SPEED_50                        '5'
#define SPEED_60                        '6'
#define SPEED_70                        '7'
#define SPEED_80                        '8'
#define SPEED_90                        '9'



/***************USED PORTS & PINS******************/

#define USART1_TX_P0RT                  PORTA
#define USART1_RX_P0RT                  PORTA

#define USART3_TX_P0RT                  PORTB
#define USART3_RX_P0RT                  PORTB

#define LED1_PORT                       PORTC

#define Buzzer1_PORT                    PORTA

#define MOTORA_PORT                     PORTA
#define MOTORB_PORT                     PORTA

#define	MOTORA_PWM_PORT                 PORTB
#define	MOTORB_PWM_PORT                 PORTB

#define SERVO1_PWM_PORT                 PORTA

#define ULTRASONICS_ECHO_PORT           PORTB

#define ULTRASONIC_FRONT_TRIG_PORT      PORTA
#define ULTRASONIC_BACK_TRIG_PORT       PORTA


typedef enum{
	MOTORDRIVER_IN1=0,
	SERVO1_pin =1,
	ULTRASONIC_FRONT_TRIG_PIN=2,
	MOTORDRIVER_IN3=3,
	MOTORDRIVER_IN4=4,
	ULTRASONIC_BACK_TRIG_PIN=5,
	Buzzer1_PIN=6,
	USART1_tx_pin=9,
	USART1_rx_pin=10,
	MOTORDRIVER_IN2=12

}USED_PINS_PORTA_t;

typedef enum{
	ULTRASONICS_ECHO_PIN=0,
	MOTORA_PWM_pin =6,
	MOTORB_PWM_pin=7,
	USART3_tx_pin=10,
	USART3_rx_pin=11
}USED_PINS_PORTB_t;

typedef enum{
	LED1_pin =14,

}USED_PINS_PORTC_t;


/*Configure PWM PINS*/
/*TIMER2 CH2 Pin-> PA1*/
/*TIMER2 CH3 Pin-> PB10*/
/*TIMER3 CH2 Pin-> PA7*/
/*TIMER4 CH1 Pin-> PB6*/
/*TIMER4 CH2 Pin-> PB7*/

#endif /* PROJECT_DEFINES_H_ */
