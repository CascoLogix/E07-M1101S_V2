/*
	CC1101.h - CC1101 module library


	This library is designed to be used with the CC1101/CC1100 module on the MSP430.
	It is designed to be portable across all MSP430 devices. To change the class for
	your specific MSP430, edit the #defines in Pinouts.h
	For details on the CC1101, please refer to the datasheet.

	Created By: Lucas Cox
	Do anything you would like with this code.
*/
#ifndef CC1101_h_
#define CC1101_h_


void CC1101_init(void);
void CC1101_sendPacket(char *txBuffer, char size);
char CC1101_receivePacket(char *rxBuffer, char *length);
char CC1101_pollReceiveFlag(void);
void CC1101_setReceive(void);
void CC1101_setIdle(void);
void CC1101_setSleep(void);
short CC1101_getRSSI(void);
void CC1101_powerupReset(void);


#endif // CC1101_h_
