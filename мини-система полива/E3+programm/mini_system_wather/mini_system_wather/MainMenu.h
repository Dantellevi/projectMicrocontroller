/*
 * MainMenu.h
 *
 * Created: 27.04.2017 15:10:24
 *  Author: Dante_L_Levi
 */ 


#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include <avr/eeprom.h>

enum{
	
	
	Menu_Mode1=1,
	Menu_Mode2,
	Menu_Mode3,
	Menu_Mode4,
	Menu_Mode5,
	Menu_timeMode3,
	Menu_settings_Time,
	Menu_Zone1,
	Menu_Zone2
	
	
	
	};

uint8_t startMenu();
void initMenu();


#endif /* MAINMENU_H_ */