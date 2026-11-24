/*********************************************************************************\
*
* Dateiname: BQ25883.h
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny3226 auf Hauptplatine V1
*
*
* Portbelegung:
* =============
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Bietet Funktionen zur Ansteuerung des BQ25883 2S Lipo Lade Controller
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 22.11.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/



#ifndef BQ25883_H_
#define BQ25883_H_

#include <stdint.h>
#include "include/hal/GPIO.h"

///// Rückgabewerte /////
#define BQ25883_OK                          0
#define BQ25883_ERR_TWI                     1
#define BQ25883_ERR_DEVICE                  2
#define BQ25883_ERR_PARAM                   3
#define BQ25883_ERR_PINS_NOT_CONFIGURED     4
#define BQ25883_ERR_VERIFY                  5
#define BQ25883_ERR_ADC_NO_CHANNELS         6
#define BQ25883_ERR_STATE                   7

///// REG12 - Interruptquellen /////
#define BQ25883_IRQ1_ADC_DONE_bm  (1u << 7)
#define BQ25883_IRQ1_IINDPM_bm    (1u << 6)
#define BQ25883_IRQ1_VINDPM_bm    (1u << 5)
#define BQ25883_IRQ1_TREG_bm      (1u << 4)
#define BQ25883_IRQ1_WD_bm        (1u << 3)
#define BQ25883_IRQ1_CHRG_bm      (1u << 0)

///// REG13 - Interruptquellen /////
#define BQ25883_IRQ2_PG_bm        (1u << 7)
#define BQ25883_IRQ2_VBUS_bm      (1u << 4)
#define BQ25883_IRQ2_TS_bm        (1u << 2)
#define BQ25883_IRQ2_ICO_bm       (1u << 1)
#define BQ25883_IRQ2_VSYS_bm      (1u << 0)


///// REG14 - Fault Interruptquellen /////
#define BQ25883_FAULT_IRQ_VBUS_OVP_bm   (1u << 7)
#define BQ25883_FAULT_IRQ_TSHUT_bm      (1u << 6)
#define BQ25883_FAULT_IRQ_BATOVP_bm     (1u << 5)
#define BQ25883_FAULT_IRQ_TMR_bm        (1u << 4)
#define BQ25883_FAULT_IRQ_SYS_SHORT_bm  (1u << 3)
#define BQ25883_FAULT_IRQ_OTG_bm        (1u << 0)


///// ADC-Messkanäle /////
#define BQ25883_ADC_IBUS_bm  (1u << 7)
#define BQ25883_ADC_ICHG_bm  (1u << 6)
#define BQ25883_ADC_VBUS_bm  (1u << 5)
#define BQ25883_ADC_VBAT_bm  (1u << 4)
#define BQ25883_ADC_VSYS_bm  (1u << 3)
#define BQ25883_ADC_TS_bm    (1u << 2)
#define BQ25883_ADC_TDIE_bm  (1u << 0)


///// Konfigurationsblöcke /////

#define BQ25883_CONFIG_BLOCK1_START   0x00
#define BQ25883_CONFIG_BLOCK1_SIZE    10

#define BQ25883_CONFIG_BLOCK2_START   0x12
#define BQ25883_CONFIG_BLOCK2_SIZE    5


///// Watchdog /////

#define BQ25883_REG_CHG_CTRL1         0x05
#define BQ25883_WATCHDOG_bm           0x30
#define BQ25883_WATCHDOG_gp           4


///// ENUM /////

// Charge Timer
typedef enum
{
    BQ25883_CHG_TIMER_5H = 0,
    BQ25883_CHG_TIMER_8H,
    BQ25883_CHG_TIMER_12H,
    BQ25883_CHG_TIMER_20H
} BQ25883_ChargeTimer_t;

// Watchdog
typedef enum
{
    BQ25883_WATCHDOG_DISABLED = 0,
    BQ25883_WATCHDOG_40S,
    BQ25883_WATCHDOG_80S,
    BQ25883_WATCHDOG_160S
} BQ25883_Watchdog_t;

// thermal regulation
typedef enum
{
    BQ25883_TREG_60C = 0,
    BQ25883_TREG_80C,
    BQ25883_TREG_100C,
    BQ25883_TREG_120C
} BQ25883_ThermalRegulation_t;

// Charge Threshold
typedef enum
{
    BQ25883_BATLOWV_5600MV = 0,
    BQ25883_BATLOWV_6000MV
} BQ25883_PrechargeThreshold_t;

// Top Off Timer
typedef enum
{
    BQ25883_TOPOFF_DISABLED = 0,
    BQ25883_TOPOFF_15MIN,
    BQ25883_TOPOFF_30MIN,
    BQ25883_TOPOFF_45MIN
} BQ25883_TopOffTimer_t;

// Anpassung der Ladeschlussspannung anhand JEITA-Profil
typedef enum
{
    BQ25883_JEITA_VOLTAGE_SUSPEND = 0,
    BQ25883_JEITA_VOLTAGE_8000MV,
    BQ25883_JEITA_VOLTAGE_8300MV,
    BQ25883_JEITA_VOLTAGE_UNCHANGED
} BQ25883_JeitaVoltage_t;

// Ladestrombegrenzung bei hoher Temperatur
typedef enum
{
    BQ25883_JEITA_HOT_CURRENT_40 = 0,
    BQ25883_JEITA_HOT_CURRENT_100
} BQ25883_JeitaHotCurrent_t;

// Ladestrombegrenzung bei tiefer Temperatur
typedef enum
{
    BQ25883_JEITA_COLD_CURRENT_SUSPEND = 0,
    BQ25883_JEITA_COLD_CURRENT_20,
    BQ25883_JEITA_COLD_CURRENT_40,
    BQ25883_JEITA_COLD_CURRENT_100
} BQ25883_JeitaColdCurrent_t;

// OTG obere Temperaturlimite
typedef enum
{
    BQ25883_OTG_HOT_60C = 0,
    BQ25883_OTG_HOT_55C,
    BQ25883_OTG_HOT_65C,
    BQ25883_OTG_HOT_DISABLED
} BQ25883_OtgHotThreshold_t;

// OTG untere TEMPERATURLIMITE
typedef enum
{
    BQ25883_OTG_COLD_MINUS10C = 0,
    BQ25883_OTG_COLD_MINUS20C
} BQ25883_OtgColdThreshold_t;

// ADC Betriebsmodus
typedef enum
{
    BQ25883_ADC_CONTINUOUS = 0,
    BQ25883_ADC_ONESHOT
} BQ25883_AdcMode_t;

// ADC Samples
typedef enum
{
    BQ25883_ADC_SAMPLE_0 = 0,
    BQ25883_ADC_SAMPLE_1,
    BQ25883_ADC_SAMPLE_2,
    BQ25883_ADC_SAMPLE_3
} BQ25883_AdcSample_t;

// Ladezustand
typedef enum
{
    BQ25883_CHG_NOT_CHARGING = 0,
    BQ25883_CHG_TRICKLE,
    BQ25883_CHG_PRECHARGE,
    BQ25883_CHG_FAST,
    BQ25883_CHG_TAPER,
    BQ25883_CHG_TOPOFF,
    BQ25883_CHG_DONE,
    BQ25883_CHG_RESERVED
} BQ25883_ChargeStatus_t;


// USB Eingangsstatus
typedef enum
{
    BQ25883_VBUS_NO_INPUT = 0,
    BQ25883_VBUS_USB_SDP,
    BQ25883_VBUS_USB_CDP,
    BQ25883_VBUS_ADAPTER,
    BQ25883_VBUS_POOR_SOURCE,
    BQ25883_VBUS_UNKNOWN_ADAPTER,
    BQ25883_VBUS_NON_STANDARD,
    BQ25883_VBUS_OTG
} BQ25883_VbusStatus_t;


// Input Current Optimizer Status
typedef enum
{
    BQ25883_ICO_DISABLED = 0,
    BQ25883_ICO_RUNNING,
    BQ25883_ICO_COMPLETED,
    BQ25883_ICO_RESERVED
} BQ25883_IcoStatus_t;


// Temperaturstatus des Akkus
typedef enum
{
    BQ25883_NTC_NORMAL = 0,
    BQ25883_NTC_RESERVED_1,
    BQ25883_NTC_WARM,
    BQ25883_NTC_COOL,
    BQ25883_NTC_RESERVED_4,
    BQ25883_NTC_COLD,
    BQ25883_NTC_HOT,
    BQ25883_NTC_RESERVED_7
} BQ25883_NtcStatus_t;


///// STRUCTS //////

// KONFIGURATION //

typedef struct
{
    ///// REG00 - Battery Voltage Limit /////
    uint16_t chargeVoltage_mV;

    ///// REG01 - Charge Current Limit /////
    uint16_t chargeCurrent_mA;
    uint8_t inputHiZEnabled;
    uint8_t ilimPinEnabled;

    ///// REG02 - Input Voltage Limit /////
    uint16_t inputVoltageLimit_mV;
    uint8_t resetVindpmOnAdapter;
    uint8_t pfmOutOfAudioEnabled;

    ///// REG03 - Input Current Limit /////
    uint16_t inputCurrentLimit_mA;
    uint8_t icoEnabled;
    
    ///// REG04 - Precharge and Termination /////
    uint16_t prechargeCurrent_mA;
    uint16_t terminationCurrent_mA;
    
    
    ///// REG05 - Charger Control 1 /////
    uint8_t terminationEnabled;
    uint8_t statPinEnabled;
    BQ25883_Watchdog_t watchdog;
    uint8_t safetyTimerEnabled;
    BQ25883_ChargeTimer_t chargeTimer;
    uint8_t safetyTimer2xEnabled;
    
    
    ///// REG06 - Charger Control 2 /////
    uint8_t autoInputDetectionEnabled;
    BQ25883_ThermalRegulation_t thermalRegulation;
    BQ25883_PrechargeThreshold_t prechargeThreshold;
    uint16_t rechargeThreshold_mV;

    ///// REG07 - Charger Control 3 /////
    uint8_t pfmEnabled;
    BQ25883_TopOffTimer_t topOffTimer;
    uint16_t minimumSystemVoltage_mV;
    
    ///// REG08 - Charger Control 4 /////
    BQ25883_OtgHotThreshold_t otgHotThreshold;
    BQ25883_OtgColdThreshold_t otgColdThreshold;

    BQ25883_JeitaVoltage_t jeitaHotVoltage;
    BQ25883_JeitaHotCurrent_t jeitaHotCurrent;
    BQ25883_JeitaColdCurrent_t jeitaColdCurrent;

    ///// REG09 - OTG Control /////
    uint16_t otgVoltage_mV;
    uint16_t otgCurrentLimit_mA;
    
    
    ///// REG12 - Charger Interrupt Mask 1 /////
    uint8_t interrupt1Enabled;

    ///// REG13 - Charger Interrupt Mask 2 /////
    uint8_t interrupt2Enabled;

    ///// REG14 - Fault Interrupt Mask /////
    uint8_t faultInterruptEnabled;

    ///// REG15 - ADC Control /////
    BQ25883_AdcMode_t adcMode;
    BQ25883_AdcSample_t adcSample;

    ///// REG16 - ADC Function Disable /////
    uint8_t adcChannelsEnabled;


} BQ25883_Config_t;

// Struct für die Konfiguration von den Datenleitungen
typedef struct BQ25883_PinConfig_t
{
    PORT_t *cePort;
    uint8_t cePin;

    PORT_t *intPort;
    uint8_t intPin;

    PORT_t *pgPort;
    uint8_t pgPin;

} BQ25883_PinConfig_t;

// Struct für alle Informationen
typedef struct
{
    ///// Ladezustand /////
    BQ25883_ChargeStatus_t chargeStatus;

    ///// Eingang und Versorgung /////
    BQ25883_VbusStatus_t vbusStatus;
    BQ25883_IcoStatus_t icoStatus;

    uint8_t powerGood;
    uint8_t inputCurrentLimitActive;
    uint8_t inputVoltageLimitActive;
    uint8_t minimumSystemVoltageActive;

    ///// Temperatur /////
    BQ25883_NtcStatus_t ntcStatus;
    uint8_t thermalRegulationActive;

    ///// Watchdog /////
    uint8_t watchdogExpired;

} BQ25883_Status_t;

// Struct für alle Fehler
typedef struct
{
    uint8_t inputOvervoltage;
    uint8_t thermalShutdown;
    uint8_t batteryOvervoltage;
    uint8_t safetyTimerExpired;

} BQ25883_FaultStatus_t;

// Struct für alle Interrupts
typedef struct
{
    // Lade- und Regelungsereignisse
    uint8_t chargeChanged;
    uint8_t inputCurrentLimitEntered;
    uint8_t inputVoltageLimitEntered;
    uint8_t thermalRegulationEntered;
    uint8_t watchdogExpired;

    // Versorgung und Temperatur
    uint8_t powerGoodChanged;
    uint8_t vbusChanged;
    uint8_t ntcChanged;
    uint8_t icoChanged;
    uint8_t minimumSystemVoltageChanged;

    // Fehler
    uint8_t inputOvervoltage;
    uint8_t thermalShutdown;
    uint8_t batteryOvervoltage;
    uint8_t safetyTimerExpired;
    uint8_t otgFault;

} BQ25883_InterruptFlags_t;


// struct für ADC Messwerte
typedef struct
{
    int16_t inputCurrent_mA;
    uint16_t chargeCurrent_mA;

    int16_t inputVoltage_mV;
    int16_t batteryVoltage_mV;
    int16_t systemVoltage_mV;

    int16_t tsPercent_x100;
    int16_t chipTemperature_cC;

    uint8_t enabledChannels;

} BQ25883_AdcValues_t;



///// FUNKTIONEN /////

// Überprüft ob BQ25883 erreichbar ist
uint8_t BQ25883_init(void);

// Konfiguriert an welchem Pin die Datenbleitungen angeschlossen sind.
uint8_t BQ25883_configPins(const BQ25883_PinConfig_t *config);

// Steuert den CE pin an
uint8_t BQ25883_setCE(uint8_t enabled);

// Konfiguriert den BQ25883 ob das Laden erlaubt ist.
uint8_t BQ25883_setEN_CHG(uint8_t enabled);

// Steuert die Ladefreigabe des BQ25883, via Hardware und TWI
uint8_t BQ25883_setChargeEnabled(uint8_t enabled);

// ändert die Ladeschlussspannung
uint8_t BQ25883_setChargeVoltage(uint16_t voltage_mV);

// Liesst die eingestellte Ladeschlussspannung des BQ25883 über TWI aus.
uint8_t BQ25883_getChargeVoltage(uint16_t *voltage_mV);

// Übernimmt die Konfiguration
uint8_t BQ25883_config(const BQ25883_Config_t *config);

// setzt die aus dem Datenblatt entnommenen reset werdte in eine config hinein
uint8_t BQ25883_defaultConfig(BQ25883_Config_t *config);

// Gibt den aktuellen Ladestatus zurück
uint8_t BQ25883_getChargeStatus(BQ25883_ChargeStatus_t *status);

// Liest die aktuellen Fehler des Ladereglers
uint8_t BQ25883_getFaultStatus(BQ25883_FaultStatus_t *status);

// Gibt alle Status Informationen zurück
uint8_t BQ25883_getStatus(BQ25883_Status_t *status);

// Liest die Interruptflags aus (werden dabei gelöscht)
uint8_t BQ25883_getInterruptFlags(BQ25883_InterruptFlags_t *flags);

///// ADC Funktionen /////
uint8_t BQ25883_startADC(void);
uint8_t BQ25883_stopADC(void);
uint8_t BQ25883_isADCRunning(uint8_t *running);
uint8_t BQ25883_setADCChannels(uint8_t channelsEnabled);
uint8_t BQ25883_getADCValues(BQ25883_AdcValues_t *values);

///// Laufzeitfunktionen /////
uint8_t BQ25883_feedWatchdog(void);

uint8_t BQ25883_forceICO(void);
uint8_t BQ25883_forceInputDetection(void);
uint8_t BQ25883_setICOEnabled(uint8_t enabled);
uint8_t BQ25883_getICOCurrentLimit(uint16_t *current_mA);

uint8_t BQ25883_setHiZEnabled(uint8_t enabled);
uint8_t BQ25883_setBatteryDischargeEnabled(uint8_t enabled);

uint8_t BQ25883_setChargeCurrent(uint16_t current_mA);
uint8_t BQ25883_setInputCurrentLimit(uint16_t current_mA);
uint8_t BQ25883_setInputVoltageLimit(uint16_t voltage_mV);

uint8_t BQ25883_setOTGLimits(uint16_t voltage_mV, uint16_t current_mA);
uint8_t BQ25883_setOTGEnabled(uint8_t enabled);

uint8_t BQ25883_resetRegisters(void);

#endif /* BQ25883_H_ */