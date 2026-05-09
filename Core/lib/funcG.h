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


#define MIN_TGL_UP    100     // Минимальная частота импульсов (макс. скорость = 50000 / MIN_TGL_UP = 500 имп/с)
#define MAX_TGL_UP    50000   // Максимальная частота (мин. скорость = 1 имп/с)



/* Функция возврата в машинный ноль (дом) */
void GoHome(_Axis_t ax);
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
