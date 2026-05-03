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
#include "t_config.h"


//void StepMoves(Axis_t* ax, SideMV_t sd, uint32_t length, uint32_t sp);
//void ContMoves(Axis_t* ax, SideMV_t sd, uint32_t sp);
//void PointMoves(Machine_t* mh, uint32_t x, uint32_t y, uint32_t sp);
//_Bool GoHome();

void StartGCode(FIL* fp, const TCHAR* path);






#endif /* LIB_FUNCG_H_ */
