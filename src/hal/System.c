/*********************************************************************************\
*
* Dateiname: System.c
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Initialisiert und konfiguriert alle Grundlegenden Systeme des ATtiny1626
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 24.10.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/

#include <avr/io.h>

#include "include/hal/System.h"


// Setzt den Haupttakt des MCU auf 20Mhz
void system_setupMainCLK(void)
{
    // Main Clock Prescaler deaktivieren mit einem Protected Write
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, CLKCTRL.MCLKCTRLB & ~CLKCTRL_PEN_bm);
}

void system_initSystemTime_ms(void)
{
    // RTC clock soruce auf 1024Hz einstellen
    RTC.CLKSEL = RTC_CLKSEL_INT1K_gc;

    // Keine Interrupts
    RTC.INTCTRL = 0;

    // RTC aktivieren ohne prescaler, macht T = 1/f = 1/1024Hz = 0.976ms
    RTC.CTRLA = RTC_PRESCALER_DIV1_gc | RTC_RTCEN_bm;
}

uint64_t system_getSystemTime_ms()
{
    
}

