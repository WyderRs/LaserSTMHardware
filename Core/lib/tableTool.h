/*
 * DriverLib.h
 *
 *  Created on: Aug 10, 2026
 *      Author: roman
 */

#ifndef LIB_TABLETOOL_H_
#define LIB_TABLETOOL_H_

#include "stm32f1xx.h"
#include <math.h>
#include <stdlib.h>

#include "g_code.h"

/* Step to home positions */
#define HOME_OFFSET			10	// 10 mm
#define DRV_DIVIDER			16
/* Максимальные размеры стола станка */
#define MAX_TABLE_X			185
#define MAX_TABLE_Y			205
#define MAX_TABLE_Z			55
/* Максимальная/минимальная скорость */
#define MAX_SPEED   		30.0f     	// mm/s
#define MIN_SPEED			0.1f   		// mm/s
/* Минимальная и максимальная мощность лазера (частота импульсов) */
#define MAX_LR_POWER		0
#define MIN_LR_POWER		0

#define VP_ENABLE_PORT		GPIOB
#define VP_ENABLE_PIN		GPIO_PIN_11

#define LED_AUTO_OP_ON		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET)
#define LED_AUTO_OP_OFF		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET)
#define LED_AUTO_OP_TGL		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_15)

#define LED_FREE_OP_ON		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET)
#define LED_FREE_OP_OFF		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET)
#define LED_FREE_OP_TGL		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_14)

#define LED_ERR_OP_ON		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)
#define LED_ERR_OP_OFF		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)
#define LED_ERR_OP_TGL		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13)

#define CULLER_ON			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET)
#define CULLER_OFF			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET)





//typedef enum AxisTaskState_t {
//	noUse = 0,
//	Progress,
//	Ended,
//} AxisTaskState_t;
//

//typedef enum state_work_t {
//	tNoInit = 0,
//	tReady,
//	tBusy,
//	tWAIT,
//	tWork,
//	tAutoMove,
//} state_work_t;

//typedef enum Coord_ax {
//	x = 0,
//	y,
//	z,
//	all,
//} Coord_ax;
//typedef enum WorkMode_t {
//	Hand_Mode = 0,
//	USB_Mode,
//	SD_Mode,
//} WorkMode_t;
//
//typedef struct Point_t{
//	float x;
//	float y;
//	float z;
//} Point_t;
//
//
///* Type definition axis struct */
//typedef struct tAxis_t {
//	GPIO_TypeDef	*port_dir;			// dir_port
//	uint32_t 		pin_dir;			// dir_pin
//	GPIO_TypeDef	*port_en;			// en_port
//	uint32_t 		pin_en;				// en_pin
//	GPIO_TypeDef	*port_pulse;		// pulse_port
//	uint32_t 		pin_pulse;			// pulse_pin
//	GPIO_TypeDef	*port_SW;			// switch_port
//	uint32_t 		pin_SW;				// switch_pin
//	 _Bool  		state_SW;			// state_sw
//
//
//	uint32_t		counter;			// counter
//	uint32_t		tgl;				// point of reverse state
//	side_t			direction;			// direction of side for rotate
//	float 			current_pos_coord;	// current position of this coordinate axis
//	uint32_t		current_cnt;		// current position of this axis
//	state_en_t		enable;				// enable axis
//
//
//	AxisTaskState_t	task_state;			// current state task resolving
//	float 			target_pos_coord;	// target position of this coordinate axis
//	float			installed_speed_mm;	// current speed in mm
//} tAxis_t;
//
//
//typedef struct ToolHead_Typedef {
//	tAxis_t 		tAxis[3];		/* x, y, z */
//
////	Point_t			corrent_point;	// current position
////	Point_t			target_point;	// target point for moving
//} ToolHead_Typedef;
//
//typedef struct ToolLaser_Typedef {
//	GPIO_TypeDef	*port;			// port
//	uint32_t 		pin;			// pin
//} ToolLaser_Typedef;
//typedef struct ToolCuller_Typedef {
//	GPIO_TypeDef	*port;			// port
//	uint32_t 		pin;			// pin
//} ToolCuller_Typedef;
//typedef struct Settings_t {
//	uint16_t		pulsesOneTurnOver;  // pulses per one turnover 	(pulse)
//	float			stpLineValue;		// step value for one pulse (mm)
//
//	float			speed;				// mm
//} Settings_t;
//typedef enum VCP_State_t {
//	Disconnect 	= 0,
//	Connect 	= 1,
//} VCP_State_t;
//typedef enum GCode_Mode_t {
//	G0_Mode = 0,
//	G1_Mode,
//	G2_Mode,
//	G3_Mode,
//} GCode_Mode_t;
//typedef struct VCP_Config_t {
//	_Bool 		VCP_FlagGetData; 		// notification flag of data is received
//	VCP_State_t VCP_State;				// USB_State
//	uint8_t 	VCP_data[1000];			// Received data
//	uint8_t 	VCP_Data_one_byte;		// Received last byte
//	uint16_t 	VCP_Data_counter;		// Received data count
//	_Bool		VCP_command_IsReceived; // Command received notification
//	uint32_t 	VCP_cnt_last_file;		// Count last file data
//} VCP_Config_t;
//typedef struct Encoder_t {
//	GPIO_TypeDef	*port1;			// port1
//	uint32_t 		pin1;			// pin1
//	GPIO_TypeDef	*port2;			// port2
//	uint32_t 		pin2;			// pin2
//	GPIO_TypeDef	*Button_port;	// button port
//	uint32_t 		Button_pin;		// button pin
//	_Bool			Button_state;	// button state
//
//
//	uint16_t 		count_last_rotate; 		// Last count of pulses
//	side_t 			current_rotate_side; 	// It for indicate side of rotate
//} Encoder_t;
//typedef struct Tool_Typedef {
//	ToolHead_Typedef 	head;			// main work tool
//	state_work_t		state;			// state of the work
//
//	ToolLaser_Typedef	laser;			// laser instance
//	ToolCuller_Typedef	culler;			// Culler instance
//
//	Settings_t			Settings;		// Global machine settings
//	VCP_Config_t		VCP_Config;		// VCP communication config
//	Encoder_t			Encoder;		// Encoder instance
//
//	WorkMode_t			WorkMode;		// Tool work mode
//	GCode_Mode_t		GCode_Status;	// Current GCODE Mode (G0, G1, G2, G3)
//} Tool_Typedef;


//===============================================================================================//

//void tInit(void);
//void tHome(void);
//void tHomeAxis(tAxis_t *ax);
//void tAxisEN(tAxis_t *ax, state_en_t st, state_en_t stateDrv); // st -> calculate, stateDrv -> driver
//void tDriverSetDir(tAxis_t *ax, side_t sd);
//void tLaserEN(state_en_t st);
//void tToolSetState(state_work_t st);
//void tMoveRelative(float x, float y, float z);		// Move from current position
//void tMoveGlobal(float x, float y, float z);		// Move from zero position
//void tMoveRelative_A(float x, float y, float z);		// Move from current position auto
//void tMove_SetOrigin(void);
//void tMoveSetSpeed(float sp);
//void tMoveAdjustmentSpeed(tAxis_t* ax, float sp);
//void tCheckEvent(void);								// For checking state machine
//
//void tbDriver(state_en_t st);						// Driver enable
//void tbMove(float tx, float ty, float tz);			// Go to move to point
//VCP_State_t tVCP_Check();
//void tGSetMode(GCode_Mode_t mode);					// Set G-code mode
//void tVCP_Command(uint32_t bytes);




/*******************/
/* Hardware parameters */
#define 				BASE_PSC		72			// const
#define 				MAX_Frequency	10000 		// Hz
#define 				MIN_Frequency	1 			// Hz
#define					ACCURACY		0.00125f 	// mm
#define					SCREW_STEP 		4.0f		// mm
#define					MOTOR_STEP 		1.8f		// mm
#define 				DRIVER_DEVIDER	16			// const
#define 				MIN_FEEDRATE	0.00125f	// mm/s
#define 				MAX_FEEDRATE	12.5f		// mm/s
/*******************/
/* Programm parameters */
#define					MODE_G0_FEEDRATE	10.0f	// mm/s

/*******************/
typedef enum GMode_t {
	_G0_mode = 0,				/* Fast positioning */
	_G1_mode,					/* Linear interpolation */
	_G2_mode,					/* Circlular interpolation clockwise */
	_G3_mode,					/* Circlular interpolation back clockwise*/
} GMode_t;
typedef enum state_en_t {
	OFF = 0,
	ON 	= 1,
} state_en_t;
typedef enum side_t {
	Forward = 0,
	BackForward,
} side_t;
typedef struct ToolLaser_Typedef {
	GPIO_TypeDef		*port;					// port
	uint32_t 			pin;					// pin

	uint32_t			timer_channel;			// pulse channel of timer
	TIM_HandleTypeDef	*timer;					// timer
	state_en_t			enable_channel;			// enable channel

} ToolLaser_Typedef;
typedef struct ToolCuller_Typedef {
	GPIO_TypeDef	*port;			// port
	uint32_t 		pin;			// pin
} ToolCuller_Typedef;
typedef struct Encoder_t {
	GPIO_TypeDef		*port1;					// port1
	uint32_t 			pin1;					// pin1
	GPIO_TypeDef		*port2;					// port2
	uint32_t 			pin2;					// pin2
	GPIO_TypeDef		*Button_port;			// button port
	uint32_t 			Button_pin;				// button pin
	_Bool				Button_state;			// button state


	uint16_t 			count_last_rotate; 		// Last count of pulses
	side_t 				current_rotate_side; 	// It for indicate side of rotate
} Encoder_t;
typedef struct tAxis_t {
	GPIO_TypeDef		*port_dir;			// dir_port
	uint32_t 			pin_dir;			// dir_pin
	GPIO_TypeDef		*port_en;			// en_port
	uint32_t 			pin_en;				// en_pin
	GPIO_TypeDef		*port_SW;			// switch_port
	uint32_t 			pin_SW;				// switch_pin
	_Bool  				state_SW;			// state_sw
	/**********/
	uint32_t			timer_channel;		// pulse channel of timer
	TIM_HandleTypeDef	*timer;				// timer
	state_en_t			enable_channel;		// enable channel
	/**********/
	uint32_t			pulse_counter;		// counter
	side_t				direction;			// direction of side for rotate
	/**********/
	float				installed_speed_mm;	// current speed in mm
	float 				cpc;				// current position of this coordinate axis
	/**********/
} tAxis_t;
typedef struct ToolHead_Typedef {
	tAxis_t 			tAxis[3];		/* x, y, z */

	float 	Feed;

} ToolHead_Typedef;
typedef struct Tool_Typedef {
	GMode_t 			GMode;
	ToolHead_Typedef 	head;
	Encoder_t			Encoder;
	ToolLaser_Typedef	laser;
	ToolCuller_Typedef	culler;





} Tool_Typedef;


/*******************/
void tInit(void);										/* Init device 	*/
void tToolAxisEN(tAxis_t *ax, state_en_t st); 			/* Set state axis */
void tToolAxisWork(tAxis_t *ax, state_en_t st);			/* Axis moving is started or stoped*/
void tToolAxisDiraction(tAxis_t *ax, side_t side);		/* Set direction for axis */
void tToolFeedrate(float feedrate); 	/* Set feedrate */
void tHome(void);										/* Go home 		*/
void tMode(GMode_t gm);									/* Enter g-mode */
void tMove(float x, float y, float z);					/* Move to target position from the current position */


void tToolPerformTimerEN(state_en_t st);				/* Timer to perform */









#endif /* LIB_TABLETOOL_H_ */
