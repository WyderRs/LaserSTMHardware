/*
 * g_code.c
 *
 *  Created on: Apr 30, 2026
 *      Author: makar
 */


#include "g_code.h"
#include <stdbool.h>
#include <string.h>
#include "Laser.h"


extern Machine_t machine;


void GC_G0(float GX, float GY, float GZ) {
	PointMoves(&machine, GX, GY, machine.FeedRate); // + GZ machine.FeedRate
//	Common_param.MovePoint(GX, GY, GZ);
	return;
}
void GC_G1(float GX, float GY, float GZ) {

	Common_param.MovePoint(GX, GY, GZ);
	return;
}
void GC_G2(void) {
	return;
}
void GC_G3(void) {
	return;
}
void GC_M3(void) {
	return;
}
void GC_M5(void) {
	return;
}
void GC_M30(void) {
	LaserDriverEnable(&machine.axis[0].drive, false);
	LaserDriverEnable(&machine.axis[1].drive, false);

	return;
}
void GC_S(float s) {
	return;
}
void GC_F(float f) {
	SetFeedRate(f);
//	Common_param.FeedRate(f);
	return;
}
void GC_G28(GC_Axis ax) {
	if (ax == GC_ALL_AXISES) {
		/* HOME Z */
//		ContMoves(&machine.axis[2], BackForward, 20);
//		while (!machine.axis[2].sw_key.sw_k_state) {}
//		GlbtimDelay(500);
//		machine.axis[2].sw_key.sw_k_enabled			= false;
//		machine.axis[2].drive.counter 				= 0;
//		StepMoves(&machine.axis[2], Forward, HOME_OFFSET, 20);
//		GlbtimDelay(500);
//		/* Сброс события прерывания */
//		EXTI->PR 									= machine.axis[2].sw_key.m_sw_k_pin;
//		machine.axis[2].sw_key.sw_k_enabled			= true;
//		GlbtimDelay(500);

		/* HOME Y */
		ContMoves(&machine.axis[1], BackForward, 20);
		while (!machine.axis[1].sw_key.sw_k_state) {}
		GlbtimDelay(500);
		machine.axis[1].sw_key.sw_k_enabled			= false;
		machine.axis[1].drive.counter 				= 0;
		StepMoves(&machine.axis[1], Forward, HOME_OFFSET, 20);
		GlbtimDelay(500);
		/* Сброс события прерывания */
		EXTI->PR 									= machine.axis[1].sw_key.m_sw_k_pin;
		machine.axis[1].sw_key.sw_k_enabled			= true;
		GlbtimDelay(500);

		/* HOME X */
		ContMoves(&machine.axis[0], BackForward, 20);
		while (!machine.axis[0].sw_key.sw_k_state) {}
		GlbtimDelay(500);
		machine.axis[0].sw_key.sw_k_enabled			= false;
		machine.axis[0].drive.counter 				= 0;
		StepMoves(&machine.axis[0], Forward, HOME_OFFSET, 20);
		GlbtimDelay(500);
		/* Сброс события прерывания */
		EXTI->PR 									= machine.axis[0].sw_key.m_sw_k_pin;
		machine.axis[0].sw_key.sw_k_enabled			= true;
		GlbtimDelay(500);
		/*****************/
		LaserDriverEnable(&machine.axis[0].drive, false);
		LaserDriverEnable(&machine.axis[1].drive, false);
//		LaserDriverEnable(&machine.axis[2].drive, false);

		LaserSW_Set(&machine.axis[0], false);
		LaserSW_Set(&machine.axis[1], false);
//		LaserSW_Set(&machine.axis[2], false);

		MachineCoordSet(&machine.axis[0], 0);
		MachineCoordSet(&machine.axis[1], 0);
//		MachineCoordSet(&machine.axis[2], 0);

		/* Устанавливаем текущие координаты равными машинным */
		machine.axis[0].current_pos_coord = 0;
		machine.axis[1].current_pos_coord = 0;
//		machine.axis[2].current_pos_coord = 0;

		machine.axis[0].c_curve.current_pos = 0;
		machine.axis[1].c_curve.current_pos = 0;
//		machine.axis[2].c_curve.current_pos = 0;

		machine.axis[0].current_side = Forward;
		machine.axis[1].current_side = Forward;
//		machine.axis[2].current_side = Forward;

	}
	else if (ax == GC_X_AXIS) {
		/* HOME X */
		ContMoves(&machine.axis[0], BackForward, 20);
		while (!machine.axis[0].sw_key.sw_k_state) {}
		GlbtimDelay(500);
		machine.axis[0].sw_key.sw_k_enabled			= false;
		machine.axis[0].drive.counter 				= 0;
		StepMoves(&machine.axis[0], Forward, HOME_OFFSET, 20);
		GlbtimDelay(500);
		/* Сброс события прерывания */
		EXTI->PR 									= machine.axis[0].sw_key.m_sw_k_pin;
		machine.axis[0].sw_key.sw_k_enabled			= true;
		GlbtimDelay(500);
		/*****************/
		LaserDriverEnable(&machine.axis[0].drive, false);
		LaserSW_Set(&machine.axis[0], false);

		MachineCoordSet(&machine.axis[0], 0);
		/* Устанавливаем текущие координаты равными машинным */
		machine.axis[0].current_pos_coord = 0;
		machine.axis[0].c_curve.current_pos = 0;
		machine.axis[0].current_side = Forward;
	}
	else if (ax == GC_Y_AXIS) {
		/* HOME Y */
		ContMoves(&machine.axis[1], BackForward, 20);
		while (!machine.axis[1].sw_key.sw_k_state) {}
		GlbtimDelay(500);
		machine.axis[1].sw_key.sw_k_enabled			= false;
		machine.axis[1].drive.counter 				= 0;
		StepMoves(&machine.axis[1], Forward, HOME_OFFSET, 20);
		GlbtimDelay(500);
		/* Сброс события прерывания */
		EXTI->PR 									= machine.axis[1].sw_key.m_sw_k_pin;
		machine.axis[1].sw_key.sw_k_enabled			= true;
		GlbtimDelay(500);
		/*****************/
		LaserDriverEnable(&machine.axis[1].drive, false);
		LaserSW_Set(&machine.axis[1], false);
		MachineCoordSet(&machine.axis[1], 0);
		/* Устанавливаем текущие координаты равными машинным */
		machine.axis[1].current_pos_coord = 0;
		machine.axis[1].c_curve.current_pos = 0;
		machine.axis[1].current_side = Forward;
	}
	else if (ax == GC_Z_AXIS) {
		/* HOME Z */
//		ContMoves(&machine.axis[2], BackForward, 20);
//		while (!machine.axis[2].sw_key.sw_k_state) {}
//		GlbtimDelay(500);
//		machine.axis[2].sw_key.sw_k_enabled			= false;
//		machine.axis[2].drive.counter 				= 0;
//		StepMoves(&machine.axis[2], Forward, HOME_OFFSET, 20);
//		GlbtimDelay(500);
//		/* Сброс события прерывания */
//		EXTI->PR 									= machine.axis[2].sw_key.m_sw_k_pin;
//		machine.axis[2].sw_key.sw_k_enabled			= true;
//		GlbtimDelay(500);
		/*****************/
//		LaserDriverEnable(&machine.axis[2].drive, false);
//		LaserSW_Set(&machine.axis[2], false);
//		MachineCoordSet(&machine.axis[2], 0);
		/* Устанавливаем текущие координаты равными машинным */
//		machine.axis[2].current_pos_coord = 0;
//		machine.axis[2].c_curve.current_pos = 0;
//		machine.axis[2].current_side = Forward;
	}
	return;
}
void G_CommandString(unsigned char* g_ch) {

	uint32_t num_ch = strlen(g_ch);

	for (uint32_t i = 0; i < num_ch;) {
		/* Rule */
		if (g_ch[i] == ' ') {i++; continue;}		/* Если находим пробел, то пропускаем его 		*/
		if (g_ch[i] == ';') break;			/* Если находим коментарий, то завершаем строку */

		/* Сначала команды с большим числом символов */
		/* M30 */
		if ((g_ch[i] == 'M') && (g_ch[i] == '3') && (g_ch[i] == '0')) {
			GC_M30();
			break;
		}
		/* G28 */
		if ((g_ch[i] == 'G') && (g_ch[i + 1] == '2') && (g_ch[i + 2] == '8')) {
			i += 3;
			if (i != num_ch) {
				for (uint8_t u = i; u < num_ch; u++) {
					if (g_ch[u] == ' ') continue;
					if (g_ch[u] == ';') {
//						GC_G28(GC_ALL_AXISES);
						break;
					}
					if ((g_ch[u] == 'Z') && (g_ch[u + 1] == '0')) {
//						GC_G28(GC_Z_AXIS);
						u += 2;
					}
					if ((g_ch[u] == 'Y') && (g_ch[u + 1] == '0')) {
//						GC_G28(GC_Y_AXIS);
						u += 2;
					}
					if ((g_ch[i] == 'X') && (g_ch[u + 1] == '0')) {
//						GC_G28(GC_X_AXIS);
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
		if ((g_ch[i] == 'G') && (g_ch[i + 1] == '0')) {
			i += 2;

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
						/* Z */
						if ((g_ch[u] == 'Z') || (g_ch[u] == 'z')) {
							uint8_t str_num_cnt = 0;
							u++;
							while(1) {
								if (((g_ch[u] >= '0') && (g_ch[u] <= '9')) || (g_ch[u] == '.')) {
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
//				t_z = (float)atof((const char*)str_num_z);
				GC_G0(t_x, t_y, 0/*t_z*/);
			}
			continue;
		}
		/* G1 */
		if ((g_ch[i] == 'G') && (g_ch[i + 1] == '1')) {

			i += 2;
			GC_G1(0, 0, 0);
			continue;
		}
		/* G2 */
		if ((g_ch[i] == 'G') && (g_ch[i + 1] == '2')) {

			i += 2;
//			GC_G2(0, 0, 0);
			continue;
		}
		/* G3 */
		if ((g_ch[i] == 'G') && (g_ch[i + 1] == '3')) {

			i += 2;
//			GC_G3(0, 0, 0);
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
		/* ... */

//	for (uint32_t row = 0; row < sd_file_rows; row++) {
//		uint8_t col = 0;
//
//		if ((uart_data[col] == 'G') && (uart_data[col + 1] == '0')) {
//			uint32_t X = 0;
//			uint32_t Y = 0;
//			uint32_t F = 0;
//
//
//			col += 2;
//			if ((uart_data[col] == ' ')) col++;
//
//			if (uart_data[col] == 'X') {
//				col++;
//
//				uint8_t i = col;
//				char st_pos[10] = {'\0', };
//				uint8_t j = 0;
//				while ((uart_data[i] != ' ') && (uart_data[i] != 'Y') && (uart_data[i] != 'F') && (uart_data[i] != ';')) {
//					st_pos[j] = uart_data[i];
//					i++;
//					j++;
//				}
//				col = ++i;
//
//				X = atof(st_pos);
//			}
//			if (uart_data[col] == 'Y') {
//				col++;
//
//				uint8_t i = col;
//				char st_pos[10] = {'\0', };
//				uint8_t j = 0;
//				while ((uart_data[i] != ' ') && (uart_data[i] != 'Y') && (uart_data[i] != 'F') && (uart_data[i] != ';')) {
//					st_pos[j] = uart_data[i];
//					i++;
//					j++;
//				}
//				col = ++i;
//
//				Y = atof(st_pos);
//			}
//			if (uart_data[col] == 'F') {
//				col++;
//
//				uint8_t i = col;
//				char st_pos[10] = {'\0', };
//				uint8_t j = 0;
//				while ((uart_data[i] != ' ') && (uart_data[i] != 'Y') && (uart_data[i] != 'F') && (uart_data[i] != ';')) {
//					st_pos[j] = uart_data[i];
//					i++;
//					j++;
//				}
//				col = ++i;
//
//				F = atof(st_pos);
//			}
//
//			PointMoves(&machine, X, Y, F);
//
//		}
//		else if (0) {
//
//		}
//	}




	if (0) GC_G28(GC_ALL_AXISES);











	return;
}











