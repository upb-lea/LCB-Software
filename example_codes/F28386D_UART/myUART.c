//=================================================================================================
/// @file       uart.c
///
/// @brief      Datei enthält Variablen und Funktionen um die UART-Schnittstelle (SCI) eines
///							TMS320F283x zu benutzen. Die Kommunikation ist Interrupt-basiert. Zum Senden wird
////						die Funktion "UartTransmit()" aufgerufen und die zu sendene Anzahl an Bytes als
///							Parameter übergeben. Die zu sendenen Daten werden zuvor in den Puffer
///							"uartBufferTx[]" geschrieben. Der Empfangsvorgang wird durch Aufruf der Funktion
///							"UartReceive()" freigegeben. Da UART asynchron ist, kann der Empfangsvorgang nur
///							freigegeben, aber nicht aktiv forciert werden. Nach Aufruf der Funktion
///							"UartReceive()", sollte in regelmäßigen Abständen die Funktion "UartGetStatusRx()"
///							aufgerufen werden um den korekten/vollständigen Empfang eines Datenpakets zu
///							prüfen. Näheres ist der Beschreibung der Funktion "UartGetStatusRx()" zu entnehmen.
///							Es wird das SCI-A Modul verwendet. Die Module B, C und D können analog zu den hier
///							gezeigten Funktionen verwendet werden.
///
///							Änderung in Version 2.0: Verwendung der Hardware-FIFOs
///
/// @version    V2.0
///
/// @date       24.03.2023
///
/// @author     Daniel Urbaneck
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "myUART.h"


//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------
// Software-Puffer für die UART-Kommunikation
uint16_t uartBufferRxA[UART_SIZE_SOFTWARE_BUFFER_RX];
uint16_t uartBufferTxA[UART_SIZE_SOFTWARE_BUFFER_TX];
// Steuern das Kopieren in und aus den Software-Puffern während der UART-Kommunikation
uint16_t uartBufferIndexRxA;
uint16_t uartBufferIndexTxA;
uint16_t uartBufferIndexRxOldA;
uint16_t uartBytesToTransferRxA;
uint16_t uartBytesToTransferTxA;
// Dient zur Erkennung des Empfangsvorgangs
uint32_t uartOldValueFifoBufferA;
// Flags speichern den aktuellen Zustand der UART-Kommunikation
uint16_t uartStatusFlagRxA;
uint16_t uartStatusFlagTxA;
// Flag kann zum Aufruf der Funktion "UartGetStatusRxA()" genutzt werden
// und sollte dazu regelmäßig (z.B. alle 5 ms) in einer ISR gesetzt werden.
// Anschließend kann z.B. im Hauptprogramm bei gesetztem Flag die Funktion
// aufgerufen und das Flag gelöscht werden
bool uartFlagCheckRxA;
// Timeout-Zähler für den Empfang eines Datenpakets
int32_t uartRxTimeoutA = UART_NO_TIMEOUT;


//-------------------------------------------------------------------------------------------------
// Global functions
//-------------------------------------------------------------------------------------------------
//=== Function: UartInitA =========================================================================
///
/// @brief  Funktion initialisiert GPIO 28 und 135 als UART-Pins und das
///         SCI-A Modul für den UART-Betrieb mit der gewünschten Baudrate.
///
/// @param  uint32_t baud, uint32_t numberOfDataBits, uint32_t numberOfStopBits, uint32_t parity
///
/// @return void
///
//=================================================================================================
void UartInitA(uint32_t baud,
							 uint32_t numberOfDataBits,
							 uint32_t numberOfStopBits,
							 uint32_t parity)
{
    // Register-Schreibschutz aufheben
    EALLOW;

    // Rx-Pin
    // GPIO-Sperre für GPIO 28 aufheben
    GpioCtrlRegs.GPALOCK.bit.GPIO28 = 0;
    // GPIO 28 auf UART-Funktion setzen (RxD)
    // Die Zahl in der obersten Zeile der Tabelle gibt den Wert für
    // GPAGMUX (MSB, 2 Bit) + GPAMUX (LSB, 2 Bit) als Dezimalzahl an.
    // (siehe S. 1645 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    GpioCtrlRegs.GPAGMUX2.bit.GPIO28 = (1 >> 2);
    GpioCtrlRegs.GPAMUX2.bit.GPIO28  = (1 & 0x03);
    // GPIO 28 Pull-Up-Widerstand deaktivieren
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 1;
    // GPIO 28 Asynchroner Eingang (muss für UART gesetzt sein)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 0x03;

    // Tx-Pin:
    // GPIO-Sperre aufheben
    GpioCtrlRegs.GPELOCK.bit.GPIO135 = 0;
    // Auf UART-Funktion setzen (TxD)
    // Die Zahl in der obersten Zeile der Tabelle gibt den Wert für
    // GPAGMUX (MSB, 2 Bit) + GPAMUX (LSB, 2 Bit) als Dezimalzahl an.
    // (siehe S. 1645 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    GpioCtrlRegs.GPEGMUX1.bit.GPIO135 = (6 >> 2);
    GpioCtrlRegs.GPEMUX1.bit.GPIO135  = (6 & 0x03);
    // Pull-Up-Widerstand deaktivieren
    GpioCtrlRegs.GPEPUD.bit.GPIO135 = 1;
    // Asynchroner Eingang (muss für UART gesetzt sein)
    GpioCtrlRegs.GPEQSEL1.bit.GPIO135 = 0x03;

    // Takt für das UART-Modul einschalten und 5 Takte
    // warten, bis der Takt zum Modul durchgestellt ist
    // (siehe S. 169 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
    __asm(" RPT #4 || NOP");
    // Baudrate setzen
    // (Low-Speed CLK / (BAUD * SCICHAR)) - 1
    // Low-Speed CLK = 50 MHz (siehe "DeviceInit()")
    uint32_t divider = (50000000 / (baud * 8U)) - 1U;
    SciaRegs.SCIHBAUD.bit.BAUD = (divider & 0xFF00) >> 8;
    SciaRegs.SCILBAUD.bit.BAUD =  divider & 0x00FF;
    // Anzahl der Datenbits setzen
    SciaRegs.SCICCR.bit.SCICHAR = numberOfDataBits;
    // Anzahl der Stopbits setzen
    SciaRegs.SCICCR.bit.STOPBITS = numberOfStopBits;
    // Parität setzen
		switch (parity)
		{
				// Gerade Parität
				case UART_PARITY_EVEN:
						SciaRegs.SCICCR.bit.PARITYENA = 1;
						SciaRegs.SCICCR.bit.PARITY    = 1;
						break;
				// Ungerade Parität
				case UART_PARITY_ODD:
						SciaRegs.SCICCR.bit.PARITYENA = 1;
						SciaRegs.SCICCR.bit.PARITY    = 0;
						break;
				// Keine Parität
				default:
						SciaRegs.SCICCR.bit.PARITYENA = 0;
		}
    // RxD und TxD ausschalten
    SciaRegs.SCICTL1.bit.RXENA = 0;
    SciaRegs.SCICTL1.bit.TXENA = 0;
    // Soft-Reset deaktivieren (mit aktiverten
		// Soft-Reset ist der FIFO-Modus ausgeschaltet)
    SciaRegs.SCICTL1.bit.SWRESET = 1;
    // FIFO-Modus (für Tx und Rx) einschalten
    SciaRegs.SCIFFTX.bit.SCIFFENA = 1;
    // FIFO-Interrupts ausschalten
    SciaRegs.SCIFFRX.bit.RXFFIENA = 0;
    SciaRegs.SCIFFTX.bit.TXFFIENA = 0;

    // CPU-Interrupts während der Konfiguration global sperren
    DINT;
    // Interrupt-Service-Routinen für den RxD-Interrupt an die
    // entsprechende Stelle (SCIA_RX_INT) der PIE-Vector Table speichern
    PieVectTable.SCIA_RX_INT = &UartRxISRA;
    // SCIA_RX-Interrupt freischalten (Zeile 9, Spalte 1 der Tabelle)
    // (siehe PIE-Vector Table S. 150 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;
    // Interrupt-Service-Routinen für den TxD-Interrupt an die
    // entsprechende Stelle (SCIA_TX_INT) der PIE-Vector Table speichern
    PieVectTable.SCIA_TX_INT = &UartTxISRA;
    // SCIA_TX-Interrupt freischalten (Zeile 9, Spalte 2 der Tabelle 3-2)
    // (siehe S. 150 Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022)
    PieCtrlRegs.PIEIER9.bit.INTx2 = 1;
    // CPU-Interrupt 9 einschalten (Zeile 9 der Tabelle 3-2)
    IER |= M_INT9;
    // CPU-Interrupts nach Konfiguration global wieder freigeben
    EINT;

		// Register-Schreibschutz setzen
		EDIS;

    // Software-Puffer inititalisieren
    UartInitBufferRxA();
    UartInitBufferTxA();
    // Steuervariablen initialisieren
    uartBufferIndexRxA     = 0;
    uartBufferIndexTxA     = 0;
    uartBufferIndexRxOldA  = uartBufferIndexRxA;
    uartBytesToTransferRxA = 0;
		uartBytesToTransferTxA = 0;
		uartStatusFlagRxA      = UART_STATUS_IDLE;
		uartStatusFlagTxA      = UART_STATUS_IDLE;
		uartFlagCheckRxA       = false;
		uartRxTimeoutA         = UART_NO_TIMEOUT;
}


//=== Function: UartInitBufferRxA =================================================================
///
/// @brief  Funktion initialisiert alle Elemente des UART Software-Empfangspuffers zu 0.
///
/// @param  void
///
/// @return void
///
//=================================================================================================
void UartInitBufferRxA(void)
{
    for(uint16_t i=0; i<UART_SIZE_SOFTWARE_BUFFER_RX; i++)
    {
        uartBufferRxA[i] = 0;
    }
}


//=== Function: UartInitTxBufferA =================================================================
///
/// @brief  Funktion initialisiert alle Elemente des UART Software-Sendepuffers zu 0.
///
/// @param  void
///
/// @return void
///
//=================================================================================================
void UartInitBufferTxA(void)
{
    for(uint16_t i=0; i<UART_SIZE_SOFTWARE_BUFFER_TX; i++)
    {
        uartBufferTxA[i] = 0;
    }
}


//=== Function: UartGetStatusRxA ==================================================================
///
/// @brief	Funktion gibt den aktuellen Status der UART-Kommunikation (Empfangs-Prozess) zurück
///				  und prüft den Empfang von Daten, d.h. es wird abhängig vom Wert der Variable
///					"uartBytesToTransferRxA" (wird über die Funktion "UartReceiveA()" gesetzt) die
///					Gültigkeit der empfangenen Daten geprüft (Länge des empfangenen Datenpakets). Damit
///					diese Prüfung funktioniert, muss die Funktion innerhalb eines definierten Intervalls
///					aufgerufen werden. Die min. Zeit zwischen den Aufrufen muss länger sein, als der
///					Empfang eines vollständigen Datenpakets dauert:
///
///         t_min > ((1 Start-Bit + 1 Stop-Bit + 8 Daten-Bits)/Baud-Rate) * Bytes pro Datenpaket
///
///					Die max. Zeit richtet sich nach der Häufigkeit der zu empfangenen Daten. Die
///					Kommunikation ist Interrupt-basiert. Die Funktion gibt folgende Zustände der
///					Kommunikation zurück:
///
///					- UART_STATUS_IDLE       : Es ist keine Empfangs-Kommunikation aktiv
///					- UART_STATUS_IN_PROGRESS: Es werde mindestens 1 Byte empfangen
///					- UART_STATUS_FINISHED   : Eine Empfangs-Kommunikation ist abgeschlossen
///
///					Zum starten einer Empfangs-Kommunikation muss die Funktionen "UartReceiveA()"
///					aufgerufen werden. Dabei wird nicht aktiv ein Empfang durchgeführt, da UART nicht
///					Master-Slave-basiert ist. Siehe hierzu die Beschreibung der Funktion "UartReceiveA()".
///
/// @param	void
///
/// @return uint16_t uartStatusFlagRxA
///
//=================================================================================================
extern uint16_t UartGetStatusRxA(void)
{
		// Die Kommunikaton wurde gestartet
		if (uartStatusFlagRxA == UART_STATUS_IN_PROGRESS)
		{
				// Es wurden seit dem letzten Aufruf der Funktion
				// keine neuen Daten in den Software-Puffer kopiert
				if (uartBufferIndexRxA == uartBufferIndexRxOldA)
				{
						// Es wurde ein vollständiges Datenpaket empfangen
						// und keine weiteren Daten empfangen (FIFO ist leer)
						if (   (uartBufferIndexRxA == uartBytesToTransferRxA)
							  && !SciaRegs.SCIFFRX.bit.RXFFST)
						{
						    // Empfangen ausschalten
						    SciaRegs.SCICTL1.bit.RXENA = 0;
						    // Empfangs-FIFO-Interrupt ausschalten
						    SciaRegs.SCIFFRX.bit.RXFFIENA = 0;
								// Timeout-Zähler initialisieren
								uartRxTimeoutA = UART_NO_TIMEOUT;
								// Status-Flag setzen
								uartStatusFlagRxA = UART_STATUS_FINISHED;
						}
						// Es wurde mindestens ein Byte in den Software-Puffer kopiert, jedoch kein
						// komplettes Datenpaket (entweder zu wenige oder zu viele Bytes empfangen)
						// oder es wurden weniger Bytes empfangen, als das Interrupt-Niveau. Die
						// letzte Bedingung würde zutreffen, wenn diese Funktion kurz nach Beginn
						// einer Empfangskommunikation aufgerufen wird, also wenn bereits ein Paar
						// Bytes empfangen wurden, jedoch deren Anzahl noch unterhalb des ersten
						// Interrupt-Niveaus liegt. Damit hierdurch die Abfrage-Bedingung nicht
						// erfüllt wird, wird der Wert der empfangenen Bytes mit dem aus dem vor-
						// herigen Funktionsaufruf verglichen
						else if (   uartBufferIndexRxA
										 || (SciaRegs.SCIFFRX.bit.RXFFST && (SciaRegs.SCIFFRX.bit.RXFFST == uartOldValueFifoBufferA)))
						{
						    // Empfangen ausschalten
						    SciaRegs.SCICTL1.bit.RXENA = 0;
						    // Empfangs-FIFO-Interrupt ausschalten
						    SciaRegs.SCIFFRX.bit.RXFFIENA = 0;
								// Status auf "bereit" setzen
								uartStatusFlagRxA = UART_STATUS_IDLE;
						}
				}
				// Es wurden seit dem letzten Aufruf der Funktion neue Daten in den Software-Puffer kopiert
				else
				{
						// Alten und neuen Zähler synchronisieren
						uartBufferIndexRxOldA = uartBufferIndexRxA;
				}
				// Aktuelle Zahl der im Empfangs-FIFO befindlichen Bytes speichern.
				// Wird zur Erkennung von Empfangsfehlern benötigt
				uartOldValueFifoBufferA = SciaRegs.SCIFFRX.bit.RXFFST;
				// Innerhalb des vorgegebenen Zeitfensters (wird bei Aufruf der Funktion
				// "UartReceive()" übergeben) wurde kein vollständiges Datenpaket empfangen
				if (uartRxTimeoutA == 0)
				{
						// Zähler initialisieren, damit der Empfangsvorgang
						// in dieser Funktion nur einmalig abgebochen wird
						uartRxTimeoutA = UART_NO_TIMEOUT;
				    // Empfangen ausschalten
				    SciaRegs.SCICTL1.bit.RXENA = 0;
				    // Empfangs-FIFO-Interrupt ausschalten
				    SciaRegs.SCIFFRX.bit.RXFFIENA = 0;
						// Staus auf "Timeout" setzen
						uartStatusFlagRxA = UART_STATUS_RX_TIMEOUT;
				}
		}
		return uartStatusFlagRxA;
}


//=== Function: UartGetStatusTxA ==================================================================
///
/// @brief	Funktion gibt den aktuellen Status der Tx UART-Kommunikation (senden) zurück.
///					Die Kommunikation ist Interrupt-basiert und kann folgende Zustände annehmen:
///
///					- UART_STATUS_IDLE       : Es ist keine Sende-Kommunikation aktiv
///					- UART_STATUS_IN_PROGRESS: Eine Sende-Kommunikation wurde gestartet
///					- UART_STATUS_FINISHED   : Das letzte Byte wurde begonnen zu senden,
///																		 ist aber noch nicht koplett versendet
///
///					Zum starten einer Sende-Kommunikation muss die Funktionen "UartTransmitA()"
///					aufgerufen werden.
///
/// @param	void
///
/// @return uint16_t uartStatusFlagTx
///
//=================================================================================================
extern uint16_t UartGetStatusTxA(void)
{
		return uartStatusFlagTxA;
}


//=== Function: UartSetStatusIdleRxA ==============================================================
///
/// @brief	Funktion setzt das Rx Status-Flag auf "idle" und gibt "true" zurück, falls die vorherige
///					Kommunikation abgeschlossen ist. Ist noch eine Kommunikation aktiv, wird das Flag nicht
///					verändert und es wird "false" zurück gegeben.
///
/// @param	void
///
/// @return bool flagSetToIdle
///
//=================================================================================================
extern bool UartSetStatusIdleRxA(void)
{
		bool flagSetToIdle = false;
		// Staus-Flag nur auf "idle" setzen, falls eine
		// vorherige Kommunikation abgeschlossen ist
		if (uartStatusFlagRxA != UART_STATUS_IN_PROGRESS)
		{
				uartStatusFlagRxA = UART_STATUS_IDLE;
				flagSetToIdle = true;
		}
		return flagSetToIdle;
}


//=== Function: UartSetStatusIdleTxA ==============================================================
///
/// @brief	Funktion setzt das Tx Status-Flag auf "idle" und gibt "true" zurück, falls die vorherige
///					Kommunikation abgeschlossen ist. Ist noch eine Kommunikation aktiv, wird das Flag nicht
///					verändert und es wird "false" zurück gegeben.
///
/// @param	void
///
/// @return bool flagSetToIdle
///
//=================================================================================================
extern bool UartSetStatusIdleTxA(void)
{
		bool flagSetToIdle = false;
		// Staus-Flag nur auf "idle" setzen, falls eine
		// vorherige Kommunikation abgeschlossen ist
		if (uartStatusFlagTxA == UART_STATUS_FINISHED)
		{
				uartStatusFlagTxA = UART_STATUS_IDLE;
				flagSetToIdle = true;
		}
		return flagSetToIdle;
}


//=== Function: UartReceiveA ======================================================================
///
/// @brief  Funktion konfiguriert die Steuervariablen und den Empfangs-Interrupt so, dass Daten
///					über UART empfangen werden können. Der Parameter "numberOfBytesRx" gibt an, wie viele
///					Bytes empfangen werden sollen. Wenn diese Anzahl erreicht ist, gibt die Funktion
///					"UartGetStatusRxA()" bei Aufruf den Wert "UART_STATUS_RX_FINISHED" zurück (Daten
///					vollständig empfangen). Wird innerhalb des mit dem Parameter "timeOut" übergebenen
///					Zeitfensters (= timeOut * 5 ms) kein vollständiges Datenpaket empfangen, so wird
///					der Empfangsvorgang abgebrochen (z.B. im Hauptprogramm durch Abfrage der Variable
///         "uartRxTimeoutA" auf 0). Da UART eine asynchrone Schnittstelle ist, ist die Funktion
///					"UartReceiveA()" nicht als Funktion zum forcierten Empfangen von Daten zu verstehen,
///					sondern als initialisierende Vorbereitung zum Empfang vom Daten.
///
/// @param  uint16_t numberOfBytesRx, int32_t timeOut
///
/// @return bool operationPerformed
///
//=================================================================================================
extern bool UartReceiveA(uint16_t numberOfBytesRx,
												 int32_t timeOut)
{
		// Ergebnis des Funktionsaufrufes (Empfangsvorgang initiiert / nicht initiiert)
		bool operationPerformed = false;
		// Vorgang nur starten falls keine vorherige Kommunikation aktiv ist
		// und die Anzahl der zu empfangenen Bytes die Größe des Software-Puffers
		// nicht überschreitet und mindestens 1 ist
		if ((uartStatusFlagRxA != UART_STATUS_IN_PROGRESS)
				&& (numberOfBytesRx <= UART_SIZE_SOFTWARE_BUFFER_RX)
				&& numberOfBytesRx)
		{
				// Rückgabewert auf "true" setzen, um der aufrufenden Stelle
				// zu signalisieren, dass der Empfangsvorgang initiiert wurde
				operationPerformed = true;
				// Flag setzen um der aufrufenden Stelle zu signalisieren,
				// dass eine UART-Kommunikation gestartet wurde
				uartStatusFlagRxA = UART_STATUS_IN_PROGRESS;
				// Timeout-Zähler auf den übergebenen Wert setzen
				uartRxTimeoutA = timeOut;

				// Index zur Verwaltung des Software-Puffers "uartBufferRxA[]" auf das erste Element
				// setzen, damit die zu sendenen Daten vom Anfang des Puffers beginnend kopiert werden
				uartBufferIndexRxA    = 0;
				uartBufferIndexRxOldA = 0;
				// Menge der zu empfangenen Bytes an die Steuervariable übergeben.
				// Diese koordiniert die restliche Kommunikation in der ISR und
				// der Funktion "UartGetStatusRxA()"
				uartBytesToTransferRxA = numberOfBytesRx;
				// Empfangs-FIFO leeren, falls in diesem noch Daten vorhanden sind
				while (SciaRegs.SCIFFRX.bit.RXFFST > 0)
				{
						uint16_t dummy = SciaRegs.SCIRXBUF.bit.SAR;
				}
				uartOldValueFifoBufferA = SciaRegs.SCIFFRX.bit.RXFFST;
		    // Empfangs-FIFO-Interrupt auslösen, wenn die Anzahl
				// erwarteter Bytes empfangen wurde oder die max.
				// Kapazität des FIFOs erreicht ist
		    SciaRegs.SCIFFRX.bit.RXFFIL = numberOfBytesRx;
		    if (numberOfBytesRx > UART_SIZE_HARDWARE_FIFO)
		    {
		    		SciaRegs.SCIFFRX.bit.RXFFIL = UART_SIZE_HARDWARE_FIFO;
		    }
		    // Evtl. gesetztes Overflow-Flag löschen, da kein Interrupt
		    // ausgelöst werden, falls das Bit gesetzt ist
		    SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
		    //Empfangs-FIFO-Interrupt-Flag löschen
		    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;
		    // Empfangs-FIFO-Interrupt einschalten
		    SciaRegs.SCIFFRX.bit.RXFFIENA = 1;
		    // Empfangen einschalten
		    SciaRegs.SCICTL1.bit.RXENA = 1;
		}
		return operationPerformed;
}


//=== Function: UartTransmitA =====================================================================
///
/// @brief  Funktion sendet über UART Daten aus dem Sotware-Puffer "uartBufferTx[]". Der
///					Parameter "numberOfBytesTx" gibt an, wie viele Bytes gesendet werden sollen. Es
///				  wird der Hardware-FIFO des Mikrocontrollers benutzt. In diesen werden zunächst
///					die Daten aus dem Software-Puffer "uartBufferTx[]" kopiert. Sollen mehr Bytes
///					versendet werden, als der FIFO fasst, so wird der FIFO vollständig gefüllt und
///					im nächsten Aufruf der ISR die restlichen Bytes in den Sende-FIFO kopiert. Die
///					ISR wird aufgerufen, sobald der Sende-FIFO leer ist.
///
/// @param  uint16_t numberOfBytesTx
///
/// @return bool operationPerformed
///
//=================================================================================================
extern bool UartTransmitA(uint16_t numberOfBytesTx)
{
		// Ergebnis des Funktionsaufrufes (Sendevorgang gestartet / nicht gestartet)
		bool operationPerformed = false;
		// Vorgang nur starten falls keine vorherige Kommunikation aktiv ist
		// und die Anzahl der zu sendenen Bytes die Größe des Software-Puffers
		// nicht überschreitet und mindestens 1 ist
		if ((uartStatusFlagTxA != UART_STATUS_IN_PROGRESS)
				&& (numberOfBytesTx <= UART_SIZE_SOFTWARE_BUFFER_TX)
				&& numberOfBytesTx)
		{
				// Rückgabewert auf "true" setzen, um der aufrufenden Stelle
				// zu signalisieren, dass der Sendevorgang gestartet wurde
				operationPerformed = true;
				// Flag setzen um der aufrufenden Stelle zu signalisieren,
				// dass eine UART-Kommunikation gestartet wurde
				uartStatusFlagTxA = UART_STATUS_IN_PROGRESS;
				// Index zur Verwaltung des Software-Puffers "uartBufferTxA[]" auf das erste Element
				// setzen, damit die zu sendenen Daten vom Anfang des Puffers aus kopiert werden
				uartBufferIndexTxA = 0;
				// Menge der zu sendenen Bytes an die Steuervariable übergeben.
				// Diese koordiniert die restliche Kommunikation in der ISR
				uartBytesToTransferTxA = numberOfBytesTx;
		    // Senden einschalten (muss VOR dem Beschreiben des Sende-FIFOs gesetzt werden)
		    SciaRegs.SCICTL1.bit.TXENA = 1;
		    // Zu sendene Daten von dem Software-Puffer in den Sende-FIFO kopieren
				// bis dieser gefüllt ist oder der Software-Puffer leer ist
				while (   (uartBufferIndexTxA < uartBytesToTransferTxA)
							 && (SciaRegs.SCIFFTX.bit.TXFFST < UART_SIZE_HARDWARE_FIFO))
				{
						SciaRegs.SCITXBUF.bit.TXDT = uartBufferTxA[uartBufferIndexTxA];
						uartBufferIndexTxA++;
				}
		    // Sende-FIFO-Interrupt-Flag löschen
		    SciaRegs.SCIFFTX.bit.TXFFINTCLR = 1;
		    // Tx-FIFO-Interrupt wird ausgelöst, wenn der Wert in SCIFFTX.TXFFST gleich oder
		    // kleiner SCIFFTX.TXFFIL ist. SCIFFTX.TXFFST gibt die Anzahl der sich im Sende-
		    // FIFO befindlichen Bytes an. Dieser Wert wird mit jedem vom Sende-FIFO in das
		    // Sende-Schieberegister kopierte Byte um 1 reduziert. ACHTUNG: SCIFFTX.TXFFST
		    // = 0 bedeutet nicht, dass das Senden abgeschlossen sit, da sich das letzte Byte
		    // noch im Sende-Shift-Register befindet und Bit für Bit ausgesendet wird. Um zu
		    // prüfen, ob der Sendevorgang vollständig abgeschlossen ist, muss das Bit
		    // SCICTL2.TXEMPTY abgefragt werden. Dies ist 1, sobald Sende-FIFO und Sende-
		    // Shift-Register leer sind.
		    // Sende-FIFO-Interrupt auslösen, wenn der Sende-FIFO leer ist
		    SciaRegs.SCIFFTX.bit.TXFFIL = 0;
		    // Tx-FIFO-Interrupt einschalten
		    SciaRegs.SCIFFTX.bit.TXFFIENA = 1;
		}
		return operationPerformed;
}


//=== Function: UartRxISRA ========================================================================
///
/// @brief  ISR wird aufgerufen, sobald der (Hardware-) Empfangs-FIFO voll ist oder die Anzahl
///					an Bytes die im Register SCIFFRX.RXFFIL steht empfangen wurde. Aus dem Empfangs-
///					FIFO werden die Daten in den Software-Puffer "uartBufferRxA[]" kopiert, bis die
///					erwartete Zahl an Bytes (uartBytesToTransferRx) erreicht ist.
///
/// @param  void
///
/// @return void
///
//=================================================================================================
__interrupt void UartRxISRA(void)
{
		// Bei jedem Eintritt in eine Interrupt-Service-Routine (ISR) wird automatisch
		// das EALLOW-Bit gelöscht, unabhängig davon, ob es zuvor gesetzt war (siehe
		// S. 148 Punkt 9, Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022).
		// Nach Abschluss der ISR wird das EALLOW-Bit automatisch wieder gesetzt, falls
		// es vor dem Auftritt des Interrupts gesetzt war. Falls in der ISR nur auf
		// Register ohne Schreibschutz zugegriffen wird, kann auf den folgenden Befehl
		// verzichtet werden (siehe Spalte "Write Protection" in der Registerübersicht)
		//EALLOW;

		// Daten aus dem Empfangs-FIFO in den Software-Puffer kopieren bis die
		// erwartete Anzahl an Bytes empfangen wurde oder der FIFO leer ist
		while (   (uartBufferIndexRxA < uartBytesToTransferRxA)
					 && (SciaRegs.SCIFFRX.bit.RXFFST > 0))
		{
				uartBufferRxA[uartBufferIndexRxA] = SciaRegs.SCIRXBUF.bit.SAR;
				uartBufferIndexRxA++;
		}
		// Es werden noch weitere Bytes erwartet -> neues Interrupt-Niveau setzen
		if (uartBufferIndexRxA < uartBytesToTransferRxA)
		{
		    if ((uartBytesToTransferRxA - uartBufferIndexRxA) > UART_SIZE_HARDWARE_FIFO)
		    {
		    		SciaRegs.SCIFFRX.bit.RXFFIL = UART_SIZE_HARDWARE_FIFO;
		    }
		    else
		    {
		    		SciaRegs.SCIFFRX.bit.RXFFIL =	(uartBytesToTransferRxA - uartBufferIndexRxA);
		    }
		}
		// Die erwartete Anzahl an Bytes wurde empfangen
		else
		{
		    // Empfangs-FIFO-Interrupt ausschalten
		    SciaRegs.SCIFFRX.bit.RXFFIENA = 0;
		    // Empfangen weiterhin eingeschaltet lassen,
		    // um eine Überzahl an Bytes zu erkennen
		    // (mehr Bytes empfangen als Datepaketgröße)
		}

		// Empfangs-FIFO-Interrupt-Flag löschen
		SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;
		// Interrupt-Flag der Gruppe 9 löschen (da gehört der INT_SCIA_RX-Interrupt zu)
		PieCtrlRegs.PIEACK.bit.ACK9 = 1;
}


//=== Function: UartTxISRA ========================================================================
///
/// @brief  ISR wird aufgerufen, sobald ein Byte aus dem Register SCITXBUF in das Senderegister
///					geshiftet wurde. Das bedeutet, dass die ISR aufgerufen wird, wenn das zu sendene
///					Byte gerade angefangen wird an dem Pin TxD auszugeben und nicht nach Ende des
///					Sendevorgangs! Sind beim Aufruf der ISR noch weitere Bytes zu senden, so wird
///         das nächste aus dem Software-Puffer "uartBufferTxA[]" gesendet. Andernfalls wird
///         der Tx-Interrupt ausgeschaltet. Anschließend werden alle Interrupt-Flags gelöscht.
///
/// @param  void
///
/// @return void
///
//=================================================================================================
__interrupt void UartTxISRA(void)
{
		// Bei jedem Eintritt in eine Interrupt-Service-Routine (ISR) wird automatisch
		// das EALLOW-Bit gelöscht, unabhängig davon, ob es zuvor gesetzt war (siehe
		// S. 148 Punkt 9, Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022).
		// Nach Abschluss der ISR wird das EALLOW-Bit automatisch wieder gesetzt, falls
		// es vor dem Auftritt des Interrupts gesetzt war. Falls in der ISR nur auf
		// Register ohne Schreibschutz zugegriffen wird, kann auf den folgenden Befehl
		// verzichtet werden (siehe Spalte "Write Protection" in der Registerübersicht)
		//EALLOW;

		// Alle Bytes wurden aus dem Software-Puffer uartBufferTx[] in den (Hardware-) Sende-Puffer
		// SCIFFTX.TXFFST und von dort in das Ausgangs-Schieberegister TXSHF geladen (siehe S. 3866
		// Reference Manual TMS320F2838x, SPRUII0D, Rev. D, July 2022). Zu diesem Zeitpunkt wird
		// das letzte Byte noch versendet!
		if (uartBufferIndexTxA == uartBytesToTransferTxA)
		{
		    // Senden ausschalten. Es werden trotzdem noch alle Daten aus dem Puffer
				// SCITXBUF.TXDT versendet (siehe S. 3885 Reference Manual TMS320F2838x,
				// SPRUII0D, Rev. D, July 2022)
		    SciaRegs.SCICTL1.bit.TXENA = 0;
		    // Sende-FIFO-Interrupt ausschalten
		    SciaRegs.SCIFFTX.bit.TXFFIENA = 0;
				// Warten, bis das letzte Byte vollständig gesendet wurde und anschließend
		    // das Status-Flag setzen um das Ende der Übertragung zu signalisieren.
		    // SCICTL2.TXEMPTY wird gesetzt, sobald der Sende-FIFO und das Ausgangs-
		    // Schieberegister TXSHF leer sind (S. 3888 Reference Manual TMS320F2838x,
		    // SPRUII0D, Rev. D, July 2022). Bei zeitkritischen Anwendungen sollte die
		    // Abfrage von SCICTL2.TXEMPTY aus der ISR ausgelagert werden und zyklisch
		    // erfolgen
		    #warning "Achtung: while()-Schleife blockiert Prorammablauf!"
		    while(!SciaRegs.SCICTL2.bit.TXEMPTY);
				uartStatusFlagTxA = UART_STATUS_FINISHED;
		}
    // Zu sendene Daten von dem Software-Puffer in den Sende-FIFO kopieren
		// bis diser gefüllt ist oder der Software-Puffer leer ist. Dieser
		// Teil muss hinter der obigen if-Abfrage stehen, da andernfalls der
		// Sendevorgang beendet werden würde
		while (   (uartBufferIndexTxA < uartBytesToTransferTxA)
					 && (SciaRegs.SCIFFTX.bit.TXFFST < UART_SIZE_HARDWARE_FIFO))
		{
				SciaRegs.SCITXBUF.bit.TXDT = uartBufferTxA[uartBufferIndexTxA];
				uartBufferIndexTxA++;
		}

		// Sende-FIFO-Interrupt-Flag löschen
		SciaRegs.SCIFFTX.bit.TXFFINTCLR = 1;
		// Interrupt-Flag der Gruppe 9 löschen (da gehört der INT_SCIA_TX-Interrupt zu)
		PieCtrlRegs.PIEACK.bit.ACK9 = 1;
}
