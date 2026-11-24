/*********************************************************************************\
*
* Dateiname: WS2812.h
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
*
* Portbelegung:
* =============
* PA3: DATA
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Bietet Funktionen zur Ansteuerung von WS2812 LEDs.
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 25.10.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/



#ifndef WS2812_H_
#define WS2812_H_

#include <stdint.h>
#include <avr/io.h>

///// STRUCTS /////
typedef struct RGB_t
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    
} RGB_t;

typedef struct WS2812_t
{
    RGB_t* leds;
    uint16_t anzahl;    
    PORT_t* port;
    uint8_t pin;
    
} WS2812_t;

///// DEFINES //////
#define WS2812_PORT         VPORTA
#define WS2812_PIN          3

///// FUNKTIONEN /////

// Initialisiert den Pin für WS2812
void WS2812_init(WS2812_t* ws2812);

void WS2812_write(WS2812_t* ws2812);





#endif /* WS2812_H_ */