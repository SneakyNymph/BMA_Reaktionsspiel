/*********************************************************************************\
*
* Dateiname: BQ25883_Registers.h
*
* Projekt  : Tisch Reaktionsspiel BMA
* Hardware : ATtiny3226 auf Hauptplatine V1
*
* Copyright: Jan Meyer
*
* Beschreibung:
* =============
* Bietet DEFINES für BQ25883.h
*
* Verlauf:
* ========
* Datum:      Autor:         Version   Grund der Änderung:
* 22.11.2026  J. Meyer       V1.0      Neuerstellung
*
\*********************************************************************************/



#ifndef BQ25883_REGISTERS_H_
#define BQ25883_REGISTERS_H_

#define BQ25883_I2C_ADDR       0x6B

#define BQ25883_REG_PART_INFO  0x25

#define BQ25883_PN_MASK       0x78
#define BQ25883_PN_VALUE      0x18

#define BQ25883_REG_CHG_CTRL2  0x06
#define BQ25883_EN_CHG_bm      (1 << 3)

#define BQ25883_REG_CHG_VOLTAGE   0x00

#define BQ25883_VREG_MIN_MV      6800
#define BQ25883_VREG_MAX_MV      9200
#define BQ25883_VREG_STEP_MV     10


#define BQ25883_REG_CHG_STATUS1   0x0B
#define BQ25883_CHRG_STAT_bm      0x07


///// Statusregister /////
#define BQ25883_REG_STATUS_START  0x0B
#define BQ25883_STATUS_REG_COUNT  3

///// REG0B - Charger Status 1 /////
#define BQ25883_IINDPM_STAT_bm    (1u << 6)
#define BQ25883_VINDPM_STAT_bm    (1u << 5)
#define BQ25883_TREG_STAT_bm      (1u << 4)
#define BQ25883_WD_STAT_bm        (1u << 3)
#define BQ25883_CHRG_STAT_bm      0x07

///// REG0C - Charger Status 2 /////
#define BQ25883_PG_STAT_bm        (1u << 7)
#define BQ25883_VBUS_STAT_bm      0x70
#define BQ25883_VBUS_STAT_gp      4
#define BQ25883_ICO_STAT_bm       0x06
#define BQ25883_ICO_STAT_gp       1
#define BQ25883_VSYS_STAT_bm      (1u << 0)

///// REG0D - NTC Status /////
#define BQ25883_TS_STAT_bm        0x07


///// REG0E - Fault Status /////
#define BQ25883_REG_FAULT_STATUS   0x0E

#define BQ25883_VBUS_OVP_STAT_bm   (1u << 7)
#define BQ25883_TSHUT_STAT_bm      (1u << 6)
#define BQ25883_BATOVP_STAT_bm     (1u << 5)
#define BQ25883_TMR_STAT_bm        (1u << 4)



#define BQ25883_REG_FLAG_START   0x0F
#define BQ25883_FLAG_REG_COUNT   3


///// REG15 - ADC Control /////
#define BQ25883_REG_ADC_CTRL          0x15
#define BQ25883_ADC_EN_bm             (1u << 7)

///// REG16 - ADC Function Disable /////
#define BQ25883_REG_ADC_CHANNELS      0x16
#define BQ25883_ADC_CHANNEL_MASK      0xFD

///// REG17 - REG24 - ADC Messwerte /////
#define BQ25883_REG_ADC_RESULTS       0x17
#define BQ25883_ADC_RESULTS_SIZE      14


///// Laufzeitregister /////
#define BQ25883_REG_CHG_CURRENT       0x01
#define BQ25883_REG_INPUT_VOLTAGE     0x02
#define BQ25883_REG_INPUT_CURRENT     0x03
#define BQ25883_REG_CHG_CTRL3         0x07
#define BQ25883_REG_OTG_CTRL          0x09
#define BQ25883_REG_ICO_LIMIT         0x0A
#define BQ25883_REG_CHG_STATUS2       0x0C

///// REG01 /////
#define BQ25883_EN_HIZ_bm             (1u << 7)
#define BQ25883_ICHG_bm               0x3F

///// REG02 /////
#define BQ25883_EN_BAT_DISCHG_bm      (1u << 6)
#define BQ25883_VINDPM_bm             0x1F

///// REG03 /////
#define BQ25883_FORCE_ICO_bm          (1u << 7)
#define BQ25883_FORCE_INDET_bm        (1u << 6)
#define BQ25883_EN_ICO_bm             (1u << 5)
#define BQ25883_IINDPM_bm             0x1F

///// REG06 /////
#define BQ25883_EN_OTG_bm             (1u << 7)

///// REG07 /////
#define BQ25883_WD_RST_bm             (1u << 6)

///// REG0A /////
#define BQ25883_ICO_ILIM_bm           0x1F

///// REG15 /////
#define BQ25883_ADC_RATE_bm           (1u << 6)

///// REG25 /////
#define BQ25883_REG_RST_bm            (1u << 7)



#endif /* BQ25883_REGISTERS_H_ */