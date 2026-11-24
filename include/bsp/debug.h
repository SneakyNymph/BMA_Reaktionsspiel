/*********************************************************************************\
*
* Dateiname: debug.h
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
* Portbelegung:
* =============
* PB0: DEBUG-1
* PB1: DEBUG-2
* PB0: DEBUG-3
* PB1: DEBUG-4
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Stellt Funktionen für die ansteuerung der Debug LEDs auf dem Print zur verfügung
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 24.10.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/



#ifndef DEBUG_H_
#define DEBUG_H_

#include <avr/io.h>

///// DEFINES /////

//PORT Defines
#define LED1_PORT       PORTA
#define LED2_PORT       PORTA
#define LED3_PORT       PORTB
#define LED4_PORT       PORTC

//PIN Defines
#define LED1_PIN        4
#define LED2_PIN        5
#define LED3_PIN        5
#define LED4_PIN        3

//// FUNKTIONEN /////

// Setzt alle LED Pins auf Ausgang
void debug_initLEDs();

void debug_setLED(uint8_t _num, uint8_t _state);

// Toggelt die Ausgewählte Debug LED
void debug_toogleLED(uint8_t _num);






#endif /* DEBUG_H_ */