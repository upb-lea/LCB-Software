//=================================================================================================
/// @file       TB_DAC.h
///
/// @brief      file contains variables and functions to use the internal digital-analogue converter
///             of the TMS320F2838x. The code configures all DACs i.e DACOUTA, DACOUTB, DACOUTC
///
/// @version    V1.1.0
///
/// @date       23-04-2024
///
/// @author     Vijay
//=================================================================================================
#ifndef MYDAC_H_
#define MYDAC_H_
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "TB_Device.h"


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
// Reference voltage
#define DAC_REF_VDAC    0
#define DAC_REF_VREFHI  1
// Load the DAC value into the active register
#define DAC_SYNC_SYSCLK 0
#define DAC_SYNC_EPWM   1
// PWM synchronisation source
#define DAC_EPWM1SYNCPER    0
#define DAC_EPWM2SYNCPER    1
#define DAC_EPWM3SYNCPER    2
#define DAC_EPWM4SYNCPER    3
#define DAC_EPWM5SYNCPER    4
#define DAC_EPWM6SYNCPER    5
#define DAC_EPWM7SYNCPER    6
#define DAC_EPWM8SYNCPER    7
#define DAC_EPWM9SYNCPER    8
#define DAC_EPWM10SYNCPER   9
#define DAC_EPWM11SYNCPER   10
#define DAC_EPWM12SYNCPER   11
#define DAC_EPWM13SYNCPER   12
#define DAC_EPWM14SYNCPER   13
#define DAC_EPWM15SYNCPER   14
#define DAC_EPWM16SYNCPER   15
// Output
#define DAC_DISABLE_OUTPUT  0
#define DAC_ENABLE_OUTPUT   1


//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Prototypes of global functions
//-------------------------------------------------------------------------------------------------
// Function initialises the DAC-A,B,C modules
extern void DACInitAll(void);


#endif
