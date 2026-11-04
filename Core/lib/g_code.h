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
	GC_X_AXIS = 0,
	GC_Y_AXIS,
	GC_Z_AXIS,
} GC_Axis;


/*
 * G21 - Установить единицы - миллиметры
 * G90 - Абсолютная система координат, все перемещения от 0 станка
 * G94 - Подача задается в MM/MIN
 * G01 F200.00 - Задать модальную рабочую подачу 200 мм/мин для линейных перемещений.
 * (СДЕЛАТЬ ПЕРЕХОД В РЕЖИМЫ G0 G1 G2 G3 ...)
 * M5 - остановить шпиндель
 * G00 Z15.0000 - ускоренно поднять Z
 * T1 - выбрать инструмент
 * M6 - сменить инструмент (выполнить смену) - при наличии автоматического сменщика
 * M0 - пауза программы до дейсвтия оператора
 * M03 - вкл. шпиндель
 * РЕАЛИЗОВАТЬ ВОЗМОЖНОСТЬ РАБОТЫ С ОТРИЦАТЕЛЬНЫМИ КООРДИНАТАМИ
 * */

//void GC_G21(GC_TypeSI);
//void GC_G90(GC_TypeCS);
//void GC_G94(); The feed is setting by mm/min


void GC_G28(GC_Axis);

/* Go to mode G0, G1, G2, G3 */
void GC_G0 (void);
void GC_G1 (void);
void GC_G2(float x1, float y1, float r);
void GC_G3(float x1, float y1, float r);


void GC_M3 (void);
void GC_M5 (void);
void GC_M30(void);

void GC_S (float s);
void GC_F (float s);

//void GC_Move(float GX, float GY, float GZ);

void GC_X(float x);
void GC_Y(float y);
void GC_Z(float z);

/**********************************/
void GC_LinePerformMove(void);

















#endif /* LIB_G_CODE_H_ */
