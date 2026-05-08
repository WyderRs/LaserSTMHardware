/*
 * g_code.c
 *
 *  Created on: Apr 30, 2026
 *      Author: makar
 */


#include "g_code.h"
#include <stdbool.h>
#include <string.h>
#include "machine.h"


extern Machine_t machine;
Common_param_t comParam;

void GC_G0(float GX, float GY, float GZ) {
	PointMoves(&machine, GX, GY, machine.FeedRate); // + GZ machine.FeedRate
//	Common_param.MovePoint(GX, GY, GZ);
	return;
}
void GC_G1(float GX, float GY, float GZ) {

//	comParam.MovePoint(GX, GY, GZ);
	return;
}
void GC_G2(float x1, float y1, float r) {
	CircleMove(x1, y1, r, 0);
	return;
}
void GC_G3(float x1, float y1, float r) {
	CircleMove(x1, y1, r, 1);
	return;
}
void GC_M3(void) {
	MachineLaserState(true);
	return;
}
void GC_M5(void) {
	MachineLaserState(false);
	return;
}
void GC_M30(void) {
	ModuleDriverEnable(&machine.axis[0].drive, false);
	ModuleDriverEnable(&machine.axis[1].drive, false);

	return;
}
void GC_S(float s) {
	return;
}
void GC_F(float f) {
	SetFeedRate(f);
//	Common_param.FeedRate(f);
	return;
}
void GC_G28(GC_Axis ax) {
	if (ax == GC_ALL_AXISES) {
		/* HOME Z */
//		ContMoves(&machine.axis[2], BackForward, 20);
//		while (!machine.axis[2].sw_key.sw_k_state) {}
//		GlbtimDelay(500);
//		machine.axis[2].sw_key.sw_k_enabled			= false;
//		machine.axis[2].drive.counter 				= 0;
//		StepMoves(&machine.axis[2], Forward, HOME_OFFSET, 20);
//		GlbtimDelay(500);
//		/* Сброс события прерывания */
//		EXTI->PR 									= machine.axis[2].sw_key.m_sw_k_pin;
//		machine.axis[2].sw_key.sw_k_enabled			= true;
//		GlbtimDelay(500);

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
		GlbtimDelay(500);
		/*****************/
		ModuleDriverEnable(&machine.axis[0].drive, false);
		ModuleDriverEnable(&machine.axis[1].drive, false);
//		ModuleDriverEnable(&machine.axis[2].drive, false);

		Machine_SW_Set(&machine.axis[0], false);
		Machine_SW_Set(&machine.axis[1], false);
//		LaserSW_Set(&machine.axis[2], false);

		MachineCoordSet(&machine.axis[0], 0);
		MachineCoordSet(&machine.axis[1], 0);
//		MachineCoordSet(&machine.axis[2], 0);

		/* Устанавливаем текущие координаты равными машинным */
		machine.axis[0].current_pos_coord = 0;
		machine.axis[1].current_pos_coord = 0;
//		machine.axis[2].current_pos_coord = 0;

		machine.axis[0].c_curve.current_pos = 0;
		machine.axis[1].c_curve.current_pos = 0;
//		machine.axis[2].c_curve.current_pos = 0;

		machine.axis[0].current_side = Forward;
		machine.axis[1].current_side = Forward;
//		machine.axis[2].current_side = Forward;

	}
	else if (ax == GC_X_AXIS) {
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
		GlbtimDelay(500);
		/*****************/
		ModuleDriverEnable(&machine.axis[0].drive, false);
		Machine_SW_Set(&machine.axis[0], false);

		MachineCoordSet(&machine.axis[0], 0);
		/* Устанавливаем текущие координаты равными машинным */
		machine.axis[0].current_pos_coord = 0;
		machine.axis[0].c_curve.current_pos = 0;
		machine.axis[0].current_side = Forward;
	}
	else if (ax == GC_Y_AXIS) {
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
		/*****************/
		ModuleDriverEnable(&machine.axis[1].drive, false);
		Machine_SW_Set(&machine.axis[1], false);
		MachineCoordSet(&machine.axis[1], 0);
		/* Устанавливаем текущие координаты равными машинным */
		machine.axis[1].current_pos_coord = 0;
		machine.axis[1].c_curve.current_pos = 0;
		machine.axis[1].current_side = Forward;
	}
	else if (ax == GC_Z_AXIS) {
		/* HOME Z */
//		ContMoves(&machine.axis[2], BackForward, 20);
//		while (!machine.axis[2].sw_key.sw_k_state) {}
//		GlbtimDelay(500);
//		machine.axis[2].sw_key.sw_k_enabled			= false;
//		machine.axis[2].drive.counter 				= 0;
//		StepMoves(&machine.axis[2], Forward, HOME_OFFSET, 20);
//		GlbtimDelay(500);
//		/* Сброс события прерывания */
//		EXTI->PR 									= machine.axis[2].sw_key.m_sw_k_pin;
//		machine.axis[2].sw_key.sw_k_enabled			= true;
//		GlbtimDelay(500);
		/*****************/
//		ModuleDriverEnable(&machine.axis[2].drive, false);
//		Machine_SW_Set(&machine.axis[2], false);
//		MachineCoordSet(&machine.axis[2], 0);
		/* Устанавливаем текущие координаты равными машинным */
//		machine.axis[2].current_pos_coord = 0;
//		machine.axis[2].c_curve.current_pos = 0;
//		machine.axis[2].current_side = Forward;
	}
	return;
}












