/*********************************************************************************\
*
* Dateiname: Sleep.c
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Stellt Funktionen für die Initialisierung und verwendung der SLPCTRL - Sleep Controller Peripherie zur verfügung.
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 21.11.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "include/hal/Sleep.h"

// Initialisiert den Sleep Controller
void Sleep_init(void)
{
    // Sleep Controller deaktivieren und IDLE auswählen
    SLPCTRL.CTRLA = SLPCTRL_SMODE_IDLE_gc;
}

// ändert den aktuellen Sleep Modus
uint8_t Sleep_setMode(Sleep_Mode_t mode)
{
    // Parameter überprüfen
    if (mode > SLEEP_POWER_DOWN)
    {
        return SLEEP_ERR_PARAM;
    }

    // Sleep-Modus im CTRLA-Register einstellen
    SLPCTRL.CTRLA = (SLPCTRL.CTRLA & ~SLPCTRL_SMODE_gm) | ((uint8_t)mode << SLPCTRL_SMODE_gp);

    return SLEEP_OK;
}


// Das Gerät in den SChlafmodus setzten
uint8_t Sleep_enter(void)
{
    // Prüfen ob globale Interrupts aktiviert sind
    if (!(SREG & CPU_I_bm))
    {
        return SLEEP_ERR_INTERRUPTS_DISABLED;
    }

    // Interrupts während der Vorbereitung sperren
    cli();

    // Sleep Controller aktivieren
    sleep_enable();

    // Interrupts freigeben und CPU schlafen legen
    sei();
    sleep_cpu();

    // Nach dem Aufwachen Sleep Controller deaktivieren
    sleep_disable();

    return SLEEP_OK;
}


// Schlafen deaktivieren
void Sleep_disable(void)
{
    // Sleep-Freigabe deaktivieren
    SLPCTRL.CTRLA &= ~SLPCTRL_SEN_bm;
}


Sleep_Mode_t Sleep_getMode(void)
{
    // Aktuellen Sleep-Modus aus dem Register auslesen
    uint8_t mode = (SLPCTRL.CTRLA & SLPCTRL_SMODE_gm)
    >> SLPCTRL_SMODE_gp;

    return (Sleep_Mode_t)mode;
}


