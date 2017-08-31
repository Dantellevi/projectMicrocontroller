/*
 * USART.h
 *
 * Created: 29.12.2016 11:54:32
 *  Author: ��������� ��������� ���������
 */ 


#ifndef USART_H_
#define USART_H_

#define F_CPU 8000000UL
#include "Main.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#define  MAX_LINE_LENGHT 40


void USART_INIT(unsigned int baud);//�������������
void USART_putc(unsigned char data);//�������� �������
unsigned char USART_getc(void);//����� �������
void USART_Write(char *str1);//�������� ������
void USART_Write_Int(unsigned int val);//�������� ��������������
char *USART_readln(char *s);//������ ������
int CharToInt(char ch);//�������������� �� ������� � �����
void USART_Calculation(unsigned int l);//
void USART_waitEnter(char *msg,char k);//�������� ����� 



#endif /* USART_H_ */