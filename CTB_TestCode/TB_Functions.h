//=================================================================================================
/// @file     TB_Functions.h
///
/// @brief    File contains functions for testing all GPIOs, PWMs, DACs and ADCs
///
/// @version  V1.1.0
///
/// @date     23-04-2024
///
/// @author   Vijay
//=================================================================================================
#ifndef MYFUNCTIONS_H_
#define MYFUNCTIONS_H_
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "TB_Device.h"

//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Prototypes of global functions
//-------------------------------------------------------------------------------------------------
// Function
extern void Error_LEDs_Check(void);
extern void PWM_LEDs_Check(void);
extern void GPIOLEDs_Check(void);
extern void ADCINs_Check(void);
extern void Hardware_Error_Detection_Check(void);
extern void ADC_ErrorCheck(int);
extern void Error_LEDs_Off(int);
extern void Error_LEDs_On(int);
extern void PWM_LEDs_On(int);
extern void PWM_LEDs_Off(int);
extern void Mux_Select(int);
extern void ADCtoPWM(int);
extern void GPIOLEDs_On(int);
extern void GPIOLEDs_Off(int);

#endif
