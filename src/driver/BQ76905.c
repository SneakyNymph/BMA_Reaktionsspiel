/*********************************************************************************\
*
* Dateiname: BQ76905.c
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
* Konfiguriert den BQ76905 für zwei LiPo-Zellen mit 10mOhm Messwiderstand.
* Bietet Funktionen zum Lesen von Messwerten und zum Steuern der Schutz-FETs.
* Die Schutz-FETs bleiben nach der Initialisierung ausgeschaltet.
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 01.11.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/

#include <stdint.h>
#include <stddef.h>

#include "include/hal/TWI.h"
#include "include/driver/BQ76905.h"

///// Register /////
#define BQ_REG_BATTERY_STATUS       0x12
#define BQ_REG_CELL1_VOLTAGE       0x14
#define BQ_REG_CELL5_VOLTAGE       0x1C
#define BQ_REG_STACK_VOLTAGE       0x26
#define BQ_REG_INT_TEMPERATURE     0x28
#define BQ_REG_RAW_CURRENT         0x36
#define BQ_REG_SAFETY_STATUS_A     0x03
#define BQ_REG_SAFETY_STATUS_B     0x05
#define BQ_REG_ALARM_STATUS        0x62
#define BQ_REG_FET_CONTROL         0x68
#define BQ_REG_REGOUT_CONTROL      0x69
#define BQ_REG_SUBCOMMAND          0x3E
#define BQ_REG_DATA_BUFFER         0x40
#define BQ_REG_CHECKSUM            0x60

///// Subcommands /////
#define BQ_CMD_DEVICE_NUMBER       0x0001
#define BQ_CMD_FET_ENABLE          0x0022
#define BQ_CMD_SET_CFGUPDATE       0x0090
#define BQ_CMD_EXIT_CFGUPDATE      0x0092
#define BQ_CMD_CB_ACTIVE_CELLS     0x0083

///// Daten-RAM /////
#define BQ_RAM_REGOUT_CONFIG       0x9015
#define BQ_RAM_DA_CONFIG           0x9019
#define BQ_RAM_VCELL_MODE          0x901B
#define BQ_RAM_FET_OPTIONS         0x901E
#define BQ_RAM_ENABLED_PROT_A      0x9024
#define BQ_RAM_ENABLED_PROT_B      0x9025
#define BQ_RAM_OPENWIRE_NORMAL     0x902B
#define BQ_RAM_CUV_THRESHOLD       0x902E
#define BQ_RAM_COV_THRESHOLD       0x9032
#define BQ_RAM_OCC_THRESHOLD       0x9036
#define BQ_RAM_OCC_DELAY           0x9037
#define BQ_RAM_OCD1_THRESHOLD      0x9038
#define BQ_RAM_OCD1_DELAY          0x9039
#define BQ_RAM_OCD2_THRESHOLD      0x903A
#define BQ_RAM_OCD2_DELAY          0x903B
#define BQ_RAM_SCD_THRESHOLD       0x903C
#define BQ_RAM_SCD_DELAY           0x903D
#define BQ_RAM_OTINT_THRESHOLD     0x904C
#define BQ_RAM_OTINT_RECOVERY      0x904E

///// Statusbits /////
#define BQ_STATUS_SAFETY_FAULT     0x1000
#define BQ_STATUS_FET_ENABLE      0x0100
#define BQ_STATUS_POR             0x0080
#define BQ_STATUS_CFGUPDATE       0x0020
#define BQ_STATUS_CHG             0x0008
#define BQ_STATUS_DSG             0x0004

#define BQ_MAX_BLOCK_LENGTH        32U
#define BQ_STATUS_RETRIES          200U

///// lokale Variablen /////
static uint8_t BQ_ready = 0;
static uint8_t BQ_lastTWIError = 0;

///// lokale Funktionen /////
static uint8_t BQ_twiStatus(uint8_t twiStatus);
static uint8_t BQ_subcommand(uint16_t command);
static uint8_t BQ_waitConfigMode(uint8_t enabled);
static uint8_t BQ_writeConfig8(uint16_t address, uint8_t value);
static uint8_t BQ_writeConfig16(uint16_t address, uint16_t value);
static uint8_t BQ_readSigned16(uint8_t reg, int16_t *value);
static uint8_t BQ_checkConfig(void);

///// Hilfsfunktionen /////

//Übersetzt Fehlercodes des TWI-Treibers
static uint8_t BQ_twiStatus(uint8_t twiStatus)
{
    BQ_lastTWIError = twiStatus;
    return (twiStatus == TWI_OK) ? BQ76905_OK : BQ76905_ERR_TWI;
}

//Sendet einen Subcommand (16-Bit, little endian)
static uint8_t BQ_subcommand(uint16_t command)
{
    uint8_t data[2] = {(uint8_t)command, (uint8_t)(command >> 8)};
    return BQ_twiStatus(TWI_writeBlock(BQ76905_ADDR, BQ_REG_SUBCOMMAND, data, 2));
}

//Wartet bis der gewünschte CONFIG_UPDATE Status erreicht ist
static uint8_t BQ_waitConfigMode(uint8_t enabled)
{
    uint16_t status;

    for (uint16_t i = 0; i < BQ_STATUS_RETRIES; i++)
    {
        uint8_t result = BQ76905_readBatteryStatus(&status);
        if (result != BQ76905_OK)
        {
            return result;
        }

        if (((status & BQ_STATUS_CFGUPDATE) != 0) == (enabled != 0))
        {
            return BQ76905_OK;
        }
    }

    return BQ76905_ERR_STATE;
}

//Schreibt und überprüft ein 8-Bit RAM-Register
static uint8_t BQ_writeConfig8(uint16_t address, uint8_t value)
{
    return BQ76905_writeDataMemory(address, &value, 1);
}

//Schreibt und überprüft ein 16-Bit RAM-Register
static uint8_t BQ_writeConfig16(uint16_t address, uint16_t value)
{
    uint8_t data[2] = {(uint8_t)value, (uint8_t)(value >> 8)};
    return BQ76905_writeDataMemory(address, data, 2);
}

//Liest einen vorzeichenbehafteten 16-Bit Wert
static uint8_t BQ_readSigned16(uint8_t reg, int16_t *value)
{
    uint16_t raw;
    uint8_t result;

    if (value == NULL)
    {
        return BQ76905_ERR_PARAM;
    }

    result = BQ76905_readDirect16(reg, &raw);
    if (result != BQ76905_OK)
    {
        return result;
    }

    //Vorzeichen ohne undefinierten Cast umrechnen
    int32_t signedValue = raw;
    if (signedValue >= 32768)
    {
        signedValue -= 65536;
    }
    *value = (int16_t)signedValue;
    return BQ76905_OK;
}

//Prüft die wichtigsten RAM-Werte, z.B. nach einem Neustart des ATtiny
static uint8_t BQ_checkConfig(void)
{
    static const struct
    {
        uint16_t address;
        uint16_t value;
        uint8_t length;
    } config[] =
    {
        {BQ_RAM_REGOUT_CONFIG, 0x000F, 1},
        {BQ_RAM_DA_CONFIG, 0x0100, 2},
        {BQ_RAM_VCELL_MODE, 0x0002, 1},
        {BQ_RAM_FET_OPTIONS, 0x0058, 1},
        {BQ_RAM_ENABLED_PROT_A, 0x00FD, 1},
        {BQ_RAM_ENABLED_PROT_B, 0x0002, 1},
        {BQ_RAM_CUV_THRESHOLD, BQ76905_CUV_MV, 2},
        {BQ_RAM_COV_THRESHOLD, BQ76905_COV_MV, 2},
        {BQ_RAM_OCC_THRESHOLD, BQ76905_OCC_2MV, 1},
        {BQ_RAM_OCC_DELAY, 0x0050, 1},
        {BQ_RAM_OCD1_THRESHOLD, BQ76905_OCD1_2MV, 1},
        {BQ_RAM_OCD1_DELAY, 0x0064, 1},
        {BQ_RAM_OCD2_THRESHOLD, BQ76905_OCD2_2MV, 1},
        {BQ_RAM_OCD2_DELAY, 0x0020, 1},
        {BQ_RAM_SCD_THRESHOLD, BQ76905_SCD_SETTING, 1},
        {BQ_RAM_SCD_DELAY, 0x0004, 1},
        {BQ_RAM_OTINT_THRESHOLD, 90, 1},
        {BQ_RAM_OTINT_RECOVERY, 80, 1},
        {BQ_RAM_OPENWIRE_NORMAL, 10, 1}
    };

    for (uint8_t i = 0; i < sizeof(config) / sizeof(config[0]); i++)
    {
        uint8_t data[2];
        uint8_t result = BQ76905_readDataMemory(config[i].address, data, config[i].length);
        if (result != BQ76905_OK) return result;

        uint16_t value = data[0];
        if (config[i].length == 2) value |= (uint16_t)data[1] << 8;
        if (value != config[i].value) return BQ76905_ERR_VERIFY;
    }

    return BQ76905_OK;
}

///// Öffentliche Funktionen /////

//Liest ein 8-Bit Direktregister
uint8_t BQ76905_readDirect8(uint8_t reg, uint8_t *value)
{
    if (value == NULL)
    {
        return BQ76905_ERR_PARAM;
    }

    return BQ_twiStatus(TWI_readBlock(BQ76905_ADDR, reg, value, 1));
}

//Liest ein 16-Bit Direktregister
uint8_t BQ76905_readDirect16(uint8_t reg, uint16_t *value)
{
    uint8_t data[2];

    if (value == NULL)
    {
        return BQ76905_ERR_PARAM;
    }

    uint8_t result = BQ_twiStatus(TWI_readBlock(BQ76905_ADDR, reg, data, 2));
    if (result != BQ76905_OK)
    {
        return result;
    }

    *value = (uint16_t)data[0] | ((uint16_t)data[1] << 8);
    return BQ76905_OK;
}

//Schreibt ein 8-Bit Direktregister
uint8_t BQ76905_writeDirect8(uint8_t reg, uint8_t value)
{
    return BQ_twiStatus(TWI_write8Bit(BQ76905_ADDR, reg, value));
}

//Schreibt ein 16-Bit Direktregister
uint8_t BQ76905_writeDirect16(uint8_t reg, uint16_t value)
{
    uint8_t data[2] = {(uint8_t)value, (uint8_t)(value >> 8)};
    return BQ_twiStatus(TWI_writeBlock(BQ76905_ADDR, reg, data, 2));
}

//Liest 1 bis 32 Datenbytes aus Data Memory oder einem Subcommand
uint8_t BQ76905_readDataMemory(uint16_t address, uint8_t *data, uint8_t length)
{
    uint8_t addrData[2] = {(uint8_t)address, (uint8_t)(address >> 8)};
    uint8_t echo[2];
    uint8_t buffer[BQ_MAX_BLOCK_LENGTH];
    uint8_t checksum;
    uint8_t sum = (uint8_t)(addrData[0] + addrData[1]);
    uint8_t result;
    uint8_t readLength;

    if (data == NULL || length == 0 || length > BQ_MAX_BLOCK_LENGTH)
    {
        return BQ76905_ERR_PARAM;
    }

    //RAM-Register liefern die Checksumme fuer den ganzen 32-Byte-Puffer
    //Subcommands werden weiterhin mit ihrer eigentlichen Datenlaenge gelesen
    readLength = (address >= 0x9000U) ? BQ_MAX_BLOCK_LENGTH : length;

    //Subcommand oder RAM-Adresse an den BQ senden
    result = BQ_subcommand(address);
    if (result != BQ76905_OK)
    {
        return result;
    }

    //Adresse zuruecklesen, damit keine alten Daten verarbeitet werden
    result = BQ_twiStatus(TWI_readBlock(BQ76905_ADDR, BQ_REG_SUBCOMMAND, echo, 2));
    if (result != BQ76905_OK)
    {
        return result;
    }
    if (echo[0] != addrData[0] || echo[1] != addrData[1])
    {
        return BQ76905_ERR_VERIFY;
    }

    //Datenpuffer auslesen
    result = BQ_twiStatus(TWI_readBlock(BQ76905_ADDR, BQ_REG_DATA_BUFFER, buffer, readLength));
    if (result != BQ76905_OK)
    {
        return result;
    }

    //Checksumme des BQ lesen
    result = BQ76905_readDirect8(BQ_REG_CHECKSUM, &checksum);
    if (result != BQ76905_OK)
    {
        return result;
    }

    //Checksumme ueber die tatsaechlich verwendete Pufferlaenge berechnen
    for (uint8_t i = 0; i < readLength; i++)
    {
        sum = (uint8_t)(sum + buffer[i]);
    }

    if ((uint8_t)(~sum) != checksum)
    {
        return BQ76905_ERR_CHECKSUM;
    }

    //Nur die vom Aufrufer angeforderten Bytes zurueckgeben
    for (uint8_t i = 0; i < length; i++)
    {
        data[i] = buffer[i];
    }

    return BQ76905_OK;
}

//Schreibt 1 bis 32 Datenbytes in RAM und prüft den geschriebenen Wert
uint8_t BQ76905_writeDataMemory(uint16_t address, const uint8_t *data, uint8_t length)
{
    uint8_t result;
    uint8_t readback[BQ_MAX_BLOCK_LENGTH];
    uint8_t checksum = (uint8_t)((uint8_t)address + (uint8_t)(address >> 8));
    uint8_t checkData[2];
    uint16_t batteryStatus;

    if (data == NULL || length == 0 || length > BQ_MAX_BLOCK_LENGTH)
    {
        return BQ76905_ERR_PARAM;
    }
    if (address < 0x9000)
    {
        return BQ76905_ERR_PARAM;
    }

    //Daten-RAM darf nur in CONFIG_UPDATE geschrieben werden
    result = BQ76905_readBatteryStatus(&batteryStatus);
    if (result != BQ76905_OK)
    {
        return result;
    }
    if (!(batteryStatus & BQ_STATUS_CFGUPDATE) ||
    (batteryStatus & (BQ_STATUS_CHG | BQ_STATUS_DSG)))
    {
        return BQ76905_ERR_STATE;
    }

    //Adresse senden
    result = BQ_subcommand(address);
    if (result != BQ76905_OK)
    {
        return result;
    }

    //Daten in den 32-Byte-Puffer schreiben
    result = BQ_twiStatus(TWI_writeBlock(BQ76905_ADDR, BQ_REG_DATA_BUFFER, data, length));
    if (result != BQ76905_OK)
    {
        return result;
    }

    //Checksumme = invertierte Summe aus Adresse und Datenbytes
    for (uint8_t i = 0; i < length; i++)
    {
        checksum = (uint8_t)(checksum + data[i]);
    }

    checkData[0] = (uint8_t)(~checksum);
    checkData[1] = (uint8_t)(length + 4); //Adresse(2), Checksumme(1), Länge(1)

    //Checksumme und Länge schreiben (Länge muss zuletzt kommen)
    result = BQ_twiStatus(TWI_writeBlock(BQ76905_ADDR, BQ_REG_CHECKSUM, checkData, 2));
    if (result != BQ76905_OK)
    {
        return result;
    }

    //Geschriebene Daten aus RAM erneut auslesen
    result = BQ76905_readDataMemory(address, readback, length);
    if (result != BQ76905_OK)
    {
        return result;
    }

    for (uint8_t i = 0; i < length; i++)
    {
        if (readback[i] != data[i])
        {
            return BQ76905_ERR_VERIFY;
        }
    }

    return BQ76905_OK;
}

//REGOUT nur dann umstellen, wenn es nicht bereits auf 5 V steht.
//Das vermeidet unnoetige Schreibzugriffe auf 0x69 bei laufendem BMS.
//Das TS_ON-Bit (Bit 4) bleibt bei einer Umstellung unveraendert.
uint8_t BQ76905_setREGOUT5V(void)
{
    uint8_t value;
    uint8_t result;

    //Zuerst die tatsaechlich aktive Einstellung lesen.
    result = BQ76905_readDirect8(BQ_REG_REGOUT_CONTROL, &value);
    if (result != BQ76905_OK)
    {
        return result;
    }

    //REG_EN (Bit 3) und REGOUTV (Bits 2..0): 0x0F = 5 V, EIN.
    if ((value & 0x0FU) == 0x0FU)
    {
        return BQ76905_OK; //Keine Schreiboperation erforderlich.
    }

    //Nur wenn noetig schreiben; TS_ON-Bit bewusst beibehalten.
    result = BQ76905_writeDirect8(BQ_REG_REGOUT_CONTROL,
    (uint8_t)((value & 0x10U) | 0x0FU));
    if (result != BQ76905_OK)
    {
        return result;
    }

    //Die wirksame Einstellung anschliessend ueberpruefen.
    result = BQ76905_readDirect8(BQ_REG_REGOUT_CONTROL, &value);
    if (result != BQ76905_OK)
    {
        return result;
    }
    return ((value & 0x0FU) == 0x0FU) ? BQ76905_OK : BQ76905_ERR_VERIFY;
}

//Liest die Gerätenummer; BQ76905 meldet 0x7605
uint8_t BQ76905_readDeviceNumber(uint16_t *deviceNumber)
{
    uint8_t data[2];

    if (deviceNumber == NULL)
    {
        return BQ76905_ERR_PARAM;
    }

    uint8_t result = BQ76905_readDataMemory(BQ_CMD_DEVICE_NUMBER, data, 2);
    if (result != BQ76905_OK)
    {
        return result;
    }

    *deviceNumber = (uint16_t)data[0] | ((uint16_t)data[1] << 8);
    return BQ76905_OK;
}

//Initialisiert Schutzkonfiguration und 5V-Regler (FETs bleiben AUS)
uint8_t BQ76905_init(void)
{
    uint16_t deviceNumber;
    uint16_t batteryStatus;
    uint8_t result;
    uint8_t inConfig = 0;

    BQ_ready = 0;

    //REGOUT vor weiteren I2C-Aufrufen auf 5 V anfordern.
    //Die Hauptanwendung startet deshalb zuerst mit langsamem CPU-Takt.
    result = BQ76905_setREGOUT5V();
    if (result != BQ76905_OK) return result;

    //Pruefen ob tatsaechlich der richtige IC antwortet.
    result = BQ76905_readDeviceNumber(&deviceNumber);
    if (result != BQ76905_OK) return result;
    if (deviceNumber != 0x7605U) return BQ76905_ERR_DEVICE;

    result = BQ76905_readBatteryStatus(&batteryStatus);
    if (result != BQ76905_OK) return result;
    if (batteryStatus & BQ_STATUS_CFGUPDATE) return BQ76905_ERR_STATE;

    //Beim ATtiny-Neustart kann der BQ schon korrekt konfiguriert sein
    if (!(batteryStatus & BQ_STATUS_POR))
    {
        result = BQ_checkConfig();
        if (result == BQ76905_OK)
        {
            //RAM-Pruefung ist NICHT gleich dem aktiven REGOUT-Steuerregister.
            result = BQ76905_setREGOUT5V();
            if (result != BQ76905_OK) return result;
            BQ_ready = 1;
            return BQ76905_OK;
        }
    }

    //Keine RAM-Änderung bei eingeschalteten MOSFETs
    if (batteryStatus & (BQ_STATUS_FET_ENABLE | BQ_STATUS_CHG | BQ_STATUS_DSG))
    {
        return BQ76905_ERR_STATE;
    }

    //CONFIG_UPDATE aktivieren; Schutzüberwachung ist darin deaktiviert!
    result = BQ_subcommand(BQ_CMD_SET_CFGUPDATE);
    if (result != BQ76905_OK) return result;
    inConfig = 1;

    result = BQ_waitConfigMode(1);
    if (result != BQ76905_OK) goto error;

    //5V auch nach einem späteren CONFIG_UPDATE beibehalten
    result = BQ_writeConfig8(BQ_RAM_REGOUT_CONFIG, 0x0F);
    if (result != BQ76905_OK) goto error;

    //TS ist auf GND: als ADC-Eingang, Pullup deaktiviert
    result = BQ_writeConfig16(BQ_RAM_DA_CONFIG, 0x0100);
    if (result != BQ76905_OK) goto error;

    //Zwei reale Zellen: Cell 1 (VC1-VC0) und Cell 5 (VC5-VC4A)
    result = BQ_writeConfig8(BQ_RAM_VCELL_MODE, 0x02);
    if (result != BQ76905_OK) goto error;

    //FET Test-Modus bis zur manuellen Freigabe; Serien-FETs, HOST OFF erlaubt
    result = BQ_writeConfig8(BQ_RAM_FET_OPTIONS, 0x58);
    if (result != BQ76905_OK) goto error;

    //COV, CUV, SCD, OCD1, OCD2, OCC und REGOUT-Prüfung aktivieren
    result = BQ_writeConfig8(BQ_RAM_ENABLED_PROT_A, 0xFD);
    if (result != BQ76905_OK) goto error;

    //Nur internen Übertemperaturschutz aktivieren; kein NTC vorhanden
    result = BQ_writeConfig8(BQ_RAM_ENABLED_PROT_B, 0x02);
    if (result != BQ76905_OK) goto error;

    //Zellspannungsgrenzen (little endian, in mV)
    result = BQ_writeConfig16(BQ_RAM_CUV_THRESHOLD, BQ76905_CUV_MV);
    if (result != BQ76905_OK) goto error;
    result = BQ_writeConfig16(BQ_RAM_COV_THRESHOLD, BQ76905_COV_MV);
    if (result != BQ76905_OK) goto error;

    //Lade- und Entlade-Überstrom: je 2mV pro Schritt
    result = BQ_writeConfig8(BQ_RAM_OCC_THRESHOLD, BQ76905_OCC_2MV);
    if (result != BQ76905_OK) goto error;
    result = BQ_writeConfig8(BQ_RAM_OCC_DELAY, 0x50); //ca. 59ms
    if (result != BQ76905_OK) goto error;
    result = BQ_writeConfig8(BQ_RAM_OCD1_THRESHOLD, BQ76905_OCD1_2MV);
    if (result != BQ76905_OK) goto error;
    result = BQ_writeConfig8(BQ_RAM_OCD1_DELAY, 0x64); //ca. 108ms
    if (result != BQ76905_OK) goto error;
    result = BQ_writeConfig8(BQ_RAM_OCD2_THRESHOLD, BQ76905_OCD2_2MV);
    if (result != BQ76905_OK) goto error;
    result = BQ_writeConfig8(BQ_RAM_OCD2_DELAY, 0x20); //ca. 11ms
    if (result != BQ76905_OK) goto error;

    //Kurzschlussschutz: 125mV / 10mOhm, Verzögerung ca. 122us
    result = BQ_writeConfig8(BQ_RAM_SCD_THRESHOLD, BQ76905_SCD_SETTING);
    if (result != BQ76905_OK) goto error;
    result = BQ_writeConfig8(BQ_RAM_SCD_DELAY, 0x04);
    if (result != BQ76905_OK) goto error;

    //Interner Übertemperaturschutz des BQ (nicht der Akkuzellen)
    result = BQ_writeConfig8(BQ_RAM_OTINT_THRESHOLD, 90); //90 Grad Celsius
    if (result != BQ76905_OK) goto error;
    result = BQ_writeConfig8(BQ_RAM_OTINT_RECOVERY, 80); //80 Grad Celsius
    if (result != BQ76905_OK) goto error;

    //Offene Zellenleitung im NORMAL-Modus periodisch erkennen
    result = BQ_writeConfig8(BQ_RAM_OPENWIRE_NORMAL, 10);
    if (result != BQ76905_OK) goto error;

    //CONFIG_UPDATE beenden, Schutz wieder aktivieren
    result = BQ_subcommand(BQ_CMD_EXIT_CFGUPDATE);
    if (result != BQ76905_OK) goto error;
    result = BQ_waitConfigMode(0);
    if (result != BQ76905_OK) goto error;
    inConfig = 0;

    //Prüfen, dass autonomer FET-Betrieb noch AUS ist
    result = BQ76905_readBatteryStatus(&batteryStatus);
    if (result != BQ76905_OK) return result;
    if (batteryStatus & (BQ_STATUS_FET_ENABLE | BQ_STATUS_CHG | BQ_STATUS_DSG))
    {
        return BQ76905_ERR_STATE;
    }

    //Abschliessend alle eingestellten Schutzwerte ueberpruefen.
    result = BQ_checkConfig();
    if (result != BQ76905_OK) return result;

    //Erneut nach CONFIG_UPDATE: das aktive REGOUT-Control auf 5 V halten.
    result = BQ76905_setREGOUT5V();
    if (result != BQ76905_OK) return result;

    BQ_ready = 1;
    return BQ76905_OK;

    error:
    //Bei Fehler CONFIG_UPDATE möglichst verlassen; FETs nicht freigeben!
    if (inConfig)
    {
        (void)BQ_subcommand(BQ_CMD_EXIT_CFGUPDATE);
        (void)BQ_waitConfigMode(0);
    }
    BQ_ready = 0;
    return result;
}

//Liest den Batteriestatus
uint8_t BQ76905_readBatteryStatus(uint16_t *status)
{
    return BQ76905_readDirect16(BQ_REG_BATTERY_STATUS, status);
}

//Liest beide Schutzstatus-Register
uint8_t BQ76905_readSafetyStatus(uint8_t *statusA, uint8_t *statusB)
{
    uint8_t result;

    if (statusA == NULL || statusB == NULL)
    {
        return BQ76905_ERR_PARAM;
    }

    result = BQ76905_readDirect8(BQ_REG_SAFETY_STATUS_A, statusA);
    if (result != BQ76905_OK) return result;
    return BQ76905_readDirect8(BQ_REG_SAFETY_STATUS_B, statusB);
}

//Liest das Alarmstatus-Register
uint8_t BQ76905_readAlarmStatus(uint16_t *status)
{
    return BQ76905_readDirect16(BQ_REG_ALARM_STATUS, status);
}

//Löscht nur die übergebenen, gelatchten Alarmbits
uint8_t BQ76905_clearAlarm(uint16_t mask)
{
    return BQ76905_writeDirect16(BQ_REG_ALARM_STATUS, mask);
}

//Schutz-FETs abschalten (HOST_FETOFF_EN muss gesetzt sein)
uint8_t BQ76905_disableFETs(void)
{
    uint16_t status;
    uint8_t result;

    //Bei einem Fehler der Initialisierung trotzdem Ausschalten versuchen
    result = BQ76905_writeDirect8(BQ_REG_FET_CONTROL, 0x0C);
    if (result != BQ76905_OK) return result;

    //Nicht nur den Befehl, sondern auch den FET-Zustand prüfen
    for (uint8_t i = 0; i < 100; i++)
    {
        result = BQ76905_readBatteryStatus(&status);
        if (result != BQ76905_OK) return result;
        if (!(status & (BQ_STATUS_CHG | BQ_STATUS_DSG))) return BQ76905_OK;
    }

    return BQ76905_ERR_VERIFY;
}

//Schutz-FETs nach erfolgreicher Initialisierung bewusst freigeben
uint8_t BQ76905_enableFETs(void)
{
    uint16_t status;
    uint8_t statusA;
    uint8_t statusB;
    int16_t cell1;
    int16_t cell2;
    uint16_t stack_mV;
    uint8_t result;

    if (!BQ_ready)
    {
        return BQ76905_ERR_NOT_READY;
    }

    result = BQ76905_readBatteryStatus(&status);
    if (result != BQ76905_OK) return result;

    //Nach RESET oder während CONFIG_UPDATE niemals freigeben
    if (status & (BQ_STATUS_POR | BQ_STATUS_CFGUPDATE | BQ_STATUS_SAFETY_FAULT))
    {
        return BQ76905_ERR_STATE;
    }

    result = BQ76905_readSafetyStatus(&statusA, &statusB);
    if (result != BQ76905_OK) return result;
    if (statusA != 0 || statusB != 0)
    {
        return BQ76905_ERR_PROTECTION;
    }

    //Beide Zellspannungen prüfen
    result = BQ76905_readCellVoltage(1, &cell1);
    if (result != BQ76905_OK) return result;
    result = BQ76905_readCellVoltage(2, &cell2);
    if (result != BQ76905_OK) return result;
    if (cell1 < (int16_t)BQ76905_CUV_MV || cell1 > (int16_t)BQ76905_COV_MV ||
    cell2 < (int16_t)BQ76905_CUV_MV || cell2 > (int16_t)BQ76905_COV_MV)
    {
        return BQ76905_ERR_PROTECTION;
    }

    //Stapelspannung mit Summe der beiden Zellen vergleichen
    result = BQ76905_readStackVoltage(&stack_mV);
    if (result != BQ76905_OK) return result;

    int32_t difference = (int32_t)stack_mV - (int32_t)cell1 - (int32_t)cell2;
    if (difference < -250 || difference > 250)
    {
        return BQ76905_ERR_PROTECTION;
    }

    //Eventuell zuvor gesetzte Host-Ausschaltbefehle löschen
    result = BQ76905_writeDirect8(BQ_REG_FET_CONTROL, 0x00);
    if (result != BQ76905_OK) return result;

    //FET_ENABLE ist ein Toggle: NUR senden, falls FET_EN = 0
    if (!(status & BQ_STATUS_FET_ENABLE))
    {
        result = BQ_subcommand(BQ_CMD_FET_ENABLE);
        if (result != BQ76905_OK) return result;
    }

    //Prüfen, ob der autonome FET-Modus wirklich aktiv ist
    result = BQ76905_readBatteryStatus(&status);
    if (result != BQ76905_OK) return result;
    return (status & BQ_STATUS_FET_ENABLE) ? BQ76905_OK : BQ76905_ERR_VERIFY;
}

//Liest die Zellspannung: cell=1 oder 2 (intern 1 oder 5)
uint8_t BQ76905_readCellVoltage(uint8_t cell, int16_t *voltage_mV)
{
    uint8_t reg;

    if (cell == 1)
    {
        reg = BQ_REG_CELL1_VOLTAGE;
    }
    else if (cell == 2)
    {
        reg = BQ_REG_CELL5_VOLTAGE;
    }
    else
    {
        return BQ76905_ERR_PARAM;
    }

    return BQ_readSigned16(reg, voltage_mV);
}

//Liest die gesamte Batteriespannung in mV
uint8_t BQ76905_readStackVoltage(uint16_t *voltage_mV)
{
    return BQ76905_readDirect16(BQ_REG_STACK_VOLTAGE, voltage_mV);
}

//Liest den unkalibrierten 24-Bit-Strommesswert (sign-extended 32 Bit)
uint8_t BQ76905_readCurrentRaw(int32_t *rawCurrent)
{
    uint8_t data[4];
    uint8_t result;
    int32_t value;

    if (rawCurrent == NULL)
    {
        return BQ76905_ERR_PARAM;
    }

    result = BQ_twiStatus(TWI_readBlock(BQ76905_ADDR, BQ_REG_RAW_CURRENT, data, 4));
    if (result != BQ76905_OK) return result;

    value = (int32_t)data[0] |
    ((int32_t)data[1] << 8) |
    ((int32_t)data[2] << 16);

    //Vorzeichen der 24-Bit-Zahl erweitern
    if (data[2] & 0x80)
    {
        if (data[3] != 0xFF) return BQ76905_ERR_VERIFY;
        value -= 16777216L;
    }
    else if (data[3] != 0x00)
    {
        return BQ76905_ERR_VERIFY;
    }

    *rawCurrent = value;
    return BQ76905_OK;
}

//Schätzt den Strom für 10mOhm in mA anhand von 29.25nV pro Roh-Count
//Achtung: Nominalwert, keine Strom-Kalibrierung für Schutzentscheidungen!
uint8_t BQ76905_readCurrentApprox(int16_t *current_mA)
{
    int32_t raw;
    uint8_t result;

    if (current_mA == NULL)
    {
        return BQ76905_ERR_PARAM;
    }

    result = BQ76905_readCurrentRaw(&raw);
    if (result != BQ76905_OK) return result;

    //mA = raw * 1.227V * 1000 / (5 * 2^23 * 10mOhm)
    int64_t mA = ((int64_t)raw * 122700LL) / 41943040LL;
    if (mA < INT16_MIN || mA > INT16_MAX) return BQ76905_ERR_PARAM;
    *current_mA = (int16_t)mA;
    return BQ76905_OK;
}

//Liest die interne Temperatur des ICs, nicht die Akkutemperatur
uint8_t BQ76905_readTemperature(int16_t *temperature_C)
{
    return BQ_readSigned16(BQ_REG_INT_TEMPERATURE, temperature_C);
}

//Liest alle wichtigen Messwerte und Statusregister
uint8_t BQ76905_readAll(BQ76905_Data *data)
{
    uint8_t result;

    if (data == NULL)
    {
        return BQ76905_ERR_PARAM;
    }

    result = BQ76905_readCellVoltage(1, &data->cell1_mV);
    if (result != BQ76905_OK) return result;
    result = BQ76905_readCellVoltage(2, &data->cell2_mV);
    if (result != BQ76905_OK) return result;
    result = BQ76905_readStackVoltage(&data->stack_mV);
    if (result != BQ76905_OK) return result;
    result = BQ76905_readCurrentApprox(&data->currentApprox_mA);
    if (result != BQ76905_OK) return result;
    result = BQ76905_readTemperature(&data->temperature_C);
    if (result != BQ76905_OK) return result;
    result = BQ76905_readBatteryStatus(&data->batteryStatus);
    if (result != BQ76905_OK) return result;
    return BQ76905_readSafetyStatus(&data->safetyStatusA, &data->safetyStatusB);
}

//Schaltet das Balancing aus; automatisches Balancing ist nicht enthalten
uint8_t BQ76905_stopBalancing(void)
{
    uint8_t data = 0;
    uint8_t check;
    uint8_t result = BQ_subcommand(BQ_CMD_CB_ACTIVE_CELLS);
    if (result != BQ76905_OK) return result;

    //Datenbyte in den Subcommand-Puffer schreiben
    result = BQ_twiStatus(TWI_writeBlock(BQ76905_ADDR, BQ_REG_DATA_BUFFER, &data, 1));
    if (result != BQ76905_OK) return result;

    uint8_t checksumLength[2] = {(uint8_t)(~(uint8_t)(0x83 + data)), 5};
    result = BQ_twiStatus(TWI_writeBlock(BQ76905_ADDR, BQ_REG_CHECKSUM, checksumLength, 2));
    if (result != BQ76905_OK) return result;

    result = BQ76905_readDataMemory(BQ_CMD_CB_ACTIVE_CELLS, &check, 1);
    if (result != BQ76905_OK) return result;
    return (check == 0) ? BQ76905_OK : BQ76905_ERR_VERIFY;
}

//Liefert den letzten Fehlercode unseres TWI-Treibers zurück
uint8_t BQ76905_getLastTWIError(void)
{
    return BQ_lastTWIError;
}

//Direktes Register 0x69: den wirksamen REGOUT-Steuerwert pruefen.
uint8_t BQ76905_readREGOUTControl(uint8_t *value)
{
    return BQ76905_readDirect8(BQ_REG_REGOUT_CONTROL, value);
}
