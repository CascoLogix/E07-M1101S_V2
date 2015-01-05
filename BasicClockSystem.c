/******************************************************************************/
//	BasicClockSystem.c
//  
//	 Created on: Jan 3, 2015
//	     Author: Clint Stevenson
//
/******************************************************************************/


/******************************************************************************/
//	Includes
/******************************************************************************/
#include <BasicClockSystem.h>
#include <callback.h>
/******************************************************************************/
//	End Includes


/******************************************************************************/
//	Defines
/******************************************************************************/
//Put defines here
/******************************************************************************/
/*                                                                            */
/*	Base address and bit definitions needed by BasicClockSystem peripherals	  */
/*                                                                            */
/******************************************************************************/
#if defined (__MSP430_HAS_BC2__)
#if defined (__MSP430G2553)
#define BCS_PERIPHERAL_CONTROL_BASE_ADDRESS								(0x0053)
#define BCS_PERIPHERAL_INTERRUPTS_BASE_ADDRESS							(0x0000)

#endif /* Device selection */
#endif /* defined (__MSP430_HAS_BC2__) */
/******************************************************************************/
/*                                                                            */
/*	END: Base address and bit definitions needed by BasicClockSystem		  */
/*       peripherals														  */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                                                                            */
/*	BasicClockSystem														  */
/*                                                                            */
/******************************************************************************/
#if defined (__MSP430_HAS_BC2__)
// BasicClockSystem peripheral control register address offsets
#if defined (__MSP430G2553)
#define BCS_CONTROL_REGISTER_ADDRESS_OFFSET								(0x0000)

#endif /* Device selection */
#endif /* __MSP430_HAS_BC2__ */
/******************************************************************************/
/*                                                                            */
/*	END: BasicClockSystem													  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
//	End Defines


/******************************************************************************/
//	Constant Struct Overlay Declarations
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*	BasicClockSystem Struct Overlay Declaration 							  */
/*                                                                            */
/******************************************************************************/
#if defined (__MSP430_HAS_BC2__)
// Peripheral Control
// Declare pointer to struct overlay for the Timer0_A3 peripheral
BCS_Control_t volatile * const p_BCS_CONTROL =
		(BCS_Control_t *) BCS_PERIPHERAL_CONTROL_BASE_ADDRESS;

BCS_Interrupts_t volatile * const p_BCS_INTERRUPTS =
		(BCS_Interrupts_t *) BCS_PERIPHERAL_INTERRUPTS_BASE_ADDRESS;
#endif /* defined (__MSP430_HAS_BC2__) */
/******************************************************************************/
/*                                                                            */
/*	END: BasicClockSystem Struct Overlay Declaration						  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
//	END: Struct Overlay Declarations for Peripheral Register Access


/******************************************************************************/
//	Constant Declarations
/******************************************************************************/
//Put Constant Declarations here
/******************************************************************************/
//	End Constant Declarations


/******************************************************************************/
//	Variable Declarations
/******************************************************************************/
//Put Variable Declarations here
functionPointer_t BCS_callback;
uint8_t BCS_LPM_bits;
/******************************************************************************/
//	End Variable Declarations


/******************************************************************************/
//	Function Prototypes
/******************************************************************************/
//Put function prototypes here
/******************************************************************************/
//	End Function Prototypes


/******************************************************************************/
//	Function Definitions
/******************************************************************************/
//Put function definitions here
void BCS_init (void)
{
	P2DIR |= BIT7;
	P2SEL |= BIT7 | BIT6;
}


void BCS_function (uint16_t param1, uint8_t param2)
{

}

// TODO: Move to NMI handler file, since multiple sources can cause NMI.
#pragma vector = NMI_VECTOR
__interrupt void NMI_ISR (void)
{
	if(BCS_callback != 0)
	{
		BCS_callback();
	}

	__bic_SR_register_on_exit(BCS_LPM_bits);
}
/******************************************************************************/
//	End Function Definitions
