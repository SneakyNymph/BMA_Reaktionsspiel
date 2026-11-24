/*
 * BQ76905_Balance.c
 * Host-Controlled Cell Balancing BQ76905 (0x0083), 2S:
 *   VC1-VC0: 0x02; VC5-VC4A: 0x20.
 * Schreibt keine Schutzwerte, FETs oder REGOUT-Einstellungen.
 */
#include <stdint.h>
#include "include/hal/TWI.h"
#include "include/driver/BQ76905.h"
#include "include/driver/BQ76905_Balance.h"

#define SUBCMD_ADDR 0x3EU
#define BUFFER_ADDR 0x40U
#define CHECK_ADDR  0x60U

uint8_t BQ_Balance_set(uint8_t mask)
{
    const uint8_t command[2] = {0x83U,0x00U};
    uint8_t verification;
    uint8_t checksumLength[2];
    uint16_t status;

    if (mask != BQ_BALANCE_OFF && mask != BQ_BALANCE_CELL1 &&
        mask != BQ_BALANCE_CELL2) return BQ76905_ERR_PARAM;

    /* Fuer AUS bestehende V4-Funktion nutzen statt zweite Umsetzung. */
    if (mask == BQ_BALANCE_OFF) return BQ76905_stopBalancing();

    if (BQ76905_readBatteryStatus(&status) != BQ76905_OK)
        return BQ76905_ERR_TWI;
    if (status & (0x1000U | 0x0080U | 0x0020U))
        return BQ76905_ERR_PROTECTION;

    if (TWI_writeBlock(BQ76905_ADDR, SUBCMD_ADDR, command, 2U) != TWI_OK)
        return BQ76905_ERR_TWI;
    if (TWI_writeBlock(BQ76905_ADDR, BUFFER_ADDR, &mask, 1U) != TWI_OK)
        return BQ76905_ERR_TWI;

    /* Checksumme: ~(0x83 + 0x00 + mask), Length = 2+1+2 = 5. */
    checksumLength[0] = (uint8_t)(~(uint8_t)(0x83U + mask));
    checksumLength[1] = 5U;
    if (TWI_writeBlock(BQ76905_ADDR, CHECK_ADDR, checksumLength, 2U) != TWI_OK)
        return BQ76905_ERR_TWI;

    if (BQ76905_readDataMemory(0x0083U, &verification, 1U) != BQ76905_OK)
        return BQ76905_ERR_VERIFY;
    return (verification == mask) ? BQ76905_OK : BQ76905_ERR_VERIFY;
}

uint8_t BQ_Balance_stop(void)
{
    return BQ76905_stopBalancing();
}
