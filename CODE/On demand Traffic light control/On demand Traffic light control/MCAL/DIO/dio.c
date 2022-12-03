/*
 * dio.c
 *
 * Created: 28/11/2022 19:47:54
 *  Author: Ashraf
 */ 

#include "dio.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"


/************************************************************************/
/*                     Functions Definitions                            */
/************************************************************************/

/*initialize dio Direction*/
DIO_state DIO_init(uint8_t pinNumber, uint8_t portNumber, uint8_t direction)
{
	/* check the port number & set the pin direction according to the given pin number */
	switch(portNumber)
	{
		case PORT_A:
				if(direction == IN)
				{
					CLEAR_BIT(DDRA,pinNumber);
				}
				else if(direction == OUT)
				{
					SET_BIT(DDRA,pinNumber);
				}
				else
				{
					return DIO_ERROR;
				}
		break;
		case PORT_B:
				if(direction == IN)
				{
					DDRB &= ~(1<<pinNumber);
				}
				else if(direction == OUT)
				{
					DDRB |= (1<<pinNumber);
				}
				else
				{
					return DIO_ERROR;
				}
		break;
		case PORT_C:
				if(direction == IN)
				{
					DDRC &= ~(1<<pinNumber);
				}
				else if(direction == OUT)
				{
					DDRC |= (1<<pinNumber);
				}
				else
				{
					return DIO_ERROR;
				}
		break;
		case PORT_D:
				if(direction == IN)
				{
					DDRD &= ~(1<<pinNumber);
				}
				else if(direction == OUT)
				{
					DDRD |= (1<<pinNumber);
				}
				else
				{
					return DIO_ERROR;
				}
		break;
	}
	return DIO_SUCCESS;
}

/*write data to dio*/
DIO_state DIO_write(uint8_t pinNumber, uint8_t portNumber, uint8_t value)
{
	/* check the port number & write the given value according to the given pin number */
	switch(portNumber)
	{
		case PORT_A:
				if(value == LOW)
				{
					CLEAR_BIT(PORTA,pinNumber);
				}
				else if(value == HIGH)
				{
					SET_BIT(PORTA,pinNumber);
				}
				else
				{
					return DIO_ERROR;
				}
		break;
		case PORT_B:
				if(value == LOW)
				{
					PORTB &= ~(1<<pinNumber);
				}
				else if(value == HIGH)
				{
					PORTB |= (1<<pinNumber);
				}
				else
				{
					return DIO_ERROR;
				}
		break;
		case PORT_C:
				if(value == LOW)
				{
					PORTC &= ~(1<<pinNumber);
				}
				else if(value == HIGH)
				{
					PORTC |= (1<<pinNumber);
				}
				else
				{
					return DIO_ERROR;
				}
		break;
		case PORT_D:
				if(value == LOW)
				{
					PORTD &= ~(1<<pinNumber);
				}
				else if(value == HIGH)
				{
					PORTD |= (1<<pinNumber);
				}
				else
				{
					return DIO_ERROR;
				}
		break;
	}
	return DIO_SUCCESS;
}

/*toggle dio*/
DIO_state DIO_toggle(uint8_t pinNumber, uint8_t portNumber)
{
		switch(portNumber)
		{
			case PORT_A:
						TOGGLE_BIT(PORTA,pinNumber);
			break;
			case PORT_B:
						PORTB ^= (1<<pinNumber);
			break;
			case PORT_C:
						PORTC ^= (1<<pinNumber);
			break;
			case PORT_D:
						PORTD ^= (1<<pinNumber);
			break;
			default:
						return DIO_ERROR;
			break;
		}
		return DIO_SUCCESS;
}

/*read dio*/
DIO_state DIO_read(uint8_t pinNumber, uint8_t portNumber, uint8_t *value)
{
			switch(portNumber)
			{
				case PORT_A:
							*value = GET_BIT(PINA,pinNumber);
				break;
				case PORT_B:
							*value = (PINB>>pinNumber)&1;
				break;
				case PORT_C:
							*value = (PINC>>pinNumber)&1;
				break;
				case PORT_D:
							*value = (PIND>>pinNumber)&1;
				break;
				default:
							return DIO_ERROR;
				break;
			}
			return DIO_SUCCESS;
}