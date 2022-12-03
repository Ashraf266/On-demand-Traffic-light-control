/*
 * diotest.c
 *
 * Created: 30/11/2022 22:31:35
 *  Author: Ashraf
 */ 



#if 0

#include "../../MCAL/DIO/dio.h"

int main(void)
{
	uint8_t value = 5;
	
	/* testing init function */
	DIO_init(PIN0,PORT_A,OUT);
	DIO_init(PIN1,PORT_A,IN);
	
	/* testing write function */
	DIO_write(PIN0,PORT_A,HIGH);
	DIO_write(PIN0,PORT_A,LOW);
	
	/* testing toggle function */
	DIO_toggle(PIN0,PORT_A);
	DIO_toggle(PIN0,PORT_A);
	
	/* testing read function */
	DIO_read(PIN1,PORT_A,&value);
	DIO_read(PIN1,PORT_A,&value);
	
	
	
	
	
}

#endif