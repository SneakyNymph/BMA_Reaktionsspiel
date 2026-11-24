/*********************************************************************************\
*
* Dateiname: battLEDs.h
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
* Portbelegung:
* =============
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Stellt Funktionen für die ansteuerung und konfiguration der Batterieanzeige LEDs auf auf dem Print via LP5814 über TWI zur verfügung
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 21.11.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/


#ifndef BATTLEDS_H_
#define BATTLEDS_H_

#include <stdint.h>

////// DEFINES /////
// Rückgabewerte
#define BATT_LEDS_OK                0x00
#define BATT_LEDS_ERR_NOT_INIT      0x01
#define BATT_LEDS_ERR_PARAM         0x02


////// FUNKTIONEN /////

// Setzt den maximal Zulässigen Strom, teil den Ouptuts eine Engine zu, schaltet alle LEDs aus.
uint8_t battLeds_init(void);

// Zeigt anhand des Batteriestands (0 bis 100) die ensprechende LED an
uint8_t battLeds_showLevel(uint8_t percent);

// Zeigt anhad des Batteristands (0 bis 100) die entsprechende LEDs an, oberste LED hat "breath" effekt
uint8_t battLeds_showCharging(uint8_t percent);

// Zeigt für 5s den Batteriestand an den LEDs, wenn 0 dann blinkt sie
uint8_t battLeds_showLevel5s(uint8_t percent);

// Started die Füll Animation
uint8_t battLeds_startFill(void);

// Stopp alle Animationen und schaltet Alle LEDs aus
uint8_t battLeds_allOff(void);

// Spielt die Ausschaltanimation ab
uint8_t battLeds_showShutdownAnim(void);

// Lässt den LP5814 einschlafen
uint8_t battLeds_sleep(void);

// Weckt den LP5814 auf und konfiguriert ihn
uint8_t battLeds_wakeup(void);

#endif /* BATTLEDS_H_ */