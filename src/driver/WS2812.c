/*********************************************************************************\
*
* Dateiname: WS2812.c
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

#include <stdint.h>
#include <stddef.h>
#include <avr/io.h>
#include <util/atomic.h>

#include "include/driver/WS2812.h"
#include "include/hal/GPIO.h"

///// LOKALE FUNKTIONEN /////
static inline void sendZero(PORT_t *port, uint8_t pin)
{
    VPORTA.OUT |= (1<<pin); // 250ns
    __asm__ volatile("nop\nnop\nnop\nnop\nnop"); //400ns
    VPORTA.OUT &= ~(1 << pin);
    __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop"); //800ns

}

static inline void sendOne(PORT_t *port, uint8_t pin)
{
    VPORTA.OUT |= (1<<pin); // 250ns
    __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop"); //800ns
    VPORTA.OUT &= ~(1 << pin);
    __asm__ volatile("nop\nnop\nnop"); //400ns

}

///// ÖFFENTLICHE FUNKTIONEN /////

// Initialisiert den WS2812 Pin
void WS2812_init(WS2812_t* ws2812)
{
    // Data pin für WS2812 als Ausgang schalten
    GPIO_setPinDirection(&PORTA, ws2812->pin, GPIO_OUTPUT);
    // Data pin auf LOW setzten
    GPIO_pinWrite(&PORTA, ws2812->pin, GPIO_LOW);
}

void WS2812_write(WS2812_t* ws2812)
{
    //Parameter prüfen
    if(ws2812 == NULL)
    {
        return;
    }
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        
        //Jede LED durchgehen
        for (uint16_t i = 0; i < ws2812->anzahl; i++)
        {
            
            RGB_t led = ws2812->leds[i];
            
            ///// GRÜN
            //Jedes Bit durchgehen, MSB zuerst
            for (uint8_t bit = 0; bit < 8; bit++)
            {
                // Wenn aktuelles bit eine 1 ist
                if(led.g & (1 << (7-bit)))
                {
                    //eine "1" senden
                    sendOne(ws2812->port, ws2812->pin);
                }
                else // Aktuelles bit ist eine 0
                {
                    //eine "0" senden
                    sendZero(ws2812->port, ws2812->pin);
                }
            }
            
            ///// ROT
            //Jedes Bit durchgehen, MSB zuerst
            for (uint8_t bit = 0; bit < 8; bit++)
            {
                // Wenn aktuelles bit eine 1 ist
                if(led.r & (1 << (7-bit)))
                {
                    //eine "1" senden
                    sendOne(ws2812->port, ws2812->pin);
                }
                else // Aktuelles bit ist eine 0
                {
                    //eine "0" senden
                    sendZero(ws2812->port, ws2812->pin);
                }
            }
            
            ///// Blau
            //Jedes Bit durchgehen, MSB zuerst
            for (uint8_t bit = 0; bit < 8; bit++)
            {
                // Wenn aktuelles bit eine 1 ist
                if(led.b & (1 << (7-bit)))
                {
                    //eine "1" senden
                    sendOne(ws2812->port, ws2812->pin);
                }
                else // Aktuelles bit ist eine 0
                {
                    //eine "0" senden
                    sendZero(ws2812->port, ws2812->pin);
                }
            }
            
        }
        
        // Reset Code
        
        for (uint16_t i = 0; i < 1000; i++)
        {
            __asm__ volatile("nop"); //50ns warten
        }
        
    }
}


/// BEISPIEL

/*
uint16_t pinValue = 0;

RGB_t leds[8] = {0};

WS2812_t ws2812 = {
.leds = leds,
.anzahl = 8,
.pin = WS2812_PIN,
.port = &WS2812_PORT
};


WS2812_init(&ws2812);

*/