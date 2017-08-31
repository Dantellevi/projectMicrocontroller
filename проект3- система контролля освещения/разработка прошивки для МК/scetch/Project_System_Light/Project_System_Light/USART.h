/*
 * USART.h
 *
 * Created: 29.12.2016 11:54:32
 *  Author: Лепотенко Александр Сергеевич
 */ 


#ifndef USART_H_
#define USART_H_

#define F_CPU 8000000UL
#include "Main.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#define  MAX_LINE_LENGHT 40


void USART_INIT(unsigned int baud);//инициализация
void USART_putc(unsigned char data);//передача символа
unsigned char USART_getc(void);//прием символа
void USART_Write(char *str1);//передача строки
void USART_Write_Int(unsigned int val);//передача целочисленного
char *USART_readln(char *s);//чтение строки
int CharToInt(char ch);//преобразование из символа в число
void USART_Calculation(unsigned int l);//
void USART_waitEnter(char *msg,char k);//ожидание ввода 



#endif /* USART_H_ */