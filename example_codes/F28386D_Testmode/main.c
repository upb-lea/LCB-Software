//=================================================================================================
/// @file			main.c
///
/// @brief		Enthält das Hauptprogramm zum Testen verschiedener Komponenten des LEA-Control-
///						Boards und des Docking-Boards. Die Ausgangsspannung der vier Potentiometer wird
///						von den vier ADC-Modulen eingelesen (jeweils ein ADC-Modul liest ein Poti ein).
///						Diese Werte werden anschließend als Tastverhältnis von vier PWM-Modulen wieder
///						ausgegeben. Zusätzlich werden die LEDs auf dem Control-Board so angesteuert,
///						dass ein Lauflicht entsteht. Die Verkabelung muss wie folgt ausgeführt werden:
//
///						Jumper auf: (Potentiometer) J29, J27, J17, J15, J20, J18, J32, J30
///												(LED green)     J42, J38, J40, J36
///												(LED yellow)    J54, J56, J52, J58
///												(LED red)       J50, J46, J48, J44
///
///						Kabel:      (Potentiometer) J28 > D2D3_N, J16 > C2C3_N, J19 > B2B3_N, J31 > A2A3_N
///												(LED green)     J41 > 151,    J37 > 149,    J39 > 147,    J35 > 145
///												(LED yellow)
///												(LED red)
///
/// @version	V1.0
///
/// @date			09.03.2023
///
/// @author		Daniel Urbaneck
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "myGPIO.h"
#include "myPWM.h"
#include "myADC.h"
#include <math.h>


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Prototypes of global functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------


//=== Function: main ==============================================================================
///
/// @brief  Hauptprogramm
///
/// @param  void
///
/// @return void
///
//=================================================================================================
void main(void)
{
		// Mikrocontroller initialisieren (Watchdog, Systemtakt, Speicher, Interrupts)
		DeviceInit(DEVICE_CLKSRC_EXTOSC_SE_25MHZ);
    // GPIOs initialisierenz
    GpioInit();
    // PWM 1 bis 4 initialisieren
    PwmInitPWM1To4();
    // PWM 8 initialisieren
    PwmInitPwm8();
    // ADC-A initialisieren
    AdcAInit(ADC_RESOLUTION_12_BIT,
						 ADC_SINGLE_ENDED_MODE);
    // ADC-B initialisieren
    AdcBInit(ADC_RESOLUTION_12_BIT,
						 ADC_SINGLE_ENDED_MODE);
    // ADC-C initialisieren
    AdcCInit(ADC_RESOLUTION_12_BIT,
						 ADC_SINGLE_ENDED_MODE);
    // ADC-D initialisieren
    AdcDInit(ADC_RESOLUTION_12_BIT,
						 ADC_SINGLE_ENDED_MODE);


    // Register-Schreibschutz ausschalten
    EALLOW;


		// Dauerschleife Hauptprogramm
    while(1)
    {

    		/*
    		// LED D1003 auf der ControlCard abhängig vom Pegel an GPIO 80 ein- bzw. ausschalten
    		if (GpioDataRegs.GPCDAT.bit.GPIO80 == 1)
    		{
    				GpioDataRegs.GPASET.bit.GPIO3 = 1;
    		}
    		else
    		{
    				GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
    		}
    		*/

    		// LEDs D1002 bis D1006 auf dem Control-Board blinken
    		if (counterToggleLeds <= 50)
    		{
        		GpioDataRegs.GPASET.bit.GPIO5   = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
    		}
    		else if (counterToggleLeds <= 100)
    		{
        		GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        		GpioDataRegs.GPASET.bit.GPIO3   = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
    		}
    		else if (counterToggleLeds <= 150)
    		{
        		GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        		GpioDataRegs.GPASET.bit.GPIO2   = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
    		}
    		else if (counterToggleLeds <= 200)
    		{
        		GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        		GpioDataRegs.GPASET.bit.GPIO6   = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
    		}
    		else if (counterToggleLeds <= 250)
    		{
        		GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        		GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        		GpioDataRegs.GPASET.bit.GPIO7   = 1;
    		}

    		// GPIOs 145, 147, 149 und 151 in Abhängigkeit
    		// der ADC-Messwerte INA3, INB3, INC3 und IND3
    		// dimmen. Exponentialfunktion und lineares
    		// Dimmen am Anfang, damit es fürs menschliche
    		// Auge halbwegs linear wirkt.
    		// PWM1
    		if (ADCINA3 < 2000)
    		{
    				EPwm1Regs.CMPA.bit.CMPA = ADCINA3/30;
    		}
    		else
    		{
    				EPwm1Regs.CMPA.bit.CMPA = pow(5000.0, (ADCINA3/4095.0));
    		}
    		// PWM2
    		if (ADCINB3 < 2000)
    		{
    				EPwm2Regs.CMPA.bit.CMPA = ADCINB3/30;
    		}
    		else
    		{
    				EPwm2Regs.CMPA.bit.CMPA = pow(5000.0, (ADCINB3/4095.0));
    		}
    		// PWM3
    		if (ADCINC3 < 2000)
    		{
    				EPwm3Regs.CMPA.bit.CMPA = ADCINC3/30;
    		}
    		else
    		{
    				EPwm3Regs.CMPA.bit.CMPA = pow(5000.0, (ADCINC3/4095.0));
    		}
    		// PWM4
    		if (ADCIND3 < 2000)
    		{
    				EPwm4Regs.CMPA.bit.CMPA = ADCIND3/30;
    		}
    		else
    		{
    				EPwm4Regs.CMPA.bit.CMPA = pow(5000.0, (ADCIND3/4095.0));
    		}


    }
}

