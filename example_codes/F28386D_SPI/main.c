//=================================================================================================
/// @file			main.c
///
/// @brief		Enthält das Hauptprogramm zur Demonstration des Moduls "mySPI.c". Die Funktionen
///						dieses Moduls implementieren eine Interrupt-basierte Kommunikation über die SPI-A
///						Schnittstelle für den Mikrocontroller TMS320F2838x. Erklärungen zur genauen
///						Funktion sind im Modul zu finden.
///
///						Änderung mySPI.c V2.0: Verwendung der Hardware-Puffer zum Senden und Empfangen
///
/// @version	V1.3
///
/// @date			24.03.2023
///
/// @author		Daniel Urbaneck
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "mySPI.h"


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Prototypes of global functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------
// Zum Starten der Kommunikation
uint32_t startSPI = 0;


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
    // SPI als Master mit 1 MHz CLK-Takt initialisieren
    SpiInitA(SPI_CLOCK_1_MHZ);

    // Register-Schreibschutz ausschalten
    EALLOW;

    // Grundsätzlicher Ablauf einer SPI-Kommunikation:
    //
    // 1) Prüfen, ob eine SPI-Kommunikation aktiv ist. Ggf. warten
    // 2) Puffer "spiBufferRxA[]" und "spiBufferTxA[]" initialisieren
    // 3) Zu sendene Daten in "spiBufferTxA[]" schreiben, falls Daten an einen Slave
    //		gesendet werden sollen. Dummy-Daten in "spiBufferTxA[]" schreiben, falls
    //		Daten vom Slave nur empfangen werden sollen
    // 4) Funktion "SpiSendDataA()" aufrufen
    // 5) Rückgabewert prüfen, ob die Kommunikation gestartet wurde
    // 6) Warten bis die Kommunikation abgeschlossen ist durch Aufruf von "SpiGetStatusA()"
    // 7) Slave abwählen z.B. durch Aufruf des Makros "SPI_DISABLE_SLAVE_1"
    // 8) Empfangene Daten aus "spiBufferRxA[]" lesen
    // 9) SPI-Status auf "idle" setzen durch Aufruf von "SpiSetStatusIdleA()"


		// Dauerschleife Hauptprogramm
    while(1)
    {
				// Vor jeder einer Kommunikation sicherstellen, das keine Kommunikation aktiv ist
				if (   (SpiGetStatusA() == SPI_STATUS_IDLE)
					  && (startSPI == 1))
				{
						// Datenpaket nur einmal senden
        		startSPI = 0;
						// 3 Bytes an Slave 1 senden und 3 Bytes von Slave 1 empfangen.
						// Um Daten über SPI an einen Slave zu senden,  müssen diese in den Sende-Puffer "spiBufferTxA[]"
						// geschrieben werden. Dabei müssen die Daten am Anfang des Puffers geschrieben werden (beginnend
						// vom Element 0 an). Es ist darauf zu achten, dass nicht mehr Daten geschrieben, als der Puffer
						// groß ist (SPI_SIZE_BUFFER)
						spiBufferTxA[0] = 1;
						spiBufferTxA[1] = 2;
						spiBufferTxA[2] = 3;

						for (uint16_t i=0; i<SPI_SIZE_SOFTWARE_BUFFER; i++)
						{
								spiBufferTxA[i] = 1;
						}

						// Sende-Vorgang starten. Falls der Rückgabewert "false" ist, wurde der Vorgang
						// nicht ausgeführt, weil z.B. die Anzahl zu sendener Bytes zu groß ist
						if (!SpiSendDataA(SPI_SLAVE_1, 3))
						{
								// Fehlerbehandlung:
								// ...
						}
				}

				// Warten, bis die Kommunikation beendet ist
				while (SpiGetStatusA() == SPI_STATUS_IN_PROGRESS);

				// Slave abwählen/inaktiv setzen
				SPI_DISABLE_SLAVE_1;

				// Status-Flag auf "idle" setzen, um die Bereitschaft der SPI-
				// Schnittstelle zu signalisieren (Rückgabewert wird hier nicht
				// gebraucht), da der Status oben bereits abgefragt wurde
				SpiSetStatusIdleA();
    }
}
