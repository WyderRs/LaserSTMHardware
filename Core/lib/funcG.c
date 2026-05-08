/*
 * func.c
 *
 *  Created on: May 1, 2026
 *      Author: makar
 */


#include "funcG.h"
#include "string.h"
#include "stdbool.h"
#include "g_code.h"

#include <math.h>

extern Machine_t machine;
/* */
extern FATFS fs;
extern FIL fil;
/* */


BYTE GC_Buffer[100][100] = {{0, }, };


void StartGCode(const TCHAR* path) {

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

void GoHome(_Axis_t ax)
{
	if (ax == _ALL_AXISES) {
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
		ModuleDriverEnable(&machine.axis[0].drive, false);
		ModuleDriverEnable(&machine.axis[1].drive, false);
//		ModuleDriverEnable(&machine.axis[2].drive, false);

		Machine_SW_Set(&machine.axis[0], false);
		Machine_SW_Set(&machine.axis[1], false);
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
	else if (ax == _X_AXIS) {
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
		ModuleDriverEnable(&machine.axis[0].drive, false);
		Machine_SW_Set(&machine.axis[0], false);

		MachineCoordSet(&machine.axis[0], 0);
		/* Устанавливаем текущие координаты равными машинным */
		machine.axis[0].current_pos_coord = 0;
		machine.axis[0].c_curve.current_pos = 0;
		machine.axis[0].current_side = Forward;
	}
	else if (ax == _Y_AXIS) {
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
		ModuleDriverEnable(&machine.axis[1].drive, false);
		Machine_SW_Set(&machine.axis[1], false);
		MachineCoordSet(&machine.axis[1], 0);
		/* Устанавливаем текущие координаты равными машинным */
		machine.axis[1].current_pos_coord = 0;
		machine.axis[1].c_curve.current_pos = 0;
		machine.axis[1].current_side = Forward;
	}
	else if (ax == _Z_AXIS) {
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
//		ModuleDriverEnable(&machine.axis[2].drive, false);
//		Machine_SW_Set(&machine.axis[2], false);
//		MachineCoordSet(&machine.axis[2], 0);
		/* Устанавливаем текущие координаты равными машинным */
//		machine.axis[2].current_pos_coord = 0;
//		machine.axis[2].c_curve.current_pos = 0;
//		machine.axis[2].current_side = Forward;
	}
	return;
}

void StepMoves(Axis_t* ax, SideMV_t sd, uint32_t length, uint32_t sp)
{
	/* Если нажат концевик и при этом направление от него, или концевик не нажат то... */
	if ((ax->sw_key.sw_k_state && (sd == Forward)) || (!ax->sw_key.sw_k_state))
	{
		/* Если мы зашли сюда при нажатом концевике, значит его требуется сбросить */
		ax->sw_key.sw_k_state = false;

		ax->drive.counter = 0;

		ax->current_side = sd;
		ModuleDriverDirection(&ax->drive, sd);
		ModuleDriverEnable(&ax->drive, true);	// 50000 число импульсов (период 10us)(максимальная)
		sp = 625.0 / sp;						//625=50000/80
		ModuleCountCurvTgl(&ax->c_curve, sp);
		ModuleCountCurvEN(&ax->c_curve, true);

		uint32_t stp = 2 * length * 80;			// (tgl=2) * length * (imp/mm=80)

		/* Ожидаем пока не доедем до требуемой точки */
		while (ax->drive.counter < stp) {
			/* Проверка нажатия на концевик*/
			if (ax->sw_key.sw_k_state) {
				stp = 0;
				ax->drive.counter = 0;

				ContMoves(ax, !sd, 20);
				while (!ax->sw_key.sw_k_state) {}
				GlbtimDelay(500);
				ax->sw_key.sw_k_enabled			= false;
				ax->drive.counter 				= 0;
				StepMoves(ax, Forward, HOME_OFFSET, 20);
				GlbtimDelay(500);
				/* Сброс события прерывания */
				EXTI->PR 						= ax->sw_key.m_sw_k_pin;
				ax->sw_key.sw_k_enabled			= true;
				GlbtimDelay(500);

				break;
			}
//			/* Проверка на позицию внутри рабочей */
//			if (ax->current_pos_coord <= ax->limit_start_coord) {
//				LaserCountCurvEN(&ax->c_curve, false);
//				break;
//			}
//			else if (ax->current_pos_coord >= ax->limit_end_coord) {
//				LaserCountCurvEN(&ax->c_curve, false);
//				break;
//			}
		}
	}
	else {}
	ModuleCountCurvEN(&ax->c_curve, false);
	ModuleDriverEnable(&ax->drive, false);
}
void PointMoves(Machine_t* mh, float x, float y, uint32_t sp)
{
	/* Если нажат концевик и при этом направление от него, или концевик не нажат то... */
	if (1)
	{
		mh->axis[0].sw_key.sw_k_state = false;
		mh->axis[1].sw_key.sw_k_state = false;

		mh->axis[0].drive.counter = 0;
		mh->axis[1].drive.counter = 0;

		if (x > mh->axis[0].current_pos_coord) {
			ModuleDriverDirection(&mh->axis[0].drive, Forward);
			mh->axis[0].current_side = Forward;
		}
		else {
			ModuleDriverDirection(&mh->axis[0].drive, BackForward);
			mh->axis[0].current_side = BackForward;
		}

		if (y > mh->axis[1].current_pos_coord) {
			ModuleDriverDirection(&mh->axis[1].drive, Forward);
			mh->axis[1].current_side = Forward;
		}
		else {
			ModuleDriverDirection(&mh->axis[1].drive, BackForward);
			mh->axis[1].current_side = BackForward;
		}

		ModuleDriverEnable(&mh->axis[0].drive, true);
		ModuleDriverEnable(&mh->axis[1].drive, true);

		/*
		 * 50000 - частота импульсов таймера
		 * sp - скорость в мм/с
		 *
		 * */
		float x1 = machine.axis[0].current_pos_coord;
		float y1 = machine.axis[1].current_pos_coord;

		float tgl_up	= 50000 / (sp * STEP_ON_ONE_MM);
		/* Приращение должно быть положительным */
		float dx = x - x1;
		float dy = y - y1;
		/* Ищем короткий путь */
		float L = sqrt((dx * dx) + (dy * dy));
		/* Если идем в туже точку, где стоим, то выходим */
		if (L == 0) {
			ModuleDriverEnable(&mh->axis[0].drive, false);
			ModuleDriverEnable(&mh->axis[1].drive, false);
			return;
		}
		/* В случае нахождения в той же точке по оси говорим что приращение равно длине L */
		/* Это сделано для получения коээфициента равного 1 - максимальная заданная скорость */
		if (dx <= EPS_PRECISION * 2) dx = L;
		if (dy <= EPS_PRECISION * 2) dy = L;
		/* Находим коэфициенты задающие скорость движения оси */
		float spp1 = L / fabs(dx);
		float spp2 = L / fabs(dy);
		/* Применяем коэфициенты*/
		uint32_t tgl_up1 = tgl_up * fabs(spp1);
		uint32_t tgl_up2 = tgl_up * fabs(spp2);
		/* Ограничение минимальной скорости */
		if (tgl_up1 <= 0) tgl_up1 = 1;
		if (tgl_up2 <= 0) tgl_up2 = 1;

		ModuleCountCurvTgl(&mh->axis[0].c_curve, tgl_up1);
		ModuleCountCurvTgl(&mh->axis[1].c_curve, tgl_up2);

		ModuleCountCurvEN(&mh->axis[0].c_curve, true);
		ModuleCountCurvEN(&mh->axis[1].c_curve, true);

		_Bool flag[2] = {false, };
		/* Ожидаем пока не доедем до требуемой точки */
		while (1) {

			if ((mh->axis[0].current_pos_coord >= (x - EPS_PRECISION)) && (mh->axis[0].current_pos_coord <= (x + EPS_PRECISION))) {
				ModuleCountCurvEN(&mh->axis[0].c_curve, false);
				flag[0] = true;
			}
			if ((mh->axis[1].current_pos_coord >= (y - EPS_PRECISION)) && (mh->axis[1].current_pos_coord <= (y + EPS_PRECISION))) {
				ModuleCountCurvEN(&mh->axis[1].c_curve, false);
				flag[1] = true;
			}
			if (flag[0] && flag[1]) break;

			/* Концевики */
			for (uint8_t i = 0; i < 2; i++) {
				if (mh->axis[i].sw_key.sw_k_state) {
					mh->axis[i].drive.counter = 0;

					ContMoves(&mh->axis[i], !mh->axis[i].current_side, 20);
					while (!mh->axis[i].sw_key.sw_k_state) {}
					GlbtimDelay(500);
					mh->axis[i].sw_key.sw_k_enabled			= false;
					mh->axis[i].drive.counter 				= 0;
					StepMoves(&mh->axis[i], Forward, HOME_OFFSET, 20);
					GlbtimDelay(500);
					/* Сброс события прерывания */
					EXTI->PR 								= mh->axis[i].sw_key.m_sw_k_pin;
					mh->axis[i].sw_key.sw_k_enabled			= true;
					GlbtimDelay(500);

					break;
				}

				/* Проверка на позицию внутри рабочей */
				if (mh->axis[i].current_pos_coord < mh->axis[i].limit_start_coord) {
					ModuleCountCurvEN(&mh->axis[i].c_curve, false);
					break;
				}
				else if (mh->axis[i].current_pos_coord > mh->axis[i].limit_end_coord) {
					ModuleCountCurvEN(&mh->axis[i].c_curve, false);
					break;
				}
			}
		}
	}
	else {}

	ModuleDriverEnable(&mh->axis[0].drive, false);
	ModuleDriverEnable(&mh->axis[1].drive, false);
}
void CircleMove(float x1, float y1, float r, _Bool dir) {
	/* Текущая положение */
	float x0 = machine.axis[0].current_pos_coord;
	float y0 = machine.axis[1].current_pos_coord;
	/* Радиус должен быть > 0 */
	if (r <= 0.0) return;
	/* Расстояние между точками */
	float dx = x1 - x0;
	float dy = y1 - y0;
	/* Находим хорду */
	float D = sqrt((dx *dx) + (dy * dy));
	/* Хорда не должна быть больше 2 радиусов */
	if (D >= (2 * r + EPS_PRECISION)) return;
	/* Середина хорды */
	float mx = (x0 + x1) / 2.0;
	float my = (y0 + y1) / 2.0;
	/* Перпендикуляры к хорде */
	float perp_x 	= -dy;
	float perp_y 	= dx;
	float D2 		= sqrt((perp_x * perp_x) + (perp_y * perp_y));
	/* Деление на ноль */
	if (D2 < EPS_PRECISION) return;

	perp_x /= D2;
	perp_y /= D2;

	/* Расстояние от середины хорды до центра окружности */
	float h = sqrt((r * r) - ((D / 2.0) * (D / 2.0)));

	/* Два возможных центра */
    float cx1 = mx + h * perp_x;
    float cy1 = my + h * perp_y;

    float cx2 = mx - h * perp_x;
    float cy2 = my - h * perp_y;

    float NormalizeAngle (float a) {
    	while (a > M_PI) a -= 2 * M_PI;
    	while (a <= -M_PI) a += 2 * M_PI;
    	return a;
    	};

    // Вычисляем углы от центров до начальной и конечной точек
    float theta0_1 	= atan2f(y0 - cy1, x0 - cx1);
    float theta1_1 	= atan2f(y1 - cy1, x1 - cx1);
    float delta1 	= NormalizeAngle(theta1_1 - theta0_1);

    float theta0_2 	= atan2f(y0 - cy2, x0 - cx2);
    float theta1_2 	= atan2f(y1 - cy2, x1 - cx2);
    float delta2 		= NormalizeAngle(theta1_2 - theta0_2);

    // Выбор центра по направлению
    float cx = 0, cy = 0;
//    if (dir == 0) {
//    	// G03: против часовой — положительный угол
//    	cx = (delta1 > 0) ? cx1 : cx2;
//    	cy = (delta1 > 0) ? cy1 : cy2;
//    } else {
//    	// G02: по часовой — отрицательный угол
//    	cx = (delta1 < 0) ? cx1 : cx2;
//    	cy = (delta1 < 0) ? cy1 : cy2;
//    }

    float delta_theta = 0;
    float theta0 = 0;
    float theta1 = 0;


    if (dir == 0) { // G03: против часовой — нужен положительный угол
        if (delta1 >= 0) {
            cx = cx1; cy = cy1; delta_theta = delta1; theta0 = theta0_1;
        } else {
            cx = cx2; cy = cy2; delta_theta = delta2; theta0 = theta0_2;
        }
    } else { // G02: по часовой — нужен отрицательный угол
        if (delta1 <= 0) {
            cx = cx1; cy = cy1; delta_theta = delta1; theta0 = theta0_1;
        } else {
            cx = cx2; cy = cy2; delta_theta = delta2; theta0 = theta0_2;
        }
    }


    // Углы от выбранного центра до начальной и конечной точек
//    float theta0 = atan2f(y0 - cy, x0 - cx);
//    float theta1 = atan2f(y1 - cy, x1 - cx);

    // Угол поворота (может быть >π или <-π, но мы не нормализуем)
//    float delta_theta = theta1 - theta0;

    // Количество шагов интерполяции
	int num_steps = 150;
	float dtheta = delta_theta / num_steps;

	// Рекуррентные cos и sin шага
	float c = cosf(dtheta);
	float s = sinf(dtheta);

	// Начальный вектор от центра до начальной точки
	float x_rel = r * cosf(theta0);
	float y_rel = r * sinf(theta0);

    // Генерация точек по дуге (рекуррентно)
    for (uint32_t i = 0; i <= num_steps; i++) {

    	float px = cx + x_rel;
        float py = cy + y_rel;

    	PointMoves(&machine, px, py, machine.FeedRate);

        // Обновляем текущую позицию (для отладки/следующих команд)
        machine.axis[0].current_pos_coord = px;
        machine.axis[1].current_pos_coord = py;

        // Обновляем вектор поворота (рекуррентно)
        if (i < num_steps) {
            float xn = c * x_rel - s * y_rel;
            float yn = s * x_rel + c * y_rel;
            x_rel = xn;
            y_rel = yn;
        }
    }
	return;
}

void ContMoves(Axis_t* ax, SideMV_t sd, uint32_t sp)
{
	/* Настраиваем драйверы на нужное направление и включаем их */
	ax->current_side = sd;
	ModuleDriverDirection(&ax->drive, sd);
	ModuleDriverEnable(&ax->drive, true);
	/* Разрешаем воспроизводить импульсы для движения */
	sp = 625.0 / sp;						//625=50000/80
	ModuleCountCurvTgl(&ax->c_curve, sp);
	ModuleCountCurvEN(&ax->c_curve, true);
}
void SetFeedRate(float fd) {
	machine.FeedRate = fd;
	fd = 625.0 / fd;						//625=50000/80
	ModuleCountCurvTgl(&machine.axis[0].c_curve, fd);
	ModuleCountCurvTgl(&machine.axis[1].c_curve, fd);
//	LaserCountCurvTgl(&ax->c_curve, fd);

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
	return;
}
//_Bool GoHome()
//{
//	/* HOME Y */
//	ContMoves(&machine.axis[1], BackForward, 20);
//	while (!machine.axis[1].sw_key.sw_k_state) {}
//	GlbtimDelay(500);
//	machine.axis[1].sw_key.sw_k_enabled			= false;
//	machine.axis[1].drive.counter 				= 0;
//	StepMoves(&machine.axis[1], Forward, HOME_OFFSET, 20);
//	GlbtimDelay(500);
//	/* Сброс события прерывания */
//	EXTI->PR 									= machine.axis[1].sw_key.m_sw_k_pin;
//	machine.axis[1].sw_key.sw_k_enabled			= true;
//	GlbtimDelay(500);
//	/* HOME X */
//	ContMoves(&machine.axis[0], BackForward, 20);
//	while (!machine.axis[0].sw_key.sw_k_state) {}
//	GlbtimDelay(500);
//	machine.axis[0].sw_key.sw_k_enabled			= false;
//	machine.axis[0].drive.counter 				= 0;
//	StepMoves(&machine.axis[0], Forward, HOME_OFFSET, 20);
//	GlbtimDelay(500);
//	/* Сброс события прерывания */
//	EXTI->PR 									= machine.axis[0].sw_key.m_sw_k_pin;
//	machine.axis[0].sw_key.sw_k_enabled			= true;
//
//	LaserDriverEnable(&machine.axis[0].drive, false);
//	LaserDriverEnable(&machine.axis[1].drive, false);
//
//	LaserSW_Set(&machine.axis[0], false);
//	LaserSW_Set(&machine.axis[1], false);
//
//	MachineCoordSet(&machine.axis[0], 0);
//	MachineCoordSet(&machine.axis[1], 0);
//
//	/* Устанавливаем текущие координаты равными машинным */
//	machine.axis[0].current_pos_coord = 0;
//	machine.axis[1].current_pos_coord = 0;
//
//	machine.axis[0].c_curve.current_pos = 0;
//	machine.axis[1].c_curve.current_pos = 0;
//
//	machine.axis[0].current_side = Forward;
//	machine.axis[1].current_side = Forward;
//
//	return 0;
//}

