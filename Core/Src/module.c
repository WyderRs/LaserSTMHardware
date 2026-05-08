/*
 * Laser.c
 *
 *  Created on: Feb 22, 2026
 *      Author: makar
 */

#include <module.h>


extern Machine_t machine;

/*Flags*/
_Bool FLAG[10];


_Bool ModuleInit()
{
	/* AXIS X */
	machine.axis[0].drive.m_pulse_port 		= GPIOD;
	machine.axis[0].drive.m_pulse_pin		= GPIO_PIN_11;
	machine.axis[0].drive.m_dir_port		= GPIOD;
	machine.axis[0].drive.m_dir_pin	 		= GPIO_PIN_9;
	machine.axis[0].drive.m_en_port 		= GPIOD;
	machine.axis[0].drive.m_en_pin			= GPIO_PIN_14;
	/****************************/
	machine.axis[0].sw_key.m_sw_k_port		= GPIOD;
	machine.axis[0].sw_key.m_sw_k_pin		= GPIO_PIN_6;
	/****************************/

	machine.axis[0].c_curve.counter 		= 0;
	machine.axis[0].c_curve.target_counter 	= 0;
	machine.axis[0].c_curve.tgl_up	 		= 0;
	machine.axis[0].c_curve.enabled 		= false;
	machine.axis[0].sw_key.sw_k_enabled		= true;
	/****************************/
	/* AXIS Y */
	machine.axis[1].drive.m_pulse_port 		= GPIOD;
	machine.axis[1].drive.m_pulse_pin		= GPIO_PIN_13;
	machine.axis[1].drive.m_dir_port		= GPIOD;
	machine.axis[1].drive.m_dir_pin	 		= GPIO_PIN_12;
	machine.axis[1].drive.m_en_port 		= GPIOD;
	machine.axis[1].drive.m_en_pin			= GPIO_PIN_15;
	/****************************/
	machine.axis[1].sw_key.m_sw_k_port		= GPIOD;
	machine.axis[1].sw_key.m_sw_k_pin		= GPIO_PIN_7;
	/****************************/

	machine.axis[1].c_curve.counter 		= 0;
	machine.axis[1].c_curve.target_counter 	= 0;
	machine.axis[1].c_curve.tgl_up	 		= 0;
	machine.axis[1].c_curve.enabled 		= false;
	machine.axis[1].sw_key.sw_k_enabled		= true;
	/****************************/
//	/* AXIS Z */
//	machine.axis[2].drive.m_pulse_port 		= GPIOD;
//	machine.axis[2].drive.m_pulse_pin		= GPIO_PIN_13;
//	machine.axis[2].drive.m_dir_port		= GPIOD;
//	machine.axis[2].drive.m_dir_pin	 		= GPIO_PIN_12;
//	machine.axis[2].drive.m_en_port 		= GPIOD;
//	machine.axis[2].drive.m_en_pin			= GPIO_PIN_15;
//	/****************************/
//	machine.axis[2].sw_key.m_sw_k_port		= GPIOD;
//	machine.axis[2].sw_key.m_sw_k_pin		= GPIO_PIN_7;
//	/****************************/
//
//	machine.axis[2].c_curve.counter 		= 0;
//	machine.axis[2].c_curve.target_counter 	= 0;
//	machine.axis[2].c_curve.tgl_up	 		= 0;
//	machine.axis[2].c_curve.enabled 		= false;
//	machine.axis[2].sw_key.sw_k_enabled		= true;
//	/****************************/

	machine.head.LR_port					= GPIOD;
	machine.head.LR_pin						= GPIO_PIN_5;
	machine.head.LR_State					= false;

//	machine.COM_Param.X						= 0;
//	machine.COM_Param.Y						= 0;
//	machine.COM_Param.Z						= 0;
//	machine.COM_Param.F						= 0;
//	machine.COM_Param.S						= 0;


	/* Устанавливаем программное ограничение на размер рабочей области */
	MachineSetProgramLimit(&machine.axis[0], 0, MAX_TABLE_X);
	MachineSetProgramLimit(&machine.axis[1], 0, MAX_TABLE_Y);
//	MachineSetProgramLimit(&machine.axis[2], 0, MAX_TABLE_Z);

	Machine_Start_MainCounter();
	Machine_Start_SupCounter();

	LCD1602_Init();
//	FRESULT sd_state = SD_Mount("", 0);
//	if (sd_state == FR_OK) StartGCode("code.txt");

	GoHome(_ALL_AXISES);
	HAL_Delay(1000);

	return 0;
}
void ModuleLoop()
{
	while(1)
	{
		if (FLAG[0])
		{
			FLAG[0] = false;
		}
		if (FLAG[1])	/* Move on X */
		{
			FLAG[1] = false;
		}
		if (FLAG[2])
		{
			FLAG[2] = false;
		}
		if (FLAG[3])
		{

		}
		if (FLAG[4])
		{

		}
		if (FLAG[5])
		{
			FLAG[5] = false;
		}
		if (FLAG[6])
		{

		}
		if (FLAG[7])
		{

		}
	}

}

