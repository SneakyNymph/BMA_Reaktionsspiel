/*********************************************************************************\
*
* Dateiname: LP5814.c
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
* 15.11.2026  J. Meyer       V1.1      Funktionen erweitern
*
\*********************************************************************************/

#ifndef F_CPU
#define F_CPU 20000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stddef.h>

#include "include/driver/LP5814.h"
#include "include/driver/LP5814_Registers.h"
#include "include/hal/TWI.h"
#include "include/hal/GPIO.h"

///// DEFINES /////
#define LP5814_PATTERN_COUNT     4
#define LP5814_PATTERN_REG_SIZE  9


///// FUNKTIONEN /////
uint8_t LP5814_init(LP5814_Config_t *config)
{
    ///// Check Configuration /////
    if (config == NULL)
    {
        return LP5814_ERR_PARAM;
    }

    if (config->fadeTime > 15)
    {
        return LP5814_ERR_PARAM;
    }

    for (uint8_t i = 0; i < 4; i++)
    {
        if (config->channel[i].engine > 3)
        {
            return LP5814_ERR_PARAM;
        }

        if (config->channel[i].mode != LP5814_MODE_MANUAL &&
        config->channel[i].mode != LP5814_MODE_AUTO)
        {
            return LP5814_ERR_PARAM;
        }
    }
    
    
    ///// Write CHIP_EN = 1 to enable device
    uint8_t data = CHIP_EN_bm;
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, LP5814_REG_CHIP_EN, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    
    ///// Set Maximum Current /////
    if(config->maxCurrent_51mA)
    {
        // MAX_CURRENT bit auf 51mA setzten
        data = MAX_CURRENT_51MA_gc;
        
        if(TWI_writeBlock(LP5814_I2C_ADDR, DEV_CONFIG0, &data, 1) != TWI_OK)
        {
            return LP5814_ERR_TWI;
        }
    }
    else
    {
        // MAX_CURRENT bit auf 25.5mA setzten
        data = MAX_CURRENT_25_5MA_gc;
        
        if(TWI_writeBlock(LP5814_I2C_ADDR, DEV_CONFIG0, &data, 1) != TWI_OK)
        {
            return LP5814_ERR_TWI;
        }
    }
    
    // Set DC Value
    
    uint8_t currents[4] =
    {
        config->channel[0].dotCurrent,
        config->channel[1].dotCurrent,
        config->channel[2].dotCurrent,
        config->channel[3].dotCurrent
    };
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, OUT0_DC, currents, 4) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    
    ///// CONFIGURE DEVICE //////
    
    ///// enable Outputs
    data =
    ((config->channel[0].enabled != 0) << OUT0_EN_bp)
    |((config->channel[1].enabled != 0) << OUT1_EN_bp)
    |((config->channel[2].enabled != 0) << OUT2_EN_bp)
    |((config->channel[3].enabled != 0) << OUT3_EN_bp);
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, DEV_CONFIG1, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    
    ///// set output dimming control mode

    data =
    ((config->channel[0].fadeEnabled != 0) << OUT0_FADE_EN_bp)
    | ((config->channel[1].fadeEnabled != 0) << OUT1_FADE_EN_bp)
    | ((config->channel[2].fadeEnabled != 0) << OUT2_FADE_EN_bp)
    | ((config->channel[3].fadeEnabled != 0) << OUT3_FADE_EN_bp)
    | (config->fadeTime << LP5814_LED_FADE_TIME_gp);
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, DEV_CONFIG2, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    
    data =
    ((config->channel[0].exponential != 0) << OUT0_EXP_EN_bp)
    |((config->channel[1].exponential != 0) << OUT1_EXP_EN_bp)
    |((config->channel[2].exponential != 0) << OUT2_EXP_EN_bp)
    |((config->channel[3].exponential != 0) << OUT3_EXP_EN_bp)
    |((config->channel[0].mode == LP5814_MODE_AUTO) << OUT0_AUTO_EN_bp)
    |((config->channel[1].mode == LP5814_MODE_AUTO) << OUT1_AUTO_EN_bp)
    |((config->channel[2].mode == LP5814_MODE_AUTO) << OUT2_AUTO_EN_bp)
    |((config->channel[3].mode == LP5814_MODE_AUTO) << OUT3_AUTO_EN_bp);
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, DEV_CONFIG3, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    data =
    (config->channel[0].engine << OUT0_ENGINE_CH_gp)
    |(config->channel[1].engine << OUT1_ENGINE_CH_gp)
    |(config->channel[2].engine << OUT2_ENGINE_CH_gp)
    |(config->channel[3].engine << OUT3_ENGINE_CH_gp);
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, DEV_CONFIG4, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    // send UPDATE_CMD to make device configuration take effect
    data = LP5814_UPDATE_bm;
    if(TWI_writeBlock(LP5814_I2C_ADDR, LP5814_REG_UPDATE_CMD, &data, 1))
    {
        return LP5814_ERR_TWI;
    }
    
    uint8_t pwm[4] =
    {
        config->channel[0].pwm,
        config->channel[1].pwm,
        config->channel[2].pwm,
        config->channel[3].pwm
    };
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, OUT0_MANUAL_PWM, pwm, 4) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    
    return LP5814_OK;
}

uint8_t LP5814_writePWM(LP5814_Config_t *config)
{
    if (config == NULL)
    {
        return LP5814_ERR_PARAM;
    }
    
    uint8_t pwm[4] =
    {
        config->channel[0].pwm,
        config->channel[1].pwm,
        config->channel[2].pwm,
        config->channel[3].pwm
    };
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, OUT0_MANUAL_PWM, pwm, 4) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    else
    {
        return LP5814_OK;
    }
}

uint8_t LP5814_isBusy(uint8_t *busy)
{
    
    // Check pointer
    if (busy == NULL)
    {
        return LP5814_ERR_PARAM;
    }
    
    
    uint8_t busyFlag = 0;
    
    if(TWI_readBlock(LP5814_I2C_ADDR, LP5814_REG_FLAG, &busyFlag, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    if (busyFlag & ENGINE_BUSY_bm)
    {
        *busy = 1;
        return LP5814_OK;
    }
    else
    {
        *busy = 0;
        return LP5814_OK;
    }
}

uint8_t LP5814_setPattern(uint8_t pattern, const LP5814_PatternConfig_t *config)
{
    
    // Parameter überprüfen
    
    if (config == NULL)
    {
        return LP5814_ERR_PARAM;
    }
    
    if (pattern >= LP5814_PATTERN_COUNT)
    {
        return LP5814_ERR_PARAM;
    }
    
    if(config->pauseEnd > LP5814_TIME_8000_ms || config->pauseStart > LP5814_TIME_8000_ms)
    {
        return LP5814_ERR_PARAM;
    }
    
    for (uint8_t i = 0; i < LP5814_PATTERN_COUNT; i++)
    {
        if(config->slopeTime[i] > LP5814_TIME_8000_ms)
        {
            return LP5814_ERR_PARAM;
        }
    }
    
    if (config->repeat > 15)
    {
        return LP5814_ERR_PARAM;
    }
    
    // Chekcken ob eine Engine läuft
    uint8_t busyFlag = 0;

    uint8_t result = LP5814_isBusy(&busyFlag);

    if (result != LP5814_OK)
    {
        return result;
    }

    if (busyFlag)
    {
        return LP5814_ERR_BUSY;
    }
    
    
    uint8_t data[LP5814_PATTERN_REG_SIZE] = {0};
    
    // Pause Time
    data[0] = (config->pauseStart << PATTERN0_PAUSE_T0_gp) | (config->pauseEnd << PATTERN0_PAUSE_T1_gp);
    
    // Repeat Time
    data[1] = config->repeat;
    
    // PWM
    for (uint8_t i = 0; i < 5; i++)
    {
        data[i + 2] = config->pwm[i];
    }
    
    // Sloper Time 1
    data[7] = (config->slopeTime[0] << PATTERN0_SLOPER_T0_gp) | (config->slopeTime[1] << PATTERN0_SLOPER_T1_gp);
    
    
    // Sloper Time 2
    data[8] = (config->slopeTime[2] << PATTERN0_SLOPER_T2_gp) | (config->slopeTime[3] << PATTERN0_SLOPER_T3_gp);
    
    uint8_t startReg = PATTERN0_PAUSE_TIME + (pattern * LP5814_PATTERN_REG_SIZE);
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, startReg, data, LP5814_PATTERN_REG_SIZE) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    return LP5814_OK;
    
}

uint8_t LP5814_setEngine(uint8_t engine, const LP5814_EngineConfig_t *config)
{
    // Parameter überprüfen
    
    if (config == NULL)
    {
        return LP5814_ERR_PARAM;
    }
    
    if (engine > 3)
    {
        return LP5814_ERR_PARAM;
    }
    
    if(config->repeat > LP5814_REP_INFINITE)
    {
        return LP5814_ERR_PARAM;
    }
    
    for (uint8_t i = 0; i < 4; i++)
    {
        if(config->order[i].pattern > 3)
        {
            return LP5814_ERR_PARAM;
        }
    }
    
    // Chekcken ob eine Engine läuft
    uint8_t busyFlag = 0;

    uint8_t result = LP5814_isBusy(&busyFlag);

    if (result != LP5814_OK)
    {
        return result;
    }

    if (busyFlag)
    {
        return LP5814_ERR_BUSY;
    }
    
    uint8_t addr = ENGINE_CONFIG0 + engine;
    
    uint8_t data =
    ((config->order[0].pattern) << ENGINE0_ORDER0_gp)
    | ((config->order[1].pattern) << ENGINE0_ORDER1_gp)
    | ((config->order[2].pattern) << ENGINE0_ORDER2_gp)
    | ((config->order[3].pattern) << ENGINE0_ORDER3_gp);
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, addr, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    

    uint8_t input[3] = {0};

    // Aktuelle kondifuration auslesen
    if (TWI_readBlock(LP5814_I2C_ADDR, ENGINE_CONFIG4, input, 3) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }


    /// Configure Order Enable ///

    // Die Enable-Bits zusammenstellen
    uint8_t enableBits = 0;

    for (uint8_t i = 0; i < 4; i++)
    {
        enableBits |= ((config->order[i].enabled != 0) << i);
    }

    // register index und bit poition berechnen
    uint8_t regIndex = engine / 2;
    uint8_t shift = (engine % 2) * 4;
    uint8_t mask = (uint8_t)(0x0F << shift);

    // Alte Bits löschen und neue einsetzten
    input[regIndex] = (input[regIndex] & ~mask) | (enableBits << shift);


    /// Configure Engine Repeat ///

    // bit position berechnen
    shift = engine * 2;
    mask = (uint8_t)(0x03 << shift);

    // alte bits löschen und neue einsetzten
    input[2] = (input[2] & ~mask) | (config->repeat << shift);


    /// Write updated configuration ///

    if (TWI_writeBlock(LP5814_I2C_ADDR, ENGINE_CONFIG4, input, 3) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    return LP5814_OK;
}

uint8_t LP5814_startAnimation(void)
{
    uint8_t data = LP5814_CMD_START;
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, START_CMD, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    return LP5814_OK;
}

uint8_t LP5814_stopAnimation(void)
{
    uint8_t data = LP5814_CMD_STOP;
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, STOP_CMD, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    return LP5814_OK;
}

uint8_t LP5814_pauseAnimation(void)
{
    uint8_t data = LP5814_PAUSE_CONTINUE_bm;
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, PAUSE_CONTINUE, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    return LP5814_OK;
}

uint8_t LP5814_continueAnimation(void)
{
    uint8_t data = 0x00;
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, PAUSE_CONTINUE, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    return LP5814_OK;
}

uint8_t LP5814_getStatus(LP5814_Status_t *status)
{
    // NULL-Pointer überprüfen
    if (status == NULL)
    {
        return LP5814_ERR_PARAM;
    }
    
    
    // Flag Register auslesen
    uint8_t data = 0;
    
    if(TWI_readBlock(LP5814_I2C_ADDR, LP5814_REG_FLAG, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    // Status Flag dekodieren
    status->por = (data & POR_bm) != 0;
    status->tsd = (data & TSD_bm) != 0;
    status->engineBusy = (data & ENGINE_BUSY_bm) != 0;
    
    // Output busy flag dekodieren
    
    for (uint8_t i = 0; i < 4; i++)
    {
        status->outputBusy[i] = (data >> (OUT0_ENGINE_BUSY_bp + i)) & 0x01;
    }
    
    return LP5814_OK;
    
}

uint8_t LP5814_clearFlags(uint8_t flags)
{
    // Paramteter kontrollieren
    if (flags == 0 || (flags & 0xFC))
    {
        return LP5814_ERR_PARAM;
    }
    
    if(TWI_writeBlock(LP5814_I2C_ADDR, PAUSE_CONTINUE, &flags, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }
    
    return LP5814_OK;
    
}

uint8_t LP5814_wakeUp(void)
{
    // TWI-MOdul deaktivieren
    if (TWI_disable() != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }

    // SCL und SDA freigeben
    GPIO_pinWrite(&PORTB, 0, GPIO_LOW);
    GPIO_pinWrite(&PORTB, 1, GPIO_LOW);
    
    GPIO_setPinDirection(&PORTB, 0, GPIO_INPUT);
    GPIO_setPinDirection(&PORTB, 1, GPIO_INPUT);

    _delay_us(15);

    // Prüfen ob SDA und SCL HIGH sind
    if ((PORTB.IN & (PIN0_bm | PIN1_bm)) != (PIN0_bm | PIN1_bm))
    {
        (void)TWI_enable();
        return LP5814_ERR_TWI;
    }

    // 8x fallende Flanke auf SDA pin
    for (uint8_t i = 0; i < 8; i++)
    {
        // SDA auf LOW ziehen
        GPIO_setPinDirection(&PORTB, 1, GPIO_OUTPUT);
        _delay_us(15);

        // SDA wieder freigeben
        GPIO_setPinDirection(&PORTB, 1, GPIO_INPUT);
        _delay_us(15);
    }

    // TWI-Modul wider aktivieren
    if (TWI_enable() != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }

    // Initialisierung des LP5814 abwarten
    _delay_ms(1);

    // Überprüfen ob der LP5814 wider erreichbar ist
    uint8_t status = 0;

    if (TWI_readBlock(LP5814_I2C_ADDR, LP5814_REG_FLAG, &status, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }

    return LP5814_OK;
}


uint8_t LP5814_shutdown(void)
{
    // Abschalt Komando senden
    uint8_t data = LP5814_CMD_SHUTDOWN;

    if (TWI_writeBlock(LP5814_I2C_ADDR, LP5814_REG_SHUTDOWN_CMD, &data, 1) != TWI_OK)
    {
        return LP5814_ERR_TWI;
    }

    return LP5814_OK;
}
