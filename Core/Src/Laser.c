/*
 * Laser.c
 *
 *  Created on: Feb 22, 2026
 *      Author: makar
 */

#include "Laser.h"
#include "AS5600.h"

#include <stdio.h>
#include <stdlib.h>
#include "SD.h"
#include "../lib/t_config.h"

extern TIM_HandleTypeDef 	htim7;
extern TIM_HandleTypeDef 	htim6;

extern UART_HandleTypeDef huart1;

uint8_t uart_data[50];
uint8_t uart_dat;
uint16_t uart_inx;


Machine_t machine;
global_time_t glb_tim;

/*Flags*/
_Bool FLAG[10];
/*
 * 0 - Флаг поиска дома
 *
 *
 *
 * */

/*************************/
uint32_t sd_file_rows;


/*************************/
extern volatile uint8_t SD_Timer1, SD_Timer2;
FATFS fs;
FIL fil;

/*************************/

void MachineSetProgramLimit(Axis_t* ax, float start, float end)
{
	ax->limit_start_coord = start;
	ax->limit_end_coord = end;
}
void LaserCountCurvEN(counter_curve_t* cc, _Bool en)
{
	cc->enabled = en;
	cc->counter = 0;
}
void LaserCountCurvTgl(counter_curve_t* cc, uint32_t tgl)
{
	cc->tgl_up = tgl;
}
void LaserDriverDirection(Drive_t* drv, SideMV_t dr)
{
	drv->m_side = dr;
	HAL_GPIO_WritePin(drv->m_dir_port, drv->m_dir_pin, dr);
}
void LaserDriverEnable(Drive_t* drv, _Bool st)
{
	drv->m_drv_enabled = st;
	HAL_GPIO_WritePin(drv->m_en_port, drv->m_en_pin, !st);
}


_Bool LaserInit()
{
	/*AXIS X*/
	machine.axis[0].drive.m_pulse_port 		= GPIOD;
	machine.axis[0].drive.m_pulse_pin		= GPIO_PIN_11;
	machine.axis[0].drive.m_dir_port		= GPIOD;
	machine.axis[0].drive.m_dir_pin	 		= GPIO_PIN_9;
	machine.axis[0].drive.m_en_port 		= GPIOD;
	machine.axis[0].drive.m_en_pin			= GPIO_PIN_14;
	/****************************/
	machine.axis[0].sw_key.m_sw_k_port		= GPIOD;
	machine.axis[0].sw_key.m_sw_k_pin		= GPIO_PIN_6;

	/****************************/
	machine.axis[0].c_curve.counter 		= 0;
	machine.axis[0].c_curve.target_counter 	= 0;
	machine.axis[0].c_curve.tgl_up	 		= 0;
	machine.axis[0].c_curve.enabled 		= false;
	machine.axis[0].sw_key.sw_k_enabled		= true;
	/****************************/

	/*****************************************************/

	/*AXIS Y*/
	machine.axis[1].drive.m_pulse_port 		= GPIOD;
	machine.axis[1].drive.m_pulse_pin		= GPIO_PIN_13;
	machine.axis[1].drive.m_dir_port		= GPIOD;
	machine.axis[1].drive.m_dir_pin	 		= GPIO_PIN_12;
	machine.axis[1].drive.m_en_port 		= GPIOD;
	machine.axis[1].drive.m_en_pin			= GPIO_PIN_15;
	machine.axis[1].sw_key.m_sw_k_port		= GPIOD;
	machine.axis[1].sw_key.m_sw_k_pin		= GPIO_PIN_7;

	/****************************/
	machine.axis[1].c_curve.counter 		= 0;
	machine.axis[1].c_curve.target_counter 	= 0;
	machine.axis[1].c_curve.tgl_up	 		= 0;
	machine.axis[1].c_curve.enabled 		= false;
	machine.axis[1].sw_key.sw_k_enabled		= true;
	/****************************/

	/* Устанавливаем программное ограничение на размер рабочей области */
	MachineSetProgramLimit(&machine.axis[0], 0, MAX_TABLE_X);
	MachineSetProgramLimit(&machine.axis[1], 0, MAX_TABLE_Y);
//	MachineSetProgramLimit(&machine.axis[2], 0, MAX_TABLE_Z);

	HAL_TIM_Base_Start_IT(&htim7);
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&uart_dat, 1);

//	StepMoves(&machine.axis[0], Forward, 100, 20);
//	PointMoves(&machine, 100, 100, 100);

//	FATFS_Init();
	FRESULT fr1 = f_mount(&fs, "", 0);

	StartGCode(&fil, "code.txt");
//	FRESULT fr1 = f_mount(&fs, "", 0);
//	HAL_Delay(100);
//	FRESULT fr2 = f_open(&fil, "code.txt", FA_READ | FA_OPEN_EXISTING);
//	HAL_Delay(100);
//	uint8_t j = 0;
//	for (uint8_t i = 1; i < 19; i++) {
//		if (j == 2) {
//			LCD1602_Clear();
//			j = 0;
//		}
//		SD_read_line(&fil, &buffer, i);
//		LCD1602_SetCursor(j++, 0);
//		LCD1602_WriteString((char*)&buffer);
//		HAL_Delay(1000);
//		memset(&buffer, 0, sizeof(buffer));
//	}
//	//	f_puts("This is an example text to check SD Card Module with STM32 Blue Pill\n", &fil);
//	f_close(&fil);











//	while(1) {}

	return 0;
}
void LaserLoop()
{
	while(1)
	{
		if (FLAG[0])
		{
			GoHome();

			FLAG[0] = false;
		}
		if (FLAG[1])	/* Move on X*/
		{
			SideMV_t side = uart_data[2];
			if (side >= 2) side = 0;
			uint32_t step = (uart_data[3] << 8) | uart_data[4];
			uint32_t speed = uart_data[5] * 10;

			StepMoves(&machine.axis[0], side, step, speed);

			FLAG[1] = false;
		}
		if (FLAG[2])
		{
			SideMV_t side = uart_data[2];
			if (side >= 3) side = 0;
			uint32_t step = (uart_data[3] << 8) | uart_data[4];
			uint32_t speed = uart_data[5] * 10;

			StepMoves(&machine.axis[1], side, step, speed);

			FLAG[2] = false;
		}
		if (FLAG[3])
		{

		}
		if (FLAG[4])
		{

		}
		if (FLAG[5])
		{
			FLAG[5] = false;
		}
		if (FLAG[6])
		{

		}
		if (FLAG[7])
		{

		}
	}

}

void MachineCoordSet(Axis_t* ax, uint32_t var) {
	ax->mach_base_crd = var;
}
void MachineRelativeSet(Axis_t* ax, uint32_t var) {
	ax->mach_base_crd = var;
}

void SetFeedRate(float fd) {
	machine.FeedRate = fd;
	fd = 625.0 / fd;						//625=50000/80
	LaserCountCurvTgl(&machine.axis[0].c_curve, fd);
	LaserCountCurvTgl(&machine.axis[1].c_curve, fd);
//	LaserCountCurvTgl(&ax->c_curve, fd);

	return;
}
void StepMoves(Axis_t* ax, SideMV_t sd, uint32_t length, uint32_t sp)
{
	/* Если нажат концевик и при этом направление от него, или концевик не нажат то...*/
	if ((ax->sw_key.sw_k_state && (sd == Forward)) || (!ax->sw_key.sw_k_state))
	{
		/* Если мы зашли сюда при нажатом концевике, значит его требуется сбросить */
		ax->sw_key.sw_k_state = false;

		ax->drive.counter = 0;

		ax->current_side = sd;
		LaserDriverDirection(&ax->drive, sd);
		LaserDriverEnable(&ax->drive, true);
		sp = 625.0 / sp;						//625=50000/80
		LaserCountCurvTgl(&ax->c_curve, sp);
		LaserCountCurvEN(&ax->c_curve, true);

		uint32_t stp = 2 * length * 80;			// (tgl=2) * length * (imp/mm=80)

		/* Ожидаем пока не доедем до требуемой точки */
		while (ax->drive.counter < stp) {
			/* Проверка нажатия на концевик*/
			if (ax->sw_key.sw_k_state) {
				stp = 0;
				ax->drive.counter = 0;

				ContMoves(ax, !sd, 20);
				while (!ax->sw_key.sw_k_state) {}
				GlbtimDelay(500);
				ax->sw_key.sw_k_enabled			= false;
				ax->drive.counter 				= 0;
				StepMoves(ax, Forward, HOME_OFFSET, 20);
				GlbtimDelay(500);
				/* Сброс события прерывания */
				EXTI->PR 						= ax->sw_key.m_sw_k_pin;
				ax->sw_key.sw_k_enabled			= true;
				GlbtimDelay(500);

				break;
			}
//			/* Проверка на позицию внутри рабочей */
//			if (ax->current_pos_coord <= ax->limit_start_coord) {
//				LaserCountCurvEN(&ax->c_curve, false);
//				break;
//			}
//			else if (ax->current_pos_coord >= ax->limit_end_coord) {
//				LaserCountCurvEN(&ax->c_curve, false);
//				break;
//			}
		}
	}
	else {}
	LaserCountCurvEN(&ax->c_curve, false);
	LaserDriverEnable(&ax->drive, false);
}
void ContMoves(Axis_t* ax, SideMV_t sd, uint32_t sp)
{
	/* Настраиваем драйверы на нужное направление и включаем их */
	ax->current_side = sd;
	LaserDriverDirection(&ax->drive, sd);
	LaserDriverEnable(&ax->drive, true);
	/* Разрешаем воспроизводить импульсы для движения */
	sp = 625.0 / sp;						//625=50000/80
	LaserCountCurvTgl(&ax->c_curve, sp);
	LaserCountCurvEN(&ax->c_curve, true);
}
void PointMoves(Machine_t* mh, uint32_t x, uint32_t y, uint32_t sp)
{
	/* Если нажат концевик и при этом направление от него, или концевик не нажат то...*/
	if (1)
	{
		mh->axis[0].sw_key.sw_k_state = false;
		mh->axis[1].sw_key.sw_k_state = false;

		mh->axis[0].drive.counter = 0;
		mh->axis[1].drive.counter = 0;

		if (x > mh->axis[0].current_pos_coord) {
			LaserDriverDirection(&mh->axis[0].drive, Forward);
			mh->axis[0].current_side = Forward;
		}
		else {
			LaserDriverDirection(&mh->axis[0].drive, BackForward);
			mh->axis[0].current_side = BackForward;
		}

		if (y > mh->axis[1].current_pos_coord) {
			LaserDriverDirection(&mh->axis[1].drive, Forward);
			mh->axis[1].current_side = Forward;
		}
		else {
			LaserDriverDirection(&mh->axis[1].drive, BackForward);
			mh->axis[1].current_side = BackForward;
		}

		LaserDriverEnable(&mh->axis[0].drive, true);
		LaserDriverEnable(&mh->axis[1].drive, true);

		sp = 625.0 / sp;						//625=50000/80
		LaserCountCurvTgl(&mh->axis[0].c_curve, sp);
		LaserCountCurvTgl(&mh->axis[1].c_curve, sp);

		LaserCountCurvEN(&mh->axis[0].c_curve, true);
		LaserCountCurvEN(&mh->axis[1].c_curve, true);

//		uint32_t stp = 2 * length * 80;			// (tgl=2) * length * (imp/mm=80)
//		x = 2 * x * 80;
//		y = 2 * y * 80;

		_Bool flag[2] = {false, };
		/* Ожидаем пока не доедем до требуемой точки */
		while (1) {

			if ((mh->axis[0].current_pos_coord >= (x - EPS_PRECISION)) && (mh->axis[0].current_pos_coord <= (x + EPS_PRECISION))) {
				LaserCountCurvEN(&mh->axis[0].c_curve, false);
				flag[0] = true;
			}
			if ((mh->axis[1].current_pos_coord >= (y - EPS_PRECISION)) && (mh->axis[1].current_pos_coord <= (y + EPS_PRECISION))) {
				LaserCountCurvEN(&mh->axis[1].c_curve, false);
				flag[1] = true;
			}
			if (flag[0] && flag[1]) break;

			/* Концевики */
			for (uint8_t i = 0; i < 2; i++) {
				if (mh->axis[i].sw_key.sw_k_state) {
					mh->axis[i].drive.counter = 0;

					ContMoves(&mh->axis[i], !mh->axis[i].current_side, 20);
					while (!mh->axis[i].sw_key.sw_k_state) {}
					GlbtimDelay(500);
					mh->axis[i].sw_key.sw_k_enabled			= false;
					mh->axis[i].drive.counter 				= 0;
					StepMoves(&mh->axis[i], Forward, HOME_OFFSET, 20);
					GlbtimDelay(500);
					/* Сброс события прерывания */
					EXTI->PR 						= mh->axis[i].sw_key.m_sw_k_pin;
					mh->axis[i].sw_key.sw_k_enabled			= true;
					GlbtimDelay(500);

					break;
				}

				/* Проверка на позицию внутри рабочей */
				if (mh->axis[i].current_pos_coord < mh->axis[i].limit_start_coord) {
					LaserCountCurvEN(&mh->axis[i].c_curve, false);
					break;
				}
				else if (mh->axis[i].current_pos_coord > mh->axis[i].limit_end_coord) {
					LaserCountCurvEN(&mh->axis[i].c_curve, false);
					break;
				}
			}
		}
	}
	else {}

	LaserDriverEnable(&mh->axis[0].drive, false);
	LaserDriverEnable(&mh->axis[1].drive, false);


}

_Bool GoHome()
{
	/* HOME Y */
	ContMoves(&machine.axis[1], BackForward, 20);
	while (!machine.axis[1].sw_key.sw_k_state) {}
	GlbtimDelay(500);
	machine.axis[1].sw_key.sw_k_enabled			= false;
	machine.axis[1].drive.counter 				= 0;
	StepMoves(&machine.axis[1], Forward, HOME_OFFSET, 20);
	GlbtimDelay(500);
	/* Сброс события прерывания */
	EXTI->PR 									= machine.axis[1].sw_key.m_sw_k_pin;
	machine.axis[1].sw_key.sw_k_enabled			= true;
	GlbtimDelay(500);
	/* HOME X */
	ContMoves(&machine.axis[0], BackForward, 20);
	while (!machine.axis[0].sw_key.sw_k_state) {}
	GlbtimDelay(500);
	machine.axis[0].sw_key.sw_k_enabled			= false;
	machine.axis[0].drive.counter 				= 0;
	StepMoves(&machine.axis[0], Forward, HOME_OFFSET, 20);
	GlbtimDelay(500);
	/* Сброс события прерывания */
	EXTI->PR 									= machine.axis[0].sw_key.m_sw_k_pin;
	machine.axis[0].sw_key.sw_k_enabled			= true;

	LaserDriverEnable(&machine.axis[0].drive, false);
	LaserDriverEnable(&machine.axis[1].drive, false);

	LaserSW_Set(&machine.axis[0], false);
	LaserSW_Set(&machine.axis[1], false);

	MachineCoordSet(&machine.axis[0], 0);
	MachineCoordSet(&machine.axis[1], 0);

	/* Устанавливаем текущие координаты равными машинным */
	machine.axis[0].current_pos_coord = 0;
	machine.axis[1].current_pos_coord = 0;

	machine.axis[0].c_curve.current_pos = 0;
	machine.axis[1].c_curve.current_pos = 0;

	machine.axis[0].current_side = Forward;
	machine.axis[1].current_side = Forward;

	return 0;
}

void LaserSW_Set(Axis_t* ax, _Bool st)
{
	ax->sw_key.sw_k_state = st;
}

//================================================================================================
//================================================================================================


void GlbtimDelay(uint32_t us) {
	uint32_t tim_end = glb_tim.glb_time_us + us;
	while (!(tim_end <= glb_tim.glb_time_us)) {}
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
		glb_tim.glb_time_us++;
		SD_Timer1++;
		SD_Timer2++;
	}
	else if (htim->Instance == 0) {
		/* Этот таймер желательно использовать чтобы запускать функции, а также для создания и обработки очередей. */

	}

}
//================================================================================================
//================================================================================================
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
		FLAG[0] = true;
	}
	else if (GPIO_Pin == GPIO_PIN_6)		// X
	{
		if (machine.axis[0].sw_key.sw_k_enabled) {
			LaserCountCurvEN(&machine.axis[0].c_curve, false);
			LaserSW_Set(&machine.axis[0], true);
			machine.axis[0].drive.counter = 0;
		}
	}
	else if (GPIO_Pin == GPIO_PIN_7)		// Y
	{
		if (machine.axis[1].sw_key.sw_k_enabled) {
			LaserCountCurvEN(&machine.axis[1].c_curve, false);
			LaserSW_Set(&machine.axis[1], true);
			machine.axis[1].drive.counter = 0;

		}
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
	{
//		if (uart_data[0] == 0xDD)
//		{
//			if (uart_data[1] == 0x01)		// X
//			{
//				FLAG[1] = true;
//			}
//			else if (uart_data[1] == 0x02)	// Y
//			{
//				FLAG[2] = true;
//			}
//		}
		if (uart_dat != ';') {
			uart_data[uart_inx++] = uart_dat;
		}
		else if (uart_dat == ';') {
			uart_data[uart_inx++] = ';';
			FLAG[5] = true;
			uart_inx = 0;
		}

		HAL_UART_Receive_IT(&huart1, (uint8_t*)&uart_dat, 1);
	}
}


//================================================================================================
//================================================================================================
//================================================================================================

