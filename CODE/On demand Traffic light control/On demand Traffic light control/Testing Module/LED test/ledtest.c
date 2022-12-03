/*
 * ledtest.c
 *
 * Created: 30/11/2022 22:31:52
 *  Author: Ashraf
 */ 



#if 0

#include "../../ECUAL/LED/led.h"

int main(void)
{
	
	/* testing init function */
	LED_init(PIN0,PORT_A);
	LED_init(PIN1,PORT_A);
	
	/* testing LED_on function */
	LED_on(PIN0,PORT_A);
	LED_on(PIN1,PORT_A);
	
	/* testing toggle function */
	LED_toggle(PIN0,PORT_A);
	LED_toggle(PIN0,PORT_A);
	
	/* testing LED_off function */
	LED_off(PIN0,PORT_A);
	LED_off(PIN1,PORT_A);
	
}

#endif