/*********************************************************************************\
*
* Dateiname: buzzer.h
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
* Stellt Funktionen für die ansteuerung des Buzzers auf dem Print zur verfügung
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 24.10.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/



#ifndef BUZZER_H_
#define BUZZER_H_

#ifndef F_CPU
#define F_CPU 20000000UL
#endif

#define BUZZER_PRESCALER    256
#define TCB0_MAX_TIME_ms    830
#define BUZZER_MAX_FREQ     5000

void buzzer_init();
void buzzer_start(uint16_t freq);
void buzzer_stop();
void buzzer_playTone(uint16_t freq_Hz, uint16_t duration_ms);




#endif /* BUZZER_H_ */