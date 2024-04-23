//=================================================================================================
/// @file       TB_DAC.c
///
/// @brief
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
#include "TB_DAC.h"


//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Global functions
//-------------------------------------------------------------------------------------------------
//=== Function: DACInitAll ==========================================================================
///
/// @brief Function initialises the DAC-A,B,C modules
///
/// @param void
///
/// @return void
///
//=================================================================================================
void DACInitAll(void)
{

    EALLOW; // Cancel register write protection

    CpuSysRegs.PCLKCR16.bit.DAC_A = 1;    // Switch on the clock for the DAC module and wait 5 clocks
    __asm(" RPT #4 || NOP");
    DacaRegs.DACCTL.bit.DACREFSEL = DAC_REF_VREFHI;   // ADC VREFHI/VSSA are the reference voltage
    DacaRegs.DACCTL.bit.LOADMODE = DAC_SYNC_SYSCLK;   // Synchronise DAC value via SYSCLK
    DacaRegs.DACCTL.bit.SYNCSEL = DAC_EPWM1SYNCPER;   // ePWM1 loads the value from the DACVALS register into the DACVALA register
    DacaRegs.DACOUTEN.bit.DACOUTEN = DAC_ENABLE_OUTPUT;   // Switch on the output of the DAC - output at pin DACOUTA (ADCINA0)
    DacaRegs.DACVALS.bit.DACVALS = 4000;
    DELAY_US(500);

    CpuSysRegs.PCLKCR16.bit.DAC_B = 1;    // Switch on the clock for the DAC module and wait 5 clocks
    __asm(" RPT #4 || NOP");
    DacbRegs.DACCTL.bit.DACREFSEL = DAC_REF_VREFHI;   // ADC VREFHI/VSSA are the reference voltage
    DacbRegs.DACCTL.bit.LOADMODE = DAC_SYNC_SYSCLK;   // Synchronise DAC value via SYSCLK
    DacbRegs.DACCTL.bit.SYNCSEL = DAC_EPWM1SYNCPER;   // ePWM1 loads the value from the DACVALS register into the DACVALA register
    DacbRegs.DACOUTEN.bit.DACOUTEN = DAC_ENABLE_OUTPUT;   // Switch on the output of the DAC - output at pin DACOUTB (ADCINA1)
    DacbRegs.DACVALS.bit.DACVALS = 4000;
    DELAY_US(500);

    CpuSysRegs.PCLKCR16.bit.DAC_C = 1;    // Switch on the clock for the DAC module and wait 5 clocks
    __asm(" RPT #4 || NOP");
    DaccRegs.DACCTL.bit.DACREFSEL = DAC_REF_VREFHI;   // ADC VREFHI/VSSA are the reference voltage
    DaccRegs.DACCTL.bit.LOADMODE = DAC_SYNC_SYSCLK;   // Synchronise DAC value via SYSCLK
    DaccRegs.DACCTL.bit.SYNCSEL = DAC_EPWM1SYNCPER;   // ePWM1 loads the value from the DACVALS register into the DACVALA register
    DaccRegs.DACOUTEN.bit.DACOUTEN = DAC_ENABLE_OUTPUT;   // Switch on the output of the DAC - output at pin DACOUTC (ADCINB1)
    DaccRegs.DACVALS.bit.DACVALS = 4000;
    DELAY_US(500);

    EDIS;   // Set register write protection

}
