/******************************************************************************/
//	Sensors.c
//  
//	 Created on: Jan 22, 2015
//	     Author: Clint Stevenson
//
/******************************************************************************/


/******************************************************************************/
//	Includes
/******************************************************************************/
#include <Sensors.h>
#include <ADC10.h>
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
struct {
	const uint8_t dataPayload;
	uint16_t battVoltage;
	int16_t pump1Temp;
	int16_t pump2Temp;
	int16_t ambAirTemp;
	int16_t tankWaterTemp;
	uint16_t tankWaterLevel;
} sensorReadings = {
	(sizeof(sensorReadings) - sizeof(sensorReadings.dataPayload)), // dataPayload
	0,														// battVoltage
	0,														// pump1Temp
	0,														// pump2Temp
	0,														// ambAirTemp
	0,														// tankWaterTemp
	0														// tankWaterLevel
};
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
void initSensors (void)
{
	ADC10_init();
}


void updateSensors (void)
{
	updateBattVoltage();
	updatePump1Temp();
	updatePump2Temp();
	updateAmbientAirTemp();
	updateTankWaterTemp();
	updateTankWaterLevel();
}


void updateBattVoltage (void)
{
	ADC10_SetInputChannel(ADC10_VCC);
	ADC10_EnableAndStartConversion;
	while(ADC10_IsBusy);
	//while(!ADC10_GetInterruptFlag);
	//ADC10_ClearInterruptFlag;
	sensorReadings.battVoltage = ADC10_GetConversionResults;
	ADC10_DisableConversion;
}


void updatePump1Temp (void)
{
	sensorReadings.pump1Temp = 0;
}


void updatePump2Temp (void)
{
	sensorReadings.pump2Temp = 0;
}


#define VTEMP							(2.5)
#define ADC10_RESOLUTION				(1023)
#define ADC10_TEMP_TO_DEG_C(a)			(a = (a - 0.986) / 0.00355)
#define DEG_C_TO_DEG_F(a)				(a = (a * 1.8) + 32)
#define CAL_ADC_25T3C					(0x7C)

void updateAmbientAirTemp (void)
{
	ADC10_SetInputChannel(ADC10_INTERNAL_TEMP);
	//ADC10_SetRef;
	ADC10_EnableAndStartConversion;
	while(ADC10_IsBusy);
	//while(!ADC10_GetInterruptFlag);
	//ADC10_ClearInterruptFlag;
	sensorReadings.ambAirTemp = ADC10_GetConversionResults + CAL_ADC_25T3C;
	ADC10_DisableConversion;
	//ADC10_ClearRef;

	//sensorReadings.ambAirTemp = sensorReadings.ambAirTemp / ADC10_RESOLUTION;
	//sensorReadings.ambAirTemp = sensorReadings.ambAirTemp * VTEMP;
	//sensorReadings.ambAirTemp = (sensorReadings.ambAirTemp - 0.986) / 0.00355;
	//sensorReadings.ambAirTemp = (sensorReadings.ambAirTemp * 1.8) + 32;
	//ADC10_TEMP_TO_DEG_C(sensorReadings.ambAirTemp);
	//DEG_C_TO_DEG_F(sensorReadings.ambAirTemp);
}


void updateTankWaterTemp (void)
{
	sensorReadings.tankWaterTemp = 0;
}


void updateTankWaterLevel (void)
{
	sensorReadings.tankWaterLevel = 0;
}


uint16_t getBattVoltage (void)
{
	return sensorReadings.battVoltage;
}


int16_t getPump1Temp (void)
{
	return sensorReadings.pump1Temp;
}


int16_t getPump2Temp (void)
{
	return sensorReadings.pump2Temp;
}


int16_t getAmbientAirTemp (void)
{
	return sensorReadings.ambAirTemp;
}


int16_t getTankWaterTemp (void)
{
	return sensorReadings.tankWaterTemp;
}


uint16_t getTankWaterLevel (void)
{
	return sensorReadings.tankWaterLevel;
}
/******************************************************************************/
//	End Function Definitions
