/*********************************************************************************\
*
* Dateiname: TCA9555.c
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
*
* Portbelegung:
* =============
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Bietet Funktionen zur Ansteuerung des TCA9555 Port Expander
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 07.11.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/

#include <stdint.h>

#include "include/driver/TCA9555.h"
#include "include/hal/TWI.h"
#include "include/hal/GPIO.h"

///// ADDRESSEN /////
#define TCA9555_ADDR_MAX                    0x27
#define TCA9555_ADDR_MIN                    0x20

///// REGISTER //////
#define TCA9555_INPUT_PORT_0                0x00
#define TCA9555_INPUT_PORT_1                0x01

#define TCA9555_OUTPUT_PORT_0               0x02
#define TCA9555_OUTPUT_PORT_1               0x03

#define TCA9555_POLARITY_INVERSION_PORT_0   0x04
#define TCA9555_POLARITY_INVERSION_PORT_1   0x05

#define TCA9555_CONFIGURATION_PORT_0        0X06
#define TCA9555_CONFIGURATION_PORT_1        0X07

uint8_t TCA9555_readInputPorts(uint8_t addr, uint16_t *data)
{
    //addresbereich prüfen
    if(addr > TCA9555_ADDR_MAX || addr < TCA9555_ADDR_MIN)
    {
        return TCA9555_ERR_ADDRESS;
    }
    
    // Input port 0 & 1 auslesen und in data zurèckgeben
    if(TWI_readBlock(addr, TCA9555_INPUT_PORT_0, (uint8_t *)data, 2) == TWI_OK)
    {
        return TCA9555_OK;
    }
    else
    {
        return TCA9555_ERR_TWI;
    }
}

uint8_t TCA9555_readOutputPorts(uint8_t addr, uint16_t *data)
{
    //addresbereich prüfen
    if(addr > TCA9555_ADDR_MAX || addr < TCA9555_ADDR_MIN)
    {
        return TCA9555_ERR_ADDRESS;
    }
    
    // Output port 0 & 1 auslesen und in data zurèckgeben
    if(TWI_readBlock(addr, TCA9555_OUTPUT_PORT_0, (uint8_t *)data, 2) == TWI_OK)
    {
        return TCA9555_OK;
    }
    else
    {
        return TCA9555_ERR_TWI;
    }
}

uint8_t TCA9555_writeOutputPorts(uint8_t addr, uint16_t outputMask)
{
    //addresbereich prüfen
    if(addr > TCA9555_ADDR_MAX || addr < TCA9555_ADDR_MIN)
    {
        return TCA9555_ERR_ADDRESS;
    }
    
    // 16bit makse aufteilen auf zwei 8bit werte
    uint8_t data[2] = 
    {
            (uint8_t)(outputMask & 0xFF),
            (uint8_t)(outputMask >> 8)
    };
    
    // Output port 0 & 1 schreiben nach outputMask
    if(TWI_writeBlock(addr, TCA9555_OUTPUT_PORT_0, data, 2) == TWI_OK)
    {
        return TCA9555_OK;
    }
    else
    {
        return TCA9555_ERR_TWI;
    }
}

uint8_t TCA9555_writePolarityInversion(uint8_t addr, uint8_t port01, uint8_t bitMask)
{
    //addresbereich prüfen
    if(addr > TCA9555_ADDR_MAX || addr < TCA9555_ADDR_MIN)
    {
        return TCA9555_ERR_ADDRESS;
    }

    
    switch (port01)
    {
        case 0:
            // Output port 0 & 1 schreiben nach outputMask
            if(TWI_writeBlock(addr, TCA9555_POLARITY_INVERSION_PORT_0, &bitMask, 1) == TWI_OK)
            {
                return TCA9555_OK;
            }
            else
            {
                return TCA9555_ERR_TWI;
            }
        break;
        
        case 1:
            // Output port 0 & 1 schreiben nach outputMask
            if(TWI_writeBlock(addr, TCA9555_POLARITY_INVERSION_PORT_1, &bitMask, 1) == TWI_OK)
            {
                return TCA9555_OK;
            }
            else
            {
                return TCA9555_ERR_TWI;
            }
        break;
        
        default:
        return TCA9555_ERR_PORT;
        break;
    }
}

uint8_t TCA9555_readPolarityInversion(uint8_t addr, uint8_t port01, uint8_t *data)
{
    //addresbereich prüfen
    if(addr > TCA9555_ADDR_MAX || addr < TCA9555_ADDR_MIN)
    {
        return TCA9555_ERR_ADDRESS;
    }
    
    switch (port01)
    {
        case 0:
            // Inversion Port 0 auslesen und in data zurèckgeben
            if(TWI_readBlock(addr, TCA9555_POLARITY_INVERSION_PORT_0, data, 1) == TWI_OK)
            {
                return TCA9555_OK;
            }
            else
            {
                return TCA9555_ERR_TWI;
            }
        break;
        
        case 1:
            // Inversion Port 1 auslesen und in data zurèckgeben
            if(TWI_readBlock(addr, TCA9555_POLARITY_INVERSION_PORT_1, data, 1) == TWI_OK)
            {
                return TCA9555_OK;
            }
            else
            {
                return TCA9555_ERR_TWI;
            }
        break;
        
        default:
            return TCA9555_ERR_PORT;
        break;
    }
}

uint8_t TCA9555_writeConfiguration(uint8_t addr, uint8_t port01, uint8_t bitMask)
{
    //addresbereich prüfen
    if(addr > TCA9555_ADDR_MAX || addr < TCA9555_ADDR_MIN)
    {
        return TCA9555_ERR_ADDRESS;
    }

    
    switch (port01)
    {
        case 0:
        // Output port 0 & 1 schreiben nach outputMask
        if(TWI_writeBlock(addr, TCA9555_CONFIGURATION_PORT_0, &bitMask, 1) == TWI_OK)
        {
            return TCA9555_OK;
        }
        else
        {
            return TCA9555_ERR_TWI;
        }
        break;
        
        case 1:
        // Output port 0 & 1 schreiben nach outputMask
        if(TWI_writeBlock(addr, TCA9555_CONFIGURATION_PORT_1, &bitMask, 1) == TWI_OK)
        {
            return TCA9555_OK;
        }
        else
        {
            return TCA9555_ERR_TWI;
        }
        break;
        
        default:
            return TCA9555_ERR_PORT;
        break;
    }
}

uint8_t TCA9555_readConfiguration(uint8_t addr, uint8_t port01, uint8_t *data)
{
    //addresbereich prüfen
    if(addr > TCA9555_ADDR_MAX || addr < TCA9555_ADDR_MIN)
    {
        return TCA9555_ERR_ADDRESS;
    }
    
    switch (port01)
    {
        case 0:
            // Configuration Port 0 auslesen und in data zurèckgeben
            if(TWI_readBlock(addr, TCA9555_CONFIGURATION_PORT_0, data, 1) == TWI_OK)
            {
                return TCA9555_OK;
            }
            else
            {
                return TCA9555_ERR_TWI;
            }
        break;
        
        case 1:
            // Configuration Port 1 auslesen und in data zurèckgeben
            if(TWI_readBlock(addr, TCA9555_CONFIGURATION_PORT_1, data, 1) == TWI_OK)
            {
                return TCA9555_OK;
            }
            else
            {
                return TCA9555_ERR_TWI;
            }
        break;
        
        default:
            return TCA9555_ERR_PORT;
        break;
    }
}

