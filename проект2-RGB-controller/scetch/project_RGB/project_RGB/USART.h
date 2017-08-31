/*
 * USART.h
 *
 * Created: 11.12.2016 16:26:38
 *  Author: DANTE_L_LEVI
 */ 


#ifndef USART_H_
#define USART_H_

#include "Main.h"

#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 8000000UL
#define  MAX_LINE_LENGHT 40
 void uart_init(unsigned int baud); 		 //������������� UART'a
 void uart_putc(unsigned char data);		 //�������� ������ �������
 unsigned char uart_getc (void);           //��������� ������ �������
 void uart_write (char *str);              //�������� ������
 void uart_write_int(unsigned int val);    //�������� ������ ����
 char *uart_readln(char *s);			     //������� ������ ������ (�������� - ��������� �� ������)
 int CharToInt(char ch);				     //����������� ����� (ASCII) � int ����������
 void uart_clr(unsigned int l);			 //������� l ��������
 void uart_wait(char *msg, char k);		//��������� ���� ������� �������


#endif /* USART_H_ */