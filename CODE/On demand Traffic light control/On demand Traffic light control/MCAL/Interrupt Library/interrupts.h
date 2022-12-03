/*
 * interrupts.h
 *
 * Created: 29/11/2022 22:24:49
 *  Author: Ashraf
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_


/************************************************************************/
/*                      MACRO Defines The ISR                           */
/************************************************************************/

#define ISR(INT_VECT)			void INT_VECT(void) __attribute__ ((signal,used));\
								void INT_VECT(void)

/* Set Global Interrupt Enable bit */
#define sei()					__asm__ __volatile__ ("sei" ::: "memory")

/* Clear Global Interrupt Enable bit */
#define cli()					__asm__ __volatile__ ("cli" ::: "memory")

/************************************************************************/
/*                             Vectors                                  */
/************************************************************************/


/* External Interrupt Request 0 */
#define EXT_INT_0				__vector_1

/* External Interrupt Request 1 */
#define EXT_INT_1				__vector_2

/* External Interrupt Request 2 */
#define EXT_INT_2				__vector_3

/* Timer0 Compare Match interrupt request */
#define TIMER0_COMP				__vector_10

/* Timer0 over flow interrupt request */
#define TIMER0_OVF				__vector_11





#endif /* INTERRUPTS_H_ */