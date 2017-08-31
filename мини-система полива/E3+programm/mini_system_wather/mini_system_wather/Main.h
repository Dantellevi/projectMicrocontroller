/*
 * Main.h
 *
 * Created: 03.04.2017 10:35:52
 *  Author: Dante_L_Levi
 */ 


#ifndef MAIN_H_
#define MAIN_H_
#define F_CPU 8000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include "ADC.h"
#include "USART.h"
#include "GLDKS108.h"
#include "Servo.h"
#include "I2C.h"
#include "Convertds1307.h"
#include "KeyEVENTS.h"
#include "Menu.h"


void Clockds_USART(void);




#endif /* MAIN_H_ */