/******************************************************************************/
//	ADC10.c
//  
//	 Created on: Jan 16, 2015
//	     Author: Clint Stevenson
//
/******************************************************************************/


/******************************************************************************/
//	Includes
/******************************************************************************/
#include <ADC10.h>
#include <callback.h>
/******************************************************************************/
//	End Includes


/******************************************************************************/
//	Defines
/******************************************************************************/
//Put defines here
/******************************************************************************/
/*                                                                            */
/*	Base address and bit definitions needed by ADC10 peripherals			  */
/*                                                                            */
/******************************************************************************/
#if defined (__MSP430_HAS_ADC10__)
#if defined (__MSP430G2553)
#define ADC10_PERIPHERAL_BASE_ADDRESS									(0x0048)

#endif /* Device selection */
#endif /* defined (__MSP430_HAS_ADC10__) */
/******************************************************************************/
/*                                                                            */
/*	END: Base address and bit definitions needed by ADC10 peripherals		  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
//	End Defines


/******************************************************************************/
//	Constant Struct Overlay Declarations
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*	ADC10 Struct Overlay Declaration 										  */
/*                                                                            */
/******************************************************************************/
#if defined (__MSP430_HAS_ADC10__)
// Peripheral Control
// Declare pointer to struct overlay for the Timer0_A3 peripheral
ADC10_t volatile * const p_ADC10 =
		(ADC10_t *) ADC10_PERIPHERAL_BASE_ADDRESS;

#endif /* defined (__MSP430_HAS_ADC10__) */
/******************************************************************************/
/*                                                                            */
/*	END: ADC10 Struct Overlay Declaration									  */
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
functionPointer_t ADC10_callback;
uint8_t ADC10_LPM_bits;
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
void ADC10_init (void)
{
	ADC10_SetClockDivider(ADC10DIV_7);		// Set Clock divider to divide by 1
	ADC10_SetClockSource(ADC10SSEL_3);		// Set Clock source to use SMCLK (SSEL3)
	ADC10_SetSampleAndHoldSource(SHS_0);	// Set sample-and-hold input source to use ADC10SC bit
	ADC10_SetSamplingRateRefBuf;			// Set to reduced conversion rate for power savings
	ADC10_On;								// Turn on ADC10 peripheral
}


void ADC10_registerCallback (functionPointer_t fPtr, uint8_t LPM_bits)
{
	ADC10_callback = fPtr;
	ADC10_LPM_bits = LPM_bits;
}


#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
	if(ADC10_callback != 0)
	{
		ADC10_callback();
	}

	__bic_SR_register_on_exit(ADC10_LPM_bits);
}
/******************************************************************************/
//	End Function Definitions
