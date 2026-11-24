/*
 * ATtiny1626 ADC0-VDD-Monitor
 * VDD/10 gegen interne 1.024-V-Referenz, 12 Bit.
 * ADC nimmt allein keine FET-Freigabe vor.
 */
#include <avr/io.h>
#include <stdint.h>
#include "include/hal/VddMonitor.h"

static uint8_t useFastClock = 0U;

void VddMonitor_setFastClock(uint8_t fast)
{
    useFastClock = fast ? 1U : 0U;
}

uint16_t VddMonitor_readMilliVolts(void)
{
    uint32_t sum = 0;
    uint16_t timeout;
    uint16_t raw;

    // Der ADC braucht mit interner Referenz 300 kHz bis 3 MHz CLK_ADC.
    // CPU nach Reset: OSC20M /6 (~3,33 bzw. 2,67 MHz): /4.
    // CPU nach system_setupMainCLK(): 20 bzw. 16 MHz: /32.
    ADC0.CTRLA = 0;
    ADC0.INTCTRL = 0U; //Dieses Modul nutzt Polling, keine ADC-Interrupts.
    ADC0.CTRLF = 0U;  //Kein Free-Run, keine Akkumulation, keine Left-Adjust.
    ADC0.CTRLB = useFastClock ? ADC_PRESC_DIV32_gc : ADC_PRESC_DIV4_gc;
    // TIMEBASE mindestens 1us: Reset-Takt /6 => 4, Fast => 20 Zyklen.
    ADC0.CTRLC = ADC_REFSEL_1024MV_gc |
        ((useFastClock ? 20U : 4U) << ADC_TIMEBASE_gp);
    ADC0.CTRLE = 31U; //Samplingdauer ausreichend lang fuer VDD/10
    ADC0.MUXPOS = ADC_MUXPOS_VDDDIV10_gc;
    ADC0.COMMAND = ADC_MODE_SINGLE_12BIT_gc;
    ADC0.CTRLA = ADC_ENABLE_bm;

    // Kurzer Wartezyklus zum Einschwingen der internen Referenz.
    for (volatile uint16_t i = 0; i < 20000U; i++) { }

    // Erste Messung verwerfen (Referenz- und MUX-Einschwingvorgang).
    for (uint8_t n = 0; n < 5U; n++)
    {
        ADC0.INTFLAGS = ADC_RESRDY_bm;
        ADC0.COMMAND = ADC_MODE_SINGLE_12BIT_gc | ADC_START_IMMEDIATE_gc;
        timeout = 60000U;
        while ((ADC0.INTFLAGS & ADC_RESRDY_bm) == 0U)
        {
            if (--timeout == 0U)
            {
                ADC0.CTRLA = 0;
                return 0U;
            }
        }
        raw = (uint16_t)ADC0.RESULT;
        if (raw == 0U || raw > 4095U)
        {
            ADC0.CTRLA = 0;
            return 0U;
        }
        if (n != 0U) sum += raw;
    }
    ADC0.CTRLA = 0U;
    raw = (uint16_t)((sum + 2U) / 4U);
    return VddMonitor_calculateMilliVolts(raw);
}
