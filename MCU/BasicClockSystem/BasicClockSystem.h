/*****************************************************************************/
//	BasicClockSystem.h
//  
//	 Created on: Jan 3, 2015
//	     Author: Clint Stevenson
//
/*****************************************************************************/


#ifndef BASIC_CLOCK_SYSTEM_H_
#define BASIC_CLOCK_SYSTEM_H_


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
//	Struct Overlay Declarations for Peripheral Register Access
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*	BasicClockSystem Struct Type Defines for Struct Overlays				 */
/*                                                                           */
/*****************************************************************************/
#if defined (__MSP430_HAS_BC2__)
// (refer to MSP430x5xx Family User's Guide)
typedef struct {
	uint8_t BCSCTL3;
	uint8_t _DNU[2];
	uint8_t DCOCTL1;
	uint8_t BCSCTL1;
	uint8_t BCSCTL2;
} BCS_Control_t;

typedef struct {
	uint8_t interrupt_enable;
	uint8_t _DNU;
	uint8_t interrupt_flag;
} BCS_Interrupts_t;
#endif // defined (__MSP430_HAS_BC2__)
/*****************************************************************************/
/*                                                                           */
/*	END: BasicClockSystem Struct Type Defines for Struct Overlays			 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
//	End Public Typedef Declarations


/*****************************************************************************/
//	Constant Struct Overlay Declarations
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*	BasicClockSystem Struct Overlay Declaration 							 */
/*                                                                           */
/*****************************************************************************/
// Declare pointer to struct overlay for the BasicClockSystem peripheral
extern BCS_Control_t volatile * const p_BCS_CONTROL;
#define BCS_CONTROL		(*p_BCS_CONTROL)

extern BCS_Interrupts_t volatile * const p_BCS_INTERRUPTS;
#define BCS_INTERRUPTS		(*p_BCS_INTERRUPTS)
/*****************************************************************************/
/*                                                                           */
/*	END: BasicClockSystem Struct Overlay Declaration						 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
//	END: Struct Overlay Declarations for Peripheral Register Access


/*****************************************************************************/
//	Macro Definitions
/*****************************************************************************/
// BasicClockSystem register manipulation macros
// DCOCTL1 Register Manipulation Macros
#define BCS_ClearDCOFreqSelect			(BCS_CONTROL.DCOCTL &= ~(DCO2 | DCO1 | DCO0))
#define BCS_SetDCOFreqSelect(a)			{BCS_ClearDCOFreqSelect; \
										 BCS_CONTROL.DCOCTL |= (a & (DCO2 | DCO1 | DCO0))}
#define BCS_ClearDCOModSelect			(BCS_CONTROL.DCOCTL &= ~(MOD4 | MOD3 | MOD2 | MOD1 | MOD0))
#define BCS_SetDCOModSelect(a)			{BCS_ClearDCOModSelect; \
										 BCS_CONTROL.DCOCTL |= (a & (MOD4 | MOD3 | MOD2 | MOD1 | MOD0))}

// BCSCTL1 Register Manipulation Macros
#define BCS_ClearDCORangeSelect			(BCS_CONTROL.BCSCTL1 &= ~(RSEL3 | RSEL2 | RSEL1 | RSEL0))
#define BCS_SetDCORangeSelect(a)		{BCS_ClearDCORangeSelect; \
										 BCS_CONTROL.BCSCTL1 |= (a & (RSEL3 | RSEL2 | RSEL1 | RSEL0))}
#define BCS_ClearACLKDivider			(BCS_CONTROL.BCSCTL1 &= ~(DIVA1 | DIVA0))
#define BCS_SetACLKDivider(a)			{BCS_ClearACLKDivider; \
										 BCS_CONTROL.BCSCTL1 |= (a & (DIVA1 | DIVA0))}
#if !defined(__MSP430G2553)
// Not supported on select devices. Refer to family user guide.
#define BCS_XT2Off						(BCS_CONTROL.BCSCTL1 |= XT2OFF)
#define BCS_XT2On						(BCS_CONTROL.BCSCTL1 &= ~XT2OFF)
#define BCS_SetLFXT1asLowFreq			(BCS_CONTROL.BCSCTL1 &= ~XTS)
#define BCS_SetLFXT1asHighFreq			(BCS_CONTROL.BCSCTL1 |= XTS)
#endif /* !defined(__MSP430G2553) */

// BCSCTL2 Register Manipulation Macros
#define BCS_ClearMCLKSourceSelect		(BCS_CONTROL.BCSCTL2 &= ~(SELM1 | SELM0))
#define BCS_SetMCLKSourceSelect(a)		{BCS_ClearMCLKSourceSelect; \
										 BCS_CONTROL.BCSCTL2 |= (a & (SELM1 | SELM0))}
#define BCS_ClearMCLKDivider			(BCS_CONTROL.BCSCTL2 &= ~(DIVM1 | DIVM0))
#define BCS_SetMCLKDivider(a)			{BCS_ClearMCLKDivider; \
										 BCS_CONTROL.BCSCTL2 |= (a & (DIVM1 | DIVM0))}
#define BCS_SelectMCLK					(BCS_CONTROL.BCSCTL2 &= ~SELS)

#if !defined(__MSP430G2553)
// Not supported on select devices. Refer to family user guide.
#define BCS_SelectXT2CLK				(BCS_CONTROL.BCSCTL2 |= SELS)
#endif /* !defined(__MSP430G2553) */

#define BCS_ClearSMCLKDivider			(BCS_CONTROL.BCSCTL2 &= ~(DIVS1 | DIVS0))
#define BCS_SetSMCLKDivider(a)			{BCS_ClearSMCLKDivider; \
										 BCS_CONTROL.BCSCTL2 |= (a & (DIVS1 | DIVS0))}
#define BCS_SelectInternalDCOResistor	(BCS_CONTROL.BCSCTL2 &= ~DCOR)
#define BCS_SelectExternalDCOResistor	(BCS_CONTROL.BCSCTL2 |= DCOR)

// BCSCTL3 Register Manipulation Macros
#define BCS_ClearXT2RangeSelect			(BCS_CONTROL.BCSCTL3 &= ~(XT2S1 | XT2S0))
#define BCS_SetXT2RangeSelect(a)		{BCS_ClearXT2RangeSelect; \
										 BCS_CONTROL.BCSCTL3 |= (a & (XT2S1 | XT2S0))}

#define BCS_ClearLowFreqClockSelect		(BCS_CONTROL.BCSCTL3 &= ~(LFXT1S1 | LFXT1S0))
#if defined (__MSP430G2553)
#define BCS_LFXT1as32768				(BCS_ClearLowFreqClockSelect)
#define BCS_LFXT1asVLOCLK				{BCS_ClearLowFreqClockSelect; \
										 BCS_CONTROL.BCSCTL3 |= LFXT1S1}
#define BCS_LFXT1asDigitalExternal		{BCS_ClearXT2RangeSelect; \
										 BCS_CONTROL.BCSCTL3 |= (LFXT1S1 | LFXT1S1)}

#elif defined (__MSP430AFE253)
#define BCS_LFXT1asVLOCLK				{BCS_ClearXT2RangeSelect; \
										 BCS_CONTROL.BCSCTL3 |= LFXT1S1}
#endif /* Device selection */
#define BCS_ClearOscCapSelect			(BCS_CONTROL.BCSCTL3 &= ~(XCAP1 | XCAP0))
#define BCS_OscCapSelect1pF				(BCS_ClearOscCapSelect)
#define BCS_OscCapSelect6pF				{BCS_ClearOscCapSelect; \
										 BCS_CONTROL.BCSCTL3 |= XCAP0}
#define BCS_OscCapSelect10pF			{BCS_ClearOscCapSelect; \
										 BCS_CONTROL.BCSCTL3 |= XCAP1}
#define BCS_OscCapSelect12pF			{BCS_ClearOscCapSelect; \
										 BCS_CONTROL.BCSCTL3 |= XCAP1 | XCAP0}
#define BCS_GetXT2OscFault				(BCS_CONTROL.BCSCTL3 & XT2OF)
#define BCS_GetLFXT1OscFault			(BCS_CONTROL.BCSCTL2 & LFXT1OF)

// BCS Interrupt Enable Register Manipulation Macros
#define BCS_EnableOscFaultInterrupt		(BCS_INTERRUPTS.interrupt_enable |= OFIE)
#define BCS_DisableOscFaultInterrupt	(BCS_INTERRUPTS.interrupt_enable &= ~OFIE)

// BCS Interrupt Flag Register Manipulation Macros
#define BCS_SetOscFaultFlag				(BCS_INTERRUPTS.interrupt_enable |= OFIFG)
#define BCS_ClearOscFaultFlag			(BCS_INTERRUPTS.interrupt_enable &= ~OFIFG)
/*****************************************************************************/
//	END: Macro Definitions
/*****************************************************************************/


//	Public Function Prototypes (extern)
/*****************************************************************************/
//Put public function prototypes here
void BCS_init (void);
/*****************************************************************************/
//	End Public Function Prototypes


#endif /* BASIC_CLOCK_SYSTEM_H_ */
