///*
// * module.c
// *
// *  Created on: Feb 15, 2026
// *      Author: makar
// */
//
//
//
//#include "module.h"
//
///* If you need freq control then please set PWM_CONTROL_OR_FREQ_CONTROL*/
//#define 	PWM_CONTROL_OR_FREQ_CONTROL	1
//
//
//
//
//extern TIM_HandleTypeDef 	htim7;
//
//module_t module;
//
//
//uint8_t uart_data[10];
//_Bool distance_security = true;
//
//_Bool ModuleInit()
//{
//	/* Init axises */
//	/* X */
//	module.axis[0].m_pulse_port				= GPIOD;
//	module.axis[0].m_pulse_pin				= GPIO_PIN_11;
//	module.axis[0].m_enable_port			= GPIOD;
//	module.axis[0].m_enable_pin				= GPIO_PIN_14;
//	module.axis[0].m_direction_port			= GPIOD;
//	module.axis[0].m_direction_pin			= GPIO_PIN_10;
//	module.axis[0].m_direction_port2		= GPIOD;
//	module.axis[0].m_direction_pin2			= GPIO_PIN_9;
//	module.axis[0].m_switch_port			= GPIOD;
//	module.axis[0].m_switch_pin				= GPIO_PIN_6;
//
//	module.axis[0].status.current_side 		= 0;
//	module.axis[0].target_side 				= 0;
//	module.axis[0].target_pulse		 		= 0;
//	module.axis[0].channel_x.pwm			= 0;
//	module.axis[0].channel_x.start_state	= GPIO_PIN_RESET;
//
//	module.axis[0].status.is_working		= false;
//	module.axis[0].channel_x.counter		= 0;
//	module.axis[0].channel_x.pos_down		= 0;
//
//	module.axis[0].status.end_switch		= false;
//
//	AxisDirection(axis_x, axis_Forward);
//
//	/* Y */
//	module.axis[1].m_pulse_port				= GPIOD;
//	module.axis[1].m_pulse_pin				= GPIO_PIN_13;
//	module.axis[1].m_enable_port			= GPIOD;
//	module.axis[1].m_enable_pin				= GPIO_PIN_15;
//	module.axis[1].m_direction_port			= GPIOD;
//	module.axis[1].m_direction_pin			= GPIO_PIN_12;
//	module.axis[1].m_switch_port			= GPIOD;
//	module.axis[1].m_switch_pin				= GPIO_PIN_7;
//	module.axis[1].status.current_side 		= 0;
//	module.axis[1].target_side 				= 0;
//	module.axis[1].target_pulse		 		= 0;
//	module.axis[1].channel_x.pwm			= 0;
//	module.axis[1].channel_x.start_state	= GPIO_PIN_RESET;
//
//	module.axis[1].status.is_working		= false;
//	module.axis[1].channel_x.counter		= 0;
//	module.axis[1].channel_x.pos_down		= 0;
//
//	module.axis[1].status.end_switch		= false;
//
//
//	AxisDirection(axis_y, axis_Backforward);
//
//	/* END INIT */
//
//	HAL_TIM_Base_Start_IT(&htim7);
//
//
//	LCD1602_Init();
//
//	LCD1602_WriteString("Enable OK");
//    LCD1602_SetCursor(1, 0);
//    LCD1602_WriteString("Version:0.0.1");
//
//    HAL_Delay(2000);
//
////    AxisStep(axis_x, axis_Backforward, 1000, 1000);
////    AxisStep(axis_y, axis_Forward, 10000, 2000);
//
//
//    Ls_GoHome();
//
//
//	return 0;
//}
//void ModuleLoop()
//{
//	while(1)
//	{
//		LED_1_TGL;
//		LED_2_TGL;
//		HAL_Delay(200);
//	}
//}
//
//void LS_GoHome()
//{
//
//}
//void AxisStop(type_axis_t axis)
//{
//	if (axis == axis_x)
//	{
//		module.axis[0].status.is_working			= false;
//	    module.axis[0].channel_x.pos_down			= 0;
//	    module.axis[0].target_pulse					= 0;
//	}
//	if (axis == axis_y)
//	{
//		module.axis[1].status.is_working			= false;
//	    module.axis[1].channel_x.pos_down			= 0;
//	    module.axis[1].target_pulse					= 0;
//	}
//	else {}
//}
//void AxisStep(type_axis_t axis, move_index_t side, uint32_t c_step, uint32_t speed)
//{
//	if (axis == axis_x)
//	{
//	    module.axis[0].channel_x.pos_down		= 100000 / speed;	/* тики на число испульсов в секунду получаем время между тиками */
//	    module.axis[0].target_pulse				= c_step;
//	    module.axis[0].target_side				= side;
//
//
//	    AxisEnable(axis_x, LS_ON);
//	    module.axis[0].status.is_working		= true;
//	}
//	else if (axis == axis_y)
//	{
//	    module.axis[1].channel_x.pos_down		= 100000 / speed;	/* тики на число испульсов в секунду получаем время между тиками */
//	    module.axis[1].target_pulse				= c_step;
//	    module.axis[1].target_side				= side;
//
//
//	    AxisEnable(axis_y, LS_ON);
//	    module.axis[1].status.is_working		= true;
//	}
//	else {}
//
//
//	HAL_Delay(200);
//
//}
//void AxisСontinuous(type_axis_t axis, move_index_t side, uint32_t speed)
//{
//	if (axis == axis_x)
//	{
//	    module.axis[0].channel_x.pos_down		= 100000 / speed;	/* тики на число испульсов в секунду получаем время между тиками */
//	    module.axis[0].target_side				= side;
//	    module.axis[0].target_pulse				= 100000;
//
//	    AxisEnable(axis_x, LS_ON);
//	    module.axis[0].status.is_working		= true;
//	}
//	else if (axis == axis_y)
//	{
//	    module.axis[1].channel_x.pos_down		= 100000 / speed;	/* тики на число испульсов в секунду получаем время между тиками */
//	    module.axis[1].target_side				= side;
//	    module.axis[1].target_pulse				= 100000;
//
//	    AxisEnable(axis_y, LS_ON);
//	    module.axis[1].status.is_working		= true;
//	}
//	else {}
//	HAL_Delay(200);
//}
//void LS_Stop()
//{
//
//}
//
//
//
//void Ls_GoHome()
//{
//	distance_security = false;
//	while (1)
//	{
//		if (!module.axis[1].status.end_switch)
//		{
//			AxisСontinuous(axis_y, axis_Forward, 10000);
//		}
//		else
//		{
//			AxisStop(axis_y);
//			module.axis[1].status.end_switch 		= true;
//			module.axis[1].status.current_pulse 	= 0;
//		}
//	}
////	while (1)
////	{
////		if (!module.axis[0].status.end_switch)
////		{
////			AxisStep(axis_x, axis_Backforward, 10, 10000);
////		}
////		else
////		{
////			AxisStop(axis_x);
////			module.axis[0].status.end_switch 		= true;
////			module.axis[0].status.current_pulse 	= 0;
////		}
////	}
//	distance_security = true;
//}
//
//
//
//void AxisDirection(type_axis_t axis, move_index_t move_side)
//{
//	if (axis == axis_x)
//	{
//		HAL_GPIO_WritePin(module.axis[axis].m_direction_port, module.axis[axis].m_direction_pin, move_side);
//		HAL_GPIO_WritePin(module.axis[axis].m_direction_port2, module.axis[axis].m_direction_pin2, !move_side);
//	}
//	else
//	{
//		HAL_GPIO_WritePin(module.axis[axis].m_direction_port, module.axis[axis].m_direction_pin, move_side);
//	}
//
//}
//void AxisEnable(type_axis_t axis, LS_state st)
//{
//	if (axis == axis_x)
//	{
//		HAL_GPIO_WritePin(module.axis[0].m_enable_port, module.axis[0].m_enable_pin, !st);
//	}
//	else if (axis == axis_y)
//	{
//		HAL_GPIO_WritePin(module.axis[1].m_enable_port, module.axis[1].m_enable_pin, !st);
//	}
//	else {}
//}
//
//
///* Program pulse */
//void pulse_control()
//{
//#ifndef PWM_CONTROL_OR_FREQ_CONTROL
////	for (uint8_t i = 0; i < 2; i++)
////	{
////		if (module.axis[i].channel_x.counter == 0)
////		{
////			if (module.axis[i].channel_x.pwm != 0)
////			{
////				HAL_GPIO_WritePin(module.axis[i].m_pulse_port, module.axis[i].m_pulse_pin, GPIO_PIN_SET);
////			}
////			else HAL_GPIO_WritePin(module.axis[i].m_pulse_port, module.axis[i].m_pulse_pin, GPIO_PIN_RESET);
////		}
////		else if (module.axis[i].channel_x.counter == module.axis[i].channel_x.pwm)
////		{
////			HAL_GPIO_WritePin(module.axis[i].m_pulse_port, module.axis[i].m_pulse_pin, GPIO_PIN_RESET);
////		}
////
////		if (99 <= module.axis[i].channel_x.counter)
////		{
////			module.axis[i].channel_x.counter = 0;
////		}
////		else module.axis[i].channel_x.counter++;
////	}
//#else
//	for (uint8_t i = 0; i < 2; i++)
//	{
//		if(module.axis[i].status.is_working)
//		{
//			if (module.axis[i].channel_x.counter >= (module.axis[i].channel_x.pos_down - 1))
//			{
//				HAL_GPIO_TogglePin(module.axis[i].m_pulse_port, module.axis[i].m_pulse_pin);
//				module.axis[i].channel_x.counter = 0;
//				module.axis[i].status.current_pulse++;
//			}
//			else
//			{
//				module.axis[i].channel_x.counter++;
//			}
//			if (module.axis[i].target_pulse < (module.axis[i].status.current_pulse * (1.0 / 2.0)))
//			{
//			    AxisEnable(axis_x, LS_OFF);
//			    module.axis[i].status.is_working		= false;
//
//			    module.axis[i].channel_x.pos_down		= 0;
//			    module.axis[i].target_pulse				= 0;
//			    module.axis[i].target_side				= 0;
//			    module.axis[i].status.current_pulse 	= 0;
//			}
//		}
//		else if(!module.axis[i].status.is_working) module.axis[i].channel_x.counter = 0;
//	}
//#endif
//
//}
///* TIM FOR PROGRAMM PWM */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if (htim->Instance == TIM7){
//		pulse_control();
//	}
//}
//
///* EXTI_Handler_Callback */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	if (GPIO_Pin == GPIO_PIN_8)
//	{
//		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_RESET)
//		{
//
//		}
//		else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_SET)
//		{
//
//		}
//		for (uint32_t slp = 0; slp < 1000; slp++) {}
//	}
//	else if (GPIO_Pin == GPIO_PIN_5)
//	{
//
//	}
//	else if (GPIO_Pin == GPIO_PIN_6)		// X
//
//	{
//		if (distance_security)
//		{
//			AxisStop(axis_x);
//			module.axis[0].status.current_pulse 	= 0;
//		}
//		module.axis[0].status.end_switch 		= true;
//	}
//	else if (GPIO_Pin == GPIO_PIN_7)		// Y
//	{
//		if (distance_security)
//		{
//			AxisStop(axis_y);
//			module.axis[1].status.current_pulse 	= 0;
//		}
//		module.axis[1].status.end_switch 		= true;
//	}
//}
////
////void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
////{
////	if (huart == &huart4)
////	{
////		LED_1_ON;
////	}
////	else if (huart == &huart5)
////	{
////		LED_1_ON;
////	}
////	else if (huart == &huart1)
////	{
////		LED_1_ON;
////	}
////	else if (huart == &huart2)
////	{
////		LED_1_ON;
////	}
////	else if (huart == &huart3)
////	{
////		LED_1_ON;
////	}
////
////
////}
//
//
//
//
