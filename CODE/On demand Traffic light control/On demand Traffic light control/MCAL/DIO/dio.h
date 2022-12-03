/*
 * dio.h
 *
 * Created: 28/11/2022 19:48:06
 *  Author: Ashraf
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../../Utilities/types.h"

/************************************************************************/
/*						   Types Declaration                            */
/************************************************************************/

typedef enum
{
	DIO_ERROR,DIO_SUCCESS
}DIO_state;

/************************************************************************/
/*						   Definitions                                  */
/************************************************************************/

/*Ports Definitions*/
#define PORT_A				'A'
#define PORT_B				'B'
#define PORT_C				'C'
#define PORT_D				'D'

/*Pins Definitions*/
#define PIN0                 0
#define PIN1                 1
#define PIN2                 2
#define PIN3                 3
#define PIN4                 4
#define PIN5                 5
#define PIN6                 6
#define PIN7                 7

/*Direction Definitions*/
#define IN					 0
#define OUT					 1

/*Value Definitions*/
#define LOW					 0
#define HIGH				 1

/************************************************************************/
/*                     Functions ProtoTypes                             */
/************************************************************************/

/*initialize dio Direction*/
DIO_state DIO_init(uint8_t pinNumber, uint8_t portNumber, uint8_t direction);

/*write data to dio*/
DIO_state DIO_write(uint8_t pinNumber, uint8_t portNumber, uint8_t value);

/*toggle dio*/
DIO_state DIO_toggle(uint8_t pinNumber, uint8_t portNumber);

/*read dio*/
DIO_state DIO_read(uint8_t pinNumber, uint8_t portNumber, uint8_t *value);

#endif /* DIO_H_ */