//=================================================================================================
/// @file       TB_ADC.c
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
#include "TB_ADC.h"

//=== Function: AdcAInit ==========================================================================
///
/// @brief  Function initialises the all ADC (module A,B,C,D)
///
/// @param  void
///
/// @return void
///
//=================================================================================================
void AdcInitAll(void)
{
    EALLOW;

    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    __asm(" RPT #4 || NOP");

    AdcaRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_DIV_4_0;
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = ADC_POWER_ON;
    DELAY_US(500);
    AdcaRegs.ADCCTL2.bit.RESOLUTION = 0;
    AdcaRegs.ADCCTL2.bit.SIGNALMODE = 0;
    AdcInitTrimRegister(ADC_MODULE_A, 0, 0);

    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN2;
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = 29;

    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcaRegs.ADCSOC3CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN3;
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = 29;

    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcaRegs.ADCSOC4CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN4;
    AdcaRegs.ADCSOC4CTL.bit.ACQPS = 29;

    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcaRegs.ADCSOC5CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN5;
    AdcaRegs.ADCSOC5CTL.bit.ACQPS = 29;

    AdcaRegs.ADCSOC14CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcaRegs.ADCSOC14CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN14;
    AdcaRegs.ADCSOC14CTL.bit.ACQPS = 29;

    AdcaRegs.ADCSOC15CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcaRegs.ADCSOC15CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN15;
    AdcaRegs.ADCSOC15CTL.bit.ACQPS = 29;

    CpuSysRegs.PCLKCR13.bit.ADC_B = 1;
    __asm(" RPT #4 || NOP");

    AdcbRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_DIV_4_0;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = ADC_POWER_ON;
    DELAY_US(500);
    AdcbRegs.ADCCTL2.bit.RESOLUTION = 0;
    AdcbRegs.ADCCTL2.bit.SIGNALMODE = 0;
    AdcInitTrimRegister(ADC_MODULE_B, 0, 0);

    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN0;
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = 29;

    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcbRegs.ADCSOC2CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN2;
    AdcbRegs.ADCSOC2CTL.bit.ACQPS = 29;

    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcbRegs.ADCSOC3CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN3;
    AdcbRegs.ADCSOC3CTL.bit.ACQPS = 29;

    AdcbRegs.ADCSOC4CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcbRegs.ADCSOC4CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN4;
    AdcbRegs.ADCSOC4CTL.bit.ACQPS = 29;

    AdcbRegs.ADCSOC5CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcbRegs.ADCSOC5CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN5;
    AdcbRegs.ADCSOC5CTL.bit.ACQPS = 29;

    CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
    __asm(" RPT #4 || NOP");

    AdccRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_DIV_4_0;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = ADC_POWER_ON;
    DELAY_US(500);
    AdccRegs.ADCCTL2.bit.RESOLUTION = 0;
    AdccRegs.ADCCTL2.bit.SIGNALMODE = 0;
    AdcInitTrimRegister(ADC_MODULE_C, 0, 0);

    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdccRegs.ADCSOC2CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN2;
    AdccRegs.ADCSOC2CTL.bit.ACQPS = 29;

    AdccRegs.ADCSOC3CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdccRegs.ADCSOC3CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN3;
    AdccRegs.ADCSOC3CTL.bit.ACQPS = 29;

    AdccRegs.ADCSOC4CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdccRegs.ADCSOC4CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN4;
    AdccRegs.ADCSOC4CTL.bit.ACQPS = 29;

    AdccRegs.ADCSOC5CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdccRegs.ADCSOC5CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN5;
    AdccRegs.ADCSOC5CTL.bit.ACQPS = 29;

    CpuSysRegs.PCLKCR13.bit.ADC_D = 1;
    __asm(" RPT #4 || NOP");

    AdcdRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_DIV_4_0;
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = ADC_POWER_ON;
    DELAY_US(500);
    AdcdRegs.ADCCTL2.bit.RESOLUTION = 0;
    AdcdRegs.ADCCTL2.bit.SIGNALMODE = 0;
    AdcInitTrimRegister(ADC_MODULE_D, 0, 0);

    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcdRegs.ADCSOC0CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN0;
    AdcdRegs.ADCSOC0CTL.bit.ACQPS = 29;

    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcdRegs.ADCSOC1CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN1;
    AdcdRegs.ADCSOC1CTL.bit.ACQPS = 29;

    AdcdRegs.ADCSOC2CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcdRegs.ADCSOC2CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN2;
    AdcdRegs.ADCSOC2CTL.bit.ACQPS = 29;

    AdcdRegs.ADCSOC3CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcdRegs.ADCSOC3CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN3;
    AdcdRegs.ADCSOC3CTL.bit.ACQPS = 29;

    AdcdRegs.ADCSOC4CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcdRegs.ADCSOC4CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN4;
    AdcdRegs.ADCSOC4CTL.bit.ACQPS = 29;

    AdcdRegs.ADCSOC5CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM1_SOCA;
    AdcdRegs.ADCSOC5CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN5;
    AdcdRegs.ADCSOC5CTL.bit.ACQPS = 29;

    EDIS;
}


//=== Function: AdcInitTrimRegister ===============================================================
///
/// @brief  Funktion läd die Exemplar-spezifischen Kalibrierwerte aus dem OTP-Speicher
///         und kopiert sie in die entsprechenden Register des ADCs
///
/// @param  uint32_t adcModule, uint32_t resolution, uint32_t signalMode
///
/// @return void
///
//=================================================================================================
extern void AdcInitTrimRegister(uint32_t adcModule,
                                uint32_t resolution,
                                uint32_t signalMode)
{
    // Trimm-Register für ADC-A initialisieren
    if (adcModule == ADC_MODULE_A)
    {
        // Pointer auf die Startadresse der Kalibrierungsdaten
        // im OTP-Speicher des Mikrocontrollers
        uint32_t *ptr = ADC_A_INLTRIM_OTP_ADDR_START;
        // Wert für die 16 Bit-Offset-Kalibrierung aus dem OTP-Speicher laden
        uint16_t offsetTrim = *ADC_A_OFFSETTRIM_OTP_16BIT;
        // Liniearitäts-Trimmregister mit den (Exemplar-
        // spezifischen) Herstellungsdaten beschreiben
        AdcaRegs.ADCINLTRIM1 = *ptr;
        AdcaRegs.ADCINLTRIM2 = *(++ptr);
        AdcaRegs.ADCINLTRIM3 = *(++ptr);
        AdcaRegs.ADCINLTRIM4 = *(++ptr);
        AdcaRegs.ADCINLTRIM5 = *(++ptr);
        AdcaRegs.ADCINLTRIM6 = *(++ptr);
        // Für den 12 Bit-Betrieb müssen einige Trimm-Register maskiert
        // werden. Warum das gemacht werden muss und welche Register
        // das sind, steht nicht im Datenblatt sondern ist aus den
        // Beispielen der driverlib übernommen worden. Im Datenblatt
        // (S. 2521 Reference Manual TMS320F2838x, SPRUII0D, Rev. D,
        // July 2022) wird lediglich darauf verwiesen, dass zur Konfiguration
        // der Auflösung und Betriebsart die TI-Funktion AdcSetMode() bzw.
        // ADC_setMode() verwendet werden solle und die Register nicht
        // direkt beschrieben werden sollen
        if(resolution == ADC_RESOLUTION_12_BIT)
        {
            AdcaRegs.ADCINLTRIM1 &= 0xFFFF0000;
            AdcaRegs.ADCINLTRIM2 &= 0xFFFF0000;
            AdcaRegs.ADCINLTRIM4 &= 0xFFFF0000;
            AdcaRegs.ADCINLTRIM5 &= 0xFFFF0000;
            // Wert für die 12 Bit-Offset-Kalibrierung aus dem OTP-Speicher laden
            offsetTrim = *ADC_A_OFFSETTRIM_OTP_12BIT;
        }
        // Wert für die Offset-Kalibrierung abhängig von der Betriebsart
        // setzen. Der Wert aus dem OTP-Speicher enthält die Kalibrierdaten
        // für beide Betriebsarten (MSB für Sigle-Ended, LSB für Differential)
        if (signalMode == ADC_SINGLE_ENDED_MODE)
        {
            AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = offsetTrim >> 8;
        }
        else
        {
            AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = offsetTrim & 0xFF;
        }
    }
    // Trimm-Register für ADC-B initialisieren
    else if (adcModule == ADC_MODULE_B)
    {
        // Pointer auf die Startadresse der Kalibrierungsdaten
        // im OTP-Speicher des Mikrocontrollers
        uint32_t *ptr = ADC_B_INLTRIM_OTP_ADDR_START;
        // Wert für die 16 Bit-Offset-Kalibrierung aus dem OTP-Speicher laden
        uint16_t offsetTrim = *ADC_B_OFFSETTRIM_OTP_16BIT;
        // Liniearitäts-Trimmregister mit den (Exemplar-
        // spezifischen) Herstellungsdaten beschreiben
        AdcbRegs.ADCINLTRIM1 = *ptr;
        AdcbRegs.ADCINLTRIM2 = *(++ptr);
        AdcbRegs.ADCINLTRIM3 = *(++ptr);
        AdcbRegs.ADCINLTRIM4 = *(++ptr);
        AdcbRegs.ADCINLTRIM5 = *(++ptr);
        AdcbRegs.ADCINLTRIM6 = *(++ptr);
        // Für den 12 Bit-Betrieb müssen einige Trimm-Register maskiert
        // werden. Warum das gemacht werden muss und welche Register
        // das sind, steht nicht im Datenblatt sondern ist aus den
        // Beispielen der driverlib übernommen worden. Im Datenblatt
        // (S. 2521 Reference Manual TMS320F2838x, SPRUII0D, Rev. D,
        // July 2022) wird lediglich darauf verwiesen, dass zur Konfiguration
        // der Auflösung und Betriebsart die TI-Funktion AdcSetMode() bzw.
        // ADC_setMode() verwendet werden solle und die Register nicht
        // direkt beschrieben werden sollen
        if(resolution == ADC_RESOLUTION_12_BIT)
        {
            AdcbRegs.ADCINLTRIM1 &= 0xFFFF0000;
            AdcbRegs.ADCINLTRIM2 &= 0xFFFF0000;
            AdcbRegs.ADCINLTRIM4 &= 0xFFFF0000;
            AdcbRegs.ADCINLTRIM5 &= 0xFFFF0000;
            // Wert für die 12 Bit-Offset-Kalibrierung aus dem OTP-Speicher laden
            offsetTrim = *ADC_B_OFFSETTRIM_OTP_12BIT;
        }
        // Wert für die Offset-Kalibrierung abhängig von der Betriebsart
        // setzen. Der Wert aus dem OTP-Speicher enthält die Kalibrierdaten
        // für beide Betriebsarten (MSB für Sigle-Ended, LSB für Differential)
        if (signalMode == ADC_SINGLE_ENDED_MODE)
        {
            AdcbRegs.ADCOFFTRIM.bit.OFFTRIM = offsetTrim >> 8;
        }
        else
        {
            AdcbRegs.ADCOFFTRIM.bit.OFFTRIM = offsetTrim & 0xFF;
        }
    }
    // Trimm-Register für ADC-C initialisieren
    else if (adcModule == ADC_MODULE_C)
    {
        // Pointer auf die Startadresse der Kalibrierungsdaten
        // im OTP-Speicher des Mikrocontrollers
        uint32_t *ptr = ADC_C_INLTRIM_OTP_ADDR_START;
        // Wert für die 16 Bit-Offset-Kalibrierung aus dem OTP-Speicher laden
        uint16_t offsetTrim = *ADC_C_OFFSETTRIM_OTP_16BIT;
        // Liniearitäts-Trimmregister mit den (Exemplar-
        // spezifischen) Herstellungsdaten beschreiben
        AdccRegs.ADCINLTRIM1 = *ptr;
        AdccRegs.ADCINLTRIM2 = *(++ptr);
        AdccRegs.ADCINLTRIM3 = *(++ptr);
        AdccRegs.ADCINLTRIM4 = *(++ptr);
        AdccRegs.ADCINLTRIM5 = *(++ptr);
        AdccRegs.ADCINLTRIM6 = *(++ptr);
        // Für den 12 Bit-Betrieb müssen einige Trimm-Register maskiert
        // werden. Warum das gemacht werden muss und welche Register
        // das sind, steht nicht im Datenblatt sondern ist aus den
        // Beispielen der driverlib übernommen worden. Im Datenblatt
        // (S. 2521 Reference Manual TMS320F2838x, SPRUII0D, Rev. D,
        // July 2022) wird lediglich darauf verwiesen, dass zur Konfiguration
        // der Auflösung und Betriebsart die TI-Funktion AdcSetMode() bzw.
        // ADC_setMode() verwendet werden solle und die Register nicht
        // direkt beschrieben werden sollen
        if(resolution == ADC_RESOLUTION_12_BIT)
        {
            AdccRegs.ADCINLTRIM1 &= 0xFFFF0000;
            AdccRegs.ADCINLTRIM2 &= 0xFFFF0000;
            AdccRegs.ADCINLTRIM4 &= 0xFFFF0000;
            AdccRegs.ADCINLTRIM5 &= 0xFFFF0000;
            // Wert für die 12 Bit-Offset-Kalibrierung aus dem OTP-Speicher laden
            offsetTrim = *ADC_C_OFFSETTRIM_OTP_12BIT;
        }
        // Wert für die Offset-Kalibrierung abhängig von der Betriebsart
        // setzen. Der Wert aus dem OTP-Speicher enthält die Kalibrierdaten
        // für beide Betriebsarten (MSB für Sigle-Ended, LSB für Differential)
        if (signalMode == ADC_SINGLE_ENDED_MODE)
        {
            AdccRegs.ADCOFFTRIM.bit.OFFTRIM = offsetTrim >> 8;
        }
        else
        {
            AdccRegs.ADCOFFTRIM.bit.OFFTRIM = offsetTrim & 0xFF;
        }
    }
    // Trimm-Register für ADC-D initialisieren
    else if (adcModule == ADC_MODULE_D)
    {
        // Pointer auf die Startadresse der Kalibrierungsdaten
        // im OTP-Speicher des Mikrocontrollers
        uint32_t *ptr = ADC_D_INLTRIM_OTP_ADDR_START;
        // Wert für die 16 Bit-Offset-Kalibrierung aus dem OTP-Speicher laden
        uint16_t offsetTrim = *ADC_D_OFFSETTRIM_OTP_16BIT;
        // Liniearitäts-Trimmregister mit den (Exemplar-
        // spezifischen) Herstellungsdaten beschreiben
        AdcdRegs.ADCINLTRIM1 = *ptr;
        AdcdRegs.ADCINLTRIM2 = *(++ptr);
        AdcdRegs.ADCINLTRIM3 = *(++ptr);
        AdcdRegs.ADCINLTRIM4 = *(++ptr);
        AdcdRegs.ADCINLTRIM5 = *(++ptr);
        AdcdRegs.ADCINLTRIM6 = *(++ptr);
        // Für den 12 Bit-Betrieb müssen einige Trimm-Register maskiert
        // werden. Warum das gemacht werden muss und welche Register
        // das sind, steht nicht im Datenblatt sondern ist aus den
        // Beispielen der driverlib übernommen worden. Im Datenblatt
        // (S. 2521 Reference Manual TMS320F2838x, SPRUII0D, Rev. D,
        // July 2022) wird lediglich darauf verwiesen, dass zur Konfiguration
        // der Auflösung und Betriebsart die TI-Funktion AdcSetMode() bzw.
        // ADC_setMode() verwendet werden solle und die Register nicht
        // direkt beschrieben werden sollen
        if(resolution == ADC_RESOLUTION_12_BIT)
        {
            AdcdRegs.ADCINLTRIM1 &= 0xFFFF0000;
            AdcdRegs.ADCINLTRIM2 &= 0xFFFF0000;
            AdcdRegs.ADCINLTRIM4 &= 0xFFFF0000;
            AdcdRegs.ADCINLTRIM5 &= 0xFFFF0000;
            // Wert für die 12 Bit-Offset-Kalibrierung aus dem OTP-Speicher laden
            offsetTrim = *ADC_D_OFFSETTRIM_OTP_12BIT;
        }
        // Wert für die Offset-Kalibrierung abhängig von der Betriebsart
        // setzen. Der Wert aus dem OTP-Speicher enthält die Kalibrierdaten
        // für beide Betriebsarten (MSB für Sigle-Ended, LSB für Differential)
        if (signalMode == ADC_SINGLE_ENDED_MODE)
        {
            AdcdRegs.ADCOFFTRIM.bit.OFFTRIM = offsetTrim >> 8;
        }
        else
        {
            AdcdRegs.ADCOFFTRIM.bit.OFFTRIM = offsetTrim & 0xFF;
        }
    }
}



