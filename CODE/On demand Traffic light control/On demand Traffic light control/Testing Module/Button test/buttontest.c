/*
 * buttontest.c
 *
 * Created: 30/11/2022 22:32:05
 *  Author: Ashraf
 */ 

#if 0

#include "../../ECUAL/Button/button.h"

int main(void)
{
	uint8_t value = 5;
	
	/* testing init function */
	BUTTON_init(PIN0,PORT_A);
	BUTTON_init(PIN1,PORT_A);
	
	/* testing read function */
	BUTTON_read(PIN0, PORT_A, &value);
	BUTTON_read(PIN0, PORT_A, &value);

	
}

#endif