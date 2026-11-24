/*********************************************************************************\
*
* Dateiname: buzzer.c
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
* Portbelegung:
* =============
* PB4: Buzzer Waveform
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
#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

#include "include/bsp/buzzer.h"
#include "include/hal/GPIO.h"

void buzzer_init()
{
    
     // Timer A konfigurieren //
     
    // Alternative Pins für WO
    PORTMUX.TCAROUTEA = PORTMUX_TCA01_ALT1_gc;

    // Control A Register konfigurieren
    TCA0.SINGLE.CTRLA =
    0 << TCA_SINGLE_RUNSTDBY_bp          /* entscheidet ob timer während dem Standby läuft */
    | TCA_SINGLE_CLKSEL_DIV256_gc         /* Prescaler einstellen */
    | 1 << TCA_SINGLE_ENABLE_bp;
    

    // Control B Register konfigurieren
    TCA0.SINGLE.CTRLB =
    0 << TCA_SINGLE_CMP1EN_bp          /* WO1 nicht aktivieren */
    | TCA_SINGLE_WGMODE_FRQ_gc;        /* Modus auf Frequenz umstellen */

    // PB4 als ausgang setzten, dort sollte das Rechteck rauskommen.
    GPIO_setPinDirection(&PORTB, 4, GPIO_OUTPUT);
    
    // Timer B Konfigurerien //
    
    // Timer während der Konfiguration deaktivieren
    TCB0.CTRLA = 0;
    
    // Anfangswert setzen, damit Timer nicht sofort startet
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        TCB0.CCMP = 0xFFFF;
        TCB0.CNT = 0xFFFF;
    }
    
    // Control B Register konfigurieren
    TCB0.CTRLB =
    0 << TCB_ASYNC_bp          /* Asynchroner Betrieb nicht aktivieren */
    | 0 << TCB_CCMPEN_bp         /* Waveform Generation deaktivieren */
    | TCB_CNTMODE_SINGLE_gc;   /* Modus auf Single-Shot umstellen */
    
    // Control A Register konfigurieren
    TCB0.CTRLA =
      0 << TCB_RUNSTDBY_bp        /* im Standby nicht laufen */
    | 0 << TCB_CASCADE_bp         /* kaskadieren wird nicht verwendet */
    | 0 << TCB_SYNCUPD_bp         /* Timer wird nicht mit TCA synchronisiert */
    | TCB_CLKSEL_TCA0_gc        /* Eingangstakt auf den TCA0 takt stellen */
    | 1 << TCB_ENABLE_bp;         /* Timer wird aktiviert */
    
    // Event Capture aktivieren
    TCB0.EVCTRL = TCB_CAPTEI_bm;
    
    // Capture Interupts aktivieren
    TCB0.INTCTRL = TCB_CAPT_bm;
    
    // EVENT System konfigurern //
    
    // Keine Peripherie mit dem EVSYS CH0 verbinden
    EVSYS.CHANNEL0 = 0x00;
    
    // TCB0 mit CH0 verbinden
    EVSYS.USERTCB0CAPT = EVSYS_USER_CHANNEL0_gc;
    
}

// Capture Interrupt von TCB0, zeit für Buzzer ist abgeloffen
ISR(TCB0_INT_vect)
{
    
    // INT-Flag löschen
    TCB0.INTFLAGS = TCB_CAPT_bm; 
    
    buzzer_stop();
}


void buzzer_start(uint16_t freq_Hz)
{
    // Ungueltige Frequenz abfangen
    if (freq_Hz == 0)
    {
        buzzer_stop();
        return;
    }

    // Maximale Frequenz begrenzen
    if (freq_Hz > BUZZER_MAX_FREQ)
    {
        freq_Hz = BUZZER_MAX_FREQ;
    }

    // Compare-Wert berechnen
    uint16_t cmpValue = (uint16_t)
    (F_CPU / (2UL * freq_Hz * BUZZER_PRESCALER) - 1UL);

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        // Waveform-Ausgang deaktivieren
        TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_FRQ_gc;

        // Neuen Vergleichswert setzen
        TCA0.SINGLE.CMP0 = cmpValue;

        // Timer-Zaehler zuruecksetzen
        TCA0.SINGLE.CNT = 0;

        // Waveform-Ausgang wieder aktivieren
        TCA0.SINGLE.CTRLB =
        TCA_SINGLE_CMP1EN_bm |
        TCA_SINGLE_WGMODE_FRQ_gc;
    }
}


void buzzer_stop()
{
    // Control B Register konfigurieren
    TCA0.SINGLE.CTRLB =
    0 << TCA_SINGLE_CMP1EN_bp          /* WO1 aktivieren */
    | TCA_SINGLE_WGMODE_FRQ_gc;        /* Modus auf Frequenz umstellen */
}

void buzzer_playTone(uint16_t freq_Hz, uint16_t duration_ms)
{
    //Eingabe anpassen von duration_ms
    if(duration_ms > TCB0_MAX_TIME_ms)
    {
        duration_ms = TCB0_MAX_TIME_ms;
    }
    
    // Frequenz Eingabe limitieren
    if(freq_Hz > BUZZER_MAX_FREQ)
    {
        freq_Hz = BUZZER_MAX_FREQ;
    }
    
    // CCMP Wert berechnen anhand von duration, F_CPU und dem Prescaler
    static uint16_t cmpValue = 0;
    cmpValue = (uint16_t)
    (((uint64_t)F_CPU * duration_ms) /
    (BUZZER_PRESCALER * 1000UL));
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        // Compare Wert auf compare value setzten
        TCB0.CCMP = cmpValue;
    }
    
    buzzer_start(freq_Hz);
    
    // Event auf CH0 generieren, startet TCB0
    EVSYS.SWEVENTA = EVSYS_CHANNEL00_bm;
    
    
}