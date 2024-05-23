//=================================================================================================
/// @file TB_GPIO.c
///
/// @brief      File contains variables and functions around the GPIOs of the microcontroller
///             TMS320F2838x to configure them as outputs or inputs
///
/// @version
///
/// @date
///
/// @author
//=================================================================================================
#ifndef MYGPIO_H_
#define MYGPIO_H_
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "TB_Device.h"


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
// Multiplexer GPIO-Funktionalität
#define GPIO_MULTIPLEX_GPIO										0
#define GPIO_MULTIPLEX_EPWM                   1
// Konfigurationssperre
#define GPIO_CONFIG_UNLOCK										0
#define GPIO_CONFIG_LOCK											1
// Pullup-Widerstand
#define GPIO_ENABLE_PULLUP										0
#define GPIO_DISABLE_PULLUP										1
// Datenrichtung
#define GPIO_INPUT														0
#define GPIO_OUTPUT														1
// Steuernde Instanz
#define GPIO_CONTROLLED_BY_CPU1								0
#define GPIO_CONTROLLED_BY_CLA_CPU1						1
#define GPIO_CONTROLLED_BY_CPU2 							2
#define GPIO_CONTROLLED_BY_CLA_CPU2						3
#define GPIO_CONTROLLED_BY_CM									4




//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Prototypes of global functions
//-------------------------------------------------------------------------------------------------
// Funktion initialisiert GPIOs als Ein- bzw. Ausgänge
extern void GpioInit_Error_LEDs(void);
extern void GpioInit_GroupABCD(void);
extern void GpioInit_GroupEFGH(void);
extern void GpioInit_PWM_LEDs(void);
extern void GpioInit_Hardware_Error_Detection(void);


#endif
