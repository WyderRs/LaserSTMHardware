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



void GC_G0(float GX, float GY, float GZ) {
//	tGSetMode(G0_Mode);
//	float sp = tTool.Settings.speed;
//	tMoveSetSpeed(MAX_SPEED);
//	tMoveGlobal(GX, GY, GZ);
//	tMoveSetSpeed(sp);

	return;
}
void GC_G1(float GX, float GY, float GZ) {
//	tGSetMode(G1_Mode);
//	if(tTool.Settings.speed > 0) tMoveGlobal(GX, GY, GZ);
	return;
}
void GC_G2(float x1, float y1, float r) {
//	tGSetMode(G2_Mode);
//	CircleMove(x1, y1, r, 0);
	return;
}
void GC_G3(float x1, float y1, float r) {
//	tGSetMode(G3_Mode);
//	CircleMove(x1, y1, r, 1);
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
//	tMoveSetSpeed(f);
	return;
}
void GC_G28(GC_Axis ax) {
	if (ax == GC_ALL_AXISES) {
//		tHome();
	}
	else if (ax == GC_X_AXIS) {
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











