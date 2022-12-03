/*
 * timer.c
 *
 * Created: 30/11/2022 19:32:38
 *  Author: Ashraf
 */ 

#include "timer.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"
#include "../Interrupt Library/interrupts.h"


/* Global Variables */
static volatile void (* g_callBackFucntion_ptr)(void) = NULL_PTR;

/* ISR */

/* over flow ISR */
ISR(TIMER0_OVF)
{
	/* Check if callBack function pointer is NULL */
	if(g_callBackFucntion_ptr != NULL_PTR)
	{
		(* g_callBackFucntion_ptr)();
	}
}

/* compare match ISR */
ISR(TIMER0_COMP)
{
	/* Check if callBack function pointer is NULL */
	if(g_callBackFucntion_ptr != NULL_PTR)
	{
		(* g_callBackFucntion_ptr)();
	}
}

/************************************************************************/
/*					      Functions Definition                          */
/************************************************************************/

TIMER_state TIMER_init(TIMER_config * config)
{
	switch(config->mode)
	{
		case NORMAL_MODE:
						/* set FOC0 bit */
						TCCR0 = (1<<7);
						/* enable Timer over flow interrupt */
						TIMSK = (1<<0);
		break;
		case CTC_MODE:
						/* set FOC0 bit & WGM01 bit*/
						TCCR0 = (1<<7) | (1<<3);
						/* enable Timer compare match interrupt */
						TIMSK = (1<<1);		
		break;
		default:
		return TIMER_ERROR;
		break;
	}
	return TIMER_SUCCESS;
}
TIMER_state TIMER_start(TIMER_config * config)
{
		switch(config->mode)
		{
			case NORMAL_MODE:
							/* set timer initial value */
							TCNT0 = config->timerInitialValue;
							/* set the pre-scaler to start counting */
							TCCR0 = (TCCR0 & 0xF8) | (config->clock & 0x07);
			break;
			case CTC_MODE:
							/* set timer compare value */
							OCR0 = config->timerCompareValue;
							/* set the pre-scaler to start counting */
							TCCR0 = (TCCR0 & 0xF8) | (config->clock & 0x07);
			break;
			default:
							return TIMER_ERROR;
			break;
		}
		return TIMER_SUCCESS;
}

void TIMER_stop(void)
{
	TCCR0 = 0;
	CLEAR_BIT(TIMSK,0);
	CLEAR_BIT(TIMSK,1);
}

void TIMER_setCallBack(void (*callBack)(void))
{
	/* assign call back function to the pointer that will run in ISR */
	g_callBackFucntion_ptr = (volatile void (*)(void))callBack;
}
