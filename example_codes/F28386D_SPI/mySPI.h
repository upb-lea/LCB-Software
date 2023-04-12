//=================================================================================================
/// @file       mySPI.h
///
/// @brief      Datei enthält Variablen und Funktionen um die SPI-Schnittstelle als Master zu
///							benutzen. Die Kommunikation ist Interrupt-basiert und nutzt die beiden 16x16-Bit
///						  großen Hardware-FIFOs. Pro Kommunikationvorgang können bis zu 65.536 Bytes
///							übertragen werden. Der Hardware-FIFO wird dabei so oft mit den Daten aus dem
///							Software-Puffer beschrieben bzw. Daten aus dem FIFO in den Software-Puffer
///							geschrieben, bis die gewünschte Zahl an Btes übertragen wurde.Der Status der
///							Kommunikation (aktiv oder nicht aktiv) kann über die Funktion "SpiGetStatus()"
///							abgefragt werden.
///
///							Änderung in Version 2.0: Verwendung der Hardware-FIFOs
///
/// @version    V2.0
///
/// @date       24.03.2023
///
/// @author     Daniel Urbaneck
//=================================================================================================
#ifndef MYSPI_H_
#define MYSPI_H_
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "myDevice.h"


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
// Taktfrequenzen (CLK) für die SPI-Kommunikation
#define SPI_CLOCK_250_KHZ									250000
#define SPI_CLOCK_500_KHZ									500000
#define SPI_CLOCK_1_MHZ										1000000
#define SPI_CLOCK_2_MHZ										2000000
// Größe der Software-Puffer
#define SPI_SIZE_SOFTWARE_BUFFER		    	50
// Größe der Hardware-FIFOs
#define SPI_SIZE_HARDWARE_FIFO						16
// Zustände der SPI-Kommunikation (spiStatusFlag)
#define SPI_STATUS_IDLE										0
#define SPI_STATUS_IN_PROGRESS						1
#define SPI_STATUS_FINISHED								2
// Slave-Select
#define SPI_SLAVE_1												0
#define SPI_SLAVE_2												1


//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
// Gibt true zurück, wenn der entsprechende Slave angewählt ist (SS-Leitung auf logisch 0)
// Gibt false zurück, wenn der entsprechende Slave nicht angewählt ist (SS-Leitung auf logisch 1)
#define SPI_SLAVE_1_IS_ENABLED						!((bool)GpioDataRegs.GPBDAT.bit.GPIO58)
#define SPI_SLAVE_2_IS_ENABLED						!((bool)GpioDataRegs.GPBDAT.bit.GPIO59)
// Wählt den entsprechenden Slave an oder ab
#define SPI_ENABLE_SLAVE_1								GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1
#define SPI_DISABLE_SLAVE_1								GpioDataRegs.GPBSET.bit.GPIO58   = 1
#define SPI_ENABLE_SLAVE_2								GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1
#define SPI_DISABLE_SLAVE_2								GpioDataRegs.GPBSET.bit.GPIO59   = 1


//-------------------------------------------------------------------------------------------------
// Global variables
//-------------------------------------------------------------------------------------------------
// Software-Puffer für die SPI-Kommunikation
extern uint16_t spiBufferTxA[SPI_SIZE_SOFTWARE_BUFFER];
extern uint16_t spiBufferRxA[SPI_SIZE_SOFTWARE_BUFFER];


//-------------------------------------------------------------------------------------------------
// Prototypes of global functions
//-------------------------------------------------------------------------------------------------
// Funktion setzt GPIOs auf SPI-Funktionalität, initialisiert das SPI-Modul
// als Master und aktiviert den SPI-Interrupt inkl. Registrierung der ISR
extern void SpiInitA(uint32_t clock);
// Funktion initialisiert den SPI Software Sende-Puffer (alle Elemente zu 0)
extern void SpiInitBufferTxA(void);
// Funktion initialisiert den SPI Software Empfangs-Puffer (alle Elemente zu 0)
extern void SpiInitBufferRxA(void);
// Funktion gibt den aktuellen Status der SPI-Kommunikation zurück
extern uint16_t SpiGetStatusA(void);
// Funktion setzt das Status-Flag auf "idle", falls die vorherige Kommunikation abgeschlossen ist
extern bool SpiSetStatusIdleA(void);
// Funktion zum Senden und Empfangen von Daten über SPI
extern bool SpiSendDataA(uint16_t slave,
												 uint16_t numberOfBytes);
// Interrupt-Service-Routine für die SPI-Kommunikation
__interrupt void SpiISRA(void);


#endif
