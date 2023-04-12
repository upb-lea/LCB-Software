//=================================================================================================
/// @file       myGPIO.c
///
/// @brief      Datei enthält Variablen und Funktionen um die GPIOs des Mikrocontrollers
///						  TMS320F2838x als Ausgänge, Eingänge oder Eingänge für externe interrupts
///							zu konfigurieren.
///
/// @version    V1.2
///
/// @date       13.02.2023
///
/// @author     Daniel Urbaneck
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "myGPIO.h"


//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Global functions
//-------------------------------------------------------------------------------------------------
//=== Function: GpioInit ==========================================================================
///
/// @brief  Funktion initialisiert GPIOs als Ein- bzw. Ausgänge
///
/// @param  void
///
/// @return void
///
//=================================================================================================
void GpioInit(void)
{
	  // Register-Schreibschutz aufheben
		EALLOW;

		//***************************************************************
		// LEDS AUF CONTROL-CARD
		//***************************************************************
		// GPIO 5 (LED D1002) als Ausgang konfigurieren:
    // Konfigurationssperre aufheben
    GpioCtrlRegs.GPALOCK.bit.GPIO5 = GPIO_CONFIG_UNLOCK;
    // Auf GPIO-Funktionalität setzen
    GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = (GPIO_MULTIPLEX_GPIO >> 2);
    GpioCtrlRegs.GPAMUX1.bit.GPIO5  = (GPIO_MULTIPLEX_GPIO & 0x03);
    // Pull-Up-Widerstand von deaktivieren
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = GPIO_DISABLE_PULLUP;
    // Auf low-Pegel setzen
    GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
    // Als Ausgang setzen
    GpioCtrlRegs.GPADIR.bit.GPIO5 = GPIO_OUTPUT;

		// GPIO 3 (LED D1003) als Ausgang konfigurieren:
    // Konfigurationssperre aufheben
    GpioCtrlRegs.GPALOCK.bit.GPIO3 = GPIO_CONFIG_UNLOCK;
    // Auf GPIO-Funktionalität setzen
    GpioCtrlRegs.GPAGMUX1.bit.GPIO3 = (GPIO_MULTIPLEX_GPIO >> 2);
    GpioCtrlRegs.GPAMUX1.bit.GPIO3  = (GPIO_MULTIPLEX_GPIO & 0x03);
    // Pull-Up-Widerstand von deaktivieren
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = GPIO_DISABLE_PULLUP;
    // Auf low-Pegel setzen
    GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
    // Als Ausgang setzen
    GpioCtrlRegs.GPADIR.bit.GPIO3 = GPIO_OUTPUT;

		// GPIO 2 (LED D1004) als Ausgang konfigurieren:
    // Konfigurationssperre aufheben
    GpioCtrlRegs.GPALOCK.bit.GPIO2 = GPIO_CONFIG_UNLOCK;
    // Auf GPIO-Funktionalität setzen
    GpioCtrlRegs.GPAGMUX1.bit.GPIO2 = (GPIO_MULTIPLEX_GPIO >> 2);
    GpioCtrlRegs.GPAMUX1.bit.GPIO2  = (GPIO_MULTIPLEX_GPIO & 0x03);
    // Pull-Up-Widerstand von deaktivieren
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = GPIO_DISABLE_PULLUP;
    // Auf low-Pegel setzen
    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
    // Als Ausgang setzen
    GpioCtrlRegs.GPADIR.bit.GPIO2 = GPIO_OUTPUT;

		// GPIO 6 (LED D1005) als Ausgang konfigurieren:
    // Konfigurationssperre aufheben
    GpioCtrlRegs.GPALOCK.bit.GPIO6 = GPIO_CONFIG_UNLOCK;
    // Auf GPIO-Funktionalität setzen
    GpioCtrlRegs.GPAGMUX1.bit.GPIO6 = (GPIO_MULTIPLEX_GPIO >> 2);
    GpioCtrlRegs.GPAMUX1.bit.GPIO6  = (GPIO_MULTIPLEX_GPIO & 0x03);
    // Pull-Up-Widerstand von deaktivieren
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = GPIO_DISABLE_PULLUP;
    // Auf low-Pegel setzen
    GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
    // Als Ausgang setzen
    GpioCtrlRegs.GPADIR.bit.GPIO6 = GPIO_OUTPUT;

		// GPIO 7 (LED D1006) als Ausgang konfigurieren:
    // Konfigurationssperre aufheben
    GpioCtrlRegs.GPALOCK.bit.GPIO7 = GPIO_CONFIG_UNLOCK;
    // Auf GPIO-Funktionalität setzen
    GpioCtrlRegs.GPAGMUX1.bit.GPIO7 = (GPIO_MULTIPLEX_GPIO >> 2);
    GpioCtrlRegs.GPAMUX1.bit.GPIO7  = (GPIO_MULTIPLEX_GPIO & 0x03);
    // Pull-Up-Widerstand von deaktivieren
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = GPIO_DISABLE_PULLUP;
    // Auf low-Pegel setzen
    GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
    // Als Ausgang setzen
    GpioCtrlRegs.GPADIR.bit.GPIO7 = GPIO_OUTPUT;


		//***************************************************************
		// LEDS FÜR PWM-AUSGANG
		//***************************************************************
    // ePWM1A-Signal auf GPIO 145 legen:
    // Konfigurationssperre aufheben
    GpioCtrlRegs.GPELOCK.bit.GPIO145 = 0;
    // Auf PWM-Funktionalität setzen
    // (siehe S. 1645 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    GpioCtrlRegs.GPEGMUX2.bit.GPIO145 = (1 >> 2);
    GpioCtrlRegs.GPEMUX2.bit.GPIO145  = (1 & 0x03);
    // Pull-Up-Widerstand deaktivieren
    GpioCtrlRegs.GPEPUD.bit.GPIO145 = 1;

    // ePWM2A-Signal auf GPIO 147 legen:
    // Konfigurationssperre aufheben
    GpioCtrlRegs.GPELOCK.bit.GPIO147 = 0;
    // Auf PWM-Funktionalität setzen
    // (siehe S. 1645 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    GpioCtrlRegs.GPEGMUX2.bit.GPIO147 = (1 >> 2);
    GpioCtrlRegs.GPEMUX2.bit.GPIO147  = (1 & 0x03);
    // Pull-Up-Widerstand deaktivieren
    GpioCtrlRegs.GPEPUD.bit.GPIO147 = 1;

    // ePWM3A-Signal auf GPIO 149 legen:
    // Konfigurationssperre aufheben
    GpioCtrlRegs.GPELOCK.bit.GPIO149 = 0;
    // Auf PWM-Funktionalität setzen
    // (siehe S. 1645 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    GpioCtrlRegs.GPEGMUX2.bit.GPIO149 = (1 >> 2);
    GpioCtrlRegs.GPEMUX2.bit.GPIO149  = (1 & 0x03);
    // Pull-Up-Widerstand deaktivieren
    GpioCtrlRegs.GPEPUD.bit.GPIO149 = 1;

    // ePWM4A-Signal auf GPIO 151 legen:
    // Konfigurationssperre aufheben
    GpioCtrlRegs.GPELOCK.bit.GPIO151 = 0;
    // Auf PWM-Funktionalität setzen
    // (siehe S. 1645 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    GpioCtrlRegs.GPEGMUX2.bit.GPIO151 = (1 >> 2);
    GpioCtrlRegs.GPEMUX2.bit.GPIO151  = (1 & 0x03);
    // Pull-Up-Widerstand deaktivieren
    GpioCtrlRegs.GPEPUD.bit.GPIO151 = 1;




    /*
	  // GPIO als EINGANG konfigurieren:
    // Konfigurationssperre für GPIO 80 aufheben
		// GPALOCK: GPIO 0   ... 31
		// GPBLOCK: GPIO 32  ... 63
		// GPCLOCK: GPIO 64  ... 95
		// GPDLOCK: GPIO 96  ... 127
		// GPELOCK: GPIO 128 ... 159
		// GPFLOCK: GPIO 160 ... 168
    GpioCtrlRegs.GPCLOCK.bit.GPIO80 = GPIO_CONFIG_UNLOCK;
    // GPIO 80 auf GPIO-Funktionalität setzen
    // Die Zahl in der obersten Zeile der Tabelle gibt den Wert für
    // GPAGMUX (MSB, 2 Bit) + GPAMUX (LSB, 2 Bit) als Dezimalzahl an
    // (siehe S. 1645 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    // GPAGMUX1: GPIO 0   ... 15	 	 GPAMUX1: GPIO 0   ... 15
    // GPAGMUX2: GPIO 16  ... 31	   GPAMUX2: GPIO 16  ... 31
    // GPBGMUX1: GPIO 32  ... 47		 GPBMUX1: GPIO 32  ... 47
    // GPBGMUX2: GPIO 48  ... 63		 GPBMUX2: GPIO 48  ... 63
    // GPCGMUX1: GPIO 64  ... 79		 GPCMUX1: GPIO 64  ... 79
    // GPCGMUX2: GPIO 80  ... 95		 GPCMUX2: GPIO 80  ... 95
    // GPDGMUX1: GPIO 96  ... 111	   GPDMUX1: GPIO 96  ... 111
    // GPDGMUX2: GPIO 112 ... 127	   GPDMUX2: GPIO 112 ... 127
    // GPEGMUX1: GPIO 128 ... 143		 GPEMUX1: GPIO 128 ... 143
    // GPEGMUX2: GPIO 144 ... 159		 GPEMUX2: GPIO 144 ... 159
    // GPFGMUX1: GPIO 160 ... 168	   GPFMUX1: GPIO 160 ... 168
    GpioCtrlRegs.GPCGMUX2.bit.GPIO80 = (GPIO_MULTIPLEX_GPIO >> 2);
    GpioCtrlRegs.GPCMUX2.bit.GPIO80  = (GPIO_MULTIPLEX_GPIO & 0x03);
    // Pull-Up-Widerstand von GPIO 80 aktivieren
    // GPAPUD: GPIO 0   ... 31
    // GPBPUD: GPIO 32  ... 63
		// GPCPUD: GPIO 64  ... 95
		// GPDPUD: GPIO 96  ... 127
		// GPEPUD: GPIO 128 ... 159
		// GPFPUD: GPIO 160 ... 168
    GpioCtrlRegs.GPCPUD.bit.GPIO80 = GPIO_ENABLE_PULLUP;
		// Art der Qualifizierung des Eingangs GPIO 80 setzen
		// 0: Bei jedem Sample (siehe GPxCTRL) wird der Eingang eingelsen und als High/Low gewertet
		// 1: 3 Samples (siehe GPxCTRL) müssen identisch sein, damit der Eingang als High/Low gewertet wird
		// 2: 6 Samples (siehe GPxCTRL) müssen identisch sein, damit der Eingang als High/Low gewertet wird
		// 3: Asynchron zum Systemtakt z.B. für I2C, SPI, PWM, etc.
    // GPAQSEL1: GPIO 0   ... 15
    // GPAQSEL2: GPIO 16  ... 31
    // GPBQSEL1: GPIO 32  ... 47
    // GPBQSEL2: GPIO 48  ... 63
    // GPCQSEL1: GPIO 64  ... 79
    // GPCQSEL2: GPIO 80  ... 95
    // GPDQSEL1: GPIO 96  ... 111
    // GPDQSEL2: GPIO 112 ... 127
    // GPEQSEL1: GPIO 128 ... 143
    // GPEQSEL2: GPIO 144 ... 159
    // GPFQSEL1: GPIO 160 ... 168
		GpioCtrlRegs.GPCQSEL2.bit.GPIO80 = 0;
    // Sample-Dauer für GPIO 80 setzen
		// Die Dauer entspricht 2*SYSCLK*GPxCTRL.QUALPRDx
    // GPACTRL.bit.QUALPRD0: GPIO 0   ... 7
    // GPACTRL.bit.QUALPRD1: GPIO 8   ... 15
    // GPACTRL.bit.QUALPRD2: GPIO 16  ... 23
    // GPACTRL.bit.QUALPRD3: GPIO 24  ... 31
    // GPBCTRL.bit.QUALPRD0: GPIO 32  ... 39
    // GPBCTRL.bit.QUALPRD1: GPIO 40  ... 47
    // GPBCTRL.bit.QUALPRD2: GPIO 48  ... 55
    // GPBCTRL.bit.QUALPRD3: GPIO 56  ... 63
    // GPCCTRL.bit.QUALPRD0: GPIO 64  ... 71
    // GPCCTRL.bit.QUALPRD1: GPIO 72  ... 79
    // GPCCTRL.bit.QUALPRD2: GPIO 80  ... 87
    // GPCCTRL.bit.QUALPRD3: GPIO 88  ... 95
    // GPDCTRL.bit.QUALPRD0: GPIO 96  ... 103
    // GPDCTRL.bit.QUALPRD1: GPIO 104 ... 111
    // GPDCTRL.bit.QUALPRD2: GPIO 112 ... 119
    // GPDCTRL.bit.QUALPRD3: GPIO 120 ... 127
    // GPECTRL.bit.QUALPRD0: GPIO 128 ... 135
    // GPECTRL.bit.QUALPRD1: GPIO 136 ... 143
    // GPECTRL.bit.QUALPRD2: GPIO 144 ... 151
    // GPECTRL.bit.QUALPRD3: GPIO 152 ... 159
    // GPFCTRL.bit.QUALPRD0: GPIO 160 ... 167
    // GPFCTRL.bit.QUALPRD1: GPIO 168
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD1 = 1;
    // GPIO 80 als Eingang setzen
    // 0: Eingang
    // 1: Ausgang
    // GPADIR: GPIO 0   ... 31
    // GPBDIR: GPIO 32  ... 63
    // GPCDIR: GPIO 64  ... 95
    // GPDDIR: GPIO 96  ... 127
    // GPEDIR: GPIO 128 ... 159
    // GPFDIR: GPIO 160 ... 168
    GpioCtrlRegs.GPCDIR.bit.GPIO80 = GPIO_INPUT;

    // GPIO als EINGANG für einen externen Interrupt konfigurieren:
    // Konfigurationssperre für GPIO 90 aufheben
    GpioCtrlRegs.GPCLOCK.bit.GPIO90 = GPIO_CONFIG_UNLOCK;
    // GPIO 90 auf GPIO-Funktionalität setzen
    GpioCtrlRegs.GPCGMUX2.bit.GPIO90 = (GPIO_MULTIPLEX_GPIO >> 2);
    GpioCtrlRegs.GPCMUX2.bit.GPIO90  = (GPIO_MULTIPLEX_GPIO & 0x03);
    // Pull-Up-Widerstand von GPIO 90 aktivieren
    GpioCtrlRegs.GPCPUD.bit.GPIO90 = GPIO_ENABLE_PULLUP;
    // GPIO 90 als Eingang setzen
    GpioCtrlRegs.GPCDIR.bit.GPIO90 = GPIO_INPUT;
    // GPIO 90 als Pin für den externen Interrupt XINT1 setzen.
    // Jeder der fünf externen Interrupts (XINT1 ... 5) ist an einem Ausgang der
    // Input-X-Bar angeschlossen (siehe S. 2142 Reference Manual TMS320F2838x,
    // SPRUII0D, Rev. D, July 2022).
    // Für jeden Interrupt muss ein GPIO ausgewählt werden.
    // 0: GPIO 0
    // 1: GPIO 1
    // 2: GPIO 2
    // ...
    InputXbarRegs.INPUT4SELECT = 90;
    // Interrupt durch fallende Flanke tiggern
    // 0: Fallende Flanke triggert Interrupt
    // 1: Steigende Flanke triggert Interrupt
    // 2: Fallende Flanke triggert Interrupt
    // 3: Steigende und fallende Flanke triggern Interrupt
    XintRegs.XINT1CR.bit.POLARITY = 0;
    // Externen Interrupt freischalten
    // 0: Interrupt deaktiviert
    // 1: Interrupt aktiviert
    XintRegs.XINT1CR.bit.ENABLE = 1;
    // CPU-Interrupts während der Konfiguration global sperren
    DINT;
    // Interrupt-Service-Routinen für den GPIO-Interrupt an die
    // entsprechende Stelle (XINT1_INT) der PIE-Vector Table speichern
    PieVectTable.XINT1_INT = &XINT1ISR;
    // INT1.4-Interrupt freischalten (Zeile 1, Spalte 4 der Tabelle 3-2)
    // (siehe S. 150 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;
    // CPU-Interrupt 1 einschalten (Zeile 1 der Tabelle)
    IER |= M_INT1;
    // CPU-Interrupts nach Konfiguration global wieder freigeben
    EINT;

    // Register-Schreibschutz setzen
    EDIS;
    */
}

