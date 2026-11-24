/*********************************************************************************\
*
* Dateiname: debug.c
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

#include <stdint.h>

#include "include/hal/GPIO.h"
#include "include/bsp/debug.h"

///// VARIABLEN /////


    
    
///// FUNKTIONEN /////

//
void debug_initLEDs()
{
    GPIO_setPinDirection(&LED1_PORT, LED1_PIN, GPIO_OUTPUT);
    GPIO_setPinDirection(&LED2_PORT, LED2_PIN, GPIO_OUTPUT);
    GPIO_setPinDirection(&LED3_PORT, LED3_PIN, GPIO_OUTPUT);
    GPIO_setPinDirection(&LED4_PORT, LED4_PIN, GPIO_OUTPUT);
}

// Schaltet eine der 4 DEBUG LEDs basierend auf _state entweder ein oder aus
void debug_setLED(uint8_t _num, uint8_t _state)
{
    PORT_t* led_ports[] = {&PORTA, &LED4_PORT, &LED3_PORT, &LED2_PORT, &LED1_PORT};
    uint8_t led_pins[] = {0, LED4_PIN, LED3_PIN, LED2_PIN, LED1_PIN};
    
    //Num zu klein
    if(_num == 0)
    {
        //Num auf 1 limitieren
        _num = 1;
    }
    else if (_num > 4)
    {
        _num = 4;
    }
    
    //state auf 1 begrenzen
    if(_state > 1)
    {
        _state = 1;
    }
    
    GPIO_pinWrite(led_ports[_num], led_pins[_num], _state);
    //GPIO_pinWrite()
}

// Toggelt die Ausgewählte Debug LED
void debug_toogleLED(uint8_t _num)
{
    PORT_t* led_ports[] = {&PORTA, &LED4_PORT, &LED3_PORT, &LED2_PORT, &LED1_PORT};
    uint8_t led_pins[] = {0, LED4_PIN, LED3_PIN, LED2_PIN, LED1_PIN};
    
    //Num zu klein
    if(_num == 0)
    {
        //Num auf 1 limitieren
        _num = 1;
    }
    else if (_num > 4)
    {
        _num = 4;
    }
    
    GPIO_pinToggle(led_ports[_num], led_pins[_num]);
    
}