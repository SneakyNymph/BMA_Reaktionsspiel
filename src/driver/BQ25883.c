
#include <stdint.h>
#include <stddef.h>

#include "include/hal/TWI.h"
#include "include/driver/BQ25883.h"
#include "include/driver/BQ25883_Registers.h"

///// VARIABLEN /////
static BQ25883_PinConfig_t bq25883_pins;
static uint8_t bq25883_pinsConfigured = 0;

///// PRIVATE FUNKTIONEN /////

static uint8_t BQ25883_validateConfig(const BQ25883_Config_t *config)
{
    ///// NULL-Pointer überprüfen /////
    if (config == NULL)
    {
        return BQ25883_ERR_PARAM;
    }

    ///// Spannungen und Ströme überprüfen /////

    // REG00 - Ladeschlussspannung
    if (config->chargeVoltage_mV < 6800 ||
    config->chargeVoltage_mV > 9200 ||
    config->chargeVoltage_mV % 10 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG01 - Ladestrom
    if (config->chargeCurrent_mA < 100 ||
    config->chargeCurrent_mA > 2200 ||
    config->chargeCurrent_mA % 50 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG02 - Eingangsspannungsgrenze
    if (config->inputVoltageLimit_mV < 3900 ||
    config->inputVoltageLimit_mV > 5500 ||
    config->inputVoltageLimit_mV % 100 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG03 - Eingangsstromgrenze
    if (config->inputCurrentLimit_mA < 500 ||
    config->inputCurrentLimit_mA > 3300 ||
    config->inputCurrentLimit_mA % 100 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG04 - Vorladestrom und Ladeendstrom
    if (config->prechargeCurrent_mA < 50 ||
    config->prechargeCurrent_mA > 800 ||
    config->prechargeCurrent_mA % 50 != 0 ||
    config->terminationCurrent_mA < 50 ||
    config->terminationCurrent_mA > 800 ||
    config->terminationCurrent_mA % 50 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG06 - Wiederladeschwelle
    if (config->rechargeThreshold_mV < 100 ||
    config->rechargeThreshold_mV > 400 ||
    config->rechargeThreshold_mV % 100 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG07 - Minimale Systemspannung
    if (config->minimumSystemVoltage_mV < 6000 ||
    config->minimumSystemVoltage_mV > 7500 ||
    config->minimumSystemVoltage_mV % 100 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG09 - OTG-Ausgangsspannung und Stromgrenze
    if (config->otgVoltage_mV < 4500 ||
    config->otgVoltage_mV > 5500 ||
    config->otgVoltage_mV % 100 != 0 ||
    config->otgCurrentLimit_mA < 500 ||
    config->otgCurrentLimit_mA > 2000 ||
    config->otgCurrentLimit_mA % 100 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    ///// Boolean-Parameter überprüfen /////

    if (config->inputHiZEnabled > 1 ||
    config->ilimPinEnabled > 1 ||
    config->resetVindpmOnAdapter > 1 ||
    config->pfmOutOfAudioEnabled > 1 ||
    config->icoEnabled > 1 ||
    config->terminationEnabled > 1 ||
    config->statPinEnabled > 1 ||
    config->safetyTimerEnabled > 1 ||
    config->safetyTimer2xEnabled > 1 ||
    config->autoInputDetectionEnabled > 1 ||
    config->pfmEnabled > 1)
    {
        return BQ25883_ERR_PARAM;
    }

    ///// Enum-Parameter überprüfen /////

    if ((unsigned int)config->chargeTimer > BQ25883_CHG_TIMER_20H ||
    (unsigned int)config->watchdog > BQ25883_WATCHDOG_160S ||
    (unsigned int)config->thermalRegulation > BQ25883_TREG_120C ||
    (unsigned int)config->prechargeThreshold > BQ25883_BATLOWV_6000MV ||
    (unsigned int)config->topOffTimer > BQ25883_TOPOFF_45MIN ||
    (unsigned int)config->jeitaHotVoltage > BQ25883_JEITA_VOLTAGE_UNCHANGED ||
    (unsigned int)config->jeitaHotCurrent > BQ25883_JEITA_HOT_CURRENT_100 ||
    (unsigned int)config->jeitaColdCurrent > BQ25883_JEITA_COLD_CURRENT_100 ||
    (unsigned int)config->otgHotThreshold > BQ25883_OTG_HOT_DISABLED ||
    (unsigned int)config->otgColdThreshold > BQ25883_OTG_COLD_MINUS20C ||
    (unsigned int)config->adcMode > BQ25883_ADC_ONESHOT ||
    (unsigned int)config->adcSample > BQ25883_ADC_SAMPLE_3)
    {
        return BQ25883_ERR_PARAM;
    }

    ///// Reservierte Bits überprüfen /////

    // REG12 - Bits 1 und 2 reserviert
    if (config->interrupt1Enabled & 0x06)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG13 - Bits 3, 5 und 6 reserviert
    if (config->interrupt2Enabled & 0x68)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG14 - Bits 1 und 2 reserviert
    if (config->faultInterruptEnabled & 0x06)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG16 - Bit 1 reserviert
    if (config->adcChannelsEnabled & 0x02)
    {
        return BQ25883_ERR_PARAM;
    }

    ///// Alle Parameter gültig /////
    return BQ25883_OK;
}


static void BQ25883_buildRegisters(const BQ25883_Config_t *config, uint8_t *block1, uint8_t *block2)
{
    ///// BLOCK 1: REG00 - REG09 /////

    // REG00 - Ladeschlussspannung
    block1[0] = (uint8_t)
    ((config->chargeVoltage_mV - 6800u) / 10u);

    // REG01 - Ladestrom, HIZ und ILIM
    block1[1] = (uint8_t)(
    (config->inputHiZEnabled << 7) |
    (config->ilimPinEnabled << 6) |
    (config->chargeCurrent_mA / 50u)
    );

    // REG02 - Eingangsspannungsgrenze
    block1[2] = (uint8_t)(
    (config->resetVindpmOnAdapter << 7) |
    ((!config->pfmOutOfAudioEnabled) << 5) |
    ((config->inputVoltageLimit_mV - 3900u) / 100u)
    );

    // REG03 - Eingangsstromgrenze und ICO
    block1[3] = (uint8_t)(
    (config->icoEnabled << 5) |
    ((config->inputCurrentLimit_mA - 500u) / 100u)
    );

    // REG04 - Vorladestrom und Ladeendstrom
    block1[4] = (uint8_t)(
    (((config->prechargeCurrent_mA - 50u) / 50u) << 4) |
    ((config->terminationCurrent_mA - 50u) / 50u)
    );

    // REG05 - Watchdog und Ladetimer
    block1[5] = (uint8_t)(
    (config->terminationEnabled << 7) |
    ((!config->statPinEnabled) << 6) |
    (config->watchdog << 4) |
    (config->safetyTimerEnabled << 3) |
    (config->chargeTimer << 1) |
    config->safetyTimer2xEnabled
    );

    // REG06 - Ladeparameter
    // EN_OTG = 0 und EN_CHG = 0
    block1[6] = (uint8_t)(
    (config->autoInputDetectionEnabled << 6) |
    (config->thermalRegulation << 4) |
    (config->prechargeThreshold << 2) |
    ((config->rechargeThreshold_mV - 100u) / 100u)
    );

    // REG07 - PFM, Top-off und Systemspannung
    // WD_RST = 0
    block1[7] = (uint8_t)(
    ((!config->pfmEnabled) << 7) |
    (config->topOffTimer << 4) |
    ((config->minimumSystemVoltage_mV - 6000u) / 100u)
    );

    // REG08 - JEITA und OTG-Temperaturgrenzen
    block1[8] = (uint8_t)(
    (config->otgHotThreshold << 6) |
    (config->otgColdThreshold << 5) |
    (config->jeitaHotVoltage << 3) |
    (config->jeitaHotCurrent << 2) |
    config->jeitaColdCurrent
    );

    // REG09 - OTG-Strom und Ausgangsspannung
    block1[9] = (uint8_t)(
    (((config->otgCurrentLimit_mA - 500u) / 100u) << 4) |
    ((config->otgVoltage_mV - 4500u) / 100u)
    );


    ///// BLOCK 2: REG12 - REG16 /////

    // REG12 - Interrupt Mask 1
    block2[0] = (uint8_t)(
    (~config->interrupt1Enabled) & 0xF9u
    );

    // REG13 - Interrupt Mask 2
    block2[1] = (uint8_t)(
    (~config->interrupt2Enabled) & 0x97u
    );

    // REG14 - Fault Interrupt Mask
    block2[2] = (uint8_t)(
    (~config->faultInterruptEnabled) & 0xF9u
    );

    // REG15 - ADC-Modus und Sampling
    // ADC_EN = 0
    block2[3] = (uint8_t)(
    (config->adcMode << 6) |
    (config->adcSample << 4)
    );

    // REG16 - ADC-Messkanäle
    block2[4] = (uint8_t)(
    (~config->adcChannelsEnabled) & 0xFDu
    );
}


static int16_t BQ25883_decodeSignedADC(uint8_t msb, uint8_t lsb)
{
    uint16_t raw = ((uint16_t)msb << 8) | lsb;

    // Vorzeichen beachten
    if (raw & 0x8000u)
    {
        return (int16_t)((int32_t)raw - 65536L);
    }

    return (int16_t)raw;
}


static uint8_t BQ25883_updateBits(uint8_t regAddr, uint8_t mask, uint8_t value)
{
    uint8_t regValue;

    if (TWI_readBlock(BQ25883_I2C_ADDR, regAddr, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // Nur die gewuenschten Bits ändern
    regValue = (uint8_t)((regValue & (uint8_t)~mask) | (value & mask));

    // Befehlsbits nicht ausversehen nochmals auslösen
    if (regAddr == BQ25883_REG_INPUT_CURRENT)
    {
        regValue &= (uint8_t)~(BQ25883_FORCE_ICO_bm | BQ25883_FORCE_INDET_bm);
    }

    if (regAddr == BQ25883_REG_CHG_CTRL3)
    {
        regValue &= (uint8_t)~BQ25883_WD_RST_bm;
    }

    if (TWI_write8Bit(BQ25883_I2C_ADDR, regAddr, regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}




///// ÖFFENTLICHE FUNKTIONEN /////

// Prüft ob der BQ25883 erreichbar ist
uint8_t BQ25883_init(void)
{
    uint8_t partInfo = 0;

    // Bausteinidentifikation auslesen
    uint8_t result = TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_PART_INFO, &partInfo, 1);

    // I2C-Kommunikation überprüfen
    if (result != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // Prüfen ob ein BQ25883 antwortet
    if ((partInfo & BQ25883_PN_MASK) != BQ25883_PN_VALUE)
    {
        return BQ25883_ERR_DEVICE;
    }

    return BQ25883_OK;
}

// Konfigurierte den CHIP anhand der ausgewählten pins
uint8_t BQ25883_configPins(const BQ25883_PinConfig_t *config)
{
    // Parameter überprüfen
    if (config == NULL || config->cePort == NULL || config->intPort == NULL || config->pgPort == NULL || config->cePin > 7 || config->intPin > 7 || config->pgPin > 7)
    {
        return BQ25883_ERR_PARAM;
    }

    // Laden sperren indem CE auf HIGH
    GPIO_pinWrite(config->cePort, config->cePin, GPIO_HIGH);
    GPIO_setPinDirection(config->cePort, config->cePin, GPIO_OUTPUT);

    // INT als Eingang konfigurieren
    GPIO_setPinDirection(config->intPort, config->intPin, GPIO_INPUT);

    // PG als Eingang konfigurieren
    GPIO_setPinDirection(config->pgPort, config->pgPin, GPIO_INPUT);

    // Pinbelegung intern speichern
    bq25883_pins = *config;
    bq25883_pinsConfigured = 1;

    return BQ25883_OK;
}

// Steuert den CE pin an
uint8_t BQ25883_setCE(uint8_t enabled)
{
    // Überprüfen ob die pins konfiguriert wurden
    if (!bq25883_pinsConfigured)
    {
        return BQ25883_ERR_PINS_NOT_CONFIGURED;
    }

    // Parameter prüfen
    if (enabled > 1)
    {
        return BQ25883_ERR_PARAM;
    }

    // CE ist aktiv LOW
    GPIO_pinWrite(bq25883_pins.cePort, bq25883_pins.cePin, enabled ? GPIO_LOW : GPIO_HIGH);

    return BQ25883_OK;
}

// Konfiguriert den BQ25883 ob das Laden erlaubt ist.
uint8_t BQ25883_setEN_CHG(uint8_t enabled)
{
    // Parameter überprüfen
    if (enabled > 1)
    {
        return BQ25883_ERR_PARAM;
    }

    uint8_t regValue;

    // Aktuellen Registerwert auslesen
    if (TWI_readBlock(BQ25883_I2C_ADDR,
    BQ25883_REG_CHG_CTRL2,
    &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // EN_CHG setzen oder löschen
    if (enabled)
    {
        regValue |= BQ25883_EN_CHG_bm;
    }
    else
    {
        regValue &= ~BQ25883_EN_CHG_bm;
    }

    // Geänderten Registerwert zurückschreiben
    if (TWI_write8Bit(BQ25883_I2C_ADDR,
    BQ25883_REG_CHG_CTRL2,
    regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}

// Über Hardware und Software das Laden aktivieren / deaktivieren   
uint8_t BQ25883_setChargeEnabled(uint8_t enabled)
{
    // Parameter überprüfen
    if (enabled > 1)
    {
        return BQ25883_ERR_PARAM;
    }

    // GPIO-Konfiguration überprüfen
    if (!bq25883_pinsConfigured)
    {
        return BQ25883_ERR_PINS_NOT_CONFIGURED;
    }

    // Laden zuerst hardwareseitig sperren
    uint8_t result = BQ25883_setCE(0);

    if (result != BQ25883_OK)
    {
        return result;
    }

    // Softwareseitige Ladefreigabe einstellen
    result = BQ25883_setEN_CHG(enabled);

    if (result != BQ25883_OK)
    {
        return result;
    }

    // Bei Aktivierung Laden hardwareseitig freigeben
    if (enabled)
    {
        result = BQ25883_setCE(1);

        if (result != BQ25883_OK)
        {
            return result;
        }
    }

    return BQ25883_OK;
}

// ändert die Ladesschlusspannung des BQ25883
uint8_t BQ25883_setChargeVoltage(uint16_t voltage_mV)
{
    // Spannungsbereich überprüfen
    if (voltage_mV < BQ25883_VREG_MIN_MV || voltage_mV > BQ25883_VREG_MAX_MV)
    {
        return BQ25883_ERR_PARAM;
    }

    // Auflösung von 10mV überprüfen
    if ((voltage_mV - BQ25883_VREG_MIN_MV) % BQ25883_VREG_STEP_MV != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    // Spannung in Registerwert umrechnen laut Datenblatt
    uint8_t regValue = (uint8_t)((voltage_mV - BQ25883_VREG_MIN_MV) / BQ25883_VREG_STEP_MV);

    // Register beschreiben
    if (TWI_write8Bit(BQ25883_I2C_ADDR, BQ25883_REG_CHG_VOLTAGE, regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}

// Liest die eingestellte Ladeschlussspannung des BQ25883 aus
uint8_t BQ25883_getChargeVoltage(uint16_t *voltage_mV)
{
    // Parameter überprüfen
    if (voltage_mV == NULL)
    {
        return BQ25883_ERR_PARAM;
    }

    uint8_t regValue;

    // Spannungsregister auslesen
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_CHG_VOLTAGE, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // Registerwert in mV umrechnen
    *voltage_mV = BQ25883_VREG_MIN_MV + ((uint16_t)regValue * BQ25883_VREG_STEP_MV);

    return BQ25883_OK;
}

// Konfiguriert den BQ25883 anhand der konfigurationsdatei
uint8_t BQ25883_config(const BQ25883_Config_t *config)
{
    uint8_t result;

    ///// Konfiguration validieren /////
    result = BQ25883_validateConfig(config);

    if (result != BQ25883_OK)
    {
        return result;
    }

    ///// GPIO-Konfiguration überprüfen /////
    if (!bq25883_pinsConfigured)
    {
        return BQ25883_ERR_PINS_NOT_CONFIGURED;
    }

    ///// Laden hardwareseitig sperren /////
    result = BQ25883_setCE(0);

    if (result != BQ25883_OK)
    {
        return result;
    }

    ///// Bausteinidentifikation überprüfen /////
    result = BQ25883_init();

    if (result != BQ25883_OK)
    {
        return result;
    }

    ///// Registerblöcke vorbereiten /////
    uint8_t block1[BQ25883_CONFIG_BLOCK1_SIZE];
    uint8_t block2[BQ25883_CONFIG_BLOCK2_SIZE];

    uint8_t readBack[BQ25883_CONFIG_BLOCK1_SIZE];

    BQ25883_buildRegisters(config, block1, block2);

    ///// Block 1: REG00 - REG09 schreiben /////
    if (TWI_writeBlock(BQ25883_I2C_ADDR, BQ25883_CONFIG_BLOCK1_START, block1, BQ25883_CONFIG_BLOCK1_SIZE) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    ///// Block 2: REG12 - REG16 schreiben /////
    if (TWI_writeBlock(BQ25883_I2C_ADDR, BQ25883_CONFIG_BLOCK2_START, block2, BQ25883_CONFIG_BLOCK2_SIZE) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    ///// Block 1 zurücklesen /////
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_CONFIG_BLOCK1_START, readBack, BQ25883_CONFIG_BLOCK1_SIZE) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    ///// Block 1 verifizieren /////
    for (uint8_t i = 0; i < BQ25883_CONFIG_BLOCK1_SIZE; i++)
    {
        if (readBack[i] != block1[i])
        {
            return BQ25883_ERR_VERIFY;
        }
    }

    ///// Block 2 zurücklesen /////
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_CONFIG_BLOCK2_START, readBack, BQ25883_CONFIG_BLOCK2_SIZE) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    ///// Block 2 verifizieren /////
    for (uint8_t i = 0; i < BQ25883_CONFIG_BLOCK2_SIZE; i++)
    {
        uint8_t mask = 0xFF;

        // REG16: Reserviertes Bit 1 ignorieren
        if (i == 4)
        {
            mask = 0xFD;
        }

        if ((readBack[i] & mask) != (block2[i] & mask))
        {
            return BQ25883_ERR_VERIFY;
        }
    }

    ///// Konfiguration erfolgreich /////
    return BQ25883_OK;
}

// setzt eine Konfiguration den im Datenblatt entsprechenden reset werden
uint8_t BQ25883_defaultConfig(BQ25883_Config_t *config)
{
    if (config == NULL)
    {
        return BQ25883_ERR_PARAM;
    }

    ///// REG00 - Battery Voltage Limit /////
    config->chargeVoltage_mV = 8400;

    ///// REG01 - Charge Current Limit /////
    config->chargeCurrent_mA = 1500;
    config->inputHiZEnabled = 0;
    config->ilimPinEnabled = 1;

    ///// REG02 - Input Voltage Limit /////
    config->inputVoltageLimit_mV = 4300;
    config->resetVindpmOnAdapter = 1;
    config->pfmOutOfAudioEnabled = 1;

    ///// REG03 - Input Current Limit /////
    config->inputCurrentLimit_mA = 3000;
    config->icoEnabled = 1;

    ///// REG04 - Precharge and Termination /////
    config->prechargeCurrent_mA = 150;
    config->terminationCurrent_mA = 150;

    ///// REG05 - Charger Control 1 /////
    config->terminationEnabled = 1;
    config->statPinEnabled = 1;
    config->watchdog = BQ25883_WATCHDOG_40S;
    config->safetyTimerEnabled = 1;
    config->chargeTimer = BQ25883_CHG_TIMER_12H;
    config->safetyTimer2xEnabled = 1;

    ///// REG06 - Charger Control 2 /////
    config->autoInputDetectionEnabled = 1;
    config->thermalRegulation = BQ25883_TREG_120C;
    config->prechargeThreshold = BQ25883_BATLOWV_6000MV;
    config->rechargeThreshold_mV = 200;

    ///// REG07 - Charger Control 3 /////
    config->pfmEnabled = 1;
    config->topOffTimer = BQ25883_TOPOFF_DISABLED;
    config->minimumSystemVoltage_mV = 6200;

    ///// REG08 - Charger Control 4 /////
    config->otgHotThreshold = BQ25883_OTG_HOT_60C;
    config->otgColdThreshold = BQ25883_OTG_COLD_MINUS10C;
    config->jeitaHotVoltage = BQ25883_JEITA_VOLTAGE_8000MV;
    config->jeitaHotCurrent = BQ25883_JEITA_HOT_CURRENT_100;
    config->jeitaColdCurrent = BQ25883_JEITA_COLD_CURRENT_20;

    ///// REG09 - OTG Control /////
    config->otgVoltage_mV = 5100;
    config->otgCurrentLimit_mA = 2000;

    ///// REG12 - Charger Interrupt Mask 1 /////
    config->interrupt1Enabled = 0xF9;

    ///// REG13 - Charger Interrupt Mask 2 /////
    config->interrupt2Enabled = 0x97;

    ///// REG14 - Fault Interrupt Mask /////
    config->faultInterruptEnabled = 0xF9;

    ///// REG15 - ADC Control /////
    config->adcMode = BQ25883_ADC_CONTINUOUS;
    config->adcSample = BQ25883_ADC_SAMPLE_3;

    ///// REG16 - ADC Function Disable /////
    config->adcChannelsEnabled = 0xFD;

    return BQ25883_OK;
}

// Gibt den aktuellen Ladestatus zurück
uint8_t BQ25883_getChargeStatus(BQ25883_ChargeStatus_t *status)
{
    uint8_t regValue;

    if (status == NULL)
    {
        return BQ25883_ERR_PARAM;
    }

    // REG0B auslesen
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_CHG_STATUS1, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // CHRG_STAT[2:0] extrahieren
    *status = (BQ25883_ChargeStatus_t)(regValue & BQ25883_CHRG_STAT_bm);

    return BQ25883_OK;
}

// Gibt alle Informationen des BQ25883 zurück
uint8_t BQ25883_getStatus(BQ25883_Status_t *status)
{
    uint8_t reg[BQ25883_STATUS_REG_COUNT];

    ///// Parameter überprüfen /////
    if (status == NULL)
    {
        return BQ25883_ERR_PARAM;
    }

    ///// Alle drei Statusregister auslesen /////
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_STATUS_START, reg, BQ25883_STATUS_REG_COUNT) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    ///// Lade und Regelungsstatus /////

    status->chargeStatus = (BQ25883_ChargeStatus_t)(reg[0] & BQ25883_CHRG_STAT_bm);

    status->inputCurrentLimitActive = (reg[0] & BQ25883_IINDPM_STAT_bm) != 0;

    status->inputVoltageLimitActive = (reg[0] & BQ25883_VINDPM_STAT_bm) != 0;

    status->thermalRegulationActive = (reg[0] & BQ25883_TREG_STAT_bm) != 0;

    status->watchdogExpired = (reg[0] & BQ25883_WD_STAT_bm) != 0;


    ///// Eingangs und Systemstatus /////

    status->powerGood = (reg[1] & BQ25883_PG_STAT_bm) != 0;

    status->vbusStatus = (BQ25883_VbusStatus_t)((reg[1] & BQ25883_VBUS_STAT_bm) >> BQ25883_VBUS_STAT_gp);

    status->icoStatus = (BQ25883_IcoStatus_t)((reg[1] & BQ25883_ICO_STAT_bm) >> BQ25883_ICO_STAT_gp);

    status->minimumSystemVoltageActive = (reg[1] & BQ25883_VSYS_STAT_bm) != 0;


    ///// Akkutemperaturstatus /////

    status->ntcStatus = (BQ25883_NtcStatus_t)(reg[2] & BQ25883_TS_STAT_bm);

    return BQ25883_OK;
}

// Gibt Fehler Informationen des BQ25883 zurück
uint8_t BQ25883_getFaultStatus(BQ25883_FaultStatus_t *status)
{
    uint8_t regValue;

    // Parameter prüfen
    if (status == NULL)
    {
        return BQ25883_ERR_PARAM;
    }

    // Fehlerregister auslesen
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_FAULT_STATUS, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // Fehlerbits auswerten
    status->inputOvervoltage = (regValue & BQ25883_VBUS_OVP_STAT_bm) != 0;
    status->thermalShutdown = (regValue & BQ25883_TSHUT_STAT_bm) != 0;
    status->batteryOvervoltage = (regValue & BQ25883_BATOVP_STAT_bm) != 0;
    status->safetyTimerExpired = (regValue & BQ25883_TMR_STAT_bm) != 0;

    return BQ25883_OK;
}

// Gibt Interrupts des BQ25883 zurück
uint8_t BQ25883_getInterruptFlags(BQ25883_InterruptFlags_t *flags)
{
    uint8_t reg[BQ25883_FLAG_REG_COUNT];

    // Parameter prüfen
    if (flags == NULL)
    {
        return BQ25883_ERR_PARAM;
    }

    // Alle drei Flag-Register auslesen
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_FLAG_START, reg, BQ25883_FLAG_REG_COUNT) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // REG0F - Ladeereignisse
    flags->chargeChanged = (reg[0] & BQ25883_IRQ1_CHRG_bm) != 0;
    flags->inputCurrentLimitEntered = (reg[0] & BQ25883_IRQ1_IINDPM_bm) != 0;
    flags->inputVoltageLimitEntered = (reg[0] & BQ25883_IRQ1_VINDPM_bm) != 0;
    flags->thermalRegulationEntered = (reg[0] & BQ25883_IRQ1_TREG_bm) != 0;
    flags->watchdogExpired = (reg[0] & BQ25883_IRQ1_WD_bm) != 0;

    // REG10 - Versorgung und Temperatur
    flags->powerGoodChanged = (reg[1] & BQ25883_IRQ2_PG_bm) != 0;
    flags->vbusChanged = (reg[1] & BQ25883_IRQ2_VBUS_bm) != 0;
    flags->ntcChanged = (reg[1] & BQ25883_IRQ2_TS_bm) != 0;
    flags->icoChanged = (reg[1] & BQ25883_IRQ2_ICO_bm) != 0;
    flags->minimumSystemVoltageChanged = (reg[1] & BQ25883_IRQ2_VSYS_bm) != 0;

    // REG11 - Fehler
    flags->inputOvervoltage = (reg[2] & BQ25883_FAULT_IRQ_VBUS_OVP_bm) != 0;
    flags->thermalShutdown = (reg[2] & BQ25883_FAULT_IRQ_TSHUT_bm) != 0;
    flags->batteryOvervoltage = (reg[2] & BQ25883_FAULT_IRQ_BATOVP_bm) != 0;
    flags->safetyTimerExpired = (reg[2] & BQ25883_FAULT_IRQ_TMR_bm) != 0;
    flags->otgFault = (reg[2] & BQ25883_FAULT_IRQ_OTG_bm) != 0;

    return BQ25883_OK;
}

// startet den internen ADC
uint8_t BQ25883_startADC(void)
{
    uint8_t regValue;

    // Prüfen ob Messkanäle aktiviert sind
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CHANNELS, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    if ((regValue & BQ25883_ADC_CHANNEL_MASK) == BQ25883_ADC_CHANNEL_MASK)
    {
        return BQ25883_ERR_ADC_NO_CHANNELS;
    }

    // ADC Steuerregister lesen
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CTRL, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // ADC einschalten
    regValue |= BQ25883_ADC_EN_bm;

    if (TWI_write8Bit(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CTRL, regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}

// stoppt den internen ADC
uint8_t BQ25883_stopADC(void)
{
    uint8_t regValue;

    // Steuerregister lesen
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CTRL, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // ADC abschalten
    regValue &= ~BQ25883_ADC_EN_bm;

    if (TWI_write8Bit(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CTRL, regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}

// ADC Betriebszustand auslesen
uint8_t BQ25883_isADCRunning(uint8_t *running)
{
    uint8_t regValue;

    if (running == NULL)
    {
        return BQ25883_ERR_PARAM;
    }

    // ADC Status lesen
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CTRL, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    *running = (regValue & BQ25883_ADC_EN_bm) != 0;

    return BQ25883_OK;
}

// ADC Messkanele einstellen
uint8_t BQ25883_setADCChannels(uint8_t channelsEnabled)
{
    uint8_t regValue;

    // Reservierte Bits prüfen
    if (channelsEnabled & ~BQ25883_ADC_CHANNEL_MASK)
    {
        return BQ25883_ERR_PARAM;
    }

    // Aktivierte Kanäle in Disable-Bits umwandeln
    regValue = (~channelsEnabled) & BQ25883_ADC_CHANNEL_MASK;

    if (TWI_write8Bit(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CHANNELS, regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}

// Alle ADC messwerte auslesen
uint8_t BQ25883_getADCValues(BQ25883_AdcValues_t *values)
{
    uint8_t reg[BQ25883_ADC_RESULTS_SIZE];
    uint8_t channelReg;
    BQ25883_AdcValues_t result;

    ///// Parameter prüfen /////
    if (values == NULL)
    {
        return BQ25883_ERR_PARAM;
    }

    ///// Aktivierte Kanäle lesen /////
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CHANNELS, &channelReg, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    ///// Alle ADC Register lesen /////
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_ADC_RESULTS, reg, BQ25883_ADC_RESULTS_SIZE) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // Aktivierte Messkanäle merken
    result.enabledChannels = (~channelReg) & BQ25883_ADC_CHANNEL_MASK;

    ///// IBUS - Eingangsstrom /////
    result.inputCurrent_mA = BQ25883_decodeSignedADC(reg[0], reg[1]);

    ///// ICHG - Ladestrom /////
    result.chargeCurrent_mA = ((uint16_t)(reg[2] & 0x7Fu) << 8) | reg[3];

    ///// VBUS - Eingangsspannung /////
    result.inputVoltage_mV = BQ25883_decodeSignedADC(reg[4], reg[5]);

    ///// VBAT - Akkuspannung /////
    result.batteryVoltage_mV = BQ25883_decodeSignedADC(reg[6], reg[7]);

    ///// VSYS - Systemspannung /////
    result.systemVoltage_mV = BQ25883_decodeSignedADC(reg[8], reg[9]);

    ///// TS - Prozent von REGN /////
    int16_t tsRaw = BQ25883_decodeSignedADC(reg[10], reg[11]);
    result.tsPercent_x100 = (int16_t)(((int32_t)tsRaw * 10000L) / 1024L);

    ///// TDIE - Chiptemperatur /////
    int16_t tempRaw = BQ25883_decodeSignedADC(reg[12], reg[13]);
    result.chipTemperature_cC = (int16_t)(tempRaw * 50);

    ///// Alles erfolgreich gelesen /////
    *values = result;

    return BQ25883_OK;
}


uint8_t BQ25883_feedWatchdog(void)
{
    uint8_t regValue;

    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_CHG_CTRL3, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // WD_RST setzen, der IC löscht es selber wieder
    regValue |= BQ25883_WD_RST_bm;

    if (TWI_write8Bit(BQ25883_I2C_ADDR, BQ25883_REG_CHG_CTRL3, regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}


uint8_t BQ25883_setICOEnabled(uint8_t enabled)
{
    if (enabled > 1)
    {
        return BQ25883_ERR_PARAM;
    }

    return BQ25883_updateBits(BQ25883_REG_INPUT_CURRENT, BQ25883_EN_ICO_bm, enabled ? BQ25883_EN_ICO_bm : 0);
}


uint8_t BQ25883_forceICO(void)
{
    uint8_t regValue;

    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_INPUT_CURRENT, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // ICO muss vorher aktiviert sein
    if (!(regValue & BQ25883_EN_ICO_bm))
    {
        return BQ25883_ERR_STATE;
    }

    // Nur ICO auslösen, nicht gleichzeitig die USB-Erkennung
    regValue &= (uint8_t)~BQ25883_FORCE_INDET_bm;
    regValue |= BQ25883_FORCE_ICO_bm;

    if (TWI_write8Bit(BQ25883_I2C_ADDR, BQ25883_REG_INPUT_CURRENT, regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}


uint8_t BQ25883_getICOCurrentLimit(uint16_t *current_mA)
{
    uint8_t regValue;

    if (current_mA == NULL)
    {
        return BQ25883_ERR_PARAM;
    }

    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_ICO_LIMIT, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    regValue &= BQ25883_ICO_ILIM_bm;

    // Nur Werte bis 3300mA sind gültig
    if (regValue > 28)
    {
        return BQ25883_ERR_STATE;
    }

    *current_mA = 500u + (uint16_t)regValue * 100u;

    return BQ25883_OK;
}


uint8_t BQ25883_forceInputDetection(void)
{
    uint8_t regValue;

    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_INPUT_CURRENT, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // USB-Erkennung neu starten
    regValue &= (uint8_t)~BQ25883_FORCE_ICO_bm;
    regValue |= BQ25883_FORCE_INDET_bm;

    if (TWI_write8Bit(BQ25883_I2C_ADDR, BQ25883_REG_INPUT_CURRENT, regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}


uint8_t BQ25883_setHiZEnabled(uint8_t enabled)
{
    if (enabled > 1)
    {
        return BQ25883_ERR_PARAM;
    }

    return BQ25883_updateBits(BQ25883_REG_CHG_CURRENT, BQ25883_EN_HIZ_bm, enabled ? BQ25883_EN_HIZ_bm : 0);
}


uint8_t BQ25883_setBatteryDischargeEnabled(uint8_t enabled)
{
    if (enabled > 1)
    {
        return BQ25883_ERR_PARAM;
    }

    return BQ25883_updateBits(BQ25883_REG_INPUT_VOLTAGE, BQ25883_EN_BAT_DISCHG_bm, enabled ? BQ25883_EN_BAT_DISCHG_bm : 0);
}


uint8_t BQ25883_setChargeCurrent(uint16_t current_mA)
{
    if (current_mA < 100 || current_mA > 2200 || current_mA % 50 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    uint8_t regValue = (uint8_t)(current_mA / 50u);

    return BQ25883_updateBits(BQ25883_REG_CHG_CURRENT, BQ25883_ICHG_bm, regValue);
}


uint8_t BQ25883_setInputCurrentLimit(uint16_t current_mA)
{
    if (current_mA < 500 || current_mA > 3300 || current_mA % 100 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    uint8_t regValue = (uint8_t)((current_mA - 500u) / 100u);

    return BQ25883_updateBits(BQ25883_REG_INPUT_CURRENT, BQ25883_IINDPM_bm, regValue);
}


uint8_t BQ25883_setInputVoltageLimit(uint16_t voltage_mV)
{
    if (voltage_mV < 3900 || voltage_mV > 5500 || voltage_mV % 100 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    uint8_t regValue = (uint8_t)((voltage_mV - 3900u) / 100u);

    return BQ25883_updateBits(BQ25883_REG_INPUT_VOLTAGE, BQ25883_VINDPM_bm, regValue);
}


uint8_t BQ25883_setOTGLimits(uint16_t voltage_mV, uint16_t current_mA)
{
    if (voltage_mV < 4500 || voltage_mV > 5500 || voltage_mV % 100 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    if (current_mA < 500 || current_mA > 2000 || current_mA % 100 != 0)
    {
        return BQ25883_ERR_PARAM;
    }

    uint8_t regValue = (uint8_t)((((current_mA - 500u) / 100u) << 4) | ((voltage_mV - 4500u) / 100u));

    if (TWI_write8Bit(BQ25883_I2C_ADDR, BQ25883_REG_OTG_CTRL, regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}


uint8_t BQ25883_setOTGEnabled(uint8_t enabled)
{
    uint8_t regValue;
    uint8_t result;

    if (enabled > 1)
    {
        return BQ25883_ERR_PARAM;
    }

    // OTG ausschalten
    if (!enabled)
    {
        return BQ25883_updateBits(BQ25883_REG_CHG_CTRL2, BQ25883_EN_OTG_bm, 0);
    }

    // Laden zuerst vollständig sperren
    result = BQ25883_setChargeEnabled(0);

    if (result != BQ25883_OK)
    {
        return result;
    }

    // Prüfen ob eine gültige Eingangsversorgung vorhanden ist
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_CHG_STATUS2, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    if (regValue & BQ25883_PG_STAT_bm)
    {
        return BQ25883_ERR_STATE;
    }

    // Es muss mindestens ein ADC Kanal aktiviert sein
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CHANNELS, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    if ((regValue & BQ25883_ADC_CHANNEL_MASK) == BQ25883_ADC_CHANNEL_MASK)
    {
        return BQ25883_ERR_ADC_NO_CHANNELS;
    }

    // ADC einschalten und auf Continuous umstellen
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CTRL, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    regValue &= (uint8_t)~BQ25883_ADC_RATE_bm;
    regValue |= BQ25883_ADC_EN_bm;

    if (TWI_write8Bit(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CTRL, regValue) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    // Prüfen ob der ADC wirklich gestartet ist
    if (TWI_readBlock(BQ25883_I2C_ADDR, BQ25883_REG_ADC_CTRL, &regValue, 1) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    if (!(regValue & BQ25883_ADC_EN_bm))
    {
        return BQ25883_ERR_STATE;
    }

    // OTG einschalten, EN_CHG bleibt 0
    return BQ25883_updateBits(BQ25883_REG_CHG_CTRL2, BQ25883_EN_OTG_bm | BQ25883_EN_CHG_bm, BQ25883_EN_OTG_bm);
}


uint8_t BQ25883_resetRegisters(void)
{
    uint8_t result;

    // Zuerst Laden über CE sperren
    result = BQ25883_setCE(0);

    if (result != BQ25883_OK)
    {
        return result;
    }

    // REG_RST löst einen Register-Reset aus
    if (TWI_write8Bit(BQ25883_I2C_ADDR, BQ25883_REG_PART_INFO, BQ25883_REG_RST_bm) != TWI_OK)
    {
        return BQ25883_ERR_TWI;
    }

    return BQ25883_OK;
}
