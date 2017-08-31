
#ifndef USART_H_
#define USART_H_

#define F_CPU 8000000UL
#include "Main.h"
#include <stdlib.h>
#include <stdio.h>
#define  MAX_LINE_LENGHT 40


void USART0_INIT(unsigned int baud);//функция инициализации USART0-канала
void USART0_puts(unsigned char data);//функция передачи данных(символа) USART0-канала
void USART0_putsString(char *str1);//функция передачи данных(строки)USART0-канала
void USART0_putsInt(unsigned int val);//функция передачи данных целочисленной переменной USART0-канал
void USART2_INIT(unsigned int baud);//функция инициализации USART2-канала
void USART2_puts(unsigned char data);//функция передачи данных(символа)USART2-канала
void USART2_putsString(char *str1);//функция передачи строки канал USART2
void USART2_putsInt(unsigned int val);//функция передачи целочисленной переменной по каналу USART2





#endif /* USART_H_ */