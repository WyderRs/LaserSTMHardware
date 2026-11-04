/*
 * G_Code.h
 *
 *  Created on: 8 окт. 2026 г.
 *      Author: makar
 */

#ifndef LIB_FUNCG_H_
#define LIB_FUNCG_H_


#include <string.h>
#include <stdbool.h>
#include "SD.h"
#include "g_code.h"
#include "tableTool.h"






void StartGCodeSD(const TCHAR* path);
void StartGCodeStorage(uint8_t data_storage[][50], uint16_t lines_cnt);
void G_CommandString(unsigned char* g_ch);


















#endif /* LIB_FUNCG_H_ */
