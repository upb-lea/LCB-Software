//=================================================================================================
/// @file       AD5664_cpu2.c
///
/// @brief      Datei enth�lt Variablen und Funktionen um den Digital-Analog-Converter AD5664
///							zu steuern
///
/// @version    V1.1
///
/// @date       13.02.2023
///
/// @author     Daniel Urbaneck
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "AD5664_cpu2.h"


//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------
// Flag speichert den aktuellen Zustand der SPI-Kommunikation  (bereit/Kommunikation aktiv)
uint32_t ad5664StatusFlag = AD5664_STATUS_IN_PROGRESS;


//-------------------------------------------------------------------------------------------------
// Global functions
//-------------------------------------------------------------------------------------------------
//=== Function: AD5664Init ========================================================================
///
/// @brief  Funktion initialisiert das SPI-D-Modul. Der Parameter "clock" gibt die gew�nschte
///					SPI-Taktfrequenz in Hz an
///
/// @param  void
///
/// @return uint32_t clock
///
//=================================================================================================
void AD5664Init(uint32_t clock)
{
    // Register-Schreibschutz aufheben
    EALLOW;

		// Warten, bis CPU 1 die Kontrolle �ber das SPI-D-Modul �bergeben hat
		while(Cpu2toCpu1IpcRegs.CPU1TOCPU2IPCSTS.bit.IPC0 == 0);
		// Flag l�schen
		Cpu2toCpu1IpcRegs.CPU2TOCPU1IPCACK.bit.IPC0 = 1;

    // Takt f�r das SPI-Modul einschalten und 5 Takte
    // warten, bis der Takt zum Modul durchgestellt ist
    // (siehe S. 169 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    CpuSysRegs.PCLKCR8.bit.SPI_D = 1;
    __asm(" RPT #4 || NOP");
		// SPI-Modul zum konfigurieren ausschalten
    SpidRegs.SPICCR.bit.SPISWRESET = 0;
    // Polarit�t = 0 (Ruhepegel: CLK = 0)
    SpidRegs.SPICCR.bit.CLKPOLARITY = 0;
    // Phase = 0 (Daten bei der ersten (mit POL = 0 also einer steigenden) Flanke �bernehmen)
    SpidRegs.SPICTL.bit.CLK_PHASE = 0;
    // 8-Bit Datenl�nge
    SpidRegs.SPICCR.bit.SPICHAR = 7;
    // Master-Mode setzen
    SpidRegs.SPICTL.bit.MASTER_SLAVE = 1;
    // �bertragung aktivieren
    SpidRegs.SPICTL.bit.TALK = 1;
    // Taktrate setzen
    // (Low-Speed CLK / clock) - 1
    // Low-Speed CLK = 50 MHz (siehe "DeviceInit()")
    SpidRegs.SPIBRR.bit.SPI_BIT_RATE = (50000000 / clock) - 1;
    // FIFO-Reset w�hrend der Konfiguration setzen
    SpidRegs.SPIFFTX.bit.TXFIFO = 0;
    // FIFO-Modus einschalten
    SpidRegs.SPIFFTX.bit.SPIFFENA = 1;
    // RX-FIFO Interrupt einschalten
    SpidRegs.SPIFFRX.bit.RXFFIENA = 1;
    // Interrupt ausl�sen, wenn 3 Bytes empfangen wurden
    SpidRegs.SPIFFRX.bit.RXFFIL = 3;
    // RX-FIFO Interupt-Flag l�schen
    SpidRegs.SPIFFRX.bit.RXFFINTCLR = 1;
    // FIFO-Reset aufheben
    SpidRegs.SPIFFTX.bit.TXFIFO = 1;
    // SPI-Modul wieder einschalten
    SpidRegs.SPICCR.bit.SPISWRESET = 1;

    // CPU-Interrupts w�hrend der Konfiguration global sperren
    DINT;
    // Interrupt-Service-Routinen f�r den SPI-Interrupt an die
    // entsprechende Stelle (SPID_RX_INT) der PIE-Vector Table speichern
    PieVectTable.SPID_RX_INT = &AD5664SpiISR;
    // SPID_RX-Interrupt freischalten (Zeile 6, Spalte 11 der Tabelle 3-2)
    // (siehe S. 150 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    PieCtrlRegs.PIEIER6.bit.INTx11 = 1;
    // CPU-Interrupt 6 einschalten (Zeile 6 der Tabelle)
    IER |= M_INT6;
    // CPU-Interrupts nach Konfiguration global wieder freigeben
    EINT;

    // Status auf "bereit" setzen
    ad5664StatusFlag = AD5664_STATUS_IDLE;

		// Register-Schreibschutz setzen
		EDIS;
}


//=== Function: AD566SetChannel ===================================================================
///
/// @brief  Funktion setzt den Wert f�r einen Kanal (A, B, C oder D) des DAC.
///					Der Wert wird vom DAC anschlie�end direkt �bernommen
///
/// @param  uint16_t channel, uint16_t value
///
/// @return void
///
//=================================================================================================
void AD566SetChannel(uint16_t channel,
										 uint16_t value)
{
		// Flag setzen um der aufrufenden Stelle zu signalisieren,
		// dass eine SPI-Kommunikation gestartet wurde
		ad5664StatusFlag = AD5664_STATUS_IN_PROGRESS;
		// Daten in den SPI-Hardware-Puffer kopieren (16 Byte, Daten m�ssen links-b�nig sein,
		// siehe S. 3904 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022):
		// Steuer-Byte (neuen DAC-Wert sofort setzen)
		SpidRegs.SPITXBUF = ( (AD5664_WRITE_REG_SET_DAC | channel) << 8 );
		// Daten MSB
		SpidRegs.SPITXBUF = ( ((value >> 8) & 0xFF) << 8 );
		// Daten LSB
		SpidRegs.SPITXBUF = ( (value & 0xFF) << 8 );
}


//=== Function: AD5664SpiISR ======================================================================
///
/// @brief	Funktion wird aufgerufen, sobald drei Bytes �ber SPI empfangen wurde. F�r den Betrieb
///					des Hardware-Monitors werden die Daten �ber SPI zwar nur gesendet, aber die Konfigu-
///					ration des Sende-Interrupts ist komplizierter als die des Emfangs-Interrupts. Zudem
///					wird der Sende-Interrupt ausgel�st, sobal der TX-Puffer leer ist. Zu diesem Zeitpunkt
///					befindet sich das letzte zu sendene Byte jedoch noch im Ausgangsregister. Der Interrupt
///					kommt also zu fr�h. Aus diesem Grund und weil beim Senden auch automatisch Daten
///					empfangen werden, wurde hier die Kommunikation mithilfe des Empfangs-Interrupts umge-
///					setzt.
///
/// @param  void
///
/// @return void
///
//=================================================================================================
__interrupt void AD5664SpiISR(void)
{
		// Bei jedem Eintritt in eine Interrupt-Service-Routine (ISR) wird automatisch
		// das EALLOW-Bit gel�scht, unabh�ngig davon, ob es zuvor gesetzt war (siehe
		// S. 148 Punkt 9, Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022).
		// Nach Abschluss der ISR wird das EALLOW-Bit automatisch wieder gesetzt, falls
		// es vor dem Auftritt des Interrupts gesetzt war. Falls in der ISR nur auf
		// Register ohne Schreibschutz zugegriffen wird, kann auf den folgenden Befehl
		// verzichtet werden (siehe Spalte "Write Protection" in der Register�bersicht)
		//EALLOW;

		// Status auf "bereit" setzen
		ad5664StatusFlag = AD5664_STATUS_IDLE;
		// Empfangene Bytes auslesen
		uint16_t dummy = SpidRegs.SPIRXBUF;
		dummy = SpidRegs.SPIRXBUF;
		dummy = SpidRegs.SPIRXBUF;

    // RX-FIFO Interupt-Flag l�schen
    SpidRegs.SPIFFRX.bit.RXFFINTCLR = 1;
		// Interrupt-Flag der Gruppe 6 l�schen (da geh�rt der SPI-Interrupt zu)
    PieCtrlRegs.PIEACK.bit.ACK6 = 1;
}
