/******************************************************************************/
//	ADC10.h
//  
//	 Created on: Jan 16, 2015
//	     Author: Clint Stevenson
//
/******************************************************************************/


#ifndef ADC10_H_
#define ADC10_H_


/******************************************************************************/
//	Includes
/******************************************************************************/
//Put conditional includes here
#include <msp430.h>
#include <stdint.h>
#include <callback.h>
/******************************************************************************/
//	End Includes


/******************************************************************************/
//	Defines
/******************************************************************************/
//Put defines here
#define ADC10_CONTROL_REGISTER_ADDRESS_OFFSET							(0x0164)

#define ADC10_A0				(0x0000)
#define ADC10_A1				(0x1000)
#define ADC10_A2				(0x2000)
#define ADC10_A3				(0x3000)
#define ADC10_A4				(0x4000)
#define ADC10_A5				(0x5000)
#define ADC10_A6				(0x6000)
#define ADC10_A7				(0x7000)
#define ADC10_A8				(0x8000)
#define ADC10_A9				(0x9000)
#define ADC10_A10				(0xA000)
#define ADC10_A11				(0xB000)
#define ADC10_A12				(0xC000)
#define ADC10_A13				(0xD000)
#define ADC10_A14				(0xE000)
#define ADC10_A15				(0xF000)
#define ADC10_VREF_PLUS			(ADC10_A8)
#define ADC10_VREF_MINUS		(ADC10_A9)
#define ADC10_INTERNAL_TEMP		(ADC10_A10)
#define ADC10_VCC				(ADC10_A11)
/******************************************************************************/
//	End Defines


/******************************************************************************/
//	Public Constant Declarations (extern)
/******************************************************************************/
//Put public variable declarations here
/******************************************************************************/
//	End Public Constant Declarations


/******************************************************************************/
//	Public Variable Declarations (extern)
/******************************************************************************/
//Put public variable declarations here
/******************************************************************************/
//	End Public Variable Declarations


/******************************************************************************/
//	Public Typedef Declarations (extern)
/******************************************************************************/
//Put public typedef declarations here
/******************************************************************************/
//	Struct Overlay Declarations for Peripheral Register Access
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*	ADC10 Struct Type Defines for Struct Overlays							  */
/*                                                                            */
/******************************************************************************/
#if defined (__MSP430_HAS_ADC10__)
// (refer to MSP430x5xx Family User's Guide)
typedef struct {
	uint8_t dataTransferControl_0;
	uint8_t dataTransferControl_1;
	uint8_t inputEnable_0;
	uint8_t inputEnable_1;
	const uint8_t _DNU0[ADC10_CONTROL_REGISTER_ADDRESS_OFFSET];
	uint16_t control_0;
	uint16_t control_1;
	uint16_t memory;
	const uint16_t _DNU1[3];
	uint16_t dataTransferStartAddr;
} ADC10_t;
#endif // defined (__MSP430_HAS_ADC10__)
/******************************************************************************/
/*                                                                            */
/*	END: ADC10 Struct Type Defines for Struct Overlays						  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
//	End Public Typedef Declarations


/******************************************************************************/
//	Constant Struct Overlay Declarations
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*	ADC10 Struct Overlay Declaration 										  */
/*                                                                            */
/******************************************************************************/
// Declare pointer to struct overlay for the ADC10 peripheral
extern ADC10_t volatile * const p_ADC10;
#define ADC10		(*p_ADC10)
/******************************************************************************/
/*                                                                            */
/*	END: ADC10 Struct Overlay Declaration									  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
//	END: Struct Overlay Declarations for Peripheral Register Access


/******************************************************************************/
//	Macro Definitions
/******************************************************************************/
// ADC10 register manipulation macros
#define ADC10_ClearRef						(ADC10.control_0 &= ~(SREF2 | SREF1 | SREF0))
#define ADC10_SetRef						{ADC10_ClearRef; \
											ADC10.control_0 |= SREF0;}

#define ADC10_ClearSampleAndHold			(ADC10.control_0 &= ~(ADC10SHT1 | ADC10SHT0))
#define ADC10_SetSampleAndHold(a)			{ADC10_ClearSampleAndHold; \
											ADC10.control_0 |= (a & (ADC10SHT1 | ADC10SHT0));}

#define ADC10_ClearSamplingRateRefBuf		(ADC10.control_0 &= ~ADC10SR)
#define ADC10_SetSamplingRateRefBuf			(ADC10.control_0 |= ADC10SR)	// Reduces max sampling rate and lowers power consumption

#define ADC10_RefOutOff						(ADC10.control_0 &= ~REFOUT)REFBURST
#define ADC10_RefOutOn						(ADC10.control_0 |= REFOUT)

#define ADC10_RefBufOnContinuous			(ADC10.control_0 &= ~REFBURST)
#define ADC10_RefBufOnWhileSH				(ADC10.control_0 |= REFBURST)

#define ADC10_MultiSHOff					(ADC10.control_0 &= ~MSC)
#define ADC10_MultiSHOn						(ADC10.control_0 |= MSC)

#define ADC10_SetRefVoltage_1_5V			(ADC10.control_0 &= ~REF2_5V)
#define ADC10_SetRefVoltage_2_5V			(ADC10.control_0 |= REF2_5V)

#define ADC10_1_5VRefOutOn					(ADC10_RefOutOn)
#define ADC10_2_5VRefOutOn					{ADC10_SetRefVoltage_2_5V; \
											ADC10_RefOutOn;}

#define ADC10_RefGeneratorOff				(ADC10.control_0 &= ~REFON)
#define ADC10_RefGeneratorOn				(ADC10.control_0 |= REFON)

#define ADC10_Off							(ADC10.control_0 &= ~ADC10ON)
#define ADC10_On							(ADC10.control_0 |= ADC10ON)

#define ADC10_DisableInterrupt				(ADC10.control_0 &= ~ADC10IE)
#define ADC10_EnableInterrupt				(ADC10.control_0 |= ADC10IE)

#define ADC10_ClearInterruptFlag			(ADC10.control_0 &= ~ADC10IFG)
#define ADC10_SetInterruptFlag				(ADC10.control_0 |= ADC10IFG)
#define ADC10_GetInterruptFlag				(ADC10.control_0 & ADC10IFG)

#define ADC10_DisableConversion				(ADC10.control_0 &= ~ENC)
#define ADC10_EnableConversion				(ADC10.control_0 |= ENC)

#define ADC10_StartConversion				(ADC10.control_0 |= ADC10SC)

#define ADC10_EnableAndStartConversion		(ADC10.control_0 |= (ENC | ADC10SC))

#define ADC10_ClearInputChannel				(ADC10.control_1 &= ~(INCH3 | INCH2 | INCH1 | INCH0))
#define ADC10_SetInputChannel(a)			{ADC10_ClearInputChannel; \
											ADC10.control_1 |= (a & (INCH3 | INCH2 | INCH1 | INCH0));}

#define ADC10_ClearSampleAndHoldSource		(ADC10.control_1 &= ~(SHS1 | SHS0))
#define ADC10_SetSampleAndHoldSource(a)		{ADC10_ClearSampleAndHoldSource; \
											ADC10.control_1 |= (a & (SHS1 | SHS0));}

#define ADC10_SetDataFormatBinary			(ADC10.control_1 &= ~ADC10DF)
#define ADC10_SetDataFormat2sComp			(ADC10.control_1 |= ADC10DF)

#define ADC10_InvertSampleAndHoldSignal		(ADC10.control_1 |= ISSH)
#define ADC10_NoninvertSampleAndHoldSignal	(ADC10.control_1 &= ~ISSH)

#define ADC10_ClearClockDivider				(ADC10.control_1 &= ~(ADC10DIV2 | ADC10DIV1 | ADC10DIV0))
#define ADC10_SetClockDivider(a)			{ADC10_ClearClockDivider; \
											ADC10.control_1 |= (a & (ADC10DIV2 | ADC10DIV1 | ADC10DIV0));}

#define ADC10_ClearClockSource				(ADC10.control_1 &= ~(ADC10SSEL1 | ADC10SSEL0))
#define ADC10_SetClockSource(a)				{ADC10_ClearClockSource; \
											ADC10.control_1 |= (a & (ADC10SSEL1 | ADC10SSEL0));}

#define ADC10_ClearConvSeqModeSelect		(ADC10.control_1 &= ~(CONSEQ1 | CONSEQ0))
#define ADC10_SetConvSeqModeSelect(a)		{ADC10_ClearConvSeqModeSelect; \
											ADC10.control_1 |= (a & (CONSEQ1 | CONSEQ0));}

#define ADC10_IsBusy						(ADC10.control_1 & ADC10BUSY)

#define ADC10_EnableAnalogInputPin(a)		(ADC10.inputEnable_0 |= (1 << a))
#define ADC10_DisableAnalogInputPin(a)		(ADC10.inputEnable_0 &= ~(1 << a))
#define ADC10_EnableAnalogInputs(a)			(ADC10.inputEnable_0 |= a)
#define ADC10_DisableAnalogInputs(a)		(ADC10.inputEnable_0 &= ~a)
#define ADC10_DisableAllAnalogInputs		(ADC10.inputEnable_0 = 0)

#if defined (__MSP430F22xx)
#define ADC10_EnableAnalogInputPin(a)		(ADC10.inputEnable_1 |= ((1 << (a - 8)) & 0xF0)
#define ADC10_DisableAnalogInputPin(a)		(ADC10.inputEnable_1 &= ~((1 << (a - 8)) & 0xF0)
#define ADC10_EnableAnalogInputs(a)			(ADC10.inputEnable_1 |= a & 0xF0)
#define ADC10_DisableAnalogInputs(a)		(ADC10.inputEnable_1 &= ~(a & 0xF0)
#define ADC10_DisableAllAnalogInputs		(ADC10.inputEnable_1 = 0)
#endif // defined (__MSP430F22xx)

#define ADC10_GetConversionResults			(ADC10.memory)

#define ADC10_SetDataTransferTwoBlockMode	(ADC10.dataTransferControl_0 |= ADC10TB)
#define ADC10_SetDataTransferOneBlockMode	(ADC10.dataTransferControl_0 &= ~ADC10TB)
#define ADC10_SetDataTransferContinuous		(ADC10.dataTransferControl_0 |= ADC10CT)
#define ADC10_StopContinuousDataTransfer	(ADC10.dataTransferControl_0 &= ~ADC10CT)
#define ADC10_GetDataTransferBlockStatus	(ADC10.dataTransferControl_0 & ADC10B1)
#define ADC10_GetDataTransferBlock1Status	(!!ADC10_GetDataTransferBlockStatus)
#define ADC10_GetDataTransferBlock2Status	(!ADC10_GetDataTransferBlockStatus)

#define ADC10_SetNumTransfersInDTC(a)		(ADC10.dataTransferControl_1 = a)

#define ADC10_SetDTCStartAddress(a)			(ADC10.dataTransferStartAddr = a)
/******************************************************************************/
//	END: Macro Definitions
/******************************************************************************/


//	Public Function Prototypes (extern)
/******************************************************************************/
//Put public function prototypes here
void ADC10_init (void);
void ADC10_registerCallback (functionPointer_t fPtr, uint8_t LPM_bits);
/******************************************************************************/
//	End Public Function Prototypes


#endif /* ADC10_H_ */
