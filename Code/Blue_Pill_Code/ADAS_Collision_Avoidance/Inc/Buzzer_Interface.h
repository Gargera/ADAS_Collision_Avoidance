#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

#include <stdint.h>

typedef struct
{
	uint8_t BuzzerPort;
	uint8_t BuzzerPin;
}Buzzer_t;

/*
 * @fn		:	Buzzer_vInit
 * @brief	:	Initializes the Buzzer
 * @param	:	void
 * @retval	:	void
 */
void Buzzer_vInit(void);

/*
 * @fn		:	Buzzer_vTurnOn
 * @brief	:	Turn on the Buzzer
 * @param	:	Buzzer_Conf     (Buzzer_t*)
 * @retval	:	void
 */
void Buzzer_vTurnOn(Buzzer_t* Buzzer_Conf);

/*
 * @fn		:	Buzzer_vTurnOff
 * @brief	:	Turn off the Buzzer
 * @param	:	Buzzer_Conf     (Buzzer_t*)
 * @retval	:	void
 */
void Buzzer_vTurnOff(Buzzer_t* Buzzer_Conf);

/*
 * @fn		:	Buzzer_vToggle
 * @brief	:	Toggle the Buzzer
 * @param	:	Buzzer_Conf     (Buzzer_t*)
 * @retval	:	void
 */
void Buzzer_vToggle(Buzzer_t* Buzzer_Conf);

/*
 * @fn		:	Buzzer_ReadStatues
 * @brief	:	Read the Buzzer Statues
 * @param	:	Buzzer_Conf     (Buzzer_t*)
 * @retval	:	uint8_t
 */
uint8_t Buzzer_ReadStatues(Buzzer_t* Buzzer_Conf);

#endif /* BUZZER_INTERFACE_H_ */
