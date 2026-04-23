/*
 * AS5600.h
 *
 *  Created on: Mar 4, 2026
 *      Author: makar
 */

#ifndef INC_AS5600_H_
#define INC_AS5600_H_



#include "stm32f1xx_hal.h"
#include "stdbool.h"

#define	AS5600_ADDR						0x36

#define	AS5600_ZMCO_REG					0x00
#define	AS5600_ZPOS_H_REG				0x01
#define	AS5600_ZPOS_L_REG				0x02
#define	AS5600_MPOS_H_REG				0x03
#define	AS5600_MPOS_L_REG				0x04
#define	AS5600_MANG_H_REG				0x05
#define	AS5600_MANG_L_REG				0x06
#define	AS5600_CONF_H_REG				0x07
#define	AS5600_CONF_L_REG				0x08
#define	AS5600_RAW_ANGLE_H_REG			0x0C
#define	AS5600_RAW_ANGLE_L_REG			0x0D
#define	AS5600_ANGLE_H_REG				0x0E
#define	AS5600_ANGLE_L_REG				0x0F
#define	AS5600_STATUS_REG				0x0B
#define	AS5600_AGC_REG					0x1A
#define	AS5600_MAGNITUDE_H_REG			0x1B
#define	AS5600_MAGNITUDE_L_REG			0x1C
#define	AS5600_BURN_REG					0xFF

enum PowerMode {
	NOM 					= 0x00,
	LPM1 					= 0x01,
	LPM2 					= 0x02,
	LPM3 					= 0x03,
};
enum Hysteresis {
	HYST_OFF 				= 0x00,
	HYST_1LSB 				= 0x01,
	HYST_2LSBs 				= 0x02,
	HYST_3LSBs 				= 0x03,
};
enum Output_Stage {
	OUTS_Analog_Full 		= 0x00,
	OUTS_digital_Reduced 	= 0x01,
	OUTS_DigitPWM 			= 0x02,
};
enum PWM_Freq {
	PWMF_115Hz 				= 0x00,
	PWMF_230Hz 				= 0x01,
	PWMF_460Hz	 			= 0x02,
	PWMF_920Hz	 			= 0x03,
};
enum SlowFilter {
	SF_16x 					= 0x00,
	SF_8x 					= 0x01,
	SF_4x	 				= 0x02,
	SF_2x	 				= 0x03,
};
enum FastFilterThreshold {
	FTH_SlowFilterOnly 		= 0x00,
	FTH_6LSBs 				= 0x01,
	FTH_7LSBs	 			= 0x02,
	FTH_9LSBs	 			= 0x03,
	FTH_18LSBs	 			= 0x04,
	FTH_21LSBs	 			= 0x05,
	FTH_24LSBs	 			= 0x06,
	FTH_10LSBs	 			= 0x07,
};
enum Watchdog {
	WD_OFF 					= 0,
	WD_ON 					= 1,
};


#define	AS5600_RAW_TO_DEGREES			(float)(360.0 / 4096.0)




















#endif /* INC_AS5600_H_ */
