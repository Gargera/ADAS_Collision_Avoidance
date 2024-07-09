
#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*Note: Timers from 2 to 5 are on APB1 Bus */
#define BUS_FREQUENCY							72000000 /*Hz*/

/*for 1000 ticks freq: a tick happens every 1 ms */
#define TICKS_FREQUENCY								1000 /*Hz*/

/*********************************************************************************************************/
/*Configurations for external clock for the timer:
 *
 *Options for external mode:
 * 1) External_Mode_One
 * 2) External_Mode_Two
 *
 * For external trigger filter: Refer to the Data-sheet at TIMx slave mode control register.
 * */
#define EXTERNAL_MODE							External_Mode_Two
#define EXTERNAL_TRIGGER_FILTER							0
/*********************************************************************************************************/
/*Choose PWM  frequency in Hz*/
#define PWM_FREQUENCY									72

#endif /* TIMER_CONFIG_H_ */
