/*
 * DriverLib.c
 *
 *  Created on: Aug 10, 2026
 *      Author: roman
 */

#include "DriverLib.h"

tHead_t tHead;



void tbInit() {
	tHead.tAxis[0].port_dir 	= GPIOC;
	tHead.tAxis[0].pin_dir 		= GPIO_PIN_8;
	tHead.tAxis[0].port_en 		= GPIOA;
	tHead.tAxis[0].pin_en 		= GPIO_PIN_8;
	tHead.tAxis[0].port_pulse 	= GPIOC;
	tHead.tAxis[0].pin_pulse 	= GPIO_PIN_9;

	tHead.tAxis[1].port_dir 	= GPIOB;
	tHead.tAxis[1].pin_dir 		= GPIO_PIN_15;
	tHead.tAxis[1].port_en 		= GPIOC;
	tHead.tAxis[1].pin_en 		= GPIO_PIN_7;
	tHead.tAxis[1].port_pulse 	= GPIOC;
	tHead.tAxis[1].pin_pulse 	= GPIO_PIN_6;

	tHead.tAxis[2].port_dir 	= GPIOB;
	tHead.tAxis[2].pin_dir 		= GPIO_PIN_12;
	tHead.tAxis[2].port_en 		= GPIOB;
	tHead.tAxis[2].pin_en 		= GPIO_PIN_14;
	tHead.tAxis[2].port_pulse 	= GPIOB;
	tHead.tAxis[2].pin_pulse 	= GPIO_PIN_13;

}


void dl_CheckPWM() {
	for (uint8_t i = 0; i < 3; i++) {
		if (tHead.state == tWORKING) {
			if (tHead.tAxis[i].counter >= (tHead.tAxis[i].tgl-1)) {
				HAL_GPIO_TogglePin(tHead.tAxis[i].port_pulse, tHead.tAxis[i].pin_pulse);
				tHead.tAxis[i].counter = 0;

				if (tHead.tAxis[i].direction == Forward) {
					tHead.tAxis[i].current_pos++;
					if ((tHead.tAxis[i].current_pos % 2) == 0) {
						tHead.tAxis[i].current_pos_coord += ONE_STEP_WIDTH;
					}
				} else if (tHead.tAxis[i].direction == BackForward) {
					tHead.tAxis[i].current_pos--;
					if ((tHead.tAxis[i].current_pos % 2) == 0) {
						tHead.tAxis[i].current_pos_coord -= ONE_STEP_WIDTH;
					}
				} else if (tHead.tAxis[i].direction == Hold) {
					__NOP();
				}
				else {}
			}
			else tHead.tAxis[i].counter++;
		}
	}
}



void tbDriver(state_en_t st) {

	for (uint8_t i = 0; i < 3; i++) HAL_GPIO_WritePin(tHead.tAxis[i].port_en, tHead.tAxis[i].pin_en, st);

	return;
}




void tbMove(float tx, float ty, float tz) {
	if (tHead.state == tON) {
		for (uint8_t i = 0; i < 3; i++) {
			if (tx < tHead.tAxis[i].current_pos_coord) {
				tHead.tAxis[i].direction = Forward;
			} else if (tx > tHead.tAxis[i].current_pos_coord) {
				tHead.tAxis[i].direction = BackForward;
			} else if 	(((tx + EPS_PRECISION) <= tHead.tAxis[i].current_pos_coord) ||
						((tx - EPS_PRECISION) >= tHead.tAxis[i].current_pos_coord)) {
				tHead.tAxis[i].direction = Hold;
			}
		}

		tbDriver(ON);
		while(1) {



		}
	}
	return;
}













