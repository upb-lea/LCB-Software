//=================================================================================================
/// @file TB_GPIO.c
///
/// @brief  configurs ALL GPIOs
///
/// @version
///
/// @date
///
/// @author
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "TB_GPIO.h"


//=== Function: GpioInit_Error_LEDs ==========================================================================
///
/// @brief Function initialises all Error LEDs GPIO's as outputs
///
/// @param void
///
/// @return void
///
//===========================================================================================================
void GpioInit_Error_LEDs(void)
{
    EALLOW;

    // Error 1
    GpioCtrlRegs.GPBLOCK.bit.GPIO47 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO47 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO47 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO47 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO47 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO47 = 1;

    // Error 2
    GpioCtrlRegs.GPCLOCK.bit.GPIO73 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO73 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO73 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO73 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO73 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO73 = 1;

    // Error 3
    GpioCtrlRegs.GPBLOCK.bit.GPIO34 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO34 = 1;

    // Error 4
    GpioCtrlRegs.GPALOCK.bit.GPIO23 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO23 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO23 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO23 = 1;

    // Error 5
    GpioCtrlRegs.GPALOCK.bit.GPIO26 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO26 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO26 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO26 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO26 = 1;

    // Error 6
    GpioCtrlRegs.GPALOCK.bit.GPIO25 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO25 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO25 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO25 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO25 = 1;

    // Error 7
    GpioCtrlRegs.GPDLOCK.bit.GPIO102 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO102 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO102 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO102 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO102 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO102 = 1;

    // Error 8
    GpioCtrlRegs.GPDLOCK.bit.GPIO101 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO101 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO101 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO101 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO101 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO101 = 1;

    // Error 9
    GpioCtrlRegs.GPALOCK.bit.GPIO18 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO18 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO18 = 1;

    // Error 10
    GpioCtrlRegs.GPALOCK.bit.GPIO17 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO17 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO17 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO17 = 1;

    // Error 11
    GpioCtrlRegs.GPALOCK.bit.GPIO13 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO13 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO13 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO13 = 1;

    // Error 12
    GpioCtrlRegs.GPALOCK.bit.GPIO0 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO0 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO0 = 1;

    // Error 13
    GpioCtrlRegs.GPALOCK.bit.GPIO4 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO4 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO4 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO4 = 1;

    // Error 14
    GpioCtrlRegs.GPDLOCK.bit.GPIO109 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO109 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO109 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO109 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO109 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO109 = 1;

    // Error 15
    GpioCtrlRegs.GPDLOCK.bit.GPIO110 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO110 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO110 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO110 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO110 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO110 = 1;

    // Error 16
    GpioCtrlRegs.GPDLOCK.bit.GPIO106 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO106 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO106 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO106 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO106 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO106 = 1;

    // Error 17
    GpioCtrlRegs.GPDLOCK.bit.GPIO108 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO108 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO108 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO108 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO108 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO108 = 1;

    // Error 18
    GpioCtrlRegs.GPDLOCK.bit.GPIO105 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO105 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO105 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO105 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO105 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO105 = 1;

    // Error 19
    GpioCtrlRegs.GPBLOCK.bit.GPIO33 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO33 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO33 = 1;

    // Error 20
    GpioCtrlRegs.GPALOCK.bit.GPIO22 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO22 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO22 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO22 = 1;

    // Error 21
    GpioCtrlRegs.GPALOCK.bit.GPIO27 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO27 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO27 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO27 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO27 = 1;

    // Error 22
    GpioCtrlRegs.GPALOCK.bit.GPIO24 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO24 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO24 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO24 = 1;

    // Error 23
    GpioCtrlRegs.GPDLOCK.bit.GPIO103 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO103 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO103 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO103 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO103 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO103 = 1;

    // Error 24
    GpioCtrlRegs.GPDLOCK.bit.GPIO100 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO100 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO100 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO100 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO100 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO100 = 1;

    // Error 25
    GpioCtrlRegs.GPALOCK.bit.GPIO19 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO19 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO19 = 1;

    // Error 26
    GpioCtrlRegs.GPALOCK.bit.GPIO16 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO16 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO16 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO16 = 1;

    // Error 27
    GpioCtrlRegs.GPALOCK.bit.GPIO12 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO12 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO12 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO12 = 1;

    // Error 28
    GpioCtrlRegs.GPALOCK.bit.GPIO1 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO1 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO1 = 1;

    // Error 29
    GpioCtrlRegs.GPCLOCK.bit.GPIO70 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO70 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO70 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO70 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO70 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO70 = 1;

    EDIS;

}

//=== Function: GpioInit_GroupABCD ==========================================================================
///
/// @brief Function initialises all GPIOs in GroupA to GroupD as outputs
///
/// @param void
///
/// @return void
///
//===========================================================================================================
void GpioInit_GroupABCD(void)
{
    EALLOW;

    GpioCtrlRegs.GPDLOCK.bit.GPIO116 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO116 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO116 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO116 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO116 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO116 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO121 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO121 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO121 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO121 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO121 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO121 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO117 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO117 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO117 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO117 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO117 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO117 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO48 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO48 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO48 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO48 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO48 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO124 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO124 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO124 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO124 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO124 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO124 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO115 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO115 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO115 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO115 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO115 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO115 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO123 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO123 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO123 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO123 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO123 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO123 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO118 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO118 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO118 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO118 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO118 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO118 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO113 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO113 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO113 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO113 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO113 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO113 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO111 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO111 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO111 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO111 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO111 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO111 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO38 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO38 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO38 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO38 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO38 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO38 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO50 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO50 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO50 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO50 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO50 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO40 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO40 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO40 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO40 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO53 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO53 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO53 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO53 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO54 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO54 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO54 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO54 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO54 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO56 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO56 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO56 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO56 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO56 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO41 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO41 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO41 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO41 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO41 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO45 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO45 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO45 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO45 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO45 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO45 = 1;

    GpioCtrlRegs.GPELOCK.bit.GPIO129 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO129 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO129 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO129 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO129 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPESET.bit.GPIO129 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO127 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO127 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO127 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO127 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO127 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO127 = 1;

    GpioCtrlRegs.GPALOCK.bit.GPIO29 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO29 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO29 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO29 = 1;

    GpioCtrlRegs.GPALOCK.bit.GPIO30 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO30 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO30 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO30 = 1;

    GpioCtrlRegs.GPELOCK.bit.GPIO134 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO134 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO134 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO134 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO134 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPESET.bit.GPIO134 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO58 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO58 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO58 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO58 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO58 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO59 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO59 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO59 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO59 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO59 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO59 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO65 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO65 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO65 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO65 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO65 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO65 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO61 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO61 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO61 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO61 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO61 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO61 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO79 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO79 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO79 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO79 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO79 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO79 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO76 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO76 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO76 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO76 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO76 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO76 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO68 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO68 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO68 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO68 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO68 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO68 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO85 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO85 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO85 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO85 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO85 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO85 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO69 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO69 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO69 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO69 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO69 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO69 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO77 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO77 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO77 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO77 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO77 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO77 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO83 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO83 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO83 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO83 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO83 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO83 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO81 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO81 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO81 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO81 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO81 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO81 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO84 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO84 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO84 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO84 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO84 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO84 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO46 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO46 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO46 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO46 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO46 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO46 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO88 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO88 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO88 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO88 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO88 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO88 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO43 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO43 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO43 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO43 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO43 = 1;

    GpioCtrlRegs.GPALOCK.bit.GPIO9 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO9 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO9 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO9 = 1;

    EDIS;

}

//=== Function: GpioInit_GroupEFGH ==========================================================================
///
/// @brief Function initialises all GPIOs in GroupE to GroupH as outputs
///
/// @param void
///
/// @return void
///
//===========================================================================================================
void GpioInit_GroupEFGH(void)
{
    EALLOW;

    GpioCtrlRegs.GPBLOCK.bit.GPIO32 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO32 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO32 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO37 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO37 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO37 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO37 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO37 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO37 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO120 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO120 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO120 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO120 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO120 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO120 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO119 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO119 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO119 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO119 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO119 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO119 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO122 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO122 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO122 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO122 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO122 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO122 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO114 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO114 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO114 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO114 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO114 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO114 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO112 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO112 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO112 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO112 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO112 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO112 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO107 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO107 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO107 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO107 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO107 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO107 = 1;

    GpioCtrlRegs.GPALOCK.bit.GPIO31 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO31 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO31 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO36 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO36 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO36 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO36 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO36 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO36 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO39 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO39 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO39 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO39 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO49 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO49 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO49 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO49 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO49 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO51 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO51 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO51 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO51 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO51 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO52 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO52 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO52 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO52 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO52 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO55 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO55 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO55 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO55 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO55 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO57 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO57 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO57 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO57 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO57 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO44 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO44 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO44 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO44 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO44 = 1;

    GpioCtrlRegs.GPELOCK.bit.GPIO130 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO130 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO130 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO130 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO130 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPESET.bit.GPIO130 = 1;

    GpioCtrlRegs.GPELOCK.bit.GPIO128 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO128 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO128 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO128 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO128 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPESET.bit.GPIO128 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO126 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO126 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO126 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO126 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO126 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO126 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO125 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX2.bit.GPIO125 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX2.bit.GPIO125 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO125 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO125 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO125 = 1;

    GpioCtrlRegs.GPELOCK.bit.GPIO131 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO131 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO131 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO131 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO131 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPESET.bit.GPIO131 = 1;

    GpioCtrlRegs.GPELOCK.bit.GPIO132 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO132 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO132 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO132 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO132 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPESET.bit.GPIO132 = 1;

    GpioCtrlRegs.GPELOCK.bit.GPIO136 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO136 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO136 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO136 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO136 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPESET.bit.GPIO136 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO60 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO60 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO60 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO60 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO60 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO64 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO64 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO64 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO64 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO64 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO64 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO66 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO66 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO66 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO66 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO66 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO66 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO63 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO63 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO63 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO63 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO63 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO63 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO62 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX2.bit.GPIO62 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX2.bit.GPIO62 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO62 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO62 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO62 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO78 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO78 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO78 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO78 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO78 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO78 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO72 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO72 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO72 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO72 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO72 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO72 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO71 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX1.bit.GPIO71 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX1.bit.GPIO71 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO71 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO71 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO71 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO87 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO87 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO87 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO87 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO87 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO87 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO86 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO86 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO86 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO86 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO86 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO86 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO80 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO80 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO80 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO80 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO80 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO80 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO82 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO82 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO82 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO82 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO82 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO82 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO90 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO90 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO90 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO90 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO90 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO90 = 1;

    GpioCtrlRegs.GPCLOCK.bit.GPIO89 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO89 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO89 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO89 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO89 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPCSET.bit.GPIO89 = 1;

    GpioCtrlRegs.GPBLOCK.bit.GPIO42 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPBGMUX1.bit.GPIO42 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPBPUD.bit.GPIO42 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPBDIR.bit.GPIO42 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPBSET.bit.GPIO42 = 1;

    GpioCtrlRegs.GPALOCK.bit.GPIO8 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO8 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO8 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO8 = 1;

    EDIS;

}

//=== Function: GpioInit_Hardware_Error_Detection ==========================================================================
///
/// @brief Function configures all GPIOs related to LCB's Hardware error detection
///
/// @param void
///
/// @return void
///
//==========================================================================================================================
void GpioInit_Hardware_Error_Detection(void)
{
    EALLOW;

    //reset GPIOs
    GpioCtrlRegs.GPDLOCK.bit.GPIO98 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO98 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO98 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO98 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO98 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO98 = 1;

    GpioCtrlRegs.GPALOCK.bit.GPIO10 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO10 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO10 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO10 = 1;

    GpioCtrlRegs.GPALOCK.bit.GPIO11 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO11 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO11 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPASET.bit.GPIO11 = 1;

    GpioCtrlRegs.GPDLOCK.bit.GPIO97 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO97 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO97 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO97 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO97 = GPIO_OUTPUT;             // Set as output
    GpioDataRegs.GPDSET.bit.GPIO97 = 1;

    //Q & Q-bar
    GpioCtrlRegs.GPDLOCK.bit.GPIO96 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO96 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO96 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO96 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO96 = GPIO_INPUT;             // Set as output

    GpioCtrlRegs.GPDLOCK.bit.GPIO99 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO99 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO99 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO99 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO99 = GPIO_INPUT;             // Set as output

    GpioCtrlRegs.GPCLOCK.bit.GPIO95 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPCGMUX2.bit.GPIO95 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPCMUX2.bit.GPIO95 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPCPUD.bit.GPIO95 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPCDIR.bit.GPIO95 = GPIO_INPUT;             // Set as output

    GpioCtrlRegs.GPALOCK.bit.GPIO15 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO15 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO15 = GPIO_INPUT;             // Set as output

    GpioCtrlRegs.GPALOCK.bit.GPIO14 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX1.bit.GPIO14 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO14 = GPIO_INPUT;             // Set as output

    GpioCtrlRegs.GPDLOCK.bit.GPIO104 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPDGMUX1.bit.GPIO104 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPDMUX1.bit.GPIO104 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPDPUD.bit.GPIO104 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPDDIR.bit.GPIO104 = GPIO_INPUT;             // Set as output

    GpioCtrlRegs.GPALOCK.bit.GPIO21 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO21 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO21 = GPIO_INPUT;             // Set as output

    GpioCtrlRegs.GPALOCK.bit.GPIO20 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPAGMUX2.bit.GPIO20 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPADIR.bit.GPIO20 = GPIO_INPUT;             // Set as output

    EDIS;

}

//=== Function: GpioInit_PWM_LEDs ==========================================================================
///
/// @brief Function configures all GPIOs related to PWM_LEDs section
///
/// @param void
///
/// @return void
///
//==========================================================================================================================
void GpioInit_PWM_LEDs(void)
{

    EALLOW;

    GpioCtrlRegs.GPELOCK.bit.GPIO137 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX1.bit.GPIO137 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX1.bit.GPIO137 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO137 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO137 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO138 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX1.bit.GPIO138 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX1.bit.GPIO138 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO138 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO138 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO139 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX1.bit.GPIO139 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX1.bit.GPIO139 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO139 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO139 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO140 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX1.bit.GPIO140 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX1.bit.GPIO140 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO140 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO140 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO141 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX1.bit.GPIO141 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX1.bit.GPIO141 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO141 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO141 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO142 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX1.bit.GPIO142 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX1.bit.GPIO142 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO142 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO142 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO143 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX1.bit.GPIO143 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX1.bit.GPIO143 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO143 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO143 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO144 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO144 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO144 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO144 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO144 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO145 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO145 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO145 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO145 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO145 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO146 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO146 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO146 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO146 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO146 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO147 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO147 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO147 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO147 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO147 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO148 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO148 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO148 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO148 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO148 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO149 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO149 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO149 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO149 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO149 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO150 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO150 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO150 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO150 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO150 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO151 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO151 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO151 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO151 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO151 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO152 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO152 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO152 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO152 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO152 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO153 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO153 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO153 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO153 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO153 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO154 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO154 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO154 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO154 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO154 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO155 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO155 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO155 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO155 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO155 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO156 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO156 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO156 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO156 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO156 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO157 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO157 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO157 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO157 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO157 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO158 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO158 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO158 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO158 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO158 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPELOCK.bit.GPIO159 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEMUX2.bit.GPIO159 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPEGMUX2.bit.GPIO159 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO159 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPEDIR.bit.GPIO159 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPFLOCK.bit.GPIO160 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFMUX1.bit.GPIO160 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPFGMUX1.bit.GPIO160 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO160 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPFDIR.bit.GPIO160 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPFLOCK.bit.GPIO161 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFMUX1.bit.GPIO161 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPFGMUX1.bit.GPIO161 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO161 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPFDIR.bit.GPIO161 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPFLOCK.bit.GPIO162 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFMUX1.bit.GPIO162 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPFGMUX1.bit.GPIO162 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO162 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPFDIR.bit.GPIO162 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPFLOCK.bit.GPIO163 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFMUX1.bit.GPIO163 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPFGMUX1.bit.GPIO163 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO163 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPFDIR.bit.GPIO163 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPFLOCK.bit.GPIO164 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFMUX1.bit.GPIO164 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPFGMUX1.bit.GPIO164 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO164 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPFDIR.bit.GPIO164 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPFLOCK.bit.GPIO165 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFMUX1.bit.GPIO165 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPFGMUX1.bit.GPIO165 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO165 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPFDIR.bit.GPIO165 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPFLOCK.bit.GPIO166 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFMUX1.bit.GPIO166 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPFGMUX1.bit.GPIO166 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO166 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPFDIR.bit.GPIO166 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPFLOCK.bit.GPIO167 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFMUX1.bit.GPIO167 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPFGMUX1.bit.GPIO167 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO167 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPFDIR.bit.GPIO167 = GPIO_OUTPUT;             // Set as output

    GpioCtrlRegs.GPFLOCK.bit.GPIO168 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFMUX1.bit.GPIO168 = (GPIO_MULTIPLEX_GPIO >> 2);    // Set to GPIO functionality
    GpioCtrlRegs.GPFGMUX1.bit.GPIO168 = (GPIO_MULTIPLEX_GPIO & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO168 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    GpioCtrlRegs.GPFDIR.bit.GPIO168 = GPIO_OUTPUT;             // Set as output

    EDIS;

}
