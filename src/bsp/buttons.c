/*********************************************************************************\
*
* Dateiname: buttons.c
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
* Portbelegung:
* =============
* PB0: INT linie
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Stellt Funktionen für die ansteuerung der Taster auf auf dem Print via TCA9555 über TWI zur verfügung
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 07.11.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/

#include <avr/io.h>

#include "include/bsp/buttons.h"
#include "include/hal/GPIO.h"
#include "include/driver/TCA9555.h"

uint8_t buttons_init(void)
{
    // Interrupt-Pin als Eingang konfigurieren
    GPIO_setPinDirection(&BUTTONS_INT_PORT, BUTTONS_INT_PIN, GPIO_INPUT);

    // Alle TCA9555 initialisieren
    for (uint8_t addr = BUTTONS_ADDR_1; addr <= BUTTONS_ADDR_4; addr++)
    {
        for (uint8_t port = 0; port < 2; port++)
        {
            uint8_t input = 0;

            // Alle Pins als Eingang konfigurieren
            if (TCA9555_writeConfiguration(addr, port, 0xFF) != TCA9555_OK)
            return BUTTONS_ERR_TWI;

            // Konfiguration kontrollieren
            if (TCA9555_readConfiguration(addr, port, &input) != TCA9555_OK)
            return BUTTONS_ERR_TWI;

            if (input != 0xFF)
            return BUTTONS_ERR_REG;

            // Eingangspolarität invertieren
            if (TCA9555_writePolarityInversion(addr, port, 0xFF) != TCA9555_OK)
            return BUTTONS_ERR_TWI;

            // Polaritätsinvertierung kontrollieren
            if (TCA9555_readPolarityInversion(addr, port, &input) != TCA9555_OK)
            return BUTTONS_ERR_TWI;

            if (input != 0xFF)
            return BUTTONS_ERR_REG;
        }
    }

    return BUTTONS_OK;
}

uint8_t button_isPressed(uint8_t button)
{
    uint16_t input = 0;
    
    if(button > 64)
    {
        return 0;
    }
    
    uint8_t ic = (button - 1) / 16;
    uint8_t bit = (button - 1) % 16;
    
    if (TCA9555_readInputPorts(BUTTONS_ADDR_1 + ic, &input) != TCA9555_OK)
    {
        return 0;
    }
    
    if(input & ((uint16_t)1U << bit))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint64_t buttons_allPressed(void)
{
    uint64_t buttonStates = 0;
    uint16_t input = 0;

    for (uint8_t i = 0; i < 4; i++)
    {
        if (TCA9555_readInputPorts(BUTTONS_ADDR_1 + i, &input) != TCA9555_OK)
        {
            return 0;
        }

        buttonStates |= ((uint64_t)input << (i * 16));
    }

    return buttonStates;
}