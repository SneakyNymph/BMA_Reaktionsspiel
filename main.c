
/*
 * main.c
 *
 * Projekt  : Tisch Reaktionsspiel BMA
 * Hardware : ATtiny3226 auf Hauptplatine V1
 *
 * Grundgeruest mit BMS, Laderegler und 5V Versorgung.
 * Spielablauf und weitere Funktionen folgen spaeter.
 */

#ifndef F_CPU
#define F_CPU 20000000UL
#endif

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "include/hal/System.h"
#include "include/hal/TWI.h"
#include "include/hal/GPIO.h"

#include "include/bsp/debug.h"
#include "include/bsp/buzzer.h"

#include "include/service/BatteryService.h"
#include "include/driver/BQ25883.h"


int main(void)
{
    ///// Grundinitialisierung /////
    system_setupMainCLK();
    TWI_init(100000);
    debug_initLEDs();
    buzzer_init();

    // 5V Versorgung zuerst ausschalten
    GPIO_setPinDirection(&PORTA, 2, GPIO_OUTPUT);
    GPIO_pinWrite(&PORTA, 2, 0);

    sei();


    ///// BMS initialisieren /////
    _delay_ms(500);

    if (!BMS_Service_start(1))
    {
        debug_setLED(1, 1);

        while (1)
        {
        }
    }

    BMS_Service_setBalancingPermission(1);


    ///// 5V Versorgung einschalten /////
    GPIO_pinWrite(&PORTA, 2, 1);


    ///// BQ25883 Pins konfigurieren /////
    BQ25883_PinConfig_t chargerPins =
    {
        .cePort  = &PORTC,
        .cePin   = 0,

        .intPort = &PORTC,
        .intPin  = 1,

        .pgPort  = &PORTC,
        .pgPin   = 2
    };

    if (BQ25883_configPins(&chargerPins) != BQ25883_OK)
    {
        debug_setLED(2, 1);
        GPIO_pinWrite(&PORTA, 2, 0);

        while (1)
        {
        }
    }


    ///// BQ25883 initialisieren /////
    BQ25883_Config_t chargerConfig;

    // TI Standardwerte laden
    if (BQ25883_defaultConfig(&chargerConfig) != BQ25883_OK)
    {
        debug_setLED(2, 1);
        GPIO_pinWrite(&PORTA, 2, 0);

        while (1)
        {
        }
    }

    // Unsere Einstellungen
    chargerConfig.watchdog = BQ25883_WATCHDOG_DISABLED;
    chargerConfig.chargeCurrent_mA = 1000;

    // Konfiguration uebertragen und prüfen
    if (BQ25883_config(&chargerConfig) != BQ25883_OK)
    {
        debug_setLED(2, 1);
        GPIO_pinWrite(&PORTA, 2, 0);

        while (1)
        {
        }
    }


    ///// Laden freigeben /////
    if (BQ25883_setChargeEnabled(1) != BQ25883_OK)
    {
        BQ25883_setChargeEnabled(0);
        debug_setLED(2, 1);
        GPIO_pinWrite(&PORTA, 2, 0);

        while (1)
        {
        }
    }


    ///// Weitere Hardware initialisieren /////
    // Hier spaeter WS2812, Taster, LP5814 usw.


    ///// Hauptschleife /////
    while (1)
    {
        // BMS alle 200ms ueberwachen
        _delay_ms(200);
        BMS_Service_tick200ms();

        BMS_Snapshot battery = BMS_Service_getSnapshot();

        if (battery.state != BMS_RUNNING)
        {
            // Laden und 5V Versorgung abschalten
            BQ25883_setChargeEnabled(0);
            GPIO_pinWrite(&PORTA, 2, 0);

            debug_setLED(1, 1);

            while (1)
            {
            }
        }


        ///// Hier spaeter Anwendungslogik /////

    }
}
