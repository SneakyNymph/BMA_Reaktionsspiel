/*********************************************************************************\
*
* Dateiname: battLEDs.c
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

#include <stdint.h>

#include "include/bsp/battLEDs.h"
#include "include/driver/LP5814.h"
#include "include/driver/LP5814_Registers.h"

///// DEFINES /////
#define BATTLEDS_DOT_CURRENT 200 // 20mA max Ausgangsstrom

///// VARIABLEN /////
// statische Konfiurationen
static LP5814_Config_t battLeds_config;
static uint8_t battLeds_initialized = 0;

uint8_t battLeds_init(void)
{
    // Initialisierungstand zurücksetzten
    battLeds_initialized = 0;
    
    // Konfiguration zurücksetzten
    battLeds_config = (LP5814_Config_t){0};
    
    // Grundeinstellung machen
    battLeds_config.maxCurrent_51mA = 0;
    battLeds_config.fadeTime = LP5814_TIME_0MS;
    
    // Alle 4 LED Ausgänge konfigurieren
    
    for (uint8_t i = 0; i < 4; i++)
    {
        battLeds_config.channel[i].enabled = 1;
        battLeds_config.channel[i].dotCurrent = BATTLEDS_DOT_CURRENT;
        battLeds_config.channel[i].pwm = 0;
        battLeds_config.channel[i].mode = LP5814_MODE_MANUAL;
        battLeds_config.channel[i].fadeEnabled = 0;
        battLeds_config.channel[i].exponential = 1;
        battLeds_config.channel[i].engine = i;
    }
    
    // LP5814 initialisieren
    uint8_t result = LP5814_init(&battLeds_config);
    
    if(result != LP5814_OK)
    {
        return result;
    }
    
    // Konfiguration abgeschlossen
    battLeds_initialized = 1;
    
    return BATT_LEDS_OK;
}

uint8_t battLeds_showLevel(uint8_t percent)
{
    //Überprüfen ob der LP5814 initialisiert wurde
    if(!battLeds_initialized)
    {
        return BATT_LEDS_ERR_NOT_INIT;
    }
    
    // Parameter prüfen
    if(percent > 100)
    {
        return BATT_LEDS_ERR_PARAM;
    }
    
    // Anzahl der eingeschalteten LEDs berechnen
    uint8_t ledCount = (percent + 24) / 25;
    
    // eventuell Laufende Animation stoppen
    uint8_t result = LP5814_stopAnimation();
    
    if (result != LP5814_OK)
    {
        return result;
    }
    
    // Alle vier LED-Ausgänge konfigurieren
    for (uint8_t i = 0; i < 4; i++)
    {
        battLeds_config.channel[i].mode = LP5814_MODE_MANUAL;
        battLeds_config.channel[i].fadeEnabled = 1;
        battLeds_config.fadeTime= LP5814_TIME_200_ms;

        if (i < ledCount)
        {
            battLeds_config.channel[i].pwm = 64;
        }
        else
        {
            battLeds_config.channel[i].pwm = 0;
        }
    }
    
    // Neue Konfiguration übernehmen
    return LP5814_init(&battLeds_config);
}

uint8_t battLeds_showCharging(uint8_t percent)
{
    //Überprüfen ob der LP5814 initialisiert wurde
    if(!battLeds_initialized)
    {
        return BATT_LEDS_ERR_NOT_INIT;
    }
    
    // Parameter prüfen
    if(percent > 100)
    {
        return BATT_LEDS_ERR_PARAM;
    }
    
    // Anzahl vollständig geladener Stufen
    uint8_t fullLeds = percent / 25;
    uint8_t result;
    
    // eventuell Laufende animation stoppen
    result = LP5814_stopAnimation();
    
    if (result != LP5814_OK)
    {
        return result;
    }
    
    // LED Ausgänge konfigurieren
    for (uint8_t i = 0; i < 4; i++)
    {
        battLeds_config.channel[i].mode = LP5814_MODE_MANUAL;
        battLeds_config.channel[i].fadeEnabled = 0;
        battLeds_config.channel[i].pwm = (i < fullLeds) ? 255 : 0;

        // Nächste LED soll atmen
        if (i == fullLeds && percent < 100)
        {
            battLeds_config.channel[i].mode = LP5814_MODE_AUTO;
        }
    }
    
    // Neue Gerätekonfiguration übernehmen
    result = LP5814_init(&battLeds_config);

    if (result != LP5814_OK)
    {
        return result;
    }
    
    // Bei 100% muss keine LED atmen
    if (percent == 100)
    {
        return BATT_LEDS_OK;
    }
    
    // Breathing effekt konfigurieren
    LP5814_PatternConfig_t pattern = {0};

    pattern.pwm[0] = 0;
    pattern.pwm[1] = 255;
    pattern.pwm[2] = 255;
    pattern.pwm[3] = 0;
    pattern.pwm[4] = 0;

    pattern.slopeTime[0] = LP5814_TIME_1000_ms;
    pattern.slopeTime[1] = LP5814_TIME_200_ms;
    pattern.slopeTime[2] = LP5814_TIME_1000_ms;
    pattern.slopeTime[3] = LP5814_TIME_200_ms;

    pattern.repeat = 1;

    result = LP5814_setPattern(0, &pattern);

    if (result != LP5814_OK)
    {
        return result;
    }
    
    // Engine konfigurieren
    LP5814_EngineConfig_t engine = {0};

    engine.order[0].enabled = 1;
    engine.order[0].pattern = 0;
    engine.repeat = LP5814_REP_INFINITE;

    result = LP5814_setEngine(fullLeds, &engine);

    if (result != LP5814_OK)
    {
        return result;
        
    }
    
    // Animation starten
    return LP5814_startAnimation();    
     
     
}

uint8_t battLeds_showLevel5s(uint8_t percent)
{
    //Überprüfen ob der LP5814 initialisiert wurde
    if(!battLeds_initialized)
    {
        return BATT_LEDS_ERR_NOT_INIT;
    }
    
    // Parameter prüfen
    if(percent > 100)
    {
        return BATT_LEDS_ERR_PARAM;
    }
    
    // Anzahl der LEDs berechnen
    uint8_t ledCount = (percent + 24) / 25;
    
    // Bei 0% soll LED0 blinken
    if (percent < 10)
    {
        ledCount = 1;
    }
    
    // eventuell Laufende Animation stoppen
    uint8_t result = LP5814_stopAnimation();
    
    if (result != LP5814_OK)
    {
        return result;
    }
    
    // LED Ausgänge konfigurieren
    
    for (uint8_t i = 0; i < 4; i++)
    {
        battLeds_config.channel[i].mode = (i < ledCount) ? LP5814_MODE_AUTO : LP5814_MODE_MANUAL;

        battLeds_config.channel[i].fadeEnabled = 0;
        battLeds_config.channel[i].pwm = 0;
    }
    
    result = LP5814_init(&battLeds_config);
    
    if (result != LP5814_OK)
    {
        return result;
    }
    
    // Pattern konfigurieren
    LP5814_PatternConfig_t pattern = {0};

    
    if (percent < 10)
    {
        // 5x blinken: 500ms EIN, 500ms AUS

        pattern.pwm[0] = 255;
        pattern.pwm[1] = 255;
        pattern.pwm[2] = 0;
        pattern.pwm[3] = 0;
        pattern.pwm[4] = 0;

        // LED bleibt 500ms eingeschaltet
        pattern.slopeTime[0] = LP5814_TIME_500_ms;

        // Sofort ausschalten
        pattern.slopeTime[1] = LP5814_TIME_0MS;

        // LED bleibt 500ms ausgeschaltet
        pattern.slopeTime[2] = LP5814_TIME_500_ms;

        // Keine weitere Verzögerung
        pattern.slopeTime[3] = LP5814_TIME_0MS;

        // Fünf Wiederholungen
        pattern.repeat = 5;
    }

    else
    {
        // 5 Sekunden konstant hell, danach AUS
        pattern.pauseStart = LP5814_TIME_4000_ms;
        pattern.slopeTime[0] = LP5814_TIME_1000_ms;

        pattern.pwm[0] = 255;
        pattern.pwm[1] = 255;
        pattern.pwm[2] = 255;
        pattern.pwm[3] = 255;
        pattern.pwm[4] = 0;

        pattern.repeat = 1;
    }

    result = LP5814_setPattern(0, &pattern);

    if (result != LP5814_OK)
    {
        return result;
    }
    
    // Benötigte Engines konfigurieren
    LP5814_EngineConfig_t engine = {0};

    engine.order[0].enabled = 1;
    engine.order[0].pattern = 0;
    engine.repeat = LP5814_REP_0;

    for (uint8_t i = 0; i < ledCount; i++)
    {
        result = LP5814_setEngine(i, &engine);

        if (result != LP5814_OK)
        {
            return result;
        }
    }
    
    // Animation starten
    return LP5814_startAnimation();
}

uint8_t battLeds_startFill(void)
{
    //Überprüfen ob der LP5814 initialisiert wurde
    if(!battLeds_initialized)
    {
        return BATT_LEDS_ERR_NOT_INIT;
    }
    

    //eventuell Laufende Animation stoppen
    uint8_t result = LP5814_stopAnimation();

    if (result != LP5814_OK)
    {
        return result;
    }
    
    // Alle LEDs in den Auto Modus setzten
    for (uint8_t i = 0; i < 4; i++)
    {
        battLeds_config.channel[i].mode = LP5814_MODE_AUTO;
        battLeds_config.channel[i].fadeEnabled = 0;
        battLeds_config.channel[i].pwm = 0;
    }
    
    result = LP5814_init(&battLeds_config);

    if (result != LP5814_OK)
    {
        return result;
    }
    
    /// PATTERN0
    
    LP5814_PatternConfig_t pattern = {0};

    for (uint8_t i = 0; i < 5; i++)
    {
        pattern.pwm[i] = 255;
    }

    // Verhindert eine zeitlose Endlosschleife
    pattern.slopeTime[0] = LP5814_TIME_1000_ms;

    // Pattern wird dauerhaft wiederholt
    pattern.repeat = 15;

    result = LP5814_setPattern(0, &pattern);

    if (result != LP5814_OK)
    {
        return result;
    }
    
    // PATTERN 1 bis 3
    for (uint8_t led = 1; led < 4; led++)
    {
        pattern = (LP5814_PatternConfig_t){0};

        // PWM0 = 0, die restlichen PWM-Werte = 255
        for (uint8_t i = 1; i < 5; i++)
        {
            pattern.pwm[i] = 255;
        }

        // Wartezeit vor dem Einschalten
        if (led == 1)
        {
            pattern.pauseStart = LP5814_TIME_250_ms;
        }
        else
        {
            pattern.pauseStart = LP5814_TIME_500_ms;
        }

        if (led == 3)
        {
            // Weitere 250ms warten
            pattern.pwm[1] = 0;
            pattern.slopeTime[0] = LP5814_TIME_250_ms;

            // auf 100% dimmen
            pattern.slopeTime[1] = LP5814_TIME_100_ms;
        }
        else
        {
            // Innerhalb von 100ms auf 100% dimmen
            pattern.slopeTime[0] = LP5814_TIME_100_ms;
        }

        // Verzögerungs-Pattern nur einmal ausführen
        pattern.repeat = 1;

        result = LP5814_setPattern(led, &pattern);

        if (result != LP5814_OK)
        {
            return result;
        }
    }
    
    // Alle 4 Engines konfigurieren
    
    for (uint8_t led = 0; led < 4; led++)
    {
        LP5814_EngineConfig_t engine = {0};

        // Zuerst das eigene Pattern ausführen
        engine.order[0].enabled = 1;
        engine.order[0].pattern = led;

        if (led > 0)
        {
            // Danach dauerhaft PATTERN0 ausführen
            engine.order[1].enabled = 1;
            engine.order[1].pattern = 0;
        }

        // Engine-Sequenz selbst nicht wiederholen
        engine.repeat = LP5814_REP_0;

        result = LP5814_setEngine(led, &engine);

        if (result != LP5814_OK)
        {
            return result;
        }
    }
    
    // Animation starten
    return LP5814_startAnimation();
}

uint8_t battLeds_allOff(void)
{
    // Überprüfen ob der LP5814 initialisiert wurde
    if (!battLeds_initialized)
    {
        return BATT_LEDS_ERR_NOT_INIT;
    }

    // Eventuell laufende Animation stoppen
    uint8_t result = LP5814_stopAnimation();

    if (result != LP5814_OK)
    {
        return result;
    }

    // Alle vier LEDs ausschalten
    for (uint8_t i = 0; i < 4; i++)
    {
        battLeds_config.channel[i].mode = LP5814_MODE_MANUAL;
        battLeds_config.channel[i].fadeEnabled = 0;
        battLeds_config.channel[i].pwm = 0;
    }

    // Fade-Zeit deaktivieren
    battLeds_config.fadeTime = LP5814_TIME_0MS;

    // Neue Konfiguration übernehmen
    return LP5814_init(&battLeds_config);
}

uint8_t battLeds_showShutdownAnim(void)
{
    ///// Initialisierung überprüfen /////
    if (!battLeds_initialized)
    {
        return BATT_LEDS_ERR_NOT_INIT;
    }

    uint8_t result;

    ///// Laufende Animation stoppen /////
    result = LP5814_stopAnimation();

    if (result != LP5814_OK)
    {
        return result;
    }

    ///// Alle LEDs in den AUTO-Modus setzen /////
    for (uint8_t i = 0; i < 4; i++)
    {
        battLeds_config.channel[i].mode = LP5814_MODE_AUTO;
        battLeds_config.channel[i].fadeEnabled = 0;
        battLeds_config.channel[i].exponential = 1;
        battLeds_config.channel[i].pwm = 0;
    }

    result = LP5814_init(&battLeds_config);

    if (result != LP5814_OK)
    {
        return result;
    }

    ///// PATTERN0: Synchronisierter Doppelimpuls /////
    LP5814_PatternConfig_t pattern = {0};

    pattern.pwm[0] = 0;
    pattern.pwm[1] = 255;
    pattern.pwm[2] = 45;
    pattern.pwm[3] = 255;
    pattern.pwm[4] = 255;

    pattern.slopeTime[0] = LP5814_TIME_100_ms;
    pattern.slopeTime[1] = LP5814_TIME_150_ms;
    pattern.slopeTime[2] = LP5814_TIME_150_ms;
    pattern.slopeTime[3] = LP5814_TIME_100_ms;

    pattern.repeat = 1;

    result = LP5814_setPattern(0, &pattern);

    if (result != LP5814_OK)
    {
        return result;
    }

    ///// PATTERN1: Mehrstufiges Ausdimmen /////
    pattern = (LP5814_PatternConfig_t){0};

    pattern.pwm[0] = 255;
    pattern.pwm[1] = 180;
    pattern.pwm[2] = 90;
    pattern.pwm[3] = 25;
    pattern.pwm[4] = 0;

    pattern.slopeTime[0] = LP5814_TIME_100_ms;
    pattern.slopeTime[1] = LP5814_TIME_150_ms;
    pattern.slopeTime[2] = LP5814_TIME_250_ms;
    pattern.slopeTime[3] = LP5814_TIME_400_ms;

    pattern.repeat = 1;

    result = LP5814_setPattern(1, &pattern);

    if (result != LP5814_OK)
    {
        return result;
    }

    ///// PATTERN2: 150ms warten bei 100% /////
    pattern = (LP5814_PatternConfig_t){0};

    for (uint8_t i = 0; i < 5; i++)
    {
        pattern.pwm[i] = 255;
    }

    pattern.slopeTime[0] = LP5814_TIME_150_ms;
    pattern.repeat = 1;

    result = LP5814_setPattern(2, &pattern);

    if (result != LP5814_OK)
    {
        return result;
    }

    ///// PATTERN3: 300ms warten bei 100% /////
    pattern = (LP5814_PatternConfig_t){0};

    for (uint8_t i = 0; i < 5; i++)
    {
        pattern.pwm[i] = 255;
    }

    pattern.slopeTime[0] = LP5814_TIME_300_ms;
    pattern.repeat = 1;

    result = LP5814_setPattern(3, &pattern);

    if (result != LP5814_OK)
    {
        return result;
    }

    ///// Vier Engines individuell konfigurieren /////
    for (uint8_t led = 0; led < 4; led++)
    {
        LP5814_EngineConfig_t engine = {0};
        uint8_t order = 0;

        // Alle LEDs beginnen mit dem Doppelimpuls
        engine.order[order].enabled = 1;
        engine.order[order].pattern = 0;
        order++;

        // LED0 und LED2 zusätzlich 150ms warten
        if (led == 0 || led == 2)
        {
            engine.order[order].enabled = 1;
            engine.order[order].pattern = 2;
            order++;
        }

        // LED0 und LED1 zusätzlich 300ms warten
        if (led == 0 || led == 1)
        {
            engine.order[order].enabled = 1;
            engine.order[order].pattern = 3;
            order++;
        }

        // Zuletzt immer weich ausdimmen
        engine.order[order].enabled = 1;
        engine.order[order].pattern = 1;

        // Gesamte Sequenz nur einmal abspielen
        engine.repeat = LP5814_REP_0;

        result = LP5814_setEngine(led, &engine);

        if (result != LP5814_OK)
        {
            return result;
        }
    }

    ///// Shutdown-Animation starten /////
    return LP5814_startAnimation();
}

uint8_t battLeds_sleep(void)
{
    // Überprüfen ob der LP5814 initialisiert wurde
    if (!battLeds_initialized)
    {
        return BATT_LEDS_ERR_NOT_INIT;
    }

    // LP5814 in den Shutdown-Modus versetzen
    uint8_t result = LP5814_shutdown();

    if (result != LP5814_OK)
    {
        return result;
    }

    // BSP als nicht initialisiert markieren
    battLeds_initialized = 0;

    return BATT_LEDS_OK;
}


uint8_t battLeds_wakeup(void)
{
    // Falls bereits initialisiert, nichts machen
    if (battLeds_initialized)
    {
        return BATT_LEDS_OK;
    }

    // LP5814 über SDA aufwecken
    uint8_t result = LP5814_wakeUp();

    if (result != LP5814_OK)
    {
        return result;
    }

    // LP5814 erneut initialisieren
    return battLeds_init();
}



