/*********************************************************************************\
*
* Dateiname: System.h
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


#ifndef SYSTEM_H_
#define SYSTEM_H_

// Entfernt den Standartmässigen prescaler und setzt den Haupttakt somit auf 20Mhz
void system_setupMainCLK();



#endif /* SYSTEM_H_ */