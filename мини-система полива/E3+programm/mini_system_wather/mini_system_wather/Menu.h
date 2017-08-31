/*
 * Menu.h
 *
 * Created: 03.05.2017 9:41:53
 *  Author: Dante_L_Levi
 */ 


#ifndef MENU_H_
#define MENU_H_

//+++++++++++++++++++++++++
#include "Main.h"
#include "KeyEVENTS.h"
#include "GLDKS108.h"
#include "ADC.h"
#include "I2C.h"
#include "Convertds1307.h"

#include <avr/eeprom.h>
//+++++++++++++++++++++++++
typedef enum{
	
	MENU_STATE_IDLE=0,
	MENU_STATE_WAIT,
	MENU_STATE_MAIN
	
}Menu_StateTypeDef;
//+++++++++++++++++++++++++

typedef enum{
	
	MAIN_MENU_STATE_IDLE=0,
	MAIN_MENU_STATE_WAIT,
	MAIN_MENU_STATE_Menu1_Auto,
	MAIN_MENU_STATE_Menu2_Manual,
	MAIN_MENU_STATE_Menu3_PC_Android,
	MAIN_MENU_STATE_Menu4_Settings,
	MAIN_MENU_STATE_EXIT,
	MAIN_MENU_STATE_Menu1_Auto_WAIT,
	MAIN_MENU_STATE_Menu2_Manual_WAIT,
	MAIN_MENU_STATE_Menu3_PC_Android_WAIT,
	MAIN_MENU_STATE_Menu4_Settings_WAIT,
	MAIN_MENU_STATE_EXIT_WAIT
	
}MAIN_MENU_StateTypeDef;

//+++++++++++++++++++++++++++
typedef enum
{
	MENU_SETTINGS_STATE_IDLE=0,
	MENU_SETTINGS_STATE_WAIT,
	MENU_SETTINGS_Menu_Zone_WAIT,
	MENU_SETTINGS_Menu_Zone,
	MENU_SETTINGS_Menu_Time_WAIT,
	MENU_SETTINGS_Menu_Time,
	MENU_NULL
}MENU_SETTINGS_StateTypeDef;

//+++++++++++++++++++++++++++
typedef enum
{
	MENU_SET_Time_IDLE=0,
	MENU_SET_Time_WAIT,
	MENU_SET_Time_TimeDateSetting_WAIT,
	MENU_SET_Time_TimeDateSetting,
	MENU_SET_Time_TimecontrolSetting_WAIT,
	MENU_SET_Time_TimecontrolSetting,
	Menu_Time_Null
	
	}MENU_SET_Time_Typedef;

//++++++++++++++++++++++++++++

//Control Load
//--------------------------------
#define Load1 5
#define Load2 6
#define Load3 7
#define Load4 2
//--------------------------------

#define ONL(x,y) (x|=(1<<y))
#define OFFL(x,y) (x&=~(1<<y))

//--------------------------------
#define ON 1
#define OFF 0

//--------------------------------
#define Zone1 1
#define Zone2 2


//--------------------------------

void MenuProcess(void);


#endif /* MENU_H_ */