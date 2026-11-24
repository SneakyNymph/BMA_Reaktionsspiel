#include <stdint.h>
#include "include/hal/VddMonitor.h"

// ADC: VDD/10 gegen interne 1.024-V-Referenz, 12-Bit Single Conversion.
uint16_t VddMonitor_calculateMilliVolts(uint16_t raw12bit)
{
    if (raw12bit == 0U || raw12bit > 4095U) return 0U;
    return (uint16_t)(((uint32_t)raw12bit * 10240UL + 2047UL) / 4095UL);
}

// Sicherheitsmarge gegen ADC-Referenztoleranz und VDD-Schwankungen.
uint8_t VddMonitor_isSafeFor20MHz(uint16_t millivolts)
{
    return (millivolts >= 4800U && millivolts <= 5300U) ? 1U : 0U;
}
