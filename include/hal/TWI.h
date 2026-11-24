/*********************************************************************************\
*
* Dateiname: TWI.h
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
*
* Portbelegung:
* =============
* PB0: SCL
* PB1: SDA
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Bietet defines und Funktion an für die konfiguration und verwendung des TWI des ATtiny1626.
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 24.10.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/


#ifndef TWI_H_
#define TWI_H_

///// DEFINES /////

// Rückgabewerte
#define TWI_OK              0
#define TWI_ERR_NACK        1
#define TWI_ERR_BUS         2
#define TWI_ERR_TIMEOUT     3
#define TWI_ERR_PARAM       4

//Definition der TWI Baudrate laut dem Datenblatt ATtiny1626
#define TWI0_BAUD(F_SCL, T_RISE)                                                                                       \
((((((float)20000000 / (float)F_SCL)) - 10 - ((float)20000000 * T_RISE / 1000000))) / 2)


///// Funktionen /////

// initialisiert das TWI und setzt die Baudrate fest. 
void TWI_init(uint32_t baudRate);

//liesst 8 Bit Daten aus einem Register eines ICs über TWI aus.
uint8_t TWI_read8Bit(uint8_t addr, uint8_t reg);

//schreibt 8Bit daten in ein Register eines ICs über TWI.
uint8_t TWI_write8Bit(uint8_t addr, uint8_t reg, uint8_t value);

//Liest mehrer Daten ab einem Register über TWI
uint8_t TWI_readBlock(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t length);

//Schreibt mehrere Daten ab einem Register über TWI
uint8_t TWI_writeBlock(uint8_t addr, uint8_t reg, const uint8_t *data, uint16_t length);

// deaktiviert das TWI-Modul
uint8_t TWI_disable(void);

// aktiviert das TWI-Modul wider
uint8_t TWI_enable(void);



#endif /* TWI_H_ */