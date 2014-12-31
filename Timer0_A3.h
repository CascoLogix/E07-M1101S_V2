/*****************************************************************************/
//	Timer0_A3.h
//  
//	 Created on: Dec 15, 2014
//	     Author: Clint Stevenson
//
/*****************************************************************************/


#ifndef TIMER0_A3_H_
#define TIMER0_A3_H_


/*****************************************************************************/
//	Includes
/*****************************************************************************/
//Put conditional includes here
#include <msp430.h>
#include <stdint.h>
#include <callback.h>
/*****************************************************************************/
//	End Includes


/*****************************************************************************/
//	Defines
/*****************************************************************************/
//Put defines here
/*****************************************************************************/
//	End Defines


/*****************************************************************************/
//	Public Constant Declarations (extern)
/*****************************************************************************/
//Put public variable declarations here
/*****************************************************************************/
//	End Public Constant Declarations


/*****************************************************************************/
//	Public Variable Declarations (extern)
/*****************************************************************************/
//Put public variable declarations here
/*****************************************************************************/
//	End Public Variable Declarations


/*****************************************************************************/
//	Public Typedef Declarations (extern)
/*****************************************************************************/
//Put public typedef declarations here
/*****************************************************************************/
//	End Public Typedef Declarations


/*****************************************************************************/
//	Public Function Prototypes (extern)
/*****************************************************************************/
//Put public function prototypes here
void Timer0_init (void);
void Timer0_armOneShot (uint16_t timerTicks, uint8_t outputVal);
void Timer0_A1_registerCallback (uint8_t index, functionPointer_t fPtr, uint8_t LPM_bits);
void Timer0_A0_registerCallback (functionPointer_t fPtr, uint8_t LPM_bits);
/*****************************************************************************/
//	End Public Function Prototypes


#endif /* TIMER0_A3_H_ */
