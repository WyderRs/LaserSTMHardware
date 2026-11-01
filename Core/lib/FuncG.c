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
/* НАДО ПЕРЕПИСАТЬ ТАК, ЧТОБЫ ФОРМИРОВАЛСЯ МАССИВ ИЗ ПОРЯДКА КОМАНДА
 * БУДЕТ МНОГО ЭЛЕМЕНТОВ В СПИСКЕ, НО ТАК БУДЕТ ПРОЩЕ СТРОИТЬ ИХ ПОРЯДОК И РАБОТУ */
void StartGCodeStorage(unsigned char* data_storage) {

	uint32_t num_ch = strlen((const char*)data_storage);
	uint16_t line = 0;
	uint8_t	out_data[1000][50] = {0, };
	uint16_t cnt_byte = 0;
	uint16_t cnt_line = 0;

	while(cnt_byte != num_ch) {
		out_data[line][cnt_line] = data_storage[cnt_byte];
		if (data_storage[cnt_byte] == ';') {
			line++;
			cnt_byte++;
			cnt_line = 0;
		}
		else {
			cnt_byte++;
			cnt_line++;
		}
	}
	for(uint16_t i = 0; i < line; i++) {
		G_CommandString(out_data[i]);
	}
	return;

}

void G_CommandString(unsigned char* g_ch) {

	uint32_t num_ch = strlen((const char*)g_ch);

	for (uint32_t i = 0; i < num_ch;) {
		/* Rule */
		if (g_ch[i] == ' ') {i++; continue;}		/* Если находим пробел, то пропускаем его 		*/
		if (g_ch[i] == ';') break;					/* Если находим коментарий, то завершаем строку */

		/* Сначала команды с большим числом символов */
		/* M30 */
		if ((g_ch[i] == 'M') && (g_ch[i + 1] == '3') && (g_ch[i + 2] == '0')) {
			i += 3;
			GC_M30();
			break;
		}
		/* M3 */
		if ((g_ch[i] == 'M') && (g_ch[i + 1] == '3')) {
			i += 2;
			GC_M3();
		}
		/* M5 */
		if ((g_ch[i] == 'M') && (g_ch[i + 1] == '5')) {
			i += 2;
			GC_M5();
		}
		/* G28 */
		if ((g_ch[i] == 'G') && (g_ch[i + 1] == '2') && (g_ch[i + 2] == '8')) {
			i += 3;
			if (i != num_ch) {
				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					if (g_ch[u] == ';') {
						GC_G28(GC_ALL_AXISES);
						break;
					}
					if ((g_ch[u] == 'Z') && (g_ch[u + 1] == '0')) {
						GC_G28(GC_Z_AXIS);
						u += 2;
					}
					if ((g_ch[u] == 'Y') && (g_ch[u + 1] == '0')) {
						GC_G28(GC_Y_AXIS);
						u += 2;
					}
					if ((g_ch[i] == 'X') && (g_ch[u + 1] == '0')) {
						GC_G28(GC_X_AXIS);
						u += 2;
					}
					if (u == num_ch) {
//						GC_G28(GC_ALL_AXISES);
					}
					i = u;
				}
			}
			else if (i == num_ch) {
				GC_G28(GC_ALL_AXISES);
			}
		}

		/* G0 */
		if (((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '0')) ||
				((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && ((g_ch[i + 2] < '0') && (g_ch[i + 2] > '9') ))) {

			if (((g_ch[i] == 'G') && (g_ch[i + 1] == '0'))) i += 2;
			else i += 3;

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
						/* X */
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
						/* Y */
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
						/* Z */
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
				GC_G0(t_x, t_y, t_z);
			}
			continue;
		}
		/* G1 */
		if (((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '1')) ||
				((g_ch[i] == 'G') && (g_ch[i + 1] == '1')) && ((g_ch[i + 2] < '0') && (g_ch[i + 2] > '9'))) {
			if (((g_ch[i] == 'G') && (g_ch[i + 1] == '1'))) i += 2;
			else i += 3;

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
						/* X */
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
						/* Y */
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
						/* Z */
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
//				t_feed 	= (float)atof((const char*)feed);
//				GC_F(t_feed);
				GC_G1(t_x, t_y, t_z);
			}
			continue;
		}
		/* G2 */
		if (((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '2')) ||
				((g_ch[i] == 'G') && (g_ch[i + 1] == '2'))) {
			if (((g_ch[i] == 'G') && (g_ch[i + 1] == '2')) && ((g_ch[i + 2] < '0') && (g_ch[i + 2] > '9'))) i += 2;
			else i += 3;

			if (i != num_ch) {
				float t_x, t_y, t_r 		= 0.0;
				unsigned char str_num_x[20] = {0, };
				unsigned char str_num_y[20] = {0, };
				unsigned char str_num_r[20] = {0, };

				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					else if (g_ch[u] == ';') {
						break;
					}
					else {
						/* X */
						if ((g_ch[u] == 'X') || (g_ch[u] == 'x')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
									str_num_x[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
						/* Y */
						if ((g_ch[u] == 'Y') || (g_ch[u] == 'y')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
									str_num_y[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
						/* R */
						if ((g_ch[u] == 'R') || (g_ch[u] == 'r')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
									str_num_r[str_num_cnt] = g_ch[u];
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
				t_r = (float)atof((const char*)str_num_r);
				GC_G2(t_x, t_y, t_r);
			}
			continue;
		}
		/* G3 */
		if (((g_ch[i] == 'G') && (g_ch[i + 1] == '0') && (g_ch[i + 2] == '3')) ||
				((g_ch[i] == 'G') && (g_ch[i + 1] == '3'))) {
			if (((g_ch[i] == 'G') && (g_ch[i + 1] == '3')) && ((g_ch[i + 2] < '0') && (g_ch[i + 2] > '9'))) i += 2;
			else i += 3;

			if (i != num_ch) {
				float t_x, t_y, t_r 		= 0.0;
				unsigned char str_num_x[20] = {0, };
				unsigned char str_num_y[20] = {0, };
				unsigned char str_num_r[20] = {0, };

				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					else if (g_ch[u] == ';') {
						break;
					}
					else {
						/* X */
						if ((g_ch[u] == 'X') || (g_ch[u] == 'x')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
									str_num_x[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
						/* Y */
						if ((g_ch[u] == 'Y') || (g_ch[u] == 'y')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
									str_num_y[str_num_cnt] = g_ch[u];
									str_num_cnt++;
									u++;
								}
								else break;
							}
						}
						/* R */
						if ((g_ch[u] == 'R') || (g_ch[u] == 'r')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
									str_num_r[str_num_cnt] = g_ch[u];
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
				t_r = (float)atof((const char*)str_num_r);
				GC_G3(t_x, t_y, t_r);
			}
			continue;
		}
		/* F */
		if (g_ch[i] == 'F') {
			float num_f = 0.0;
			i += 1;
			if (i != num_ch) {
				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					else if (g_ch[u] == ';') {
						break;
					}
					else {
						uint8_t str_num_cnt = 0;
						unsigned char str_num[20] = {0, };
						while(1) {
							if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
								str_num[str_num_cnt] = g_ch[u];
								str_num_cnt++;
								i++;
							}
							else
							{
								break;
							}
							u++;
						}
						num_f = (float)atof((const char*)str_num);
					}
				}
				GC_F(num_f);
			}

		}

	}
	return;
}















