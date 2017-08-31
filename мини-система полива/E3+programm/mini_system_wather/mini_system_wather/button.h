/*
 * button.h
 *
 * Created: 14.04.2017 16:47:41
 *  Author: Dante_L_Levi
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "Main.h"
#include "ADC.h"

unsigned char button_state[5];

#define  Button_Right 0x00
#define  Button_Up 0x01
#define  Button_Down 0x02
#define  Button_Left 0x03
#define  Button_Select 0x04

#define ST_PRESSED 0b00000001
#define ST_UNPRESSED 0b00000010
#define ST_ERROR 0b00000100
#define ST_PRESSURE 0b00001000
#define ST_UNPRESSURE 0b00010000
#define ST_LOCKED 0b00100000


void Button_ini(void);
void ResetButtonState(unsigned char b, unsigned char st);
void SetButtonState(unsigned char b, unsigned char st);


#endif /* BUTTON_H_ */