#ifndef MOTORDRIVER_MOTORDRIVER_INTERFACE_H
#define MOTORDRIVER_MOTORDRIVER_INTERFACE_H


void Motors_Init(void);
void MOTORS_Forward(uint8_t speed);
void MOTORS_Backward(uint8_t speed);
void Motors_Speed(uint8_t speed);
void MOTORS_Stop(void);


void MOTORS_Forward_Right(uint8_t speed);
void MOTORS_Forward_Left(uint8_t speed);

void MOTORS_Backward_Right(uint8_t speed);
void MOTORS_Backward_Left(uint8_t speed);


void Motor1_Forward(void);
void Motor2_Forward(void);

void Motor1_Back(void);
void Motor2_Back(void);

void Motor1_Stop(void);
void Motor2_Stop(void);

void Motor1_Speed(uint8_t speed);
void Motor2_Speed(uint8_t speed);

#endif


