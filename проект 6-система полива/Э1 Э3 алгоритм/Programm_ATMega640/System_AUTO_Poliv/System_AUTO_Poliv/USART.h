
#ifndef USART_H_
#define USART_H_

#define F_CPU 8000000UL
#include "Main.h"
#include <stdlib.h>
#include <stdio.h>
#define  MAX_LINE_LENGHT 40


void USART0_INIT(unsigned int baud);//������� ������������� USART0-������
void USART0_puts(unsigned char data);//������� �������� ������(�������) USART0-������
void USART0_putsString(char *str1);//������� �������� ������(������)USART0-������
void USART0_putsInt(unsigned int val);//������� �������� ������ ������������� ���������� USART0-�����
void USART2_INIT(unsigned int baud);//������� ������������� USART2-������
void USART2_puts(unsigned char data);//������� �������� ������(�������)USART2-������
void USART2_putsString(char *str1);//������� �������� ������ ����� USART2
void USART2_putsInt(unsigned int val);//������� �������� ������������� ���������� �� ������ USART2





#endif /* USART_H_ */