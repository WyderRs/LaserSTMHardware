/*
 * func.c
 *
 *  Created on: May 1, 2026
 *      Author: makar
 */


#include "funcG.h"
#include "string.h"
#include "stdbool.h"

#include "Laser.h"


extern Machine_t machine;


BYTE GC_Buffer[20][40] = {{0, }, };


//void StepMoves(Axis_t* ax, SideMV_t sd, uint32_t length, uint32_t sp) {
//
//	/* Если нажат концевик и при этом направление от него, или концевик не нажат то...*/
//	if ((ax->sw_key.sw_k_state && (sd == Forward)) || (!ax->sw_key.sw_k_state))
//	{
//		/* Если мы зашли сюда при нажатом концевике, значит его требуется сбросить */
//		ax->sw_key.sw_k_state = false;
//
//		ax->drive.counter = 0;
//
//		ax->current_side = sd;
//		LaserDriverDirection(&ax->drive, sd);
//		LaserDriverEnable(&ax->drive, true);
//		sp = 625.0 / sp;						//625=50000/80
//		LaserCountCurvTgl(&ax->c_curve, sp);
//		LaserCountCurvEN(&ax->c_curve, true);
//
//		uint32_t stp = 2 * length * 80;			// (tgl=2) * length * (imp/mm=80)
//
//		/* Ожидаем пока не доедем до требуемой точки */
//		while (ax->drive.counter < stp) {
//			/* Проверка нажатия на концевик*/
//			if (ax->sw_key.sw_k_state) {
//				stp = 0;
//				ax->drive.counter = 0;
//
//				ContMoves(ax, !sd, 20);
//				while (!ax->sw_key.sw_k_state) {}
//				GlbtimDelay(500);
//				ax->sw_key.sw_k_enabled			= false;
//				ax->drive.counter 				= 0;
//				StepMoves(ax, Forward, HOME_OFFSET, 20);
//				GlbtimDelay(500);
//				/* Сброс события прерывания */
//				EXTI->PR 						= ax->sw_key.m_sw_k_pin;
//				ax->sw_key.sw_k_enabled			= true;
//				GlbtimDelay(500);
//
//				break;
//			}
////			/* Проверка на позицию внутри рабочей */
////			if (ax->current_pos_coord <= ax->limit_start_coord) {
////				LaserCountCurvEN(&ax->c_curve, false);
////				break;
////			}
////			else if (ax->current_pos_coord >= ax->limit_end_coord) {
////				LaserCountCurvEN(&ax->c_curve, false);
////				break;
////			}
//		}
//	}
//	else {}
//	LaserCountCurvEN(&ax->c_curve, false);
//	LaserDriverEnable(&ax->drive, false);
//
//}
//void ContMoves(Axis_t* ax, SideMV_t sd, uint32_t sp) {
//
//}
//void PointMoves(Machine_t* mh, uint32_t x, uint32_t y, uint32_t sp) {
//
//	/* Если нажат концевик и при этом направление от него, или концевик не нажат то...*/
//	if (1)
//	{
//		mh->axis[0].sw_key.sw_k_state = false;
//		mh->axis[1].sw_key.sw_k_state = false;
//
//		mh->axis[0].drive.counter = 0;
//		mh->axis[1].drive.counter = 0;
//
//		if (x > mh->axis[0].current_pos_coord) {
//			LaserDriverDirection(&mh->axis[0].drive, Forward);
//			mh->axis[0].current_side = Forward;
//		}
//		else {
//			LaserDriverDirection(&mh->axis[0].drive, BackForward);
//			mh->axis[0].current_side = BackForward;
//		}
//
//		if (y > mh->axis[1].current_pos_coord) {
//			LaserDriverDirection(&mh->axis[1].drive, Forward);
//			mh->axis[1].current_side = Forward;
//		}
//		else {
//			LaserDriverDirection(&mh->axis[1].drive, BackForward);
//			mh->axis[1].current_side = BackForward;
//		}
//
//		LaserDriverEnable(&mh->axis[0].drive, true);
//		LaserDriverEnable(&mh->axis[1].drive, true);
//
//		sp = 625.0 / sp;						//625=50000/80
//		LaserCountCurvTgl(&mh->axis[0].c_curve, sp);
//		LaserCountCurvTgl(&mh->axis[1].c_curve, sp);
//
//		LaserCountCurvEN(&mh->axis[0].c_curve, true);
//		LaserCountCurvEN(&mh->axis[1].c_curve, true);
//
////		uint32_t stp = 2 * length * 80;			// (tgl=2) * length * (imp/mm=80)
////		x = 2 * x * 80;
////		y = 2 * y * 80;
//
//		_Bool flag[2] = {false, };
//		/* Ожидаем пока не доедем до требуемой точки */
//		while (1) {
//
//			if ((mh->axis[0].current_pos_coord >= (x - EPS_PRECISION)) && (mh->axis[0].current_pos_coord <= (x + EPS_PRECISION))) {
//				LaserCountCurvEN(&mh->axis[0].c_curve, false);
//				flag[0] = true;
//			}
//			if ((mh->axis[1].current_pos_coord >= (y - EPS_PRECISION)) && (mh->axis[1].current_pos_coord <= (y + EPS_PRECISION))) {
//				LaserCountCurvEN(&mh->axis[1].c_curve, false);
//				flag[1] = true;
//			}
//			if (flag[0] && flag[1]) break;
//
//			for (uint8_t i = 0; i < 2; i++) {
//				if (mh->axis[i].sw_key.sw_k_state) {
//					mh->axis[i].drive.counter = 0;
//
//					ContMoves(&mh->axis[i], !mh->axis[i].current_side, 20);
//					while (!mh->axis[i].sw_key.sw_k_state) {}
//					GlbtimDelay(500);
//					mh->axis[i].sw_key.sw_k_enabled			= false;
//					mh->axis[i].drive.counter 				= 0;
//					StepMoves(&mh->axis[i], Forward, HOME_OFFSET, 20);
//					GlbtimDelay(500);
//					/* Сброс события прерывания */
//					EXTI->PR 						= mh->axis[i].sw_key.m_sw_k_pin;
//					mh->axis[i].sw_key.sw_k_enabled			= true;
//					GlbtimDelay(500);
//
//					break;
//				}
//
//				/* Проверка на позицию внутри рабочей */
//				if (mh->axis[i].current_pos_coord < mh->axis[i].limit_start_coord) {
//					LaserCountCurvEN(&mh->axis[i].c_curve, false);
//					break;
//				}
//				else if (mh->axis[i].current_pos_coord > mh->axis[i].limit_end_coord) {
//					LaserCountCurvEN(&mh->axis[i].c_curve, false);
//					break;
//				}
//			}
//
//
//		}
//	}
//	else {}
//
//	LaserDriverEnable(&mh->axis[0].drive, false);
//	LaserDriverEnable(&mh->axis[1].drive, false);
//

//}
//_Bool GoHome() {
//
//	/* HOME Y */
//	ContMoves(&machine.axis[1], BackForward, 20);
//	while (!machine.axis[1].sw_key.sw_k_state) {}
//	GlbtimDelay(500);
//	machine.axis[1].sw_key.sw_k_enabled			= false;
//	machine.axis[1].drive.counter 				= 0;
//	StepMoves(&machine.axis[1], Forward, HOME_OFFSET, 20);
//	GlbtimDelay(500);
//	/* Сброс события прерывания */
//	EXTI->PR 									= machine.axis[1].sw_key.m_sw_k_pin;
//	machine.axis[1].sw_key.sw_k_enabled			= true;
//	GlbtimDelay(500);
//	/* HOME X */
//	ContMoves(&machine.axis[0], BackForward, 20);
//	while (!machine.axis[0].sw_key.sw_k_state) {}
//	GlbtimDelay(500);
//	machine.axis[0].sw_key.sw_k_enabled			= false;
//	machine.axis[0].drive.counter 				= 0;
//	StepMoves(&machine.axis[0], Forward, HOME_OFFSET, 20);
//	GlbtimDelay(500);
//	/* Сброс события прерывания */
//	EXTI->PR 									= machine.axis[0].sw_key.m_sw_k_pin;
//	machine.axis[0].sw_key.sw_k_enabled			= true;
//
//	LaserDriverEnable(&machine.axis[0].drive, false);
//	LaserDriverEnable(&machine.axis[1].drive, false);
//
//	LaserSW_Set(&machine.axis[0], false);
//	LaserSW_Set(&machine.axis[1], false);
//
//	MachineCoordSet(&machine.axis[0], 0);
//	MachineCoordSet(&machine.axis[1], 0);
//
//	/* Устанавливаем текущие координаты равными машинным */
//	machine.axis[0].current_pos_coord = 0;
//	machine.axis[1].current_pos_coord = 0;
//
//	machine.axis[0].c_curve.current_pos = 0;
//	machine.axis[1].c_curve.current_pos = 0;
//
//	machine.axis[0].current_side = Forward;
//	machine.axis[1].current_side = Forward;
//
//	/* Устанавливаем программное ограничение на размер рабочей области */
//
//	MachineSetProgramLimit(&machine.axis[0], 0, 170);
//	MachineSetProgramLimit(&machine.axis[1], 0, 130);
//
//
//	return 0;

//}


void StartGCode(FIL* fp, const TCHAR* path) {

	FRESULT fr2 = f_open(fp, path, FA_READ | FA_OPEN_EXISTING);

	HAL_Delay(100);	// Удалить

	uint16_t line = 0;
	_Bool flag_end = false;
	while (!flag_end) {
		flag_end = SD_read_line(fp, &GC_Buffer[line], line);
		line++;
	}
	uint8_t tt = line;
	line = 0;
	while(line != tt) {
//		{
//			LCD1602_SetCursor(0, 0);
//			LCD1602_WriteString((char*)&GC_Buffer[line]);
//		}

		G_CommandString(&GC_Buffer[line]);
//		{
//			LCD1602_SetCursor(0, 0);
//			LCD1602_WriteString("                ");
//		}
//		memset(GC_Buffer, 0, strlen(GC_Buffer));
		line++;
	}

	f_close(&fp);
	return;
}





