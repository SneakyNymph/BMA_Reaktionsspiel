/*********************************************************************************\
*
* Dateiname: Sleep.h
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


#ifndef SLEEP_H_
#define SLEEP_H_

#include <stdint.h>


// Enum für die 3 verschiedenen Sleep Modi
typedef enum
{
    SLEEP_IDLE = 0,
    SLEEP_STANDBY,
    SLEEP_POWER_DOWN
} Sleep_Mode_t;

// Rückgabewerte
#define SLEEP_OK                        0
#define SLEEP_ERR_PARAM                 1
#define SLEEP_ERR_INTERRUPTS_DISABLED   2

///// FUNKTIONEN /////

// Konfiguriert den Sleep Controller
void Sleep_init(void);

// ändert den aktuellen Sleep Modus
uint8_t Sleep_setMode(Sleep_Mode_t mode);

// versetzt das Gerät in den ausgewählten Schlafmodus
uint8_t Sleep_enter(void);

// Schlafen deaktivieren
void Sleep_disable(void);

// Gibt den aktuell ausgewählten Sleep Mode zurück
Sleep_Mode_t Sleep_getMode(void);




#endif /* SLEEP_H_ */