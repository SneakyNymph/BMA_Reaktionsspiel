/*
 * BQ76905.h
 *
 * Projekt  : Tisch Reaktionsspiel BMA
 * Hardware : ATtiny1626 auf Hauptplatine V1
 *
 * Copyright: Jan Meyer
 */

#ifndef BQ76905_H_
#define BQ76905_H_

#include <stdint.h>

//7-Bit TWI-Adresse des BQ76905
#define BQ76905_ADDR               0x08

//Rückgabewerte
#define BQ76905_OK                 0
#define BQ76905_ERR_TWI            1
#define BQ76905_ERR_PARAM          2
#define BQ76905_ERR_DEVICE         3
#define BQ76905_ERR_CHECKSUM       4
#define BQ76905_ERR_VERIFY         5
#define BQ76905_ERR_STATE          6
#define BQ76905_ERR_PROTECTION     7
#define BQ76905_ERR_NOT_READY      8

//Schutzwerte für 2S-LiPo mit 10 mOhm Messwiderstand
#define BQ76905_CUV_MV             3000U  //Zell-Unterspannung
#define BQ76905_COV_MV             4250U  //Zell-Überspannung
#define BQ76905_OCC_2MV            17U    //Laden: 34mV / 10mOhm = 3.4A
#define BQ76905_OCD1_2MV           35U    //Entladen: 70mV / 10mOhm = 7A
#define BQ76905_OCD2_2MV           45U    //Entladen: 90mV / 10mOhm = 9A
#define BQ76905_SCD_SETTING        6U     //Kurzschluss: 125mV / 10mOhm = 12.5A

//Bits im Safety Status A
#define BQ76905_FAULT_COV          0x80
#define BQ76905_FAULT_CUV          0x40
#define BQ76905_FAULT_SCD          0x20
#define BQ76905_FAULT_OCD1         0x10
#define BQ76905_FAULT_OCD2         0x08
#define BQ76905_FAULT_OCC          0x04

//Gesammelte Betriebsdaten
typedef struct
{
    int16_t cell1_mV;
    int16_t cell2_mV;
    uint16_t stack_mV;
    int16_t currentApprox_mA;
    int16_t temperature_C;
    uint16_t batteryStatus;
    uint8_t safetyStatusA;
    uint8_t safetyStatusB;
} BQ76905_Data;

///// Initialisierung und Steuerung /////
uint8_t BQ76905_init(void);
uint8_t BQ76905_enableFETs(void);
uint8_t BQ76905_disableFETs(void);
uint8_t BQ76905_setREGOUT5V(void);
uint8_t BQ76905_readREGOUTControl(uint8_t *value);
uint8_t BQ76905_getLastTWIError(void);

///// Messwerte /////
uint8_t BQ76905_readCellVoltage(uint8_t cell, int16_t *voltage_mV);
uint8_t BQ76905_readStackVoltage(uint16_t *voltage_mV);
uint8_t BQ76905_readCurrentRaw(int32_t *rawCurrent);
uint8_t BQ76905_readCurrentApprox(int16_t *current_mA);
uint8_t BQ76905_readTemperature(int16_t *temperature_C);
uint8_t BQ76905_readAll(BQ76905_Data *data);

///// Status /////
uint8_t BQ76905_readBatteryStatus(uint16_t *status);
uint8_t BQ76905_readSafetyStatus(uint8_t *statusA, uint8_t *statusB);
uint8_t BQ76905_readAlarmStatus(uint16_t *status);
uint8_t BQ76905_clearAlarm(uint16_t mask);
uint8_t BQ76905_readDeviceNumber(uint16_t *deviceNumber);

///// Datenregister /////
//Direkte Register auch ausserhalb CONFIG_UPDATE lesbar
uint8_t BQ76905_readDirect8(uint8_t reg, uint8_t *value);
uint8_t BQ76905_readDirect16(uint8_t reg, uint16_t *value);
uint8_t BQ76905_writeDirect8(uint8_t reg, uint8_t value);
uint8_t BQ76905_writeDirect16(uint8_t reg, uint16_t value);

//RAM schreiben nur im CONFIG_UPDATE Modus und bei ausgeschalteten FETs
uint8_t BQ76905_readDataMemory(uint16_t address, uint8_t *data, uint8_t length);
uint8_t BQ76905_writeDataMemory(uint16_t address, const uint8_t *data, uint8_t length);

//Cell Balancing absichtlich nicht automatisch eingeschaltet
uint8_t BQ76905_stopBalancing(void);

#endif /* BQ76905_H_ */
