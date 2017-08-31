/*
 * GLDKS108.h
 *
 * Created: 03.04.2017 10:37:42
 *  Author: Dante_L_Levi
 */ 


#ifndef GLDKS108_H_
#define GLDKS108_H_


#include "Main.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>



#define DPIN PINB
#define DDDR DDRB
#define DPORT PORTB

#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7


#define CDDR DDRB
#define CPORT PORTB


#define RS 0
#define RW 1
#define E 2


void LCDGotoXY(uint8_t,uint8_t);			             //Устанавливаем курсор в X, Y позицию
void LCDdata(uint8_t);						             //Вывести 1 символ на дисплей.
void LCDdataXY(uint8_t,uint8_t,uint8_t);	             //Вывести 1 символ на дисплей в X, Y позицию .
void LCDsendString(char*);                             //Вывести строку на дисплей
void LCDstringXY(char*,uint8_t,uint8_t);		             //Вывести строку на дисплей в позицию x,y
void LCDstring_of_sramXY(uint8_t*,uint8_t,uint8_t);			 //Вывести строку на дисплей в позицию x,y из ОЗУ
void LCDstring_of_flashXY(const uint8_t*,uint8_t, uint8_t);//Вывести строку в позицию x,y из флеша

void LCDinit(void);							//Инициализация LCD
void LCDblank(void);			//Сделать невидимым инфо на дисплее
void LCDnblank(void);			//Сделать видимой инфо на дисплее + отключение видимых курсоров.
void LCDclear(void);			//Очистить дисплей от инфо + курсор на позицию 0,0
void LCDcursor_bl(void);		//Включить мигающий курсор
void LCDcursor_on(void);		//Включить подчеркивающий курсор
void LCDcursor_vi(void);		//Включить оба курсора
void LCDcursorOFF(void);		//Выключить курсор (любой)
void LCDacr(void);				//Cчетчик адреса AC всегда будет смещаться на n+1
void LCDacl(void);				//Cчетчик адреса AC всегда будет смещаться на n-1
void LCDcursorl(void);			//Сместить курсор влево на 1 символ
void LCDcursorr(void);			//Сместить курсор вправо на 1 символ
void LCDcursorln(uint8_t);		//Сместить курсор влево на n символов
void LCDcursorrn(uint8_t);		//Сместить курсор вправо на n символов
void LCDscreenl(void);			//Сместить экран влево на 1 символ
void LCDscreenr(void);			//Сместить экран вправо на 1 символ
void LCDscreenln(uint8_t);		//Сместить экран влево на n символов
void LCDscreenrn(uint8_t);		//Сместить экран вправо на n символов
void LCDscreenL(void);			//С каждым новым символом экран будет смещаться влево
void LCDscreenR(void);			//С каждым новым символом экран будет смещаться вправо
void LCDresshift(void);			//Курсор в позицию 0,0 + сброс всех сдвигов, изображение остается
void LCDstring_of_sram(uint8_t* data,uint8_t nBytes,uint8_t x, uint8_t y);
void PrintInt(int val);
#define LINE0 0x00
#define LINE1 0x40
#define LINE2 0x14
#define LINE3 0x54

#endif /* GLDKS108_H_ */