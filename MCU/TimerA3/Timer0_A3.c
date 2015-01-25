/******************************************************************************/
//	Timer0_A3.c
//  
//	 Created on: Dec 15, 2014
//	     Author: Clint Stevenson
//
/******************************************************************************/


/******************************************************************************/
//	Includes
/******************************************************************************/
#include <Timer0_A3.h>
#include <callback.h>
/******************************************************************************/
//	End Includes


/******************************************************************************/
//	Defines
/******************************************************************************/
//Put defines here
/******************************************************************************/
/*                                                                            */
/*	Base address and bit definitions needed by Timer0_A3 peripherals		  */
/*                                                                            */
/******************************************************************************/
#if defined (__MSP430_HAS_TA3__)
#if defined (__MSP430G2553)
#define TIMER0_A3_PERIPHERAL_BASE_ADDRESS								(0x0160)

#endif /* Device selection */
#endif /* defined (__MSP430_HAS_TA3__) */
/******************************************************************************/
/*                                                                            */
/*	END: Base address and bit definitions needed by Timer0_A3 peripherals	  */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                                                                            */
/*	Timer0_A3																  */
/*                                                                            */
/******************************************************************************/
#if defined (__MSP430_HAS_TA3__)
// Timer0_A3 peripheral control register address offsets
#define TIMER0_A3_CONTROL_REGISTER_ADDRESS_OFFSET						(0x0000)
#define TIMER0_A3_CC0_CONTROL_REGISTER_ADDRESS_OFFSET					(0x0002)
#define TIMER0_A3_CC1_CONTROL_REGISTER_ADDRESS_OFFSET					(0x0004)
#define TIMER0_A3_CC2_CONTROL_REGISTER_ADDRESS_OFFSET					(0x0006)
#define TIMER0_A3_COUNTER_REGISTER_ADDRESS_OFFSET						(0x0010)
#define TIMER0_A3_CC0_REGISTER_ADDRESS_OFFSET							(0x0012)
#define TIMER0_A3_CC1_REGISTER_ADDRESS_OFFSET							(0x0014)
#define TIMER0_A3_CC2_REGISTER_ADDRESS_OFFSET							(0x0016)

#endif /* __MSP430_HAS_TA3__ */
/******************************************************************************/
/*                                                                            */
/*	END: Timer0_A3															  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
//	End Defines


/******************************************************************************/
//	Constant Struct Overlay Declarations
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*	Timer0_A3 Struct Overlay Declaration 									  */
/*                                                                            */
/******************************************************************************/
#if defined (__MSP430_HAS_TA3__)
// Peripheral Control
// Declare pointer to struct overlay for the Timer0_A3 peripheral
Timer0_A3_t volatile * const p_TIMER0_A3 =
		(Timer0_A3_t *) TIMER0_A3_PERIPHERAL_BASE_ADDRESS;

#endif /* defined (__MSP430_HAS_TA3__) */
/******************************************************************************/
/*                                                                            */
/*	END: Timer0_A3 Struct Overlay Declaration								  */
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
#define NUM_CALLBACKS				(4)
functionPointer_t timer0_A3_callback[NUM_CALLBACKS];
uint8_t timer0_A3_LPM_bits[NUM_CALLBACKS];
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
void Timer0_A3_init (void)
{
	// Don't use TACLR bit, as it basically resets the entire timer peripheral
	TA0CTL = TASSEL_1;			// Clk = ACLK/1
	TA0CCR0 = 32767;			// Initialize compare register
	TA0CCTL0 |= CCIE;			// Enable compare interrupt
}


void Timer0_A3_armOneShot (uint16_t timerTicks, uint8_t outputVal)
{
	// Don't use TACLR bit, as it basically resets the entire timer peripheral
	TA0CCR1 = timerTicks;				// Set compare register
	TAR = 0;

	if (1 == outputVal)					// If output pulse value should be hi
	{
		TA0CCTL1 = OUT;
		TA0CCTL1 |= OUTMOD_5 | CCIE;
	}

	else if (0 == outputVal)			// If output pulse value should be lo
	{
		TA0CCTL1 &= OUTMOD_1;			// Set mode to 'Set'
		TA0CCTL1 &= ~OUT;				// Set OUT lo
	}
}


void Timer0_A3_registerCallback (uint8_t index, functionPointer_t fPtr, uint8_t LPM_bits)
{
	timer0_A3_callback[index] = fPtr;
	timer0_A3_LPM_bits[index] = LPM_bits;
}


#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR (void)
{
	volatile uint16_t idx = TA0IV >> 1;	// Divide by two

	// TA0CCR1, TA0CCR2 and TA0OVF are possible sources for this ISR
	if(timer0_A3_callback[idx] != 0)
	{
		timer0_A3_callback[idx]();	// TA0IV will only ever be even
	}

	__bic_SR_register_on_exit(timer0_A3_LPM_bits[idx]);
}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
	// TA0CCR0 is the single source for this ISR
	if(timer0_A3_callback[TA0CC0] != 0)
	{
		timer0_A3_callback[TA0CC0]();
	}

	__bic_SR_register_on_exit(timer0_A3_LPM_bits[TA0CC0]);
}
/******************************************************************************/
//	End Function Definitions
