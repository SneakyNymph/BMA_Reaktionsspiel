/*********************************************************************************\
*
* Dateiname: buttons.h
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
* Portbelegung:
* =============
* PA1: INT linie
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Stellt Funktionen für die ansteuerung der Taster auf auf dem Print via TCA9555 über TWI zur verfügung
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 07.11.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/



#ifndef BUTTONS_H_
#define BUTTONS_H_

#define BUTTONS_INT_PORT        PORTA
#define BUTTONS_INT_PIN         1

///// Rückgabewerte
#define BUTTONS_OK              0x00
#define BUTTONS_ERR_PARAM       0x01
#define BUTTONS_ERR_TWI         0x02
#define BUTTONS_ERR_REG         0x03

///// Addressen
#define BUTTONS_ADDR_1          0x20
#define BUTTONS_ADDR_2          0x21
#define BUTTONS_ADDR_3          0x22
#define BUTTONS_ADDR_4          0x23

///// FUNKTIONEN //////
uint8_t buttons_init(void);

uint64_t buttons_allPressed(void);

uint8_t button_isPressed(uint8_t button);

#endif /* BUTTONS_H_ */