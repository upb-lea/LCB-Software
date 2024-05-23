//=================================================================================================
/// @file       TB_PWM.c
///
/// @brief      file contains variables and functions to configure all PWM modules.
///             PWM modules 1 to 16 are initialised.
///
/// @version    V1.1.0
///
/// @date       23-04-2024
///
/// @author     Vijay
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "TB_PWM.h"
#include "TB_GPIO.h"


//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Global functions
//-------------------------------------------------------------------------------------------------
//=== Function: PwmInitAll =====================================================================
///
/// @brief  functions to configure all PWM modules
///
/// @param  void
///
/// @return void
///
//=================================================================================================
void PwmInitAll(void)
{
    EALLOW;   // Disable register write protection
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // Switch off synchronization clock during configuration
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;   // Switch on clock for the PWM1 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm1Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_1;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_1;
    EPwm1Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM1 is the master module
    EPwm1Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm1Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm1Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm1Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm1Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm1Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm1Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm1Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm1Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm1Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm1Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm1Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm1Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm1Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm1Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm1Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm1Regs.TBCTR = 0;    // Set timer to 0

    EPwm1Regs.ETSEL.bit.SOCAEN = PWM_ET_SOC_ENABLE;
    EPwm1Regs.ETSEL.bit.SOCASEL = PWM_ET_CTR_ZERO;
    EPwm1Regs.ETPS.bit.SOCAPRD = PWM_ET_1ST;

    // ePWM 1A
    GpioCtrlRegs.GPELOCK.bit.GPIO145 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO145 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO145 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO145 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 1B
    GpioCtrlRegs.GPELOCK.bit.GPIO146 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO146 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO146 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO146 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor

    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;   // Switch on clock for the PWM2 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm2Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm2Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM2 is the master module
    EPwm2Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm2Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm2Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm2Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm2Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm2Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm2Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm2Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm2Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm2Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm2Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm2Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm2Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm2Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm2Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm2Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm2Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 2A
    GpioCtrlRegs.GPELOCK.bit.GPIO147 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO147 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO147 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO147 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 2B
    GpioCtrlRegs.GPELOCK.bit.GPIO148 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO148 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO148 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO148 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM3 = 1;   // Switch on clock for the PWM3 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm3Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm3Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM3 is the master module
    EPwm3Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm3Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm3Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm3Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm3Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm3Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm3Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm3Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm3Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm3Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm3Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm3Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm3Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm3Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm3Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm3Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm3Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 3A
    GpioCtrlRegs.GPELOCK.bit.GPIO149 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO149 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO149 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO149 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 3B
    GpioCtrlRegs.GPELOCK.bit.GPIO150 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO150 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO150 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO150 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM4 = 1;   // Switch on clock for the PWM4 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm4Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm4Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM4 is the master module
    EPwm4Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm4Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm4Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm4Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm4Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm4Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm4Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm4Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm4Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm4Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm4Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm4Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm4Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm4Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm4Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm4Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm4Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 4A
    GpioCtrlRegs.GPELOCK.bit.GPIO151 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO151 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO151 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO151 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 4B
    GpioCtrlRegs.GPELOCK.bit.GPIO152 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO152 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO152 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO152 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM5 = 1;   // Switch on clock for the PWM5 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm5Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm5Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM5 is the master module
    EPwm5Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm5Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm5Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm5Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm5Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm5Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm5Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm5Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm5Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm5Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm5Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm5Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm5Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm5Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm5Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm5Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm5Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 5A
    GpioCtrlRegs.GPELOCK.bit.GPIO153 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO153 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO153 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO153 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 5B
    GpioCtrlRegs.GPELOCK.bit.GPIO154 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO154 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO154 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO154 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM6 = 1;   // Switch on clock for the PWM6 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm6Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm6Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM6 is the master module
    EPwm6Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm6Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm6Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm6Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm6Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm6Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm6Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm6Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm6Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm6Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm6Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm6Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm6Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm6Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm6Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm6Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm6Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 6A
    GpioCtrlRegs.GPELOCK.bit.GPIO155 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO155 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO155 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO155 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 6B
    GpioCtrlRegs.GPELOCK.bit.GPIO156 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO156 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO156 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO156 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM7 = 1;   // Switch on clock for the PWM7 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm7Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm7Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM7 is the master module
    EPwm7Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm7Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm7Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm7Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm7Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm7Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm7Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm7Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm7Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm7Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm7Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm7Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm7Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm7Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm7Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm7Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm7Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm7Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm7Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 7A
    GpioCtrlRegs.GPELOCK.bit.GPIO157 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO157 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO157 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO157 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 7B
    GpioCtrlRegs.GPELOCK.bit.GPIO158 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO158 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO158 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO158 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM8 = 1;   // Switch on clock for the PWM8 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm8Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm8Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm8Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM8 is the master module
    EPwm8Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm8Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm8Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm8Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm8Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm8Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm8Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm8Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm8Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm8Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm8Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm8Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm8Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm8Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm8Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm8Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm8Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm8Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm8Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 8A
    GpioCtrlRegs.GPELOCK.bit.GPIO159 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO159 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO159 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO159 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 8B
    GpioCtrlRegs.GPFLOCK.bit.GPIO160 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFGMUX1.bit.GPIO160 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPFMUX1.bit.GPIO160 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO160 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM9 = 1;   // Switch on clock for the PWM9 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm9Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm9Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm9Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM9 is the master module
    EPwm9Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm9Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm9Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm9Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm9Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm9Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm9Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm9Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm9Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm9Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm9Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm9Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm9Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm9Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm9Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm9Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm9Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm9Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm9Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 9A
    GpioCtrlRegs.GPFLOCK.bit.GPIO161 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFGMUX1.bit.GPIO161 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPFMUX1.bit.GPIO161 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO161 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 9B
    GpioCtrlRegs.GPFLOCK.bit.GPIO162 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFGMUX1.bit.GPIO162 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPFMUX1.bit.GPIO162 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO162 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM10 = 1;   // Switch on clock for the PWM10 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm10Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm10Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm10Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM10 is the master module
    EPwm10Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm10Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm10Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm10Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm10Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm10Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm10Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm10Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm10Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm10Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm10Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm10Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm10Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm10Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm10Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm10Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm10Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm10Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm10Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 10A
    GpioCtrlRegs.GPFLOCK.bit.GPIO163 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFGMUX1.bit.GPIO163 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPFMUX1.bit.GPIO163 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO163 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 10B
    GpioCtrlRegs.GPFLOCK.bit.GPIO164 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFGMUX1.bit.GPIO164 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPFMUX1.bit.GPIO164 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO164 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM11 = 1;   // Switch on clock for the PWM11 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm11Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm11Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm11Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM11 is the master module
    EPwm11Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm11Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm11Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm11Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm11Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm11Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm11Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm11Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm11Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm11Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm11Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm11Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm11Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm11Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm11Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm11Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm11Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm11Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm11Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 11A
    GpioCtrlRegs.GPFLOCK.bit.GPIO165 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFGMUX1.bit.GPIO165 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPFMUX1.bit.GPIO165 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO165 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 11B
    GpioCtrlRegs.GPFLOCK.bit.GPIO166 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFGMUX1.bit.GPIO166 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPFMUX1.bit.GPIO166 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO166 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM12 = 1;   // Switch on clock for the PWM12 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm12Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm12Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm12Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM12 is the master module
    EPwm12Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm12Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm12Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm12Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm12Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm12Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm12Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm12Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm12Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm12Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm12Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm12Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm12Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm12Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm12Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm12Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm12Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm12Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm12Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 12A
    GpioCtrlRegs.GPFLOCK.bit.GPIO167 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFGMUX1.bit.GPIO167 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPFMUX1.bit.GPIO167 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO167 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 12B
    GpioCtrlRegs.GPFLOCK.bit.GPIO168 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPFGMUX1.bit.GPIO168 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPFMUX1.bit.GPIO168 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPFPUD.bit.GPIO168 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM13 = 1;   // Switch on clock for the PWM13 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm13Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm13Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm13Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM13 is the master module
    EPwm13Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm13Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm13Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm13Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm13Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm13Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm13Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm13Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm13Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm13Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm13Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm13Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm13Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm13Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm13Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm13Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm13Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm13Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm13Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 13A
    GpioCtrlRegs.GPELOCK.bit.GPIO137 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO137 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO137 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO137 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 13B
    GpioCtrlRegs.GPELOCK.bit.GPIO138 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO138 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO138 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO138 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM14 = 1;   // Switch on clock for the PWM14 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm14Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm14Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm14Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM14 is the master module
    EPwm14Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm14Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm14Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm14Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm14Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm14Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm14Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm14Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm14Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm14Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm14Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm14Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm14Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm14Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm14Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm14Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm14Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm14Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm14Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 14A
    GpioCtrlRegs.GPELOCK.bit.GPIO139 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO139 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO139 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO139 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 14B
    GpioCtrlRegs.GPELOCK.bit.GPIO140 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO140 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO140 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO140 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM15 = 1;   // Switch on clock for the PWM15 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm15Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm15Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm15Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM15 is the master module
    EPwm15Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm15Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm15Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm15Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm15Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm15Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm15Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm15Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm15Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm15Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm15Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm15Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm15Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm15Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm15Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm15Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm15Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm15Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm15Regs.TBCTR = 0;    // Set timer to 0
    // ePWM 15A
    GpioCtrlRegs.GPELOCK.bit.GPIO141 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO141 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO141 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO141 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 15B
    GpioCtrlRegs.GPELOCK.bit.GPIO142 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO142 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO142 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO142 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    //=================================================================================================
    CpuSysRegs.PCLKCR2.bit.EPWM16 = 1;   // Switch on clock for the PWM16 module and wait 5 clocks
    __asm(" RPT #4 || NOP");  // Wait for 4 NOP cycles
    EPwm16Regs.TBCTL.bit.CLKDIV    = PWM_CLK_DIV_128;    // Set the clock divider of the PWM module - PWM-CLOCK = SYSCLKOUT / (CLKDIV * HSPCLKDIV)
    EPwm16Regs.TBCTL.bit.HSPCLKDIV = PWM_HSPCLKDIV_14;
    EPwm16Regs.TBCTL.bit.PHSEN = PWM_TB_PHSEN_DISABLE;   // No synchronization because ePWM16 is the master module
    EPwm16Regs.TBPHS.bit.TBPHS = 0;    // No phase shift
    EPwm16Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;   // Generate synchronization pulse (SYNCOUT) if timer = 0
    EPwm16Regs.TBCTL2.bit.OSHTSYNCMODE = 0;    // Continuous synchronization mode
    EPwm16Regs.TBCTL.bit.CTRMODE = PWM_TB_COUNT_UP;    // Operating mode: count updown
    EPwm16Regs.TBCTL.bit.PRDLD = PWM_TB_IMMEDIATE;   // Apply value that is written in TBPRD immediately
    EPwm16Regs.TBPRD = PWM_PERIOD;    // Set period
    EPwm16Regs.CMPCTL.bit.SHDWAMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm16Regs.CMPCTL.bit.LOADAMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm16Regs.CMPA.bit.CMPA = 0;    // Set duty cycle to 0
    EPwm16Regs.AQCTLA.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm16Regs.AQCTLA.bit.CAU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm16Regs.CMPCTL.bit.SHDWBMODE = PWM_CC_IMMEDIATE;   // Only write to the compare register when the counter reaches the value 0
    //EPwm16Regs.CMPCTL.bit.LOADBMODE = PWM_CC_SHDW_CTR_ZERO;
    EPwm16Regs.CMPB.bit.CMPB = 0;    // Set duty cycle to 0
    EPwm16Regs.AQCTLB.bit.ZRO = PWM_AQ_SET;    // pin to high when TBCTR reaches the value CMP
    EPwm16Regs.AQCTLB.bit.CBU = PWM_AQ_CLEAR;    // pin to low when TBCTR reaches the value CMP
    EPwm16Regs.DBCTL.bit.OUT_MODE = PWM_DB_BOTH_BYPASSED; // p.2898
    EPwm16Regs.DBCTL.bit.OUTSWAP = PWM_DB_SWAP_NONE;
    EPwm16Regs.TBCTR = 0;    // Set timer to 0

    // ePWM 16A
    GpioCtrlRegs.GPELOCK.bit.GPIO143 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX1.bit.GPIO143 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX1.bit.GPIO143 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO143 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor
    // ePWM 16B
    GpioCtrlRegs.GPELOCK.bit.GPIO144 = GPIO_CONFIG_UNLOCK;            // Unlock configuration
    GpioCtrlRegs.GPEGMUX2.bit.GPIO144 = (GPIO_MULTIPLEX_EPWM >> 2);    // Set to PWM functionality
    GpioCtrlRegs.GPEMUX2.bit.GPIO144 = (GPIO_MULTIPLEX_EPWM & 0x03);
    GpioCtrlRegs.GPEPUD.bit.GPIO144 = GPIO_DISABLE_PULLUP;             // Disable pull-up resistor

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    EDIS; // Set register write protection
}

