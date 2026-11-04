/*
 * G_Code.c
 *
 *  Created on: 8 окт. 2026 г.
 *      Author: makar
 */

#include "FuncG.h"


extern FATFS fs;
extern FIL fil;


BYTE GC_Buffer[100][100] = {{0, }, };


void StartGCodeSD(const TCHAR* path) {

	FRESULT state = f_open(&fil, path, FA_READ | FA_OPEN_EXISTING);
	if (state != FR_OK) return;
	HAL_Delay(100);	// Удалить

	uint16_t line = 0;
	_Bool flag_end = false;
	while (!flag_end) {
		flag_end = SD_read_line(&fil, &GC_Buffer[line], line);
		line++;
	}
	uint8_t tt = line;
	line = 0;
	while(line != tt) {
//		{
//			LCD1602_SetCursor(0, 0);
//			LCD1602_WriteString((char*)&GC_Buffer[line]);
//		}

		G_CommandString(GC_Buffer[line]);
//		{
//			LCD1602_SetCursor(0, 0);
//			LCD1602_WriteString("                ");
//		}
//		memset(GC_Buffer, 0, strlen(GC_Buffer));
		line++;
	}

	f_close(&fil);
	return;
}
/* Processing from microcontroller`s storage */
void StartGCodeStorage(uint8_t data_storage[][50], uint16_t lines_cnt) {

	for(uint16_t i = 0; i < lines_cnt; i++) {
		G_CommandString(data_storage[i]);
	}
	return;

}

void G_CommandString(unsigned char* g_ch) {

	struct flags {
		_Bool	M30;	_Bool	M3;
		_Bool	M5; 	_Bool	G28_X;
		_Bool 	G28_Y;	_Bool	G28_Z;
		_Bool	G0;		_Bool	G1;
		_Bool	G2;		_Bool	G3;
		_Bool	X;		_Bool	Y;
		_Bool	Z;		_Bool	F;
	} flags = {false, };

	float n_x = 0, n_y = 0, n_z = 0;
	float n_feedrate = 0;

	uint32_t num_ch = g_ch[0];

	for (uint32_t i = 1; i < num_ch;) {
		/* Rule */
		if (g_ch[i] == ' ') {i++; continue;}		/* Если находим пробел, то пропускаем его 		*/

		/* M30 */
		if ((g_ch[i] == 'M') && (g_ch[i + 1] == '3') && (g_ch[i + 2] == '0')) {
			i += 3;
			flags.M30 = true;
		}
		/* M3 */
		if (((g_ch[i] == 'M') && (g_ch[i + 1] == '3')) ||
				((g_ch[i] == 'M') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '3') )) {

			if (((g_ch[i] == 'M') && (g_ch[i + 1] == '3'))) i += 2;
			else i += 3;

			flags.M3 = true;
		}
		/* M5 */
		if (((g_ch[i] == 'M') && (g_ch[i + 1] == '5')) ||
				((g_ch[i] == 'M') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '5') )) {

			if (((g_ch[i] == 'M') && (g_ch[i + 1] == '5'))) i += 2;
			else i += 3;

			flags.M5 = true;
		}
		/* G28 */
		if ((g_ch[i] == 'G') && (g_ch[i + 1] == '2') && (g_ch[i + 2] == '8')) {
			i += 3;
			if (i != num_ch) {
				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					if ((g_ch[u] == 'Z') && (g_ch[u + 1] == '0')) {
						flags.G28_Z = true;
						u += 2;
					}
					if ((g_ch[u] == 'Y') && (g_ch[u + 1] == '0')) {
						flags.G28_Y = true;
						u += 2;
					}
					if ((g_ch[i] == 'X') && (g_ch[u + 1] == '0')) {
						flags.G28_X = true;
						u += 2;
					}
//					if (u == num_ch) {
//						flags.G28_X = true;
//						flags.G28_Y = true;
//						flags.G28_Z = true;
//					}
					i = u;
				}
			}
			else if (i == num_ch) {
				flags.G28_X = true;
				flags.G28_Y = true;
				flags.G28_Z = true;
			}
		}
		/* G0 */
		if (((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '0')) ||
				((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && ((g_ch[i + 2] < '0') && (g_ch[i + 2] > '9') ))) {

			if (((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '0'))) i += 3;
			else i += 2;

			flags.G0 = true;

		}
		/* G1 */
		if (((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '1')) ||
				((g_ch[i] == 'G') && (g_ch[i + 1] == '1') && ((g_ch[i + 2] < '0') && (g_ch[i + 2] > '9')))) {

			if (((g_ch[i] == 'G') && (g_ch[i + 1] == '1'))) i += 2;
			else i += 3;

			flags.G1 = true;
		}
		/* G2 */
		if (((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '2')) ||
				((g_ch[i] == 'G') && (g_ch[i + 1] == '2'))) {

			if (((g_ch[i] == 'G') && (g_ch[i + 1] == '2')) && ((g_ch[i + 2] < '0') && (g_ch[i + 2] > '9'))) i += 2;
			else i += 3;

			flags.G2 = true;
		}
		/* G3 */
		if (((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '3')) ||
				((g_ch[i] == 'G') && (g_ch[i + 1] == '3'))) {

			if (((g_ch[i] == 'G') && (g_ch[i + 1] == '3')) && ((g_ch[i + 2] < '0') && (g_ch[i + 2] > '9'))) i += 2;
			else i += 3;

			flags.G3 = true;
		}
		/* F */
		if ((g_ch[i] == 'F') || (g_ch[i] == 'f')) {
			i += 1;
			if (i != num_ch) {
				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					else {
						uint8_t str_num_cnt = 0;
						unsigned char str_num[20] = {0, };
						while(1) {
							if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
								str_num[str_num_cnt] = g_ch[u];
								str_num_cnt++;
								i++;
							}
							else break;
							u++;
						}
						n_feedrate = (float)atof((const char*)str_num);
						break;
					}
				}
				flags.F = true;
			}
		}
		/* X */
		if ((g_ch[i] == 'X') || (g_ch[i] == 'x')) {
			i += 1;
			if (i != num_ch) {
				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					else {
						uint8_t str_num_cnt = 0;
						unsigned char str_num[20] = {0, };
						while(1) {
							if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
								str_num[str_num_cnt] = g_ch[u];
								str_num_cnt++;
								i++;
							}
							else break;
							u++;
						}
						n_x = (float)atof((const char*)str_num);		// strtod - надо бы на нее заменить
						break;
					}
				}
				flags.X = true;
			}
		}
		/* Y */
		if ((g_ch[i] == 'Y') || (g_ch[i] == 'y')) {
			i += 1;
			if (i != num_ch) {
				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					else {
						uint8_t str_num_cnt = 0;
						unsigned char str_num[20] = {0, };
						while(1) {
							if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
								str_num[str_num_cnt] = g_ch[u];
								str_num_cnt++;
								i++;
							}
							else break;
							u++;
						}
						n_y = (float)atof((const char*)str_num);		// strtod - надо бы на нее заменить
						break;
					}
				}
			}
			flags.Y = true;
		}
		/* Z */
		if ((g_ch[i] == 'Z') || (g_ch[i] == 'z')) {
			i += 1;
			if (i != num_ch) {
				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					else {
						uint8_t str_num_cnt = 0;
						unsigned char str_num[20] = {0, };
						while(1) {
							if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
								str_num[str_num_cnt] = g_ch[u];
								str_num_cnt++;
								i++;
							}
							else break;
							u++;
						}
						n_z = (float)atof((const char*)str_num);		// strtod - надо бы на нее заменить
						break;
					}
				}
			}
			flags.Z = true;
		}
	}
	if (flags.M30) GC_M30();
	if (flags.M3) GC_M3();
	if (flags.M5) GC_M5();
	if (flags.G28_Z) GC_G28(GC_Z_AXIS);
	if (flags.G28_Y) GC_G28(GC_Y_AXIS);
	if (flags.G28_X)GC_G28(GC_X_AXIS);
	if (flags.G0) GC_G0();
	if (flags.G1) GC_G1();
//	if (flags.G2) GC_G2();
//	if (flags.G3) GC_G3();
	if (flags.F) GC_F(n_feedrate);
	if (flags.X) GC_X(n_x);
	if (flags.Y) GC_Y(n_y);
	if (flags.Z) GC_Z(n_z);

	GC_LinePerformMove();
	return;
}



/*

 if (i != num_ch) {
				float t_x, t_y, t_z 		= 0.0;
				unsigned char str_num_x[20] = {0, };
				unsigned char str_num_y[20] = {0, };
				unsigned char str_num_z[20] = {0, };

				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					else if (g_ch[u] == ';') {
						break;
					}
					else {
						// X
						if ((g_ch[u] == 'X') || (g_ch[u] == 'x')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.') || (g_ch[u] == '-')) {
									str_num_x[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
						// Y
						if ((g_ch[u] == 'Y') || (g_ch[u] == 'y')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.') || (g_ch[u] == '-')) {
									str_num_y[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
						// Z
						if ((g_ch[u] == 'Z') || (g_ch[u] == 'z')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.') || (g_ch[u] == '-')) {
									str_num_z[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
					}
					i = u;
				}
				t_x = (float)atof((const char*)str_num_x);
				t_y = (float)atof((const char*)str_num_y);
				t_z = (float)atof((const char*)str_num_z);

			}
 */


/*


			if (i != num_ch) {
				float t_x = 0.0, t_y = 0.0, t_z = 0.0, t_feed = 0.0;
				unsigned char str_num_x[20] = {0, };
				unsigned char str_num_y[20] = {0, };
				unsigned char str_num_z[20] = {0, };
				unsigned char feed[10] 		= {0, };

				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					else if ((g_ch[u] == ';') || (g_ch[u] == '\n')) {
						break;
					}
					else {
						// X
						if ((g_ch[u] == 'X') || (g_ch[u] == 'x')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.') || (g_ch[u] == '-')) {
									str_num_x[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
						// Y
						if ((g_ch[u] == 'Y') || (g_ch[u] == 'y')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.') || (g_ch[u] == '-')) {
									str_num_y[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
						// Z
						if ((g_ch[u] == 'Z') || (g_ch[u] == 'z')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.') || (g_ch[u] == '-')) {
									str_num_z[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
						else if ((g_ch[u] == 'F')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
									feed[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
					}
					i = u;
				}
				t_x 	= (float)atof((const char*)str_num_x);
				t_y 	= (float)atof((const char*)str_num_y);
				t_z 	= (float)atof((const char*)str_num_z);
				t_feed 	= (float)atof((const char*)feed);
				GC_F(t_feed);


*/







