/*
 * bit_manipulation.h
 *
 * Created: 28/11/2022 21:45:53
 *  Author: Ashraf
 */ 


#ifndef BIT_MANIPULATION_H_
#define BIT_MANIPULATION_H_

/* Set a certain bit in any register */

#define SET_BIT(REG,BIT) (REG |= (1<<BIT))

/* Clear a certain bit in any register */

#define CLEAR_BIT(REG,BIT) (REG &= (~(1<<BIT)))

/* Toggle a certain bit in any register */

#define TOGGLE_BIT(REG,BIT) (REG ^= (1<<BIT))

/* Rotate right the register value with specific number of rotates */

#define ROR(REG,NUM) (REG = (REG>>NUM) | (REG<<(sizeof(REG)-NUM)))

/* Rotate left the register value with specific number of rotates */

#define ROL(REG,NUM) (REG = (REG<<NUM) | (REG>>(sizeof(REG)-NUM)))

/* Check if a specific bit is set in any register and return true if yes */

#define BIT_IS_SET(REG,BIT) (REG & (1<<BIT))

/* Check if a specific bit is cleared in any register and return true if yes */

#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))

/* Get a value of a certain bit */

#define GET_BIT(REG,BIT) (((REG)>>(BIT)) & 1)



#endif /* BIT_MANIPULATION_H_ */