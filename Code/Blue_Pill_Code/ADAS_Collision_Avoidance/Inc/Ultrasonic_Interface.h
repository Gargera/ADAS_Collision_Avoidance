/*
 * Ultrasonic_Interface.h
 *
 *  Created on: Apr 1, 2024
 *      Author: Gargera
 */

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

#include <stdint.h>

typedef struct
{
	uint8_t TrigPort ;
	uint8_t TrigPin  ;
	uint8_t EchoPort ;
	uint8_t EchoPin  ;
}Ultrasonic_t;


/*
 * @fn		:	Ultrasonic_Init
 * @brief	:	Initializes the Ultrasonic
 * @param	:	void
 * @retval	:	void
 *
 * */
void Ultrasonic_Init(void);

/*
 * @fn		:	Ultrasonic_readDistance
 * @brief	:	Calculates the distance
 * @param	:	Ultrasonic_Conf     (Ultrasonic_t*)
 * @retval	:	uint32_t
 *
 * */
uint32_t Ultrasonic_readDistance(Ultrasonic_t* Ultrasonic_Conf);

#endif /* ULTRASONIC_INTERFACE_H_ */
