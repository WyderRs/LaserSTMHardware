/*
 * DriverLib.h
 *
 *  Created on: Aug 10, 2026
 *      Author: roman
 */

#ifndef LIB_DRIVERLIB_H_
#define LIB_DRIVERLIB_H_

#include "stm32f1xx.h"


/* Step to home positions */
#define HOME_OFFSET			10	// 10 mm
/* Количество шагов на оборот двигателя  */
#define MOTOR_STEP_ON_PER	200
/* Количестов импульсов на 1 мм */
#define STEP_ON_ONE_MM		80
/* Величина шага (импульса) на 1 мм */
#define ONE_STEP_WIDTH		0.0125		// 1 mm / 80 imp
/* Окрестность точности */
#define EPS_PRECISION		0.0125
/* Точность */
#define EPS_IMP_PRECISION	1
/* Максимальные размеры стола станка */
#define MAX_TABLE_X			170
#define MAX_TABLE_Y			130
/* Максимальная/минимальная скорость */
#define MAX_SPEED   		150.0f     	// mm/s
#define MIN_SPEED			0.01f   	// mm/s
/* Минимальная и максимальная мощность лазера (частота импульсов) */
#define MAX_LR_POWER		20
#define MIN_LR_POWER		100

typedef enum state_en_t {
	OFF = 0,
	ON = 1,
} state_en_t;
typedef enum state_work_t {
	tOFF = 0,
	tON,
	tBUSY,
	tWAIT,
	tWORKING,
} state_work_t;
typedef enum side_t {
	Forward = 0,
	BackForward,
	Hold,
} side_t;
typedef enum Coord_ax {
	x = 0,
	y,
	z,
	all,
} Coord_ax;

typedef struct Point_t{
	float x;
	float y;
	float z;
} Point_t;


/* Type definition axis struct */
typedef struct tAxis_t {
	GPIO_TypeDef	*port_dir;			// dir_port
	uint32_t 		pin_dir;			// dir_pin
	GPIO_TypeDef	*port_en;			// en_port
	uint32_t 		pin_en;				// en_pin
	GPIO_TypeDef	*port_pulse;		// pulse_port
	uint32_t 		pin_pulse;			// pulse_pin


	uint32_t		counter;			// counter
	uint32_t		tgl;				// point of reverse state
	side_t			direction;			// direction of side for rotate


	float 			current_pos_coord;	// current position of this coordinate axis
	uint32_t		current_pos;		// current position of this axis

} tAxis_t;


typedef struct tHead_t {
	tAxis_t 		tAxis[3];	/* x, y, z */
	state_work_t	state;		// state of the work
} tHead_t;











void tbInit();										// Initialize main structure
void tbDriver(state_en_t st);									// Driver enable
void dl_CheckPWM();									// For working PWM
void tbMove(float tx, float ty, float tz);			// Go to move to point





#endif /* LIB_DRIVERLIB_H_ */
