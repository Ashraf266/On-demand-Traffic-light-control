/*------------------------------------------------------------------
[FILE NAME]:	registers.h
[AUTHOR]:		Mohamed Ashraf
[DATE CREATED]:	28/11/2022
[DESCRIPTION]:	Header file Contains ATmega32 Registers
------------------------------------------------------------------*/


/************************************************************************/
/*						 ATmega32 Registers		   	                    */
/************************************************************************/

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "types.h"

/************************************************************************/
/*                          DIO Registers                               */
/************************************************************************/

/* PORT A registers */
#define PORTA		(*((volatile uint8_t * const)(0x3B)))
#define DDRA		(*((volatile uint8_t * const)(0x3A)))
#define PINA		(*(volatile const uint8_t * const)(0x39))

/* PORT B registers */
#define PORTB		(*((volatile uint8_t * const)(0x38)))
#define DDRB		(*((volatile uint8_t * const)(0x37)))
#define PINB		(*(volatile const uint8_t * const)(0x36))

/* PORT C registers */
#define PORTC		(*((volatile uint8_t * const)(0x35)))
#define DDRC		(*((volatile uint8_t * const)(0x34)))
#define PINC		(*(volatile const uint8_t * const)(0x33))

/* PORT D registers */
#define PORTD		(*((volatile uint8_t * const)(0x32)))
#define DDRD		(*((volatile uint8_t * const)(0x31)))
#define PIND		(*(volatile const uint8_t * const)(0x30))


/************************************************************************/
/*                         Timers Registers                             */
/************************************************************************/

#define TIFR		(*((volatile uint8_t * const)(0x58)))
#define TIMSK		(*((volatile uint8_t * const)(0x59)))

/* Timer0 */
#define TCNT0		(*((volatile uint8_t * const)(0x52)))
#define TCCR0		(*((volatile uint8_t * const)(0x53)))
#define OCR0		(*((volatile uint8_t * const)(0x5C)))

/************************************************************************/
/*                      Interrupts  Registers                           */
/************************************************************************/

#define MCUCR		(*((volatile uint8_t * const)(0x55)))
#define MCUCSR		(*((volatile uint8_t * const)(0x54)))

/* External Interrupts */
#define GICR		(*((volatile uint8_t * const)(0x5B)))
#define GIFR		(*((volatile uint8_t * const)(0x5A)))


#endif /* REGISTERS_H_ */