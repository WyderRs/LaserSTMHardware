/*
 * DriverLib.c
 *
 *  Created on: Aug 10, 2026
 *      Author: roman
 */

#include "tableTool.h"

#include <stdbool.h>
#include <stdio.h>
#include "../lib/LCD2004.h"
#include "../lib/FuncG.h"


Tool_Typedef tTool;

extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart1;


extern TIM_HandleTypeDef htim3;




/*******************/
/* Init device */
void tInit(void) {
	tTool.GMode = _G0_mode;

	/* Axis X */
	tTool.head.tAxis[0].port_dir 				= GPIOA;
	tTool.head.tAxis[0].pin_dir 				= GPIO_PIN_11;
	tTool.head.tAxis[0].port_en 				= GPIOA;
	tTool.head.tAxis[0].pin_en 					= GPIO_PIN_12;
	tTool.head.tAxis[0].port_SW					= GPIOC;
	tTool.head.tAxis[0].pin_SW					= GPIO_PIN_12;
	tTool.head.tAxis[0].state_SW				= false;
	tTool.head.tAxis[0].timer					= &htim3;
	tTool.head.tAxis[0].timer_channel 			= TIM_CHANNEL_4;
	tTool.head.tAxis[0].timer->Instance->CCR4 	= 50;

	/* Axis Y */
	tTool.head.tAxis[1].port_dir 				= GPIOB;
	tTool.head.tAxis[1].pin_dir 				= GPIO_PIN_14;
	tTool.head.tAxis[1].port_en 				= GPIOB;
	tTool.head.tAxis[1].pin_en 					= GPIO_PIN_15;
	tTool.head.tAxis[1].port_SW					= GPIOD;
	tTool.head.tAxis[1].pin_SW					= GPIO_PIN_2;
	tTool.head.tAxis[1].state_SW				= false;
	tTool.head.tAxis[1].timer					= &htim3;
	tTool.head.tAxis[1].timer_channel 			= TIM_CHANNEL_3;
	tTool.head.tAxis[1].timer->Instance->CCR3 	= 50;
	/* Axis Z */
	tTool.head.tAxis[2].port_dir 				= GPIOB;
	tTool.head.tAxis[2].pin_dir 				= GPIO_PIN_12;
	tTool.head.tAxis[2].port_en 				= GPIOB;
	tTool.head.tAxis[2].pin_en 					= GPIO_PIN_13;
	tTool.head.tAxis[2].port_SW					= GPIOB;
	tTool.head.tAxis[2].pin_SW					= GPIO_PIN_3;
	tTool.head.tAxis[2].state_SW				= false;
	tTool.head.tAxis[2].timer					= &htim3;
	tTool.head.tAxis[2].timer_channel 			= TIM_CHANNEL_2;
	tTool.head.tAxis[2].timer->Instance->CCR2 	= 50;
	/* Encoder */
	tTool.Encoder.port1							= GPIOB;
	tTool.Encoder.pin1							= GPIO_PIN_5;
	tTool.Encoder.port2							= GPIOB;
	tTool.Encoder.pin2							= GPIO_PIN_4;
	tTool.Encoder.Button_port					= GPIOB;
	tTool.Encoder.Button_pin					= GPIO_PIN_8;
	tTool.Encoder.current_rotate_side 			= Forward;
	tTool.Encoder.count_last_rotate	 			= 0;
	tTool.Encoder.Button_state 					= false;

	/* Laser */
	tTool.laser.port							= GPIOB;
	tTool.laser.pin								= GPIO_PIN_9;
	tTool.laser.timer							= &htim3;
	tTool.laser.timer_channel 					= TIM_CHANNEL_1;
	tTool.laser.timer->Instance->CCR1 			= 50;
	/* Culler */
	tTool.culler.port							= GPIOC;
	tTool.culler.pin							= GPIO_PIN_11;


	tToolAxisEN(&tTool.head.tAxis[0], OFF);
	tToolAxisEN(&tTool.head.tAxis[1], OFF);
	tToolAxisEN(&tTool.head.tAxis[2], OFF);



	LED_AUTO_OP_ON;
	LED_FREE_OP_ON;
	LED_ERR_OP_ON;
	HAL_Delay(500);
	LED_AUTO_OP_OFF;
	LED_FREE_OP_OFF;
	LED_ERR_OP_OFF;


	tMode(_G1_mode);
	tToolFeedrateType(ftt_mm_min);
	tToolFeedrate(100);
	/***********************/
	tHome();
	tTool.origin_pos[0] 	= tTool.curr_pos[0];
	tTool.origin_pos[1] 	= tTool.curr_pos[1];
	tTool.origin_pos[2] 	= tTool.curr_pos[2];

	tTool.Encoder.md_ct[0] 	= 2000;	// ENC_Auto
	tTool.Encoder.md_ct[1] 	= 3000;	// ENC_HAND
	tTool.Encoder.md_ct[2] 	= 4000;	// ENC_NONE

	tTool.Encoder.md_ct[3] 	= 2000;	// ENC_X
	tTool.Encoder.md_ct[4] 	= 3000;	// ENC_Y
	tTool.Encoder.md_ct[5] 	= 4000;	// ENC_Z

	tTool.Encoder.mode 		= ENC_Auto;
	/***********************/
	tTool.VCP.State = tVCP_Check();

	if (tTool.VCP.State) {
		HAL_UART_Receive_DMA(&huart1, (uint8_t*)&tTool.VCP.Data_one_byte, 1);
	}

	while(1) {
		if (tTool.VCP.command_IsReceived) {
			__NOP();
			StartGCodeStorage(tTool.VCP.data, tTool.VCP.line_count);
			tTool.VCP.command_IsReceived = false;
		}

		/*********************/
		if (tTool.Encoder.Button_state) {
			if (tTool.Encoder.md_sct != uwTick) tTool.Encoder.ButtonHasPressed = true;
		}
		else {
			if (tTool.Encoder.ButtonHasPressed) {
				if (((tTool.Encoder.md_sct + tTool.Encoder.md_ct[0]) <= uwTick) &&
						((tTool.Encoder.md_sct + tTool.Encoder.md_ct[1]) >= uwTick)) {
					tTool.Encoder.mode = ENC_Auto;
				}

				else if (((tTool.Encoder.md_sct + tTool.Encoder.md_ct[1]) <= uwTick) &&
						((tTool.Encoder.md_sct + tTool.Encoder.md_ct[2]) >= uwTick)) {
					tTool.Encoder.mode = ENC_HAND;
				}

				else if (((tTool.Encoder.md_sct + tTool.Encoder.md_ct[2]) <= uwTick) /*&&		// пока только три режима
						((tTool.Encoder.md_sct + tTool.Encoder.md_ct[1]) >= uwTick)*/) {
					tTool.Encoder.mode = ENC_NONE;
				}
				tTool.Encoder.ButtonHasPressed = false;
			}
			tTool.Encoder.md_sct = uwTick;
		}

		if (tTool.Encoder.mode == ENC_HAND) {
			while(1) {
				if (tTool.Encoder.Button_state) {
					if (tTool.Encoder.md_sct != uwTick) tTool.Encoder.ButtonHasPressed = true;
				}
				else {
					if (tTool.Encoder.ButtonHasPressed) {
						if (((tTool.Encoder.md_sct + tTool.Encoder.md_ct[3]) <= uwTick) &&
								((tTool.Encoder.md_sct + tTool.Encoder.md_ct[4]) >= uwTick)) {
							tTool.Encoder.mode = ENC_X;
						}

						else if (((tTool.Encoder.md_sct + tTool.Encoder.md_ct[4]) <= uwTick) &&
								((tTool.Encoder.md_sct + tTool.Encoder.md_ct[5]) >= uwTick)) {
							tTool.Encoder.mode = ENC_Y;
						}

						else if (((tTool.Encoder.md_sct + tTool.Encoder.md_ct[6]) <= uwTick) /*&&
								((tTool.Encoder.md_sct + tTool.Encoder.md_ct[1]) >= uwTick)*/) {
							tTool.Encoder.mode = ENC_Z;
						}
						else if (((tTool.Encoder.md_sct + tTool.Encoder.md_ct[6]) <= uwTick) &&
								((tTool.Encoder.md_sct + (tTool.Encoder.md_ct[6] + 1000)) >= uwTick)) {
							tTool.Encoder.mode = ENC_NONE;
							tTool.Encoder.ButtonHasPressed = false;
							break;
						}
						tTool.Encoder.ButtonHasPressed = false;
					}
					tTool.Encoder.md_sct = uwTick;
				}

				if (tTool.Encoder.mode == ENC_X) {
					if (tTool.Encoder.count_last_rotate >= 1) {
						float x = tTool.curr_pos[0];
						if (tTool.Encoder.current_rotate_side == Forward) x += 5;
						else if (tTool.Encoder.current_rotate_side == BackForward) x -= 5;
						tToolMove(x, tTool.curr_pos[1], tTool.curr_pos[2]);
						tTool.Encoder.count_last_rotate = 0;
					}
				}
				else if (tTool.Encoder.mode == ENC_Y) {
					if (tTool.Encoder.count_last_rotate >= 1) {
						float y = tTool.curr_pos[1];
						if (tTool.Encoder.current_rotate_side == Forward) y += 5;
						else if (tTool.Encoder.current_rotate_side == BackForward) y -= 5;
						tToolMove(tTool.curr_pos[0], y, tTool.curr_pos[2]);
						tTool.Encoder.count_last_rotate = 0;
					}
				}
				else if (tTool.Encoder.mode == ENC_Z) {
					if (tTool.Encoder.count_last_rotate >= 1) {
						float z = tTool.curr_pos[2];
						if (tTool.Encoder.current_rotate_side == Forward) z += 5;
						else if (tTool.Encoder.current_rotate_side == BackForward) z -= 5;
						tToolMove(tTool.curr_pos[0], tTool.curr_pos[1], z);
						tTool.Encoder.count_last_rotate = 0;
					}
				}
			}
		}





		/*********************/

	}

	while(1) {
		HAL_Delay(500);
		LED_FREE_OP_TGL;
	}

//	tMove(4.3538, -0.5502, 10);
//	tMove(4.3705, -0.5728, 10);
//	tMove(4.3774, -0.5814, 10);
//	tMove(4.4325, -0.6422, 10);
//	tMove(4.4405, -0.6500, 10);
//	tMove(4.4959, -0.7002, 10);
//	tMove(4.5043, -0.7073, 10);
//	tMove(4.5673, -0.7541, 10);
//	tMove(4.5795, -0.7622, 10);
//	tMove(4.6501, -0.8043, 10);
//	tMove(4.7276, -0.8411, 10);
//	tMove(4.7379, -0.8452, 10);
//	tMove(4.8153, -0.8727, 10);
//	tMove(4.8949, -0.8929, 10);
//	tMove(4.9093, -0.8957, 10);
//	tMove(4.9906, -0.9076, 10);
//	tMove(5.0726, -0.9118, 10);
//	tMove(5.0874, -0.9118, 10);
//	tMove(5.1620, -0.9081, 10);
//	tMove(5.1767, -0.9067, 10);
//	tMove(5.2579, -0.8945, 10);
//	tMove(5.3447, -0.8727, 10);
//	tMove(5.4290, -0.8426, 10);
//	tMove(5.5099, -0.8043, 10);
//	tMove(5.5867, -0.7583, 10);
//	tMove(5.6586, -0.7050, 10);
//	tMove(5.7249, -0.6449, 10);
//	tMove(5.7850, -0.5786, 10);
//	tMove(5.8383, -0.5067, 10);
//	tMove(5.8843, -0.4299, 10);
//	tMove(5.9226, -0.3490, 10);
//	tMove(5.9527, -0.2647, 10);
//	tMove(5.9745, -0.1779, 10);
//	tMove(5.9876, -0.0894, 10);
//	tMove(5.9920, 0.0000, 10);
//	tMove(5.9881, 0.0820, 10);
//	tMove(5.9867, 0.0967, 10);
//	tMove(5.9757, 0.1707, 10);
//	tMove(5.9729, 0.1851, 10);
//	tMove(5.9527, 0.2647, 10);
//	tMove(5.9252, 0.3421, 10);
//	tMove(5.9196, 0.3557, 10);
//	tMove(5.8843, 0.4299, 10);
//	tMove(5.8383, 0.5067, 10);
//	tMove(5.7850, 0.5786, 10);
//	tMove(5.7300, 0.6395, 10);
//	tMove(5.7195, 0.6500, 10);
//	tMove(5.6586, 0.7050, 10);
//	tMove(5.5867, 0.7583, 10);
//	tMove(5.5099, 0.8043, 10);
//	tMove(5.4290, 0.8426, 10);
//	tMove(5.3447, 0.8727, 10);
//	tMove(5.2579, 0.8945, 10);
//	tMove(5.1694, 0.9076, 10);
//	tMove(5.0874, 0.9118, 10);
//	tMove(5.0726, 0.9118, 10);
//	tMove(4.9906, 0.9076, 10);
//	tMove(4.9093, 0.8957, 10);
//	tMove(4.8949, 0.8929, 10);
//	tMove(4.8153, 0.8727, 10);
//	tMove(4.7379, 0.8452, 10);
//	tMove(4.7243, 0.8396, 10);
//	tMove(4.6534, 0.8060, 10);
//	tMove(4.6437, 0.8007, 10);
//	tMove(4.5733, 0.7583, 10);
//	tMove(4.5072, 0.7095, 10);
//	tMove(4.4986, 0.7026, 10);
//	tMove(4.4405, 0.6500, 10);
//	tMove(4.4325, 0.6422, 10);
//	tMove(4.3774, 0.5814, 10);
//	tMove(4.3705, 0.5728, 10);
//	tMove(4.3538, 0.5502, 10);
//	tMove(-4.3538, 0.5502, 10);
//	tMove(-4.3705, 0.5728, 10);
//	tMove(-4.3774, 0.5814, 10);
//	tMove(-4.4325, 0.6422, 10);
//	tMove(-4.4405, 0.6500, 10);
//	tMove(-4.4986, 0.7026, 10);
//	tMove(-4.5072, 0.7095, 10);
//	tMove(-4.5733, 0.7583, 10);
//	tMove(-4.6437, 0.8007, 10);
//	tMove(-4.6534, 0.8060, 10);
//	tMove(-4.7243, 0.8396, 10);
//	tMove(-4.7379, 0.8452, 10);
//	tMove(-4.8153, 0.8727, 10);
//	tMove(-4.8949, 0.8929, 10);
//	tMove(-4.9093, 0.8957, 10);
//	tMove(-4.9906, 0.9076, 10);
//	tMove(-5.0800, 0.9120, 10);
//	tMove(-5.1694, 0.9076, 10);
//	tMove(-5.2507, 0.8957, 10);
//	tMove(-5.2651, 0.8929, 10);
//	tMove(-5.3447, 0.8727, 10);
//	tMove(-5.4221, 0.8452, 10);
//	tMove(-5.4357, 0.8396, 10);
//	tMove(-5.5033, 0.8076, 10);
//	tMove(-5.5163, 0.8007, 10);
//	tMove(-5.5867, 0.7583, 10);
//	tMove(-5.6586, 0.7050, 10);
//	tMove(-5.7249, 0.6449, 10);
//	tMove(-5.7802, 0.5841, 10);
//	tMove(-5.7873, 0.5757, 10);
//	tMove(-5.8383, 0.5067, 10);
//	tMove(-5.8843, 0.4299, 10);
//	tMove(-5.9226, 0.3490, 10);
//	tMove(-5.9527, 0.2647, 10);
//	tMove(-5.9745, 0.1779, 10);
//	tMove(-5.9876, 0.0894, 10);
//	tMove(-5.9920, -0.0000, 10);
//	tMove(-5.9876, -0.0894, 10);
//	tMove(-5.9745, -0.1779, 10);
//	tMove(-5.9527, -0.2647, 10);
//	tMove(-5.9226, -0.3490, 10);
//	tMove(-5.8843, -0.4299, 10);
//	tMove(-5.8383, -0.5067, 10);
//	tMove(-5.7850, -0.5786, 10);
//	tMove(-5.7249, -0.6449, 10);
//	tMove(-5.6641, -0.7002, 10);
//	tMove(-5.6557, -0.7073, 10);
//	tMove(-5.5867, -0.7583, 10);
//	tMove(-5.5099, -0.8043, 10);
//	tMove(-5.4290, -0.8426, 10);
//	tMove(-5.3447, -0.8727, 10);
//	tMove(-5.2579, -0.8945, 10);
//	tMove(-5.1694, -0.9076, 10);
//	tMove(-5.0800, -0.9120, 10);
//	tMove(-4.9980, -0.9081, 10);
//	tMove(-4.9869, -0.9072, 10);
//	tMove(-4.9021, -0.8945, 10);
//	tMove(-4.8153, -0.8727, 10);
//	tMove(-4.7310, -0.8426, 10);
//	tMove(-4.6567, -0.8076, 10);
//	tMove(-4.6469, -0.8025, 10);
//	tMove(-4.5733, -0.7583, 10);
//	tMove(-4.5072, -0.7095, 10);
//	tMove(-4.4986, -0.7026, 10);
//	tMove(-4.4405, -0.6500, 10);
//	tMove(-4.4325, -0.6422, 10);
//	tMove(-4.3774, -0.5814, 10);
//	tMove(-4.3705, -0.5728, 10);
//	tMove(-4.3538, -0.5502, 10);


//	tHome();
//	tTool.VCP_Config.VCP_State = tVCP_Check();

	/************************************************************************/
//	HAL_UART_Receive_IT(&huart1, tTool.VCP_Config.VCP_data, 20);
//	HAL_UART_Receive_DMA(&huart1, (uint8_t*)&tTool.VCP_Config.VCP_Data_one_byte, 1);


}
void tToolAxisEN(tAxis_t *ax, state_en_t st) {
	HAL_GPIO_WritePin(ax->port_en, ax->pin_en, !st);
}
void tToolAxisWork(tAxis_t *ax, state_en_t st) {
	if (st == ON) {
		HAL_TIM_PWM_Start_IT(ax->timer, ax->timer_channel);
		ax->state_en = st;
	}
	else {
		HAL_TIM_PWM_Stop_IT(ax->timer, ax->timer_channel);
		ax->state_en = st;
	}
}
void tToolAxisDiraction(tAxis_t *ax, side_t side) {
	HAL_GPIO_WritePin(ax->port_dir, ax->pin_dir, side);
}
void tToolSetGMode(GMode_t gm) {
	tTool.GMode = gm;
}
void tToolFeedrateType(feedrate_type_t ftt) {
	tTool.ftt = ftt;
}
void tToolFeedrate(float feedrate) {

	tTool.head.Feed = feedrate;

	/* Finding freq */
	if (tTool.ftt == ftt_mm_min) {			// at 60 sec
		feedrate = feedrate / 60.0;
	}
	else if (tTool.ftt == ftt_mm_sec) { 	// at 1 sec

	}
	float temp = feedrate / ((MOTOR_STEP * SCREW_STEP) / (360.0 * DRIVER_DEVIDER));

	if (temp >= MAX_Frequency) {
		temp = MAX_Frequency;
		tTool.head.Feed = MAX_FEEDRATE;
	}
	else if (temp <= MIN_Frequency) {
		temp = MIN_Frequency;
		tTool.head.Feed = MIN_FEEDRATE;
	}
	/* Finding PS */
	temp = BASE_PSC * (1.0 / (temp / MAX_Frequency));

	tTool.head.tAxis[0].timer->Instance->PSC = temp;
	tTool.head.tAxis[1].timer->Instance->PSC = temp;
	tTool.head.tAxis[2].timer->Instance->PSC = temp;
}

/* Go home */
void tHome(void) {
	tMode(_G1_mode);
	tToolFeedrateType(ftt_mm_min);
	tToolFeedrate(200);

	for (int8_t i = 2; i >= 0; i--) {
		tToolAxisDiraction(&tTool.head.tAxis[i], BackForward);

		tToolAxisEN(&tTool.head.tAxis[i], ON);
		tToolAxisWork(&tTool.head.tAxis[i], ON);
		while (!tTool.head.tAxis[i].state_SW) {}

		tToolAxisDiraction(&tTool.head.tAxis[i], Forward);
		while (tTool.head.tAxis[i].state_SW) {}

		for(uint32_t i = 0; i < 1000000; i++) {}				// Это нужно чтобы отъехать

		tToolAxisWork(&tTool.head.tAxis[i], OFF);

	}

	tToolAxisEN(&tTool.head.tAxis[0], OFF);
	tToolAxisEN(&tTool.head.tAxis[1], OFF);
	tToolAxisEN(&tTool.head.tAxis[2], OFF);

}
/* Timer to perform */
void tToolPerformTimerEN(state_en_t st) {
	if (st) HAL_TIM_Base_Start_IT(&htim14);
	else HAL_TIM_Base_Stop_IT(&htim14);
}
/* Enter g-mode */
void tMode(GMode_t gm) {
	tTool.GMode	= gm;
}
/* Hard forward movement */
static void tMoveDirect(float x, float y, float z) {
	tTool.trg_pos[0] = x;
	tTool.trg_pos[1] = y;
	tTool.trg_pos[2] = z;

	if (x != tTool.curr_pos[0]) {
		if (x > tTool.curr_pos[0]) {
			tTool.head.tAxis[0].direction = Forward;
			tToolAxisDiraction(&tTool.head.tAxis[0], Forward);
		}
		else if (x < tTool.curr_pos[0]) {
			tTool.head.tAxis[0].direction = BackForward;
			tToolAxisDiraction(&tTool.head.tAxis[0], BackForward);
		}

		tToolAxisWork(&tTool.head.tAxis[0], ON);
		tTool.ax_st[0] = ON;
	}
	if (y != tTool.curr_pos[1]) {
		if (y > tTool.curr_pos[1]) {
			tTool.head.tAxis[1].direction = Forward;
			tToolAxisDiraction(&tTool.head.tAxis[1], Forward);
		}
		else if (y < tTool.curr_pos[1]) {
			tTool.head.tAxis[1].direction = BackForward;
			tToolAxisDiraction(&tTool.head.tAxis[1], BackForward);
		}

		tToolAxisWork(&tTool.head.tAxis[1], ON);
		tTool.ax_st[1] = ON;
	}
	if (z != tTool.curr_pos[2]) {
		if (z > tTool.curr_pos[2]) {
			tTool.head.tAxis[2].direction = Forward;
			tToolAxisDiraction(&tTool.head.tAxis[2], Forward);
		}
		else if (z < tTool.curr_pos[2]) {
			tTool.head.tAxis[2].direction = BackForward;
			tToolAxisDiraction(&tTool.head.tAxis[2], BackForward);
		}

		tToolAxisWork(&tTool.head.tAxis[2], ON);
		tTool.ax_st[2] = ON;
	}

	while (1) {
		if (tTool.ax_st[0] == OFF) tToolAxisWork(&tTool.head.tAxis[0], OFF);
		if (tTool.ax_st[1] == OFF) tToolAxisWork(&tTool.head.tAxis[1], OFF);
		if (tTool.ax_st[2] == OFF) tToolAxisWork(&tTool.head.tAxis[2], OFF);
		if (!tTool.ax_st[0] && !tTool.ax_st[1] && !tTool.ax_st[2]) break;
	}

}
/* Move to target position from the current position (calculate) */
void tToolMove(float x, float y, float z) {

	if (tTool.GMode == _G0_mode) {
		tToolFeedrate(MODE_G0_FEEDRATE);

		float x0 = tTool.curr_pos[0];
		float y0 = tTool.curr_pos[1];
		float z0 = tTool.curr_pos[2];

		// Абсолютные разницы
		float dx = fabs(x - x0);
		float dy = fabs(y - y0);
		float dz = fabs(z - z0);
		// Направления
		float sx = (x > x0) ? ACCURACY : ((x < x0) ? -ACCURACY : 0);
		float sy = (y > y0) ? ACCURACY : ((y < y0) ? -ACCURACY : 0);
		float sz = (z > z0) ? ACCURACY : ((z < z0) ? -ACCURACY : 0);
	    // Ошибки
		float err_x = 0.0f;
	    float err_y = 0.0f;
	    float err_z = 0.0f;
	    float d_err_x;
	    float d_err_y;
	    float d_err_z;
	    // Текущие координаты
	    float tx = x0, ty = y0, tz = z0;
	    /***************************************/
		tToolAxisEN(&tTool.head.tAxis[0], ON);
		tToolAxisEN(&tTool.head.tAxis[1], ON);
		tToolAxisEN(&tTool.head.tAxis[2], ON);
	    /***************************************/
	    /* Ведущая X */
	    if ((dx >= dy) && (dx >= dz)) {
	    	d_err_y = (dy + ACCURACY) / (dx + ACCURACY);
	    	d_err_z = (dz + ACCURACY) / (dx + ACCURACY);
	    	d_err_y = d_err_y * ACCURACY;
	    	d_err_z = d_err_z * ACCURACY;
	    	for (;;) {
	    		tMoveDirect(tx, ty, tz);
	    		/* Поиграться с положением этой строки -> */
	    		if (((x - ACCURACY) < tx) && ((x + ACCURACY) > tx)) break;
	    		tx += sx;

	    		err_y += d_err_y;
	    		while (err_y >= ACCURACY) {
	    			ty += sy;
	    			err_y -= ACCURACY;
	    		}
	    		err_z += d_err_z;
	    		while (err_z >= ACCURACY) {
	    			tz += sz;
	    			err_z -= ACCURACY;
	    		}
	    	}
	    }
	    /* Ведущая Y */
	    else if ((dy >= dx) && (dy >= dz)) {
	    	d_err_x = (dx + ACCURACY) / (dy + ACCURACY);
	    	d_err_z = (dz + ACCURACY) / (dy + ACCURACY);
	    	d_err_x = d_err_x * ACCURACY;
	    	d_err_z = d_err_z * ACCURACY;
	    	for (;;) {
	    		tMoveDirect(tx, ty, tz);
	    		/* Поиграться с положением этой строки -> */
	    		if (((y - ACCURACY) < ty) && ((y + ACCURACY) > ty)) break;
	    		ty += sy;

	    		err_x += d_err_x;
	    		while (err_x >= ACCURACY) {
	    			tx += sy;
	    			err_x -= ACCURACY;
	    		}
	    		err_z += d_err_z;
	    		while (err_z >= ACCURACY) {
	    			tz += sz;
	    			err_z -= ACCURACY;
	    		}
	    	}
	    }
	    /* Ведущая Z */
	    else if ((dz >= dx) && (dz >= dx)) {
	    	d_err_x = (dx + ACCURACY) / (dz + ACCURACY);
	    	d_err_y = (dy + ACCURACY) / (dz + ACCURACY);
	    	d_err_x = d_err_x * ACCURACY;
	    	d_err_y = d_err_y * ACCURACY;
	    	for (;;) {
	    		tMoveDirect(tx, ty, tz);
	    		/* Поиграться с положением этой строки -> */
	    		if (((z - ACCURACY) < tz) && ((z + ACCURACY) > tz)) break;
	    		tz += sz;

	    		err_x += d_err_x;
	    		while (err_x >= ACCURACY) {
	    			tx += sx;
	    			err_x -= ACCURACY;
	    		}
	    		err_y += d_err_y;
	    		while (err_y >= ACCURACY) {
	    			ty += sy;
	    			err_y -= ACCURACY;
	    		}
	    	}
	    }

	    /***************************************/
	    tToolAxisWork(&tTool.head.tAxis[0], OFF);
	    tToolAxisWork(&tTool.head.tAxis[1], OFF);
		tToolAxisWork(&tTool.head.tAxis[2], OFF);
		tToolAxisEN(&tTool.head.tAxis[0], OFF);
		tToolAxisEN(&tTool.head.tAxis[1], OFF);
		tToolAxisEN(&tTool.head.tAxis[2], OFF);
	    /***************************************/

//		tToolPerformTimerEN(ON);
//		while(1) {}

	} else if (tTool.GMode == _G1_mode) {
		tToolFeedrate(tTool.head.Feed);

		float x0 = tTool.curr_pos[0];
		float y0 = tTool.curr_pos[1];
		float z0 = tTool.curr_pos[2];

		// Абсолютные разницы
		float dx = fabs(x - x0);
		float dy = fabs(y - y0);
		float dz = fabs(z - z0);
		// Направления
		float sx = (x > x0) ? ACCURACY : ((x < x0) ? -ACCURACY : 0);
		float sy = (y > y0) ? ACCURACY : ((y < y0) ? -ACCURACY : 0);
		float sz = (z > z0) ? ACCURACY : ((z < z0) ? -ACCURACY : 0);
	    // Ошибки
		float err_x = 0.0f;
	    float err_y = 0.0f;
	    float err_z = 0.0f;
	    float d_err_x;
	    float d_err_y;
	    float d_err_z;
	    // Текущие координаты
	    float tx = x0, ty = y0, tz = z0;
	    /***************************************/
		tToolAxisEN(&tTool.head.tAxis[0], ON);
		tToolAxisEN(&tTool.head.tAxis[1], ON);
		tToolAxisEN(&tTool.head.tAxis[2], ON);
	    /***************************************/
	    /* Ведущая X */
	    if ((dx >= dy) && (dx >= dz)) {
	    	d_err_y = (dy + ACCURACY) / (dx + ACCURACY);
	    	d_err_z = (dz + ACCURACY) / (dx + ACCURACY);
	    	d_err_y = d_err_y * ACCURACY;
	    	d_err_z = d_err_z * ACCURACY;
	    	for (;;) {
	    		tMoveDirect(tx, ty, tz);
	    		/* Поиграться с положением этой строки -> */
	    		if (((x - ACCURACY) < tx) && ((x + ACCURACY) > tx)) break;
	    		tx += sx;

	    		err_y += d_err_y;
	    		while (err_y >= ACCURACY) {
	    			ty += sy;
	    			err_y -= ACCURACY;
	    		}
	    		err_z += d_err_z;
	    		while (err_z >= ACCURACY) {
	    			tz += sz;
	    			err_z -= ACCURACY;
	    		}
	    	}
	    }
	    /* Ведущая Y */
	    else if ((dy >= dx) && (dy >= dz)) {
	    	d_err_x = (dx + ACCURACY) / (dy + ACCURACY);
	    	d_err_z = (dz + ACCURACY) / (dy + ACCURACY);
	    	d_err_x = d_err_x * ACCURACY;
	    	d_err_z = d_err_z * ACCURACY;
	    	for (;;) {
	    		tMoveDirect(tx, ty, tz);
	    		/* Поиграться с положением этой строки -> */
	    		if (((y - ACCURACY) < ty) && ((y + ACCURACY) > ty)) break;
	    		ty += sy;

	    		err_x += d_err_x;
	    		while (err_x >= ACCURACY) {
	    			tx += sy;
	    			err_x -= ACCURACY;
	    		}
	    		err_z += d_err_z;
	    		while (err_z >= ACCURACY) {
	    			tz += sz;
	    			err_z -= ACCURACY;
	    		}
	    	}
	    }
	    /* Ведущая Z */
	    else if ((dz >= dx) && (dz >= dx)) {
	    	d_err_x = (dx + ACCURACY) / (dz + ACCURACY);
	    	d_err_y = (dy + ACCURACY) / (dz + ACCURACY);
	    	d_err_x = d_err_x * ACCURACY;
	    	d_err_y = d_err_y * ACCURACY;
	    	for (;;) {
	    		tMoveDirect(tx, ty, tz);
	    		/* Поиграться с положением этой строки -> */
	    		if (((z - ACCURACY) < tz) && ((z + ACCURACY) > tz)) break;
	    		tz += sz;

	    		err_x += d_err_x;
	    		while (err_x >= ACCURACY) {
	    			tx += sx;
	    			err_x -= ACCURACY;
	    		}
	    		err_y += d_err_y;
	    		while (err_y >= ACCURACY) {
	    			ty += sy;
	    			err_y -= ACCURACY;
	    		}
	    	}
	    }

	    /***************************************/
	    tToolAxisWork(&tTool.head.tAxis[0], OFF);
	    tToolAxisWork(&tTool.head.tAxis[1], OFF);
		tToolAxisWork(&tTool.head.tAxis[2], OFF);
		tToolAxisEN(&tTool.head.tAxis[0], OFF);
		tToolAxisEN(&tTool.head.tAxis[1], OFF);
		tToolAxisEN(&tTool.head.tAxis[2], OFF);
	    /***************************************/

	} else if (tTool.GMode == _G2_mode) {
		__NOP();
	} else if (tTool.GMode == _G3_mode) {
		__NOP();
	}
}
VCP_State_t tVCP_Check(void) {
	return (VCP_State_t)HAL_GPIO_ReadPin(VP_ENABLE_PORT, VP_ENABLE_PIN);
}

void tToolSetOrigin(void) {
	tTool.origin_pos[0] = tTool.curr_pos[0];
	tTool.origin_pos[1] = tTool.curr_pos[1];
	tTool.origin_pos[2] = tTool.curr_pos[2];
}
void tToolMoveToOrigin(void) {
	tToolMove(tTool.origin_pos[0], tTool.origin_pos[1], tTool.origin_pos[2]);
}

//===============================================================================================//
// CALLBACKS
//===============================================================================================//
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	/* Switch Axis edges */
	if (GPIO_Pin == tTool.head.tAxis[0].pin_SW) {		// X
		if (tTool.head.tAxis[0].port_SW->IDR & tTool.head.tAxis[0].pin_SW) tTool.head.tAxis[0].state_SW = false;
		else if(!(tTool.head.tAxis[0].port_SW->IDR & tTool.head.tAxis[0].pin_SW)) tTool.head.tAxis[0].state_SW = true;
	}
	else if (GPIO_Pin == tTool.head.tAxis[1].pin_SW) {	// Y
		if (tTool.head.tAxis[1].port_SW->IDR & tTool.head.tAxis[1].pin_SW) tTool.head.tAxis[1].state_SW = false;
		else if(!(tTool.head.tAxis[1].port_SW->IDR & tTool.head.tAxis[1].pin_SW)) tTool.head.tAxis[1].state_SW = true;
	}
	else if (GPIO_Pin == tTool.head.tAxis[2].pin_SW) {	// Z
		if (tTool.head.tAxis[2].port_SW->IDR & tTool.head.tAxis[2].pin_SW) tTool.head.tAxis[2].state_SW = false;
		else if(!(tTool.head.tAxis[2].port_SW->IDR & tTool.head.tAxis[2].pin_SW)) tTool.head.tAxis[2].state_SW = true;
	}
	/* Encoder */
	else if (GPIO_Pin == tTool.Encoder.pin1) {
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET) {
			if (tTool.Encoder.current_rotate_side == Forward) {
				tTool.Encoder.current_rotate_side = BackForward;
				tTool.Encoder.count_last_rotate = 0;
			}
			tTool.Encoder.count_last_rotate++;
		}
		else {
			if (tTool.Encoder.current_rotate_side == BackForward) {
				tTool.Encoder.current_rotate_side = Forward;
				tTool.Encoder.count_last_rotate = 0;
			}
			tTool.Encoder.count_last_rotate++;
		}
	}
	/* Encoder button */
	else if (GPIO_Pin == tTool.Encoder.Button_pin) {
		if (tTool.Encoder.Button_port->IDR & tTool.Encoder.Button_pin) tTool.Encoder.Button_state = false;
		else if(!(tTool.Encoder.Button_port->IDR &tTool.Encoder.Button_pin)) tTool.Encoder.Button_state = true;
	}

//	else if (GPIO_Pin == tTool.Encoder.Button_pin) {
//		tTool.Encoder.Button_state = true;
//	}

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == &huart1) {
		if (tTool.VCP.Data_one_byte == 0xEF) {
			tTool.VCP.line_count	= tTool.VCP.line_temp;
			tTool.VCP.line_temp 	= 0;
			tTool.VCP.data_counter 	= 0;
			tTool.VCP.command_IsReceived = true;
		}
		else if ((tTool.VCP.data_counter >= (tTool.VCP.data[tTool.VCP.line_temp][0])) && (tTool.VCP.data_counter != 0)) {
			tTool.VCP.data[tTool.VCP.line_temp][tTool.VCP.data_counter] = tTool.VCP.Data_one_byte;
			tTool.VCP.data_counter 	= 0;
			tTool.VCP.line_temp++;
		}
		else {
			tTool.VCP.data[tTool.VCP.line_temp][tTool.VCP.data_counter] = tTool.VCP.Data_one_byte;
			tTool.VCP.data_counter++;
		}
	}
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM3) {
//		for (uint8_t i = 0; i < 3; i++) {
//			if (tTool.head.tAxis[i].state_en == ON) {
//
//			}
//		}

		__NOP();
	}
}
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM3) {
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {

		} else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
			if (tTool.ax_st[2]) {
				if (tTool.head.tAxis[2].direction == Forward) {
					tTool.curr_pos[2] += ACCURACY;
					if (tTool.curr_pos[2] >= tTool.trg_pos[2]) tTool.ax_st[2] = false;
				}
				else if (tTool.head.tAxis[2].direction == BackForward) 	{
					tTool.curr_pos[2] -= ACCURACY;
					if (tTool.curr_pos[2] <= tTool.trg_pos[2]) tTool.ax_st[2] = false;
				}
			}
		} else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
			if (tTool.ax_st[1]) {
				if (tTool.head.tAxis[1].direction == Forward) {
					tTool.curr_pos[1] += ACCURACY;
					if (tTool.curr_pos[1] >= tTool.trg_pos[1]) tTool.ax_st[1] = false;
				}
				else if (tTool.head.tAxis[1].direction == BackForward) {
					tTool.curr_pos[1] -= ACCURACY;
					if (tTool.curr_pos[1] <= tTool.trg_pos[1]) tTool.ax_st[1] = false;
				}
			}
		} else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {
			if (tTool.ax_st[0]) {
				if (tTool.head.tAxis[0].direction == Forward) {
					tTool.curr_pos[0] += ACCURACY;
					if (tTool.curr_pos[0] >= tTool.trg_pos[0]) tTool.ax_st[0] = false;
				}
				else if (tTool.head.tAxis[0].direction == BackForward) {
					tTool.curr_pos[0] -= ACCURACY;
					if (tTool.curr_pos[0] <= tTool.trg_pos[0]) tTool.ax_st[0] = false;
				}
			}
		}

//		if (tTool.ax_st[2]) {
//			if (tTool.curr_pos[2] >= tTool.trg_pos[2]) {
//				tTool.ax_st[2] = false;
//			}
//		}
//		if (tTool.ax_st[1]) {
//			if (tTool.curr_pos[1] >= tTool.trg_pos[1]) {
//				tTool.ax_st[1] = false;
//			}
//		}
//		if (tTool.ax_st[0]) {
//			if (tTool.curr_pos[0] >= tTool.trg_pos[0]) {
//				tTool.ax_st[0] = false;
//			}
//		}
	}

}

