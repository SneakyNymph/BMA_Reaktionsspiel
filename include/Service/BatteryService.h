/*
 * BatteryService.h - BMS-Applikationszustand auf Basis der erfolgreich
 * getesteten V4, ohne ADC-/VddMonitor-Abhaengigkeiten.
 */
#ifndef BATTERY_SERVICE_H_
#define BATTERY_SERVICE_H_
#include <stdint.h>
#include "include/driver/BQ76905.h"

typedef enum {
    BMS_OFF = 0,
    BMS_READY,
    BMS_RUNNING,
    BMS_PROTECTED,
    BMS_FAULT,
    BMS_FINISHED
} BMS_State;

typedef enum {
    BMS_E_NONE = 0,
    BMS_E_INIT = 1,
    BMS_E_FET_OFF = 2,
    BMS_E_RECOVERY = 3,
    BMS_E_PROFILE = 4,
    BMS_E_REGOUT = 5,
    BMS_E_READ = 6,
    BMS_E_PLAUSIBILITY = 7,
    BMS_E_FET_ON = 8,
    BMS_E_COMMUNICATION = 9,
    BMS_E_PROTECTION = 10,
    BMS_E_BALANCING = 11
} BMS_Error;

typedef struct {
    BMS_State state;
    BMS_Error error;
    uint8_t driverError;
    uint8_t profileIndex;
    uint8_t balancingCell;  /* 0=aus, 1=unten, 2=oben */
    BQ76905_Data battery;
} BMS_Snapshot;

/* Nach system_setupMainCLK(), TWI_init(100000), debug_initLEDs(), 500ms.
 * enableFETs=0 entspricht V4 Stufe 0, enableFETs=1 V4 Stufe 1.
 */
uint8_t BMS_Service_start(uint8_t enableFETs);
/* Exakt alle ~200ms im Hauptprogramm aufrufen (nicht in ISR). */
void BMS_Service_tick200ms(void);
/* Aktive Freigabe aus der Anwendung; OHNE Hardwarefreigabe im Source
 * sind Balancing-Befehle trotzdem gesperrt. Default=0. */
void BMS_Service_setBalancingPermission(uint8_t allowed);
/* Manuelle Host-Abschaltung. Kein automatisches Wiederanlaufen. */
uint8_t BMS_Service_stop(void);
BMS_Snapshot BMS_Service_getSnapshot(void);
#endif
