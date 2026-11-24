/*
 * BMS_Profile.h
 * V4-Schutzprofil fuer 2S-LiPo, nur die in V4 geprueften Werte.
 */
#ifndef BMS_PROFILE_H_
#define BMS_PROFILE_H_
#include <stdint.h>

typedef enum {
    BMS_PROFILE_OK = 0,
    BMS_PROFILE_IO_ERROR = 1,
    BMS_PROFILE_MISMATCH = 2,
    BMS_PROFILE_STATE = 3,
    BMS_PROFILE_REGOUT = 4
} BMS_ProfileResult;

/* Nur die OCD-Recovery (0x903F) ggf. auf 5s zurueckstellen.
   Muss vor FET-Freigabe aufgerufen werden. */
BMS_ProfileResult BMS_Profile_restoreRecovery(void);
/* 23 bekannte RAM-Werte und aktives REGOUT (0x69) nur LESEN. */
BMS_ProfileResult BMS_Profile_verify(void);
/* 1..23 fuer RAM, 24 fuer aktives REGOUT; 0 wenn kein Fehler. */
uint8_t BMS_Profile_lastCheckIndex(void);
#endif
