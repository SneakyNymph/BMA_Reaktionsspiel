/*
 * BatteryService.c
 * V4-Initialisierung wird nicht neu erfunden; nur in Funktionen getrennt.
 * Autonomer Schutz: BQ76905. Host-Software ist zusaetzliche Ueberwachung.
 * Keine automatische Wiederfreigabe nach Fehlern.
 */
#include <stdint.h>
#include "include/service/BatteryService.h"
#include "include/service/BMS_Profile.h"
#include "include/driver/BQ76905_Balance.h"

/* Experimenteller Balancing-Code ist kompiliert, aber erst nach einer
 * EXPLIZITEN Laufzeitfreigabe durch main.c aktiv.
 * Keine Temperaturmessung direkt an LiPo-Zellen vorhanden: NUR
 * fuer kurze, beaufsichtigte Versuche, NICHT Serienbetrieb! */
#ifndef BMS_BALANCING_EXPERIMENTAL_ENABLE
#define BMS_BALANCING_EXPERIMENTAL_ENABLE 1U
#endif
#if BMS_BALANCING_EXPERIMENTAL_ENABLE > 1U
#error BMS_BALANCING_EXPERIMENTAL_ENABLE_muss_0_oder_1_sein
#endif

#define ST_SAFETY    0x1000U
#define ST_FET_EN    0x0100U
#define ST_POR       0x0080U
#define ST_CFG       0x0020U
#define ST_CHG       0x0008U
#define ST_DSG       0x0004U

/* Konservative optionale Balancing-Freigabe nach HW-Validierung. */
#define BAL_MIN_CELL_MV      4000
#define BAL_MAX_CELL_MV      4180
#define BAL_START_DIFF_MV    30
#define BAL_STOP_DIFF_MV     15
#define BAL_MAX_ABS_MA       30
#define BAL_MAX_DIE_C       55
#define BAL_ON_TICKS         10U /* ca. 2 s, Hardwarelimit max. 20 s */
#define BAL_COOLDOWN_TICKS  150U /* mindestens ca. 30 s Pause */

static BMS_Snapshot bms;
static uint8_t allowed;
static uint8_t balancePhase; /* 0=idle, 1=on, 2=cooldown */
static uint16_t balanceTicks;
static uint8_t balanceCheckTick;

static void balanceReset(void)
{
    bms.balancingCell = 0U;
    balancePhase = 0U;
    balanceTicks = 0U;
}

/* Als Sicherheitsreaktion versuchen. Bei TWI-Ausfall nicht garantiert! */
static void softwareFault(BMS_Error reason, uint8_t driverStatus)
{
#if BMS_BALANCING_EXPERIMENTAL_ENABLE
    (void)BQ_Balance_stop();
#endif
    (void)BQ76905_disableFETs();
    balanceReset();
    allowed = 0U;
    bms.error = reason;
    bms.driverError = driverStatus;
    bms.state = BMS_FAULT;
}

/* Autonomer Schutzfehler: CHG/DSG nicht hostseitig beide erzwingen,
 * damit z. B. CUV-Laderecovery nicht unnoetig blockiert wird. */
static void deviceProtected(BMS_Error reason)
{
#if BMS_BALANCING_EXPERIMENTAL_ENABLE
    (void)BQ_Balance_stop();
#endif
    balanceReset();
    allowed = 0U;
    bms.error = reason;
    bms.state = BMS_PROTECTED;
}

static uint8_t measurementsSafe(const BQ76905_Data *d)
{
    int32_t delta = (int32_t)d->stack_mV -
                    (int32_t)d->cell1_mV - (int32_t)d->cell2_mV;
    if (d->cell1_mV < 3000 || d->cell1_mV > 4250 ||
        d->cell2_mV < 3000 || d->cell2_mV > 4250) return 0U;
    if (delta < -250 || delta > 250) return 0U;
    if (d->temperature_C < -20 || d->temperature_C > 80) return 0U;
    return 1U;
}

uint8_t BMS_Service_start(uint8_t enableFETs)
{
    uint16_t status;
    BMS_ProfileResult pr;
    uint8_t rc;

    /* NICHT aus einem laufenden Zustand neu initialisieren. */
    if (bms.state != BMS_OFF) return 0U;
    bms.error = BMS_E_NONE;
    bms.driverError = BQ76905_OK;
    bms.profileIndex = 0U;
    allowed = 0U;
    balanceCheckTick = 0U;
    balanceReset();

    /* Funktion aus der real getesteten V4; inklusive read-before-write REGOUT. */
    rc = BQ76905_init();
    if (rc != BQ76905_OK) {
        softwareFault(BMS_E_INIT, rc);
        return 0U;
    }
    rc = BQ76905_disableFETs();
    if (rc != BQ76905_OK) {
        softwareFault(BMS_E_FET_OFF, rc);
        return 0U;
    }
    rc = BQ76905_readBatteryStatus(&status);
    if (rc != BQ76905_OK ||
        (status & (ST_CHG | ST_DSG | ST_CFG)) != 0U) {
        softwareFault(BMS_E_FET_OFF, rc);
        return 0U;
    }

    pr = BMS_Profile_restoreRecovery();
    if (pr != BMS_PROFILE_OK) {
        softwareFault(BMS_E_RECOVERY, (uint8_t)pr);
        return 0U;
    }
    pr = BMS_Profile_verify();
    if (pr != BMS_PROFILE_OK) {
        bms.profileIndex = BMS_Profile_lastCheckIndex();
        softwareFault(pr == BMS_PROFILE_REGOUT ? BMS_E_REGOUT : BMS_E_PROFILE,
                      (uint8_t)pr);
        return 0U;
    }

    rc = BQ76905_readAll(&bms.battery);
    if (rc != BQ76905_OK) {
        softwareFault(BMS_E_READ, rc);
        return 0U;
    }
    if (!measurementsSafe(&bms.battery) ||
        (bms.battery.batteryStatus & (ST_SAFETY | ST_POR | ST_CFG)) != 0U ||
        bms.battery.safetyStatusA || bms.battery.safetyStatusB) {
        /* Beim Start bleiben FETs bereits aus. */
        bms.state = BMS_PROTECTED;
        bms.error = BMS_E_PLAUSIBILITY;
        return 0U;
    }

    if (!enableFETs) {
        bms.state = BMS_READY;
        return 1U;
    }

    rc = BQ76905_enableFETs();
    if (rc != BQ76905_OK) {
        softwareFault(BMS_E_FET_ON, rc);
        return 0U;
    }
    rc = BQ76905_readBatteryStatus(&status);
    if (rc != BQ76905_OK ||
        (status & (ST_FET_EN | ST_CHG | ST_DSG)) !=
                   (ST_FET_EN | ST_CHG | ST_DSG)) {
        softwareFault(BMS_E_FET_ON, rc != BQ76905_OK ? rc : BQ76905_ERR_VERIFY);
        return 0U;
    }
    bms.state = BMS_RUNNING;
    return 1U;
}

#if BMS_BALANCING_EXPERIMENTAL_ENABLE
static uint8_t balancingSafe(void)
{
    const BQ76905_Data *d = &bms.battery;
    int32_t current = d->currentApprox_mA;
    if (!allowed || bms.state != BMS_RUNNING) return 0U;
    if (d->cell1_mV < BAL_MIN_CELL_MV || d->cell2_mV < BAL_MIN_CELL_MV ||
        d->cell1_mV > BAL_MAX_CELL_MV || d->cell2_mV > BAL_MAX_CELL_MV)
        return 0U;
    if (d->temperature_C < 0 || d->temperature_C > BAL_MAX_DIE_C)
        return 0U;
    if (current < 0) current = -current;
    return current <= BAL_MAX_ABS_MA;
}

static void balanceTick(void)
{
    int32_t delta = (int32_t)bms.battery.cell1_mV - (int32_t)bms.battery.cell2_mV;
    uint8_t rc;
    if (delta < 0) delta = -delta;

    if (balancePhase == 1U) {
        if (!balancingSafe() || delta <= BAL_STOP_DIFF_MV ||
            ++balanceTicks >= BAL_ON_TICKS) {
            rc = BQ_Balance_stop();
            if (rc != BQ76905_OK) {
                softwareFault(BMS_E_BALANCING, rc);
                return;
            }
            bms.balancingCell = 0U;
            balancePhase = 2U;
            balanceTicks = 0U;
        }
        return;
    }
    if (balancePhase == 2U) {
        if (++balanceTicks >= BAL_COOLDOWN_TICKS) balanceReset();
        return;
    }
    if (!balancingSafe() || delta < BAL_START_DIFF_MV) return;

    /* Physische 2S-Anschluesse: Cell1=Bit1, Cell5=Bit5! */
    rc = BQ_Balance_set(bms.battery.cell1_mV > bms.battery.cell2_mV ?
                        BQ_BALANCE_CELL1 : BQ_BALANCE_CELL2);
    if (rc != BQ76905_OK) {
        softwareFault(BMS_E_BALANCING, rc);
        return;
    }
    bms.balancingCell = (bms.battery.cell1_mV > bms.battery.cell2_mV) ? 1U : 2U;
    balancePhase = 1U;
    balanceTicks = 0U;
}
#endif

void BMS_Service_tick200ms(void)
{
    uint8_t rc;
    uint8_t regout;
    if (bms.state != BMS_RUNNING) return;

    rc = BQ76905_readAll(&bms.battery);
    if (rc != BQ76905_OK) {
        softwareFault(BMS_E_COMMUNICATION, rc);
        return;
    }
    if (bms.battery.safetyStatusA || bms.battery.safetyStatusB ||
        (bms.battery.batteryStatus & ST_SAFETY)) {
        deviceProtected(BMS_E_PROTECTION);
        return;
    }
    if (bms.battery.batteryStatus & (ST_POR | ST_CFG)) {
        softwareFault(BMS_E_PROFILE, BQ76905_ERR_STATE);
        return;
    }
    if (!measurementsSafe(&bms.battery)) {
        deviceProtected(BMS_E_PLAUSIBILITY);
        return;
    }
    if ((bms.battery.batteryStatus & (ST_FET_EN | ST_CHG | ST_DSG)) !=
        (ST_FET_EN | ST_CHG | ST_DSG)) {
        deviceProtected(BMS_E_PROTECTION);
        return;
    }

    /* Wie in V4: aktives REGOUT nur LESEN und nicht bei jedem Tick. */
    if (++balanceCheckTick >= 5U) {
        balanceCheckTick = 0U;
        rc = BQ76905_readDirect8(0x69U, &regout);
        if (rc != BQ76905_OK || (regout & 0x0FU) != 0x0FU) {
            softwareFault(BMS_E_REGOUT,
                          rc != BQ76905_OK ? rc : BQ76905_ERR_VERIFY);
            return;
        }
    }
#if BMS_BALANCING_EXPERIMENTAL_ENABLE
    balanceTick();
#endif
}

void BMS_Service_setBalancingPermission(uint8_t permission)
{
#if BMS_BALANCING_EXPERIMENTAL_ENABLE
    /* Ruecknahme der Freigabe soll einen bereits aktiven Puls sofort stoppen.
     * Bei I2C-Fehler: verriegeln und FET-Abschaltung versuchen. */
    if (permission == 0U) {
        allowed = 0U;
        if (balancePhase == 1U) {
            uint8_t rc = BQ_Balance_stop();
            if (rc != BQ76905_OK) {
                softwareFault(BMS_E_BALANCING, rc);
                return;
            }
        }
        balanceReset();
        return;
    }
    if (bms.state == BMS_RUNNING && bms.error == BMS_E_NONE)
        allowed = 1U;
#else
    (void)permission;
    allowed = 0U;
#endif
}

uint8_t BMS_Service_stop(void)
{
    uint8_t rc;
    allowed = 0U;
#if BMS_BALANCING_EXPERIMENTAL_ENABLE
    rc = BQ_Balance_stop();
    if (rc != BQ76905_OK) {
        softwareFault(BMS_E_BALANCING, rc);
        return 0U;
    }
#endif
    balanceReset();
    rc = BQ76905_disableFETs();
    if (rc != BQ76905_OK) {
        softwareFault(BMS_E_FET_OFF, rc);
        return 0U;
    }
    {
        uint16_t status;
        rc = BQ76905_readBatteryStatus(&status);
        if (rc != BQ76905_OK || (status & (ST_CHG | ST_DSG))) {
            softwareFault(BMS_E_FET_OFF,
                rc != BQ76905_OK ? rc : BQ76905_ERR_VERIFY);
            return 0U;
        }
    }
    bms.error = BMS_E_NONE;
    bms.state = BMS_FINISHED;
    return 1U;
}

BMS_Snapshot BMS_Service_getSnapshot(void)
{
    return bms;
}
