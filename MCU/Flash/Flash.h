/*****************************************************************************/
//	Flash.h
//  
//	 Created on: Jan 21, 2015
//	     Author: Clint Stevenson
//
/*****************************************************************************/


#ifndef FLASH_H_
#define FLASH_H_


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
/*	Flash Struct Type Defines for Struct Overlays						 */
/*                                                                           */
/*****************************************************************************/
#if defined (__MSP430_HAS_FLASH2__)
// (refer to MSP430x5xx Family User's Guide)
typedef struct {
	uint16_t control_1;
	uint16_t control_2;
	uint16_t control_3;
	const uint16_t _DNU0[0x90];
	uint16_t control_4;
} Flash_t;
#endif // defined (__MSP430_HAS_FLASH2__)
/*****************************************************************************/
/*                                                                           */
/*	END: Flash Struct Type Defines for Struct Overlays					 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
//	End Public Typedef Declarations


/*****************************************************************************/
//	Constant Struct Overlay Declarations
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*	Flash Struct Overlay Declaration 									 */
/*                                                                           */
/*****************************************************************************/
// Declare pointer to struct overlay for the Flash peripheral
extern Flash_t volatile * const p_Flash;
#define FLASH		(*p_Flash)
/*****************************************************************************/
/*                                                                           */
/*	END: Flash Struct Overlay Declaration								 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
//	END: Struct Overlay Declarations for Peripheral Register Access


/*****************************************************************************/
//	Macro Definitions
/*****************************************************************************/
// Flash register manipulation macros
#define Flash_Unlock							(Flash.control_1 |= FWKEY)
#define Flash_SetBlockWriteMode					(Flash.control_1 |= BLKWRT)
#define Flash_ClearBlockWriteMode				(Flash.control_1 &= ~BLKWRT)
#define Flash_SetWriteMode						(Flash.control_1 |= WRT)
#define Flash_ClearWriteMode					(Flash.control_1 &= ~WRT)
/*****************************************************************************/
//	END: Macro Definitions
/*****************************************************************************/


//	Public Function Prototypes (extern)
/*****************************************************************************/
//Put public function prototypes here
void Flash_init (void);
/*****************************************************************************/
//	End Public Function Prototypes


#endif /* FLASH_H_ */
