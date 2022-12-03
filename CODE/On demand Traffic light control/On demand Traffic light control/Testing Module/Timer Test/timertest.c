/*
 * timertest.c
 *
 * Created: 30/11/2022 22:32:21
 *  Author: Ashraf
 */ 

#if 0

#include "../../MCAL/Timer/timer.h"
#include "../../MCAL/Interrupt Library/interrupts.h"

uint8_t g_counter = 0;

void count(void)
{
	g_counter++;
}

int main(void)
{
	sei();
	TIMER_config T0_Configurations = {NORMAL_MODE,T0_F_CPU,0,0};
	TIMER_init(&T0_Configurations);
	TIMER_setCallBack(count);
	TIMER_start(&T0_Configurations);
	while(g_counter < 5);
	TIMER_stop();
	
}

#endif