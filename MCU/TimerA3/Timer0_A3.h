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
#include <GPIO.h>		// Dependent on GPIO for setting port settings for USCI
/*****************************************************************************/
//	End Includes


/*****************************************************************************/
//	Defines
/*****************************************************************************/
//Put defines here
#define TA0CC0						(0)
#define TA0CC1						(1)
#define TA0CC2						(2)
#define TA0OVF						(3)
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
//	Struct Overlay Declarations for Peripheral Register Access
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*	Timer0_A3 Struct Type Defines for Struct Overlays						 */
/*                                                                           */
/*****************************************************************************/
#if defined (__MSP430_HAS_TA3__)
// (refer to MSP430x5xx Family User's Guide)
typedef struct {
	uint16_t control;
	uint16_t CC_control[3];
	const uint16_t _DNU2[4];
	uint16_t count;
	uint16_t CCR[3];
} Timer0_A3_t;
#endif // defined (__MSP430_HAS_TA3__)
/*****************************************************************************/
/*                                                                           */
/*	END: Timer0_A3 Struct Type Defines for Struct Overlays					 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
//	End Public Typedef Declarations


/*****************************************************************************/
//	Constant Struct Overlay Declarations
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*	Timer0_A3 Struct Overlay Declaration 									 */
/*                                                                           */
/*****************************************************************************/
// Declare pointer to struct overlay for the USCI_B0 peripheral
extern Timer0_A3_t volatile * const p_TIMER0_A3;
#define TIMER0_A3		(*p_TIMER0_A3)
/*****************************************************************************/
/*                                                                           */
/*	END: Timer0_A3 Struct Overlay Declaration								 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
//	END: Struct Overlay Declarations for Peripheral Register Access


/*****************************************************************************/
//	Macro Definitions
/*****************************************************************************/
// Timer0_A3 Control register manipulation macros
#define TIMER0_A3_ResetAll		 				(TIMER0_A3.control |= TACLR)
#define TIMER0_A3_EnableOverflowInterrupt 		(TIMER0_A3.control |= TAIE)
#define TIMER0_A3_DisableOverflowInterrupt	 	(TIMER0_A3.control &= ~TAIE)
#define TIMER0_A3_GetOverflowInterruptFlag 		(TIMER0_A3.control & TAIFG)
#define TIMER0_A3_ClearOverflowInterruptFlag 	(TIMER0_A3.control &= ~TAIFG)
#define TIMER0_A3_SetOverflowInterruptFlag 		(TIMER0_A3.control |= TAIFG)
#define TIMER0_A3_ClearClockSourceSelect 		(TIMER0_A3.control &= ~(TASSEL1 | TASSEL0))
#define TIMER0_A3_ClockSourceSelect(a) 			(TIMER0_A3_ClearClockSourceSelect; \
												 TIMER0_A3.control |= (a & (TASSEL1 | TASSEL0)))
#define TIMER0_A3_Stop				 			(TIMER0_A3.control &= ~(MC1 | MC0))
#define TIMER0_A3_SetCountMode(a) 				{TIMER0_A3_Stop; \
												TIMER0_A3.control |= (a & (MC1 | MC0));}
#define TIMER0_A3_SetDivider(a) 				{TIMER0_A3_ClearDivider; \
												 TIMER0_A3.control |= (a & (ID1 | ID0));}
#define TIMER0_A3_ClearDivider				 	(TIMER0_A3.control &= ~(ID1 | ID0))

// Timer0_A3 Counter register manipulation macros
#define TIMER0_A3_ClearCounter					(TIMER0_A3.count = 0)
#define TIMER0_A3_SetCounter(a)					(TIMER0_A3.count = a)
#define TIMER0_A3_GetCounter					(TIMER0_A3.count)

// Timer0_A3 Capture/Compare register manipulation macros
#define TIMER0_A3_SetCaptureCompare(a,b) 		(TIMER0_A3.CCR[a] = b)

// Timer0_A3 Capture/Compare control register manipulation macros
#define TIMER0_A3_ClearCaptureEdgeSelect(a)	 	(TIMER0_A3.CC_control[a] &= ~(CM1 | CM0))
#define TIMER0_A3_SetCaptureEdgeSelect(a) 		{TIMER0_A3_ClearCaptureMode(a); \
												 TIMER0_A3.CC_control[a] |= (a & (CM1 | CM0));}
#define TIMER0_A3_ClearCCInputSelect(a)	 		(TIMER0_A3.CC_control[a] &= ~(CCIS1 | CCIS0))
#define TIMER0_A3_SetCCInputSelect(a) 			{TIMER0_A3_ClearCCInputSelect(a); \
												 TIMER0_A3.CC_control[a] |= (a & (CCIS1 | CCIS0));}
#define TIMER0_A3_GetSyncCaptureSource(a)		(TIMER0_A3.CC_control[a] & SCS)
#define TIMER0_A3_ClearSyncCaptureSource(a)		(TIMER0_A3.CC_control[a] &= ~SCS)
#define TIMER0_A3_SetSyncCaptureSource(a) 		(TIMER0_A3.CC_control[a] |= SCS)
#define TIMER0_A3_GetSCCI(a) 					(TIMER0_A3.CC_control[a] & SCCI)
#define TIMER0_A3_GetCaptureMode(a)				(TIMER0_A3.CC_control[a] & CAP)
#define TIMER0_A3_SetCompareMode(a)				(TIMER0_A3.CC_control[a] &= ~CAP)
#define TIMER0_A3_SetCaptureMode(a) 			(TIMER0_A3.CC_control[a] |= CAP)
#define TIMER0_A3_ClearOutputMode(a)	 		(TIMER0_A3.CC_control[a] &= ~(OUTMOD2 | OUTMOD1 | OUTMOD0))
#define TIMER0_A3_SetOutputMode(a) 				{TIMER0_A3_ClearOutputMode(a); \
												 TIMER0_A3.CC_control[a] |= (a & (OUTMOD2 | OUTMOD1 | OUTMOD0));}
#define TIMER0_A3_EnableCCInterrupt(a) 			(TIMER0_A3.CC_control[a] |= CCIE)
#define TIMER0_A3_DisableCCInterrupt(a) 		(TIMER0_A3.CC_control[a] &= ~CCIE)
#define TIMER0_A3_GetCCInterruptFlag(a) 		(TIMER0_A3.CC_control[a] & CCIFG)
#define TIMER0_A3_ClearCCInterruptFlag(a)	 	(TIMER0_A3.CC_control[a] &= ~CCIFG)
#define TIMER0_A3_SetCCInterruptFlag(a) 		(TIMER0_A3.CC_control[a] |= CCIFG)
#define TIMER0_A3_GetCCInput(a)			 		(TIMER0_A3.CC_control[a] & CCI)
#define TIMER0_A3_GetCOVBit(a)			 		(TIMER0_A3.CC_control[a] & COV)
#define TIMER0_A3_ClearCOVBit(a)			 	(TIMER0_A3.CC_control[a] &= ~COV)
#define TIMER0_A3_GetOutput(a)					(TIMER0_A3.CC_control[a] & OUT)
#define TIMER0_A3_ClearOutput(a)				(TIMER0_A3.CC_control[a] &= ~OUT)
#define TIMER0_A3_SetOutput(a) 					(TIMER0_A3.CC_control[a] |= OUT)
/*****************************************************************************/
//	END: Macro Definitions
/*****************************************************************************/


//	Public Function Prototypes (extern)
/*****************************************************************************/
//Put public function prototypes here
void Timer0_A3_init (void);
void Timer0_A3_armOneShot (uint16_t timerTicks, uint8_t outputVal);
void Timer0_A3_registerCallback (uint8_t index, functionPointer_t fPtr, uint8_t LPM_bits);
/*****************************************************************************/
//	End Public Function Prototypes


#endif /* TIMER0_A3_H_ */
