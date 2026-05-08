/*
 * g_code.h
 *
 *  Created on: Apr 30, 2026
 *      Author: makar
 */

#ifndef LIB_G_CODE_H_
#define LIB_G_CODE_H_

/*
 * GC 		- G-Code
 * GC_XX 	- XX = code
 * S - параметр для регулировки мощности лазера
 * */


#include "stm32f1xx.h"
#include <stdlib.h>
#include "funcG.h"


//typedef struct Common_param_t {
//	float X;
//	float Y;
//	float Z;
//
//	float S;
//	float F;
//
//	void (*FeedRate) (float fd);
//	void (*MovePoint) (float x, float y, float z);
//	void (*MoveHome) (float x, float y, float z);
//
//} Common_param_t;

typedef enum GC_Axis {
	GC_ALL_AXISES = 0,
	GC_X_AXIS,
	GC_Y_AXIS,
	GC_Z_AXIS,
} GC_Axis;



void GC_G0 (float GX, float GY, float GZ);
void GC_G1 (float GX, float GY, float GZ);
void GC_G2(float x1, float y1, float r);
void GC_G3(float x1, float y1, float r);
void GC_G28(GC_Axis);

void GC_M3 (void);
void GC_M5 (void);
void GC_M30(void);

void GC_S (float s);
void GC_F (float s);
























#endif /* LIB_G_CODE_H_ */
