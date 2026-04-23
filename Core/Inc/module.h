///*
// * module.h
// *
// *  Created on: Feb 15, 2026
// *      Author: makar
// */
//
//#ifndef INC_MODULE_H_
//#define INC_MODULE_H_
//
//
//#include "stm32f1xx_hal.h"
//#include "LCD1602.h"
//
///* LEDS */
//#define	LED_1_ON		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
//#define	LED_1_OFF		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
//#define LED_1_TGL		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
//
//#define	LED_2_ON		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
//#define	LED_2_OFF		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
//#define LED_2_TGL		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
//
///* State */
//typedef enum LS_state
//{
//	LS_OFF = 0,
//	LS_ON,
//} LS_state;
///* Enumirate axises */
//typedef enum type_axis_t
//{
//	axis_x = 0,
//	axis_y = 1,
//	axis_z = 2,
//} type_axis_t;
///* Programm PWM variable */
//typedef struct pulse_t
//{
//	/* for pwm_ctrl */
//	GPIO_PinState	start_state;
//	uint32_t 		pwm;
//	/* for freq ctrl */
//	uint32_t		counter;
//	uint32_t		pos_down;
//} pulse_t;
///* Enumirate of type for side */
//typedef enum move_index_t {
//	axis_Forward			= 0,
//	axis_Backforward 		= 1,
//} move_index_t;
///* Work status axis */
//typedef struct status_t
//{
//	move_index_t		current_side;
//	uint32_t			current_pulse;
//	_Bool				is_working;
//
//	_Bool				end_switch;
//
//} status_t;
///* Struct of the axis */
//typedef struct axis_t
//{
//	/*motor def*/
//	GPIO_TypeDef*		m_pulse_port;
//	uint32_t 			m_pulse_pin;
//
//	GPIO_TypeDef*		m_enable_port;
//	uint32_t 			m_enable_pin;
//
//	GPIO_TypeDef*		m_direction_port;
//	uint32_t 			m_direction_pin;
//	GPIO_TypeDef*		m_direction_port2;
//	uint32_t 			m_direction_pin2;
//	GPIO_TypeDef*		m_switch_port;
//	uint32_t 			m_switch_pin;
//
//	/* task */
//	move_index_t		target_side;
//	uint32_t			target_pulse;
//	pulse_t				channel_x;
//
//	/* debug info*/
//	status_t			status;
//
//} axis_t;
//
//
//
///* Struct of the module*/
//typedef struct module_t
//{
//	axis_t				axis[2];
//
//
//} module_t;
//
//
//
//
//
//
///* ************** FUNCTIONS ************** */
//_Bool ModuleInit();
//void ModuleLoop();
//void LS_GoHome();
//void LS_GoPoint(uint32_t x, uint32_t y, uint32_t speed);
//void LS_Stop();
//void Ls_GoHome();
//
//
//void AxisStop(type_axis_t axis);
//void AxisStep(type_axis_t axis, move_index_t side, uint32_t c_step, uint32_t speed);
//void AxisСontinuous(type_axis_t axis, move_index_t side, uint32_t speed);
//void AxisEnable(type_axis_t axis, LS_state st);
//void AxisDirection(type_axis_t axis, move_index_t move_side);
//
//
//
//
//
//
//
//
//
//
//
//#endif /* INC_MODULE_H_ */
