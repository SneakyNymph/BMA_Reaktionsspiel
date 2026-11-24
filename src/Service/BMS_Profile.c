/*
 * BMS_Profile.c
 * Exakt auf V4 getestete Sollwerte; keine FET-Freigabe, kein Balancing.
 * REGOUT 0x69 wird NUR gelesen, nicht bei jeder Pruefung beschrieben.
 */
#ifndef F_CPU
#define F_CPU 20000000UL
#endif
#include <stdint.h>
#include <util/delay.h>
#include "include/driver/BQ76905.h"
#include "include/service/BMS_Profile.h"

#define ST_FET_EN       0x0100U
#define ST_CFGUPDATE   0x0020U
#define ST_CHG         0x0008U
#define ST_DSG         0x0004U
#define RECOVERY_ADDR  0x903FU
#define RECOVERY_VALUE 5U

typedef struct { uint16_t address; uint16_t expected; uint8_t length; } RegisterCheck;
static uint8_t lastIndex;

/* Unveraenderte Werte aus der am Board erfolgreichen V4-main.c. */
static const RegisterCheck checks[] = {
    {0x9015U,0x000FU,1U},{0x9019U,0x0100U,2U},
    {0x901BU,0x0002U,1U},{0x901EU,0x0058U,1U},
    {0x9024U,0x00FDU,1U},{0x9025U,0x0002U,1U},
    {0x9026U,0x00FFU,1U},{0x9027U,0x00EFU,1U},
    {0x9028U,0x0006U,1U},{0x902EU,BQ76905_CUV_MV,2U},
    {0x9032U,BQ76905_COV_MV,2U},
    {0x9036U,BQ76905_OCC_2MV,1U},{0x9037U,0x0050U,1U},
    {0x9038U,BQ76905_OCD1_2MV,1U},{0x9039U,0x0064U,1U},
    {0x903AU,BQ76905_OCD2_2MV,1U},{0x903BU,0x0020U,1U},
    {0x903CU,BQ76905_SCD_SETTING,1U},{0x903DU,0x0004U,1U},
    {0x904CU,90U,1U},{0x904EU,80U,1U},{0x902BU,10U,1U},
    {RECOVERY_ADDR,RECOVERY_VALUE,1U}
};

uint8_t BMS_Profile_lastCheckIndex(void) { return lastIndex; }

static uint8_t waitConfig(uint8_t enabled)
{
    uint16_t st;
    for (uint8_t i=0U; i<100U; ++i) {
        if (BQ76905_readBatteryStatus(&st) != BQ76905_OK) return 0U;
        if (((st & ST_CFGUPDATE) != 0U) == (enabled != 0U)) return 1U;
        _delay_ms(5);
    }
    return 0U;
}

static uint8_t setConfig(uint8_t enabled)
{
    if (BQ76905_writeDirect16(0x3EU, enabled ? 0x0090U : 0x0092U)
        != BQ76905_OK) return 0U;
    return waitConfig(enabled);
}

BMS_ProfileResult BMS_Profile_restoreRecovery(void)
{
    uint8_t value;
    uint16_t st;
    uint8_t writeOk;

    if (BQ76905_readDataMemory(RECOVERY_ADDR, &value, 1U) != BQ76905_OK)
        return BMS_PROFILE_IO_ERROR;
    if (value == RECOVERY_VALUE) return BMS_PROFILE_OK;

    if (BQ76905_readBatteryStatus(&st) != BQ76905_OK)
        return BMS_PROFILE_IO_ERROR;
    if ((st & (ST_FET_EN | ST_CHG | ST_DSG | ST_CFGUPDATE)) != 0U)
        return BMS_PROFILE_STATE;

    if (!setConfig(1U)) {
        (void)setConfig(0U);
        return BMS_PROFILE_IO_ERROR;
    }
    writeOk = (uint8_t)(BQ76905_writeDataMemory(
        RECOVERY_ADDR, (const uint8_t[]){RECOVERY_VALUE}, 1U) == BQ76905_OK);
    /* CONFIG_UPDATE selbst bei Schreibfehler immer verlassen versuchen. */
    if (!setConfig(0U)) return BMS_PROFILE_IO_ERROR;
    if (!writeOk) return BMS_PROFILE_IO_ERROR;
    if (BQ76905_readDataMemory(RECOVERY_ADDR, &value, 1U) != BQ76905_OK)
        return BMS_PROFILE_IO_ERROR;
    return value == RECOVERY_VALUE ? BMS_PROFILE_OK : BMS_PROFILE_MISMATCH;
}

BMS_ProfileResult BMS_Profile_verify(void)
{
    uint8_t data[2];
    uint8_t control;
    uint16_t actual;
    lastIndex = 0U;

    for (uint8_t i=0U; i<(uint8_t)(sizeof(checks)/sizeof(checks[0])); ++i) {
        lastIndex = (uint8_t)(i+1U);
        if (BQ76905_readDataMemory(checks[i].address, data,
                                   checks[i].length) != BQ76905_OK)
            return BMS_PROFILE_IO_ERROR;
        actual = data[0];
        if (checks[i].length == 2U) actual |= (uint16_t)data[1] << 8;
        if (actual != checks[i].expected) return BMS_PROFILE_MISMATCH;
    }

    lastIndex = 24U;
    if (BQ76905_readDirect8(0x69U, &control) != BQ76905_OK)
        return BMS_PROFILE_IO_ERROR;
    if ((control & 0x0FU) != 0x0FU) return BMS_PROFILE_REGOUT;
    lastIndex = 0U;
    return BMS_PROFILE_OK;
}
