/*
 * led.c
 *
 * Created: 28/11/2022 21:44:49
 *  Author: Ashraf
 */ 


#include "led.h"

/************************************************************************/
/*                     Functions Definitions                            */
/************************************************************************/

LED_state LED_init(uint8_t ledPin, uint8_t ledPort)
{
	if(DIO_init(ledPin, ledPort, OUT) == DIO_SUCCESS )
	{
		return LED_SUCCESS;
	}
	else
	{
		return LED_ERROR;
	}
}
LED_state LED_on(uint8_t ledPin, uint8_t ledPort)
{
	if(DIO_write(ledPin, ledPort, ON) == DIO_SUCCESS )
	{
		return LED_SUCCESS;
	}
	else
	{
		return LED_ERROR;
	}
}
LED_state LED_toggle(uint8_t ledPin, uint8_t ledPort)
{
	if(DIO_toggle(ledPin, ledPort) == DIO_SUCCESS )
	{
		return LED_SUCCESS;
	}
	else
	{
		return LED_ERROR;
	}
}
LED_state LED_off(uint8_t ledPin, uint8_t ledPort)
{
	if(DIO_write(ledPin, ledPort, OFF) == DIO_SUCCESS )
	{
		return LED_SUCCESS;
	}
	else
	{
		return LED_ERROR;
	}
}