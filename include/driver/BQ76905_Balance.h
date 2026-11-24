/*
 * BQ76905_Balance.h
 */
#ifndef BQ76905_BALANCE_H_
#define BQ76905_BALANCE_H_
#include <stdint.h>
#define BQ_BALANCE_OFF     0x00U
#define BQ_BALANCE_CELL1   0x02U
#define BQ_BALANCE_CELL2   0x20U

/* Nur aus Service bei positiver Freigabe aufrufen. */
uint8_t BQ_Balance_set(uint8_t mask);
uint8_t BQ_Balance_stop(void);
#endif
