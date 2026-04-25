/*
 * Laser.h
 *
 *  Created on: Feb 22, 2026
 *      Author: makar
 */

#ifndef INC_LASER_H_
#define INC_LASER_H_


#include "stm32f1xx_hal.h"
#include "LCD1602.h"


/* LEDS */
#define	LED_1_ON			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
#define	LED_1_OFF			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
#define LED_1_TGL			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);

#define	LED_2_ON			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
#define	LED_2_OFF			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
#define LED_2_TGL			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);

#define	LED_2_ON			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
#define	LED_2_OFF			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

#define	LASER_ON			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
#define	LASER_OFF			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);


#define HOME_OFFSET			10	// 10 mm
#define MOTOR_STEP_ON_PER	200
#define STEP_ON_ONE_MM		80
#define ONE_STEP_WIDTH		0.0125		// 1 mm / 80 imp
#define EPS_PRECISION		0.0250
#define EPS_IMP_PRECISION	1
//================================================================================================
//================================================================================================
//================================================================================================

typedef struct switch_key_t
{
	GPIO_TypeDef*		m_sw_k_port;
	uint32_t 			m_sw_k_pin;

	_Bool				sw_k_enabled;
	_Bool				sw_k_state;
} switch_key_t;

/* Internal counter of pulse */
typedef struct counter_curve_t {
	uint32_t			counter;
	uint32_t			tgl_up;
	_Bool 				enabled;

	uint32_t 			current_pos; 	/* Количество импульсов которое двигатель насчитал в отработки процессе последней команды */
	uint32_t 			target_counter;
} counter_curve_t;

  /* Side movement */
typedef enum SideMV_t {
	Forward = 0,
	BackForward,
} SideMV_t;

typedef struct Drive_t {
	GPIO_TypeDef*		m_pulse_port;
	uint32_t 			m_pulse_pin;
	GPIO_TypeDef*		m_dir_port;
	uint32_t 			m_dir_pin;
	GPIO_TypeDef*		m_en_port;
	uint32_t 			m_en_pin;
	/****************************/
	/*Step accuracy*/
	//	  GPIO_TypeDef*		m_M_port[3];
	//	  uint32_t 			m_M_pin[3];
	//	  _Bool				m_M_state[3];

	SideMV_t			m_side;
	_Bool				m_drv_enabled;

	uint32_t			counter;
} Drive_t;

typedef struct Axis_t {
	Drive_t				drive;
	counter_curve_t		c_curve;
	switch_key_t		sw_key;

	float 				current_pos_coord;
	SideMV_t 			current_side;
	uint32_t 			speed;
	_Bool				working;

	uint32_t 			mach_base_crd;		/* Машинные координаты */
	uint32_t 			relative_base_crd;	/* Относительные координаты координаты */

	float				limit_start_coord;
	float				limit_end_coord;
} Axis_t;
typedef struct Head_t {

} Head_t;
typedef struct Machine_t {
	Head_t 				head;
	Axis_t				axis[2];

} Machine_t;



//================================================================================================

typedef struct global_time_t {
	uint32_t glb_time_us;



} global_time_t;

uint32_t GlbtimGetTim();
void GlbtimDelay(uint32_t us);

//================================================================================================



//================================================================================================
//================================================================================================
//================================================================================================

void LaserCountCurvEN(counter_curve_t* cc, _Bool en);
void LaserCountCurvTgl(counter_curve_t* cc, uint32_t tgl);
void LaserDriverDirection(Drive_t* drv, SideMV_t dr);
void LaserDriverEnable(Drive_t* drv, _Bool st);
void LaserSW_Set(Axis_t* ax, _Bool st);

_Bool LaserInit();
void LaserLoop();
_Bool GoHome();

void StepMoves(Axis_t* ax, SideMV_t sd, uint32_t length, uint32_t sp);
void ContMoves(Axis_t* ax, SideMV_t sd, uint32_t sp);
void PointMoves(Machine_t* mh, uint32_t x, uint32_t y, uint32_t sp);







#endif /* INC_LASER_H_ */
