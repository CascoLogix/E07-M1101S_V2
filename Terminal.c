/******************************************************************************/
//	Terminal.c
//  
//	 Created on: Jan 11, 2015
//	     Author: Clint Stevenson
//
/******************************************************************************/


/******************************************************************************/
//	Includes
/******************************************************************************/
#include <main.h>
#include <Terminal.h>
#include <stdint.h>
/******************************************************************************/
//	End Includes


/******************************************************************************/
//	Defines
/******************************************************************************/
//Put defines here
/******************************************************************************/
//	End Defines


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
#ifndef TX_QUEUE_SIZE
#error "TX_QUEUE_SIZE not defined"
#endif
char TXQueue[TX_QUEUE_SIZE];

#ifndef RX_QUEUE_SIZE
#error "RX_QUEUE_SIZE not defined"
#endif
char RXQueue[RX_QUEUE_SIZE];
/******************************************************************************/
//	End Variable Declarations


/******************************************************************************/
//	Function Prototypes
/******************************************************************************/
//Put function prototypes here
uint8_t isNumeric (uint8_t ASCIIchar);
uint8_t isUpperCase (uint8_t ASCIIchar);
uint8_t isLowerCase (uint8_t ASCIIchar);
uint8_t isAlpha (uint8_t ASCIIchar);
char getChar (void);
void putChar (char data);
void getLine (char * pString);
/******************************************************************************/
//	End Function Prototypes


/******************************************************************************/
//	Function Definitions
/******************************************************************************/
//Put function definitions here
uint8_t isNumeric (uint8_t ASCIIchar)
{
	uint8_t retVal = 0;

	if (ASCIIchar >= '0' && ASCIIchar <= '9')
	{
		retVal = 1;
	}

	return retVal;
}


uint8_t isUpperCase (uint8_t ASCIIchar)
{
	uint8_t retVal = 0;

	if (ASCIIchar >= 'A' && ASCIIchar <= 'Z')
	{
		retVal = 1;
	}

	return retVal;
}


uint8_t isLowerCase (uint8_t ASCIIchar)
{
	uint8_t retVal = 0;

	if (ASCIIchar >= 'a' && ASCIIchar <= 'z')
	{
		retVal = 1;
	}

	return retVal;
}


uint8_t isAlpha (uint8_t ASCIIchar)
{
	uint8_t retVal = 0;

	if (isUpperCase(ASCIIchar) || isLowerCase(ASCIIchar))
	{
		retVal = 1;
	}

	return retVal;
}


char getChar (void)
{
	uint8_t rxChar = 0;

	while (!(IFG2 & UCA0RXIFG));	// Wait for RX'd char
	//RXQueue[];
	rxChar = UCA0RXBUF;				// Read RX'd char
	putChar(rxChar);				// Echo RX'd char
	return rxChar;					// Return RX'd char
}


void putChar (char data)
{
	while (!(IFG2 & UCA0TXIFG));	// Wait for any buffered data
	//TXQueue[];
	UCA0TXBUF = data;
}


void writeLine (char * pString)
{
	while (*pString)
	{
		putChar(*pString);
		pString++;
	}
}



void getLine (char * pString)
{
	while (*pString != '\r' || *pString != '\n')	// Check for line terminator
	{
		*pString = getChar();						// Get char
		pString++;									// Increment string pointer
	}

	pString--;										// Decrement string pointer
	pString = 0;									// Null-terminate string
}
/******************************************************************************/
//	End Function Definitions
