/*
 * button.h
 *
 * Created: 28/11/2022 23:18:34
 *  Author: Ashraf
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../Utilities/types.h"
#include "../../MCAL/DIO/dio.h"

/************************************************************************/
/*						   Types Declaration                            */
/************************************************************************/

typedef enum
{
	BUTTON_ERROR,BUTTON_SUCCESS
}BUTTON_state;

/************************************************************************/
/*						   Definitions                                  */
/************************************************************************/

/*Button states*/
#define PRESSED			HIGH
#define RELEASED		LOW

/*Pedestrian button*/
#define PEDESTRIANS_BUTTON_PIN			PIN2
#define PEDESTRIANS_BUTTON_PORT			PORT_D

/************************************************************************/
/*                     Functions ProtoTypes                             */
/************************************************************************/

/*Initialize Button*/
BUTTON_state BUTTON_init(uint8_t buttonPin,uint8_t buttonPort);

/*read Button*/
BUTTON_state BUTTON_read(uint8_t buttonPin,uint8_t buttonPort, uint8_t *value);



#endif /* BUTTON_H_ */