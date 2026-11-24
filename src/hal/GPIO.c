/*********************************************************************************\
*
* Dateiname: GPIO.c
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Stellt Funktionen für die Initialisierung und verwendung der GPIO Ports zur verfügung.
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 24.10.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/

#include <avr/io.h>

#include <avr/interrupt.h>
#include "include/bsp/debug.h"

#include "include/hal/GPIO.h"

///// Öffentliche Funktionen /////

void GPIO_setPinDirection(PORT_t *port, uint8_t pin, uint8_t direction)
{
    if(direction == GPIO_OUTPUT)
    { 
        port->DIRSET = (1 << pin);
    }
    else if(direction == GPIO_INPUT)
    {
        port->DIRCLR = (1 << pin);
    }
}


// Schreibt einen digitalen Ausgang (an Port *port, Bit-Nummer pin) auf den gegebenen Wert (0 oder 1).
void GPIO_pinWrite(PORT_t *port, uint8_t pin, uint8_t value)
{
    if (value)
    {
        port->OUTSET = (1<<pin);
    }
    else
    {
        port->OUTCLR = (1<<pin);
    }
}

// Toggelt den Zustand eines digitalen Ausgangs (an Port *port, Bit-Nummer pin).
void GPIO_pinToggle(PORT_t *port, uint8_t pin){
    
    port->OUTTGL = (1<<pin);
    
}

//Liest einen PIN aus und gibt dessen Wert zurück (1/0)
uint8_t GPIO_pinRead(PORT_t *port, uint8_t pin)
{
    return (port->IN & (1 << pin)) ? 1 : 0;
}

void GPIO_setInterrupt(PORT_t *port, uint8_t pin, uint8_t intMode)
{
    if(pin > 7)
    {
        return;
    }
    
    if(intMode > GPIO_INTERRUPT_LEVEL)
    {
        return;
    }
    
    volatile uint8_t *pinCtrl = &port->PIN0CTRL + pin;
    
    *pinCtrl = (*pinCtrl & ~PORT_ISC_gm) | intMode;
}
