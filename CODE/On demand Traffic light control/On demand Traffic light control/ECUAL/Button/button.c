/*
 * button.c
 *
 * Created: 28/11/2022 23:19:19
 *  Author: Ashraf
 */ 

#include "button.h"


/************************************************************************/
/*                     Functions Definitions                            */
/************************************************************************/

BUTTON_state BUTTON_init(uint8_t buttonPin,uint8_t buttonPort)
{
	if(DIO_init(buttonPin, buttonPort, IN) == DIO_SUCCESS )
	{
		return BUTTON_SUCCESS;
	}
	else
	{
		return BUTTON_ERROR;
	}
}

BUTTON_state BUTTON_read(uint8_t buttonPin,uint8_t buttonPort, uint8_t *value)
{
	if(DIO_read(buttonPin, buttonPort, value) == DIO_SUCCESS )
	{
		return BUTTON_SUCCESS;
	}
	else
	{
		return BUTTON_ERROR;
	}
}