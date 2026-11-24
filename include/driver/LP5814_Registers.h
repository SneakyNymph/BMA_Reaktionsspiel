/******************************************************************************
 * @file    LP5814_Registers.h
 * @brief   Register map and #define constants for TI LP5814 LED driver.
 *
 * @details
 *   Complete LP5814 register map (0x00 through 0x40) including all named
 *   bitfields, generated from TI SNVSCQ0A, revised September 2026,
 *   section 7.6 (Register Maps).
 *
 *   AVR-compatible naming conventions:
 *     <FIELD>_bp : bit position (0..7)
 *     <FIELD>_bm : bit mask (also available for multi-bit fields)
 *     <FIELD>_gp : group position, for multi-bit fields
 *     <FIELD>_gm : group mask, for multi-bit fields
 *     <FIELD>_<SETTING>_gc : shifted group configuration value
 *
 *   All names are available with the safe LP5814_ prefix. By default,
 *   short, datasheet-identical acronyms are also exported, e.g.:
 *     DEV_CONFIG1, OUT0_EN_bm, OUT0_EN_bp
 *   Define LP5814_NO_SHORT_NAMES before including this file to disable
 *   the short aliases and prevent collisions in larger applications.
 *
 *   IMPORTANT: This is an external I2C device! Register constants are
 *   8-bit I2C subaddresses, NOT memory-mapped AVR registers. Use your
 *   TWI/I2C read and write functions to access the device.
 *
 * @note    Registers 0x01-0x05 need UPDATE_CMD with value 0x55 to apply
 *          their changes; update is accepted only with CHIP_EN == 1.
 * @note    FLAG_CLR uses write-one-to-clear (W1C) bits. Avoid generic
 *          read-modify-write operations on W1C registers.
 * @note    Exiting command shutdown requires eight SDA falling edges
 *          while SCL remains HIGH (maximum SDA toggle rate 100 kHz).
 *          This cannot be done by writing a normal register value.
 *
 * @note    Definitions only: no function prototypes, state or source code.
 *          Include this file from your existing LP5814.h.
 *
 * @version 1.1
 ******************************************************************************/

#ifndef LP5814_REGISTERS_H_
#define LP5814_REGISTERS_H_

#include <stdint.h>

/* ---------------------------------------------------------------------------
 *  I2C slave addresses (7-bit, not shifted).
 * --------------------------------------------------------------------------- */
#define LP5814_I2C_ADDR              (0x2Cu)  /* LP5814DRLR / LP5814YCHR */
#define LP5814I_I2C_ADDR             (0x2Eu)  /* LP5814IYCHR variant      */
#define LP5814_I2C_BROADCAST_ADDR    (0x34u)  /* Broadcast mode           */

/* ---------------------------------------------------------------------------
 *  Complete register address map (all 65 registers).
 *  All registers have a documented reset value of 0x00.
 * --------------------------------------------------------------------------- */

/* Device configuration, engines and commands */
#define LP5814_REG_CHIP_EN                     (0x00u)
#define LP5814_REG_DEV_CONFIG0                 (0x01u)
#define LP5814_REG_DEV_CONFIG1                 (0x02u)
#define LP5814_REG_DEV_CONFIG2                 (0x03u)
#define LP5814_REG_DEV_CONFIG3                 (0x04u)
#define LP5814_REG_DEV_CONFIG4                 (0x05u)
#define LP5814_REG_ENGINE_CONFIG0              (0x06u)
#define LP5814_REG_ENGINE_CONFIG1              (0x07u)
#define LP5814_REG_ENGINE_CONFIG2              (0x08u)
#define LP5814_REG_ENGINE_CONFIG3              (0x09u)
#define LP5814_REG_ENGINE_CONFIG4              (0x0Au)
#define LP5814_REG_ENGINE_CONFIG5              (0x0Bu)
#define LP5814_REG_ENGINE_CONFIG6              (0x0Cu)
#define LP5814_REG_SHUTDOWN_CMD                (0x0Du)
#define LP5814_REG_RESET_CMD                   (0x0Eu)
#define LP5814_REG_UPDATE_CMD                  (0x0Fu)
#define LP5814_REG_START_CMD                   (0x10u)
#define LP5814_REG_STOP_CMD                    (0x11u)
#define LP5814_REG_PAUSE_CONTINUE              (0x12u)
#define LP5814_REG_FLAG_CLR                    (0x13u)

/* Dot current and manual PWM */
#define LP5814_REG_OUT0_DC                     (0x14u)
#define LP5814_REG_OUT1_DC                     (0x15u)
#define LP5814_REG_OUT2_DC                     (0x16u)
#define LP5814_REG_OUT3_DC                     (0x17u)
#define LP5814_REG_OUT0_MANUAL_PWM             (0x18u)
#define LP5814_REG_OUT1_MANUAL_PWM             (0x19u)
#define LP5814_REG_OUT2_MANUAL_PWM             (0x1Au)
#define LP5814_REG_OUT3_MANUAL_PWM             (0x1Bu)

/* Pattern 0 */
#define LP5814_REG_PATTERN0_PAUSE_TIME         (0x1Cu)
#define LP5814_REG_PATTERN0_REPEAT_TIME        (0x1Du)
#define LP5814_REG_PATTERN0_PWM0               (0x1Eu)
#define LP5814_REG_PATTERN0_PWM1               (0x1Fu)
#define LP5814_REG_PATTERN0_PWM2               (0x20u)
#define LP5814_REG_PATTERN0_PWM3               (0x21u)
#define LP5814_REG_PATTERN0_PWM4               (0x22u)
#define LP5814_REG_PATTERN0_SLOPER_TIME1       (0x23u)
#define LP5814_REG_PATTERN0_SLOPER_TIME2       (0x24u)

/* Pattern 1 */
#define LP5814_REG_PATTERN1_PAUSE_TIME         (0x25u)
#define LP5814_REG_PATTERN1_REPEAT_TIME        (0x26u)
#define LP5814_REG_PATTERN1_PWM0               (0x27u)
#define LP5814_REG_PATTERN1_PWM1               (0x28u)
#define LP5814_REG_PATTERN1_PWM2               (0x29u)
#define LP5814_REG_PATTERN1_PWM3               (0x2Au)
#define LP5814_REG_PATTERN1_PWM4               (0x2Bu)
#define LP5814_REG_PATTERN1_SLOPER_TIME1       (0x2Cu)
#define LP5814_REG_PATTERN1_SLOPER_TIME2       (0x2Du)

/* Pattern 2 */
#define LP5814_REG_PATTERN2_PAUSE_TIME         (0x2Eu)
#define LP5814_REG_PATTERN2_REPEAT_TIME        (0x2Fu)
#define LP5814_REG_PATTERN2_PWM0               (0x30u)
#define LP5814_REG_PATTERN2_PWM1               (0x31u)
#define LP5814_REG_PATTERN2_PWM2               (0x32u)
#define LP5814_REG_PATTERN2_PWM3               (0x33u)
#define LP5814_REG_PATTERN2_PWM4               (0x34u)
#define LP5814_REG_PATTERN2_SLOPER_TIME1       (0x35u)
#define LP5814_REG_PATTERN2_SLOPER_TIME2       (0x36u)

/* Pattern 3 */
#define LP5814_REG_PATTERN3_PAUSE_TIME         (0x37u)
#define LP5814_REG_PATTERN3_REPEAT_TIME        (0x38u)
#define LP5814_REG_PATTERN3_PWM0               (0x39u)
#define LP5814_REG_PATTERN3_PWM1               (0x3Au)
#define LP5814_REG_PATTERN3_PWM2               (0x3Bu)
#define LP5814_REG_PATTERN3_PWM3               (0x3Cu)
#define LP5814_REG_PATTERN3_PWM4               (0x3Du)
#define LP5814_REG_PATTERN3_SLOPER_TIME1       (0x3Eu)
#define LP5814_REG_PATTERN3_SLOPER_TIME2       (0x3Fu)

/* Read-only status flags */
#define LP5814_REG_FLAG                        (0x40u)

/* ---------------------------------------------------------------------------
 *  Bit positions and masks, grouped by register.
 *
 *  Access notation: R = read only, W = write only, RW = read/write,
 *                   W1C = write 1 to clear.
 *  Reserved fields are intentionally NOT exposed.
 * --------------------------------------------------------------------------- */

/* CHIP_EN (0x00, reset 0x00) */
/* [0] RW */
#define LP5814_CHIP_EN_bp (0u)
#define LP5814_CHIP_EN_bm (0x01u)

/* DEV_CONFIG0 (0x01, reset 0x00) */
/* [0] RW */
#define LP5814_MAX_CURRENT_bp (0u)
#define LP5814_MAX_CURRENT_bm (0x01u)

/* DEV_CONFIG1 (0x02, reset 0x00) */
/* [3] RW */
#define LP5814_OUT3_EN_bp (3u)
#define LP5814_OUT3_EN_bm (0x08u)
/* [2] RW */
#define LP5814_OUT2_EN_bp (2u)
#define LP5814_OUT2_EN_bm (0x04u)
/* [1] RW */
#define LP5814_OUT1_EN_bp (1u)
#define LP5814_OUT1_EN_bm (0x02u)
/* [0] RW */
#define LP5814_OUT0_EN_bp (0u)
#define LP5814_OUT0_EN_bm (0x01u)

/* DEV_CONFIG2 (0x03, reset 0x00) */
/* [7:4] RW */
#define LP5814_LED_FADE_TIME_bp (4u)
#define LP5814_LED_FADE_TIME_bm (0xF0u)
#define LP5814_LED_FADE_TIME_gp LP5814_LED_FADE_TIME_bp
#define LP5814_LED_FADE_TIME_gm LP5814_LED_FADE_TIME_bm
/* [3] RW */
#define LP5814_OUT3_FADE_EN_bp (3u)
#define LP5814_OUT3_FADE_EN_bm (0x08u)
/* [2] RW */
#define LP5814_OUT2_FADE_EN_bp (2u)
#define LP5814_OUT2_FADE_EN_bm (0x04u)
/* [1] RW */
#define LP5814_OUT1_FADE_EN_bp (1u)
#define LP5814_OUT1_FADE_EN_bm (0x02u)
/* [0] RW */
#define LP5814_OUT0_FADE_EN_bp (0u)
#define LP5814_OUT0_FADE_EN_bm (0x01u)

/* DEV_CONFIG3 (0x04, reset 0x00) */
/* [7] RW */
#define LP5814_OUT3_EXP_EN_bp (7u)
#define LP5814_OUT3_EXP_EN_bm (0x80u)
/* [6] RW */
#define LP5814_OUT2_EXP_EN_bp (6u)
#define LP5814_OUT2_EXP_EN_bm (0x40u)
/* [5] RW */
#define LP5814_OUT1_EXP_EN_bp (5u)
#define LP5814_OUT1_EXP_EN_bm (0x20u)
/* [4] RW */
#define LP5814_OUT0_EXP_EN_bp (4u)
#define LP5814_OUT0_EXP_EN_bm (0x10u)
/* [3] RW */
#define LP5814_OUT3_AUTO_EN_bp (3u)
#define LP5814_OUT3_AUTO_EN_bm (0x08u)
/* [2] RW */
#define LP5814_OUT2_AUTO_EN_bp (2u)
#define LP5814_OUT2_AUTO_EN_bm (0x04u)
/* [1] RW */
#define LP5814_OUT1_AUTO_EN_bp (1u)
#define LP5814_OUT1_AUTO_EN_bm (0x02u)
/* [0] RW */
#define LP5814_OUT0_AUTO_EN_bp (0u)
#define LP5814_OUT0_AUTO_EN_bm (0x01u)

/* DEV_CONFIG4 (0x05, reset 0x00) */
/* [7:6] RW */
#define LP5814_OUT3_ENGINE_CH_bp (6u)
#define LP5814_OUT3_ENGINE_CH_bm (0xC0u)
#define LP5814_OUT3_ENGINE_CH_gp LP5814_OUT3_ENGINE_CH_bp
#define LP5814_OUT3_ENGINE_CH_gm LP5814_OUT3_ENGINE_CH_bm
/* [5:4] RW */
#define LP5814_OUT2_ENGINE_CH_bp (4u)
#define LP5814_OUT2_ENGINE_CH_bm (0x30u)
#define LP5814_OUT2_ENGINE_CH_gp LP5814_OUT2_ENGINE_CH_bp
#define LP5814_OUT2_ENGINE_CH_gm LP5814_OUT2_ENGINE_CH_bm
/* [3:2] RW */
#define LP5814_OUT1_ENGINE_CH_bp (2u)
#define LP5814_OUT1_ENGINE_CH_bm (0x0Cu)
#define LP5814_OUT1_ENGINE_CH_gp LP5814_OUT1_ENGINE_CH_bp
#define LP5814_OUT1_ENGINE_CH_gm LP5814_OUT1_ENGINE_CH_bm
/* [1:0] RW */
#define LP5814_OUT0_ENGINE_CH_bp (0u)
#define LP5814_OUT0_ENGINE_CH_bm (0x03u)
#define LP5814_OUT0_ENGINE_CH_gp LP5814_OUT0_ENGINE_CH_bp
#define LP5814_OUT0_ENGINE_CH_gm LP5814_OUT0_ENGINE_CH_bm

/* ENGINE_CONFIG0 (0x06, reset 0x00) */
/* [7:6] RW */
#define LP5814_ENGINE0_ORDER3_bp (6u)
#define LP5814_ENGINE0_ORDER3_bm (0xC0u)
#define LP5814_ENGINE0_ORDER3_gp LP5814_ENGINE0_ORDER3_bp
#define LP5814_ENGINE0_ORDER3_gm LP5814_ENGINE0_ORDER3_bm
/* [5:4] RW */
#define LP5814_ENGINE0_ORDER2_bp (4u)
#define LP5814_ENGINE0_ORDER2_bm (0x30u)
#define LP5814_ENGINE0_ORDER2_gp LP5814_ENGINE0_ORDER2_bp
#define LP5814_ENGINE0_ORDER2_gm LP5814_ENGINE0_ORDER2_bm
/* [3:2] RW */
#define LP5814_ENGINE0_ORDER1_bp (2u)
#define LP5814_ENGINE0_ORDER1_bm (0x0Cu)
#define LP5814_ENGINE0_ORDER1_gp LP5814_ENGINE0_ORDER1_bp
#define LP5814_ENGINE0_ORDER1_gm LP5814_ENGINE0_ORDER1_bm
/* [1:0] RW */
#define LP5814_ENGINE0_ORDER0_bp (0u)
#define LP5814_ENGINE0_ORDER0_bm (0x03u)
#define LP5814_ENGINE0_ORDER0_gp LP5814_ENGINE0_ORDER0_bp
#define LP5814_ENGINE0_ORDER0_gm LP5814_ENGINE0_ORDER0_bm

/* ENGINE_CONFIG1 (0x07, reset 0x00) */
/* [7:6] RW */
#define LP5814_ENGINE1_ORDER3_bp (6u)
#define LP5814_ENGINE1_ORDER3_bm (0xC0u)
#define LP5814_ENGINE1_ORDER3_gp LP5814_ENGINE1_ORDER3_bp
#define LP5814_ENGINE1_ORDER3_gm LP5814_ENGINE1_ORDER3_bm
/* [5:4] RW */
#define LP5814_ENGINE1_ORDER2_bp (4u)
#define LP5814_ENGINE1_ORDER2_bm (0x30u)
#define LP5814_ENGINE1_ORDER2_gp LP5814_ENGINE1_ORDER2_bp
#define LP5814_ENGINE1_ORDER2_gm LP5814_ENGINE1_ORDER2_bm
/* [3:2] RW */
#define LP5814_ENGINE1_ORDER1_bp (2u)
#define LP5814_ENGINE1_ORDER1_bm (0x0Cu)
#define LP5814_ENGINE1_ORDER1_gp LP5814_ENGINE1_ORDER1_bp
#define LP5814_ENGINE1_ORDER1_gm LP5814_ENGINE1_ORDER1_bm
/* [1:0] RW */
#define LP5814_ENGINE1_ORDER0_bp (0u)
#define LP5814_ENGINE1_ORDER0_bm (0x03u)
#define LP5814_ENGINE1_ORDER0_gp LP5814_ENGINE1_ORDER0_bp
#define LP5814_ENGINE1_ORDER0_gm LP5814_ENGINE1_ORDER0_bm

/* ENGINE_CONFIG2 (0x08, reset 0x00) */
/* [7:6] RW */
#define LP5814_ENGINE2_ORDER3_bp (6u)
#define LP5814_ENGINE2_ORDER3_bm (0xC0u)
#define LP5814_ENGINE2_ORDER3_gp LP5814_ENGINE2_ORDER3_bp
#define LP5814_ENGINE2_ORDER3_gm LP5814_ENGINE2_ORDER3_bm
/* [5:4] RW */
#define LP5814_ENGINE2_ORDER2_bp (4u)
#define LP5814_ENGINE2_ORDER2_bm (0x30u)
#define LP5814_ENGINE2_ORDER2_gp LP5814_ENGINE2_ORDER2_bp
#define LP5814_ENGINE2_ORDER2_gm LP5814_ENGINE2_ORDER2_bm
/* [3:2] RW */
#define LP5814_ENGINE2_ORDER1_bp (2u)
#define LP5814_ENGINE2_ORDER1_bm (0x0Cu)
#define LP5814_ENGINE2_ORDER1_gp LP5814_ENGINE2_ORDER1_bp
#define LP5814_ENGINE2_ORDER1_gm LP5814_ENGINE2_ORDER1_bm
/* [1:0] RW */
#define LP5814_ENGINE2_ORDER0_bp (0u)
#define LP5814_ENGINE2_ORDER0_bm (0x03u)
#define LP5814_ENGINE2_ORDER0_gp LP5814_ENGINE2_ORDER0_bp
#define LP5814_ENGINE2_ORDER0_gm LP5814_ENGINE2_ORDER0_bm

/* ENGINE_CONFIG3 (0x09, reset 0x00) */
/* [7:6] RW */
#define LP5814_ENGINE3_ORDER3_bp (6u)
#define LP5814_ENGINE3_ORDER3_bm (0xC0u)
#define LP5814_ENGINE3_ORDER3_gp LP5814_ENGINE3_ORDER3_bp
#define LP5814_ENGINE3_ORDER3_gm LP5814_ENGINE3_ORDER3_bm
/* [5:4] RW */
#define LP5814_ENGINE3_ORDER2_bp (4u)
#define LP5814_ENGINE3_ORDER2_bm (0x30u)
#define LP5814_ENGINE3_ORDER2_gp LP5814_ENGINE3_ORDER2_bp
#define LP5814_ENGINE3_ORDER2_gm LP5814_ENGINE3_ORDER2_bm
/* [3:2] RW */
#define LP5814_ENGINE3_ORDER1_bp (2u)
#define LP5814_ENGINE3_ORDER1_bm (0x0Cu)
#define LP5814_ENGINE3_ORDER1_gp LP5814_ENGINE3_ORDER1_bp
#define LP5814_ENGINE3_ORDER1_gm LP5814_ENGINE3_ORDER1_bm
/* [1:0] RW */
#define LP5814_ENGINE3_ORDER0_bp (0u)
#define LP5814_ENGINE3_ORDER0_bm (0x03u)
#define LP5814_ENGINE3_ORDER0_gp LP5814_ENGINE3_ORDER0_bp
#define LP5814_ENGINE3_ORDER0_gm LP5814_ENGINE3_ORDER0_bm

/* ENGINE_CONFIG4 (0x0A, reset 0x00) */
/* [7] RW */
#define LP5814_E1O3_EN_bp (7u)
#define LP5814_E1O3_EN_bm (0x80u)
/* [6] RW */
#define LP5814_E1O2_EN_bp (6u)
#define LP5814_E1O2_EN_bm (0x40u)
/* [5] RW */
#define LP5814_E1O1_EN_bp (5u)
#define LP5814_E1O1_EN_bm (0x20u)
/* [4] RW */
#define LP5814_E1O0_EN_bp (4u)
#define LP5814_E1O0_EN_bm (0x10u)
/* [3] RW */
#define LP5814_E0O3_EN_bp (3u)
#define LP5814_E0O3_EN_bm (0x08u)
/* [2] RW */
#define LP5814_E0O2_EN_bp (2u)
#define LP5814_E0O2_EN_bm (0x04u)
/* [1] RW */
#define LP5814_E0O1_EN_bp (1u)
#define LP5814_E0O1_EN_bm (0x02u)
/* [0] RW */
#define LP5814_E0O0_EN_bp (0u)
#define LP5814_E0O0_EN_bm (0x01u)

/* ENGINE_CONFIG5 (0x0B, reset 0x00) */
/* [7] RW */
#define LP5814_E3O3_EN_bp (7u)
#define LP5814_E3O3_EN_bm (0x80u)
/* [6] RW */
#define LP5814_E3O2_EN_bp (6u)
#define LP5814_E3O2_EN_bm (0x40u)
/* [5] RW */
#define LP5814_E3O1_EN_bp (5u)
#define LP5814_E3O1_EN_bm (0x20u)
/* [4] RW */
#define LP5814_E3O0_EN_bp (4u)
#define LP5814_E3O0_EN_bm (0x10u)
/* [3] RW */
#define LP5814_E2O3_EN_bp (3u)
#define LP5814_E2O3_EN_bm (0x08u)
/* [2] RW */
#define LP5814_E2O2_EN_bp (2u)
#define LP5814_E2O2_EN_bm (0x04u)
/* [1] RW */
#define LP5814_E2O1_EN_bp (1u)
#define LP5814_E2O1_EN_bm (0x02u)
/* [0] RW */
#define LP5814_E2O0_EN_bp (0u)
#define LP5814_E2O0_EN_bm (0x01u)

/* ENGINE_CONFIG6 (0x0C, reset 0x00) */
/* [7:6] RW */
#define LP5814_ENGINE3_REPT_bp (6u)
#define LP5814_ENGINE3_REPT_bm (0xC0u)
#define LP5814_ENGINE3_REPT_gp LP5814_ENGINE3_REPT_bp
#define LP5814_ENGINE3_REPT_gm LP5814_ENGINE3_REPT_bm
/* [5:4] RW */
#define LP5814_ENGINE2_REPT_bp (4u)
#define LP5814_ENGINE2_REPT_bm (0x30u)
#define LP5814_ENGINE2_REPT_gp LP5814_ENGINE2_REPT_bp
#define LP5814_ENGINE2_REPT_gm LP5814_ENGINE2_REPT_bm
/* [3:2] RW */
#define LP5814_ENGINE1_REPT_bp (2u)
#define LP5814_ENGINE1_REPT_bm (0x0Cu)
#define LP5814_ENGINE1_REPT_gp LP5814_ENGINE1_REPT_bp
#define LP5814_ENGINE1_REPT_gm LP5814_ENGINE1_REPT_bm
/* [1:0] RW */
#define LP5814_ENGINE0_REPT_bp (0u)
#define LP5814_ENGINE0_REPT_bm (0x03u)
#define LP5814_ENGINE0_REPT_gp LP5814_ENGINE0_REPT_bp
#define LP5814_ENGINE0_REPT_gm LP5814_ENGINE0_REPT_bm

/* SHUTDOWN_CMD (0x0D, reset 0x00) */
/* [7:0] W */
#define LP5814_SHUTDOWN_bp (0u)
#define LP5814_SHUTDOWN_bm (0xFFu)
#define LP5814_SHUTDOWN_gp LP5814_SHUTDOWN_bp
#define LP5814_SHUTDOWN_gm LP5814_SHUTDOWN_bm

/* RESET_CMD (0x0E, reset 0x00) */
/* [7:0] W */
#define LP5814_RESET_bp (0u)
#define LP5814_RESET_bm (0xFFu)
#define LP5814_RESET_gp LP5814_RESET_bp
#define LP5814_RESET_gm LP5814_RESET_bm

/* UPDATE_CMD (0x0F, reset 0x00) */
/* [7:0] W */
#define LP5814_UPDATE_bp (0u)
#define LP5814_UPDATE_bm (0x55u)
#define LP5814_UPDATE_gp LP5814_UPDATE_bp
#define LP5814_UPDATE_gm LP5814_UPDATE_bm

/* START_CMD (0x10, reset 0x00) */
/* [7:0] W */
#define LP5814_START_bp (0u)
#define LP5814_START_bm (0xFFu)
#define LP5814_START_gp LP5814_START_bp
#define LP5814_START_gm LP5814_START_bm

/* STOP_CMD (0x11, reset 0x00) */
/* [7:0] W */
#define LP5814_STOP_bp (0u)
#define LP5814_STOP_bm (0xAAu)
#define LP5814_STOP_gp LP5814_STOP_bp
#define LP5814_STOP_gm LP5814_STOP_bm

/* PAUSE_CONTINUE (0x12, reset 0x00) */
/* [0] RW */
#define LP5814_PAUSE_CONTINUE_bp (0u)
#define LP5814_PAUSE_CONTINUE_bm (0x01u)

/* FLAG_CLR (0x13, reset 0x00) */
/* [1] W1C */
#define LP5814_TSD_CLR_bp (1u)
#define LP5814_TSD_CLR_bm (0x02u)
/* [0] W1C */
#define LP5814_POR_CLR_bp (0u)
#define LP5814_POR_CLR_bm (0x01u)

/* OUT0_DC (0x14, reset 0x00) */
/* [7:0] RW */
#define LP5814_OUT0_DC_bp (0u)
#define LP5814_OUT0_DC_bm (0xFFu)
#define LP5814_OUT0_DC_gp LP5814_OUT0_DC_bp
#define LP5814_OUT0_DC_gm LP5814_OUT0_DC_bm

/* OUT1_DC (0x15, reset 0x00) */
/* [7:0] RW */
#define LP5814_OUT1_DC_bp (0u)
#define LP5814_OUT1_DC_bm (0xFFu)
#define LP5814_OUT1_DC_gp LP5814_OUT1_DC_bp
#define LP5814_OUT1_DC_gm LP5814_OUT1_DC_bm

/* OUT2_DC (0x16, reset 0x00) */
/* [7:0] RW */
#define LP5814_OUT2_DC_bp (0u)
#define LP5814_OUT2_DC_bm (0xFFu)
#define LP5814_OUT2_DC_gp LP5814_OUT2_DC_bp
#define LP5814_OUT2_DC_gm LP5814_OUT2_DC_bm

/* OUT3_DC (0x17, reset 0x00) */
/* [7:0] RW */
#define LP5814_OUT3_DC_bp (0u)
#define LP5814_OUT3_DC_bm (0xFFu)
#define LP5814_OUT3_DC_gp LP5814_OUT3_DC_bp
#define LP5814_OUT3_DC_gm LP5814_OUT3_DC_bm

/* OUT0_MANUAL_PWM (0x18, reset 0x00) */
/* [7:0] RW */
#define LP5814_OUT0_MANUAL_PWM_bp (0u)
#define LP5814_OUT0_MANUAL_PWM_bm (0xFFu)
#define LP5814_OUT0_MANUAL_PWM_gp LP5814_OUT0_MANUAL_PWM_bp
#define LP5814_OUT0_MANUAL_PWM_gm LP5814_OUT0_MANUAL_PWM_bm

/* OUT1_MANUAL_PWM (0x19, reset 0x00) */
/* [7:0] RW */
#define LP5814_OUT1_MANUAL_PWM_bp (0u)
#define LP5814_OUT1_MANUAL_PWM_bm (0xFFu)
#define LP5814_OUT1_MANUAL_PWM_gp LP5814_OUT1_MANUAL_PWM_bp
#define LP5814_OUT1_MANUAL_PWM_gm LP5814_OUT1_MANUAL_PWM_bm

/* OUT2_MANUAL_PWM (0x1A, reset 0x00) */
/* [7:0] RW */
#define LP5814_OUT2_MANUAL_PWM_bp (0u)
#define LP5814_OUT2_MANUAL_PWM_bm (0xFFu)
#define LP5814_OUT2_MANUAL_PWM_gp LP5814_OUT2_MANUAL_PWM_bp
#define LP5814_OUT2_MANUAL_PWM_gm LP5814_OUT2_MANUAL_PWM_bm

/* OUT3_MANUAL_PWM (0x1B, reset 0x00) */
/* [7:0] RW */
#define LP5814_OUT3_MANUAL_PWM_bp (0u)
#define LP5814_OUT3_MANUAL_PWM_bm (0xFFu)
#define LP5814_OUT3_MANUAL_PWM_gp LP5814_OUT3_MANUAL_PWM_bp
#define LP5814_OUT3_MANUAL_PWM_gm LP5814_OUT3_MANUAL_PWM_bm

/* PATTERN0_PAUSE_TIME (0x1C, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN0_PAUSE_T0_bp (4u)
#define LP5814_PATTERN0_PAUSE_T0_bm (0xF0u)
#define LP5814_PATTERN0_PAUSE_T0_gp LP5814_PATTERN0_PAUSE_T0_bp
#define LP5814_PATTERN0_PAUSE_T0_gm LP5814_PATTERN0_PAUSE_T0_bm
/* [3:0] RW */
#define LP5814_PATTERN0_PAUSE_T1_bp (0u)
#define LP5814_PATTERN0_PAUSE_T1_bm (0x0Fu)
#define LP5814_PATTERN0_PAUSE_T1_gp LP5814_PATTERN0_PAUSE_T1_bp
#define LP5814_PATTERN0_PAUSE_T1_gm LP5814_PATTERN0_PAUSE_T1_bm

/* PATTERN0_REPEAT_TIME (0x1D, reset 0x00) */
/* [3:0] RW */
#define LP5814_PATTERN0_PT_bp (0u)
#define LP5814_PATTERN0_PT_bm (0x0Fu)
#define LP5814_PATTERN0_PT_gp LP5814_PATTERN0_PT_bp
#define LP5814_PATTERN0_PT_gm LP5814_PATTERN0_PT_bm

/* PATTERN0_PWM0 (0x1E, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN0_PWM0_bp (0u)
#define LP5814_PATTERN0_PWM0_bm (0xFFu)
#define LP5814_PATTERN0_PWM0_gp LP5814_PATTERN0_PWM0_bp
#define LP5814_PATTERN0_PWM0_gm LP5814_PATTERN0_PWM0_bm

/* PATTERN0_PWM1 (0x1F, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN0_PWM1_bp (0u)
#define LP5814_PATTERN0_PWM1_bm (0xFFu)
#define LP5814_PATTERN0_PWM1_gp LP5814_PATTERN0_PWM1_bp
#define LP5814_PATTERN0_PWM1_gm LP5814_PATTERN0_PWM1_bm

/* PATTERN0_PWM2 (0x20, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN0_PWM2_bp (0u)
#define LP5814_PATTERN0_PWM2_bm (0xFFu)
#define LP5814_PATTERN0_PWM2_gp LP5814_PATTERN0_PWM2_bp
#define LP5814_PATTERN0_PWM2_gm LP5814_PATTERN0_PWM2_bm

/* PATTERN0_PWM3 (0x21, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN0_PWM3_bp (0u)
#define LP5814_PATTERN0_PWM3_bm (0xFFu)
#define LP5814_PATTERN0_PWM3_gp LP5814_PATTERN0_PWM3_bp
#define LP5814_PATTERN0_PWM3_gm LP5814_PATTERN0_PWM3_bm

/* PATTERN0_PWM4 (0x22, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN0_PWM4_bp (0u)
#define LP5814_PATTERN0_PWM4_bm (0xFFu)
#define LP5814_PATTERN0_PWM4_gp LP5814_PATTERN0_PWM4_bp
#define LP5814_PATTERN0_PWM4_gm LP5814_PATTERN0_PWM4_bm

/* PATTERN0_SLOPER_TIME1 (0x23, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN0_SLOPER_T1_bp (4u)
#define LP5814_PATTERN0_SLOPER_T1_bm (0xF0u)
#define LP5814_PATTERN0_SLOPER_T1_gp LP5814_PATTERN0_SLOPER_T1_bp
#define LP5814_PATTERN0_SLOPER_T1_gm LP5814_PATTERN0_SLOPER_T1_bm
/* [3:0] RW */
#define LP5814_PATTERN0_SLOPER_T0_bp (0u)
#define LP5814_PATTERN0_SLOPER_T0_bm (0x0Fu)
#define LP5814_PATTERN0_SLOPER_T0_gp LP5814_PATTERN0_SLOPER_T0_bp
#define LP5814_PATTERN0_SLOPER_T0_gm LP5814_PATTERN0_SLOPER_T0_bm

/* PATTERN0_SLOPER_TIME2 (0x24, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN0_SLOPER_T3_bp (4u)
#define LP5814_PATTERN0_SLOPER_T3_bm (0xF0u)
#define LP5814_PATTERN0_SLOPER_T3_gp LP5814_PATTERN0_SLOPER_T3_bp
#define LP5814_PATTERN0_SLOPER_T3_gm LP5814_PATTERN0_SLOPER_T3_bm
/* [3:0] RW */
#define LP5814_PATTERN0_SLOPER_T2_bp (0u)
#define LP5814_PATTERN0_SLOPER_T2_bm (0x0Fu)
#define LP5814_PATTERN0_SLOPER_T2_gp LP5814_PATTERN0_SLOPER_T2_bp
#define LP5814_PATTERN0_SLOPER_T2_gm LP5814_PATTERN0_SLOPER_T2_bm

/* PATTERN1_PAUSE_TIME (0x25, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN1_PAUSE_T0_bp (4u)
#define LP5814_PATTERN1_PAUSE_T0_bm (0xF0u)
#define LP5814_PATTERN1_PAUSE_T0_gp LP5814_PATTERN1_PAUSE_T0_bp
#define LP5814_PATTERN1_PAUSE_T0_gm LP5814_PATTERN1_PAUSE_T0_bm
/* [3:0] RW */
#define LP5814_PATTERN1_PAUSE_T1_bp (0u)
#define LP5814_PATTERN1_PAUSE_T1_bm (0x0Fu)
#define LP5814_PATTERN1_PAUSE_T1_gp LP5814_PATTERN1_PAUSE_T1_bp
#define LP5814_PATTERN1_PAUSE_T1_gm LP5814_PATTERN1_PAUSE_T1_bm

/* PATTERN1_REPEAT_TIME (0x26, reset 0x00) */
/* [3:0] RW */
#define LP5814_PATTERN1_PT_bp (0u)
#define LP5814_PATTERN1_PT_bm (0x0Fu)
#define LP5814_PATTERN1_PT_gp LP5814_PATTERN1_PT_bp
#define LP5814_PATTERN1_PT_gm LP5814_PATTERN1_PT_bm

/* PATTERN1_PWM0 (0x27, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN1_PWM0_bp (0u)
#define LP5814_PATTERN1_PWM0_bm (0xFFu)
#define LP5814_PATTERN1_PWM0_gp LP5814_PATTERN1_PWM0_bp
#define LP5814_PATTERN1_PWM0_gm LP5814_PATTERN1_PWM0_bm

/* PATTERN1_PWM1 (0x28, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN1_PWM1_bp (0u)
#define LP5814_PATTERN1_PWM1_bm (0xFFu)
#define LP5814_PATTERN1_PWM1_gp LP5814_PATTERN1_PWM1_bp
#define LP5814_PATTERN1_PWM1_gm LP5814_PATTERN1_PWM1_bm

/* PATTERN1_PWM2 (0x29, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN1_PWM2_bp (0u)
#define LP5814_PATTERN1_PWM2_bm (0xFFu)
#define LP5814_PATTERN1_PWM2_gp LP5814_PATTERN1_PWM2_bp
#define LP5814_PATTERN1_PWM2_gm LP5814_PATTERN1_PWM2_bm

/* PATTERN1_PWM3 (0x2A, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN1_PWM3_bp (0u)
#define LP5814_PATTERN1_PWM3_bm (0xFFu)
#define LP5814_PATTERN1_PWM3_gp LP5814_PATTERN1_PWM3_bp
#define LP5814_PATTERN1_PWM3_gm LP5814_PATTERN1_PWM3_bm

/* PATTERN1_PWM4 (0x2B, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN1_PWM4_bp (0u)
#define LP5814_PATTERN1_PWM4_bm (0xFFu)
#define LP5814_PATTERN1_PWM4_gp LP5814_PATTERN1_PWM4_bp
#define LP5814_PATTERN1_PWM4_gm LP5814_PATTERN1_PWM4_bm

/* PATTERN1_SLOPER_TIME1 (0x2C, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN1_SLOPER_T1_bp (4u)
#define LP5814_PATTERN1_SLOPER_T1_bm (0xF0u)
#define LP5814_PATTERN1_SLOPER_T1_gp LP5814_PATTERN1_SLOPER_T1_bp
#define LP5814_PATTERN1_SLOPER_T1_gm LP5814_PATTERN1_SLOPER_T1_bm
/* [3:0] RW */
#define LP5814_PATTERN1_SLOPER_T0_bp (0u)
#define LP5814_PATTERN1_SLOPER_T0_bm (0x0Fu)
#define LP5814_PATTERN1_SLOPER_T0_gp LP5814_PATTERN1_SLOPER_T0_bp
#define LP5814_PATTERN1_SLOPER_T0_gm LP5814_PATTERN1_SLOPER_T0_bm

/* PATTERN1_SLOPER_TIME2 (0x2D, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN1_SLOPER_T3_bp (4u)
#define LP5814_PATTERN1_SLOPER_T3_bm (0xF0u)
#define LP5814_PATTERN1_SLOPER_T3_gp LP5814_PATTERN1_SLOPER_T3_bp
#define LP5814_PATTERN1_SLOPER_T3_gm LP5814_PATTERN1_SLOPER_T3_bm
/* [3:0] RW */
#define LP5814_PATTERN1_SLOPER_T2_bp (0u)
#define LP5814_PATTERN1_SLOPER_T2_bm (0x0Fu)
#define LP5814_PATTERN1_SLOPER_T2_gp LP5814_PATTERN1_SLOPER_T2_bp
#define LP5814_PATTERN1_SLOPER_T2_gm LP5814_PATTERN1_SLOPER_T2_bm

/* PATTERN2_PAUSE_TIME (0x2E, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN2_PAUSE_T0_bp (4u)
#define LP5814_PATTERN2_PAUSE_T0_bm (0xF0u)
#define LP5814_PATTERN2_PAUSE_T0_gp LP5814_PATTERN2_PAUSE_T0_bp
#define LP5814_PATTERN2_PAUSE_T0_gm LP5814_PATTERN2_PAUSE_T0_bm
/* [3:0] RW */
#define LP5814_PATTERN2_PAUSE_T1_bp (0u)
#define LP5814_PATTERN2_PAUSE_T1_bm (0x0Fu)
#define LP5814_PATTERN2_PAUSE_T1_gp LP5814_PATTERN2_PAUSE_T1_bp
#define LP5814_PATTERN2_PAUSE_T1_gm LP5814_PATTERN2_PAUSE_T1_bm

/* PATTERN2_REPEAT_TIME (0x2F, reset 0x00) */
/* [3:0] RW */
#define LP5814_PATTERN2_PT_bp (0u)
#define LP5814_PATTERN2_PT_bm (0x0Fu)
#define LP5814_PATTERN2_PT_gp LP5814_PATTERN2_PT_bp
#define LP5814_PATTERN2_PT_gm LP5814_PATTERN2_PT_bm

/* PATTERN2_PWM0 (0x30, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN2_PWM0_bp (0u)
#define LP5814_PATTERN2_PWM0_bm (0xFFu)
#define LP5814_PATTERN2_PWM0_gp LP5814_PATTERN2_PWM0_bp
#define LP5814_PATTERN2_PWM0_gm LP5814_PATTERN2_PWM0_bm

/* PATTERN2_PWM1 (0x31, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN2_PWM1_bp (0u)
#define LP5814_PATTERN2_PWM1_bm (0xFFu)
#define LP5814_PATTERN2_PWM1_gp LP5814_PATTERN2_PWM1_bp
#define LP5814_PATTERN2_PWM1_gm LP5814_PATTERN2_PWM1_bm

/* PATTERN2_PWM2 (0x32, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN2_PWM2_bp (0u)
#define LP5814_PATTERN2_PWM2_bm (0xFFu)
#define LP5814_PATTERN2_PWM2_gp LP5814_PATTERN2_PWM2_bp
#define LP5814_PATTERN2_PWM2_gm LP5814_PATTERN2_PWM2_bm

/* PATTERN2_PWM3 (0x33, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN2_PWM3_bp (0u)
#define LP5814_PATTERN2_PWM3_bm (0xFFu)
#define LP5814_PATTERN2_PWM3_gp LP5814_PATTERN2_PWM3_bp
#define LP5814_PATTERN2_PWM3_gm LP5814_PATTERN2_PWM3_bm

/* PATTERN2_PWM4 (0x34, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN2_PWM4_bp (0u)
#define LP5814_PATTERN2_PWM4_bm (0xFFu)
#define LP5814_PATTERN2_PWM4_gp LP5814_PATTERN2_PWM4_bp
#define LP5814_PATTERN2_PWM4_gm LP5814_PATTERN2_PWM4_bm

/* PATTERN2_SLOPER_TIME1 (0x35, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN2_SLOPER_T1_bp (4u)
#define LP5814_PATTERN2_SLOPER_T1_bm (0xF0u)
#define LP5814_PATTERN2_SLOPER_T1_gp LP5814_PATTERN2_SLOPER_T1_bp
#define LP5814_PATTERN2_SLOPER_T1_gm LP5814_PATTERN2_SLOPER_T1_bm
/* [3:0] RW */
#define LP5814_PATTERN2_SLOPER_T0_bp (0u)
#define LP5814_PATTERN2_SLOPER_T0_bm (0x0Fu)
#define LP5814_PATTERN2_SLOPER_T0_gp LP5814_PATTERN2_SLOPER_T0_bp
#define LP5814_PATTERN2_SLOPER_T0_gm LP5814_PATTERN2_SLOPER_T0_bm

/* PATTERN2_SLOPER_TIME2 (0x36, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN2_SLOPER_T3_bp (4u)
#define LP5814_PATTERN2_SLOPER_T3_bm (0xF0u)
#define LP5814_PATTERN2_SLOPER_T3_gp LP5814_PATTERN2_SLOPER_T3_bp
#define LP5814_PATTERN2_SLOPER_T3_gm LP5814_PATTERN2_SLOPER_T3_bm
/* [3:0] RW */
#define LP5814_PATTERN2_SLOPER_T2_bp (0u)
#define LP5814_PATTERN2_SLOPER_T2_bm (0x0Fu)
#define LP5814_PATTERN2_SLOPER_T2_gp LP5814_PATTERN2_SLOPER_T2_bp
#define LP5814_PATTERN2_SLOPER_T2_gm LP5814_PATTERN2_SLOPER_T2_bm

/* PATTERN3_PAUSE_TIME (0x37, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN3_PAUSE_T0_bp (4u)
#define LP5814_PATTERN3_PAUSE_T0_bm (0xF0u)
#define LP5814_PATTERN3_PAUSE_T0_gp LP5814_PATTERN3_PAUSE_T0_bp
#define LP5814_PATTERN3_PAUSE_T0_gm LP5814_PATTERN3_PAUSE_T0_bm
/* [3:0] RW */
#define LP5814_PATTERN3_PAUSE_T1_bp (0u)
#define LP5814_PATTERN3_PAUSE_T1_bm (0x0Fu)
#define LP5814_PATTERN3_PAUSE_T1_gp LP5814_PATTERN3_PAUSE_T1_bp
#define LP5814_PATTERN3_PAUSE_T1_gm LP5814_PATTERN3_PAUSE_T1_bm

/* PATTERN3_REPEAT_TIME (0x38, reset 0x00) */
/* [3:0] RW */
#define LP5814_PATTERN3_PT_bp (0u)
#define LP5814_PATTERN3_PT_bm (0x0Fu)
#define LP5814_PATTERN3_PT_gp LP5814_PATTERN3_PT_bp
#define LP5814_PATTERN3_PT_gm LP5814_PATTERN3_PT_bm

/* PATTERN3_PWM0 (0x39, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN3_PWM0_bp (0u)
#define LP5814_PATTERN3_PWM0_bm (0xFFu)
#define LP5814_PATTERN3_PWM0_gp LP5814_PATTERN3_PWM0_bp
#define LP5814_PATTERN3_PWM0_gm LP5814_PATTERN3_PWM0_bm

/* PATTERN3_PWM1 (0x3A, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN3_PWM1_bp (0u)
#define LP5814_PATTERN3_PWM1_bm (0xFFu)
#define LP5814_PATTERN3_PWM1_gp LP5814_PATTERN3_PWM1_bp
#define LP5814_PATTERN3_PWM1_gm LP5814_PATTERN3_PWM1_bm

/* PATTERN3_PWM2 (0x3B, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN3_PWM2_bp (0u)
#define LP5814_PATTERN3_PWM2_bm (0xFFu)
#define LP5814_PATTERN3_PWM2_gp LP5814_PATTERN3_PWM2_bp
#define LP5814_PATTERN3_PWM2_gm LP5814_PATTERN3_PWM2_bm

/* PATTERN3_PWM3 (0x3C, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN3_PWM3_bp (0u)
#define LP5814_PATTERN3_PWM3_bm (0xFFu)
#define LP5814_PATTERN3_PWM3_gp LP5814_PATTERN3_PWM3_bp
#define LP5814_PATTERN3_PWM3_gm LP5814_PATTERN3_PWM3_bm

/* PATTERN3_PWM4 (0x3D, reset 0x00) */
/* [7:0] RW */
#define LP5814_PATTERN3_PWM4_bp (0u)
#define LP5814_PATTERN3_PWM4_bm (0xFFu)
#define LP5814_PATTERN3_PWM4_gp LP5814_PATTERN3_PWM4_bp
#define LP5814_PATTERN3_PWM4_gm LP5814_PATTERN3_PWM4_bm

/* PATTERN3_SLOPER_TIME1 (0x3E, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN3_SLOPER_T1_bp (4u)
#define LP5814_PATTERN3_SLOPER_T1_bm (0xF0u)
#define LP5814_PATTERN3_SLOPER_T1_gp LP5814_PATTERN3_SLOPER_T1_bp
#define LP5814_PATTERN3_SLOPER_T1_gm LP5814_PATTERN3_SLOPER_T1_bm
/* [3:0] RW */
#define LP5814_PATTERN3_SLOPER_T0_bp (0u)
#define LP5814_PATTERN3_SLOPER_T0_bm (0x0Fu)
#define LP5814_PATTERN3_SLOPER_T0_gp LP5814_PATTERN3_SLOPER_T0_bp
#define LP5814_PATTERN3_SLOPER_T0_gm LP5814_PATTERN3_SLOPER_T0_bm

/* PATTERN3_SLOPER_TIME2 (0x3F, reset 0x00) */
/* [7:4] RW */
#define LP5814_PATTERN3_SLOPER_T3_bp (4u)
#define LP5814_PATTERN3_SLOPER_T3_bm (0xF0u)
#define LP5814_PATTERN3_SLOPER_T3_gp LP5814_PATTERN3_SLOPER_T3_bp
#define LP5814_PATTERN3_SLOPER_T3_gm LP5814_PATTERN3_SLOPER_T3_bm
/* [3:0] RW */
#define LP5814_PATTERN3_SLOPER_T2_bp (0u)
#define LP5814_PATTERN3_SLOPER_T2_bm (0x0Fu)
#define LP5814_PATTERN3_SLOPER_T2_gp LP5814_PATTERN3_SLOPER_T2_bp
#define LP5814_PATTERN3_SLOPER_T2_gm LP5814_PATTERN3_SLOPER_T2_bm

/* FLAG (0x40, reset 0x00) */
/* [6] R */
#define LP5814_OUT3_ENGINE_BUSY_bp (6u)
#define LP5814_OUT3_ENGINE_BUSY_bm (0x40u)
/* [5] R */
#define LP5814_OUT2_ENGINE_BUSY_bp (5u)
#define LP5814_OUT2_ENGINE_BUSY_bm (0x20u)
/* [4] R */
#define LP5814_OUT1_ENGINE_BUSY_bp (4u)
#define LP5814_OUT1_ENGINE_BUSY_bm (0x10u)
/* [3] R */
#define LP5814_OUT0_ENGINE_BUSY_bp (3u)
#define LP5814_OUT0_ENGINE_BUSY_bm (0x08u)
/* [2] R */
#define LP5814_ENGINE_BUSY_bp (2u)
#define LP5814_ENGINE_BUSY_bm (0x04u)
/* [1] R */
#define LP5814_TSD_bp (1u)
#define LP5814_TSD_bm (0x02u)
/* [0] R */
#define LP5814_POR_bp (0u)
#define LP5814_POR_bm (0x01u)

/* ---------------------------------------------------------------------------
 *  Command bytes (write exactly these values to the matching *_CMD reg).
 * --------------------------------------------------------------------------- */
#define LP5814_CMD_SHUTDOWN          (0x33u)
#define LP5814_CMD_RESET             (0xCCu)
#define LP5814_CMD_UPDATE            (0x55u)
#define LP5814_CMD_START             (0xFFu)
#define LP5814_CMD_STOP              (0xAAu)

/* ---------------------------------------------------------------------------
 *  Symbolic field values.
 * --------------------------------------------------------------------------- */
#define LP5814_DISABLED                   (0u)
#define LP5814_ENABLED                    (1u)
#define LP5814_MAX_CURRENT_25_5MA         (0u)
#define LP5814_MAX_CURRENT_51MA           (1u)
#define LP5814_ENGINE_0                    (0u)
#define LP5814_ENGINE_1                    (1u)
#define LP5814_ENGINE_2                    (2u)
#define LP5814_ENGINE_3                    (3u)
#define LP5814_ENGINE_REPEAT_NONE         (0u)
#define LP5814_ENGINE_REPEAT_ONCE         (1u)
#define LP5814_ENGINE_REPEAT_TWICE        (2u)
#define LP5814_ENGINE_REPEAT_INFINITE     (3u)
/* Shared time coding for LED_FADE_TIME and PATTERNx_*_TIME fields. */
#define LP5814_TIME_0MS                  (0x00u)
#define LP5814_TIME_50MS                 (0x01u)
#define LP5814_TIME_100MS                (0x02u)
#define LP5814_TIME_150MS                (0x03u)
#define LP5814_TIME_200MS                (0x04u)
#define LP5814_TIME_250MS                (0x05u)
#define LP5814_TIME_300MS                (0x06u)
#define LP5814_TIME_350MS                (0x07u)
#define LP5814_TIME_400MS                (0x08u)
#define LP5814_TIME_450MS                (0x09u)
#define LP5814_TIME_500MS                (0x0Au)
#define LP5814_TIME_1000MS               (0x0Bu)
#define LP5814_TIME_2000MS               (0x0Cu)
#define LP5814_TIME_4000MS               (0x0Du)
#define LP5814_TIME_6000MS               (0x0Eu)
#define LP5814_TIME_8000MS               (0x0Fu)

/* ---------------------------------------------------------------------------
 *  AVR-style _gc values for enumerated configuration fields.
 *  These values are already shifted to their register bit positions.
 *  They can be OR-ed with other non-overlapping configuration fields.
 *  See section 7.6 of TI datasheet SNVSCQ0A.
 * --------------------------------------------------------------------------- */

/* Maximum output current (DEV_CONFIG0) */
#define LP5814_MAX_CURRENT_25_5MA_gc                              (0x00u)
#define LP5814_MAX_CURRENT_51MA_gc                                (0x01u)

/* Fade time for all channels (DEV_CONFIG2) */
#define LP5814_LED_FADE_TIME_0MS_gc                               (0x00u)
#define LP5814_LED_FADE_TIME_50MS_gc                              (0x10u)
#define LP5814_LED_FADE_TIME_100MS_gc                             (0x20u)
#define LP5814_LED_FADE_TIME_150MS_gc                             (0x30u)
#define LP5814_LED_FADE_TIME_200MS_gc                             (0x40u)
#define LP5814_LED_FADE_TIME_250MS_gc                             (0x50u)
#define LP5814_LED_FADE_TIME_300MS_gc                             (0x60u)
#define LP5814_LED_FADE_TIME_350MS_gc                             (0x70u)
#define LP5814_LED_FADE_TIME_400MS_gc                             (0x80u)
#define LP5814_LED_FADE_TIME_450MS_gc                             (0x90u)
#define LP5814_LED_FADE_TIME_500MS_gc                             (0xA0u)
#define LP5814_LED_FADE_TIME_1000MS_gc                            (0xB0u)
#define LP5814_LED_FADE_TIME_2000MS_gc                            (0xC0u)
#define LP5814_LED_FADE_TIME_4000MS_gc                            (0xD0u)
#define LP5814_LED_FADE_TIME_6000MS_gc                            (0xE0u)
#define LP5814_LED_FADE_TIME_8000MS_gc                            (0xF0u)

/* Output channel -> animation engine selections (DEV_CONFIG4) */
#define LP5814_OUT0_ENGINE_CH_ENGINE0_gc                          (0x00u)
#define LP5814_OUT0_ENGINE_CH_ENGINE1_gc                          (0x01u)
#define LP5814_OUT0_ENGINE_CH_ENGINE2_gc                          (0x02u)
#define LP5814_OUT0_ENGINE_CH_ENGINE3_gc                          (0x03u)
#define LP5814_OUT1_ENGINE_CH_ENGINE0_gc                          (0x00u)
#define LP5814_OUT1_ENGINE_CH_ENGINE1_gc                          (0x04u)
#define LP5814_OUT1_ENGINE_CH_ENGINE2_gc                          (0x08u)
#define LP5814_OUT1_ENGINE_CH_ENGINE3_gc                          (0x0Cu)
#define LP5814_OUT2_ENGINE_CH_ENGINE0_gc                          (0x00u)
#define LP5814_OUT2_ENGINE_CH_ENGINE1_gc                          (0x10u)
#define LP5814_OUT2_ENGINE_CH_ENGINE2_gc                          (0x20u)
#define LP5814_OUT2_ENGINE_CH_ENGINE3_gc                          (0x30u)
#define LP5814_OUT3_ENGINE_CH_ENGINE0_gc                          (0x00u)
#define LP5814_OUT3_ENGINE_CH_ENGINE1_gc                          (0x40u)
#define LP5814_OUT3_ENGINE_CH_ENGINE2_gc                          (0x80u)
#define LP5814_OUT3_ENGINE_CH_ENGINE3_gc                          (0xC0u)

/* Engine order -> pattern selection (ENGINE_CONFIG0..3) */
#define LP5814_ENGINE0_ORDER0_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE0_ORDER0_PATTERN1_gc                         (0x01u)
#define LP5814_ENGINE0_ORDER0_PATTERN2_gc                         (0x02u)
#define LP5814_ENGINE0_ORDER0_PATTERN3_gc                         (0x03u)
#define LP5814_ENGINE0_ORDER1_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE0_ORDER1_PATTERN1_gc                         (0x04u)
#define LP5814_ENGINE0_ORDER1_PATTERN2_gc                         (0x08u)
#define LP5814_ENGINE0_ORDER1_PATTERN3_gc                         (0x0Cu)
#define LP5814_ENGINE0_ORDER2_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE0_ORDER2_PATTERN1_gc                         (0x10u)
#define LP5814_ENGINE0_ORDER2_PATTERN2_gc                         (0x20u)
#define LP5814_ENGINE0_ORDER2_PATTERN3_gc                         (0x30u)
#define LP5814_ENGINE0_ORDER3_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE0_ORDER3_PATTERN1_gc                         (0x40u)
#define LP5814_ENGINE0_ORDER3_PATTERN2_gc                         (0x80u)
#define LP5814_ENGINE0_ORDER3_PATTERN3_gc                         (0xC0u)
#define LP5814_ENGINE1_ORDER0_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE1_ORDER0_PATTERN1_gc                         (0x01u)
#define LP5814_ENGINE1_ORDER0_PATTERN2_gc                         (0x02u)
#define LP5814_ENGINE1_ORDER0_PATTERN3_gc                         (0x03u)
#define LP5814_ENGINE1_ORDER1_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE1_ORDER1_PATTERN1_gc                         (0x04u)
#define LP5814_ENGINE1_ORDER1_PATTERN2_gc                         (0x08u)
#define LP5814_ENGINE1_ORDER1_PATTERN3_gc                         (0x0Cu)
#define LP5814_ENGINE1_ORDER2_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE1_ORDER2_PATTERN1_gc                         (0x10u)
#define LP5814_ENGINE1_ORDER2_PATTERN2_gc                         (0x20u)
#define LP5814_ENGINE1_ORDER2_PATTERN3_gc                         (0x30u)
#define LP5814_ENGINE1_ORDER3_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE1_ORDER3_PATTERN1_gc                         (0x40u)
#define LP5814_ENGINE1_ORDER3_PATTERN2_gc                         (0x80u)
#define LP5814_ENGINE1_ORDER3_PATTERN3_gc                         (0xC0u)
#define LP5814_ENGINE2_ORDER0_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE2_ORDER0_PATTERN1_gc                         (0x01u)
#define LP5814_ENGINE2_ORDER0_PATTERN2_gc                         (0x02u)
#define LP5814_ENGINE2_ORDER0_PATTERN3_gc                         (0x03u)
#define LP5814_ENGINE2_ORDER1_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE2_ORDER1_PATTERN1_gc                         (0x04u)
#define LP5814_ENGINE2_ORDER1_PATTERN2_gc                         (0x08u)
#define LP5814_ENGINE2_ORDER1_PATTERN3_gc                         (0x0Cu)
#define LP5814_ENGINE2_ORDER2_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE2_ORDER2_PATTERN1_gc                         (0x10u)
#define LP5814_ENGINE2_ORDER2_PATTERN2_gc                         (0x20u)
#define LP5814_ENGINE2_ORDER2_PATTERN3_gc                         (0x30u)
#define LP5814_ENGINE2_ORDER3_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE2_ORDER3_PATTERN1_gc                         (0x40u)
#define LP5814_ENGINE2_ORDER3_PATTERN2_gc                         (0x80u)
#define LP5814_ENGINE2_ORDER3_PATTERN3_gc                         (0xC0u)
#define LP5814_ENGINE3_ORDER0_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE3_ORDER0_PATTERN1_gc                         (0x01u)
#define LP5814_ENGINE3_ORDER0_PATTERN2_gc                         (0x02u)
#define LP5814_ENGINE3_ORDER0_PATTERN3_gc                         (0x03u)
#define LP5814_ENGINE3_ORDER1_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE3_ORDER1_PATTERN1_gc                         (0x04u)
#define LP5814_ENGINE3_ORDER1_PATTERN2_gc                         (0x08u)
#define LP5814_ENGINE3_ORDER1_PATTERN3_gc                         (0x0Cu)
#define LP5814_ENGINE3_ORDER2_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE3_ORDER2_PATTERN1_gc                         (0x10u)
#define LP5814_ENGINE3_ORDER2_PATTERN2_gc                         (0x20u)
#define LP5814_ENGINE3_ORDER2_PATTERN3_gc                         (0x30u)
#define LP5814_ENGINE3_ORDER3_PATTERN0_gc                         (0x00u)
#define LP5814_ENGINE3_ORDER3_PATTERN1_gc                         (0x40u)
#define LP5814_ENGINE3_ORDER3_PATTERN2_gc                         (0x80u)
#define LP5814_ENGINE3_ORDER3_PATTERN3_gc                         (0xC0u)

/* Engine repeat count (ENGINE_CONFIG6): 3 means infinite */
#define LP5814_ENGINE0_REPT_NONE_gc                               (0x00u)
#define LP5814_ENGINE0_REPT_ONCE_gc                               (0x01u)
#define LP5814_ENGINE0_REPT_TWICE_gc                              (0x02u)
#define LP5814_ENGINE0_REPT_INFINITE_gc                           (0x03u)
#define LP5814_ENGINE1_REPT_NONE_gc                               (0x00u)
#define LP5814_ENGINE1_REPT_ONCE_gc                               (0x04u)
#define LP5814_ENGINE1_REPT_TWICE_gc                              (0x08u)
#define LP5814_ENGINE1_REPT_INFINITE_gc                           (0x0Cu)
#define LP5814_ENGINE2_REPT_NONE_gc                               (0x00u)
#define LP5814_ENGINE2_REPT_ONCE_gc                               (0x10u)
#define LP5814_ENGINE2_REPT_TWICE_gc                              (0x20u)
#define LP5814_ENGINE2_REPT_INFINITE_gc                           (0x30u)
#define LP5814_ENGINE3_REPT_NONE_gc                               (0x00u)
#define LP5814_ENGINE3_REPT_ONCE_gc                               (0x40u)
#define LP5814_ENGINE3_REPT_TWICE_gc                              (0x80u)
#define LP5814_ENGINE3_REPT_INFINITE_gc                           (0xC0u)

/* Pattern repeat count: 0..14 or infinite (0xF) */
#define LP5814_PATTERN0_PT_REPEAT0_gc                             (0x00u)
#define LP5814_PATTERN0_PT_REPEAT1_gc                             (0x01u)
#define LP5814_PATTERN0_PT_REPEAT2_gc                             (0x02u)
#define LP5814_PATTERN0_PT_REPEAT3_gc                             (0x03u)
#define LP5814_PATTERN0_PT_REPEAT4_gc                             (0x04u)
#define LP5814_PATTERN0_PT_REPEAT5_gc                             (0x05u)
#define LP5814_PATTERN0_PT_REPEAT6_gc                             (0x06u)
#define LP5814_PATTERN0_PT_REPEAT7_gc                             (0x07u)
#define LP5814_PATTERN0_PT_REPEAT8_gc                             (0x08u)
#define LP5814_PATTERN0_PT_REPEAT9_gc                             (0x09u)
#define LP5814_PATTERN0_PT_REPEAT10_gc                            (0x0Au)
#define LP5814_PATTERN0_PT_REPEAT11_gc                            (0x0Bu)
#define LP5814_PATTERN0_PT_REPEAT12_gc                            (0x0Cu)
#define LP5814_PATTERN0_PT_REPEAT13_gc                            (0x0Du)
#define LP5814_PATTERN0_PT_REPEAT14_gc                            (0x0Eu)
#define LP5814_PATTERN0_PT_INFINITE_gc                            (0x0Fu)
#define LP5814_PATTERN1_PT_REPEAT0_gc                             (0x00u)
#define LP5814_PATTERN1_PT_REPEAT1_gc                             (0x01u)
#define LP5814_PATTERN1_PT_REPEAT2_gc                             (0x02u)
#define LP5814_PATTERN1_PT_REPEAT3_gc                             (0x03u)
#define LP5814_PATTERN1_PT_REPEAT4_gc                             (0x04u)
#define LP5814_PATTERN1_PT_REPEAT5_gc                             (0x05u)
#define LP5814_PATTERN1_PT_REPEAT6_gc                             (0x06u)
#define LP5814_PATTERN1_PT_REPEAT7_gc                             (0x07u)
#define LP5814_PATTERN1_PT_REPEAT8_gc                             (0x08u)
#define LP5814_PATTERN1_PT_REPEAT9_gc                             (0x09u)
#define LP5814_PATTERN1_PT_REPEAT10_gc                            (0x0Au)
#define LP5814_PATTERN1_PT_REPEAT11_gc                            (0x0Bu)
#define LP5814_PATTERN1_PT_REPEAT12_gc                            (0x0Cu)
#define LP5814_PATTERN1_PT_REPEAT13_gc                            (0x0Du)
#define LP5814_PATTERN1_PT_REPEAT14_gc                            (0x0Eu)
#define LP5814_PATTERN1_PT_INFINITE_gc                            (0x0Fu)
#define LP5814_PATTERN2_PT_REPEAT0_gc                             (0x00u)
#define LP5814_PATTERN2_PT_REPEAT1_gc                             (0x01u)
#define LP5814_PATTERN2_PT_REPEAT2_gc                             (0x02u)
#define LP5814_PATTERN2_PT_REPEAT3_gc                             (0x03u)
#define LP5814_PATTERN2_PT_REPEAT4_gc                             (0x04u)
#define LP5814_PATTERN2_PT_REPEAT5_gc                             (0x05u)
#define LP5814_PATTERN2_PT_REPEAT6_gc                             (0x06u)
#define LP5814_PATTERN2_PT_REPEAT7_gc                             (0x07u)
#define LP5814_PATTERN2_PT_REPEAT8_gc                             (0x08u)
#define LP5814_PATTERN2_PT_REPEAT9_gc                             (0x09u)
#define LP5814_PATTERN2_PT_REPEAT10_gc                            (0x0Au)
#define LP5814_PATTERN2_PT_REPEAT11_gc                            (0x0Bu)
#define LP5814_PATTERN2_PT_REPEAT12_gc                            (0x0Cu)
#define LP5814_PATTERN2_PT_REPEAT13_gc                            (0x0Du)
#define LP5814_PATTERN2_PT_REPEAT14_gc                            (0x0Eu)
#define LP5814_PATTERN2_PT_INFINITE_gc                            (0x0Fu)
#define LP5814_PATTERN3_PT_REPEAT0_gc                             (0x00u)
#define LP5814_PATTERN3_PT_REPEAT1_gc                             (0x01u)
#define LP5814_PATTERN3_PT_REPEAT2_gc                             (0x02u)
#define LP5814_PATTERN3_PT_REPEAT3_gc                             (0x03u)
#define LP5814_PATTERN3_PT_REPEAT4_gc                             (0x04u)
#define LP5814_PATTERN3_PT_REPEAT5_gc                             (0x05u)
#define LP5814_PATTERN3_PT_REPEAT6_gc                             (0x06u)
#define LP5814_PATTERN3_PT_REPEAT7_gc                             (0x07u)
#define LP5814_PATTERN3_PT_REPEAT8_gc                             (0x08u)
#define LP5814_PATTERN3_PT_REPEAT9_gc                             (0x09u)
#define LP5814_PATTERN3_PT_REPEAT10_gc                            (0x0Au)
#define LP5814_PATTERN3_PT_REPEAT11_gc                            (0x0Bu)
#define LP5814_PATTERN3_PT_REPEAT12_gc                            (0x0Cu)
#define LP5814_PATTERN3_PT_REPEAT13_gc                            (0x0Du)
#define LP5814_PATTERN3_PT_REPEAT14_gc                            (0x0Eu)
#define LP5814_PATTERN3_PT_INFINITE_gc                            (0x0Fu)

/* Pattern pause and sloper timings (PATTERN0..3) */
#define LP5814_PATTERN0_PAUSE_T0_0MS_gc                           (0x00u)
#define LP5814_PATTERN0_PAUSE_T0_50MS_gc                          (0x10u)
#define LP5814_PATTERN0_PAUSE_T0_100MS_gc                         (0x20u)
#define LP5814_PATTERN0_PAUSE_T0_150MS_gc                         (0x30u)
#define LP5814_PATTERN0_PAUSE_T0_200MS_gc                         (0x40u)
#define LP5814_PATTERN0_PAUSE_T0_250MS_gc                         (0x50u)
#define LP5814_PATTERN0_PAUSE_T0_300MS_gc                         (0x60u)
#define LP5814_PATTERN0_PAUSE_T0_350MS_gc                         (0x70u)
#define LP5814_PATTERN0_PAUSE_T0_400MS_gc                         (0x80u)
#define LP5814_PATTERN0_PAUSE_T0_450MS_gc                         (0x90u)
#define LP5814_PATTERN0_PAUSE_T0_500MS_gc                         (0xA0u)
#define LP5814_PATTERN0_PAUSE_T0_1000MS_gc                        (0xB0u)
#define LP5814_PATTERN0_PAUSE_T0_2000MS_gc                        (0xC0u)
#define LP5814_PATTERN0_PAUSE_T0_4000MS_gc                        (0xD0u)
#define LP5814_PATTERN0_PAUSE_T0_6000MS_gc                        (0xE0u)
#define LP5814_PATTERN0_PAUSE_T0_8000MS_gc                        (0xF0u)
#define LP5814_PATTERN0_PAUSE_T1_0MS_gc                           (0x00u)
#define LP5814_PATTERN0_PAUSE_T1_50MS_gc                          (0x01u)
#define LP5814_PATTERN0_PAUSE_T1_100MS_gc                         (0x02u)
#define LP5814_PATTERN0_PAUSE_T1_150MS_gc                         (0x03u)
#define LP5814_PATTERN0_PAUSE_T1_200MS_gc                         (0x04u)
#define LP5814_PATTERN0_PAUSE_T1_250MS_gc                         (0x05u)
#define LP5814_PATTERN0_PAUSE_T1_300MS_gc                         (0x06u)
#define LP5814_PATTERN0_PAUSE_T1_350MS_gc                         (0x07u)
#define LP5814_PATTERN0_PAUSE_T1_400MS_gc                         (0x08u)
#define LP5814_PATTERN0_PAUSE_T1_450MS_gc                         (0x09u)
#define LP5814_PATTERN0_PAUSE_T1_500MS_gc                         (0x0Au)
#define LP5814_PATTERN0_PAUSE_T1_1000MS_gc                        (0x0Bu)
#define LP5814_PATTERN0_PAUSE_T1_2000MS_gc                        (0x0Cu)
#define LP5814_PATTERN0_PAUSE_T1_4000MS_gc                        (0x0Du)
#define LP5814_PATTERN0_PAUSE_T1_6000MS_gc                        (0x0Eu)
#define LP5814_PATTERN0_PAUSE_T1_8000MS_gc                        (0x0Fu)
#define LP5814_PATTERN0_SLOPER_T0_0MS_gc                          (0x00u)
#define LP5814_PATTERN0_SLOPER_T0_50MS_gc                         (0x01u)
#define LP5814_PATTERN0_SLOPER_T0_100MS_gc                        (0x02u)
#define LP5814_PATTERN0_SLOPER_T0_150MS_gc                        (0x03u)
#define LP5814_PATTERN0_SLOPER_T0_200MS_gc                        (0x04u)
#define LP5814_PATTERN0_SLOPER_T0_250MS_gc                        (0x05u)
#define LP5814_PATTERN0_SLOPER_T0_300MS_gc                        (0x06u)
#define LP5814_PATTERN0_SLOPER_T0_350MS_gc                        (0x07u)
#define LP5814_PATTERN0_SLOPER_T0_400MS_gc                        (0x08u)
#define LP5814_PATTERN0_SLOPER_T0_450MS_gc                        (0x09u)
#define LP5814_PATTERN0_SLOPER_T0_500MS_gc                        (0x0Au)
#define LP5814_PATTERN0_SLOPER_T0_1000MS_gc                       (0x0Bu)
#define LP5814_PATTERN0_SLOPER_T0_2000MS_gc                       (0x0Cu)
#define LP5814_PATTERN0_SLOPER_T0_4000MS_gc                       (0x0Du)
#define LP5814_PATTERN0_SLOPER_T0_6000MS_gc                       (0x0Eu)
#define LP5814_PATTERN0_SLOPER_T0_8000MS_gc                       (0x0Fu)
#define LP5814_PATTERN0_SLOPER_T1_0MS_gc                          (0x00u)
#define LP5814_PATTERN0_SLOPER_T1_50MS_gc                         (0x10u)
#define LP5814_PATTERN0_SLOPER_T1_100MS_gc                        (0x20u)
#define LP5814_PATTERN0_SLOPER_T1_150MS_gc                        (0x30u)
#define LP5814_PATTERN0_SLOPER_T1_200MS_gc                        (0x40u)
#define LP5814_PATTERN0_SLOPER_T1_250MS_gc                        (0x50u)
#define LP5814_PATTERN0_SLOPER_T1_300MS_gc                        (0x60u)
#define LP5814_PATTERN0_SLOPER_T1_350MS_gc                        (0x70u)
#define LP5814_PATTERN0_SLOPER_T1_400MS_gc                        (0x80u)
#define LP5814_PATTERN0_SLOPER_T1_450MS_gc                        (0x90u)
#define LP5814_PATTERN0_SLOPER_T1_500MS_gc                        (0xA0u)
#define LP5814_PATTERN0_SLOPER_T1_1000MS_gc                       (0xB0u)
#define LP5814_PATTERN0_SLOPER_T1_2000MS_gc                       (0xC0u)
#define LP5814_PATTERN0_SLOPER_T1_4000MS_gc                       (0xD0u)
#define LP5814_PATTERN0_SLOPER_T1_6000MS_gc                       (0xE0u)
#define LP5814_PATTERN0_SLOPER_T1_8000MS_gc                       (0xF0u)
#define LP5814_PATTERN0_SLOPER_T2_0MS_gc                          (0x00u)
#define LP5814_PATTERN0_SLOPER_T2_50MS_gc                         (0x01u)
#define LP5814_PATTERN0_SLOPER_T2_100MS_gc                        (0x02u)
#define LP5814_PATTERN0_SLOPER_T2_150MS_gc                        (0x03u)
#define LP5814_PATTERN0_SLOPER_T2_200MS_gc                        (0x04u)
#define LP5814_PATTERN0_SLOPER_T2_250MS_gc                        (0x05u)
#define LP5814_PATTERN0_SLOPER_T2_300MS_gc                        (0x06u)
#define LP5814_PATTERN0_SLOPER_T2_350MS_gc                        (0x07u)
#define LP5814_PATTERN0_SLOPER_T2_400MS_gc                        (0x08u)
#define LP5814_PATTERN0_SLOPER_T2_450MS_gc                        (0x09u)
#define LP5814_PATTERN0_SLOPER_T2_500MS_gc                        (0x0Au)
#define LP5814_PATTERN0_SLOPER_T2_1000MS_gc                       (0x0Bu)
#define LP5814_PATTERN0_SLOPER_T2_2000MS_gc                       (0x0Cu)
#define LP5814_PATTERN0_SLOPER_T2_4000MS_gc                       (0x0Du)
#define LP5814_PATTERN0_SLOPER_T2_6000MS_gc                       (0x0Eu)
#define LP5814_PATTERN0_SLOPER_T2_8000MS_gc                       (0x0Fu)
#define LP5814_PATTERN0_SLOPER_T3_0MS_gc                          (0x00u)
#define LP5814_PATTERN0_SLOPER_T3_50MS_gc                         (0x10u)
#define LP5814_PATTERN0_SLOPER_T3_100MS_gc                        (0x20u)
#define LP5814_PATTERN0_SLOPER_T3_150MS_gc                        (0x30u)
#define LP5814_PATTERN0_SLOPER_T3_200MS_gc                        (0x40u)
#define LP5814_PATTERN0_SLOPER_T3_250MS_gc                        (0x50u)
#define LP5814_PATTERN0_SLOPER_T3_300MS_gc                        (0x60u)
#define LP5814_PATTERN0_SLOPER_T3_350MS_gc                        (0x70u)
#define LP5814_PATTERN0_SLOPER_T3_400MS_gc                        (0x80u)
#define LP5814_PATTERN0_SLOPER_T3_450MS_gc                        (0x90u)
#define LP5814_PATTERN0_SLOPER_T3_500MS_gc                        (0xA0u)
#define LP5814_PATTERN0_SLOPER_T3_1000MS_gc                       (0xB0u)
#define LP5814_PATTERN0_SLOPER_T3_2000MS_gc                       (0xC0u)
#define LP5814_PATTERN0_SLOPER_T3_4000MS_gc                       (0xD0u)
#define LP5814_PATTERN0_SLOPER_T3_6000MS_gc                       (0xE0u)
#define LP5814_PATTERN0_SLOPER_T3_8000MS_gc                       (0xF0u)
#define LP5814_PATTERN1_PAUSE_T0_0MS_gc                           (0x00u)
#define LP5814_PATTERN1_PAUSE_T0_50MS_gc                          (0x10u)
#define LP5814_PATTERN1_PAUSE_T0_100MS_gc                         (0x20u)
#define LP5814_PATTERN1_PAUSE_T0_150MS_gc                         (0x30u)
#define LP5814_PATTERN1_PAUSE_T0_200MS_gc                         (0x40u)
#define LP5814_PATTERN1_PAUSE_T0_250MS_gc                         (0x50u)
#define LP5814_PATTERN1_PAUSE_T0_300MS_gc                         (0x60u)
#define LP5814_PATTERN1_PAUSE_T0_350MS_gc                         (0x70u)
#define LP5814_PATTERN1_PAUSE_T0_400MS_gc                         (0x80u)
#define LP5814_PATTERN1_PAUSE_T0_450MS_gc                         (0x90u)
#define LP5814_PATTERN1_PAUSE_T0_500MS_gc                         (0xA0u)
#define LP5814_PATTERN1_PAUSE_T0_1000MS_gc                        (0xB0u)
#define LP5814_PATTERN1_PAUSE_T0_2000MS_gc                        (0xC0u)
#define LP5814_PATTERN1_PAUSE_T0_4000MS_gc                        (0xD0u)
#define LP5814_PATTERN1_PAUSE_T0_6000MS_gc                        (0xE0u)
#define LP5814_PATTERN1_PAUSE_T0_8000MS_gc                        (0xF0u)
#define LP5814_PATTERN1_PAUSE_T1_0MS_gc                           (0x00u)
#define LP5814_PATTERN1_PAUSE_T1_50MS_gc                          (0x01u)
#define LP5814_PATTERN1_PAUSE_T1_100MS_gc                         (0x02u)
#define LP5814_PATTERN1_PAUSE_T1_150MS_gc                         (0x03u)
#define LP5814_PATTERN1_PAUSE_T1_200MS_gc                         (0x04u)
#define LP5814_PATTERN1_PAUSE_T1_250MS_gc                         (0x05u)
#define LP5814_PATTERN1_PAUSE_T1_300MS_gc                         (0x06u)
#define LP5814_PATTERN1_PAUSE_T1_350MS_gc                         (0x07u)
#define LP5814_PATTERN1_PAUSE_T1_400MS_gc                         (0x08u)
#define LP5814_PATTERN1_PAUSE_T1_450MS_gc                         (0x09u)
#define LP5814_PATTERN1_PAUSE_T1_500MS_gc                         (0x0Au)
#define LP5814_PATTERN1_PAUSE_T1_1000MS_gc                        (0x0Bu)
#define LP5814_PATTERN1_PAUSE_T1_2000MS_gc                        (0x0Cu)
#define LP5814_PATTERN1_PAUSE_T1_4000MS_gc                        (0x0Du)
#define LP5814_PATTERN1_PAUSE_T1_6000MS_gc                        (0x0Eu)
#define LP5814_PATTERN1_PAUSE_T1_8000MS_gc                        (0x0Fu)
#define LP5814_PATTERN1_SLOPER_T0_0MS_gc                          (0x00u)
#define LP5814_PATTERN1_SLOPER_T0_50MS_gc                         (0x01u)
#define LP5814_PATTERN1_SLOPER_T0_100MS_gc                        (0x02u)
#define LP5814_PATTERN1_SLOPER_T0_150MS_gc                        (0x03u)
#define LP5814_PATTERN1_SLOPER_T0_200MS_gc                        (0x04u)
#define LP5814_PATTERN1_SLOPER_T0_250MS_gc                        (0x05u)
#define LP5814_PATTERN1_SLOPER_T0_300MS_gc                        (0x06u)
#define LP5814_PATTERN1_SLOPER_T0_350MS_gc                        (0x07u)
#define LP5814_PATTERN1_SLOPER_T0_400MS_gc                        (0x08u)
#define LP5814_PATTERN1_SLOPER_T0_450MS_gc                        (0x09u)
#define LP5814_PATTERN1_SLOPER_T0_500MS_gc                        (0x0Au)
#define LP5814_PATTERN1_SLOPER_T0_1000MS_gc                       (0x0Bu)
#define LP5814_PATTERN1_SLOPER_T0_2000MS_gc                       (0x0Cu)
#define LP5814_PATTERN1_SLOPER_T0_4000MS_gc                       (0x0Du)
#define LP5814_PATTERN1_SLOPER_T0_6000MS_gc                       (0x0Eu)
#define LP5814_PATTERN1_SLOPER_T0_8000MS_gc                       (0x0Fu)
#define LP5814_PATTERN1_SLOPER_T1_0MS_gc                          (0x00u)
#define LP5814_PATTERN1_SLOPER_T1_50MS_gc                         (0x10u)
#define LP5814_PATTERN1_SLOPER_T1_100MS_gc                        (0x20u)
#define LP5814_PATTERN1_SLOPER_T1_150MS_gc                        (0x30u)
#define LP5814_PATTERN1_SLOPER_T1_200MS_gc                        (0x40u)
#define LP5814_PATTERN1_SLOPER_T1_250MS_gc                        (0x50u)
#define LP5814_PATTERN1_SLOPER_T1_300MS_gc                        (0x60u)
#define LP5814_PATTERN1_SLOPER_T1_350MS_gc                        (0x70u)
#define LP5814_PATTERN1_SLOPER_T1_400MS_gc                        (0x80u)
#define LP5814_PATTERN1_SLOPER_T1_450MS_gc                        (0x90u)
#define LP5814_PATTERN1_SLOPER_T1_500MS_gc                        (0xA0u)
#define LP5814_PATTERN1_SLOPER_T1_1000MS_gc                       (0xB0u)
#define LP5814_PATTERN1_SLOPER_T1_2000MS_gc                       (0xC0u)
#define LP5814_PATTERN1_SLOPER_T1_4000MS_gc                       (0xD0u)
#define LP5814_PATTERN1_SLOPER_T1_6000MS_gc                       (0xE0u)
#define LP5814_PATTERN1_SLOPER_T1_8000MS_gc                       (0xF0u)
#define LP5814_PATTERN1_SLOPER_T2_0MS_gc                          (0x00u)
#define LP5814_PATTERN1_SLOPER_T2_50MS_gc                         (0x01u)
#define LP5814_PATTERN1_SLOPER_T2_100MS_gc                        (0x02u)
#define LP5814_PATTERN1_SLOPER_T2_150MS_gc                        (0x03u)
#define LP5814_PATTERN1_SLOPER_T2_200MS_gc                        (0x04u)
#define LP5814_PATTERN1_SLOPER_T2_250MS_gc                        (0x05u)
#define LP5814_PATTERN1_SLOPER_T2_300MS_gc                        (0x06u)
#define LP5814_PATTERN1_SLOPER_T2_350MS_gc                        (0x07u)
#define LP5814_PATTERN1_SLOPER_T2_400MS_gc                        (0x08u)
#define LP5814_PATTERN1_SLOPER_T2_450MS_gc                        (0x09u)
#define LP5814_PATTERN1_SLOPER_T2_500MS_gc                        (0x0Au)
#define LP5814_PATTERN1_SLOPER_T2_1000MS_gc                       (0x0Bu)
#define LP5814_PATTERN1_SLOPER_T2_2000MS_gc                       (0x0Cu)
#define LP5814_PATTERN1_SLOPER_T2_4000MS_gc                       (0x0Du)
#define LP5814_PATTERN1_SLOPER_T2_6000MS_gc                       (0x0Eu)
#define LP5814_PATTERN1_SLOPER_T2_8000MS_gc                       (0x0Fu)
#define LP5814_PATTERN1_SLOPER_T3_0MS_gc                          (0x00u)
#define LP5814_PATTERN1_SLOPER_T3_50MS_gc                         (0x10u)
#define LP5814_PATTERN1_SLOPER_T3_100MS_gc                        (0x20u)
#define LP5814_PATTERN1_SLOPER_T3_150MS_gc                        (0x30u)
#define LP5814_PATTERN1_SLOPER_T3_200MS_gc                        (0x40u)
#define LP5814_PATTERN1_SLOPER_T3_250MS_gc                        (0x50u)
#define LP5814_PATTERN1_SLOPER_T3_300MS_gc                        (0x60u)
#define LP5814_PATTERN1_SLOPER_T3_350MS_gc                        (0x70u)
#define LP5814_PATTERN1_SLOPER_T3_400MS_gc                        (0x80u)
#define LP5814_PATTERN1_SLOPER_T3_450MS_gc                        (0x90u)
#define LP5814_PATTERN1_SLOPER_T3_500MS_gc                        (0xA0u)
#define LP5814_PATTERN1_SLOPER_T3_1000MS_gc                       (0xB0u)
#define LP5814_PATTERN1_SLOPER_T3_2000MS_gc                       (0xC0u)
#define LP5814_PATTERN1_SLOPER_T3_4000MS_gc                       (0xD0u)
#define LP5814_PATTERN1_SLOPER_T3_6000MS_gc                       (0xE0u)
#define LP5814_PATTERN1_SLOPER_T3_8000MS_gc                       (0xF0u)
#define LP5814_PATTERN2_PAUSE_T0_0MS_gc                           (0x00u)
#define LP5814_PATTERN2_PAUSE_T0_50MS_gc                          (0x10u)
#define LP5814_PATTERN2_PAUSE_T0_100MS_gc                         (0x20u)
#define LP5814_PATTERN2_PAUSE_T0_150MS_gc                         (0x30u)
#define LP5814_PATTERN2_PAUSE_T0_200MS_gc                         (0x40u)
#define LP5814_PATTERN2_PAUSE_T0_250MS_gc                         (0x50u)
#define LP5814_PATTERN2_PAUSE_T0_300MS_gc                         (0x60u)
#define LP5814_PATTERN2_PAUSE_T0_350MS_gc                         (0x70u)
#define LP5814_PATTERN2_PAUSE_T0_400MS_gc                         (0x80u)
#define LP5814_PATTERN2_PAUSE_T0_450MS_gc                         (0x90u)
#define LP5814_PATTERN2_PAUSE_T0_500MS_gc                         (0xA0u)
#define LP5814_PATTERN2_PAUSE_T0_1000MS_gc                        (0xB0u)
#define LP5814_PATTERN2_PAUSE_T0_2000MS_gc                        (0xC0u)
#define LP5814_PATTERN2_PAUSE_T0_4000MS_gc                        (0xD0u)
#define LP5814_PATTERN2_PAUSE_T0_6000MS_gc                        (0xE0u)
#define LP5814_PATTERN2_PAUSE_T0_8000MS_gc                        (0xF0u)
#define LP5814_PATTERN2_PAUSE_T1_0MS_gc                           (0x00u)
#define LP5814_PATTERN2_PAUSE_T1_50MS_gc                          (0x01u)
#define LP5814_PATTERN2_PAUSE_T1_100MS_gc                         (0x02u)
#define LP5814_PATTERN2_PAUSE_T1_150MS_gc                         (0x03u)
#define LP5814_PATTERN2_PAUSE_T1_200MS_gc                         (0x04u)
#define LP5814_PATTERN2_PAUSE_T1_250MS_gc                         (0x05u)
#define LP5814_PATTERN2_PAUSE_T1_300MS_gc                         (0x06u)
#define LP5814_PATTERN2_PAUSE_T1_350MS_gc                         (0x07u)
#define LP5814_PATTERN2_PAUSE_T1_400MS_gc                         (0x08u)
#define LP5814_PATTERN2_PAUSE_T1_450MS_gc                         (0x09u)
#define LP5814_PATTERN2_PAUSE_T1_500MS_gc                         (0x0Au)
#define LP5814_PATTERN2_PAUSE_T1_1000MS_gc                        (0x0Bu)
#define LP5814_PATTERN2_PAUSE_T1_2000MS_gc                        (0x0Cu)
#define LP5814_PATTERN2_PAUSE_T1_4000MS_gc                        (0x0Du)
#define LP5814_PATTERN2_PAUSE_T1_6000MS_gc                        (0x0Eu)
#define LP5814_PATTERN2_PAUSE_T1_8000MS_gc                        (0x0Fu)
#define LP5814_PATTERN2_SLOPER_T0_0MS_gc                          (0x00u)
#define LP5814_PATTERN2_SLOPER_T0_50MS_gc                         (0x01u)
#define LP5814_PATTERN2_SLOPER_T0_100MS_gc                        (0x02u)
#define LP5814_PATTERN2_SLOPER_T0_150MS_gc                        (0x03u)
#define LP5814_PATTERN2_SLOPER_T0_200MS_gc                        (0x04u)
#define LP5814_PATTERN2_SLOPER_T0_250MS_gc                        (0x05u)
#define LP5814_PATTERN2_SLOPER_T0_300MS_gc                        (0x06u)
#define LP5814_PATTERN2_SLOPER_T0_350MS_gc                        (0x07u)
#define LP5814_PATTERN2_SLOPER_T0_400MS_gc                        (0x08u)
#define LP5814_PATTERN2_SLOPER_T0_450MS_gc                        (0x09u)
#define LP5814_PATTERN2_SLOPER_T0_500MS_gc                        (0x0Au)
#define LP5814_PATTERN2_SLOPER_T0_1000MS_gc                       (0x0Bu)
#define LP5814_PATTERN2_SLOPER_T0_2000MS_gc                       (0x0Cu)
#define LP5814_PATTERN2_SLOPER_T0_4000MS_gc                       (0x0Du)
#define LP5814_PATTERN2_SLOPER_T0_6000MS_gc                       (0x0Eu)
#define LP5814_PATTERN2_SLOPER_T0_8000MS_gc                       (0x0Fu)
#define LP5814_PATTERN2_SLOPER_T1_0MS_gc                          (0x00u)
#define LP5814_PATTERN2_SLOPER_T1_50MS_gc                         (0x10u)
#define LP5814_PATTERN2_SLOPER_T1_100MS_gc                        (0x20u)
#define LP5814_PATTERN2_SLOPER_T1_150MS_gc                        (0x30u)
#define LP5814_PATTERN2_SLOPER_T1_200MS_gc                        (0x40u)
#define LP5814_PATTERN2_SLOPER_T1_250MS_gc                        (0x50u)
#define LP5814_PATTERN2_SLOPER_T1_300MS_gc                        (0x60u)
#define LP5814_PATTERN2_SLOPER_T1_350MS_gc                        (0x70u)
#define LP5814_PATTERN2_SLOPER_T1_400MS_gc                        (0x80u)
#define LP5814_PATTERN2_SLOPER_T1_450MS_gc                        (0x90u)
#define LP5814_PATTERN2_SLOPER_T1_500MS_gc                        (0xA0u)
#define LP5814_PATTERN2_SLOPER_T1_1000MS_gc                       (0xB0u)
#define LP5814_PATTERN2_SLOPER_T1_2000MS_gc                       (0xC0u)
#define LP5814_PATTERN2_SLOPER_T1_4000MS_gc                       (0xD0u)
#define LP5814_PATTERN2_SLOPER_T1_6000MS_gc                       (0xE0u)
#define LP5814_PATTERN2_SLOPER_T1_8000MS_gc                       (0xF0u)
#define LP5814_PATTERN2_SLOPER_T2_0MS_gc                          (0x00u)
#define LP5814_PATTERN2_SLOPER_T2_50MS_gc                         (0x01u)
#define LP5814_PATTERN2_SLOPER_T2_100MS_gc                        (0x02u)
#define LP5814_PATTERN2_SLOPER_T2_150MS_gc                        (0x03u)
#define LP5814_PATTERN2_SLOPER_T2_200MS_gc                        (0x04u)
#define LP5814_PATTERN2_SLOPER_T2_250MS_gc                        (0x05u)
#define LP5814_PATTERN2_SLOPER_T2_300MS_gc                        (0x06u)
#define LP5814_PATTERN2_SLOPER_T2_350MS_gc                        (0x07u)
#define LP5814_PATTERN2_SLOPER_T2_400MS_gc                        (0x08u)
#define LP5814_PATTERN2_SLOPER_T2_450MS_gc                        (0x09u)
#define LP5814_PATTERN2_SLOPER_T2_500MS_gc                        (0x0Au)
#define LP5814_PATTERN2_SLOPER_T2_1000MS_gc                       (0x0Bu)
#define LP5814_PATTERN2_SLOPER_T2_2000MS_gc                       (0x0Cu)
#define LP5814_PATTERN2_SLOPER_T2_4000MS_gc                       (0x0Du)
#define LP5814_PATTERN2_SLOPER_T2_6000MS_gc                       (0x0Eu)
#define LP5814_PATTERN2_SLOPER_T2_8000MS_gc                       (0x0Fu)
#define LP5814_PATTERN2_SLOPER_T3_0MS_gc                          (0x00u)
#define LP5814_PATTERN2_SLOPER_T3_50MS_gc                         (0x10u)
#define LP5814_PATTERN2_SLOPER_T3_100MS_gc                        (0x20u)
#define LP5814_PATTERN2_SLOPER_T3_150MS_gc                        (0x30u)
#define LP5814_PATTERN2_SLOPER_T3_200MS_gc                        (0x40u)
#define LP5814_PATTERN2_SLOPER_T3_250MS_gc                        (0x50u)
#define LP5814_PATTERN2_SLOPER_T3_300MS_gc                        (0x60u)
#define LP5814_PATTERN2_SLOPER_T3_350MS_gc                        (0x70u)
#define LP5814_PATTERN2_SLOPER_T3_400MS_gc                        (0x80u)
#define LP5814_PATTERN2_SLOPER_T3_450MS_gc                        (0x90u)
#define LP5814_PATTERN2_SLOPER_T3_500MS_gc                        (0xA0u)
#define LP5814_PATTERN2_SLOPER_T3_1000MS_gc                       (0xB0u)
#define LP5814_PATTERN2_SLOPER_T3_2000MS_gc                       (0xC0u)
#define LP5814_PATTERN2_SLOPER_T3_4000MS_gc                       (0xD0u)
#define LP5814_PATTERN2_SLOPER_T3_6000MS_gc                       (0xE0u)
#define LP5814_PATTERN2_SLOPER_T3_8000MS_gc                       (0xF0u)
#define LP5814_PATTERN3_PAUSE_T0_0MS_gc                           (0x00u)
#define LP5814_PATTERN3_PAUSE_T0_50MS_gc                          (0x10u)
#define LP5814_PATTERN3_PAUSE_T0_100MS_gc                         (0x20u)
#define LP5814_PATTERN3_PAUSE_T0_150MS_gc                         (0x30u)
#define LP5814_PATTERN3_PAUSE_T0_200MS_gc                         (0x40u)
#define LP5814_PATTERN3_PAUSE_T0_250MS_gc                         (0x50u)
#define LP5814_PATTERN3_PAUSE_T0_300MS_gc                         (0x60u)
#define LP5814_PATTERN3_PAUSE_T0_350MS_gc                         (0x70u)
#define LP5814_PATTERN3_PAUSE_T0_400MS_gc                         (0x80u)
#define LP5814_PATTERN3_PAUSE_T0_450MS_gc                         (0x90u)
#define LP5814_PATTERN3_PAUSE_T0_500MS_gc                         (0xA0u)
#define LP5814_PATTERN3_PAUSE_T0_1000MS_gc                        (0xB0u)
#define LP5814_PATTERN3_PAUSE_T0_2000MS_gc                        (0xC0u)
#define LP5814_PATTERN3_PAUSE_T0_4000MS_gc                        (0xD0u)
#define LP5814_PATTERN3_PAUSE_T0_6000MS_gc                        (0xE0u)
#define LP5814_PATTERN3_PAUSE_T0_8000MS_gc                        (0xF0u)
#define LP5814_PATTERN3_PAUSE_T1_0MS_gc                           (0x00u)
#define LP5814_PATTERN3_PAUSE_T1_50MS_gc                          (0x01u)
#define LP5814_PATTERN3_PAUSE_T1_100MS_gc                         (0x02u)
#define LP5814_PATTERN3_PAUSE_T1_150MS_gc                         (0x03u)
#define LP5814_PATTERN3_PAUSE_T1_200MS_gc                         (0x04u)
#define LP5814_PATTERN3_PAUSE_T1_250MS_gc                         (0x05u)
#define LP5814_PATTERN3_PAUSE_T1_300MS_gc                         (0x06u)
#define LP5814_PATTERN3_PAUSE_T1_350MS_gc                         (0x07u)
#define LP5814_PATTERN3_PAUSE_T1_400MS_gc                         (0x08u)
#define LP5814_PATTERN3_PAUSE_T1_450MS_gc                         (0x09u)
#define LP5814_PATTERN3_PAUSE_T1_500MS_gc                         (0x0Au)
#define LP5814_PATTERN3_PAUSE_T1_1000MS_gc                        (0x0Bu)
#define LP5814_PATTERN3_PAUSE_T1_2000MS_gc                        (0x0Cu)
#define LP5814_PATTERN3_PAUSE_T1_4000MS_gc                        (0x0Du)
#define LP5814_PATTERN3_PAUSE_T1_6000MS_gc                        (0x0Eu)
#define LP5814_PATTERN3_PAUSE_T1_8000MS_gc                        (0x0Fu)
#define LP5814_PATTERN3_SLOPER_T0_0MS_gc                          (0x00u)
#define LP5814_PATTERN3_SLOPER_T0_50MS_gc                         (0x01u)
#define LP5814_PATTERN3_SLOPER_T0_100MS_gc                        (0x02u)
#define LP5814_PATTERN3_SLOPER_T0_150MS_gc                        (0x03u)
#define LP5814_PATTERN3_SLOPER_T0_200MS_gc                        (0x04u)
#define LP5814_PATTERN3_SLOPER_T0_250MS_gc                        (0x05u)
#define LP5814_PATTERN3_SLOPER_T0_300MS_gc                        (0x06u)
#define LP5814_PATTERN3_SLOPER_T0_350MS_gc                        (0x07u)
#define LP5814_PATTERN3_SLOPER_T0_400MS_gc                        (0x08u)
#define LP5814_PATTERN3_SLOPER_T0_450MS_gc                        (0x09u)
#define LP5814_PATTERN3_SLOPER_T0_500MS_gc                        (0x0Au)
#define LP5814_PATTERN3_SLOPER_T0_1000MS_gc                       (0x0Bu)
#define LP5814_PATTERN3_SLOPER_T0_2000MS_gc                       (0x0Cu)
#define LP5814_PATTERN3_SLOPER_T0_4000MS_gc                       (0x0Du)
#define LP5814_PATTERN3_SLOPER_T0_6000MS_gc                       (0x0Eu)
#define LP5814_PATTERN3_SLOPER_T0_8000MS_gc                       (0x0Fu)
#define LP5814_PATTERN3_SLOPER_T1_0MS_gc                          (0x00u)
#define LP5814_PATTERN3_SLOPER_T1_50MS_gc                         (0x10u)
#define LP5814_PATTERN3_SLOPER_T1_100MS_gc                        (0x20u)
#define LP5814_PATTERN3_SLOPER_T1_150MS_gc                        (0x30u)
#define LP5814_PATTERN3_SLOPER_T1_200MS_gc                        (0x40u)
#define LP5814_PATTERN3_SLOPER_T1_250MS_gc                        (0x50u)
#define LP5814_PATTERN3_SLOPER_T1_300MS_gc                        (0x60u)
#define LP5814_PATTERN3_SLOPER_T1_350MS_gc                        (0x70u)
#define LP5814_PATTERN3_SLOPER_T1_400MS_gc                        (0x80u)
#define LP5814_PATTERN3_SLOPER_T1_450MS_gc                        (0x90u)
#define LP5814_PATTERN3_SLOPER_T1_500MS_gc                        (0xA0u)
#define LP5814_PATTERN3_SLOPER_T1_1000MS_gc                       (0xB0u)
#define LP5814_PATTERN3_SLOPER_T1_2000MS_gc                       (0xC0u)
#define LP5814_PATTERN3_SLOPER_T1_4000MS_gc                       (0xD0u)
#define LP5814_PATTERN3_SLOPER_T1_6000MS_gc                       (0xE0u)
#define LP5814_PATTERN3_SLOPER_T1_8000MS_gc                       (0xF0u)
#define LP5814_PATTERN3_SLOPER_T2_0MS_gc                          (0x00u)
#define LP5814_PATTERN3_SLOPER_T2_50MS_gc                         (0x01u)
#define LP5814_PATTERN3_SLOPER_T2_100MS_gc                        (0x02u)
#define LP5814_PATTERN3_SLOPER_T2_150MS_gc                        (0x03u)
#define LP5814_PATTERN3_SLOPER_T2_200MS_gc                        (0x04u)
#define LP5814_PATTERN3_SLOPER_T2_250MS_gc                        (0x05u)
#define LP5814_PATTERN3_SLOPER_T2_300MS_gc                        (0x06u)
#define LP5814_PATTERN3_SLOPER_T2_350MS_gc                        (0x07u)
#define LP5814_PATTERN3_SLOPER_T2_400MS_gc                        (0x08u)
#define LP5814_PATTERN3_SLOPER_T2_450MS_gc                        (0x09u)
#define LP5814_PATTERN3_SLOPER_T2_500MS_gc                        (0x0Au)
#define LP5814_PATTERN3_SLOPER_T2_1000MS_gc                       (0x0Bu)
#define LP5814_PATTERN3_SLOPER_T2_2000MS_gc                       (0x0Cu)
#define LP5814_PATTERN3_SLOPER_T2_4000MS_gc                       (0x0Du)
#define LP5814_PATTERN3_SLOPER_T2_6000MS_gc                       (0x0Eu)
#define LP5814_PATTERN3_SLOPER_T2_8000MS_gc                       (0x0Fu)
#define LP5814_PATTERN3_SLOPER_T3_0MS_gc                          (0x00u)
#define LP5814_PATTERN3_SLOPER_T3_50MS_gc                         (0x10u)
#define LP5814_PATTERN3_SLOPER_T3_100MS_gc                        (0x20u)
#define LP5814_PATTERN3_SLOPER_T3_150MS_gc                        (0x30u)
#define LP5814_PATTERN3_SLOPER_T3_200MS_gc                        (0x40u)
#define LP5814_PATTERN3_SLOPER_T3_250MS_gc                        (0x50u)
#define LP5814_PATTERN3_SLOPER_T3_300MS_gc                        (0x60u)
#define LP5814_PATTERN3_SLOPER_T3_350MS_gc                        (0x70u)
#define LP5814_PATTERN3_SLOPER_T3_400MS_gc                        (0x80u)
#define LP5814_PATTERN3_SLOPER_T3_450MS_gc                        (0x90u)
#define LP5814_PATTERN3_SLOPER_T3_500MS_gc                        (0xA0u)
#define LP5814_PATTERN3_SLOPER_T3_1000MS_gc                       (0xB0u)
#define LP5814_PATTERN3_SLOPER_T3_2000MS_gc                       (0xC0u)
#define LP5814_PATTERN3_SLOPER_T3_4000MS_gc                       (0xD0u)
#define LP5814_PATTERN3_SLOPER_T3_6000MS_gc                       (0xE0u)
#define LP5814_PATTERN3_SLOPER_T3_8000MS_gc                       (0xF0u)

/* ---------------------------------------------------------------------------
 *  Field helpers. Pass an unqualified field name WITHOUT _bp/_bm suffix.
 *  Example: LP5814_FIELD_PREP(OUT3_ENGINE_CH, LP5814_ENGINE_2)
 *  With LP5814_NO_SHORT_NAMES:
 *    LP5814_FIELD_PREP(LP5814_OUT3_ENGINE_CH, LP5814_ENGINE_2)
 *  Input values are masked to the width of the selected bitfield.
 * --------------------------------------------------------------------------- */
#define LP5814_FIELD_PREP(field, value) \
    ((uint8_t)((((uint8_t)(value)) << field##_bp) & field##_bm))
#define LP5814_FIELD_GET(field, reg_value) \
    ((uint8_t)((((uint8_t)(reg_value)) & field##_bm) >> field##_bp))
#define LP5814_FIELD_REPLACE(field, reg_value, value) \
    ((uint8_t)((((uint8_t)(reg_value)) & (uint8_t)~field##_bm) | \
               LP5814_FIELD_PREP(field, value)))

/* ---------------------------------------------------------------------------
 *  Optional short datasheet acronyms. These are ON by default.
 *  For integration with other drivers, define LP5814_NO_SHORT_NAMES.
 * --------------------------------------------------------------------------- */
#ifndef LP5814_NO_SHORT_NAMES

/* Register names */
#define CHIP_EN                        LP5814_REG_CHIP_EN
#define DEV_CONFIG0                    LP5814_REG_DEV_CONFIG0
#define DEV_CONFIG1                    LP5814_REG_DEV_CONFIG1
#define DEV_CONFIG2                    LP5814_REG_DEV_CONFIG2
#define DEV_CONFIG3                    LP5814_REG_DEV_CONFIG3
#define DEV_CONFIG4                    LP5814_REG_DEV_CONFIG4
#define ENGINE_CONFIG0                 LP5814_REG_ENGINE_CONFIG0
#define ENGINE_CONFIG1                 LP5814_REG_ENGINE_CONFIG1
#define ENGINE_CONFIG2                 LP5814_REG_ENGINE_CONFIG2
#define ENGINE_CONFIG3                 LP5814_REG_ENGINE_CONFIG3
#define ENGINE_CONFIG4                 LP5814_REG_ENGINE_CONFIG4
#define ENGINE_CONFIG5                 LP5814_REG_ENGINE_CONFIG5
#define ENGINE_CONFIG6                 LP5814_REG_ENGINE_CONFIG6
#define SHUTDOWN_CMD                   LP5814_REG_SHUTDOWN_CMD
#define RESET_CMD                      LP5814_REG_RESET_CMD
#define UPDATE_CMD                     LP5814_REG_UPDATE_CMD
#define START_CMD                      LP5814_REG_START_CMD
#define STOP_CMD                       LP5814_REG_STOP_CMD
#define PAUSE_CONTINUE                 LP5814_REG_PAUSE_CONTINUE
#define FLAG_CLR                       LP5814_REG_FLAG_CLR
#define OUT0_DC                        LP5814_REG_OUT0_DC
#define OUT1_DC                        LP5814_REG_OUT1_DC
#define OUT2_DC                        LP5814_REG_OUT2_DC
#define OUT3_DC                        LP5814_REG_OUT3_DC
#define OUT0_MANUAL_PWM                LP5814_REG_OUT0_MANUAL_PWM
#define OUT1_MANUAL_PWM                LP5814_REG_OUT1_MANUAL_PWM
#define OUT2_MANUAL_PWM                LP5814_REG_OUT2_MANUAL_PWM
#define OUT3_MANUAL_PWM                LP5814_REG_OUT3_MANUAL_PWM
#define PATTERN0_PAUSE_TIME            LP5814_REG_PATTERN0_PAUSE_TIME
#define PATTERN0_REPEAT_TIME           LP5814_REG_PATTERN0_REPEAT_TIME
#define PATTERN0_PWM0                  LP5814_REG_PATTERN0_PWM0
#define PATTERN0_PWM1                  LP5814_REG_PATTERN0_PWM1
#define PATTERN0_PWM2                  LP5814_REG_PATTERN0_PWM2
#define PATTERN0_PWM3                  LP5814_REG_PATTERN0_PWM3
#define PATTERN0_PWM4                  LP5814_REG_PATTERN0_PWM4
#define PATTERN0_SLOPER_TIME1          LP5814_REG_PATTERN0_SLOPER_TIME1
#define PATTERN0_SLOPER_TIME2          LP5814_REG_PATTERN0_SLOPER_TIME2
#define PATTERN1_PAUSE_TIME            LP5814_REG_PATTERN1_PAUSE_TIME
#define PATTERN1_REPEAT_TIME           LP5814_REG_PATTERN1_REPEAT_TIME
#define PATTERN1_PWM0                  LP5814_REG_PATTERN1_PWM0
#define PATTERN1_PWM1                  LP5814_REG_PATTERN1_PWM1
#define PATTERN1_PWM2                  LP5814_REG_PATTERN1_PWM2
#define PATTERN1_PWM3                  LP5814_REG_PATTERN1_PWM3
#define PATTERN1_PWM4                  LP5814_REG_PATTERN1_PWM4
#define PATTERN1_SLOPER_TIME1          LP5814_REG_PATTERN1_SLOPER_TIME1
#define PATTERN1_SLOPER_TIME2          LP5814_REG_PATTERN1_SLOPER_TIME2
#define PATTERN2_PAUSE_TIME            LP5814_REG_PATTERN2_PAUSE_TIME
#define PATTERN2_REPEAT_TIME           LP5814_REG_PATTERN2_REPEAT_TIME
#define PATTERN2_PWM0                  LP5814_REG_PATTERN2_PWM0
#define PATTERN2_PWM1                  LP5814_REG_PATTERN2_PWM1
#define PATTERN2_PWM2                  LP5814_REG_PATTERN2_PWM2
#define PATTERN2_PWM3                  LP5814_REG_PATTERN2_PWM3
#define PATTERN2_PWM4                  LP5814_REG_PATTERN2_PWM4
#define PATTERN2_SLOPER_TIME1          LP5814_REG_PATTERN2_SLOPER_TIME1
#define PATTERN2_SLOPER_TIME2          LP5814_REG_PATTERN2_SLOPER_TIME2
#define PATTERN3_PAUSE_TIME            LP5814_REG_PATTERN3_PAUSE_TIME
#define PATTERN3_REPEAT_TIME           LP5814_REG_PATTERN3_REPEAT_TIME
#define PATTERN3_PWM0                  LP5814_REG_PATTERN3_PWM0
#define PATTERN3_PWM1                  LP5814_REG_PATTERN3_PWM1
#define PATTERN3_PWM2                  LP5814_REG_PATTERN3_PWM2
#define PATTERN3_PWM3                  LP5814_REG_PATTERN3_PWM3
#define PATTERN3_PWM4                  LP5814_REG_PATTERN3_PWM4
#define PATTERN3_SLOPER_TIME1          LP5814_REG_PATTERN3_SLOPER_TIME1
#define PATTERN3_SLOPER_TIME2          LP5814_REG_PATTERN3_SLOPER_TIME2
#define FLAG                           LP5814_REG_FLAG

/* Named bits and fields */
/* CHIP_EN */
#define CHIP_EN_bp                        LP5814_CHIP_EN_bp
#define CHIP_EN_bm                        LP5814_CHIP_EN_bm
/* DEV_CONFIG0 */
#define MAX_CURRENT_bp                    LP5814_MAX_CURRENT_bp
#define MAX_CURRENT_bm                    LP5814_MAX_CURRENT_bm
/* DEV_CONFIG1 */
#define OUT3_EN_bp                        LP5814_OUT3_EN_bp
#define OUT3_EN_bm                        LP5814_OUT3_EN_bm
#define OUT2_EN_bp                        LP5814_OUT2_EN_bp
#define OUT2_EN_bm                        LP5814_OUT2_EN_bm
#define OUT1_EN_bp                        LP5814_OUT1_EN_bp
#define OUT1_EN_bm                        LP5814_OUT1_EN_bm
#define OUT0_EN_bp                        LP5814_OUT0_EN_bp
#define OUT0_EN_bm                        LP5814_OUT0_EN_bm
/* DEV_CONFIG2 */
#define LED_FADE_TIME_bp                  LP5814_LED_FADE_TIME_bp
#define LED_FADE_TIME_bm                  LP5814_LED_FADE_TIME_bm
#define LED_FADE_TIME_gp                  LP5814_LED_FADE_TIME_gp
#define LED_FADE_TIME_gm                  LP5814_LED_FADE_TIME_gm
#define OUT3_FADE_EN_bp                   LP5814_OUT3_FADE_EN_bp
#define OUT3_FADE_EN_bm                   LP5814_OUT3_FADE_EN_bm
#define OUT2_FADE_EN_bp                   LP5814_OUT2_FADE_EN_bp
#define OUT2_FADE_EN_bm                   LP5814_OUT2_FADE_EN_bm
#define OUT1_FADE_EN_bp                   LP5814_OUT1_FADE_EN_bp
#define OUT1_FADE_EN_bm                   LP5814_OUT1_FADE_EN_bm
#define OUT0_FADE_EN_bp                   LP5814_OUT0_FADE_EN_bp
#define OUT0_FADE_EN_bm                   LP5814_OUT0_FADE_EN_bm
/* DEV_CONFIG3 */
#define OUT3_EXP_EN_bp                    LP5814_OUT3_EXP_EN_bp
#define OUT3_EXP_EN_bm                    LP5814_OUT3_EXP_EN_bm
#define OUT2_EXP_EN_bp                    LP5814_OUT2_EXP_EN_bp
#define OUT2_EXP_EN_bm                    LP5814_OUT2_EXP_EN_bm
#define OUT1_EXP_EN_bp                    LP5814_OUT1_EXP_EN_bp
#define OUT1_EXP_EN_bm                    LP5814_OUT1_EXP_EN_bm
#define OUT0_EXP_EN_bp                    LP5814_OUT0_EXP_EN_bp
#define OUT0_EXP_EN_bm                    LP5814_OUT0_EXP_EN_bm
#define OUT3_AUTO_EN_bp                   LP5814_OUT3_AUTO_EN_bp
#define OUT3_AUTO_EN_bm                   LP5814_OUT3_AUTO_EN_bm
#define OUT2_AUTO_EN_bp                   LP5814_OUT2_AUTO_EN_bp
#define OUT2_AUTO_EN_bm                   LP5814_OUT2_AUTO_EN_bm
#define OUT1_AUTO_EN_bp                   LP5814_OUT1_AUTO_EN_bp
#define OUT1_AUTO_EN_bm                   LP5814_OUT1_AUTO_EN_bm
#define OUT0_AUTO_EN_bp                   LP5814_OUT0_AUTO_EN_bp
#define OUT0_AUTO_EN_bm                   LP5814_OUT0_AUTO_EN_bm
/* DEV_CONFIG4 */
#define OUT3_ENGINE_CH_bp                 LP5814_OUT3_ENGINE_CH_bp
#define OUT3_ENGINE_CH_bm                 LP5814_OUT3_ENGINE_CH_bm
#define OUT3_ENGINE_CH_gp                 LP5814_OUT3_ENGINE_CH_gp
#define OUT3_ENGINE_CH_gm                 LP5814_OUT3_ENGINE_CH_gm
#define OUT2_ENGINE_CH_bp                 LP5814_OUT2_ENGINE_CH_bp
#define OUT2_ENGINE_CH_bm                 LP5814_OUT2_ENGINE_CH_bm
#define OUT2_ENGINE_CH_gp                 LP5814_OUT2_ENGINE_CH_gp
#define OUT2_ENGINE_CH_gm                 LP5814_OUT2_ENGINE_CH_gm
#define OUT1_ENGINE_CH_bp                 LP5814_OUT1_ENGINE_CH_bp
#define OUT1_ENGINE_CH_bm                 LP5814_OUT1_ENGINE_CH_bm
#define OUT1_ENGINE_CH_gp                 LP5814_OUT1_ENGINE_CH_gp
#define OUT1_ENGINE_CH_gm                 LP5814_OUT1_ENGINE_CH_gm
#define OUT0_ENGINE_CH_bp                 LP5814_OUT0_ENGINE_CH_bp
#define OUT0_ENGINE_CH_bm                 LP5814_OUT0_ENGINE_CH_bm
#define OUT0_ENGINE_CH_gp                 LP5814_OUT0_ENGINE_CH_gp
#define OUT0_ENGINE_CH_gm                 LP5814_OUT0_ENGINE_CH_gm
/* ENGINE_CONFIG0 */
#define ENGINE0_ORDER3_bp                 LP5814_ENGINE0_ORDER3_bp
#define ENGINE0_ORDER3_bm                 LP5814_ENGINE0_ORDER3_bm
#define ENGINE0_ORDER3_gp                 LP5814_ENGINE0_ORDER3_gp
#define ENGINE0_ORDER3_gm                 LP5814_ENGINE0_ORDER3_gm
#define ENGINE0_ORDER2_bp                 LP5814_ENGINE0_ORDER2_bp
#define ENGINE0_ORDER2_bm                 LP5814_ENGINE0_ORDER2_bm
#define ENGINE0_ORDER2_gp                 LP5814_ENGINE0_ORDER2_gp
#define ENGINE0_ORDER2_gm                 LP5814_ENGINE0_ORDER2_gm
#define ENGINE0_ORDER1_bp                 LP5814_ENGINE0_ORDER1_bp
#define ENGINE0_ORDER1_bm                 LP5814_ENGINE0_ORDER1_bm
#define ENGINE0_ORDER1_gp                 LP5814_ENGINE0_ORDER1_gp
#define ENGINE0_ORDER1_gm                 LP5814_ENGINE0_ORDER1_gm
#define ENGINE0_ORDER0_bp                 LP5814_ENGINE0_ORDER0_bp
#define ENGINE0_ORDER0_bm                 LP5814_ENGINE0_ORDER0_bm
#define ENGINE0_ORDER0_gp                 LP5814_ENGINE0_ORDER0_gp
#define ENGINE0_ORDER0_gm                 LP5814_ENGINE0_ORDER0_gm
/* ENGINE_CONFIG1 */
#define ENGINE1_ORDER3_bp                 LP5814_ENGINE1_ORDER3_bp
#define ENGINE1_ORDER3_bm                 LP5814_ENGINE1_ORDER3_bm
#define ENGINE1_ORDER3_gp                 LP5814_ENGINE1_ORDER3_gp
#define ENGINE1_ORDER3_gm                 LP5814_ENGINE1_ORDER3_gm
#define ENGINE1_ORDER2_bp                 LP5814_ENGINE1_ORDER2_bp
#define ENGINE1_ORDER2_bm                 LP5814_ENGINE1_ORDER2_bm
#define ENGINE1_ORDER2_gp                 LP5814_ENGINE1_ORDER2_gp
#define ENGINE1_ORDER2_gm                 LP5814_ENGINE1_ORDER2_gm
#define ENGINE1_ORDER1_bp                 LP5814_ENGINE1_ORDER1_bp
#define ENGINE1_ORDER1_bm                 LP5814_ENGINE1_ORDER1_bm
#define ENGINE1_ORDER1_gp                 LP5814_ENGINE1_ORDER1_gp
#define ENGINE1_ORDER1_gm                 LP5814_ENGINE1_ORDER1_gm
#define ENGINE1_ORDER0_bp                 LP5814_ENGINE1_ORDER0_bp
#define ENGINE1_ORDER0_bm                 LP5814_ENGINE1_ORDER0_bm
#define ENGINE1_ORDER0_gp                 LP5814_ENGINE1_ORDER0_gp
#define ENGINE1_ORDER0_gm                 LP5814_ENGINE1_ORDER0_gm
/* ENGINE_CONFIG2 */
#define ENGINE2_ORDER3_bp                 LP5814_ENGINE2_ORDER3_bp
#define ENGINE2_ORDER3_bm                 LP5814_ENGINE2_ORDER3_bm
#define ENGINE2_ORDER3_gp                 LP5814_ENGINE2_ORDER3_gp
#define ENGINE2_ORDER3_gm                 LP5814_ENGINE2_ORDER3_gm
#define ENGINE2_ORDER2_bp                 LP5814_ENGINE2_ORDER2_bp
#define ENGINE2_ORDER2_bm                 LP5814_ENGINE2_ORDER2_bm
#define ENGINE2_ORDER2_gp                 LP5814_ENGINE2_ORDER2_gp
#define ENGINE2_ORDER2_gm                 LP5814_ENGINE2_ORDER2_gm
#define ENGINE2_ORDER1_bp                 LP5814_ENGINE2_ORDER1_bp
#define ENGINE2_ORDER1_bm                 LP5814_ENGINE2_ORDER1_bm
#define ENGINE2_ORDER1_gp                 LP5814_ENGINE2_ORDER1_gp
#define ENGINE2_ORDER1_gm                 LP5814_ENGINE2_ORDER1_gm
#define ENGINE2_ORDER0_bp                 LP5814_ENGINE2_ORDER0_bp
#define ENGINE2_ORDER0_bm                 LP5814_ENGINE2_ORDER0_bm
#define ENGINE2_ORDER0_gp                 LP5814_ENGINE2_ORDER0_gp
#define ENGINE2_ORDER0_gm                 LP5814_ENGINE2_ORDER0_gm
/* ENGINE_CONFIG3 */
#define ENGINE3_ORDER3_bp                 LP5814_ENGINE3_ORDER3_bp
#define ENGINE3_ORDER3_bm                 LP5814_ENGINE3_ORDER3_bm
#define ENGINE3_ORDER3_gp                 LP5814_ENGINE3_ORDER3_gp
#define ENGINE3_ORDER3_gm                 LP5814_ENGINE3_ORDER3_gm
#define ENGINE3_ORDER2_bp                 LP5814_ENGINE3_ORDER2_bp
#define ENGINE3_ORDER2_bm                 LP5814_ENGINE3_ORDER2_bm
#define ENGINE3_ORDER2_gp                 LP5814_ENGINE3_ORDER2_gp
#define ENGINE3_ORDER2_gm                 LP5814_ENGINE3_ORDER2_gm
#define ENGINE3_ORDER1_bp                 LP5814_ENGINE3_ORDER1_bp
#define ENGINE3_ORDER1_bm                 LP5814_ENGINE3_ORDER1_bm
#define ENGINE3_ORDER1_gp                 LP5814_ENGINE3_ORDER1_gp
#define ENGINE3_ORDER1_gm                 LP5814_ENGINE3_ORDER1_gm
#define ENGINE3_ORDER0_bp                 LP5814_ENGINE3_ORDER0_bp
#define ENGINE3_ORDER0_bm                 LP5814_ENGINE3_ORDER0_bm
#define ENGINE3_ORDER0_gp                 LP5814_ENGINE3_ORDER0_gp
#define ENGINE3_ORDER0_gm                 LP5814_ENGINE3_ORDER0_gm
/* ENGINE_CONFIG4 */
#define E1O3_EN_bp                        LP5814_E1O3_EN_bp
#define E1O3_EN_bm                        LP5814_E1O3_EN_bm
#define E1O2_EN_bp                        LP5814_E1O2_EN_bp
#define E1O2_EN_bm                        LP5814_E1O2_EN_bm
#define E1O1_EN_bp                        LP5814_E1O1_EN_bp
#define E1O1_EN_bm                        LP5814_E1O1_EN_bm
#define E1O0_EN_bp                        LP5814_E1O0_EN_bp
#define E1O0_EN_bm                        LP5814_E1O0_EN_bm
#define E0O3_EN_bp                        LP5814_E0O3_EN_bp
#define E0O3_EN_bm                        LP5814_E0O3_EN_bm
#define E0O2_EN_bp                        LP5814_E0O2_EN_bp
#define E0O2_EN_bm                        LP5814_E0O2_EN_bm
#define E0O1_EN_bp                        LP5814_E0O1_EN_bp
#define E0O1_EN_bm                        LP5814_E0O1_EN_bm
#define E0O0_EN_bp                        LP5814_E0O0_EN_bp
#define E0O0_EN_bm                        LP5814_E0O0_EN_bm
/* ENGINE_CONFIG5 */
#define E3O3_EN_bp                        LP5814_E3O3_EN_bp
#define E3O3_EN_bm                        LP5814_E3O3_EN_bm
#define E3O2_EN_bp                        LP5814_E3O2_EN_bp
#define E3O2_EN_bm                        LP5814_E3O2_EN_bm
#define E3O1_EN_bp                        LP5814_E3O1_EN_bp
#define E3O1_EN_bm                        LP5814_E3O1_EN_bm
#define E3O0_EN_bp                        LP5814_E3O0_EN_bp
#define E3O0_EN_bm                        LP5814_E3O0_EN_bm
#define E2O3_EN_bp                        LP5814_E2O3_EN_bp
#define E2O3_EN_bm                        LP5814_E2O3_EN_bm
#define E2O2_EN_bp                        LP5814_E2O2_EN_bp
#define E2O2_EN_bm                        LP5814_E2O2_EN_bm
#define E2O1_EN_bp                        LP5814_E2O1_EN_bp
#define E2O1_EN_bm                        LP5814_E2O1_EN_bm
#define E2O0_EN_bp                        LP5814_E2O0_EN_bp
#define E2O0_EN_bm                        LP5814_E2O0_EN_bm
/* ENGINE_CONFIG6 */
#define ENGINE3_REPT_bp                   LP5814_ENGINE3_REPT_bp
#define ENGINE3_REPT_bm                   LP5814_ENGINE3_REPT_bm
#define ENGINE3_REPT_gp                   LP5814_ENGINE3_REPT_gp
#define ENGINE3_REPT_gm                   LP5814_ENGINE3_REPT_gm
#define ENGINE2_REPT_bp                   LP5814_ENGINE2_REPT_bp
#define ENGINE2_REPT_bm                   LP5814_ENGINE2_REPT_bm
#define ENGINE2_REPT_gp                   LP5814_ENGINE2_REPT_gp
#define ENGINE2_REPT_gm                   LP5814_ENGINE2_REPT_gm
#define ENGINE1_REPT_bp                   LP5814_ENGINE1_REPT_bp
#define ENGINE1_REPT_bm                   LP5814_ENGINE1_REPT_bm
#define ENGINE1_REPT_gp                   LP5814_ENGINE1_REPT_gp
#define ENGINE1_REPT_gm                   LP5814_ENGINE1_REPT_gm
#define ENGINE0_REPT_bp                   LP5814_ENGINE0_REPT_bp
#define ENGINE0_REPT_bm                   LP5814_ENGINE0_REPT_bm
#define ENGINE0_REPT_gp                   LP5814_ENGINE0_REPT_gp
#define ENGINE0_REPT_gm                   LP5814_ENGINE0_REPT_gm
/* SHUTDOWN_CMD */
#define SHUTDOWN_bp                       LP5814_SHUTDOWN_bp
#define SHUTDOWN_bm                       LP5814_SHUTDOWN_bm
#define SHUTDOWN_gp                       LP5814_SHUTDOWN_gp
#define SHUTDOWN_gm                       LP5814_SHUTDOWN_gm
/* RESET_CMD */
#define RESET_bp                          LP5814_RESET_bp
#define RESET_bm                          LP5814_RESET_bm
#define RESET_gp                          LP5814_RESET_gp
#define RESET_gm                          LP5814_RESET_gm
/* UPDATE_CMD */
#define UPDATE_bp                         LP5814_UPDATE_bp
#define UPDATE_bm                         LP5814_UPDATE_bm
#define UPDATE_gp                         LP5814_UPDATE_gp
#define UPDATE_gm                         LP5814_UPDATE_gm
/* START_CMD */
#define START_bp                          LP5814_START_bp
#define START_bm                          LP5814_START_bm
#define START_gp                          LP5814_START_gp
#define START_gm                          LP5814_START_gm
/* STOP_CMD */
#define STOP_bp                           LP5814_STOP_bp
#define STOP_bm                           LP5814_STOP_bm
#define STOP_gp                           LP5814_STOP_gp
#define STOP_gm                           LP5814_STOP_gm
/* PAUSE_CONTINUE */
#define PAUSE_CONTINUE_bp                 LP5814_PAUSE_CONTINUE_bp
#define PAUSE_CONTINUE_bm                 LP5814_PAUSE_CONTINUE_bm
/* FLAG_CLR */
#define TSD_CLR_bp                        LP5814_TSD_CLR_bp
#define TSD_CLR_bm                        LP5814_TSD_CLR_bm
#define POR_CLR_bp                        LP5814_POR_CLR_bp
#define POR_CLR_bm                        LP5814_POR_CLR_bm
/* OUT0_DC */
#define OUT0_DC_bp                        LP5814_OUT0_DC_bp
#define OUT0_DC_bm                        LP5814_OUT0_DC_bm
#define OUT0_DC_gp                        LP5814_OUT0_DC_gp
#define OUT0_DC_gm                        LP5814_OUT0_DC_gm
/* OUT1_DC */
#define OUT1_DC_bp                        LP5814_OUT1_DC_bp
#define OUT1_DC_bm                        LP5814_OUT1_DC_bm
#define OUT1_DC_gp                        LP5814_OUT1_DC_gp
#define OUT1_DC_gm                        LP5814_OUT1_DC_gm
/* OUT2_DC */
#define OUT2_DC_bp                        LP5814_OUT2_DC_bp
#define OUT2_DC_bm                        LP5814_OUT2_DC_bm
#define OUT2_DC_gp                        LP5814_OUT2_DC_gp
#define OUT2_DC_gm                        LP5814_OUT2_DC_gm
/* OUT3_DC */
#define OUT3_DC_bp                        LP5814_OUT3_DC_bp
#define OUT3_DC_bm                        LP5814_OUT3_DC_bm
#define OUT3_DC_gp                        LP5814_OUT3_DC_gp
#define OUT3_DC_gm                        LP5814_OUT3_DC_gm
/* OUT0_MANUAL_PWM */
#define OUT0_MANUAL_PWM_bp                LP5814_OUT0_MANUAL_PWM_bp
#define OUT0_MANUAL_PWM_bm                LP5814_OUT0_MANUAL_PWM_bm
#define OUT0_MANUAL_PWM_gp                LP5814_OUT0_MANUAL_PWM_gp
#define OUT0_MANUAL_PWM_gm                LP5814_OUT0_MANUAL_PWM_gm
/* OUT1_MANUAL_PWM */
#define OUT1_MANUAL_PWM_bp                LP5814_OUT1_MANUAL_PWM_bp
#define OUT1_MANUAL_PWM_bm                LP5814_OUT1_MANUAL_PWM_bm
#define OUT1_MANUAL_PWM_gp                LP5814_OUT1_MANUAL_PWM_gp
#define OUT1_MANUAL_PWM_gm                LP5814_OUT1_MANUAL_PWM_gm
/* OUT2_MANUAL_PWM */
#define OUT2_MANUAL_PWM_bp                LP5814_OUT2_MANUAL_PWM_bp
#define OUT2_MANUAL_PWM_bm                LP5814_OUT2_MANUAL_PWM_bm
#define OUT2_MANUAL_PWM_gp                LP5814_OUT2_MANUAL_PWM_gp
#define OUT2_MANUAL_PWM_gm                LP5814_OUT2_MANUAL_PWM_gm
/* OUT3_MANUAL_PWM */
#define OUT3_MANUAL_PWM_bp                LP5814_OUT3_MANUAL_PWM_bp
#define OUT3_MANUAL_PWM_bm                LP5814_OUT3_MANUAL_PWM_bm
#define OUT3_MANUAL_PWM_gp                LP5814_OUT3_MANUAL_PWM_gp
#define OUT3_MANUAL_PWM_gm                LP5814_OUT3_MANUAL_PWM_gm
/* PATTERN0_PAUSE_TIME */
#define PATTERN0_PAUSE_T0_bp              LP5814_PATTERN0_PAUSE_T0_bp
#define PATTERN0_PAUSE_T0_bm              LP5814_PATTERN0_PAUSE_T0_bm
#define PATTERN0_PAUSE_T0_gp              LP5814_PATTERN0_PAUSE_T0_gp
#define PATTERN0_PAUSE_T0_gm              LP5814_PATTERN0_PAUSE_T0_gm
#define PATTERN0_PAUSE_T1_bp              LP5814_PATTERN0_PAUSE_T1_bp
#define PATTERN0_PAUSE_T1_bm              LP5814_PATTERN0_PAUSE_T1_bm
#define PATTERN0_PAUSE_T1_gp              LP5814_PATTERN0_PAUSE_T1_gp
#define PATTERN0_PAUSE_T1_gm              LP5814_PATTERN0_PAUSE_T1_gm
/* PATTERN0_REPEAT_TIME */
#define PATTERN0_PT_bp                    LP5814_PATTERN0_PT_bp
#define PATTERN0_PT_bm                    LP5814_PATTERN0_PT_bm
#define PATTERN0_PT_gp                    LP5814_PATTERN0_PT_gp
#define PATTERN0_PT_gm                    LP5814_PATTERN0_PT_gm
/* PATTERN0_PWM0 */
#define PATTERN0_PWM0_bp                  LP5814_PATTERN0_PWM0_bp
#define PATTERN0_PWM0_bm                  LP5814_PATTERN0_PWM0_bm
#define PATTERN0_PWM0_gp                  LP5814_PATTERN0_PWM0_gp
#define PATTERN0_PWM0_gm                  LP5814_PATTERN0_PWM0_gm
/* PATTERN0_PWM1 */
#define PATTERN0_PWM1_bp                  LP5814_PATTERN0_PWM1_bp
#define PATTERN0_PWM1_bm                  LP5814_PATTERN0_PWM1_bm
#define PATTERN0_PWM1_gp                  LP5814_PATTERN0_PWM1_gp
#define PATTERN0_PWM1_gm                  LP5814_PATTERN0_PWM1_gm
/* PATTERN0_PWM2 */
#define PATTERN0_PWM2_bp                  LP5814_PATTERN0_PWM2_bp
#define PATTERN0_PWM2_bm                  LP5814_PATTERN0_PWM2_bm
#define PATTERN0_PWM2_gp                  LP5814_PATTERN0_PWM2_gp
#define PATTERN0_PWM2_gm                  LP5814_PATTERN0_PWM2_gm
/* PATTERN0_PWM3 */
#define PATTERN0_PWM3_bp                  LP5814_PATTERN0_PWM3_bp
#define PATTERN0_PWM3_bm                  LP5814_PATTERN0_PWM3_bm
#define PATTERN0_PWM3_gp                  LP5814_PATTERN0_PWM3_gp
#define PATTERN0_PWM3_gm                  LP5814_PATTERN0_PWM3_gm
/* PATTERN0_PWM4 */
#define PATTERN0_PWM4_bp                  LP5814_PATTERN0_PWM4_bp
#define PATTERN0_PWM4_bm                  LP5814_PATTERN0_PWM4_bm
#define PATTERN0_PWM4_gp                  LP5814_PATTERN0_PWM4_gp
#define PATTERN0_PWM4_gm                  LP5814_PATTERN0_PWM4_gm
/* PATTERN0_SLOPER_TIME1 */
#define PATTERN0_SLOPER_T1_bp             LP5814_PATTERN0_SLOPER_T1_bp
#define PATTERN0_SLOPER_T1_bm             LP5814_PATTERN0_SLOPER_T1_bm
#define PATTERN0_SLOPER_T1_gp             LP5814_PATTERN0_SLOPER_T1_gp
#define PATTERN0_SLOPER_T1_gm             LP5814_PATTERN0_SLOPER_T1_gm
#define PATTERN0_SLOPER_T0_bp             LP5814_PATTERN0_SLOPER_T0_bp
#define PATTERN0_SLOPER_T0_bm             LP5814_PATTERN0_SLOPER_T0_bm
#define PATTERN0_SLOPER_T0_gp             LP5814_PATTERN0_SLOPER_T0_gp
#define PATTERN0_SLOPER_T0_gm             LP5814_PATTERN0_SLOPER_T0_gm
/* PATTERN0_SLOPER_TIME2 */
#define PATTERN0_SLOPER_T3_bp             LP5814_PATTERN0_SLOPER_T3_bp
#define PATTERN0_SLOPER_T3_bm             LP5814_PATTERN0_SLOPER_T3_bm
#define PATTERN0_SLOPER_T3_gp             LP5814_PATTERN0_SLOPER_T3_gp
#define PATTERN0_SLOPER_T3_gm             LP5814_PATTERN0_SLOPER_T3_gm
#define PATTERN0_SLOPER_T2_bp             LP5814_PATTERN0_SLOPER_T2_bp
#define PATTERN0_SLOPER_T2_bm             LP5814_PATTERN0_SLOPER_T2_bm
#define PATTERN0_SLOPER_T2_gp             LP5814_PATTERN0_SLOPER_T2_gp
#define PATTERN0_SLOPER_T2_gm             LP5814_PATTERN0_SLOPER_T2_gm
/* PATTERN1_PAUSE_TIME */
#define PATTERN1_PAUSE_T0_bp              LP5814_PATTERN1_PAUSE_T0_bp
#define PATTERN1_PAUSE_T0_bm              LP5814_PATTERN1_PAUSE_T0_bm
#define PATTERN1_PAUSE_T0_gp              LP5814_PATTERN1_PAUSE_T0_gp
#define PATTERN1_PAUSE_T0_gm              LP5814_PATTERN1_PAUSE_T0_gm
#define PATTERN1_PAUSE_T1_bp              LP5814_PATTERN1_PAUSE_T1_bp
#define PATTERN1_PAUSE_T1_bm              LP5814_PATTERN1_PAUSE_T1_bm
#define PATTERN1_PAUSE_T1_gp              LP5814_PATTERN1_PAUSE_T1_gp
#define PATTERN1_PAUSE_T1_gm              LP5814_PATTERN1_PAUSE_T1_gm
/* PATTERN1_REPEAT_TIME */
#define PATTERN1_PT_bp                    LP5814_PATTERN1_PT_bp
#define PATTERN1_PT_bm                    LP5814_PATTERN1_PT_bm
#define PATTERN1_PT_gp                    LP5814_PATTERN1_PT_gp
#define PATTERN1_PT_gm                    LP5814_PATTERN1_PT_gm
/* PATTERN1_PWM0 */
#define PATTERN1_PWM0_bp                  LP5814_PATTERN1_PWM0_bp
#define PATTERN1_PWM0_bm                  LP5814_PATTERN1_PWM0_bm
#define PATTERN1_PWM0_gp                  LP5814_PATTERN1_PWM0_gp
#define PATTERN1_PWM0_gm                  LP5814_PATTERN1_PWM0_gm
/* PATTERN1_PWM1 */
#define PATTERN1_PWM1_bp                  LP5814_PATTERN1_PWM1_bp
#define PATTERN1_PWM1_bm                  LP5814_PATTERN1_PWM1_bm
#define PATTERN1_PWM1_gp                  LP5814_PATTERN1_PWM1_gp
#define PATTERN1_PWM1_gm                  LP5814_PATTERN1_PWM1_gm
/* PATTERN1_PWM2 */
#define PATTERN1_PWM2_bp                  LP5814_PATTERN1_PWM2_bp
#define PATTERN1_PWM2_bm                  LP5814_PATTERN1_PWM2_bm
#define PATTERN1_PWM2_gp                  LP5814_PATTERN1_PWM2_gp
#define PATTERN1_PWM2_gm                  LP5814_PATTERN1_PWM2_gm
/* PATTERN1_PWM3 */
#define PATTERN1_PWM3_bp                  LP5814_PATTERN1_PWM3_bp
#define PATTERN1_PWM3_bm                  LP5814_PATTERN1_PWM3_bm
#define PATTERN1_PWM3_gp                  LP5814_PATTERN1_PWM3_gp
#define PATTERN1_PWM3_gm                  LP5814_PATTERN1_PWM3_gm
/* PATTERN1_PWM4 */
#define PATTERN1_PWM4_bp                  LP5814_PATTERN1_PWM4_bp
#define PATTERN1_PWM4_bm                  LP5814_PATTERN1_PWM4_bm
#define PATTERN1_PWM4_gp                  LP5814_PATTERN1_PWM4_gp
#define PATTERN1_PWM4_gm                  LP5814_PATTERN1_PWM4_gm
/* PATTERN1_SLOPER_TIME1 */
#define PATTERN1_SLOPER_T1_bp             LP5814_PATTERN1_SLOPER_T1_bp
#define PATTERN1_SLOPER_T1_bm             LP5814_PATTERN1_SLOPER_T1_bm
#define PATTERN1_SLOPER_T1_gp             LP5814_PATTERN1_SLOPER_T1_gp
#define PATTERN1_SLOPER_T1_gm             LP5814_PATTERN1_SLOPER_T1_gm
#define PATTERN1_SLOPER_T0_bp             LP5814_PATTERN1_SLOPER_T0_bp
#define PATTERN1_SLOPER_T0_bm             LP5814_PATTERN1_SLOPER_T0_bm
#define PATTERN1_SLOPER_T0_gp             LP5814_PATTERN1_SLOPER_T0_gp
#define PATTERN1_SLOPER_T0_gm             LP5814_PATTERN1_SLOPER_T0_gm
/* PATTERN1_SLOPER_TIME2 */
#define PATTERN1_SLOPER_T3_bp             LP5814_PATTERN1_SLOPER_T3_bp
#define PATTERN1_SLOPER_T3_bm             LP5814_PATTERN1_SLOPER_T3_bm
#define PATTERN1_SLOPER_T3_gp             LP5814_PATTERN1_SLOPER_T3_gp
#define PATTERN1_SLOPER_T3_gm             LP5814_PATTERN1_SLOPER_T3_gm
#define PATTERN1_SLOPER_T2_bp             LP5814_PATTERN1_SLOPER_T2_bp
#define PATTERN1_SLOPER_T2_bm             LP5814_PATTERN1_SLOPER_T2_bm
#define PATTERN1_SLOPER_T2_gp             LP5814_PATTERN1_SLOPER_T2_gp
#define PATTERN1_SLOPER_T2_gm             LP5814_PATTERN1_SLOPER_T2_gm
/* PATTERN2_PAUSE_TIME */
#define PATTERN2_PAUSE_T0_bp              LP5814_PATTERN2_PAUSE_T0_bp
#define PATTERN2_PAUSE_T0_bm              LP5814_PATTERN2_PAUSE_T0_bm
#define PATTERN2_PAUSE_T0_gp              LP5814_PATTERN2_PAUSE_T0_gp
#define PATTERN2_PAUSE_T0_gm              LP5814_PATTERN2_PAUSE_T0_gm
#define PATTERN2_PAUSE_T1_bp              LP5814_PATTERN2_PAUSE_T1_bp
#define PATTERN2_PAUSE_T1_bm              LP5814_PATTERN2_PAUSE_T1_bm
#define PATTERN2_PAUSE_T1_gp              LP5814_PATTERN2_PAUSE_T1_gp
#define PATTERN2_PAUSE_T1_gm              LP5814_PATTERN2_PAUSE_T1_gm
/* PATTERN2_REPEAT_TIME */
#define PATTERN2_PT_bp                    LP5814_PATTERN2_PT_bp
#define PATTERN2_PT_bm                    LP5814_PATTERN2_PT_bm
#define PATTERN2_PT_gp                    LP5814_PATTERN2_PT_gp
#define PATTERN2_PT_gm                    LP5814_PATTERN2_PT_gm
/* PATTERN2_PWM0 */
#define PATTERN2_PWM0_bp                  LP5814_PATTERN2_PWM0_bp
#define PATTERN2_PWM0_bm                  LP5814_PATTERN2_PWM0_bm
#define PATTERN2_PWM0_gp                  LP5814_PATTERN2_PWM0_gp
#define PATTERN2_PWM0_gm                  LP5814_PATTERN2_PWM0_gm
/* PATTERN2_PWM1 */
#define PATTERN2_PWM1_bp                  LP5814_PATTERN2_PWM1_bp
#define PATTERN2_PWM1_bm                  LP5814_PATTERN2_PWM1_bm
#define PATTERN2_PWM1_gp                  LP5814_PATTERN2_PWM1_gp
#define PATTERN2_PWM1_gm                  LP5814_PATTERN2_PWM1_gm
/* PATTERN2_PWM2 */
#define PATTERN2_PWM2_bp                  LP5814_PATTERN2_PWM2_bp
#define PATTERN2_PWM2_bm                  LP5814_PATTERN2_PWM2_bm
#define PATTERN2_PWM2_gp                  LP5814_PATTERN2_PWM2_gp
#define PATTERN2_PWM2_gm                  LP5814_PATTERN2_PWM2_gm
/* PATTERN2_PWM3 */
#define PATTERN2_PWM3_bp                  LP5814_PATTERN2_PWM3_bp
#define PATTERN2_PWM3_bm                  LP5814_PATTERN2_PWM3_bm
#define PATTERN2_PWM3_gp                  LP5814_PATTERN2_PWM3_gp
#define PATTERN2_PWM3_gm                  LP5814_PATTERN2_PWM3_gm
/* PATTERN2_PWM4 */
#define PATTERN2_PWM4_bp                  LP5814_PATTERN2_PWM4_bp
#define PATTERN2_PWM4_bm                  LP5814_PATTERN2_PWM4_bm
#define PATTERN2_PWM4_gp                  LP5814_PATTERN2_PWM4_gp
#define PATTERN2_PWM4_gm                  LP5814_PATTERN2_PWM4_gm
/* PATTERN2_SLOPER_TIME1 */
#define PATTERN2_SLOPER_T1_bp             LP5814_PATTERN2_SLOPER_T1_bp
#define PATTERN2_SLOPER_T1_bm             LP5814_PATTERN2_SLOPER_T1_bm
#define PATTERN2_SLOPER_T1_gp             LP5814_PATTERN2_SLOPER_T1_gp
#define PATTERN2_SLOPER_T1_gm             LP5814_PATTERN2_SLOPER_T1_gm
#define PATTERN2_SLOPER_T0_bp             LP5814_PATTERN2_SLOPER_T0_bp
#define PATTERN2_SLOPER_T0_bm             LP5814_PATTERN2_SLOPER_T0_bm
#define PATTERN2_SLOPER_T0_gp             LP5814_PATTERN2_SLOPER_T0_gp
#define PATTERN2_SLOPER_T0_gm             LP5814_PATTERN2_SLOPER_T0_gm
/* PATTERN2_SLOPER_TIME2 */
#define PATTERN2_SLOPER_T3_bp             LP5814_PATTERN2_SLOPER_T3_bp
#define PATTERN2_SLOPER_T3_bm             LP5814_PATTERN2_SLOPER_T3_bm
#define PATTERN2_SLOPER_T3_gp             LP5814_PATTERN2_SLOPER_T3_gp
#define PATTERN2_SLOPER_T3_gm             LP5814_PATTERN2_SLOPER_T3_gm
#define PATTERN2_SLOPER_T2_bp             LP5814_PATTERN2_SLOPER_T2_bp
#define PATTERN2_SLOPER_T2_bm             LP5814_PATTERN2_SLOPER_T2_bm
#define PATTERN2_SLOPER_T2_gp             LP5814_PATTERN2_SLOPER_T2_gp
#define PATTERN2_SLOPER_T2_gm             LP5814_PATTERN2_SLOPER_T2_gm
/* PATTERN3_PAUSE_TIME */
#define PATTERN3_PAUSE_T0_bp              LP5814_PATTERN3_PAUSE_T0_bp
#define PATTERN3_PAUSE_T0_bm              LP5814_PATTERN3_PAUSE_T0_bm
#define PATTERN3_PAUSE_T0_gp              LP5814_PATTERN3_PAUSE_T0_gp
#define PATTERN3_PAUSE_T0_gm              LP5814_PATTERN3_PAUSE_T0_gm
#define PATTERN3_PAUSE_T1_bp              LP5814_PATTERN3_PAUSE_T1_bp
#define PATTERN3_PAUSE_T1_bm              LP5814_PATTERN3_PAUSE_T1_bm
#define PATTERN3_PAUSE_T1_gp              LP5814_PATTERN3_PAUSE_T1_gp
#define PATTERN3_PAUSE_T1_gm              LP5814_PATTERN3_PAUSE_T1_gm
/* PATTERN3_REPEAT_TIME */
#define PATTERN3_PT_bp                    LP5814_PATTERN3_PT_bp
#define PATTERN3_PT_bm                    LP5814_PATTERN3_PT_bm
#define PATTERN3_PT_gp                    LP5814_PATTERN3_PT_gp
#define PATTERN3_PT_gm                    LP5814_PATTERN3_PT_gm
/* PATTERN3_PWM0 */
#define PATTERN3_PWM0_bp                  LP5814_PATTERN3_PWM0_bp
#define PATTERN3_PWM0_bm                  LP5814_PATTERN3_PWM0_bm
#define PATTERN3_PWM0_gp                  LP5814_PATTERN3_PWM0_gp
#define PATTERN3_PWM0_gm                  LP5814_PATTERN3_PWM0_gm
/* PATTERN3_PWM1 */
#define PATTERN3_PWM1_bp                  LP5814_PATTERN3_PWM1_bp
#define PATTERN3_PWM1_bm                  LP5814_PATTERN3_PWM1_bm
#define PATTERN3_PWM1_gp                  LP5814_PATTERN3_PWM1_gp
#define PATTERN3_PWM1_gm                  LP5814_PATTERN3_PWM1_gm
/* PATTERN3_PWM2 */
#define PATTERN3_PWM2_bp                  LP5814_PATTERN3_PWM2_bp
#define PATTERN3_PWM2_bm                  LP5814_PATTERN3_PWM2_bm
#define PATTERN3_PWM2_gp                  LP5814_PATTERN3_PWM2_gp
#define PATTERN3_PWM2_gm                  LP5814_PATTERN3_PWM2_gm
/* PATTERN3_PWM3 */
#define PATTERN3_PWM3_bp                  LP5814_PATTERN3_PWM3_bp
#define PATTERN3_PWM3_bm                  LP5814_PATTERN3_PWM3_bm
#define PATTERN3_PWM3_gp                  LP5814_PATTERN3_PWM3_gp
#define PATTERN3_PWM3_gm                  LP5814_PATTERN3_PWM3_gm
/* PATTERN3_PWM4 */
#define PATTERN3_PWM4_bp                  LP5814_PATTERN3_PWM4_bp
#define PATTERN3_PWM4_bm                  LP5814_PATTERN3_PWM4_bm
#define PATTERN3_PWM4_gp                  LP5814_PATTERN3_PWM4_gp
#define PATTERN3_PWM4_gm                  LP5814_PATTERN3_PWM4_gm
/* PATTERN3_SLOPER_TIME1 */
#define PATTERN3_SLOPER_T1_bp             LP5814_PATTERN3_SLOPER_T1_bp
#define PATTERN3_SLOPER_T1_bm             LP5814_PATTERN3_SLOPER_T1_bm
#define PATTERN3_SLOPER_T1_gp             LP5814_PATTERN3_SLOPER_T1_gp
#define PATTERN3_SLOPER_T1_gm             LP5814_PATTERN3_SLOPER_T1_gm
#define PATTERN3_SLOPER_T0_bp             LP5814_PATTERN3_SLOPER_T0_bp
#define PATTERN3_SLOPER_T0_bm             LP5814_PATTERN3_SLOPER_T0_bm
#define PATTERN3_SLOPER_T0_gp             LP5814_PATTERN3_SLOPER_T0_gp
#define PATTERN3_SLOPER_T0_gm             LP5814_PATTERN3_SLOPER_T0_gm
/* PATTERN3_SLOPER_TIME2 */
#define PATTERN3_SLOPER_T3_bp             LP5814_PATTERN3_SLOPER_T3_bp
#define PATTERN3_SLOPER_T3_bm             LP5814_PATTERN3_SLOPER_T3_bm
#define PATTERN3_SLOPER_T3_gp             LP5814_PATTERN3_SLOPER_T3_gp
#define PATTERN3_SLOPER_T3_gm             LP5814_PATTERN3_SLOPER_T3_gm
#define PATTERN3_SLOPER_T2_bp             LP5814_PATTERN3_SLOPER_T2_bp
#define PATTERN3_SLOPER_T2_bm             LP5814_PATTERN3_SLOPER_T2_bm
#define PATTERN3_SLOPER_T2_gp             LP5814_PATTERN3_SLOPER_T2_gp
#define PATTERN3_SLOPER_T2_gm             LP5814_PATTERN3_SLOPER_T2_gm
/* FLAG */
#define OUT3_ENGINE_BUSY_bp               LP5814_OUT3_ENGINE_BUSY_bp
#define OUT3_ENGINE_BUSY_bm               LP5814_OUT3_ENGINE_BUSY_bm
#define OUT2_ENGINE_BUSY_bp               LP5814_OUT2_ENGINE_BUSY_bp
#define OUT2_ENGINE_BUSY_bm               LP5814_OUT2_ENGINE_BUSY_bm
#define OUT1_ENGINE_BUSY_bp               LP5814_OUT1_ENGINE_BUSY_bp
#define OUT1_ENGINE_BUSY_bm               LP5814_OUT1_ENGINE_BUSY_bm
#define OUT0_ENGINE_BUSY_bp               LP5814_OUT0_ENGINE_BUSY_bp
#define OUT0_ENGINE_BUSY_bm               LP5814_OUT0_ENGINE_BUSY_bm
#define ENGINE_BUSY_bp                    LP5814_ENGINE_BUSY_bp
#define ENGINE_BUSY_bm                    LP5814_ENGINE_BUSY_bm
#define TSD_bp                            LP5814_TSD_bp
#define TSD_bm                            LP5814_TSD_bm
#define POR_bp                            LP5814_POR_bp
#define POR_bm                            LP5814_POR_bm


/* Optional short names for AVR-style _gc configuration choices */
#define MAX_CURRENT_25_5MA_gc                              LP5814_MAX_CURRENT_25_5MA_gc
#define MAX_CURRENT_51MA_gc                                LP5814_MAX_CURRENT_51MA_gc
#define LED_FADE_TIME_0MS_gc                               LP5814_LED_FADE_TIME_0MS_gc
#define LED_FADE_TIME_50MS_gc                              LP5814_LED_FADE_TIME_50MS_gc
#define LED_FADE_TIME_100MS_gc                             LP5814_LED_FADE_TIME_100MS_gc
#define LED_FADE_TIME_150MS_gc                             LP5814_LED_FADE_TIME_150MS_gc
#define LED_FADE_TIME_200MS_gc                             LP5814_LED_FADE_TIME_200MS_gc
#define LED_FADE_TIME_250MS_gc                             LP5814_LED_FADE_TIME_250MS_gc
#define LED_FADE_TIME_300MS_gc                             LP5814_LED_FADE_TIME_300MS_gc
#define LED_FADE_TIME_350MS_gc                             LP5814_LED_FADE_TIME_350MS_gc
#define LED_FADE_TIME_400MS_gc                             LP5814_LED_FADE_TIME_400MS_gc
#define LED_FADE_TIME_450MS_gc                             LP5814_LED_FADE_TIME_450MS_gc
#define LED_FADE_TIME_500MS_gc                             LP5814_LED_FADE_TIME_500MS_gc
#define LED_FADE_TIME_1000MS_gc                            LP5814_LED_FADE_TIME_1000MS_gc
#define LED_FADE_TIME_2000MS_gc                            LP5814_LED_FADE_TIME_2000MS_gc
#define LED_FADE_TIME_4000MS_gc                            LP5814_LED_FADE_TIME_4000MS_gc
#define LED_FADE_TIME_6000MS_gc                            LP5814_LED_FADE_TIME_6000MS_gc
#define LED_FADE_TIME_8000MS_gc                            LP5814_LED_FADE_TIME_8000MS_gc
#define OUT0_ENGINE_CH_ENGINE0_gc                          LP5814_OUT0_ENGINE_CH_ENGINE0_gc
#define OUT0_ENGINE_CH_ENGINE1_gc                          LP5814_OUT0_ENGINE_CH_ENGINE1_gc
#define OUT0_ENGINE_CH_ENGINE2_gc                          LP5814_OUT0_ENGINE_CH_ENGINE2_gc
#define OUT0_ENGINE_CH_ENGINE3_gc                          LP5814_OUT0_ENGINE_CH_ENGINE3_gc
#define OUT1_ENGINE_CH_ENGINE0_gc                          LP5814_OUT1_ENGINE_CH_ENGINE0_gc
#define OUT1_ENGINE_CH_ENGINE1_gc                          LP5814_OUT1_ENGINE_CH_ENGINE1_gc
#define OUT1_ENGINE_CH_ENGINE2_gc                          LP5814_OUT1_ENGINE_CH_ENGINE2_gc
#define OUT1_ENGINE_CH_ENGINE3_gc                          LP5814_OUT1_ENGINE_CH_ENGINE3_gc
#define OUT2_ENGINE_CH_ENGINE0_gc                          LP5814_OUT2_ENGINE_CH_ENGINE0_gc
#define OUT2_ENGINE_CH_ENGINE1_gc                          LP5814_OUT2_ENGINE_CH_ENGINE1_gc
#define OUT2_ENGINE_CH_ENGINE2_gc                          LP5814_OUT2_ENGINE_CH_ENGINE2_gc
#define OUT2_ENGINE_CH_ENGINE3_gc                          LP5814_OUT2_ENGINE_CH_ENGINE3_gc
#define OUT3_ENGINE_CH_ENGINE0_gc                          LP5814_OUT3_ENGINE_CH_ENGINE0_gc
#define OUT3_ENGINE_CH_ENGINE1_gc                          LP5814_OUT3_ENGINE_CH_ENGINE1_gc
#define OUT3_ENGINE_CH_ENGINE2_gc                          LP5814_OUT3_ENGINE_CH_ENGINE2_gc
#define OUT3_ENGINE_CH_ENGINE3_gc                          LP5814_OUT3_ENGINE_CH_ENGINE3_gc
#define ENGINE0_ORDER0_PATTERN0_gc                         LP5814_ENGINE0_ORDER0_PATTERN0_gc
#define ENGINE0_ORDER0_PATTERN1_gc                         LP5814_ENGINE0_ORDER0_PATTERN1_gc
#define ENGINE0_ORDER0_PATTERN2_gc                         LP5814_ENGINE0_ORDER0_PATTERN2_gc
#define ENGINE0_ORDER0_PATTERN3_gc                         LP5814_ENGINE0_ORDER0_PATTERN3_gc
#define ENGINE0_ORDER1_PATTERN0_gc                         LP5814_ENGINE0_ORDER1_PATTERN0_gc
#define ENGINE0_ORDER1_PATTERN1_gc                         LP5814_ENGINE0_ORDER1_PATTERN1_gc
#define ENGINE0_ORDER1_PATTERN2_gc                         LP5814_ENGINE0_ORDER1_PATTERN2_gc
#define ENGINE0_ORDER1_PATTERN3_gc                         LP5814_ENGINE0_ORDER1_PATTERN3_gc
#define ENGINE0_ORDER2_PATTERN0_gc                         LP5814_ENGINE0_ORDER2_PATTERN0_gc
#define ENGINE0_ORDER2_PATTERN1_gc                         LP5814_ENGINE0_ORDER2_PATTERN1_gc
#define ENGINE0_ORDER2_PATTERN2_gc                         LP5814_ENGINE0_ORDER2_PATTERN2_gc
#define ENGINE0_ORDER2_PATTERN3_gc                         LP5814_ENGINE0_ORDER2_PATTERN3_gc
#define ENGINE0_ORDER3_PATTERN0_gc                         LP5814_ENGINE0_ORDER3_PATTERN0_gc
#define ENGINE0_ORDER3_PATTERN1_gc                         LP5814_ENGINE0_ORDER3_PATTERN1_gc
#define ENGINE0_ORDER3_PATTERN2_gc                         LP5814_ENGINE0_ORDER3_PATTERN2_gc
#define ENGINE0_ORDER3_PATTERN3_gc                         LP5814_ENGINE0_ORDER3_PATTERN3_gc
#define ENGINE1_ORDER0_PATTERN0_gc                         LP5814_ENGINE1_ORDER0_PATTERN0_gc
#define ENGINE1_ORDER0_PATTERN1_gc                         LP5814_ENGINE1_ORDER0_PATTERN1_gc
#define ENGINE1_ORDER0_PATTERN2_gc                         LP5814_ENGINE1_ORDER0_PATTERN2_gc
#define ENGINE1_ORDER0_PATTERN3_gc                         LP5814_ENGINE1_ORDER0_PATTERN3_gc
#define ENGINE1_ORDER1_PATTERN0_gc                         LP5814_ENGINE1_ORDER1_PATTERN0_gc
#define ENGINE1_ORDER1_PATTERN1_gc                         LP5814_ENGINE1_ORDER1_PATTERN1_gc
#define ENGINE1_ORDER1_PATTERN2_gc                         LP5814_ENGINE1_ORDER1_PATTERN2_gc
#define ENGINE1_ORDER1_PATTERN3_gc                         LP5814_ENGINE1_ORDER1_PATTERN3_gc
#define ENGINE1_ORDER2_PATTERN0_gc                         LP5814_ENGINE1_ORDER2_PATTERN0_gc
#define ENGINE1_ORDER2_PATTERN1_gc                         LP5814_ENGINE1_ORDER2_PATTERN1_gc
#define ENGINE1_ORDER2_PATTERN2_gc                         LP5814_ENGINE1_ORDER2_PATTERN2_gc
#define ENGINE1_ORDER2_PATTERN3_gc                         LP5814_ENGINE1_ORDER2_PATTERN3_gc
#define ENGINE1_ORDER3_PATTERN0_gc                         LP5814_ENGINE1_ORDER3_PATTERN0_gc
#define ENGINE1_ORDER3_PATTERN1_gc                         LP5814_ENGINE1_ORDER3_PATTERN1_gc
#define ENGINE1_ORDER3_PATTERN2_gc                         LP5814_ENGINE1_ORDER3_PATTERN2_gc
#define ENGINE1_ORDER3_PATTERN3_gc                         LP5814_ENGINE1_ORDER3_PATTERN3_gc
#define ENGINE2_ORDER0_PATTERN0_gc                         LP5814_ENGINE2_ORDER0_PATTERN0_gc
#define ENGINE2_ORDER0_PATTERN1_gc                         LP5814_ENGINE2_ORDER0_PATTERN1_gc
#define ENGINE2_ORDER0_PATTERN2_gc                         LP5814_ENGINE2_ORDER0_PATTERN2_gc
#define ENGINE2_ORDER0_PATTERN3_gc                         LP5814_ENGINE2_ORDER0_PATTERN3_gc
#define ENGINE2_ORDER1_PATTERN0_gc                         LP5814_ENGINE2_ORDER1_PATTERN0_gc
#define ENGINE2_ORDER1_PATTERN1_gc                         LP5814_ENGINE2_ORDER1_PATTERN1_gc
#define ENGINE2_ORDER1_PATTERN2_gc                         LP5814_ENGINE2_ORDER1_PATTERN2_gc
#define ENGINE2_ORDER1_PATTERN3_gc                         LP5814_ENGINE2_ORDER1_PATTERN3_gc
#define ENGINE2_ORDER2_PATTERN0_gc                         LP5814_ENGINE2_ORDER2_PATTERN0_gc
#define ENGINE2_ORDER2_PATTERN1_gc                         LP5814_ENGINE2_ORDER2_PATTERN1_gc
#define ENGINE2_ORDER2_PATTERN2_gc                         LP5814_ENGINE2_ORDER2_PATTERN2_gc
#define ENGINE2_ORDER2_PATTERN3_gc                         LP5814_ENGINE2_ORDER2_PATTERN3_gc
#define ENGINE2_ORDER3_PATTERN0_gc                         LP5814_ENGINE2_ORDER3_PATTERN0_gc
#define ENGINE2_ORDER3_PATTERN1_gc                         LP5814_ENGINE2_ORDER3_PATTERN1_gc
#define ENGINE2_ORDER3_PATTERN2_gc                         LP5814_ENGINE2_ORDER3_PATTERN2_gc
#define ENGINE2_ORDER3_PATTERN3_gc                         LP5814_ENGINE2_ORDER3_PATTERN3_gc
#define ENGINE3_ORDER0_PATTERN0_gc                         LP5814_ENGINE3_ORDER0_PATTERN0_gc
#define ENGINE3_ORDER0_PATTERN1_gc                         LP5814_ENGINE3_ORDER0_PATTERN1_gc
#define ENGINE3_ORDER0_PATTERN2_gc                         LP5814_ENGINE3_ORDER0_PATTERN2_gc
#define ENGINE3_ORDER0_PATTERN3_gc                         LP5814_ENGINE3_ORDER0_PATTERN3_gc
#define ENGINE3_ORDER1_PATTERN0_gc                         LP5814_ENGINE3_ORDER1_PATTERN0_gc
#define ENGINE3_ORDER1_PATTERN1_gc                         LP5814_ENGINE3_ORDER1_PATTERN1_gc
#define ENGINE3_ORDER1_PATTERN2_gc                         LP5814_ENGINE3_ORDER1_PATTERN2_gc
#define ENGINE3_ORDER1_PATTERN3_gc                         LP5814_ENGINE3_ORDER1_PATTERN3_gc
#define ENGINE3_ORDER2_PATTERN0_gc                         LP5814_ENGINE3_ORDER2_PATTERN0_gc
#define ENGINE3_ORDER2_PATTERN1_gc                         LP5814_ENGINE3_ORDER2_PATTERN1_gc
#define ENGINE3_ORDER2_PATTERN2_gc                         LP5814_ENGINE3_ORDER2_PATTERN2_gc
#define ENGINE3_ORDER2_PATTERN3_gc                         LP5814_ENGINE3_ORDER2_PATTERN3_gc
#define ENGINE3_ORDER3_PATTERN0_gc                         LP5814_ENGINE3_ORDER3_PATTERN0_gc
#define ENGINE3_ORDER3_PATTERN1_gc                         LP5814_ENGINE3_ORDER3_PATTERN1_gc
#define ENGINE3_ORDER3_PATTERN2_gc                         LP5814_ENGINE3_ORDER3_PATTERN2_gc
#define ENGINE3_ORDER3_PATTERN3_gc                         LP5814_ENGINE3_ORDER3_PATTERN3_gc
#define ENGINE0_REPT_NONE_gc                               LP5814_ENGINE0_REPT_NONE_gc
#define ENGINE0_REPT_ONCE_gc                               LP5814_ENGINE0_REPT_ONCE_gc
#define ENGINE0_REPT_TWICE_gc                              LP5814_ENGINE0_REPT_TWICE_gc
#define ENGINE0_REPT_INFINITE_gc                           LP5814_ENGINE0_REPT_INFINITE_gc
#define ENGINE1_REPT_NONE_gc                               LP5814_ENGINE1_REPT_NONE_gc
#define ENGINE1_REPT_ONCE_gc                               LP5814_ENGINE1_REPT_ONCE_gc
#define ENGINE1_REPT_TWICE_gc                              LP5814_ENGINE1_REPT_TWICE_gc
#define ENGINE1_REPT_INFINITE_gc                           LP5814_ENGINE1_REPT_INFINITE_gc
#define ENGINE2_REPT_NONE_gc                               LP5814_ENGINE2_REPT_NONE_gc
#define ENGINE2_REPT_ONCE_gc                               LP5814_ENGINE2_REPT_ONCE_gc
#define ENGINE2_REPT_TWICE_gc                              LP5814_ENGINE2_REPT_TWICE_gc
#define ENGINE2_REPT_INFINITE_gc                           LP5814_ENGINE2_REPT_INFINITE_gc
#define ENGINE3_REPT_NONE_gc                               LP5814_ENGINE3_REPT_NONE_gc
#define ENGINE3_REPT_ONCE_gc                               LP5814_ENGINE3_REPT_ONCE_gc
#define ENGINE3_REPT_TWICE_gc                              LP5814_ENGINE3_REPT_TWICE_gc
#define ENGINE3_REPT_INFINITE_gc                           LP5814_ENGINE3_REPT_INFINITE_gc
#define PATTERN0_PT_REPEAT0_gc                             LP5814_PATTERN0_PT_REPEAT0_gc
#define PATTERN0_PT_REPEAT1_gc                             LP5814_PATTERN0_PT_REPEAT1_gc
#define PATTERN0_PT_REPEAT2_gc                             LP5814_PATTERN0_PT_REPEAT2_gc
#define PATTERN0_PT_REPEAT3_gc                             LP5814_PATTERN0_PT_REPEAT3_gc
#define PATTERN0_PT_REPEAT4_gc                             LP5814_PATTERN0_PT_REPEAT4_gc
#define PATTERN0_PT_REPEAT5_gc                             LP5814_PATTERN0_PT_REPEAT5_gc
#define PATTERN0_PT_REPEAT6_gc                             LP5814_PATTERN0_PT_REPEAT6_gc
#define PATTERN0_PT_REPEAT7_gc                             LP5814_PATTERN0_PT_REPEAT7_gc
#define PATTERN0_PT_REPEAT8_gc                             LP5814_PATTERN0_PT_REPEAT8_gc
#define PATTERN0_PT_REPEAT9_gc                             LP5814_PATTERN0_PT_REPEAT9_gc
#define PATTERN0_PT_REPEAT10_gc                            LP5814_PATTERN0_PT_REPEAT10_gc
#define PATTERN0_PT_REPEAT11_gc                            LP5814_PATTERN0_PT_REPEAT11_gc
#define PATTERN0_PT_REPEAT12_gc                            LP5814_PATTERN0_PT_REPEAT12_gc
#define PATTERN0_PT_REPEAT13_gc                            LP5814_PATTERN0_PT_REPEAT13_gc
#define PATTERN0_PT_REPEAT14_gc                            LP5814_PATTERN0_PT_REPEAT14_gc
#define PATTERN0_PT_INFINITE_gc                            LP5814_PATTERN0_PT_INFINITE_gc
#define PATTERN1_PT_REPEAT0_gc                             LP5814_PATTERN1_PT_REPEAT0_gc
#define PATTERN1_PT_REPEAT1_gc                             LP5814_PATTERN1_PT_REPEAT1_gc
#define PATTERN1_PT_REPEAT2_gc                             LP5814_PATTERN1_PT_REPEAT2_gc
#define PATTERN1_PT_REPEAT3_gc                             LP5814_PATTERN1_PT_REPEAT3_gc
#define PATTERN1_PT_REPEAT4_gc                             LP5814_PATTERN1_PT_REPEAT4_gc
#define PATTERN1_PT_REPEAT5_gc                             LP5814_PATTERN1_PT_REPEAT5_gc
#define PATTERN1_PT_REPEAT6_gc                             LP5814_PATTERN1_PT_REPEAT6_gc
#define PATTERN1_PT_REPEAT7_gc                             LP5814_PATTERN1_PT_REPEAT7_gc
#define PATTERN1_PT_REPEAT8_gc                             LP5814_PATTERN1_PT_REPEAT8_gc
#define PATTERN1_PT_REPEAT9_gc                             LP5814_PATTERN1_PT_REPEAT9_gc
#define PATTERN1_PT_REPEAT10_gc                            LP5814_PATTERN1_PT_REPEAT10_gc
#define PATTERN1_PT_REPEAT11_gc                            LP5814_PATTERN1_PT_REPEAT11_gc
#define PATTERN1_PT_REPEAT12_gc                            LP5814_PATTERN1_PT_REPEAT12_gc
#define PATTERN1_PT_REPEAT13_gc                            LP5814_PATTERN1_PT_REPEAT13_gc
#define PATTERN1_PT_REPEAT14_gc                            LP5814_PATTERN1_PT_REPEAT14_gc
#define PATTERN1_PT_INFINITE_gc                            LP5814_PATTERN1_PT_INFINITE_gc
#define PATTERN2_PT_REPEAT0_gc                             LP5814_PATTERN2_PT_REPEAT0_gc
#define PATTERN2_PT_REPEAT1_gc                             LP5814_PATTERN2_PT_REPEAT1_gc
#define PATTERN2_PT_REPEAT2_gc                             LP5814_PATTERN2_PT_REPEAT2_gc
#define PATTERN2_PT_REPEAT3_gc                             LP5814_PATTERN2_PT_REPEAT3_gc
#define PATTERN2_PT_REPEAT4_gc                             LP5814_PATTERN2_PT_REPEAT4_gc
#define PATTERN2_PT_REPEAT5_gc                             LP5814_PATTERN2_PT_REPEAT5_gc
#define PATTERN2_PT_REPEAT6_gc                             LP5814_PATTERN2_PT_REPEAT6_gc
#define PATTERN2_PT_REPEAT7_gc                             LP5814_PATTERN2_PT_REPEAT7_gc
#define PATTERN2_PT_REPEAT8_gc                             LP5814_PATTERN2_PT_REPEAT8_gc
#define PATTERN2_PT_REPEAT9_gc                             LP5814_PATTERN2_PT_REPEAT9_gc
#define PATTERN2_PT_REPEAT10_gc                            LP5814_PATTERN2_PT_REPEAT10_gc
#define PATTERN2_PT_REPEAT11_gc                            LP5814_PATTERN2_PT_REPEAT11_gc
#define PATTERN2_PT_REPEAT12_gc                            LP5814_PATTERN2_PT_REPEAT12_gc
#define PATTERN2_PT_REPEAT13_gc                            LP5814_PATTERN2_PT_REPEAT13_gc
#define PATTERN2_PT_REPEAT14_gc                            LP5814_PATTERN2_PT_REPEAT14_gc
#define PATTERN2_PT_INFINITE_gc                            LP5814_PATTERN2_PT_INFINITE_gc
#define PATTERN3_PT_REPEAT0_gc                             LP5814_PATTERN3_PT_REPEAT0_gc
#define PATTERN3_PT_REPEAT1_gc                             LP5814_PATTERN3_PT_REPEAT1_gc
#define PATTERN3_PT_REPEAT2_gc                             LP5814_PATTERN3_PT_REPEAT2_gc
#define PATTERN3_PT_REPEAT3_gc                             LP5814_PATTERN3_PT_REPEAT3_gc
#define PATTERN3_PT_REPEAT4_gc                             LP5814_PATTERN3_PT_REPEAT4_gc
#define PATTERN3_PT_REPEAT5_gc                             LP5814_PATTERN3_PT_REPEAT5_gc
#define PATTERN3_PT_REPEAT6_gc                             LP5814_PATTERN3_PT_REPEAT6_gc
#define PATTERN3_PT_REPEAT7_gc                             LP5814_PATTERN3_PT_REPEAT7_gc
#define PATTERN3_PT_REPEAT8_gc                             LP5814_PATTERN3_PT_REPEAT8_gc
#define PATTERN3_PT_REPEAT9_gc                             LP5814_PATTERN3_PT_REPEAT9_gc
#define PATTERN3_PT_REPEAT10_gc                            LP5814_PATTERN3_PT_REPEAT10_gc
#define PATTERN3_PT_REPEAT11_gc                            LP5814_PATTERN3_PT_REPEAT11_gc
#define PATTERN3_PT_REPEAT12_gc                            LP5814_PATTERN3_PT_REPEAT12_gc
#define PATTERN3_PT_REPEAT13_gc                            LP5814_PATTERN3_PT_REPEAT13_gc
#define PATTERN3_PT_REPEAT14_gc                            LP5814_PATTERN3_PT_REPEAT14_gc
#define PATTERN3_PT_INFINITE_gc                            LP5814_PATTERN3_PT_INFINITE_gc
#define PATTERN0_PAUSE_T0_0MS_gc                           LP5814_PATTERN0_PAUSE_T0_0MS_gc
#define PATTERN0_PAUSE_T0_50MS_gc                          LP5814_PATTERN0_PAUSE_T0_50MS_gc
#define PATTERN0_PAUSE_T0_100MS_gc                         LP5814_PATTERN0_PAUSE_T0_100MS_gc
#define PATTERN0_PAUSE_T0_150MS_gc                         LP5814_PATTERN0_PAUSE_T0_150MS_gc
#define PATTERN0_PAUSE_T0_200MS_gc                         LP5814_PATTERN0_PAUSE_T0_200MS_gc
#define PATTERN0_PAUSE_T0_250MS_gc                         LP5814_PATTERN0_PAUSE_T0_250MS_gc
#define PATTERN0_PAUSE_T0_300MS_gc                         LP5814_PATTERN0_PAUSE_T0_300MS_gc
#define PATTERN0_PAUSE_T0_350MS_gc                         LP5814_PATTERN0_PAUSE_T0_350MS_gc
#define PATTERN0_PAUSE_T0_400MS_gc                         LP5814_PATTERN0_PAUSE_T0_400MS_gc
#define PATTERN0_PAUSE_T0_450MS_gc                         LP5814_PATTERN0_PAUSE_T0_450MS_gc
#define PATTERN0_PAUSE_T0_500MS_gc                         LP5814_PATTERN0_PAUSE_T0_500MS_gc
#define PATTERN0_PAUSE_T0_1000MS_gc                        LP5814_PATTERN0_PAUSE_T0_1000MS_gc
#define PATTERN0_PAUSE_T0_2000MS_gc                        LP5814_PATTERN0_PAUSE_T0_2000MS_gc
#define PATTERN0_PAUSE_T0_4000MS_gc                        LP5814_PATTERN0_PAUSE_T0_4000MS_gc
#define PATTERN0_PAUSE_T0_6000MS_gc                        LP5814_PATTERN0_PAUSE_T0_6000MS_gc
#define PATTERN0_PAUSE_T0_8000MS_gc                        LP5814_PATTERN0_PAUSE_T0_8000MS_gc
#define PATTERN0_PAUSE_T1_0MS_gc                           LP5814_PATTERN0_PAUSE_T1_0MS_gc
#define PATTERN0_PAUSE_T1_50MS_gc                          LP5814_PATTERN0_PAUSE_T1_50MS_gc
#define PATTERN0_PAUSE_T1_100MS_gc                         LP5814_PATTERN0_PAUSE_T1_100MS_gc
#define PATTERN0_PAUSE_T1_150MS_gc                         LP5814_PATTERN0_PAUSE_T1_150MS_gc
#define PATTERN0_PAUSE_T1_200MS_gc                         LP5814_PATTERN0_PAUSE_T1_200MS_gc
#define PATTERN0_PAUSE_T1_250MS_gc                         LP5814_PATTERN0_PAUSE_T1_250MS_gc
#define PATTERN0_PAUSE_T1_300MS_gc                         LP5814_PATTERN0_PAUSE_T1_300MS_gc
#define PATTERN0_PAUSE_T1_350MS_gc                         LP5814_PATTERN0_PAUSE_T1_350MS_gc
#define PATTERN0_PAUSE_T1_400MS_gc                         LP5814_PATTERN0_PAUSE_T1_400MS_gc
#define PATTERN0_PAUSE_T1_450MS_gc                         LP5814_PATTERN0_PAUSE_T1_450MS_gc
#define PATTERN0_PAUSE_T1_500MS_gc                         LP5814_PATTERN0_PAUSE_T1_500MS_gc
#define PATTERN0_PAUSE_T1_1000MS_gc                        LP5814_PATTERN0_PAUSE_T1_1000MS_gc
#define PATTERN0_PAUSE_T1_2000MS_gc                        LP5814_PATTERN0_PAUSE_T1_2000MS_gc
#define PATTERN0_PAUSE_T1_4000MS_gc                        LP5814_PATTERN0_PAUSE_T1_4000MS_gc
#define PATTERN0_PAUSE_T1_6000MS_gc                        LP5814_PATTERN0_PAUSE_T1_6000MS_gc
#define PATTERN0_PAUSE_T1_8000MS_gc                        LP5814_PATTERN0_PAUSE_T1_8000MS_gc
#define PATTERN0_SLOPER_T0_0MS_gc                          LP5814_PATTERN0_SLOPER_T0_0MS_gc
#define PATTERN0_SLOPER_T0_50MS_gc                         LP5814_PATTERN0_SLOPER_T0_50MS_gc
#define PATTERN0_SLOPER_T0_100MS_gc                        LP5814_PATTERN0_SLOPER_T0_100MS_gc
#define PATTERN0_SLOPER_T0_150MS_gc                        LP5814_PATTERN0_SLOPER_T0_150MS_gc
#define PATTERN0_SLOPER_T0_200MS_gc                        LP5814_PATTERN0_SLOPER_T0_200MS_gc
#define PATTERN0_SLOPER_T0_250MS_gc                        LP5814_PATTERN0_SLOPER_T0_250MS_gc
#define PATTERN0_SLOPER_T0_300MS_gc                        LP5814_PATTERN0_SLOPER_T0_300MS_gc
#define PATTERN0_SLOPER_T0_350MS_gc                        LP5814_PATTERN0_SLOPER_T0_350MS_gc
#define PATTERN0_SLOPER_T0_400MS_gc                        LP5814_PATTERN0_SLOPER_T0_400MS_gc
#define PATTERN0_SLOPER_T0_450MS_gc                        LP5814_PATTERN0_SLOPER_T0_450MS_gc
#define PATTERN0_SLOPER_T0_500MS_gc                        LP5814_PATTERN0_SLOPER_T0_500MS_gc
#define PATTERN0_SLOPER_T0_1000MS_gc                       LP5814_PATTERN0_SLOPER_T0_1000MS_gc
#define PATTERN0_SLOPER_T0_2000MS_gc                       LP5814_PATTERN0_SLOPER_T0_2000MS_gc
#define PATTERN0_SLOPER_T0_4000MS_gc                       LP5814_PATTERN0_SLOPER_T0_4000MS_gc
#define PATTERN0_SLOPER_T0_6000MS_gc                       LP5814_PATTERN0_SLOPER_T0_6000MS_gc
#define PATTERN0_SLOPER_T0_8000MS_gc                       LP5814_PATTERN0_SLOPER_T0_8000MS_gc
#define PATTERN0_SLOPER_T1_0MS_gc                          LP5814_PATTERN0_SLOPER_T1_0MS_gc
#define PATTERN0_SLOPER_T1_50MS_gc                         LP5814_PATTERN0_SLOPER_T1_50MS_gc
#define PATTERN0_SLOPER_T1_100MS_gc                        LP5814_PATTERN0_SLOPER_T1_100MS_gc
#define PATTERN0_SLOPER_T1_150MS_gc                        LP5814_PATTERN0_SLOPER_T1_150MS_gc
#define PATTERN0_SLOPER_T1_200MS_gc                        LP5814_PATTERN0_SLOPER_T1_200MS_gc
#define PATTERN0_SLOPER_T1_250MS_gc                        LP5814_PATTERN0_SLOPER_T1_250MS_gc
#define PATTERN0_SLOPER_T1_300MS_gc                        LP5814_PATTERN0_SLOPER_T1_300MS_gc
#define PATTERN0_SLOPER_T1_350MS_gc                        LP5814_PATTERN0_SLOPER_T1_350MS_gc
#define PATTERN0_SLOPER_T1_400MS_gc                        LP5814_PATTERN0_SLOPER_T1_400MS_gc
#define PATTERN0_SLOPER_T1_450MS_gc                        LP5814_PATTERN0_SLOPER_T1_450MS_gc
#define PATTERN0_SLOPER_T1_500MS_gc                        LP5814_PATTERN0_SLOPER_T1_500MS_gc
#define PATTERN0_SLOPER_T1_1000MS_gc                       LP5814_PATTERN0_SLOPER_T1_1000MS_gc
#define PATTERN0_SLOPER_T1_2000MS_gc                       LP5814_PATTERN0_SLOPER_T1_2000MS_gc
#define PATTERN0_SLOPER_T1_4000MS_gc                       LP5814_PATTERN0_SLOPER_T1_4000MS_gc
#define PATTERN0_SLOPER_T1_6000MS_gc                       LP5814_PATTERN0_SLOPER_T1_6000MS_gc
#define PATTERN0_SLOPER_T1_8000MS_gc                       LP5814_PATTERN0_SLOPER_T1_8000MS_gc
#define PATTERN0_SLOPER_T2_0MS_gc                          LP5814_PATTERN0_SLOPER_T2_0MS_gc
#define PATTERN0_SLOPER_T2_50MS_gc                         LP5814_PATTERN0_SLOPER_T2_50MS_gc
#define PATTERN0_SLOPER_T2_100MS_gc                        LP5814_PATTERN0_SLOPER_T2_100MS_gc
#define PATTERN0_SLOPER_T2_150MS_gc                        LP5814_PATTERN0_SLOPER_T2_150MS_gc
#define PATTERN0_SLOPER_T2_200MS_gc                        LP5814_PATTERN0_SLOPER_T2_200MS_gc
#define PATTERN0_SLOPER_T2_250MS_gc                        LP5814_PATTERN0_SLOPER_T2_250MS_gc
#define PATTERN0_SLOPER_T2_300MS_gc                        LP5814_PATTERN0_SLOPER_T2_300MS_gc
#define PATTERN0_SLOPER_T2_350MS_gc                        LP5814_PATTERN0_SLOPER_T2_350MS_gc
#define PATTERN0_SLOPER_T2_400MS_gc                        LP5814_PATTERN0_SLOPER_T2_400MS_gc
#define PATTERN0_SLOPER_T2_450MS_gc                        LP5814_PATTERN0_SLOPER_T2_450MS_gc
#define PATTERN0_SLOPER_T2_500MS_gc                        LP5814_PATTERN0_SLOPER_T2_500MS_gc
#define PATTERN0_SLOPER_T2_1000MS_gc                       LP5814_PATTERN0_SLOPER_T2_1000MS_gc
#define PATTERN0_SLOPER_T2_2000MS_gc                       LP5814_PATTERN0_SLOPER_T2_2000MS_gc
#define PATTERN0_SLOPER_T2_4000MS_gc                       LP5814_PATTERN0_SLOPER_T2_4000MS_gc
#define PATTERN0_SLOPER_T2_6000MS_gc                       LP5814_PATTERN0_SLOPER_T2_6000MS_gc
#define PATTERN0_SLOPER_T2_8000MS_gc                       LP5814_PATTERN0_SLOPER_T2_8000MS_gc
#define PATTERN0_SLOPER_T3_0MS_gc                          LP5814_PATTERN0_SLOPER_T3_0MS_gc
#define PATTERN0_SLOPER_T3_50MS_gc                         LP5814_PATTERN0_SLOPER_T3_50MS_gc
#define PATTERN0_SLOPER_T3_100MS_gc                        LP5814_PATTERN0_SLOPER_T3_100MS_gc
#define PATTERN0_SLOPER_T3_150MS_gc                        LP5814_PATTERN0_SLOPER_T3_150MS_gc
#define PATTERN0_SLOPER_T3_200MS_gc                        LP5814_PATTERN0_SLOPER_T3_200MS_gc
#define PATTERN0_SLOPER_T3_250MS_gc                        LP5814_PATTERN0_SLOPER_T3_250MS_gc
#define PATTERN0_SLOPER_T3_300MS_gc                        LP5814_PATTERN0_SLOPER_T3_300MS_gc
#define PATTERN0_SLOPER_T3_350MS_gc                        LP5814_PATTERN0_SLOPER_T3_350MS_gc
#define PATTERN0_SLOPER_T3_400MS_gc                        LP5814_PATTERN0_SLOPER_T3_400MS_gc
#define PATTERN0_SLOPER_T3_450MS_gc                        LP5814_PATTERN0_SLOPER_T3_450MS_gc
#define PATTERN0_SLOPER_T3_500MS_gc                        LP5814_PATTERN0_SLOPER_T3_500MS_gc
#define PATTERN0_SLOPER_T3_1000MS_gc                       LP5814_PATTERN0_SLOPER_T3_1000MS_gc
#define PATTERN0_SLOPER_T3_2000MS_gc                       LP5814_PATTERN0_SLOPER_T3_2000MS_gc
#define PATTERN0_SLOPER_T3_4000MS_gc                       LP5814_PATTERN0_SLOPER_T3_4000MS_gc
#define PATTERN0_SLOPER_T3_6000MS_gc                       LP5814_PATTERN0_SLOPER_T3_6000MS_gc
#define PATTERN0_SLOPER_T3_8000MS_gc                       LP5814_PATTERN0_SLOPER_T3_8000MS_gc
#define PATTERN1_PAUSE_T0_0MS_gc                           LP5814_PATTERN1_PAUSE_T0_0MS_gc
#define PATTERN1_PAUSE_T0_50MS_gc                          LP5814_PATTERN1_PAUSE_T0_50MS_gc
#define PATTERN1_PAUSE_T0_100MS_gc                         LP5814_PATTERN1_PAUSE_T0_100MS_gc
#define PATTERN1_PAUSE_T0_150MS_gc                         LP5814_PATTERN1_PAUSE_T0_150MS_gc
#define PATTERN1_PAUSE_T0_200MS_gc                         LP5814_PATTERN1_PAUSE_T0_200MS_gc
#define PATTERN1_PAUSE_T0_250MS_gc                         LP5814_PATTERN1_PAUSE_T0_250MS_gc
#define PATTERN1_PAUSE_T0_300MS_gc                         LP5814_PATTERN1_PAUSE_T0_300MS_gc
#define PATTERN1_PAUSE_T0_350MS_gc                         LP5814_PATTERN1_PAUSE_T0_350MS_gc
#define PATTERN1_PAUSE_T0_400MS_gc                         LP5814_PATTERN1_PAUSE_T0_400MS_gc
#define PATTERN1_PAUSE_T0_450MS_gc                         LP5814_PATTERN1_PAUSE_T0_450MS_gc
#define PATTERN1_PAUSE_T0_500MS_gc                         LP5814_PATTERN1_PAUSE_T0_500MS_gc
#define PATTERN1_PAUSE_T0_1000MS_gc                        LP5814_PATTERN1_PAUSE_T0_1000MS_gc
#define PATTERN1_PAUSE_T0_2000MS_gc                        LP5814_PATTERN1_PAUSE_T0_2000MS_gc
#define PATTERN1_PAUSE_T0_4000MS_gc                        LP5814_PATTERN1_PAUSE_T0_4000MS_gc
#define PATTERN1_PAUSE_T0_6000MS_gc                        LP5814_PATTERN1_PAUSE_T0_6000MS_gc
#define PATTERN1_PAUSE_T0_8000MS_gc                        LP5814_PATTERN1_PAUSE_T0_8000MS_gc
#define PATTERN1_PAUSE_T1_0MS_gc                           LP5814_PATTERN1_PAUSE_T1_0MS_gc
#define PATTERN1_PAUSE_T1_50MS_gc                          LP5814_PATTERN1_PAUSE_T1_50MS_gc
#define PATTERN1_PAUSE_T1_100MS_gc                         LP5814_PATTERN1_PAUSE_T1_100MS_gc
#define PATTERN1_PAUSE_T1_150MS_gc                         LP5814_PATTERN1_PAUSE_T1_150MS_gc
#define PATTERN1_PAUSE_T1_200MS_gc                         LP5814_PATTERN1_PAUSE_T1_200MS_gc
#define PATTERN1_PAUSE_T1_250MS_gc                         LP5814_PATTERN1_PAUSE_T1_250MS_gc
#define PATTERN1_PAUSE_T1_300MS_gc                         LP5814_PATTERN1_PAUSE_T1_300MS_gc
#define PATTERN1_PAUSE_T1_350MS_gc                         LP5814_PATTERN1_PAUSE_T1_350MS_gc
#define PATTERN1_PAUSE_T1_400MS_gc                         LP5814_PATTERN1_PAUSE_T1_400MS_gc
#define PATTERN1_PAUSE_T1_450MS_gc                         LP5814_PATTERN1_PAUSE_T1_450MS_gc
#define PATTERN1_PAUSE_T1_500MS_gc                         LP5814_PATTERN1_PAUSE_T1_500MS_gc
#define PATTERN1_PAUSE_T1_1000MS_gc                        LP5814_PATTERN1_PAUSE_T1_1000MS_gc
#define PATTERN1_PAUSE_T1_2000MS_gc                        LP5814_PATTERN1_PAUSE_T1_2000MS_gc
#define PATTERN1_PAUSE_T1_4000MS_gc                        LP5814_PATTERN1_PAUSE_T1_4000MS_gc
#define PATTERN1_PAUSE_T1_6000MS_gc                        LP5814_PATTERN1_PAUSE_T1_6000MS_gc
#define PATTERN1_PAUSE_T1_8000MS_gc                        LP5814_PATTERN1_PAUSE_T1_8000MS_gc
#define PATTERN1_SLOPER_T0_0MS_gc                          LP5814_PATTERN1_SLOPER_T0_0MS_gc
#define PATTERN1_SLOPER_T0_50MS_gc                         LP5814_PATTERN1_SLOPER_T0_50MS_gc
#define PATTERN1_SLOPER_T0_100MS_gc                        LP5814_PATTERN1_SLOPER_T0_100MS_gc
#define PATTERN1_SLOPER_T0_150MS_gc                        LP5814_PATTERN1_SLOPER_T0_150MS_gc
#define PATTERN1_SLOPER_T0_200MS_gc                        LP5814_PATTERN1_SLOPER_T0_200MS_gc
#define PATTERN1_SLOPER_T0_250MS_gc                        LP5814_PATTERN1_SLOPER_T0_250MS_gc
#define PATTERN1_SLOPER_T0_300MS_gc                        LP5814_PATTERN1_SLOPER_T0_300MS_gc
#define PATTERN1_SLOPER_T0_350MS_gc                        LP5814_PATTERN1_SLOPER_T0_350MS_gc
#define PATTERN1_SLOPER_T0_400MS_gc                        LP5814_PATTERN1_SLOPER_T0_400MS_gc
#define PATTERN1_SLOPER_T0_450MS_gc                        LP5814_PATTERN1_SLOPER_T0_450MS_gc
#define PATTERN1_SLOPER_T0_500MS_gc                        LP5814_PATTERN1_SLOPER_T0_500MS_gc
#define PATTERN1_SLOPER_T0_1000MS_gc                       LP5814_PATTERN1_SLOPER_T0_1000MS_gc
#define PATTERN1_SLOPER_T0_2000MS_gc                       LP5814_PATTERN1_SLOPER_T0_2000MS_gc
#define PATTERN1_SLOPER_T0_4000MS_gc                       LP5814_PATTERN1_SLOPER_T0_4000MS_gc
#define PATTERN1_SLOPER_T0_6000MS_gc                       LP5814_PATTERN1_SLOPER_T0_6000MS_gc
#define PATTERN1_SLOPER_T0_8000MS_gc                       LP5814_PATTERN1_SLOPER_T0_8000MS_gc
#define PATTERN1_SLOPER_T1_0MS_gc                          LP5814_PATTERN1_SLOPER_T1_0MS_gc
#define PATTERN1_SLOPER_T1_50MS_gc                         LP5814_PATTERN1_SLOPER_T1_50MS_gc
#define PATTERN1_SLOPER_T1_100MS_gc                        LP5814_PATTERN1_SLOPER_T1_100MS_gc
#define PATTERN1_SLOPER_T1_150MS_gc                        LP5814_PATTERN1_SLOPER_T1_150MS_gc
#define PATTERN1_SLOPER_T1_200MS_gc                        LP5814_PATTERN1_SLOPER_T1_200MS_gc
#define PATTERN1_SLOPER_T1_250MS_gc                        LP5814_PATTERN1_SLOPER_T1_250MS_gc
#define PATTERN1_SLOPER_T1_300MS_gc                        LP5814_PATTERN1_SLOPER_T1_300MS_gc
#define PATTERN1_SLOPER_T1_350MS_gc                        LP5814_PATTERN1_SLOPER_T1_350MS_gc
#define PATTERN1_SLOPER_T1_400MS_gc                        LP5814_PATTERN1_SLOPER_T1_400MS_gc
#define PATTERN1_SLOPER_T1_450MS_gc                        LP5814_PATTERN1_SLOPER_T1_450MS_gc
#define PATTERN1_SLOPER_T1_500MS_gc                        LP5814_PATTERN1_SLOPER_T1_500MS_gc
#define PATTERN1_SLOPER_T1_1000MS_gc                       LP5814_PATTERN1_SLOPER_T1_1000MS_gc
#define PATTERN1_SLOPER_T1_2000MS_gc                       LP5814_PATTERN1_SLOPER_T1_2000MS_gc
#define PATTERN1_SLOPER_T1_4000MS_gc                       LP5814_PATTERN1_SLOPER_T1_4000MS_gc
#define PATTERN1_SLOPER_T1_6000MS_gc                       LP5814_PATTERN1_SLOPER_T1_6000MS_gc
#define PATTERN1_SLOPER_T1_8000MS_gc                       LP5814_PATTERN1_SLOPER_T1_8000MS_gc
#define PATTERN1_SLOPER_T2_0MS_gc                          LP5814_PATTERN1_SLOPER_T2_0MS_gc
#define PATTERN1_SLOPER_T2_50MS_gc                         LP5814_PATTERN1_SLOPER_T2_50MS_gc
#define PATTERN1_SLOPER_T2_100MS_gc                        LP5814_PATTERN1_SLOPER_T2_100MS_gc
#define PATTERN1_SLOPER_T2_150MS_gc                        LP5814_PATTERN1_SLOPER_T2_150MS_gc
#define PATTERN1_SLOPER_T2_200MS_gc                        LP5814_PATTERN1_SLOPER_T2_200MS_gc
#define PATTERN1_SLOPER_T2_250MS_gc                        LP5814_PATTERN1_SLOPER_T2_250MS_gc
#define PATTERN1_SLOPER_T2_300MS_gc                        LP5814_PATTERN1_SLOPER_T2_300MS_gc
#define PATTERN1_SLOPER_T2_350MS_gc                        LP5814_PATTERN1_SLOPER_T2_350MS_gc
#define PATTERN1_SLOPER_T2_400MS_gc                        LP5814_PATTERN1_SLOPER_T2_400MS_gc
#define PATTERN1_SLOPER_T2_450MS_gc                        LP5814_PATTERN1_SLOPER_T2_450MS_gc
#define PATTERN1_SLOPER_T2_500MS_gc                        LP5814_PATTERN1_SLOPER_T2_500MS_gc
#define PATTERN1_SLOPER_T2_1000MS_gc                       LP5814_PATTERN1_SLOPER_T2_1000MS_gc
#define PATTERN1_SLOPER_T2_2000MS_gc                       LP5814_PATTERN1_SLOPER_T2_2000MS_gc
#define PATTERN1_SLOPER_T2_4000MS_gc                       LP5814_PATTERN1_SLOPER_T2_4000MS_gc
#define PATTERN1_SLOPER_T2_6000MS_gc                       LP5814_PATTERN1_SLOPER_T2_6000MS_gc
#define PATTERN1_SLOPER_T2_8000MS_gc                       LP5814_PATTERN1_SLOPER_T2_8000MS_gc
#define PATTERN1_SLOPER_T3_0MS_gc                          LP5814_PATTERN1_SLOPER_T3_0MS_gc
#define PATTERN1_SLOPER_T3_50MS_gc                         LP5814_PATTERN1_SLOPER_T3_50MS_gc
#define PATTERN1_SLOPER_T3_100MS_gc                        LP5814_PATTERN1_SLOPER_T3_100MS_gc
#define PATTERN1_SLOPER_T3_150MS_gc                        LP5814_PATTERN1_SLOPER_T3_150MS_gc
#define PATTERN1_SLOPER_T3_200MS_gc                        LP5814_PATTERN1_SLOPER_T3_200MS_gc
#define PATTERN1_SLOPER_T3_250MS_gc                        LP5814_PATTERN1_SLOPER_T3_250MS_gc
#define PATTERN1_SLOPER_T3_300MS_gc                        LP5814_PATTERN1_SLOPER_T3_300MS_gc
#define PATTERN1_SLOPER_T3_350MS_gc                        LP5814_PATTERN1_SLOPER_T3_350MS_gc
#define PATTERN1_SLOPER_T3_400MS_gc                        LP5814_PATTERN1_SLOPER_T3_400MS_gc
#define PATTERN1_SLOPER_T3_450MS_gc                        LP5814_PATTERN1_SLOPER_T3_450MS_gc
#define PATTERN1_SLOPER_T3_500MS_gc                        LP5814_PATTERN1_SLOPER_T3_500MS_gc
#define PATTERN1_SLOPER_T3_1000MS_gc                       LP5814_PATTERN1_SLOPER_T3_1000MS_gc
#define PATTERN1_SLOPER_T3_2000MS_gc                       LP5814_PATTERN1_SLOPER_T3_2000MS_gc
#define PATTERN1_SLOPER_T3_4000MS_gc                       LP5814_PATTERN1_SLOPER_T3_4000MS_gc
#define PATTERN1_SLOPER_T3_6000MS_gc                       LP5814_PATTERN1_SLOPER_T3_6000MS_gc
#define PATTERN1_SLOPER_T3_8000MS_gc                       LP5814_PATTERN1_SLOPER_T3_8000MS_gc
#define PATTERN2_PAUSE_T0_0MS_gc                           LP5814_PATTERN2_PAUSE_T0_0MS_gc
#define PATTERN2_PAUSE_T0_50MS_gc                          LP5814_PATTERN2_PAUSE_T0_50MS_gc
#define PATTERN2_PAUSE_T0_100MS_gc                         LP5814_PATTERN2_PAUSE_T0_100MS_gc
#define PATTERN2_PAUSE_T0_150MS_gc                         LP5814_PATTERN2_PAUSE_T0_150MS_gc
#define PATTERN2_PAUSE_T0_200MS_gc                         LP5814_PATTERN2_PAUSE_T0_200MS_gc
#define PATTERN2_PAUSE_T0_250MS_gc                         LP5814_PATTERN2_PAUSE_T0_250MS_gc
#define PATTERN2_PAUSE_T0_300MS_gc                         LP5814_PATTERN2_PAUSE_T0_300MS_gc
#define PATTERN2_PAUSE_T0_350MS_gc                         LP5814_PATTERN2_PAUSE_T0_350MS_gc
#define PATTERN2_PAUSE_T0_400MS_gc                         LP5814_PATTERN2_PAUSE_T0_400MS_gc
#define PATTERN2_PAUSE_T0_450MS_gc                         LP5814_PATTERN2_PAUSE_T0_450MS_gc
#define PATTERN2_PAUSE_T0_500MS_gc                         LP5814_PATTERN2_PAUSE_T0_500MS_gc
#define PATTERN2_PAUSE_T0_1000MS_gc                        LP5814_PATTERN2_PAUSE_T0_1000MS_gc
#define PATTERN2_PAUSE_T0_2000MS_gc                        LP5814_PATTERN2_PAUSE_T0_2000MS_gc
#define PATTERN2_PAUSE_T0_4000MS_gc                        LP5814_PATTERN2_PAUSE_T0_4000MS_gc
#define PATTERN2_PAUSE_T0_6000MS_gc                        LP5814_PATTERN2_PAUSE_T0_6000MS_gc
#define PATTERN2_PAUSE_T0_8000MS_gc                        LP5814_PATTERN2_PAUSE_T0_8000MS_gc
#define PATTERN2_PAUSE_T1_0MS_gc                           LP5814_PATTERN2_PAUSE_T1_0MS_gc
#define PATTERN2_PAUSE_T1_50MS_gc                          LP5814_PATTERN2_PAUSE_T1_50MS_gc
#define PATTERN2_PAUSE_T1_100MS_gc                         LP5814_PATTERN2_PAUSE_T1_100MS_gc
#define PATTERN2_PAUSE_T1_150MS_gc                         LP5814_PATTERN2_PAUSE_T1_150MS_gc
#define PATTERN2_PAUSE_T1_200MS_gc                         LP5814_PATTERN2_PAUSE_T1_200MS_gc
#define PATTERN2_PAUSE_T1_250MS_gc                         LP5814_PATTERN2_PAUSE_T1_250MS_gc
#define PATTERN2_PAUSE_T1_300MS_gc                         LP5814_PATTERN2_PAUSE_T1_300MS_gc
#define PATTERN2_PAUSE_T1_350MS_gc                         LP5814_PATTERN2_PAUSE_T1_350MS_gc
#define PATTERN2_PAUSE_T1_400MS_gc                         LP5814_PATTERN2_PAUSE_T1_400MS_gc
#define PATTERN2_PAUSE_T1_450MS_gc                         LP5814_PATTERN2_PAUSE_T1_450MS_gc
#define PATTERN2_PAUSE_T1_500MS_gc                         LP5814_PATTERN2_PAUSE_T1_500MS_gc
#define PATTERN2_PAUSE_T1_1000MS_gc                        LP5814_PATTERN2_PAUSE_T1_1000MS_gc
#define PATTERN2_PAUSE_T1_2000MS_gc                        LP5814_PATTERN2_PAUSE_T1_2000MS_gc
#define PATTERN2_PAUSE_T1_4000MS_gc                        LP5814_PATTERN2_PAUSE_T1_4000MS_gc
#define PATTERN2_PAUSE_T1_6000MS_gc                        LP5814_PATTERN2_PAUSE_T1_6000MS_gc
#define PATTERN2_PAUSE_T1_8000MS_gc                        LP5814_PATTERN2_PAUSE_T1_8000MS_gc
#define PATTERN2_SLOPER_T0_0MS_gc                          LP5814_PATTERN2_SLOPER_T0_0MS_gc
#define PATTERN2_SLOPER_T0_50MS_gc                         LP5814_PATTERN2_SLOPER_T0_50MS_gc
#define PATTERN2_SLOPER_T0_100MS_gc                        LP5814_PATTERN2_SLOPER_T0_100MS_gc
#define PATTERN2_SLOPER_T0_150MS_gc                        LP5814_PATTERN2_SLOPER_T0_150MS_gc
#define PATTERN2_SLOPER_T0_200MS_gc                        LP5814_PATTERN2_SLOPER_T0_200MS_gc
#define PATTERN2_SLOPER_T0_250MS_gc                        LP5814_PATTERN2_SLOPER_T0_250MS_gc
#define PATTERN2_SLOPER_T0_300MS_gc                        LP5814_PATTERN2_SLOPER_T0_300MS_gc
#define PATTERN2_SLOPER_T0_350MS_gc                        LP5814_PATTERN2_SLOPER_T0_350MS_gc
#define PATTERN2_SLOPER_T0_400MS_gc                        LP5814_PATTERN2_SLOPER_T0_400MS_gc
#define PATTERN2_SLOPER_T0_450MS_gc                        LP5814_PATTERN2_SLOPER_T0_450MS_gc
#define PATTERN2_SLOPER_T0_500MS_gc                        LP5814_PATTERN2_SLOPER_T0_500MS_gc
#define PATTERN2_SLOPER_T0_1000MS_gc                       LP5814_PATTERN2_SLOPER_T0_1000MS_gc
#define PATTERN2_SLOPER_T0_2000MS_gc                       LP5814_PATTERN2_SLOPER_T0_2000MS_gc
#define PATTERN2_SLOPER_T0_4000MS_gc                       LP5814_PATTERN2_SLOPER_T0_4000MS_gc
#define PATTERN2_SLOPER_T0_6000MS_gc                       LP5814_PATTERN2_SLOPER_T0_6000MS_gc
#define PATTERN2_SLOPER_T0_8000MS_gc                       LP5814_PATTERN2_SLOPER_T0_8000MS_gc
#define PATTERN2_SLOPER_T1_0MS_gc                          LP5814_PATTERN2_SLOPER_T1_0MS_gc
#define PATTERN2_SLOPER_T1_50MS_gc                         LP5814_PATTERN2_SLOPER_T1_50MS_gc
#define PATTERN2_SLOPER_T1_100MS_gc                        LP5814_PATTERN2_SLOPER_T1_100MS_gc
#define PATTERN2_SLOPER_T1_150MS_gc                        LP5814_PATTERN2_SLOPER_T1_150MS_gc
#define PATTERN2_SLOPER_T1_200MS_gc                        LP5814_PATTERN2_SLOPER_T1_200MS_gc
#define PATTERN2_SLOPER_T1_250MS_gc                        LP5814_PATTERN2_SLOPER_T1_250MS_gc
#define PATTERN2_SLOPER_T1_300MS_gc                        LP5814_PATTERN2_SLOPER_T1_300MS_gc
#define PATTERN2_SLOPER_T1_350MS_gc                        LP5814_PATTERN2_SLOPER_T1_350MS_gc
#define PATTERN2_SLOPER_T1_400MS_gc                        LP5814_PATTERN2_SLOPER_T1_400MS_gc
#define PATTERN2_SLOPER_T1_450MS_gc                        LP5814_PATTERN2_SLOPER_T1_450MS_gc
#define PATTERN2_SLOPER_T1_500MS_gc                        LP5814_PATTERN2_SLOPER_T1_500MS_gc
#define PATTERN2_SLOPER_T1_1000MS_gc                       LP5814_PATTERN2_SLOPER_T1_1000MS_gc
#define PATTERN2_SLOPER_T1_2000MS_gc                       LP5814_PATTERN2_SLOPER_T1_2000MS_gc
#define PATTERN2_SLOPER_T1_4000MS_gc                       LP5814_PATTERN2_SLOPER_T1_4000MS_gc
#define PATTERN2_SLOPER_T1_6000MS_gc                       LP5814_PATTERN2_SLOPER_T1_6000MS_gc
#define PATTERN2_SLOPER_T1_8000MS_gc                       LP5814_PATTERN2_SLOPER_T1_8000MS_gc
#define PATTERN2_SLOPER_T2_0MS_gc                          LP5814_PATTERN2_SLOPER_T2_0MS_gc
#define PATTERN2_SLOPER_T2_50MS_gc                         LP5814_PATTERN2_SLOPER_T2_50MS_gc
#define PATTERN2_SLOPER_T2_100MS_gc                        LP5814_PATTERN2_SLOPER_T2_100MS_gc
#define PATTERN2_SLOPER_T2_150MS_gc                        LP5814_PATTERN2_SLOPER_T2_150MS_gc
#define PATTERN2_SLOPER_T2_200MS_gc                        LP5814_PATTERN2_SLOPER_T2_200MS_gc
#define PATTERN2_SLOPER_T2_250MS_gc                        LP5814_PATTERN2_SLOPER_T2_250MS_gc
#define PATTERN2_SLOPER_T2_300MS_gc                        LP5814_PATTERN2_SLOPER_T2_300MS_gc
#define PATTERN2_SLOPER_T2_350MS_gc                        LP5814_PATTERN2_SLOPER_T2_350MS_gc
#define PATTERN2_SLOPER_T2_400MS_gc                        LP5814_PATTERN2_SLOPER_T2_400MS_gc
#define PATTERN2_SLOPER_T2_450MS_gc                        LP5814_PATTERN2_SLOPER_T2_450MS_gc
#define PATTERN2_SLOPER_T2_500MS_gc                        LP5814_PATTERN2_SLOPER_T2_500MS_gc
#define PATTERN2_SLOPER_T2_1000MS_gc                       LP5814_PATTERN2_SLOPER_T2_1000MS_gc
#define PATTERN2_SLOPER_T2_2000MS_gc                       LP5814_PATTERN2_SLOPER_T2_2000MS_gc
#define PATTERN2_SLOPER_T2_4000MS_gc                       LP5814_PATTERN2_SLOPER_T2_4000MS_gc
#define PATTERN2_SLOPER_T2_6000MS_gc                       LP5814_PATTERN2_SLOPER_T2_6000MS_gc
#define PATTERN2_SLOPER_T2_8000MS_gc                       LP5814_PATTERN2_SLOPER_T2_8000MS_gc
#define PATTERN2_SLOPER_T3_0MS_gc                          LP5814_PATTERN2_SLOPER_T3_0MS_gc
#define PATTERN2_SLOPER_T3_50MS_gc                         LP5814_PATTERN2_SLOPER_T3_50MS_gc
#define PATTERN2_SLOPER_T3_100MS_gc                        LP5814_PATTERN2_SLOPER_T3_100MS_gc
#define PATTERN2_SLOPER_T3_150MS_gc                        LP5814_PATTERN2_SLOPER_T3_150MS_gc
#define PATTERN2_SLOPER_T3_200MS_gc                        LP5814_PATTERN2_SLOPER_T3_200MS_gc
#define PATTERN2_SLOPER_T3_250MS_gc                        LP5814_PATTERN2_SLOPER_T3_250MS_gc
#define PATTERN2_SLOPER_T3_300MS_gc                        LP5814_PATTERN2_SLOPER_T3_300MS_gc
#define PATTERN2_SLOPER_T3_350MS_gc                        LP5814_PATTERN2_SLOPER_T3_350MS_gc
#define PATTERN2_SLOPER_T3_400MS_gc                        LP5814_PATTERN2_SLOPER_T3_400MS_gc
#define PATTERN2_SLOPER_T3_450MS_gc                        LP5814_PATTERN2_SLOPER_T3_450MS_gc
#define PATTERN2_SLOPER_T3_500MS_gc                        LP5814_PATTERN2_SLOPER_T3_500MS_gc
#define PATTERN2_SLOPER_T3_1000MS_gc                       LP5814_PATTERN2_SLOPER_T3_1000MS_gc
#define PATTERN2_SLOPER_T3_2000MS_gc                       LP5814_PATTERN2_SLOPER_T3_2000MS_gc
#define PATTERN2_SLOPER_T3_4000MS_gc                       LP5814_PATTERN2_SLOPER_T3_4000MS_gc
#define PATTERN2_SLOPER_T3_6000MS_gc                       LP5814_PATTERN2_SLOPER_T3_6000MS_gc
#define PATTERN2_SLOPER_T3_8000MS_gc                       LP5814_PATTERN2_SLOPER_T3_8000MS_gc
#define PATTERN3_PAUSE_T0_0MS_gc                           LP5814_PATTERN3_PAUSE_T0_0MS_gc
#define PATTERN3_PAUSE_T0_50MS_gc                          LP5814_PATTERN3_PAUSE_T0_50MS_gc
#define PATTERN3_PAUSE_T0_100MS_gc                         LP5814_PATTERN3_PAUSE_T0_100MS_gc
#define PATTERN3_PAUSE_T0_150MS_gc                         LP5814_PATTERN3_PAUSE_T0_150MS_gc
#define PATTERN3_PAUSE_T0_200MS_gc                         LP5814_PATTERN3_PAUSE_T0_200MS_gc
#define PATTERN3_PAUSE_T0_250MS_gc                         LP5814_PATTERN3_PAUSE_T0_250MS_gc
#define PATTERN3_PAUSE_T0_300MS_gc                         LP5814_PATTERN3_PAUSE_T0_300MS_gc
#define PATTERN3_PAUSE_T0_350MS_gc                         LP5814_PATTERN3_PAUSE_T0_350MS_gc
#define PATTERN3_PAUSE_T0_400MS_gc                         LP5814_PATTERN3_PAUSE_T0_400MS_gc
#define PATTERN3_PAUSE_T0_450MS_gc                         LP5814_PATTERN3_PAUSE_T0_450MS_gc
#define PATTERN3_PAUSE_T0_500MS_gc                         LP5814_PATTERN3_PAUSE_T0_500MS_gc
#define PATTERN3_PAUSE_T0_1000MS_gc                        LP5814_PATTERN3_PAUSE_T0_1000MS_gc
#define PATTERN3_PAUSE_T0_2000MS_gc                        LP5814_PATTERN3_PAUSE_T0_2000MS_gc
#define PATTERN3_PAUSE_T0_4000MS_gc                        LP5814_PATTERN3_PAUSE_T0_4000MS_gc
#define PATTERN3_PAUSE_T0_6000MS_gc                        LP5814_PATTERN3_PAUSE_T0_6000MS_gc
#define PATTERN3_PAUSE_T0_8000MS_gc                        LP5814_PATTERN3_PAUSE_T0_8000MS_gc
#define PATTERN3_PAUSE_T1_0MS_gc                           LP5814_PATTERN3_PAUSE_T1_0MS_gc
#define PATTERN3_PAUSE_T1_50MS_gc                          LP5814_PATTERN3_PAUSE_T1_50MS_gc
#define PATTERN3_PAUSE_T1_100MS_gc                         LP5814_PATTERN3_PAUSE_T1_100MS_gc
#define PATTERN3_PAUSE_T1_150MS_gc                         LP5814_PATTERN3_PAUSE_T1_150MS_gc
#define PATTERN3_PAUSE_T1_200MS_gc                         LP5814_PATTERN3_PAUSE_T1_200MS_gc
#define PATTERN3_PAUSE_T1_250MS_gc                         LP5814_PATTERN3_PAUSE_T1_250MS_gc
#define PATTERN3_PAUSE_T1_300MS_gc                         LP5814_PATTERN3_PAUSE_T1_300MS_gc
#define PATTERN3_PAUSE_T1_350MS_gc                         LP5814_PATTERN3_PAUSE_T1_350MS_gc
#define PATTERN3_PAUSE_T1_400MS_gc                         LP5814_PATTERN3_PAUSE_T1_400MS_gc
#define PATTERN3_PAUSE_T1_450MS_gc                         LP5814_PATTERN3_PAUSE_T1_450MS_gc
#define PATTERN3_PAUSE_T1_500MS_gc                         LP5814_PATTERN3_PAUSE_T1_500MS_gc
#define PATTERN3_PAUSE_T1_1000MS_gc                        LP5814_PATTERN3_PAUSE_T1_1000MS_gc
#define PATTERN3_PAUSE_T1_2000MS_gc                        LP5814_PATTERN3_PAUSE_T1_2000MS_gc
#define PATTERN3_PAUSE_T1_4000MS_gc                        LP5814_PATTERN3_PAUSE_T1_4000MS_gc
#define PATTERN3_PAUSE_T1_6000MS_gc                        LP5814_PATTERN3_PAUSE_T1_6000MS_gc
#define PATTERN3_PAUSE_T1_8000MS_gc                        LP5814_PATTERN3_PAUSE_T1_8000MS_gc
#define PATTERN3_SLOPER_T0_0MS_gc                          LP5814_PATTERN3_SLOPER_T0_0MS_gc
#define PATTERN3_SLOPER_T0_50MS_gc                         LP5814_PATTERN3_SLOPER_T0_50MS_gc
#define PATTERN3_SLOPER_T0_100MS_gc                        LP5814_PATTERN3_SLOPER_T0_100MS_gc
#define PATTERN3_SLOPER_T0_150MS_gc                        LP5814_PATTERN3_SLOPER_T0_150MS_gc
#define PATTERN3_SLOPER_T0_200MS_gc                        LP5814_PATTERN3_SLOPER_T0_200MS_gc
#define PATTERN3_SLOPER_T0_250MS_gc                        LP5814_PATTERN3_SLOPER_T0_250MS_gc
#define PATTERN3_SLOPER_T0_300MS_gc                        LP5814_PATTERN3_SLOPER_T0_300MS_gc
#define PATTERN3_SLOPER_T0_350MS_gc                        LP5814_PATTERN3_SLOPER_T0_350MS_gc
#define PATTERN3_SLOPER_T0_400MS_gc                        LP5814_PATTERN3_SLOPER_T0_400MS_gc
#define PATTERN3_SLOPER_T0_450MS_gc                        LP5814_PATTERN3_SLOPER_T0_450MS_gc
#define PATTERN3_SLOPER_T0_500MS_gc                        LP5814_PATTERN3_SLOPER_T0_500MS_gc
#define PATTERN3_SLOPER_T0_1000MS_gc                       LP5814_PATTERN3_SLOPER_T0_1000MS_gc
#define PATTERN3_SLOPER_T0_2000MS_gc                       LP5814_PATTERN3_SLOPER_T0_2000MS_gc
#define PATTERN3_SLOPER_T0_4000MS_gc                       LP5814_PATTERN3_SLOPER_T0_4000MS_gc
#define PATTERN3_SLOPER_T0_6000MS_gc                       LP5814_PATTERN3_SLOPER_T0_6000MS_gc
#define PATTERN3_SLOPER_T0_8000MS_gc                       LP5814_PATTERN3_SLOPER_T0_8000MS_gc
#define PATTERN3_SLOPER_T1_0MS_gc                          LP5814_PATTERN3_SLOPER_T1_0MS_gc
#define PATTERN3_SLOPER_T1_50MS_gc                         LP5814_PATTERN3_SLOPER_T1_50MS_gc
#define PATTERN3_SLOPER_T1_100MS_gc                        LP5814_PATTERN3_SLOPER_T1_100MS_gc
#define PATTERN3_SLOPER_T1_150MS_gc                        LP5814_PATTERN3_SLOPER_T1_150MS_gc
#define PATTERN3_SLOPER_T1_200MS_gc                        LP5814_PATTERN3_SLOPER_T1_200MS_gc
#define PATTERN3_SLOPER_T1_250MS_gc                        LP5814_PATTERN3_SLOPER_T1_250MS_gc
#define PATTERN3_SLOPER_T1_300MS_gc                        LP5814_PATTERN3_SLOPER_T1_300MS_gc
#define PATTERN3_SLOPER_T1_350MS_gc                        LP5814_PATTERN3_SLOPER_T1_350MS_gc
#define PATTERN3_SLOPER_T1_400MS_gc                        LP5814_PATTERN3_SLOPER_T1_400MS_gc
#define PATTERN3_SLOPER_T1_450MS_gc                        LP5814_PATTERN3_SLOPER_T1_450MS_gc
#define PATTERN3_SLOPER_T1_500MS_gc                        LP5814_PATTERN3_SLOPER_T1_500MS_gc
#define PATTERN3_SLOPER_T1_1000MS_gc                       LP5814_PATTERN3_SLOPER_T1_1000MS_gc
#define PATTERN3_SLOPER_T1_2000MS_gc                       LP5814_PATTERN3_SLOPER_T1_2000MS_gc
#define PATTERN3_SLOPER_T1_4000MS_gc                       LP5814_PATTERN3_SLOPER_T1_4000MS_gc
#define PATTERN3_SLOPER_T1_6000MS_gc                       LP5814_PATTERN3_SLOPER_T1_6000MS_gc
#define PATTERN3_SLOPER_T1_8000MS_gc                       LP5814_PATTERN3_SLOPER_T1_8000MS_gc
#define PATTERN3_SLOPER_T2_0MS_gc                          LP5814_PATTERN3_SLOPER_T2_0MS_gc
#define PATTERN3_SLOPER_T2_50MS_gc                         LP5814_PATTERN3_SLOPER_T2_50MS_gc
#define PATTERN3_SLOPER_T2_100MS_gc                        LP5814_PATTERN3_SLOPER_T2_100MS_gc
#define PATTERN3_SLOPER_T2_150MS_gc                        LP5814_PATTERN3_SLOPER_T2_150MS_gc
#define PATTERN3_SLOPER_T2_200MS_gc                        LP5814_PATTERN3_SLOPER_T2_200MS_gc
#define PATTERN3_SLOPER_T2_250MS_gc                        LP5814_PATTERN3_SLOPER_T2_250MS_gc
#define PATTERN3_SLOPER_T2_300MS_gc                        LP5814_PATTERN3_SLOPER_T2_300MS_gc
#define PATTERN3_SLOPER_T2_350MS_gc                        LP5814_PATTERN3_SLOPER_T2_350MS_gc
#define PATTERN3_SLOPER_T2_400MS_gc                        LP5814_PATTERN3_SLOPER_T2_400MS_gc
#define PATTERN3_SLOPER_T2_450MS_gc                        LP5814_PATTERN3_SLOPER_T2_450MS_gc
#define PATTERN3_SLOPER_T2_500MS_gc                        LP5814_PATTERN3_SLOPER_T2_500MS_gc
#define PATTERN3_SLOPER_T2_1000MS_gc                       LP5814_PATTERN3_SLOPER_T2_1000MS_gc
#define PATTERN3_SLOPER_T2_2000MS_gc                       LP5814_PATTERN3_SLOPER_T2_2000MS_gc
#define PATTERN3_SLOPER_T2_4000MS_gc                       LP5814_PATTERN3_SLOPER_T2_4000MS_gc
#define PATTERN3_SLOPER_T2_6000MS_gc                       LP5814_PATTERN3_SLOPER_T2_6000MS_gc
#define PATTERN3_SLOPER_T2_8000MS_gc                       LP5814_PATTERN3_SLOPER_T2_8000MS_gc
#define PATTERN3_SLOPER_T3_0MS_gc                          LP5814_PATTERN3_SLOPER_T3_0MS_gc
#define PATTERN3_SLOPER_T3_50MS_gc                         LP5814_PATTERN3_SLOPER_T3_50MS_gc
#define PATTERN3_SLOPER_T3_100MS_gc                        LP5814_PATTERN3_SLOPER_T3_100MS_gc
#define PATTERN3_SLOPER_T3_150MS_gc                        LP5814_PATTERN3_SLOPER_T3_150MS_gc
#define PATTERN3_SLOPER_T3_200MS_gc                        LP5814_PATTERN3_SLOPER_T3_200MS_gc
#define PATTERN3_SLOPER_T3_250MS_gc                        LP5814_PATTERN3_SLOPER_T3_250MS_gc
#define PATTERN3_SLOPER_T3_300MS_gc                        LP5814_PATTERN3_SLOPER_T3_300MS_gc
#define PATTERN3_SLOPER_T3_350MS_gc                        LP5814_PATTERN3_SLOPER_T3_350MS_gc
#define PATTERN3_SLOPER_T3_400MS_gc                        LP5814_PATTERN3_SLOPER_T3_400MS_gc
#define PATTERN3_SLOPER_T3_450MS_gc                        LP5814_PATTERN3_SLOPER_T3_450MS_gc
#define PATTERN3_SLOPER_T3_500MS_gc                        LP5814_PATTERN3_SLOPER_T3_500MS_gc
#define PATTERN3_SLOPER_T3_1000MS_gc                       LP5814_PATTERN3_SLOPER_T3_1000MS_gc
#define PATTERN3_SLOPER_T3_2000MS_gc                       LP5814_PATTERN3_SLOPER_T3_2000MS_gc
#define PATTERN3_SLOPER_T3_4000MS_gc                       LP5814_PATTERN3_SLOPER_T3_4000MS_gc
#define PATTERN3_SLOPER_T3_6000MS_gc                       LP5814_PATTERN3_SLOPER_T3_6000MS_gc
#define PATTERN3_SLOPER_T3_8000MS_gc                       LP5814_PATTERN3_SLOPER_T3_8000MS_gc

#endif /* !LP5814_NO_SHORT_NAMES */

#endif /* LP5814_REGISTERS_H_ */
