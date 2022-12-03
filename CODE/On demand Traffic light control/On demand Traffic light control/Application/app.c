/*
 * app.c
 *
 * Created: 30/11/2022 21:24:02
 *  Author: Ashraf
 */ 


#include "app.h"
#include "../MCAL/Interrupt Library/interrupts.h"
#include "../Utilities/registers.h"
#include "../MCAL/Timer/timer.h"
#include "../MCAL/DIO/dio.h"
#include "../ECUAL/Button/button.h"
#include "../ECUAL/LED/led.h"

/************************************************************************/
/*                     PRIVATE Functions ProtoTypes                     */
/************************************************************************/
static void APP_init(void);
static void countOverFlows(void);
static void delaySeconds(uint8_t sec);
static void normalMode(carsLED_State * state);
static void pedestrianMode(carsLED_State * state);
static void delayHalfSeconds(uint8_t sec);
static void turnOn_carsGreenlight(void);
static void turnOn_carsYellowlight(void);
static void turnOn_carsRedlight(void);
static void turnOn_pedestrianRedWithCarsGreen(void);
static void turnOn_pedestrianRedWithCarsYellow(void);
static void turnOn_bothYellowlights(void);
static void turnOn_pedestrianGreenWithCarsRed(void);



/************************************************************************/
/*                          Global Variables                            */
/************************************************************************/
/* counter to count number of timers overflows */
uint8_t g_overFlows = 0;

/* flag to indicate Entering the pedestrian Mode */
uint8_t g_pedestrianModeFlag = 0;

/* flag to indicate that pedestrian Mode is Active at that moment */
uint8_t g_inProgressFlag = 0;


/************************************************************************/
/*								   ISR                                  */
/************************************************************************/
/* External interrupt ISR */
ISR(EXT_INT_0)
{
	/* if pedestrian mode is activated do not set the pedestrian mode flag */
	if(g_inProgressFlag == 0)
		g_pedestrianModeFlag = 1;
}


/************************************************************************/
/*                      Functions Definition                            */
/************************************************************************/

/*
 * Description:
 *			function to initialize everything the application need to start functioning
 */
static void APP_init(void)
{
	/* Set Global Interrupt Enable bit "I-bit" */
	sei();
	
	/* External interrupt Initialization */
	
	/* initializing PD2(INT0) as input pin */
	BUTTON_init(PEDESTRIANS_BUTTON_PIN,PEDESTRIANS_BUTTON_PORT);
	/* Interrupt 0 Sense Control => Rising Edge */
	MCUCR |= (1<<0) | (1<<1);
	/* Enable External Interrupt 0 */
	GICR |= (1<<6);
	
	/* Initialize Cars LEDs */
	LED_init(CAR_GREEN_LED_PIN, CAR_GREEN_LED_PORT);
	LED_init(CAR_YELLOW_LED_PIN, CAR_YELLOW_LED_PORT);
	LED_init(CAR_RED_LED_PIN, CAR_RED_LED_PORT);
	
	/* Initialize Pedestrian LEDs */
	LED_init(PEDESTRIANS_GREEN_LED_PIN, PEDESTRIANS_GREEN_LED_PORT);
	LED_init(PEDESTRIANS_YELLOW_LED_PIN, PEDESTRIANS_YELLOW_LED_PORT);
	LED_init(PEDESTRIANS_RED_LED_PIN, PEDESTRIANS_RED_LED_PORT);
	
}

/*
 * Description:
 *			function to start the application
 */
void APP_start(void)
{
	/* initialize all we need for the app to start functioning */
	APP_init();
	
	/* Variable to store LED state */
	carsLED_State state;
	
	while(1)
	{
		normalMode(&state);
		pedestrianMode(&state);
	}
}

/*
 * function IN:  carsLED_State * state : a refrence to a variable to store cars' light state
 * function OUT: Nothing
 *
 * Description:
 *			Normal Mode:
 *				1.Cars' LEDs will be changed every five seconds starting from Green then yellow then red then yellow then Green.
 *				2.The Yellow LED will blink for five seconds before moving to Green or Red LEDs.
 */
static void normalMode(carsLED_State * state)
{
	while(1)
	{
		/* store current cars' lights state */
		*state = GREEN;
		/* Turn on cars' green light for 5 seconds */
		turnOn_carsGreenlight();
		/* check if there's a pedestrian want to cross the road if there's one switch to pedestrian mode */
		if(g_pedestrianModeFlag == 1) break;
		
		
		/* store current cars' lights state */
		*state = YELLOW;
		/* Blink the cars' yellow light for 5 seconds */
		turnOn_carsYellowlight();
		/* check if there's a pedestrian want to cross the road if there's one switch to pedestrian mode */
		if(g_pedestrianModeFlag == 1) break;


		/* store current cars' lights state */
		*state = RED;
		/* Turn on cars' red light for 5 seconds */
		turnOn_carsRedlight();
		/* check if there's a pedestrian want to cross the road if there's one switch to pedestrian mode */
		if(g_pedestrianModeFlag == 1) break;
		
		
		/* store current cars' lights state */
		*state = YELLOW;
		/* Blink the cars' yellow light for 5 seconds */
		turnOn_carsYellowlight();
		/* check if there's a pedestrian want to cross the road if there's one switch to pedestrian mode */
		if(g_pedestrianModeFlag == 1) break;
		
	}
}


/*
 * function IN:  carsLED_State * state : a refrence to the car state variable to Load cars' light state
 * function OUT: Nothing
 *
 * Description:
 *			Pedestrian Mode:
 *				1.Change from normal mode to pedestrian mode when the pedestrian button is pressed.
 *				2.If pressed when the cars' Red LED is on, the pedestrian's Green LED and the cars' Red LEDs will be on for five seconds,
 *				  this means that pedestrians can cross the street while the pedestrian's Green LED is on.
 *				3.If pressed when the cars' Green LED is on or the cars' Yellow LED is blinking,
 *				  the pedestrian Red LED will be on then both Yellow LEDs start to blink for five seconds,
 *				  then the cars' Red LED and pedestrian Green LEDs are on for five seconds,
 *				  this means that pedestrian must wait until the Green LED is on.
 *				4.At the end of the two states, the cars' Red LED will be off and both Yellow LEDs start blinking for 5 seconds and the pedestrian's Green LED is still on.
 *				5.After the five seconds the pedestrian Green LED will be off and both the pedestrian Red LED and the cars' Green LED will be on.
 *				6.Traffic lights signals are going to the normal mode again.
 */
static void pedestrianMode(carsLED_State * state)
{
	/* clear pedestrian mode flag */
	g_pedestrianModeFlag = 0;
	/* set in progress flag to tell that pedestrian mode is activater */
	g_inProgressFlag = 1;
	
	/* check cars' lights state */
	switch(*state)
	{
		/* if the button pressed while cars' green light is on */
		case GREEN:
		
				/* Turn on pedestrians' Red light while cars' green light still on */
				turnOn_pedestrianRedWithCarsGreen();
				
				/* Blink the both yellow lights for 5 seconds */
				turnOn_bothYellowlights();

				/* the pedestrian's Green LED and the cars' Red LEDs will be on for five seconds */
				turnOn_pedestrianGreenWithCarsRed();
				/* & Do not turn off pedestrians' green light */
				
		break;
		
		/* if the button pressed while cars' yellow light is on */
		case YELLOW:
				/* Turn on pedestrians' Red light while cars' yellow light still blinking */
				turnOn_pedestrianRedWithCarsYellow();
				
				/* Blink the both yellow lights for 5 seconds */
				turnOn_bothYellowlights();

				/* the pedestrian's Green LED and the cars' Red LEDs will be on for five seconds */
				turnOn_pedestrianGreenWithCarsRed();
				/* & Do not turn off pedestrians' green light */
		
		break;
		
		/* if the button pressed while cars' red light is on */
		case RED:
				/* the pedestrian's Green LED and the cars' Red LEDs will be on for five seconds */
				turnOn_pedestrianGreenWithCarsRed();
				/* & Do not turn off pedestrians' green light */
				
		break;
	}
	
	/* Blink the both yellow lights for 5 seconds */
	turnOn_bothYellowlights();
	
	LED_off(PEDESTRIANS_GREEN_LED_PIN, PEDESTRIANS_GREEN_LED_PORT);
	
	/* Turn on cars' green light & pedestrians' Red light */
	turnOn_pedestrianRedWithCarsGreen();
	
	
	/* clear in progress flag */
	g_inProgressFlag = 0;
}



/*
 * Description:
 *			function to turn on cars' green light for 5s 
 */
static void turnOn_carsGreenlight(void)
{
	/* Turn on cars' green light for 5 seconds */
	LED_on(CAR_GREEN_LED_PIN, CAR_GREEN_LED_PORT);
	delaySeconds(SWITCHING_DELAY);
	LED_off(CAR_GREEN_LED_PIN, CAR_GREEN_LED_PORT);
	if(g_pedestrianModeFlag == 1) return;
}

/*
 * Description:
 *			function to turn on cars' yellow light for 5s 
 */
static void turnOn_carsYellowlight(void)
{
	uint8_t i;
	/* Blink the cars' yellow light for 5 seconds */
	for(i=0;i<5;i++)
	{
		LED_on(CAR_YELLOW_LED_PIN, CAR_YELLOW_LED_PORT);
		delayHalfSeconds(1);
		LED_off(CAR_YELLOW_LED_PIN, CAR_YELLOW_LED_PORT);
		delayHalfSeconds(1);
		if(g_pedestrianModeFlag == 1) return;
	}
	
}

/*
 * Description:
 *			function to turn on cars' red light for 5s 
 */
static void turnOn_carsRedlight(void)
{
	/* Turn on cars' red light for 5 seconds */
	LED_on(CAR_RED_LED_PIN, CAR_RED_LED_PORT);
	delaySeconds(SWITCHING_DELAY);
	LED_off(CAR_RED_LED_PIN, CAR_RED_LED_PORT);
	if(g_pedestrianModeFlag == 1) return;
}

/*
 * Description:
 *			function to Turn on pedestrians' Red light while cars' green light still on
 */
static void turnOn_pedestrianRedWithCarsGreen(void)
{
	/* Turn on pedestrians' Red light while cars' green light still on */
	LED_on(PEDESTRIANS_RED_LED_PIN, PEDESTRIANS_RED_LED_PORT);
	LED_on(CAR_GREEN_LED_PIN, CAR_GREEN_LED_PORT);
	delaySeconds(SWITCHING_DELAY);
	LED_off(CAR_GREEN_LED_PIN, CAR_GREEN_LED_PORT);
	LED_off(PEDESTRIANS_RED_LED_PIN, PEDESTRIANS_RED_LED_PORT);
}

/*
 * Description:
 *			function to Turn on pedestrians' Red light while cars' yellow light still blinking
 */
static void turnOn_pedestrianRedWithCarsYellow(void)
{
	uint8_t i;
	/* Turn on pedestrians' Red light while cars' yellow light still blinking */
	LED_on(PEDESTRIANS_RED_LED_PIN, PEDESTRIANS_RED_LED_PORT);
	for(i=0;i<5;i++)
	{
		LED_on(CAR_YELLOW_LED_PIN, CAR_YELLOW_LED_PORT);
		delayHalfSeconds(1);
		LED_off(CAR_YELLOW_LED_PIN, CAR_YELLOW_LED_PORT);
		delayHalfSeconds(1);
	}
	LED_off(PEDESTRIANS_RED_LED_PIN, PEDESTRIANS_RED_LED_PORT);
}

/*
 * Description:
 *			function to Blink the both yellow lights for 5 seconds
 */
static void turnOn_bothYellowlights(void)
{
	uint8_t i;
	/* Blink the both yellow lights for 5 seconds */
	for(i=0;i<5;i++)
	{
		LED_on(PEDESTRIANS_YELLOW_LED_PIN, PEDESTRIANS_YELLOW_LED_PORT);
		LED_on(CAR_YELLOW_LED_PIN, CAR_YELLOW_LED_PORT);
		delayHalfSeconds(1);
		LED_off(PEDESTRIANS_YELLOW_LED_PIN, PEDESTRIANS_YELLOW_LED_PORT);
		LED_off(CAR_YELLOW_LED_PIN, CAR_YELLOW_LED_PORT);
		delayHalfSeconds(1);
	}
	
}

/*
 * Description:
 *			function to the pedestrian's Green LED and the cars' Red LED will be on for five seconds and keep pedestrian's Green LED ON
 */
static void turnOn_pedestrianGreenWithCarsRed(void)
{
	/* the pedestrian's Green LED and the cars' Red LED will be on for five seconds */
	LED_on(CAR_RED_LED_PIN, CAR_RED_LED_PORT);
	LED_on(PEDESTRIANS_GREEN_LED_PIN, PEDESTRIANS_GREEN_LED_PORT);
	delaySeconds(SWITCHING_DELAY);
	LED_off(CAR_RED_LED_PIN, CAR_RED_LED_PORT);
	/* Do not turn off pedestrians' green light */
}

/*
 * Description:
 *			the function that we will set as a callback to the timer to count number of overflows
 */
static void countOverFlows(void)
{
	g_overFlows++;
}

/*
 * function IN:  uint8_t sec : the number of seconds that you want the delay to be
 * function OUT: Nothing
 *
 * Description:
 *			function to delay the given number of seconds
 */
static void delaySeconds(uint8_t sec)
{
	/* Timer configuration structure */
	/* According to calculations if we use 1024 pre-scaler the Initial value will be 12 and for 1s we need 4 OVFs */
	TIMER_config timer_configuration = {NORMAL_MODE,T0_F_CPU_1024,12,0};
		
	/* Initialize the Timer */
	TIMER_init(&timer_configuration);
	
	/* Set call back function to count the over flows */
	TIMER_setCallBack(countOverFlows);
	
	/* Start the timer */
	TIMER_start(&timer_configuration);
	
	/* wait till we reach the required Number of Seconds
	 * for each second we need 4 Over Flows */
	while(g_overFlows < (sec*4))
	{
		if(g_pedestrianModeFlag == 1) break;
	}
	
	/* Stop the timer */
	TIMER_stop();
	
	/* reset the number of over flow for the next use */
	g_overFlows = 0;
}

/*
 * function IN:  uint8_t halfSec : the number of half seconds that you want the delay to be
 * function OUT: Nothing
 *
 * Description:
 *			function to delay the given number of half seconds
 */
static void delayHalfSeconds(uint8_t halfSec)
{
	/* Timer configuration structure */
	/* According to calculations if we use 1024 pre-scaler the Initial value will be 12 and for 1s we need 4 OVFs */
	TIMER_config timer_configuration = {NORMAL_MODE,T0_F_CPU_1024,12,0};
		
	/* Initialize the Timer */
	TIMER_init(&timer_configuration);
	
	/* Set call back function to count the over flows */
	TIMER_setCallBack(countOverFlows);
	
	/* Start the timer */
	TIMER_start(&timer_configuration);
	
	/* wait till we reach the required Number of Seconds
	 * for half a second we need 2 Over Flows */
	while(g_overFlows < (halfSec*2))
	{
		if(g_pedestrianModeFlag == 1) break;
	}
	
	/* Stop the timer */
	TIMER_stop();
	
	/* reset the number of over flow for the next use */
	g_overFlows = 0;
}