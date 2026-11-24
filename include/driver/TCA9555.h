/*********************************************************************************\
*
* Dateiname: TCA9555.h
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
*
* Portbelegung:
* =============
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Bietet Funktionen zur Ansteuerung des TCA9555 Port Expander
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 07.11.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/


#ifndef TCA9555_H_
#define TCA9555_H_

///// DEFINES /////

///// Rèckgabecodes

#define TCA9555_OK              0x00
#define TCA9555_ERR_TWI         0x01
#define TCA9555_ERR_UNABLE      0x02
#define TCA9555_ERR_ADDRESS     0x03
#define TCA9555_ERR_PORT        0x04

///// FUNKTIONEN /////
//liest 16bit daten aus dem Input Port register über TWI aus
uint8_t TCA9555_readInputPorts(uint8_t addr, uint16_t *data);

//liesst 16Bit Daten aus dem Output Port Register über TWI aus
uint8_t TCA9555_readOutputPorts(uint8_t addr, uint16_t *data);

//Schreibt 16Bit der Ouput Maske auf das Ausgangsregister über TWI
uint8_t TCA9555_writeOutputPorts(uint8_t addr, uint16_t outputMask);

//Schreibt 16Bit der Bit Maske auf das Ausgangspolaritätsumkehrsregister über TWI
uint8_t TCA9555_writePolarityInversion(uint8_t addr, uint8_t port01, uint8_t bitMask);

//liesst 16Bit Daten aus dem Output Ausgangspolaritätsumkehrsregister über TWI aus
uint8_t TCA9555_readPolarityInversion(uint8_t addr, uint8_t port01, uint8_t *data);

//Schreibt 16Bit der Bit Maske auf das Konfigurationsregister über TWI
uint8_t TCA9555_writeConfiguration(uint8_t addr, uint8_t port01, uint8_t bitMask);

//liesst 16Bit Daten aus dem Output Konfigurationsregister über TWI aus
uint8_t TCA9555_readConfiguration(uint8_t addr, uint8_t port01, uint8_t *data);


#endif /* TCA9555_H_ */