/******************************************************************************/
//	Sensors.h
//  
//	 Created on: Jan 22, 2015
//	     Author: Clint Stevenson
//
/******************************************************************************/


#ifndef SENSORS_H_
#define SENSORS_H_


/******************************************************************************/
//	Includes
/******************************************************************************/
//Put conditional includes here
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
//	End Public Typedef Declarations


/******************************************************************************/
//	Public Function Prototypes (extern)
/******************************************************************************/
//Put public function prototypes here
void initSensors (void);
void updateSensors (void);
void updateBattVoltage (void);
void updatePump1Temp (void);
void updatePump2Temp (void);
void updateAmbientAirTemp (void);
void updateTankWaterTemp (void);
void updateTankWaterLevel (void);
uint16_t getBattVoltage (void);
int16_t getPump1Temp (void);
int16_t getPump2Temp (void);
int16_t getAmbientAirTemp (void);
int16_t getTankWaterTemp (void);
uint16_t getTankWaterLevel (void);
/******************************************************************************/
//	End Public Function Prototypes


#endif /* SENSORS_H_ */
