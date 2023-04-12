//=================================================================================================
/// @file       myADC.c
///
/// @brief      Datei enthält Variablen und Funktionen um die vier internen Analog-Digital-Wandler
///							des TMS320F2838x zu nutzen. Der Code nutzt alle Module (A bis D). Die ADCs werden
///							so konfiguriert, dass die externe 3,0 V-Referenz verwendet wird und die ADCs mit
///							50 MHz-Takt laufen (SYSCLK = 200 MHz). Die Messung wird durch das ePWM8-Modul
///							getriggert. Die Messeingänge sind jeweils ADCINx3 (x= A, B, C oder D). Nach dem
///						  Ende einer Messung wird ein Interrupt ausgelöst und dort der Messwert in eine
///							globale Variable kopiert.
///
/// @version    V1.0
///
/// @date       09.03.2023
///
/// @author     Daniel Urbaneck
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "myADC.h"


//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------
// Messwerte der ADC-Eingänge
uint16_t ADCINA3 = 0;
uint16_t ADCINB3 = 0;
uint16_t ADCINC3 = 0;
uint16_t ADCIND3 = 0;


//-------------------------------------------------------------------------------------------------
// Global functions
//-------------------------------------------------------------------------------------------------
//=== Function: AdcInitTrimRegister ===============================================================
///
/// @brief	Funktion läd die Exemplar-spezifischen Kalibrierwerte aus dem OTP-Speicher
///					und kopiert sie in die entsprechenden Register des ADCs
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


//=== Function: AdcAInit ==========================================================================
///
/// @brief	Funktion initialisiert den ADC (Modul A)
///
/// @param  uint32_t resolution, uint32_t signalMode
///
/// @return void
///
//=================================================================================================
void AdcAInit(uint32_t resolution,
							uint32_t signalMode)
{
		// Register-Schreibschutz aufheben
		EALLOW;

		// ADC konfigurieren:
    // Takt für das ADC-Modul einschalten und 5 Takte
    // warten, bis der Takt zum Modul durchgestellt ist
    // (siehe S. 169 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
		CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    __asm(" RPT #4 || NOP");
    // HINWEIS: Es gibt keine interne ADC-Referenzspannung!
    //					(siehe S. 2521 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    //
    // Taktteiler auf 4 setzen => ADCCLK = SYSCLK / 4 = 50 MHz
    // maximaler ADCCLK = 50 MHz (siehe S. 138 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    AdcaRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_DIV_4_0;
		// Stromversorgung des ADC einschalten
		AdcaRegs.ADCCTL1.bit.ADCPWDNZ = ADC_POWER_ON;
    // Erst 500 µs nach Einschalten des ADC kann eine korrekte Messung durchgeführt werden
		// (siehe "Power Up Time" S. 139 + 142 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    DELAY_US(500);
    // Auflösung auf 12 Bit setzen
    // 0: 12 Bit-Auflösung (Achtung: nur Single-Ended möglich!)
    // 1: 16 Bit-Auflösung
    AdcaRegs.ADCCTL2.bit.RESOLUTION = resolution;
    // Single-Ended Mode als Betriebsart setzen
    // (siehe S. 2523 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    // 0: Single-ended (Spannung an einem ADC-Pin gegen untere Referenzspannung
		//									bezogen auf Referenzsspannungsband: (ADCINx - VREFLO) / (VREFHI-VREFLO))
    // 1: Differential (Spannungsdifferenz an zwei ADC-Pins gegen 2*Referenzspannung:
    //									(ADCINxP - ADCINxN + VREFHI) / (2*VREFHI). In diesem Betriebsmodus
    //									muss VREFLO auf Analog-GND (VSSA) gelegt sein)
    AdcaRegs.ADCCTL2.bit.SIGNALMODE = signalMode;
    // Trimm-Register für Offset- und Linearitätsabweichung
    // mit Werten aus dem OTP-Speicher initialisieren
    AdcInitTrimRegister(ADC_MODULE_A,
												resolution,
												signalMode);

    // SOC0 konfigurieren:
    // Messung durch das ePWM8-Modul triggern (SOCA).
    // Weitere Triggerquellen: CPU-Timer, ePWM-Module
    // (siehe S. 2607 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM8_SOCA;
    // Eingang ADCIN3 setzen
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN3;
    // Abtastzeitfenster 60 (SYSCLK-)Taktzyklen = 300 ns.
    // ACQPS muss mindestens einen ADCLK-Takt lang sein.
    // Abtastzeitfenster = 1/SYSCLK * (ACQPS+1)
    // (siehe S. 2526 und 2556 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022
    // sowie S. 145 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 59;
    // Kein SOC-Trigger durch ADC-Interrupt
    AdcaRegs.ADCINTSOCSEL1.bit.SOC0 = ADC_NO_SOC_TRIGGER;
    // ADC-Interrupt konfigurieren:
    // ADC-Interrupt auslösen, nachdem der Wert
    // in das Result-Register geschrieben wurde
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = ADC_PULSE_END_OF_CONV;
    // ADCINT1-Interrupt einschalten
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = ADC_INT_ENABLE;
		// EOC0 als Trigger für ADCINT1 setzen
		AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = ADC_EOC_NUMBER_0;
    // ADCINT1 nur einmal auslösen. Erneutes
    // Auslösen erst nach löschen des INT-Flags
    // 0: Einmaliges Auslösen, erst wieder nach Löschen des Flags
    // 1: Kontinuierliches Auslösen bei jedem Trigger
    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = ADC_INT_PULSE_ONE_SHOT;
		// CPU-Interrupts während der Konfiguration global sperren
    DINT;
		// Interrupt-Service-Routinen für den ADCA1-Interrupt an die
    // entsprechende Stelle (Interrupt) der PIE-Vector Table speichern
    PieVectTable.ADCA1_INT = &AdcAInt1ISR;
    // ADCA1-Interrupt freischalten (Zeile 1, Spalte 1 der Tabelle 3-2)
    // (siehe S. 150 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
    // CPU-Interrupt 1 einschalten (Zeile 1 der Tabelle)
    IER |= M_INT1;
    // Interrupts global einschalten
    EINT;

		// Register-Schreibschutz setzen
		EDIS;
}


//=== Function: AdcBInit ==========================================================================
///
/// @brief	Funktion initialisiert den ADC (Modul B)
///
/// @param  uint32_t resolution, uint32_t signalMode
///
/// @return void
///
//=================================================================================================
void AdcBInit(uint32_t resolution,
							uint32_t signalMode)
{
		// Register-Schreibschutz aufheben
		EALLOW;

		// ADC konfigurieren:
    // Takt für das ADC-Modul einschalten und 5 Takte
    // warten, bis der Takt zum Modul durchgestellt ist
    // (siehe S. 169 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
		CpuSysRegs.PCLKCR13.bit.ADC_B = 1;
    __asm(" RPT #4 || NOP");
    // HINWEIS: Es gibt keine interne ADC-Referenzspannung!
    //					(siehe S. 2521 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    //
    // Taktteiler auf 4 setzen => ADCCLK = SYSCLK / 4 = 50 MHz
    // maximaler ADCCLK = 50 MHz (siehe S. 138 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    AdcbRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_DIV_4_0;
		// Stromversorgung des ADC einschalten
		AdcbRegs.ADCCTL1.bit.ADCPWDNZ = ADC_POWER_ON;
    // Erst 500 µs nach Einschalten des ADC kann eine korrekte Messung durchgeführt werden
		// (siehe "Power Up Time" S. 139 + 142 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    DELAY_US(500);
    // Auflösung auf 12 Bit setzen
    // 0: 12 Bit-Auflösung (Achtung: nur Single-Ended möglich!)
    // 1: 16 Bit-Auflösung
    AdcbRegs.ADCCTL2.bit.RESOLUTION = resolution;
    // Single-Ended Mode als Betriebsart setzen
    // (siehe S. 2523 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    // 0: Single-ended (Spannung an einem ADC-Pin gegen untere Referenzspannung
		//									bezogen auf Referenzsspannungsband: (ADCINx - VREFLO) / (VREFHI-VREFLO))
    // 1: Differential (Spannungsdifferenz an zwei ADC-Pins gegen 2*Referenzspannung:
    //									(ADCINxP - ADCINxN + VREFHI) / (2*VREFHI). In diesem Betriebsmodus
    //									muss VREFLO auf Analog-GND (VSSA) gelegt sein)
    AdcbRegs.ADCCTL2.bit.SIGNALMODE = signalMode;
    // Trimm-Register für Offset- und Linearitätsabweichung
    // mit Werten aus dem OTP-Speicher initialisieren
    AdcInitTrimRegister(ADC_MODULE_B,
												resolution,
												signalMode);

    // SOC0 konfigurieren:
    // Messung durch das ePWM8-Modul triggern (SOCA).
    // Weitere Triggerquellen: CPU-Timer, ePWM-Module
    // (siehe S. 2607 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM8_SOCA;
    // Eingang ADCIN3 setzen
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN3;
    // Abtastzeitfenster 60 (SYSCLK-)Taktzyklen = 300 ns.
    // ACQPS muss mindestens einen ADCLK-Takt lang sein.
    // Abtastzeitfenster = 1/SYSCLK * (ACQPS+1)
    // (siehe S. 2526 und 2556 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022
    // sowie S. 145 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = 59;
    // Kein SOC-Trigger durch ADC-Interrupt
    AdcbRegs.ADCINTSOCSEL1.bit.SOC0 = ADC_NO_SOC_TRIGGER;
    // ADC-Interrupt konfigurieren:
    // ADC-Interrupt auslösen, nachdem der Wert
    // in das Result-Register geschrieben wurde
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = ADC_PULSE_END_OF_CONV;
    // ADCINT1-Interrupt einschalten
    AdcbRegs.ADCINTSEL1N2.bit.INT1E = ADC_INT_ENABLE;
		// EOC0 als Trigger für ADCINT1 setzen
		AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = ADC_EOC_NUMBER_0;
    // ADCINT1 nur einmal auslösen. Erneutes
    // Auslösen erst nach löschen des INT-Flags
    // 0: Einmaliges Auslösen, erst wieder nach Löschen des Flags
    // 1: Kontinuierliches Auslösen bei jedem Trigger
    AdcbRegs.ADCINTSEL1N2.bit.INT1CONT = ADC_INT_PULSE_ONE_SHOT;
		// CPU-Interrupts während der Konfiguration global sperren
    DINT;
		// Interrupt-Service-Routinen für den ADCB1-Interrupt an die
    // entsprechende Stelle (Interrupt) der PIE-Vector Table speichern
    PieVectTable.ADCB1_INT = &AdcBInt1ISR;
    // ADCB1-Interrupt freischalten (Zeile 1, Spalte 2 der Tabelle 3-2)
    // (siehe S. 150 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    PieCtrlRegs.PIEIER1.bit.INTx2 = 1;
    // CPU-Interrupt 1 einschalten (Zeile 1 der Tabelle)
    IER |= M_INT1;
    // Interrupts global einschalten
    EINT;

		// Register-Schreibschutz setzen
		EDIS;
}


//=== Function: AdcCInit ==========================================================================
///
/// @brief	Funktion initialisiert den ADC (Modul C)
///
/// @param  uint32_t resolution, uint32_t signalMode
///
/// @return void
///
//=================================================================================================
void AdcCInit(uint32_t resolution,
							uint32_t signalMode)
{
		// Register-Schreibschutz aufheben
		EALLOW;

		// ADC konfigurieren:
    // Takt für das ADC-Modul einschalten und 5 Takte
    // warten, bis der Takt zum Modul durchgestellt ist
    // (siehe S. 169 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
		CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
    __asm(" RPT #4 || NOP");
    // HINWEIS: Es gibt keine interne ADC-Referenzspannung!
    //					(siehe S. 2521 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    //
    // Taktteiler auf 4 setzen => ADCCLK = SYSCLK / 4 = 50 MHz
    // maximaler ADCCLK = 50 MHz (siehe S. 138 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    AdccRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_DIV_4_0;
		// Stromversorgung des ADC einschalten
		AdccRegs.ADCCTL1.bit.ADCPWDNZ = ADC_POWER_ON;
    // Erst 500 µs nach Einschalten des ADC kann eine korrekte Messung durchgeführt werden
		// (siehe "Power Up Time" S. 139 + 142 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    DELAY_US(500);
    // Auflösung auf 12 Bit setzen
    // 0: 12 Bit-Auflösung (Achtung: nur Single-Ended möglich!)
    // 1: 16 Bit-Auflösung
    AdccRegs.ADCCTL2.bit.RESOLUTION = resolution;
    // Single-Ended Mode als Betriebsart setzen
    // (siehe S. 2523 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    // 0: Single-ended (Spannung an einem ADC-Pin gegen untere Referenzspannung
		//									bezogen auf Referenzsspannungsband: (ADCINx - VREFLO) / (VREFHI-VREFLO))
    // 1: Differential (Spannungsdifferenz an zwei ADC-Pins gegen 2*Referenzspannung:
    //									(ADCINxP - ADCINxN + VREFHI) / (2*VREFHI). In diesem Betriebsmodus
    //									muss VREFLO auf Analog-GND (VSSA) gelegt sein)
    AdccRegs.ADCCTL2.bit.SIGNALMODE = signalMode;
    // Trimm-Register für Offset- und Linearitätsabweichung
    // mit Werten aus dem OTP-Speicher initialisieren
    AdcInitTrimRegister(ADC_MODULE_C,
												resolution,
												signalMode);

    // SOC0 konfigurieren:
    // Messung durch das ePWM8-Modul triggern (SOCA).
    // Weitere Triggerquellen: CPU-Timer, ePWM-Module
    // (siehe S. 2607 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM8_SOCA;
    // Eingang ADCIN3 setzen
    AdccRegs.ADCSOC0CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN3;
    // Abtastzeitfenster 60 (SYSCLK-)Taktzyklen = 300 ns.
    // ACQPS muss mindestens einen ADCLK-Takt lang sein.
    // Abtastzeitfenster = 1/SYSCLK * (ACQPS+1)
    // (siehe S. 2526 und 2556 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022
    // sowie S. 145 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    AdccRegs.ADCSOC0CTL.bit.ACQPS = 59;
    // Kein SOC-Trigger durch ADC-Interrupt
    AdccRegs.ADCINTSOCSEL1.bit.SOC0 = ADC_NO_SOC_TRIGGER;
    // ADC-Interrupt konfigurieren:
    // ADC-Interrupt auslösen, nachdem der Wert
    // in das Result-Register geschrieben wurde
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = ADC_PULSE_END_OF_CONV;
    // ADCINT1-Interrupt einschalten
    AdccRegs.ADCINTSEL1N2.bit.INT1E = ADC_INT_ENABLE;
		// EOC0 als Trigger für ADCINT1 setzen
		AdccRegs.ADCINTSEL1N2.bit.INT1SEL = ADC_EOC_NUMBER_0;
    // ADCINT1 nur einmal auslösen. Erneutes
    // Auslösen erst nach löschen des INT-Flags
    // 0: Einmaliges Auslösen, erst wieder nach Löschen des Flags
    // 1: Kontinuierliches Auslösen bei jedem Trigger
    AdccRegs.ADCINTSEL1N2.bit.INT1CONT = ADC_INT_PULSE_ONE_SHOT;
		// CPU-Interrupts während der Konfiguration global sperren
    DINT;
		// Interrupt-Service-Routinen für den ADCC1-Interrupt an die
    // entsprechende Stelle (Interrupt) der PIE-Vector Table speichern
    PieVectTable.ADCC1_INT = &AdcCInt1ISR;
    // ADCC1-Interrupt freischalten (Zeile 1, Spalte 3 der Tabelle 3-2)
    // (siehe S. 150 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    PieCtrlRegs.PIEIER1.bit.INTx3 = 1;
    // CPU-Interrupt 1 einschalten (Zeile 1 der Tabelle)
    IER |= M_INT1;
    // Interrupts global einschalten
    EINT;

		// Register-Schreibschutz setzen
		EDIS;
}


//=== Function: AdcDInit ==========================================================================
///
/// @brief	Funktion initialisiert den ADC (Modul B)
///
/// @param  uint32_t resolution, uint32_t signalMode
///
/// @return void
///
//=================================================================================================
void AdcDInit(uint32_t resolution,
							uint32_t signalMode)
{
		// Register-Schreibschutz aufheben
		EALLOW;

		// ADC konfigurieren:
    // Takt für das ADC-Modul einschalten und 5 Takte
    // warten, bis der Takt zum Modul durchgestellt ist
    // (siehe S. 169 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
		CpuSysRegs.PCLKCR13.bit.ADC_D = 1;
    __asm(" RPT #4 || NOP");
    // HINWEIS: Es gibt keine interne ADC-Referenzspannung!
    //					(siehe S. 2521 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    //
    // Taktteiler auf 4 setzen => ADCCLK = SYSCLK / 4 = 50 MHz
    // maximaler ADCCLK = 50 MHz (siehe S. 138 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    AdcdRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_DIV_4_0;
		// Stromversorgung des ADC einschalten
		AdcdRegs.ADCCTL1.bit.ADCPWDNZ = ADC_POWER_ON;
    // Erst 500 µs nach Einschalten des ADC kann eine korrekte Messung durchgeführt werden
		// (siehe "Power Up Time" S. 139 + 142 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    DELAY_US(500);
    // Auflösung auf 12 Bit setzen
    // 0: 12 Bit-Auflösung (Achtung: nur Single-Ended möglich!)
    // 1: 16 Bit-Auflösung
    AdcdRegs.ADCCTL2.bit.RESOLUTION = resolution;
    // Single-Ended Mode als Betriebsart setzen
    // (siehe S. 2523 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    // 0: Single-ended (Spannung an einem ADC-Pin gegen untere Referenzspannung
		//									bezogen auf Referenzsspannungsband: (ADCINx - VREFLO) / (VREFHI-VREFLO))
    // 1: Differential (Spannungsdifferenz an zwei ADC-Pins gegen 2*Referenzspannung:
    //									(ADCINxP - ADCINxN + VREFHI) / (2*VREFHI). In diesem Betriebsmodus
    //									muss VREFLO auf Analog-GND (VSSA) gelegt sein)
    AdcdRegs.ADCCTL2.bit.SIGNALMODE = signalMode;
    // Trimm-Register für Offset- und Linearitätsabweichung
    // mit Werten aus dem OTP-Speicher initialisieren
    AdcInitTrimRegister(ADC_MODULE_D,
												resolution,
												signalMode);

    // SOC0 konfigurieren:
    // Messung durch das ePWM8-Modul triggern (SOCA).
    // Weitere Triggerquellen: CPU-Timer, ePWM-Module
    // (siehe S. 2607 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = ADC_TRIGGER_EPWM8_SOCA;
    // Eingang ADCIN3 setzen
    AdcdRegs.ADCSOC0CTL.bit.CHSEL = ADC_SINGLE_ENDED_ADCIN3;
    // Abtastzeitfenster 60 (SYSCLK-)Taktzyklen = 300 ns.
    // ACQPS muss mindestens einen ADCLK-Takt lang sein.
    // Abtastzeitfenster = 1/SYSCLK * (ACQPS+1)
    // (siehe S. 2526 und 2556 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022
    // sowie S. 145 Data Sheet TMS320F2838x, SPRSP14D, Rev. D, Feb. 2021)
    AdcdRegs.ADCSOC0CTL.bit.ACQPS = 59;
    // Kein SOC-Trigger durch ADC-Interrupt
    AdcdRegs.ADCINTSOCSEL1.bit.SOC0 = ADC_NO_SOC_TRIGGER;
    // ADC-Interrupt konfigurieren:
    // ADC-Interrupt auslösen, nachdem der Wert
    // in das Result-Register geschrieben wurde
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = ADC_PULSE_END_OF_CONV;
    // ADCINT1-Interrupt einschalten
    AdcdRegs.ADCINTSEL1N2.bit.INT1E = ADC_INT_ENABLE;
		// EOC0 als Trigger für ADCINT1 setzen
		AdcdRegs.ADCINTSEL1N2.bit.INT1SEL = ADC_EOC_NUMBER_0;
    // ADCINT1 nur einmal auslösen. Erneutes
    // Auslösen erst nach löschen des INT-Flags
    // 0: Einmaliges Auslösen, erst wieder nach Löschen des Flags
    // 1: Kontinuierliches Auslösen bei jedem Trigger
    AdcdRegs.ADCINTSEL1N2.bit.INT1CONT = ADC_INT_PULSE_ONE_SHOT;
		// CPU-Interrupts während der Konfiguration global sperren
    DINT;
		// Interrupt-Service-Routinen für den ADCD1-Interrupt an die
    // entsprechende Stelle (Interrupt) der PIE-Vector Table speichern
    PieVectTable.ADCD1_INT = &AdcDInt1ISR;
    // ADCD1-Interrupt freischalten (Zeile 1, Spalte 6 der Tabelle 3-2)
    // (siehe S. 150 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;
    // CPU-Interrupt 1 einschalten (Zeile 1 der Tabelle)
    IER |= M_INT1;
    // Interrupts global einschalten
    EINT;

		// Register-Schreibschutz setzen
		EDIS;
}


//=== Function: AdcAInt1ISR =======================================================================
///
/// @brief	ISR wird aufgerufen, wenn ein ADCINT1-Interrupt (Modul A) ausgelöst wurde
///
/// @param  void
///
/// @return void
///
//=================================================================================================
__interrupt void AdcAInt1ISR(void)
{
		// Bei jedem Eintritt in eine Interrupt-Service-Routine (ISR) wird automatisch
		// das EALLOW-Bit gelöscht, unabhängig davon, ob es zuvor gesetzt war (siehe
		// S. 148 Punkt 9, Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022).
		// Nach Abschluss der ISR wird das EALLOW-Bit automatisch wieder gesetzt, falls
		// es vor dem Auftritt des Interrupts gesetzt war. Falls in der ISR nur auf
		// Register ohne Schreibschutz zugegriffen wird, kann auf den folgenden Befehl
		// verzichtet werden (siehe Spalte "Write Protection" in der Registerübersicht)
		//EALLOW;
		// Messwert auslesen
		ADCINA3 = AdcaResultRegs.ADCRESULT0;

    // Interrupt-Flag im ADC-Modul löschen
		AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
		// Interrupt-Flag der Gruppe 1 löschen (da gehört der ADCA1_INT-Interrupt zu)
		PieCtrlRegs.PIEACK.bit.ACK1 = 1;
}


//=== Function: AdcBInt1ISR =======================================================================
///
/// @brief	ISR wird aufgerufen, wenn ein ADCINT1-Interrupt (Modul B) ausgelöst wurde
///
/// @param  void
///
/// @return void
///
//=================================================================================================
__interrupt void AdcBInt1ISR(void)
{
		// Bei jedem Eintritt in eine Interrupt-Service-Routine (ISR) wird automatisch
		// das EALLOW-Bit gelöscht, unabhängig davon, ob es zuvor gesetzt war (siehe
		// S. 148 Punkt 9, Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022).
		// Nach Abschluss der ISR wird das EALLOW-Bit automatisch wieder gesetzt, falls
		// es vor dem Auftritt des Interrupts gesetzt war. Falls in der ISR nur auf
		// Register ohne Schreibschutz zugegriffen wird, kann auf den folgenden Befehl
		// verzichtet werden (siehe Spalte "Write Protection" in der Registerübersicht)
		//EALLOW;
		// Messwert auslesen
		ADCINB3 = AdcbResultRegs.ADCRESULT0;

    // Interrupt-Flag im ADC-Modul löschen
		AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
		// Interrupt-Flag der Gruppe 1 löschen (da gehört der ADCB1_INT-Interrupt zu)
		PieCtrlRegs.PIEACK.bit.ACK1 = 1;
}


//=== Function: AdcCInt1ISR =======================================================================
///
/// @brief	ISR wird aufgerufen, wenn ein ADCINT1-Interrupt (Modul C) ausgelöst wurde
///
/// @param  void
///
/// @return void
///
//=================================================================================================
__interrupt void AdcCInt1ISR(void)
{
		// Bei jedem Eintritt in eine Interrupt-Service-Routine (ISR) wird automatisch
		// das EALLOW-Bit gelöscht, unabhängig davon, ob es zuvor gesetzt war (siehe
		// S. 148 Punkt 9, Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022).
		// Nach Abschluss der ISR wird das EALLOW-Bit automatisch wieder gesetzt, falls
		// es vor dem Auftritt des Interrupts gesetzt war. Falls in der ISR nur auf
		// Register ohne Schreibschutz zugegriffen wird, kann auf den folgenden Befehl
		// verzichtet werden (siehe Spalte "Write Protection" in der Registerübersicht)
		//EALLOW;
		// Messwert auslesen
		ADCINC3 = AdccResultRegs.ADCRESULT0;

    // Interrupt-Flag im ADC-Modul löschen
		AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
		// Interrupt-Flag der Gruppe 1 löschen (da gehört der ADCC1_INT-Interrupt zu)
		PieCtrlRegs.PIEACK.bit.ACK1 = 1;
}


//=== Function: AdcDInt1ISR =======================================================================
///
/// @brief	ISR wird aufgerufen, wenn ein ADCINT1-Interrupt (Modul D) ausgelöst wurde
///
/// @param  void
///
/// @return void
///
//=================================================================================================
__interrupt void AdcDInt1ISR(void)
{
		// Bei jedem Eintritt in eine Interrupt-Service-Routine (ISR) wird automatisch
		// das EALLOW-Bit gelöscht, unabhängig davon, ob es zuvor gesetzt war (siehe
		// S. 148 Punkt 9, Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022).
		// Nach Abschluss der ISR wird das EALLOW-Bit automatisch wieder gesetzt, falls
		// es vor dem Auftritt des Interrupts gesetzt war. Falls in der ISR nur auf
		// Register ohne Schreibschutz zugegriffen wird, kann auf den folgenden Befehl
		// verzichtet werden (siehe Spalte "Write Protection" in der Registerübersicht)
		//EALLOW;
		// Messwert auslesen
		ADCIND3 = AdcdResultRegs.ADCRESULT0;

    // Interrupt-Flag im ADC-Modul löschen
		AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
		// Interrupt-Flag der Gruppe 1 löschen (da gehört der ADCD1_INT-Interrupt zu)
		PieCtrlRegs.PIEACK.bit.ACK1 = 1;
}




