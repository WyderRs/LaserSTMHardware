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



//char LCD_Buffer[20];

//void tInit(void) {
//	tTool.state 					= tNoInit;
//	/* Axis X */
//	tTool.head.tAxis[0].port_dir 	= GPIOC;
//	tTool.head.tAxis[0].pin_dir 	= GPIO_PIN_8;
//	tTool.head.tAxis[0].port_en 	= GPIOA;
//	tTool.head.tAxis[0].pin_en 		= GPIO_PIN_8;
//	tTool.head.tAxis[0].port_pulse 	= GPIOC;
//	tTool.head.tAxis[0].pin_pulse 	= GPIO_PIN_9;
//	tTool.head.tAxis[0].port_SW		= GPIOC;
//	tTool.head.tAxis[0].pin_SW		= GPIO_PIN_12;
//	tTool.head.tAxis[0].state_SW	= false;
//	/* Axis Y */
//	tTool.head.tAxis[1].port_dir 	= GPIOB;
//	tTool.head.tAxis[1].pin_dir 	= GPIO_PIN_15;
//	tTool.head.tAxis[1].port_en 	= GPIOC;
//	tTool.head.tAxis[1].pin_en 		= GPIO_PIN_7;
//	tTool.head.tAxis[1].port_pulse 	= GPIOC;
//	tTool.head.tAxis[1].pin_pulse 	= GPIO_PIN_6;
//	tTool.head.tAxis[1].port_SW		= GPIOD;
//	tTool.head.tAxis[1].pin_SW		= GPIO_PIN_2;
//	tTool.head.tAxis[1].state_SW	= false;
//	/* Axis Z */
//	tTool.head.tAxis[2].port_dir 	= GPIOB;
//	tTool.head.tAxis[2].pin_dir 	= GPIO_PIN_12;
//	tTool.head.tAxis[2].port_en 	= GPIOB;
//	tTool.head.tAxis[2].pin_en 		= GPIO_PIN_14;
//	tTool.head.tAxis[2].port_pulse 	= GPIOB;
//	tTool.head.tAxis[2].pin_pulse 	= GPIO_PIN_13;
//	tTool.head.tAxis[2].port_SW		= GPIOB;
//	tTool.head.tAxis[2].pin_SW		= GPIO_PIN_3;
//	tTool.head.tAxis[2].state_SW	= false;
//	/* Encoder */
//	tTool.Encoder.port1				= GPIOB;
//	tTool.Encoder.pin1				= GPIO_PIN_5;
//	tTool.Encoder.port2				= GPIOB;
//	tTool.Encoder.pin2				= GPIO_PIN_4;
//	tTool.Encoder.Button_port		= GPIOB;
//	tTool.Encoder.Button_pin		= GPIO_PIN_8;
//	tTool.Encoder.current_rotate_side = Forward;
//	tTool.Encoder.count_last_rotate = 0;
//	tTool.Encoder.Button_state 		= false;
//
//	/* Laser */
//	tTool.laser.port				= GPIOB;
//	tTool.laser.pin					= GPIO_PIN_9;
//	/* Culler */
//	tTool.culler.port				= GPIOC;
//	tTool.culler.pin				= GPIO_PIN_11;
//
//	/* x = [8(step line screw) * 1.8(step motor step)] / [360 * 16(step divider on driver)] = 0.0025mm */
//	tTool.Settings.stpLineValue			= (8.0 * 1.8) / (360.0 * DRV_DIVIDER);
//
//	/* First definition */
//	tAxisEN(&tTool.head.tAxis[0], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[1], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[2], OFF, OFF);
//	tLaserEN(OFF);
//	tTool.VCP_Config.VCP_State = tVCP_Check();
//
//	tToolSetState(tReady);
//	HAL_TIM_Base_Start_IT(&htim11);
//	/************************************************************************/
//
//
////	HAL_UART_Receive_IT(&huart1, tTool.VCP_Config.VCP_data, 20);
//	HAL_UART_Receive_DMA(&huart1, (uint8_t*)&tTool.VCP_Config.VCP_Data_one_byte, 1);
//}

//void tHome(void) {
//	tToolSetState(tReady);
//	tMoveSetSpeed(8);
//
//	tAxisEN(&tTool.head.tAxis[0], OFF, ON);
//	tAxisEN(&tTool.head.tAxis[1], OFF, ON);
//	tAxisEN(&tTool.head.tAxis[2], OFF, ON);
//
//	for (uint8_t i = 2; i <= 2; i--) {
//		tDriverSetDir(&tTool.head.tAxis[i], BackForward);
//		tAxisEN(&tTool.head.tAxis[i], ON, ON);
//		while(!tTool.head.tAxis[i].state_SW) {}
//		tDriverSetDir(&tTool.head.tAxis[i], Forward);
//		while(tTool.head.tAxis[i].state_SW) {}
//		tAxisEN(&tTool.head.tAxis[i], OFF, ON);
//	}
//
//	tAxisEN(&tTool.head.tAxis[0], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[1], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[2], OFF, OFF);
//
//	tMove_SetOrigin();
//}
//void tHomeAxis(tAxis_t *ax) {
//	tToolSetState(tReady);
//	tMoveSetSpeed(8);
//
//	tAxisEN(ax, OFF, ON);
//
//	tDriverSetDir(ax, BackForward);
//	tAxisEN(ax, ON, ON);
//	while(!ax->state_SW) {}
//	tDriverSetDir(ax, Forward);
//	while(ax->state_SW) {}
//
//	tAxisEN(ax, OFF, OFF);
//
//	tMove_SetOrigin();
//}
//
//void tMove_SetOrigin(void) {
//	tTool.head.tAxis[0].current_pos_coord = 0;
//	tTool.head.tAxis[1].current_pos_coord = 0;
//	tTool.head.tAxis[2].current_pos_coord = 0;
//	tTool.head.tAxis[0].current_cnt = 0;
//	tTool.head.tAxis[1].current_cnt = 0;
//	tTool.head.tAxis[2].current_cnt = 0;
//
//}
//void tMoveRelative_A(float x, float y, float z) {	// (A)uto, not holding down the program
//	if (x < 0) {
//		tDriverSetDir(&tTool.head.tAxis[0], BackForward);
//	}
//	else if (x > 0) {
//		tDriverSetDir(&tTool.head.tAxis[0], Forward);
//	}
//	if (y < 0) {
//		tDriverSetDir(&tTool.head.tAxis[1], BackForward);
//	}
//	else if (y > 0) {
//		tDriverSetDir(&tTool.head.tAxis[1], Forward);
//	}
//	if (z < 0) {
//		tDriverSetDir(&tTool.head.tAxis[2], BackForward);
//	}
//	else if (z > 0) {
//		tDriverSetDir(&tTool.head.tAxis[2], Forward);
//	}
//
//
//	if (x == 0) tAxisEN(&tTool.head.tAxis[0], OFF, OFF); else tAxisEN(&tTool.head.tAxis[0], ON, ON);
//	if (y == 0) tAxisEN(&tTool.head.tAxis[1], OFF, OFF); else tAxisEN(&tTool.head.tAxis[1], ON, ON);
//	if (z == 0) tAxisEN(&tTool.head.tAxis[2], OFF, OFF); else tAxisEN(&tTool.head.tAxis[2], ON, ON);
//
//	LED_AUTO_OP_ON;
//	tTool.state = tAutoMove;
//}
//void tMoveRelative(float dx, float dy, float dz) {
//
//	tToolSetState(tBusy);
//
//	if (dx < 0) tDriverSetDir(&tTool.head.tAxis[0], BackForward);
//	else if (dx > 0) tDriverSetDir(&tTool.head.tAxis[0], Forward);
//
//	if (dy < 0) tDriverSetDir(&tTool.head.tAxis[1], BackForward);
//	else if (dy > 0)tDriverSetDir(&tTool.head.tAxis[1], Forward);
//
//	if (dz < 0) tDriverSetDir(&tTool.head.tAxis[2], BackForward);
//	else if (dz > 0) tDriverSetDir(&tTool.head.tAxis[2], Forward);
//
//	tTool.head.tAxis[0].target_pos_coord = tTool.head.tAxis[0].current_pos_coord + dx;
//	tTool.head.tAxis[1].target_pos_coord = tTool.head.tAxis[1].current_pos_coord + dy;
//	tTool.head.tAxis[2].target_pos_coord = tTool.head.tAxis[2].current_pos_coord + dz;
//
//	dx = fabs(tTool.head.tAxis[0].current_pos_coord - tTool.head.tAxis[0].target_pos_coord);
//	dy = fabs(tTool.head.tAxis[1].current_pos_coord - tTool.head.tAxis[1].target_pos_coord);
//	dz = fabs(tTool.head.tAxis[2].current_pos_coord - tTool.head.tAxis[2].target_pos_coord);
//
//	float c = sqrt(dx * dx + dy * dy + dz * dz);
//
//	float xk = fabs(dx / c);
//	float yk = fabs(dy / c);
//	float zk = fabs(dz / c);
//
//	tMoveAdjustmentSpeed(&tTool.head.tAxis[0], xk * tTool.head.tAxis[0].installed_speed_mm);
//	tMoveAdjustmentSpeed(&tTool.head.tAxis[1], yk * tTool.head.tAxis[1].installed_speed_mm);
//	tMoveAdjustmentSpeed(&tTool.head.tAxis[2], zk * tTool.head.tAxis[2].installed_speed_mm);
//
//
//	if (((0 + tTool.Settings.stpLineValue) > dx) && ((0 - tTool.Settings.stpLineValue) < dx)) {
//		tAxisEN(&tTool.head.tAxis[0], OFF, ON);
//	}
//	else {
//		tTool.head.tAxis[0].task_state = Progress;
//		tAxisEN(&tTool.head.tAxis[0], ON, ON);
//	}
//	if (((0 + tTool.Settings.stpLineValue) > dy) && ((0 - tTool.Settings.stpLineValue) < dy)) {
//		tAxisEN(&tTool.head.tAxis[1], OFF, ON);
//	}
//	else {
//		tTool.head.tAxis[1].task_state = Progress;
//		tAxisEN(&tTool.head.tAxis[1], ON, ON);
//	}
//	if (((0 + tTool.Settings.stpLineValue) > dz) && ((0 - tTool.Settings.stpLineValue) < dz)) {
//		tAxisEN(&tTool.head.tAxis[2], OFF, ON);
//	}
//	else {
//		tTool.head.tAxis[2].task_state = Progress;
//		tAxisEN(&tTool.head.tAxis[2], ON, ON);
//	}
//
//	tToolSetState(tReady);
//	_Bool flag[3] = {false,};
//	while(!((flag[0]) && (flag[1]) && (flag[2]))) {
//
//		if (tTool.head.tAxis[0].task_state == Ended) {
//			flag[0] = true;
//		}
//		if (tTool.head.tAxis[1].task_state == Ended) {
//			flag[1] = true;
//		}
//		if (tTool.head.tAxis[2].task_state == Ended) {
//			flag[2] = true;
//		}
//	}
//
//	tAxisEN(&tTool.head.tAxis[0], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[1], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[2], OFF, OFF);
//}
//void tMoveGlobal(float x, float y, float z) {
//
//	tToolSetState(tBusy);
//
//	if (x < tTool.head.tAxis[0].current_pos_coord) tDriverSetDir(&tTool.head.tAxis[0], BackForward);
//	else if (x > tTool.head.tAxis[0].current_pos_coord) tDriverSetDir(&tTool.head.tAxis[0], Forward);
//
//	if (y < tTool.head.tAxis[1].current_pos_coord) tDriverSetDir(&tTool.head.tAxis[1], BackForward);
//	else if (y > tTool.head.tAxis[1].current_pos_coord)tDriverSetDir(&tTool.head.tAxis[1], Forward);
//
//	if (z < tTool.head.tAxis[2].current_pos_coord) tDriverSetDir(&tTool.head.tAxis[2], BackForward);
//	else if (z > tTool.head.tAxis[2].current_pos_coord) tDriverSetDir(&tTool.head.tAxis[2], Forward);
//
//	tTool.head.tAxis[0].target_pos_coord = x;
//	tTool.head.tAxis[1].target_pos_coord = y;
//	tTool.head.tAxis[2].target_pos_coord = z;
//
//	float dx = fabs(tTool.head.tAxis[0].current_pos_coord - tTool.head.tAxis[0].target_pos_coord);
//	float dy = fabs(tTool.head.tAxis[1].current_pos_coord - tTool.head.tAxis[1].target_pos_coord);
//	float dz = fabs(tTool.head.tAxis[2].current_pos_coord - tTool.head.tAxis[2].target_pos_coord);
//
//	float c = sqrt(dx * dx + dy * dy + dz * dz);
//
//	float xk = fabs(dx / c);
//	float yk = fabs(dy / c);
//	float zk = fabs(dz / c);
//
//	tMoveAdjustmentSpeed(&tTool.head.tAxis[0], xk * tTool.head.tAxis[0].installed_speed_mm);
//	tMoveAdjustmentSpeed(&tTool.head.tAxis[1], yk * tTool.head.tAxis[1].installed_speed_mm);
//	tMoveAdjustmentSpeed(&tTool.head.tAxis[2], zk * tTool.head.tAxis[2].installed_speed_mm);
//
//
//	if (((0 + tTool.Settings.stpLineValue) > dx) && ((0 - tTool.Settings.stpLineValue) < dx)) {
//		tAxisEN(&tTool.head.tAxis[0], OFF, ON);
//	}
//	else {
//		tTool.head.tAxis[0].task_state = Progress;
//		tAxisEN(&tTool.head.tAxis[0], ON, ON);
//	}
//	if (((0 + tTool.Settings.stpLineValue) > dy) && ((0 - tTool.Settings.stpLineValue) < dy)) {
//		tAxisEN(&tTool.head.tAxis[1], OFF, ON);
//	}
//	else {
//		tTool.head.tAxis[1].task_state = Progress;
//		tAxisEN(&tTool.head.tAxis[1], ON, ON);
//	}
//	if (((0 + tTool.Settings.stpLineValue) > dz) && ((0 - tTool.Settings.stpLineValue) < dz)) {
//		tAxisEN(&tTool.head.tAxis[2], OFF, ON);
//	}
//	else {
//		tTool.head.tAxis[2].task_state = Progress;
//		tAxisEN(&tTool.head.tAxis[2], ON, ON);
//	}
//
//	tToolSetState(tReady);
//	_Bool flag[3] = {false,};
//	while(!((flag[0]) && (flag[1]) && (flag[2]))) {
//
//		if ((tTool.head.tAxis[0].task_state == Ended) || (tTool.head.tAxis[0].task_state == noUse)) {
//			flag[0] = true;
//		}
//		if ((tTool.head.tAxis[1].task_state == Ended) || (tTool.head.tAxis[1].task_state == noUse)) {
//			flag[1] = true;
//		}
//		if ((tTool.head.tAxis[2].task_state == Ended) || (tTool.head.tAxis[2].task_state == noUse)) {
//			flag[2] = true;
//		}
//	}
//
//	tAxisEN(&tTool.head.tAxis[0], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[1], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[2], OFF, OFF);
//}
//void tMoveAdjustmentSpeed(tAxis_t* ax, float sp) {
//	uint32_t number_pulses = (float)(1.0 / (4.0 * sp * tTool.Settings.stpLineValue));
//	ax->tgl = number_pulses;
//}
//void tMoveSetSpeed(float sp) {
//	// e.g.: 1mm / 2.0 * 2.0 * step = number pulses (2.0 because TogglePin), (2.0 because TogglePin for mm)
//	// 1 mm = 25p => toggle => 1mm == 50p,
//	uint32_t number_pulses = (float)(1.0 / (4 * sp * tTool.Settings.stpLineValue));
//	tTool.head.tAxis[0].tgl = number_pulses;
//	tTool.head.tAxis[1].tgl = number_pulses;
//	tTool.head.tAxis[2].tgl = number_pulses;
//
//	tTool.head.tAxis[0].installed_speed_mm = sp;
//	tTool.head.tAxis[1].installed_speed_mm = sp;
//	tTool.head.tAxis[2].installed_speed_mm = sp;
//	tTool.Settings.speed = sp;
//}
//void tToolSetState(state_work_t st) {
//	tTool.state = st;
//}
//void tAxisEN(tAxis_t *ax, state_en_t st, state_en_t stateDrv) {
//	HAL_GPIO_WritePin(ax->port_en, ax->pin_en, !stateDrv);
//	ax->enable = st;
//}
//void tDriverSetDir(tAxis_t *ax, side_t sd) {
//	HAL_GPIO_WritePin(ax->port_dir, ax->pin_dir, sd);
//	ax->direction = sd;
//}
//void tLaserEN(state_en_t st) {
//	HAL_GPIO_WritePin(tTool.laser.port, tTool.laser.pin, st);
//}
//
//VCP_State_t tVCP_Check(void) {
//	return (VCP_State_t)HAL_GPIO_ReadPin(VP_ENABLE_PORT, VP_ENABLE_PIN);
//}
//void tGSetMode(GCode_Mode_t mode) {
//
//	tTool.GCode_Status = mode;
//	return;
//}
//
//
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//
//	if (htim->Instance == TIM11) { // 10us
//
//		for (uint8_t i = 0; i < 3; i++) {
//			if ((tTool.state == tReady) || (tTool.state == tAutoMove)) {
//				if (tTool.head.tAxis[i].enable) {
//					if (tTool.head.tAxis[i].counter >= (tTool.head.tAxis[i].tgl-1)) {
//						HAL_GPIO_TogglePin(tTool.head.tAxis[i].port_pulse, tTool.head.tAxis[i].pin_pulse);
//						tTool.head.tAxis[i].counter = 0;
//
//						if (tTool.head.tAxis[i].direction == Forward) {
//							tTool.head.tAxis[i].current_cnt++;
//							if ((tTool.head.tAxis[i].current_cnt % 2) == 0) {
//								tTool.head.tAxis[i].current_pos_coord += tTool.Settings.stpLineValue;
//							}
//						}
//						else if (tTool.head.tAxis[i].direction == BackForward) {
//							tTool.head.tAxis[i].current_cnt--;
//							if ((tTool.head.tAxis[i].current_cnt % 2) == 0) {
//								tTool.head.tAxis[i].current_pos_coord -= tTool.Settings.stpLineValue;
//							}
//						}
//					}
//					else tTool.head.tAxis[i].counter++;
//
//					if (tTool.head.tAxis[i].task_state == Progress) {
//						if ((tTool.head.tAxis[i].current_pos_coord > (tTool.head.tAxis[i].target_pos_coord - tTool.Settings.stpLineValue))
//								&& (tTool.head.tAxis[i].current_pos_coord < (tTool.head.tAxis[i].target_pos_coord + tTool.Settings.stpLineValue))) {
//							tTool.head.tAxis[i].task_state = Ended;
//							tAxisEN(&tTool.head.tAxis[i], OFF, ON);
//						}
//					}
//				}
//			}
//		}
//	}
//}


//void tVCP_Command(uint32_t bytes) {
//
//	tTool.VCP_Config.VCP_command_IsReceived = true;
//	tTool.VCP_Config.VCP_cnt_last_file = bytes;
//
//}
//===============================================================================================//
// CALLBACKS
//===============================================================================================//
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
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

//	else if (GPIO_Pin == tTool.Encoder.pin1) {
//		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET) {
//			if (tTool.Encoder.current_rotate_side == Forward) {
//				tTool.Encoder.current_rotate_side = BackForward;
//				tTool.Encoder.count_last_rotate = 0;
//			}
//			tTool.Encoder.count_last_rotate++;
//		}
//		else {
//			if (tTool.Encoder.current_rotate_side == BackForward) {
//				tTool.Encoder.current_rotate_side = Forward;
//				tTool.Encoder.count_last_rotate = 0;
//			}
//			tTool.Encoder.count_last_rotate++;
//		}
//	}
//	else if (GPIO_Pin == tTool.Encoder.Button_pin) {
//		tTool.Encoder.Button_state = true;
//	}

}
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//
//	if (huart == &huart1) {
//
//		tTool.VCP_Config.VCP_data[tTool.VCP_Config.VCP_Data_counter] = tTool.VCP_Config.VCP_Data_one_byte;
//		tTool.VCP_Config.VCP_Data_counter++;
//
//		if (tTool.VCP_Config.VCP_Data_counter == (((tTool.VCP_Config.VCP_data[0] << 8) | (tTool.VCP_Config.VCP_data[1] << 0)) + 1)) {
//			tVCP_Command(tTool.VCP_Config.VCP_Data_counter);
//			tTool.VCP_Config.VCP_Data_counter = 0;
//		}
//	}
//
//}






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




	tHome();



	/* x = [8(step line screw) * 1.8(step motor step)] / [360 * 16(step divider on driver)] = 0.0025mm */
//	tTool.Settings.stpLineValue			= (8.0 * 1.8) / (360.0 * DRV_DIVIDER);
	/* First definition */
//	tAxisEN(&tTool.head.tAxis[0], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[1], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[2], OFF, OFF);
//	tTool.VCP_Config.VCP_State = tVCP_Check();

//	tToolSetState(tReady);
//	HAL_TIM_Base_Start_IT(&htim11);
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
	}
	else HAL_TIM_PWM_Stop_IT(ax->timer, ax->timer_channel);
}
void tToolAxisDiraction(tAxis_t *ax, side_t side) {
	HAL_GPIO_WritePin(ax->port_dir, ax->pin_dir, side);
}
void tToolFeedrate(float feedrate) {
	/* Finding freq */
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

	tTool.head.tAxis[2].timer->Instance->PSC = temp;
}

/* Go home */
void tHome(void) {
	tTool.GMode 					= _G0_mode;
	tToolFeedrate(3);
	tTool.head.tAxis[2].timer->Instance->CCR2 = 50;

	for (int8_t i = 2; i >= 0; i--) {
		tToolAxisDiraction(&tTool.head.tAxis[i], Forward);

		tToolAxisEN(&tTool.head.tAxis[i], ON);
		tToolAxisWork(&tTool.head.tAxis[i], ON);
		while (!tTool.head.tAxis[i].state_SW) {}

		tToolAxisDiraction(&tTool.head.tAxis[i], BackForward);

		while (tTool.head.tAxis[i].state_SW) {}
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

}
/* Move to target position from the current position */
void tMove(float x, float y, float z) {

	if (tTool.GMode == _G0_mode) {
		tToolFeedrate(MODE_G0_FEEDRATE);

		int16_t x0 = 0, y0 = 0, z0 = 0;
		int16_t x1 = 0, y1 = 0, z1 = 0;
		// Абсолютные разницы
		int16_t delta_x = abs(x1 - x0);
		int16_t delta_y = abs(y1 - y0);
		int16_t delta_z = abs(z1 - z0);
		// Направления
		int8_t sx = (x1 > x0) ? 1 : ((x1 < x0) ? -1 : 0);
		int8_t sy = (y1 > y0) ? 1 : ((y1 < y0) ? -1 : 0);
		int8_t sz = (z1 > z0) ? 1 : ((z1 < z0) ? -1 : 0);
	    // Ошибки
	    float err_y = 0.0f;
	    float err_z = 0.0f;
	    float delta_err_y, delta_err_z;
	    // Текущие координаты
	    int16_t x = x0, y = y0, z = z0;







	    int16_t dx = abs(x1 - x0);
	    int16_t dy = abs(y1 - y0);
	    int16_t dz = abs(z1 - z0);

	    int8_t sx = (x1 > x0) ? 1 : ((x1 < x0) ? -1 : 0);
	    int8_t sy = (y1 > y0) ? 1 : ((y1 < y0) ? -1 : 0);
	    int8_t sz = (z1 > z0) ? 1 : ((z1 < z0) ? -1 : 0);

	    float err_y = 0.0f, err_z = 0.0f, err_x = 0.0f;
	    float d_err_x, d_err_y, d_err_z;

	    int16_t x = x0, y = y0, z = z0;

	    if (dx >= dy && dx >= dz) {
	        /* Ведущая ось X */
	        d_err_y = (dy + 1.0f) / (dx + 1.0f);
	        d_err_z = (dz + 1.0f) / (dx + 1.0f);
	        for (int16_t i = 0; i <= dx; i++) {
	            PlotVoxel(x, y, z, color);
	            x += sx;
	            err_y += d_err_y; while (err_y >= 1.0f) { y += sy; err_y -= 1.0f; }
	            err_z += d_err_z; while (err_z >= 1.0f) { z += sz; err_z -= 1.0f; }
	        }
	    } else if (dy >= dx && dy >= dz) {
	        /* Ведущая ось Y */
	        d_err_x = (dx + 1.0f) / (dy + 1.0f);
	        d_err_z = (dz + 1.0f) / (dy + 1.0f);
	        for (int16_t i = 0; i <= dy; i++) {
	            PlotVoxel(x, y, z, color);
	            y += sy;
	            err_x += d_err_x; while (err_x >= 1.0f) { x += sx; err_x -= 1.0f; }
	            err_z += d_err_z; while (err_z >= 1.0f) { z += sz; err_z -= 1.0f; }
	        }
	    } else {
	        /* Ведущая ось Z */
	        d_err_x = (dx + 1.0f) / (dz + 1.0f);
	        d_err_y = (dy + 1.0f) / (dz + 1.0f);
	        for (int16_t i = 0; i <= dz; i++) {
	            PlotVoxel(x, y, z, color);
	            z += sz;
	            err_x += d_err_x; while (err_x >= 1.0f) { x += sx; err_x -= 1.0f; }
	            err_y += d_err_y; while (err_y >= 1.0f) { y += sy; err_y -= 1.0f; }
	        }
	    }












		tToolPerformTimerEN(ON);
		while(1) {}


	} else if (tTool.GMode == _G1_mode) {

		tToolFeedrate(tTool.head.Feed);

//		int16_t x0 = 0, y0 = 0, z0 = 0;
//		int16_t x1 = 0, y1 = 0, z1 = 0;
//		// Абсолютные разницы
//		int16_t delta_x = abs(x1 - x0);
//		int16_t delta_y = abs(y1 - y0);
//		int16_t delta_z = abs(z1 - z0);
//	    // Направления
//	    int8_t sx = (x1 > x0) ? 1 : ((x1 < x0) ? -1 : 0);
//	    int8_t sy = (y1 > y0) ? 1 : ((y1 < y0) ? -1 : 0);
//	    int8_t sz = (z1 > z0) ? 1 : ((z1 < z0) ? -1 : 0);
//
//
//
//
//
//
//
//
//		// Bresenham's algorithm
//		int16_t delta_x = abs(x1 - x0);
//		int16_t delta_y = abs(y1 - y0);
//
//		float err = 0;
//		float delta_err = ((delta_y + 1.0) / (delta_x + 1.0));
//
//		int16_t y = y0;
//		int16_t dir_y = y1 - y0;
//
//		if (dir_y > 0) {
//			dir_y = 1;
//		} else if (dir_y < 0) dir_y = -1;
//
//		for (uint16_t x = x0; x <= x1; x++) {

//			ST7735_DrawPixel(x, y, color);
//			err = err + delta_err;
//
//			if (err >= 1.0) {
//				while (err >= 1.0) {
//
//					y = y + dir_y;
//					err = err - 1.0;
//					ST7735_DrawPixel(x, y, color);
//				}
//			}
//		}

	} else if (tTool.GMode == _G2_mode) {

	} else if (tTool.GMode == _G3_mode) {

	}




}



/*
void draw_line_3d(int16_t x0, int16_t y0, int16_t z0,
                  int16_t x1, int16_t y1, int16_t z1,
                  uint16_t color)
{
    // Абсолютные разницы
    int16_t dx = abs(x1 - x0);
    int16_t dy = abs(y1 - y0);
    int16_t dz = abs(z1 - z0);

    // Направления
    int8_t sx = (x1 > x0) ? 1 : ((x1 < x0) ? -1 : 0);
    int8_t sy = (y1 > y0) ? 1 : ((y1 < y0) ? -1 : 0);
    int8_t sz = (z1 > z0) ? 1 : ((z1 < z0) ? -1 : 0);

    // Ошибки
    float err_y = 0.0f;
    float err_z = 0.0f;
    float delta_err_y, delta_err_z;

    // Текущие координаты
    int16_t x = x0, y = y0, z = z0;

    // Выбираем ведущую ось — ту, по которой больше всего шагов
    if (dx >= dy && dx >= dz) {
        // Ведущая ось X
        delta_err_y = (dy + 1.0f) / (dx + 1.0f);
        delta_err_z = (dz + 1.0f) / (dx + 1.0f);

        for (int16_t i = 0; i <= dx; i++) {
            PlotVoxel(x, y, z, color);
            x += sx;

            err_y += delta_err_y;
            while (err_y >= 1.0f) {
                y += sy;
                err_y -= 1.0f;
            }

            err_z += delta_err_z;
            while (err_z >= 1.0f) {
                z += sz;
                err_z -= 1.0f;
            }
        }
    } else if (dy >= dx && dy >= dz) {
        // Ведущая ось Y
        delta_err_x = ...
        // аналогично
    } else {
        // Ведущая ось Z
    }
}


*/





