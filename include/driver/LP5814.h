/*********************************************************************************\
*
* Dateiname: LP5814.h
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
* Bietet Funktionen zur Ansteuerung des LP5814 LED Controller
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 08.11.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/


#ifndef LP5814_H_
#define LP5814_H_

// Rückgabewerte
#define LP5814_OK               0x00
#define LP5814_ERR_TWI          0x01
#define LP5814_ERR_PARAM        0x02
#define LP5814_ERR_BUSY         0x03

// Repeat Times
#define LP5814_REP_0            0
#define LP5814_REP_1            1
#define LP5814_REP_2            2
#define LP5814_REP_INFINITE     3

// Flag zurücksetzten
#define LP5814_CLEAR_POR  0x01
#define LP5814_CLEAR_TSD  0x02

// Modues ob der IC über PWM Manuel angesteuret wird oder im Automatischen Betrieb ist
typedef enum
{
    LP5814_MODE_MANUAL = 0,
    LP5814_MODE_AUTO
} LP5814_Mode_t;

// Enum für die möglichen Zeitwerte
typedef enum
{
    LP5814_TIME_0_ms = 0,
    LP5814_TIME_50_ms,
    LP5814_TIME_100_ms,
    LP5814_TIME_150_ms,
    LP5814_TIME_200_ms,
    LP5814_TIME_250_ms,
    LP5814_TIME_300_ms,
    LP5814_TIME_350_ms,
    LP5814_TIME_400_ms,
    LP5814_TIME_450_ms,
    LP5814_TIME_500_ms,
    LP5814_TIME_1000_ms,
    LP5814_TIME_2000_ms,
    LP5814_TIME_4000_ms,
    LP5814_TIME_6000_ms,
    LP5814_TIME_8000_ms
} LP5814_Time_t;

// Struct für die Konfiguration eines Channels
typedef struct
{
    uint8_t enabled;
    uint8_t dotCurrent;
    uint8_t pwm;
    LP5814_Mode_t mode;
    uint8_t fadeEnabled;
    uint8_t exponential;
    uint8_t engine;
} LP5814_ChannelConfig_t;

// Struct für die Konfiguration des gesamten Chips
typedef struct
{
    uint8_t maxCurrent_51mA;
    LP5814_Time_t fadeTime;

    LP5814_ChannelConfig_t channel[4];

} LP5814_Config_t;

// Struct für die erstellung eines Patterns
typedef struct
{
    uint8_t pwm[5];

    uint8_t slopeTime[4];

    LP5814_Time_t pauseStart;
    LP5814_Time_t pauseEnd;

    uint8_t repeat;

} LP5814_PatternConfig_t;

// Struct für die erstellung einer Engine Order
typedef struct
{
    uint8_t enabled;
    uint8_t pattern;

} LP5814_EngineOrder_t;

// Struct für die Kondifuration einer Engine
typedef struct
{
    LP5814_EngineOrder_t order[4];

    uint8_t repeat;

} LP5814_EngineConfig_t;

// Status Struct
typedef struct
{
    uint8_t por;
    uint8_t tsd;
    uint8_t engineBusy;
    uint8_t outputBusy[4];

} LP5814_Status_t;

///// FUNKTIONEN /////
uint8_t LP5814_init(LP5814_Config_t *config);
uint8_t LP5814_writePWM(LP5814_Config_t *config);
uint8_t LP5814_isBusy(uint8_t *busy);
uint8_t LP5814_setPattern(uint8_t pattern, const LP5814_PatternConfig_t *config);
uint8_t LP5814_setEngine(uint8_t engine, const LP5814_EngineConfig_t *config);
uint8_t LP5814_startAnimation(void);
uint8_t LP5814_stopAnimation(void);
uint8_t LP5814_pauseAnimation(void);
uint8_t LP5814_continueAnimation(void);
uint8_t LP5814_getStatus(LP5814_Status_t *status);
uint8_t LP5814_clearFlags(uint8_t flags);
uint8_t LP5814_wakeUp(void);
uint8_t LP5814_shutdown(void);



#endif /* LP5814_H_ */