/*
 * func.h
 *
 *  Created on: May 1, 2026
 *      Author: makar
 */

#ifndef LIB_FUNCG_H_
#define LIB_FUNCG_H_


#include "stm32f1xx.h"
#include "SD.h"
#include "machine.h"

typedef enum _Axis_t {
	_ALL_AXISES = 0,
	_X_AXIS,
	_Y_AXIS,
	_Z_AXIS,
} _Axis_t;



//void StepMoves(Axis_t* ax, SideMV_t sd, uint32_t length, uint32_t sp);
//void ContMoves(Axis_t* ax, SideMV_t sd, uint32_t sp);
//void PointMoves(Machine_t* mh, uint32_t x, uint32_t y, uint32_t sp);
//_Bool GoHome();

/* Функция чтения и отработки файла из внешнего устройства памяти */
void StartGCode(const TCHAR* path);
/* Прямое движение на величину числа шагов */
void StepMoves(Axis_t* ax, SideMV_t sd, uint32_t length, uint32_t sp);
/* Движение к точке (x, y, z) */
void PointMoves(Machine_t* mh, float x, float y, uint32_t sp);
/* Движение по дуге */
void CircleMove(float x1, float y1, float r, _Bool dir);
/* Непрерывное движение */
void ContMoves(Axis_t* ax, SideMV_t sd, uint32_t sp);
/* Установка скорости движения (рабочая) */
void SetFeedRate(float fd);
/* Функция для разбора строки и поиска G кода */
void G_CommandString(unsigned char*);

#endif /* LIB_FUNCG_H_ */
