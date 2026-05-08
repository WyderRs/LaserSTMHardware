/*
 * machine.h
 *
 *  Created on: May 4, 2026
 *      Author: makar
 */

#ifndef INC_MACHINE_H_
#define INC_MACHINE_H_


#include "stm32f1xx.h"


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

/* Системные параметры */
typedef struct Common_param_t {
	float X;
	float Y;
	float Z;

	float S;
	float F;

} Common_param_t;

/* Side movement */
typedef enum SideMV_t {
	Forward = 0,
	BackForward,
} SideMV_t;

/* Структура концевиков */
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

/* Структура драйвера двигателя */
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

/* Структура оси (X,Y,Z)*/
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

/* Голова (станка) */
/* LR 	- LASER 	*/
/* SDL - SPINDLE */
typedef struct Head_t {
	/***************************************************/
	/* LASER */
	GPIO_TypeDef*		LR_port;	// Порт лазера
	uint32_t 			LR_pin;		// Пин лазера

	_Bool				LR_State;	// Состояние лазера
	/***************************************************/
	/* SPINDLE */
	GPIO_TypeDef*		SPL_port;	// Порт лазера
	uint32_t 			SPL_pin;		// Пин лазера


	_Bool				SDL_State;	// Состояние шпинделя


	/* ПРОВЕРИТЬ МОЖНО ЛИ ЛАЗЕРОМ УПРАВЛЯТЬ С ПОМОЩЬЮ ШИМ */
} Head_t;

/* Главная структура (описание станка) */
typedef struct Machine_t {
	Head_t 				head;
	Axis_t				axis[2];

	Common_param_t		COM_Param;
	float 				FeedRate;
} Machine_t;
/* Структура счетчика */
typedef struct global_time_t {
	uint32_t glb_time;
} global_time_t;


/* Funtions */
/* Ограничение рабочей области */
void MachineSetProgramLimit(Axis_t* ax, float start, float end);
/* Разрешение производить расчет выходных импульсов для двигателей */
void ModuleCountCurvEN(counter_curve_t* cc, _Bool en);
/* Установка времени формирования импулься (параметр определяет скорость осей) */
void ModuleCountCurvTgl(counter_curve_t* cc, uint32_t tgl);
/* Установка направления вращения двигателя */
void ModuleDriverDirection(Drive_t* drv, SideMV_t dr);
/* Включение/выключение драйверов */
void ModuleDriverEnable(Drive_t* drv, _Bool st);
/* Включение/выключение работы концевиков */
void Machine_SW_Set(Axis_t* ax, _Bool st);
/* Установка начала машинной (абсолютной) системы координат */
void MachineCoordSet(Axis_t* ax, uint32_t var);
/* Установка начала локальной (относительной) системы координат */
void MachineRelativeSet(Axis_t* ax, uint32_t var);
/* Вкл/Выкл лазер */
void MachineLaserState(_Bool st);


//================================================================================================

//================================================================================================

//================================================================================================
/* Запуск оссцилятора, отвечающего за генерацию импульсов двигателям */
void Machine_Start_MainCounter(void);
/* Остановка оссцилятора, отвечающего за генерацию импульсов двигателям */
void Machine_Stop_MainCounter(void);
/* Запуск оссцилятора, отвечающего за счет импульсов 1us */
void Machine_Start_SupCounter(void);
/* Остановка оссцилятора, отвечающего за счет импульсов 1us */
void Machine_Stop_SupCounter(void);
/* Задержка (временнАя) */
void GlbtimDelay(uint32_t us);









#endif /* INC_MACHINE_H_ */
