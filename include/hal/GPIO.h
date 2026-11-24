/*********************************************************************************\
*
* Dateiname: GPIO.h
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



#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>
#include <stdint.h>

///// DEFINES /////

//LVL
#define GPIO_HIGH       1
#define GPIO_LOW        0

//DIR
#define GPIO_INPUT      0
#define GPIO_OUTPUT     1

//Interrupt
#define GPIO_INTERRUPT_DISABLE          PORT_ISC_INTDISABLE_gc
#define GPIO_INTERRUPT_EDGE_BOTH        PORT_ISC_BOTHEDGES_gc
#define GPIO_INTERRUPT_EDGE_FALLING     PORT_ISC_FALLING_gc
#define GPIO_INTERRUPT_EDGE_RISING      PORT_ISC_RISING_gc
#define GPIO_INTERRUPT_LEVEL            PORT_ISC_LEVEL_gc

///// FUNKTIONEN /////

//Setzt einen GPIO port entweder als Eingang oder Ausgang fest.
void GPIO_setPinDirection(PORT_t *port, uint8_t pin, uint8_t direction);

// Schreibt einen digitalen Ausgang (an Port *port, Bit-Nummer pin) auf den gegebenen Wert (0 oder 1).
void GPIO_pinWrite(PORT_t *port, uint8_t pin, uint8_t value);

// Toggelt den Zustand eines digitalen Ausgangs (an Port *port, Bit-Nummer pin).
void GPIO_pinToggle(PORT_t *port, uint8_t pin);

//Liest einen PIN aus und gibt dessen Wert zurück (1/0)
uint8_t GPIO_pinRead(PORT_t *port, uint8_t pin);

// Konfiguriert einen Pin nach seinem Interrupt verhalten
void GPIO_setInterrupt(PORT_t *port, uint8_t pin, uint8_t intMode);


#endif /* GPIO_H_ */