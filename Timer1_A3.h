/*****************************************************************************/
//	Timer1_A3.h
//  
//	 Created on: Dec 15, 2014
//	     Author: Clint Stevenson
//
/*****************************************************************************/


#ifndef TIMER1_A3_H_
#define TIMER1_A3_H_


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
void Timer1_init (void);
void Timer1_armOneShot (uint16_t timerTicks, uint8_t outputVal);
void Timer1_A1_registerCallback (uint8_t index, functionPointer_t fPtr, uint8_t LPM_bits);
void Timer1_A0_registerCallback (functionPointer_t fPtr, uint8_t LPM_bits);
/*****************************************************************************/
//	End Public Function Prototypes


#endif /* TIMER1_A3_H_ */
