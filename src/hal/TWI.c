/*********************************************************************************\
*
* Dateiname: TWI.c
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny1626 auf Hauptplatine V1
*
* Portbelegung:
* =============
* PB0: SCL
* PB1: SDA
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Initialisiert und konfiguriert das TWI innerhalb des ATtiny1626 und bietet Ansteuerungsmöglichkeiten.
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 24.10.2026  J. Meyer       V1.0      Neuerstellung
* 01.11.2026  J. Meyer       V1.1      Blockfunktionen und Fehlerbehandlung
* 21.11.2026  J. Meyer       V1.2      TWI-Modul Ein-/Ausschalten könnten
*
\*********************************************************************************/

#include <stdint.h>
#include <avr/io.h>

#include "include/hal/TWI.h"
#include "include/hal/GPIO.h"

#define TWI_TIMEOUT 60000U

///// lokale Funktionen /////
static void TWI_writeAddress(uint8_t addr);
static void TWI_writeData(uint8_t data);
static uint8_t TWI_read(void);
static void TWI_stop(void);
static uint8_t TWI_waitStop(void);
static uint8_t TWI_waitWriteChecked(void);
static uint8_t TWI_waitReadChecked(void);

///// Hilfsfunktionen /////

//Sendet 1 Byte an das Adressregister
static void TWI_writeAddress(uint8_t addr)
{
    TWI0.MADDR = addr;
}

//Sendet 1 Byte an das Datenregister
static void TWI_writeData(uint8_t data)
{
    TWI0.MDATA = data;
}

//Gibt die eingelesenen Daten des Datenregisters zurück
static uint8_t TWI_read(void)
{
    return TWI0.MDATA;
}

//Sendet STOP, sofern der ATtiny noch Besitzer des Busses ist
static void TWI_stop(void)
{
    if ((TWI0.MSTATUS & TWI_BUSSTATE_gm) == TWI_BUSSTATE_OWNER_gc)
    {
        TWI0.MCTRLB = TWI_MCMD_STOP_gc;
        (void)TWI_waitStop();
    }
}

//Wartet bis die STOP-Bedingung abgeschlossen ist
static uint8_t TWI_waitStop(void)
{
    uint16_t timeoutTime = TWI_TIMEOUT;

    while ((TWI0.MSTATUS & TWI_BUSSTATE_gm) == TWI_BUSSTATE_OWNER_gc)
    {
        if (--timeoutTime == 0)
        {
            return TWI_ERR_TIMEOUT;
        }
    }

    return TWI_OK;
}

//Wartet auf WIF und prüft auf Fehler
static uint8_t TWI_waitWriteChecked(void)
{
    uint16_t timeoutTime = TWI_TIMEOUT;

    while (1)
    {
        uint8_t status = TWI0.MSTATUS;

        //Busfehler oder Arbitration Lost: Bus gehört uns nicht mehr
        if (status & (TWI_ARBLOST_bm | TWI_BUSERR_bm))
        {
            return TWI_ERR_BUS;
        }

        //Das Adress- oder Datenbyte wurde gesendet
        if (status & TWI_WIF_bm)
        {
            if (status & TWI_RXACK_bm)
            {
                TWI_stop();
                return TWI_ERR_NACK;
            }

            return TWI_OK;
        }

        //Falls Timeout
        if (--timeoutTime == 0)
        {
            TWI_stop();
            return TWI_ERR_TIMEOUT;
        }
    }
}

//Wartet auf RIF und prüft auf Fehler
static uint8_t TWI_waitReadChecked(void)
{
    uint16_t timeoutTime = TWI_TIMEOUT;

    while (1)
    {
        uint8_t status = TWI0.MSTATUS;

        //Busfehler oder Arbitration Lost: Bus gehört uns nicht mehr
        if (status & (TWI_ARBLOST_bm | TWI_BUSERR_bm))
        {
            return TWI_ERR_BUS;
        }

        //Ein Datenbyte wurde empfangen
        if (status & TWI_RIF_bm)
        {
            return TWI_OK;
        }

        //WIF statt RIF: z.B. Slave-Adresse nicht bestätigt
        if (status & TWI_WIF_bm)
        {
            TWI_stop();
            return (status & TWI_RXACK_bm) ? TWI_ERR_NACK : TWI_ERR_BUS;
        }

        //Falls Timeout
        if (--timeoutTime == 0)
        {
            TWI_stop();
            return TWI_ERR_TIMEOUT;
        }
    }
}

///// Öffentliche Funktionen /////

//Initialisiert das TWI
void TWI_init(uint32_t baudRate)
{
    //TWI deaktivieren, damit die Baudrate geschrieben werden darf
    TWI0.MCTRLA = 0;

    //Standard-/Fast-Mode ohne zusätzliche SDA-Haltezeit
    TWI0.CTRLA = 0;

    //Baudrate einstellen (muss zur tatsächlichen CPU-Frequenz passen)
    TWI0.MBAUD = (uint8_t)TWI0_BAUD(baudRate, 0);

    //TWI als Master konfigurieren, Smart Mode und Interrupts deaktiviert
    TWI0.MCTRLA = TWI_ENABLE_bm | TWI_TIMEOUT_DISABLED_gc;

    //Busstatus auf IDLE zwingen
    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
}

//Liest mehrere Bytes ab einem Register über TWI aus
uint8_t TWI_readBlock(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t length)
{
    uint8_t status;

    //Ungültige Parameter pruefen
    if ((addr > 0x7F) || ((data == 0) && (length > 0)))
    {
        return TWI_ERR_PARAM;
    }

    //Bei 0 Bytes ist keine Übertragung notwendig
    if (length == 0)
    {
        return TWI_OK;
    }

    //START + Slave-Adresse als Write senden
    TWI_writeAddress((addr << 1) | 0);
    if ((status = TWI_waitWriteChecked()) != TWI_OK)
    {
        return status;
    }

    //Register-Adresse senden
    TWI_writeData(reg);
    if ((status = TWI_waitWriteChecked()) != TWI_OK)
    {
        return status;
    }

    //Repeated Start + dieselbe Slave-Adresse als Read senden
    TWI_writeAddress((addr << 1) | 1);

    for (uint16_t i = 0; i < length; i++)
    {
        //Auf das nächste empfangene Byte warten
        if ((status = TWI_waitReadChecked()) != TWI_OK)
        {
            return status;
        }

        //Empfangenes Byte auslesen
        data[i] = TWI_read();

        if (i < (length - 1))
        {
            //ACK senden und nächstes Byte empfangen
            TWI0.MCTRLB = TWI_ACKACT_ACK_gc | TWI_MCMD_RECVTRANS_gc;
        }
        else
        {
            //Letztes Byte: NACK senden und STOP auslösen
            TWI0.MCTRLB = TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;
        }
    }

    return TWI_waitStop();
}

//Schreibt mehrere Bytes ab einem Register über TWI
uint8_t TWI_writeBlock(uint8_t addr, uint8_t reg, const uint8_t *data, uint16_t length)
{
    uint8_t status;

    //Ungültige Parameter pruefen
    if ((addr > 0x7F) || ((data == 0) && (length > 0)))
    {
        return TWI_ERR_PARAM;
    }

    //Bei 0 Bytes ist keine Übertragung notwendig
    if (length == 0)
    {
        return TWI_OK;
    }

    //START + Slave-Adresse als Write senden
    TWI_writeAddress((addr << 1) | 0);
    if ((status = TWI_waitWriteChecked()) != TWI_OK)
    {
        return status;
    }

    //Register-Adresse senden
    TWI_writeData(reg);
    if ((status = TWI_waitWriteChecked()) != TWI_OK)
    {
        return status;
    }

    //Alle Datenbytes nacheinander senden
    for (uint16_t i = 0; i < length; i++)
    {
        TWI_writeData(data[i]);
        if ((status = TWI_waitWriteChecked()) != TWI_OK)
        {
            return status;
        }
    }

    //STOP senden und auf die Freigabe des Busses warten
    TWI0.MCTRLB = TWI_MCMD_STOP_gc;

    return TWI_waitStop();
}

//Liest 1 Byte über TWI aus einem Register aus (alte Rueckgabe beibehalten)
uint8_t TWI_read8Bit(uint8_t addr, uint8_t reg)
{
    uint8_t value = 0;
    uint8_t status = TWI_readBlock(addr, reg, &value, 1);

    if (status != TWI_OK)
    {
        return status;
    }

    return value;
}

//Schreibt 1 Byte über TWI in ein Register
uint8_t TWI_write8Bit(uint8_t addr, uint8_t reg, uint8_t value)
{
    return TWI_writeBlock(addr, reg, &value, 1);
}

// TWI-Modul deaktivieren

uint8_t TWI_disable(void)
{
    // Überprüfen ob TWI aktiviert ist
    if (TWI0.MCTRLA & TWI_ENABLE_bm)
    {
        uint8_t busState = TWI0.MSTATUS & TWI_BUSSTATE_gm;

        // Falls uC den Bus besitz STOP senden
        if (busState == TWI_BUSSTATE_OWNER_gc)
        {
            TWI0.MCTRLB = TWI_MCMD_STOP_gc;

            uint8_t result = TWI_waitStop();

            if (result != TWI_OK)
            {
                return result;
            }
        }

        // Überprüfen ob der Bus jetzt frei ist
        if ((TWI0.MSTATUS & TWI_BUSSTATE_gm)
        != TWI_BUSSTATE_IDLE_gc)
        {
            return TWI_ERR_BUS;
        }

        // TWI deaktivieren
        TWI0.MCTRLA &= ~TWI_ENABLE_bm;
    }

    // SCL und SDA pins als Eingang festlegen
    GPIO_setPinDirection(&PORTB, 0, GPIO_INPUT);
    GPIO_setPinDirection(&PORTB, 1, GPIO_INPUT);

    return TWI_OK;
}


// TWI-Modul aktivieren
uint8_t TWI_enable(void)
{
    // Überprüfen ob das TWI-Modul bereits aktiviert ist
    if (TWI0.MCTRLA & TWI_ENABLE_bm)
    {
        return TWI_OK;
    }

    // SCL und SDA freigeben
    PORTB.DIRCLR = PIN0_bm | PIN1_bm;
    PORTB.OUTCLR = PIN0_bm | PIN1_bm;

    // Überprüfen ob SDA und SCL HIGH sind
    if ((PORTB.IN & (PIN0_bm | PIN1_bm)) != (PIN0_bm | PIN1_bm))
    {
        return TWI_ERR_BUS;
    }

    // TWI aktivieren
    TWI0.MCTRLA |= TWI_ENABLE_bm;

    // Busstatus auf IDLE setzten
    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;

    return TWI_OK;
}
