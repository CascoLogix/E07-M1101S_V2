/*****************************************************************************/
//	SPI.h
//  
//	 Created on: Dec 10, 2014
//	     Author: Clint Stevenson
//
/*****************************************************************************/


#ifndef SPI_H_
#define SPI_H_


/*****************************************************************************/
//	Includes
/*****************************************************************************/
//Put conditional includes here
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
void SPI_setup(void);
void SPI_writeReg(char addr, char value);
void SPI_writeBurstReg(char addr, char *buffer, char count);
char SPI_readReg(char addr);
void SPI_readBurstReg(char addr, char *buffer, char count);
char SPI_readStatus(char addr);
void SPI_strobe(char strobe);
void SPI_wait(unsigned int cycles);
/*****************************************************************************/
//	End Public Function Prototypes


#endif /* SPI_H_ */
