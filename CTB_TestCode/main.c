//=================================================================================================
/// @file main.c
///
/// @brief  Test code for checking all BGA solder connections of TMS320F2838xDZWT
///         checks all pins, PWM signals, ADCs and DACs for functionality
/// @version V1.1.0
///
/// @date
///
/// @author
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Including
//-------------------------------------------------------------------------------------------------
#include "TB_PWM.h"
#include "TB_ADC.h"
#include "TB_GPIO.h"
#include "TB_DAC.h"
#include "TB_Functions.h"
#include "TB_Device.h"

//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------

//=== Function: main ==============================================================================
///
/// @brief main programme
///
/// @param void
///
/// @return void
///
//=================================================================================================
void main(void)
{
    //  initialise microcontroller (watchdog, system clock, memory, interrupts)
    DeviceInit(DEVICE_CLKSRC_EXTOSC_SE_25MHZ);

    //  configurs all GPIOs in Error_LEDs section on Test board
    GpioInit_Error_LEDs();

    //  configurs all GPIOs in Group-A to Group-D on Test board
    GpioInit_GroupABCD();

    //  configurs all GPIOs in Group-E to Group-H on Test board
    GpioInit_GroupEFGH();

    //  configurs all GPIOs in PWM_LEDs section on Test board
    GpioInit_PWM_LEDs();

    //  configurs all GPIOs related to Hardware_Error_Detection on LEA Control Board
    GpioInit_Hardware_Error_Detection();

    //------------------------------------------------------------------------------

    //  Lights up all LED's in Error_LEDs section
    Error_LEDs_Check();

    //  Lights up all LED's in PWM_LEDs section
    PWM_LEDs_Check();

    //  Lights up all LED's in Group-A to Group-H
    GPIOLEDs_Check();

    //------------------------------------------------------------------------------

    //  initialise all PWMs (ePWM 1 to 16)
    PwmInitAll();

    //  initialise all DACs (module A,B,C)
    DACInitAll();

    //  initialise all ADCs (module A,B,C,D)
    AdcInitAll();

    //------------------------------------------------------------------------------

    //  Checks Hardware_Error_Detection section
    Hardware_Error_Detection_Check();

    //  Checks all ADCINs
    ADCINs_Check();

    //------------------------------------------------------------------------------

    // Continuous loop main programme
    while(1)
    {

    }
}
