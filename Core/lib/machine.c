/*
 * machine.c
 *
 *  Created on: May 4, 2026
 *      Author: makar
 */

#include <stdbool.h>
#include "machine.h"

Machine_t machine;
global_time_t glb_tim;


extern TIM_HandleTypeDef 	htim7;
extern TIM_HandleTypeDef 	htim6;
extern UART_HandleTypeDef 	huart1;

extern volatile uint8_t SD_Timer1, SD_Timer2;



void MachineSetProgramLimit(Axis_t* ax, float start, float end)
{
	ax->limit_start_coord 	= start;
	ax->limit_end_coord 	= end;
}
void ModuleCountCurvEN(counter_curve_t* cc, _Bool en)
{
	cc->enabled = en;
	cc->counter = 0;
}
void ModuleCountCurvTgl(counter_curve_t* cc, uint32_t tgl)
{
	cc->tgl_up = tgl;
}
void ModuleDriverDirection(Drive_t* drv, SideMV_t dr)
{
	drv->m_side = dr;
	HAL_GPIO_WritePin(drv->m_dir_port, drv->m_dir_pin, dr);
}
void ModuleDriverEnable(Drive_t* drv, _Bool st)
{
	drv->m_drv_enabled = st;
	HAL_GPIO_WritePin(drv->m_en_port, drv->m_en_pin, !st);
}
void Machine_SW_Set(Axis_t* ax, _Bool st)
{
	ax->sw_key.sw_k_state = st;
}
void MachineCoordSet(Axis_t* ax, uint32_t var) {
	ax->mach_base_crd = var;
}
void MachineRelativeSet(Axis_t* ax, uint32_t var) {
	ax->mach_base_crd = var;
}
void MachineLaserState(_Bool st) {
	machine.head.LR_State = st;
	HAL_GPIO_WritePin(machine.head.LR_port, machine.head.LR_pin, st);
}
//================================================================================================
void GlbtimDelay(uint32_t us) {
	uint32_t tim_end = glb_tim.glb_time + us;
	while (!(tim_end <= glb_tim.glb_time)) {}
}
void Machine_Start_MainCounter(void) {
	HAL_TIM_Base_Start_IT(&htim7);
}
void Machine_Stop_MainCounter(void) {
	HAL_TIM_Base_Stop_IT(&htim7);
}
void Machine_Start_SupCounter(void) {
	HAL_TIM_Base_Start_IT(&htim6);
}
void Machine_Stop_SupCounter(void) {
	HAL_TIM_Base_Stop_IT(&htim6);
}
//================================================================================================

//================================================================================================

//================================================================================================
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* 10 uS */
	if (htim->Instance == TIM7) {
		for (uint8_t i = 0; i < 2; i++)
		{
//			if(machine.axis[i].working)
//			{
				/********/
				if (machine.axis[i].c_curve.enabled) {
					if (machine.axis[i].c_curve.counter >= (machine.axis[i].c_curve.tgl_up - 1)) {
						HAL_GPIO_TogglePin(machine.axis[i].drive.m_pulse_port, machine.axis[i].drive.m_pulse_pin);
						machine.axis[i].c_curve.counter = 0;

						/***************/
						machine.axis[i].drive.counter++;

						if (machine.axis[i].current_side == Forward) {
							machine.axis[i].c_curve.current_pos++;
							if ((machine.axis[i].c_curve.current_pos % 2) == 0) {
								machine.axis[i].current_pos_coord += ONE_STEP_WIDTH;
							}
						}
						else if (machine.axis[i].current_side == BackForward) {
							machine.axis[i].c_curve.current_pos--;
							if ((machine.axis[i].c_curve.current_pos % 2) == 0) {
								machine.axis[i].current_pos_coord -= ONE_STEP_WIDTH;
							}
						}
						else {}
						/***************/
					}
					else machine.axis[i].c_curve.counter++;
				}
//			}
		}
	}
	else if (htim->Instance == TIM6) {
		/* Таймер счета времени (милисекунды) */
		glb_tim.glb_time++;
		SD_Timer1++;
		SD_Timer2++;
	}
	else if (htim->Instance == 0) {
		/* Этот таймер желательно использовать чтобы запускать функции, а также для создания и обработки очередей. */
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_8) /*encoder*/
	{
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_RESET)
		{

		}
		else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_SET)
		{

		}
		for (uint32_t slp = 0; slp < 1000; slp++) {}
	}
	else if (GPIO_Pin == GPIO_PIN_5)		// button
	{
//		FLAG[0] = true;
	}
	else if (GPIO_Pin == GPIO_PIN_6)		// X
	{
		if (machine.axis[0].sw_key.sw_k_enabled) {
			ModuleCountCurvEN(&machine.axis[0].c_curve, false);
			Machine_SW_Set(&machine.axis[0], true);
			machine.axis[0].drive.counter = 0;
		}
	}
	else if (GPIO_Pin == GPIO_PIN_7)		// Y
	{
		if (machine.axis[1].sw_key.sw_k_enabled) {
			ModuleCountCurvEN(&machine.axis[1].c_curve, false);
			Machine_SW_Set(&machine.axis[1], true);
			machine.axis[1].drive.counter = 0;

		}
	}
}



//uint8_t uart_data[50];
//uint8_t uart_dat;
//uint16_t uart_inx;
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if (huart == &huart1)
//	{
////		if (uart_data[0] == 0xDD)
////		{
////			if (uart_data[1] == 0x01)		// X
////			{
////				FLAG[1] = true;
////			}
////			else if (uart_data[1] == 0x02)	// Y
////			{
////				FLAG[2] = true;
////			}
////		}
//		if (uart_dat != ';') {
//			uart_data[uart_inx++] = uart_dat;
//		}
//		else if (uart_dat == ';') {
//			uart_data[uart_inx++] = ';';
//			FLAG[5] = true;
//			uart_inx = 0;
//		}
//
//		HAL_UART_Receive_IT(&huart1, (uint8_t*)&uart_dat, 1);
//	}
//}





