/*
 * timer.h
 *
 * Created: 30/11/2022 19:32:23
 *  Author: Ashraf
 */ 


#ifndef TIMER_H_
#define TIMER_H_



#include "../../Utilities/types.h"

/************************************************************************/
/*						   Types Declaration                            */
/************************************************************************/

/* Timer0 Modes enum */
typedef enum
{
	NORMAL_MODE,
	CTC_MODE
}TIMER_modes;

/* Timer0 Pre-scaler enum*/
typedef enum
{
	TIMER0_STOP,
	T0_F_CPU,
	T0_F_CPU_8,
	T0_F_CPU_64,
	T0_F_CPU_256,
	T0_F_CPU_1024,
	EXTERNAL_CLK_FALLING,
	EXTERNAL_CLK_RISING
}TIMER_clk;

/* Timer0 Configuration Structure */
typedef struct 
{
	TIMER_modes mode;
	TIMER_clk   clock;
	uint8_t		timerInitialValue;
	uint8_t		timerCompareValue;
}TIMER_config;

typedef enum
{
	TIMER_ERROR,TIMER_SUCCESS
}TIMER_state;


/************************************************************************/
/*                        Functions prototypes                          */
/************************************************************************/

/* initialize the timer */
TIMER_state TIMER_init(TIMER_config * config);

/* start the timer */
TIMER_state TIMER_start(TIMER_config * config);

/* stop the timer */
void TIMER_stop(void);

/* set the call back function to run it in the ISR */
void TIMER_setCallBack(void (*callBack)(void));


#endif /* TIMER_H_ */