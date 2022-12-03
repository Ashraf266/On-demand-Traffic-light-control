/*
 * led.h
 *
 * Created: 28/11/2022 21:45:00
 *  Author: Ashraf
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../Utilities/types.h"
#include "../../MCAL/DIO/dio.h"

/************************************************************************/
/*						   Types Declaration                            */
/************************************************************************/

typedef enum
{
	LED_ERROR,LED_SUCCESS
}LED_state;

/************************************************************************/
/*						   Definitions                                  */
/************************************************************************/

#define ON			HIGH
#define OFF			LOW

/* Cars LEDs */
#define CAR_RED_LED_PIN					PIN0
#define CAR_RED_LED_PORT				PORT_A


#define CAR_YELLOW_LED_PIN				PIN1
#define CAR_YELLOW_LED_PORT				PORT_A

#define CAR_GREEN_LED_PIN				PIN2
#define CAR_GREEN_LED_PORT				PORT_A

/* Pedestrians LEDs */
#define PEDESTRIANS_RED_LED_PIN					PIN0
#define PEDESTRIANS_RED_LED_PORT				PORT_B


#define PEDESTRIANS_YELLOW_LED_PIN				PIN1
#define PEDESTRIANS_YELLOW_LED_PORT				PORT_B

#define PEDESTRIANS_GREEN_LED_PIN				PIN2
#define PEDESTRIANS_GREEN_LED_PORT				PORT_B

/************************************************************************/
/*                     Functions ProtoTypes                             */
/************************************************************************/

/*initialize led*/
LED_state LED_init(uint8_t ledPin, uint8_t ledPort);

/*Turn on led*/
LED_state LED_on(uint8_t ledPin, uint8_t ledPort);

/*toggle led*/
LED_state LED_toggle(uint8_t ledPin, uint8_t ledPort);

/*Turn off led*/
LED_state LED_off(uint8_t ledPin, uint8_t ledPort);



#endif /* LED_H_ */