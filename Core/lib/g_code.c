/*
 * g_code.c
 *
 *  Created on: Apr 30, 2026
 *      Author: makar
 */


#include "g_code.h"
#include <stdbool.h>
#include <string.h>

extern Tool_Typedef tTool;

float target_x, target_y, target_z;
_Bool flag_x, flag_y, flag_z;

void GC_G0(void) {
	tToolSetGMode(_G0_mode);
	return;
}
void GC_G1(void) {
	tToolSetGMode(_G1_mode);
	return;
}
void GC_G2(float x1, float y1, float r) {
//	tToolSetGMode(_G2_mode);
	return;
}
void GC_G3(float x1, float y1, float r) {
//	tToolSetGMode(_G3_mode);
	return;
}
void GC_M3(void) {
//	MachineLaserState(true);
	return;
}
void GC_M5(void) {
//	MachineLaserState(false);
	return;
}
void GC_M30(void) {
//	tAxisEN(&tTool.head.tAxis[0], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[1], OFF, OFF);
//	tAxisEN(&tTool.head.tAxis[2], OFF, OFF);
	return;
}
void GC_S(float s) {
	return;
}
void GC_F(float f) {
	tToolFeedrate(f);
	return;
}
void GC_G28(GC_Axis ax) {
	if (ax == GC_X_AXIS) {
//		tHomeAxis(&tTool.head.tAxis[0]);
	}
	else if (ax == GC_Y_AXIS) {
//		tHomeAxis(&tTool.head.tAxis[1]);
	}
	else if (ax == GC_Z_AXIS) {
//		tHomeAxis(&tTool.head.tAxis[2]);
	}
	return;
}
void GC_G31(void) {
//	TouchSensor();
	return;
}
//void GC_Move(float GX, float GY, float GZ) {
//	tMove(GX, GY, GZ);
//	return;
//}

void GC_X(float x) {
	target_x = x;
	flag_x = true;
}
void GC_Y(float y) {
	target_y = y;
	flag_y = true;
}
void GC_Z(float z) {
	target_z = z;
	flag_z = true;
}
void GC_LinePerformMove(void) {
	if (!flag_x) target_x = tTool.curr_pos[0];
	if (!flag_y) target_y = tTool.curr_pos[1];
	if (!flag_z) target_z = tTool.curr_pos[2];

	tToolMove(target_x, target_y, target_z);
}






