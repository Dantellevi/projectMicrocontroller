#ifndef MAIN_H_
#define MAIN_H_
#define  F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUD    2400
#define UBRR_VAL    F_CPU/16/BAUD-1

//Определение ножки Echo
#define Echo_Port PORTD
#define Echo_ddr DDRD
#define  Echo_Pin PIND
#define Echo_N 2

//Определяем ножку Trig
#define Trig_Port PORTD
#define Trig_DDr DDRD
#define Trig_Pin PIND
#define Trig_N 7



#include "UART.h"



#endif /* MAIN_H_ */