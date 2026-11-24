/* Misst ATtiny-VDD via ADC0 (interne Referenz 1.024 V, VDD/10). */
#ifndef VDD_MONITOR_H_
#define VDD_MONITOR_H_
#include <stdint.h>

//Vor Wechsel des Haupttakts: 0 (default); danach: 1.
void VddMonitor_setFastClock(uint8_t fast);

// 0 bei ADC-Fehler oder ungültigem Ergebnis; sonst ca. VDD in mV.
uint16_t VddMonitor_readMilliVolts(void);

// Reine Umrechnung; fuer PC-Tests bewusst ohne AVR-Zugriff.
uint16_t VddMonitor_calculateMilliVolts(uint16_t raw12bit);
uint8_t VddMonitor_isSafeFor20MHz(uint16_t millivolts);
#endif
