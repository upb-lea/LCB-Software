//=================================================================================================
/// @file     TB_Functions.c
///
/// @brief    File contains functions and variables for testing all GPIOs, PWMs, DACs and ADCs
///           All GPIOs and PWMs are connected to LEDs.
///           Functions lights-ups the LEDs for visual checking of GPIOs and PWMs.
///           Functions also generate linearly increaseing DAC values and passes it through analog MUX...
///           finally checks for error ADC results and lights-ups the resp. Error LED if any error
///
/// @version  V1.1.0
///
/// @date     23-04-2024
///
/// @author   Vijay
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "TB_Functions.h"

//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------
long double OFFTIME = 10000, ONTIME = 500000;
uint16_t  Repeat_count = 3;
float32   ADC_error_buffer=0.96;
uint16_t  S=0,A2=0,A3=0,A4=0,A5=0,B0=0,B2=0,B3=0,B4=0,B5=0,C2=0,C3=0,C4=0,C5=0,D0=0,D1=0,D2=0,D3=0,D4=0,D5=0,IN14=0,IN15=0;
uint16_t  A2_Error_count=0,A3_Error_count=0,A4_Error_count=0,A5_Error_count=0;
uint16_t  B0_Error_count=0,B2_Error_count=0,B3_Error_count=0,B4_Error_count=0,B5_Error_count=0;
uint16_t  C2_Error_count=0,C3_Error_count=0,C4_Error_count=0,C5_Error_count=0;
uint16_t  D0_Error_count=0,D1_Error_count=0,D2_Error_count=0,D3_Error_count=0,D4_Error_count=0,D5_Error_count=0,IN14_Error_count=0,IN15_Error_count=0;

//-------------------------------------------------------------------------------------------------
// Global functions
//-------------------------------------------------------------------------------------------------

//=== Function: Error_LEDs_Check ==========================================================================
///
/// @brief  Function to light-up all Error LEDs connected to GPIOs, one at a time
///         repeats the process for 3 times
///
/// @param  void
///
/// @return void
///
//=================================================================================================
void Error_LEDs_Check(void)
{
    EALLOW;
    for(uint16_t j = 0; j < Repeat_count; j++)
    {
        for(uint16_t i = 1; i < 30; i++)
        {
            Error_LEDs_On(i);
            DELAY_US(ONTIME);
            Error_LEDs_Off(i);
            DELAY_US(OFFTIME);
        }
    }
    EDIS;
}

//=== Function: PWM_LEDs_Check ==========================================================================
///
/// @brief  Function to light-up all PWM LEDs connected to GPIOs, four at a time
///         repeats the process for 3 times
///
/// @param  void
///
/// @return void
///
//=================================================================================================
void PWM_LEDs_Check(void)
{
    EALLOW;
    for(uint16_t j = 0; j < Repeat_count; j++)
    {
        for(uint16_t i = 0; i < 8; i++)
        {
            PWM_LEDs_On(i);
            DELAY_US(ONTIME);
            PWM_LEDs_Off(i);
            DELAY_US(OFFTIME);
        }
    }
    EDIS;
}

//=== Function:GPIOLEDs_Check==========================================================================
///
/// @brief  Function to light-up the First LEDs of all the Group-A to Group-H and followed...
///         by the next LEDs till the last LEDs of all groups.
///         repeats the process for 16 times
///
/// @param  void
///
/// @return void
///
//=================================================================================================
void GPIOLEDs_Check(void)
{
    EALLOW;
    for(uint16_t j = 0; j < 16; j++)
    {
        for(uint16_t i = 0; i < 10; i++)
        {
            GPIOLEDs_On(i);
            DELAY_US(ONTIME);
            GPIOLEDs_Off(i);
            DELAY_US(OFFTIME);
        }
    }
    EDIS;
}

//=== Function:ADCINs_Check==========================================================================
///
/// @brief  DACs generate a linearly increased analog value which will be read by ADCINs,
///         if the code detects any error/mismatch in data read by ADCIN to that of DAC generated value,
///         it will light up the respective Error LED. The ADCIN values are simultaneously sent to ePWMs,
///         which control the brightness of PWM LEDs, making them gradually brighter.
///         repeats the process for 3 times
///
/// @param  void
///
/// @return void
///
//=================================================================================================
void ADCINs_Check(void)
{
    EALLOW;
    for(uint16_t k = 0; k < Repeat_count; k++)
    {
        for(uint16_t i = 0; i < 32; i++)
        {
            Mux_Select(i);
            for(uint16_t j = 0; j<3900; j++)
            {
                DacaRegs.DACVALS.bit.DACVALS = j;
                DacbRegs.DACVALS.bit.DACVALS = j;
                DaccRegs.DACVALS.bit.DACVALS = j;
                ADCtoPWM(i);
                if(j == 1000 || j == 2000 || j == 3000 || j>3898)
                    ADC_ErrorCheck(i);
                DELAY_US(500);
            }
            ADCtoPWM(32);
            Mux_Select(23);
        }
    }
    EDIS;
}

//=== Function: Hardware_Error_Detection_Check ==========================================================================
///
/// @brief  Function to check the all Hardware Error Detections
///
/// @param  void
///
/// @return void
///
//===========================================================================================================
void Hardware_Error_Detection_Check(void)
{
    EALLOW;
    for(uint16_t i = 0; i < Repeat_count; i++)
    {
        Mux_Select(0);
        DELAY_US(ONTIME);
        GpioDataRegs.GPDCLEAR.bit.GPIO98 = 1;
        DELAY_US(OFFTIME);
        Mux_Select(23);

        Mux_Select(5);
        DELAY_US(ONTIME);
        GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;
        DELAY_US(OFFTIME);
        Mux_Select(23);

        Mux_Select(11);
        DELAY_US(ONTIME);
        GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
        DELAY_US(OFFTIME);
        Mux_Select(23);

        Mux_Select(13);
        DELAY_US(ONTIME);
        GpioDataRegs.GPDCLEAR.bit.GPIO97 = 1;
        DELAY_US(OFFTIME);
        Mux_Select(23);
        DELAY_US(OFFTIME);
        GpioDataRegs.GPDSET.bit.GPIO98  = 1;
        GpioDataRegs.GPASET.bit.GPIO10  = 1;
        GpioDataRegs.GPASET.bit.GPIO11  = 1;
        GpioDataRegs.GPDSET.bit.GPIO97  = 1;
        DELAY_US(ONTIME);
    }
    EDIS;
}

//=== Function: ADC_ErrorCheck ==========================================================================
///
/// @brief  Function to detect errors in ADC results and accordingly indicates error through Error_LEDs
///
/// @param  void
///
/// @return void
///
//===========================================================================================================
void ADC_ErrorCheck(int i)
{
    switch(i)
    {
        case 0:
            if(A2 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { A2_Error_count++; }
            if(A2_Error_count > 2) { GpioDataRegs.GPBCLEAR.bit.GPIO47 = 1; }
            break;
        case 1:
            if(A3 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { A3_Error_count++; }
            if(A3_Error_count > 2) { GpioDataRegs.GPCCLEAR.bit.GPIO73 = 1; }
            break;
        case 2:
            if(A4 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { A4_Error_count++; }
            if(A4_Error_count > 2) { GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; }
            break;
        case 3:
            if(A5 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { A5_Error_count++; }
            if(A5_Error_count > 2) { GpioDataRegs.GPACLEAR.bit.GPIO23 = 1; }
            break;
        case 4:
            if(B0 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { B0_Error_count++; }
            if(B0_Error_count > 2) { GpioDataRegs.GPACLEAR.bit.GPIO26 = 1; }
            break;
        case 5:
            if(B2 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { B2_Error_count++; }
            if(B2_Error_count > 2) { GpioDataRegs.GPACLEAR.bit.GPIO25 = 1; }
            break;
        case 6:
            if(B3 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { B3_Error_count++; }
            if(B3_Error_count > 2) { GpioDataRegs.GPDCLEAR.bit.GPIO102 = 1; }
            break;
        case 7:
            if(B4 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { B4_Error_count++; }
            if(B4_Error_count > 2) { GpioDataRegs.GPDCLEAR.bit.GPIO101 = 1; }
            break;
        case 8:
            if(B5 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { B5_Error_count++; }
            if(B5_Error_count > 2) { GpioDataRegs.GPACLEAR.bit.GPIO18 = 1; }
            break;
        case 9:
            if(C2 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { C2_Error_count++; }
            if(C2_Error_count > 2) { GpioDataRegs.GPACLEAR.bit.GPIO17 = 1; }
            break;
        case 10:
            if(C3 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { C3_Error_count++; }
            if(C3_Error_count > 2) { GpioDataRegs.GPACLEAR.bit.GPIO13 = 1; }
            break;
        case 11:
            if(C4 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { C4_Error_count++; }
            if(C4_Error_count > 2) { GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; }
            break;
        case 12:
            if(C5 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { C5_Error_count++; }
            if(C5_Error_count > 2) { GpioDataRegs.GPACLEAR.bit.GPIO4 = 1; }
            break;
        case 13:
            if(D0 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { D0_Error_count++; }
            if(D0_Error_count > 2) { GpioDataRegs.GPDCLEAR.bit.GPIO109 = 1; }
            break;
        case 14:
            if(D1 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { D1_Error_count++; }
            if(D1_Error_count > 2) { GpioDataRegs.GPDCLEAR.bit.GPIO110 = 1; }
            break;
        case 15:
            if(D2 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { D2_Error_count++; }
            if(D2_Error_count > 2) { GpioDataRegs.GPDCLEAR.bit.GPIO106 = 1; }
            break;
        case 16:
            if(D3 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { D3_Error_count++; }
            if(D3_Error_count > 2) { GpioDataRegs.GPDCLEAR.bit.GPIO108 = 1; }
            break;
        case 17:
            if(D4 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { D4_Error_count++; }
            if(D4_Error_count > 2) { GpioDataRegs.GPDCLEAR.bit.GPIO105 = 1; }
            break;
        case 18:
            if(D5 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { D5_Error_count++; }
            if(D5_Error_count > 2) { GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1; }
            break;
        case 19:
            if(IN14 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { IN14_Error_count++; }
            if(IN14_Error_count > 2) { GpioDataRegs.GPACLEAR.bit.GPIO22 = 1; }
            break;
        case 20:
            if(IN15 < ADC_error_buffer*DacaRegs.DACVALS.bit.DACVALS) { IN15_Error_count++; }
            if(IN15_Error_count > 2) { GpioDataRegs.GPACLEAR.bit.GPIO27 = 1; }
            break;
        default:
            break;
    }
}

//=== Function: Error_LEDs_Off ==========================================================================
///
/// @brief  Function to turn-OFF Error_LEDs one at a time
///
/// @param  void
///
/// @return void
///
//===========================================================================================================
void Error_LEDs_Off(int i)
{
    switch(i)
    {
        case 1: GpioDataRegs.GPBSET.bit.GPIO47 = 1; break;
        case 2: GpioDataRegs.GPCSET.bit.GPIO73 = 1; break;
        case 3: GpioDataRegs.GPBSET.bit.GPIO34 = 1; break;
        case 4: GpioDataRegs.GPASET.bit.GPIO23 = 1; break;
        case 5: GpioDataRegs.GPASET.bit.GPIO26 = 1; break;
        case 6: GpioDataRegs.GPASET.bit.GPIO25 = 1; break;
        case 7: GpioDataRegs.GPDSET.bit.GPIO102 = 1; break;
        case 8: GpioDataRegs.GPDSET.bit.GPIO101 = 1; break;
        case 9: GpioDataRegs.GPASET.bit.GPIO18 = 1; break;
        case 10: GpioDataRegs.GPASET.bit.GPIO17 = 1; break;
        case 11: GpioDataRegs.GPASET.bit.GPIO13 = 1; break;
        case 12: GpioDataRegs.GPASET.bit.GPIO0 = 1; break;
        case 13: GpioDataRegs.GPASET.bit.GPIO4 = 1; break;
        case 14: GpioDataRegs.GPDSET.bit.GPIO109 = 1; break;
        case 15: GpioDataRegs.GPDSET.bit.GPIO110 = 1; break;
        case 16: GpioDataRegs.GPDSET.bit.GPIO106 = 1; break;
        case 17: GpioDataRegs.GPDSET.bit.GPIO108 = 1; break;
        case 18: GpioDataRegs.GPDSET.bit.GPIO105 = 1; break;
        case 19: GpioDataRegs.GPBSET.bit.GPIO33 = 1; break;
        case 20: GpioDataRegs.GPASET.bit.GPIO22 = 1; break;
        case 21: GpioDataRegs.GPASET.bit.GPIO27 = 1; break;
        case 22: GpioDataRegs.GPASET.bit.GPIO24 = 1; break;
        case 23: GpioDataRegs.GPDSET.bit.GPIO103 = 1; break;
        case 24: GpioDataRegs.GPDSET.bit.GPIO100 = 1; break;
        case 25: GpioDataRegs.GPASET.bit.GPIO19 = 1; break;
        case 26: GpioDataRegs.GPASET.bit.GPIO16 = 1; break;
        case 27: GpioDataRegs.GPASET.bit.GPIO12 = 1; break;
        case 28: GpioDataRegs.GPASET.bit.GPIO1 = 1; break;
        case 29: GpioDataRegs.GPCSET.bit.GPIO70 = 1; break;
        default:  break;
    }
}

//=== Function: Error_LEDs_On ==========================================================================
///
/// @brief  Function to turn-ON Error_LEDs one at a time
///
/// @param  void
///
/// @return void
///
//===========================================================================================================
void Error_LEDs_On(int i)
{
    switch(i)
    {
        case 1: GpioDataRegs.GPBCLEAR.bit.GPIO47 = 1; break;
        case 2: GpioDataRegs.GPCCLEAR.bit.GPIO73 = 1; break;
        case 3: GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; break;
        case 4: GpioDataRegs.GPACLEAR.bit.GPIO23 = 1; break;
        case 5: GpioDataRegs.GPACLEAR.bit.GPIO26 = 1; break;
        case 6: GpioDataRegs.GPACLEAR.bit.GPIO25 = 1; break;
        case 7: GpioDataRegs.GPDCLEAR.bit.GPIO102 = 1; break;
        case 8: GpioDataRegs.GPDCLEAR.bit.GPIO101 = 1; break;
        case 9: GpioDataRegs.GPACLEAR.bit.GPIO18 = 1; break;
        case 10: GpioDataRegs.GPACLEAR.bit.GPIO17 = 1; break;
        case 11: GpioDataRegs.GPACLEAR.bit.GPIO13 = 1; break;
        case 12: GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; break;
        case 13: GpioDataRegs.GPACLEAR.bit.GPIO4 = 1; break;
        case 14: GpioDataRegs.GPDCLEAR.bit.GPIO109 = 1; break;
        case 15: GpioDataRegs.GPDCLEAR.bit.GPIO110 = 1; break;
        case 16: GpioDataRegs.GPDCLEAR.bit.GPIO106 = 1; break;
        case 17: GpioDataRegs.GPDCLEAR.bit.GPIO108 = 1; break;
        case 18: GpioDataRegs.GPDCLEAR.bit.GPIO105 = 1; break;
        case 19: GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1; break;
        case 20: GpioDataRegs.GPACLEAR.bit.GPIO22 = 1; break;
        case 21: GpioDataRegs.GPACLEAR.bit.GPIO27 = 1; break;
        case 22: GpioDataRegs.GPACLEAR.bit.GPIO24 = 1; break;
        case 23: GpioDataRegs.GPDCLEAR.bit.GPIO103 = 1; break;
        case 24: GpioDataRegs.GPDCLEAR.bit.GPIO100 = 1; break;
        case 25: GpioDataRegs.GPACLEAR.bit.GPIO19 = 1; break;
        case 26: GpioDataRegs.GPACLEAR.bit.GPIO16 = 1; break;
        case 27: GpioDataRegs.GPACLEAR.bit.GPIO12 = 1; break;
        case 28: GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; break;
        case 29: GpioDataRegs.GPCCLEAR.bit.GPIO70 = 1; break;
        default:  break;
    }
}

//=== Function: PWM_LEDs_On ==========================================================================
///
/// @brief  Function to turn-ON PWM_LEDs four at a time
///
/// @param  void
///
/// @return void
///
//===========================================================================================================
void PWM_LEDs_On(int i)
{
    switch(i)
    {
        case 0:
            GpioDataRegs.GPESET.bit.GPIO145 = 1;
            GpioDataRegs.GPESET.bit.GPIO153 = 1;
            GpioDataRegs.GPFSET.bit.GPIO161 = 1;
            GpioDataRegs.GPESET.bit.GPIO137 = 1;
            break;
        case 1:
            GpioDataRegs.GPESET.bit.GPIO146 = 1;
            GpioDataRegs.GPESET.bit.GPIO154 = 1;
            GpioDataRegs.GPFSET.bit.GPIO162 = 1;
            GpioDataRegs.GPESET.bit.GPIO138 = 1;
            break;
        case 2:
            GpioDataRegs.GPESET.bit.GPIO147 = 1;
            GpioDataRegs.GPESET.bit.GPIO155 = 1;
            GpioDataRegs.GPFSET.bit.GPIO163 = 1;
            GpioDataRegs.GPESET.bit.GPIO139 = 1;
            break;
        case 3:
            GpioDataRegs.GPESET.bit.GPIO148 = 1;
            GpioDataRegs.GPESET.bit.GPIO156 = 1;
            GpioDataRegs.GPFSET.bit.GPIO164 = 1;
            GpioDataRegs.GPESET.bit.GPIO140 = 1;
            break;
        case 4:
            GpioDataRegs.GPESET.bit.GPIO149 = 1;
            GpioDataRegs.GPESET.bit.GPIO157 = 1;
            GpioDataRegs.GPFSET.bit.GPIO165 = 1;
            GpioDataRegs.GPESET.bit.GPIO141 = 1;
            break;
        case 5:
            GpioDataRegs.GPESET.bit.GPIO150 = 1;
            GpioDataRegs.GPESET.bit.GPIO158 = 1;
            GpioDataRegs.GPFSET.bit.GPIO166 = 1;
            GpioDataRegs.GPESET.bit.GPIO142 = 1;
            break;
        case 6:
            GpioDataRegs.GPESET.bit.GPIO151 = 1;
            GpioDataRegs.GPESET.bit.GPIO159 = 1;
            GpioDataRegs.GPFSET.bit.GPIO167 = 1;
            GpioDataRegs.GPESET.bit.GPIO143 = 1;
            break;
        case 7:
            GpioDataRegs.GPESET.bit.GPIO152 = 1;
            GpioDataRegs.GPFSET.bit.GPIO160 = 1;
            GpioDataRegs.GPFSET.bit.GPIO168 = 1;
            GpioDataRegs.GPESET.bit.GPIO144 = 1;
            break;
        default:
            break;
    }
}

//=== Function: PWM_LEDs_Off ==========================================================================
///
/// @brief  Function to turn-ON PWM_LEDs four at a time
///
/// @param  void
///
/// @return void
///
//===========================================================================================================
void PWM_LEDs_Off(int i)
{
    switch(i)
    {
        case 0:
            GpioDataRegs.GPECLEAR.bit.GPIO145 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO153 = 1;
            GpioDataRegs.GPFCLEAR.bit.GPIO161 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO137 = 1;
            break;
        case 1:
            GpioDataRegs.GPECLEAR.bit.GPIO146 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO154 = 1;
            GpioDataRegs.GPFCLEAR.bit.GPIO162 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO138 = 1;
            break;
        case 2:
            GpioDataRegs.GPECLEAR.bit.GPIO147 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO155 = 1;
            GpioDataRegs.GPFCLEAR.bit.GPIO163 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO139 = 1;
            break;
        case 3:
            GpioDataRegs.GPECLEAR.bit.GPIO148 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO156 = 1;
            GpioDataRegs.GPFCLEAR.bit.GPIO164 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO140 = 1;
            break;
        case 4:
            GpioDataRegs.GPECLEAR.bit.GPIO149 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO157 = 1;
            GpioDataRegs.GPFCLEAR.bit.GPIO165 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO141 = 1;
            break;
        case 5:
            GpioDataRegs.GPECLEAR.bit.GPIO150 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO158 = 1;
            GpioDataRegs.GPFCLEAR.bit.GPIO166 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO142 = 1;
            break;
        case 6:
            GpioDataRegs.GPECLEAR.bit.GPIO151 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO159 = 1;
            GpioDataRegs.GPFCLEAR.bit.GPIO167 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO143 = 1;
            break;
        case 7:
            GpioDataRegs.GPECLEAR.bit.GPIO152 = 1;
            GpioDataRegs.GPFCLEAR.bit.GPIO160 = 1;
            GpioDataRegs.GPFCLEAR.bit.GPIO168 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO144 = 1;
            break;
        default:
            break;
    }
}

//=== Function: Mux_Select ==========================================================================
///
/// @brief  Function to set Mux Select pins for passing DACOUT to ADCIN
///
/// @param  void
///
/// @return void
///
//===========================================================================================================
void Mux_Select(int i)
{
    switch (i)
    {
        case 0:
            GpioDataRegs.GPECLEAR.bit.GPIO136 = 1;
            GpioDataRegs.GPESET.bit.GPIO132 = 1;
            GpioDataRegs.GPESET.bit.GPIO131 = 1;
            S = 0;
            break;
        case 1:
            GpioDataRegs.GPESET.bit.GPIO136 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO132 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO131 = 1;
            S = 1;
            break;
        case 2:
            GpioDataRegs.GPDCLEAR.bit.GPIO126 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO128 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO130 = 1;
            S = 2;
            break;
        case 3:
            GpioDataRegs.GPDCLEAR.bit.GPIO126 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO128 = 1;
            GpioDataRegs.GPESET.bit.GPIO130 = 1;
            S = 3;
            break;
        case 4:
            GpioDataRegs.GPECLEAR.bit.GPIO136 = 1;
            GpioDataRegs.GPESET.bit.GPIO132 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO131 = 1;
            S = 4;
            break;
        case 5:
            GpioDataRegs.GPBSET.bit.GPIO44 = 1;
            GpioDataRegs.GPBSET.bit.GPIO57 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1;
            S = 5;
            break;
        case 6:
            GpioDataRegs.GPBSET.bit.GPIO44 = 1;
            GpioDataRegs.GPBSET.bit.GPIO57 = 1;
            GpioDataRegs.GPBSET.bit.GPIO55 = 1;
            S = 6;
            break;
        case 7:
            GpioDataRegs.GPDSET.bit.GPIO126 = 1;
            GpioDataRegs.GPESET.bit.GPIO128 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO130 = 1;
            S = 7;
            break;
        case 8:
            GpioDataRegs.GPDSET.bit.GPIO126 = 1;
            GpioDataRegs.GPESET.bit.GPIO128 = 1;
            GpioDataRegs.GPESET.bit.GPIO130 = 1;
            S = 8;
            break;
        case 9:
            GpioDataRegs.GPBSET.bit.GPIO44 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1;
            S = 9;
            break;
        case 10:
            GpioDataRegs.GPBSET.bit.GPIO44 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;
            GpioDataRegs.GPBSET.bit.GPIO55 = 1;
            S = 10;
            break;
        case 11:
            GpioDataRegs.GPDSET.bit.GPIO126 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO128 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO130 = 1;
            S = 11;
            break;
        case 12:
            GpioDataRegs.GPDSET.bit.GPIO126 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO128 = 1;
            GpioDataRegs.GPESET.bit.GPIO130 = 1;
            S = 12;
            break;
        case 13:
            GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
            GpioDataRegs.GPBSET.bit.GPIO57 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1;
            S = 13;
            break;
        case 14:
            GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
            GpioDataRegs.GPBSET.bit.GPIO57 = 1;
            GpioDataRegs.GPBSET.bit.GPIO55 = 1;
            S = 14;
            break;
        case 15:
            GpioDataRegs.GPDCLEAR.bit.GPIO126 = 1;
            GpioDataRegs.GPESET.bit.GPIO128 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO130 = 1;
            S = 15;
            break;
        case 16:
            GpioDataRegs.GPDCLEAR.bit.GPIO126 = 1;
            GpioDataRegs.GPESET.bit.GPIO128 = 1;
            GpioDataRegs.GPESET.bit.GPIO130 = 1;
            S = 16;
            break;
        case 17:
            GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1;
            S = 17;
            break;
        case 18:
            GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;
            GpioDataRegs.GPBSET.bit.GPIO55 = 1;
            S = 18;
            break;
        case 19:
            GpioDataRegs.GPESET.bit.GPIO136 = 1;
            GpioDataRegs.GPESET.bit.GPIO132 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO131 = 1;
            S = 19;
            break;
        case 20:
            GpioDataRegs.GPESET.bit.GPIO136 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO132 = 1;
            GpioDataRegs.GPESET.bit.GPIO131 = 1;
            S = 20;
            break;
        case 23:
            GpioDataRegs.GPDSET.bit.GPIO126 = 1;
            GpioDataRegs.GPESET.bit.GPIO128 = 1;
            GpioDataRegs.GPESET.bit.GPIO130 = 1;
            GpioDataRegs.GPESET.bit.GPIO136 = 1;
            GpioDataRegs.GPESET.bit.GPIO132 = 1;
            GpioDataRegs.GPESET.bit.GPIO131 = 1;
            GpioDataRegs.GPBSET.bit.GPIO44 = 1;
            GpioDataRegs.GPBSET.bit.GPIO57 = 1;
            GpioDataRegs.GPBSET.bit.GPIO55 = 1;
            A2_Error_count = 0;
            A3_Error_count = 0;
            A4_Error_count = 0;
            A5_Error_count = 0;
            B0_Error_count = 0;
            B2_Error_count = 0;
            B3_Error_count = 0;
            B4_Error_count = 0;
            B5_Error_count = 0;
            C2_Error_count = 0;
            C3_Error_count = 0;
            C4_Error_count = 0;
            C5_Error_count = 0;
            D0_Error_count = 0;
            D1_Error_count = 0;
            D2_Error_count = 0;
            D3_Error_count = 0;
            D4_Error_count = 0;
            D5_Error_count = 0;
            IN14_Error_count = 0;
            IN15_Error_count = 0;
            break;
        default:
            break;
    }
}

//=== Function: ADCtoPWM ==========================================================================
///
/// @brief  Function to store the ADC result and also pass it to PWM compares for adjusting brightness of PWM_LEDs
///
/// @param  void
///
/// @return void
///
//===========================================================================================================
void ADCtoPWM(int i)
{
    switch(i)
    {
        case 0:
            EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD * powf((AdcaResultRegs.ADCRESULT2 / 4095.0), 2.0);
            A2 = AdcaResultRegs.ADCRESULT2;
            break;
        case 1:
            EPwm1Regs.CMPB.bit.CMPB = EPwm1Regs.TBPRD * powf((AdcaResultRegs.ADCRESULT3 / 4095.0), 2.0);
            A3 = AdcaResultRegs.ADCRESULT3;
            break;
        case 2:
            EPwm2Regs.CMPA.bit.CMPA = EPwm2Regs.TBPRD * powf((AdcaResultRegs.ADCRESULT4 / 4095.0), 2.0);
            A4 = AdcaResultRegs.ADCRESULT4;
            break;
        case 3:
            EPwm2Regs.CMPB.bit.CMPB = EPwm2Regs.TBPRD * powf((AdcaResultRegs.ADCRESULT5 / 4095.0), 2.0);
            A5 = AdcaResultRegs.ADCRESULT5;
            break;
        case 4:
            EPwm3Regs.CMPA.bit.CMPA = EPwm3Regs.TBPRD * powf((AdcbResultRegs.ADCRESULT0 / 4095.0), 2.0);
            B0 = AdcbResultRegs.ADCRESULT0;
            break;
        case 5:
            EPwm3Regs.CMPB.bit.CMPB = EPwm3Regs.TBPRD * powf((AdcbResultRegs.ADCRESULT2 / 4095.0), 2.0);
            B2 = AdcbResultRegs.ADCRESULT2;
            break;
        case 6:
            EPwm4Regs.CMPA.bit.CMPA = EPwm4Regs.TBPRD * powf((AdcbResultRegs.ADCRESULT3 / 4095.0), 2.0);
            B3 = AdcbResultRegs.ADCRESULT3;
            break;
        case 7:
            EPwm4Regs.CMPB.bit.CMPB = EPwm4Regs.TBPRD * powf((AdcbResultRegs.ADCRESULT4 / 4095.0), 2.0);
            B4 = AdcbResultRegs.ADCRESULT4;
            break;
        case 8:
            EPwm5Regs.CMPA.bit.CMPA = EPwm5Regs.TBPRD * powf((AdcbResultRegs.ADCRESULT5 / 4095.0), 2.0);
            B5 = AdcbResultRegs.ADCRESULT5;
            break;
        case 9:
            EPwm5Regs.CMPB.bit.CMPB = EPwm5Regs.TBPRD * powf((AdccResultRegs.ADCRESULT2 / 4095.0), 2.0);
            C2 = AdccResultRegs.ADCRESULT2;
            break;
        case 10:
            EPwm6Regs.CMPA.bit.CMPA = EPwm6Regs.TBPRD * powf((AdccResultRegs.ADCRESULT3 / 4095.0), 2.0);
            C3 = AdccResultRegs.ADCRESULT3;
            break;
        case 11:
            EPwm6Regs.CMPB.bit.CMPB = EPwm6Regs.TBPRD * powf((AdccResultRegs.ADCRESULT4 / 4095.0), 2.0);
            C4 = AdccResultRegs.ADCRESULT4;
            break;
        case 12:
            EPwm7Regs.CMPA.bit.CMPA = EPwm7Regs.TBPRD * powf((AdccResultRegs.ADCRESULT5 / 4095.0), 2.0);
            C5 = AdccResultRegs.ADCRESULT5;
            break;
        case 13:
            EPwm7Regs.CMPB.bit.CMPB = EPwm7Regs.TBPRD * powf((AdcdResultRegs.ADCRESULT0 / 4095.0), 2.0);
            D0 = AdcdResultRegs.ADCRESULT0;
            break;
        case 14:
            EPwm8Regs.CMPA.bit.CMPA = EPwm8Regs.TBPRD * powf((AdcdResultRegs.ADCRESULT1 / 4095.0), 2.0);
            D1 = AdcdResultRegs.ADCRESULT1;
            break;
        case 15:
            EPwm8Regs.CMPB.bit.CMPB = EPwm8Regs.TBPRD * powf((AdcdResultRegs.ADCRESULT2 / 4095.0), 2.0);
            D2 = AdcdResultRegs.ADCRESULT2;
            break;
        case 16:
            EPwm9Regs.CMPA.bit.CMPA = EPwm9Regs.TBPRD * powf((AdcdResultRegs.ADCRESULT3 / 4095.0), 2.0);
            D3 = AdcdResultRegs.ADCRESULT3;
            break;
        case 17:
            EPwm9Regs.CMPB.bit.CMPB = EPwm9Regs.TBPRD * powf((AdcdResultRegs.ADCRESULT4 / 4095.0), 2.0);
            D4 = AdcdResultRegs.ADCRESULT4;
            break;
        case 18:
            EPwm10Regs.CMPA.bit.CMPA = EPwm10Regs.TBPRD * powf((AdcdResultRegs.ADCRESULT5 / 4095.0), 2.0);
            D5 = AdcdResultRegs.ADCRESULT5;
            break;
        case 19:
            EPwm10Regs.CMPB.bit.CMPB = EPwm10Regs.TBPRD * powf((AdcaResultRegs.ADCRESULT14 / 4095.0), 2.0);
            IN14 = AdcaResultRegs.ADCRESULT14;
            break;
        case 20:
            EPwm11Regs.CMPA.bit.CMPA = EPwm11Regs.TBPRD * powf((AdcaResultRegs.ADCRESULT15 / 4095.0), 2.0);
            IN15 = AdcaResultRegs.ADCRESULT15;
            break;
        case 21:
            EPwm11Regs.CMPB.bit.CMPB = EPwm11Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 22:
            EPwm12Regs.CMPA.bit.CMPA = EPwm12Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 23:
            EPwm12Regs.CMPB.bit.CMPB = EPwm12Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 24:
            EPwm13Regs.CMPA.bit.CMPA = EPwm13Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 25:
            EPwm13Regs.CMPB.bit.CMPB = EPwm13Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 26:
            EPwm14Regs.CMPA.bit.CMPA = EPwm14Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 27:
            EPwm14Regs.CMPB.bit.CMPB = EPwm14Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 28:
            EPwm15Regs.CMPA.bit.CMPA = EPwm15Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 29:
            EPwm15Regs.CMPB.bit.CMPB = EPwm15Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 30:
            EPwm16Regs.CMPA.bit.CMPA = EPwm16Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 31:
            EPwm16Regs.CMPB.bit.CMPB = EPwm16Regs.TBPRD * powf((DacaRegs.DACVALS.bit.DACVALS / 4095.0), 2.0);
            break;
        case 32:
            EPwm1Regs.CMPA.bit.CMPA = 0;
            EPwm1Regs.CMPB.bit.CMPB = 0;
            EPwm2Regs.CMPA.bit.CMPA = 0;
            EPwm2Regs.CMPB.bit.CMPB = 0;
            EPwm3Regs.CMPA.bit.CMPA = 0;
            EPwm3Regs.CMPB.bit.CMPB = 0;
            EPwm4Regs.CMPA.bit.CMPA = 0;
            EPwm4Regs.CMPB.bit.CMPB = 0;
            EPwm5Regs.CMPA.bit.CMPA = 0;
            EPwm5Regs.CMPB.bit.CMPB = 0;
            EPwm6Regs.CMPA.bit.CMPA = 0;
            EPwm6Regs.CMPB.bit.CMPB = 0;
            EPwm7Regs.CMPA.bit.CMPA = 0;
            EPwm7Regs.CMPB.bit.CMPB = 0;
            EPwm8Regs.CMPA.bit.CMPA = 0;
            EPwm8Regs.CMPB.bit.CMPB = 0;
            EPwm9Regs.CMPA.bit.CMPA = 0;
            EPwm9Regs.CMPB.bit.CMPB = 0;
            EPwm10Regs.CMPA.bit.CMPA = 0;
            EPwm10Regs.CMPB.bit.CMPB = 0;
            EPwm11Regs.CMPA.bit.CMPA = 0;
            EPwm11Regs.CMPB.bit.CMPB = 0;
            EPwm12Regs.CMPA.bit.CMPA = 0;
            EPwm12Regs.CMPB.bit.CMPB = 0;
            EPwm13Regs.CMPA.bit.CMPA = 0;
            EPwm13Regs.CMPB.bit.CMPB = 0;
            EPwm14Regs.CMPA.bit.CMPA = 0;
            EPwm14Regs.CMPB.bit.CMPB = 0;
            EPwm15Regs.CMPA.bit.CMPA = 0;
            EPwm15Regs.CMPB.bit.CMPB = 0;
            EPwm16Regs.CMPA.bit.CMPA = 0;
            EPwm16Regs.CMPB.bit.CMPB = 0;
            break;
        default:
            break;
    }
}

//=== Function: GPIOLEDs_On ==========================================================================
///
/// @brief  Function to turn-ON all fisrt LEDs in all Groups at a time, followed by second LEDs and so on
///
/// @param  void
///
/// @return void
///
//===========================================================================================================
void GPIOLEDs_On(int i)
{
    switch (i)
    {
        case 0:
            GpioDataRegs.GPDCLEAR.bit.GPIO116 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO38 = 1;
            GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO85 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO125 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO72 = 1;
            break;
        case 1:
            GpioDataRegs.GPDCLEAR.bit.GPIO121 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1;
            GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO69 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO37 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO131 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO71 = 1;
            break;
        case 2:
            GpioDataRegs.GPDCLEAR.bit.GPIO117 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO134 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO77 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO120 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO51 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO132 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO87 = 1;
            break;
        case 3:
            GpioDataRegs.GPCCLEAR.bit.GPIO83 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO119 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO53 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO136 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO86 = 1;
            break;
        case 4:
            GpioDataRegs.GPCCLEAR.bit.GPIO81 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO124 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO122 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO54 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO80 = 1;
            break;
        case 5:
            GpioDataRegs.GPCCLEAR.bit.GPIO84 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO115 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO114 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO56 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO64 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO65 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO82 = 1;
            break;
        case 6:
            GpioDataRegs.GPBCLEAR.bit.GPIO46 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO123 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO112 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO66 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO90 = 1;
            break;
        case 7:
            GpioDataRegs.GPCCLEAR.bit.GPIO88 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO130 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO118 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO107 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO45 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO79 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO89 = 1;
            break;
        case 8:
            GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO128 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO113 = 1;
            GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
            GpioDataRegs.GPECLEAR.bit.GPIO129 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO62 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO76 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;
            break;
        case 9:
            GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO126 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO111 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO36 = 1;
            GpioDataRegs.GPDCLEAR.bit.GPIO127 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO78 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO68 = 1;
            GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;
            break;
        default:
            break;
    }
}

//=== Function: GPIOLEDs_Off ==========================================================================
///
/// @brief  Function to turn-OFF all fisrt LEDs in all Groups at a time, followed by second LEDs and so on
///
/// @param  void
///
/// @return void
///
//===========================================================================================================
void GPIOLEDs_Off(int i)
{
    switch (i)
    {
        case 0:
            GpioDataRegs.GPDSET.bit.GPIO116 = 1;
            GpioDataRegs.GPBSET.bit.GPIO38 = 1;
            GpioDataRegs.GPASET.bit.GPIO29 = 1;
            GpioDataRegs.GPCSET.bit.GPIO85 = 1;
            GpioDataRegs.GPBSET.bit.GPIO32 = 1;
            GpioDataRegs.GPBSET.bit.GPIO39 = 1;
            GpioDataRegs.GPDSET.bit.GPIO125 = 1;
            GpioDataRegs.GPCSET.bit.GPIO72 = 1;
            break;
        case 1:
            GpioDataRegs.GPDSET.bit.GPIO121 = 1;
            GpioDataRegs.GPBSET.bit.GPIO50 = 1;
            GpioDataRegs.GPASET.bit.GPIO30 = 1;
            GpioDataRegs.GPCSET.bit.GPIO69 = 1;
            GpioDataRegs.GPBSET.bit.GPIO37 = 1;
            GpioDataRegs.GPBSET.bit.GPIO49 = 1;
            GpioDataRegs.GPESET.bit.GPIO131 = 1;
            GpioDataRegs.GPCSET.bit.GPIO71 = 1;
            break;
        case 2:
            GpioDataRegs.GPDSET.bit.GPIO117 = 1;
            GpioDataRegs.GPBSET.bit.GPIO40 = 1;
            GpioDataRegs.GPESET.bit.GPIO134 = 1;
            GpioDataRegs.GPCSET.bit.GPIO77 = 1;
            GpioDataRegs.GPDSET.bit.GPIO120 = 1;
            GpioDataRegs.GPBSET.bit.GPIO51 = 1;
            GpioDataRegs.GPESET.bit.GPIO132 = 1;
            GpioDataRegs.GPCSET.bit.GPIO87 = 1;
            break;
        case 3:
            GpioDataRegs.GPCSET.bit.GPIO83 = 1;
            GpioDataRegs.GPBSET.bit.GPIO52 = 1;
            GpioDataRegs.GPBSET.bit.GPIO48 = 1;
            GpioDataRegs.GPDSET.bit.GPIO119 = 1;
            GpioDataRegs.GPBSET.bit.GPIO53 = 1;
            GpioDataRegs.GPESET.bit.GPIO136 = 1;
            GpioDataRegs.GPBSET.bit.GPIO58 = 1;
            GpioDataRegs.GPCSET.bit.GPIO86 = 1;
            break;
        case 4:
            GpioDataRegs.GPCSET.bit.GPIO81 = 1;
            GpioDataRegs.GPBSET.bit.GPIO55 = 1;
            GpioDataRegs.GPDSET.bit.GPIO124 = 1;
            GpioDataRegs.GPDSET.bit.GPIO122 = 1;
            GpioDataRegs.GPBSET.bit.GPIO54 = 1;
            GpioDataRegs.GPBSET.bit.GPIO60 = 1;
            GpioDataRegs.GPBSET.bit.GPIO59 = 1;
            GpioDataRegs.GPCSET.bit.GPIO80 = 1;
            break;
        case 5:
            GpioDataRegs.GPCSET.bit.GPIO84 = 1;
            GpioDataRegs.GPBSET.bit.GPIO57 = 1;
            GpioDataRegs.GPDSET.bit.GPIO115 = 1;
            GpioDataRegs.GPDSET.bit.GPIO114 = 1;
            GpioDataRegs.GPBSET.bit.GPIO56 = 1;
            GpioDataRegs.GPCSET.bit.GPIO64 = 1;
            GpioDataRegs.GPCSET.bit.GPIO65 = 1;
            GpioDataRegs.GPCSET.bit.GPIO82 = 1;
            break;
        case 6:
            GpioDataRegs.GPBSET.bit.GPIO46 = 1;
            GpioDataRegs.GPBSET.bit.GPIO44 = 1;
            GpioDataRegs.GPDSET.bit.GPIO123 = 1;
            GpioDataRegs.GPDSET.bit.GPIO112 = 1;
            GpioDataRegs.GPBSET.bit.GPIO41 = 1;
            GpioDataRegs.GPCSET.bit.GPIO66 = 1;
            GpioDataRegs.GPBSET.bit.GPIO61 = 1;
            GpioDataRegs.GPCSET.bit.GPIO90 = 1;
            break;
        case 7:
            GpioDataRegs.GPCSET.bit.GPIO88 = 1;
            GpioDataRegs.GPESET.bit.GPIO130 = 1;
            GpioDataRegs.GPDSET.bit.GPIO118 = 1;
            GpioDataRegs.GPDSET.bit.GPIO107 = 1;
            GpioDataRegs.GPBSET.bit.GPIO45 = 1;
            GpioDataRegs.GPBSET.bit.GPIO63 = 1;
            GpioDataRegs.GPCSET.bit.GPIO79 = 1;
            GpioDataRegs.GPCSET.bit.GPIO89 = 1;
            break;
        case 8:
            GpioDataRegs.GPBSET.bit.GPIO43 = 1;
            GpioDataRegs.GPESET.bit.GPIO128 = 1;
            GpioDataRegs.GPDSET.bit.GPIO113 = 1;
            GpioDataRegs.GPASET.bit.GPIO31 = 1;
            GpioDataRegs.GPESET.bit.GPIO129 = 1;
            GpioDataRegs.GPBSET.bit.GPIO62 = 1;
            GpioDataRegs.GPCSET.bit.GPIO76 = 1;
            GpioDataRegs.GPBSET.bit.GPIO42 = 1;
            break;
        case 9:
            GpioDataRegs.GPASET.bit.GPIO9 = 1;
            GpioDataRegs.GPDSET.bit.GPIO126 = 1;
            GpioDataRegs.GPDSET.bit.GPIO111 = 1;
            GpioDataRegs.GPBSET.bit.GPIO36 = 1;
            GpioDataRegs.GPDSET.bit.GPIO127 = 1;
            GpioDataRegs.GPCSET.bit.GPIO78 = 1;
            GpioDataRegs.GPCSET.bit.GPIO68 = 1;
            GpioDataRegs.GPASET.bit.GPIO8 = 1;
            break;
        default:
            break;
    }
}
