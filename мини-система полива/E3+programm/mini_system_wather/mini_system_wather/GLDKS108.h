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


void LCDGotoXY(uint8_t,uint8_t);			             //������������� ������ � X, Y �������
void LCDdata(uint8_t);						             //������� 1 ������ �� �������.
void LCDdataXY(uint8_t,uint8_t,uint8_t);	             //������� 1 ������ �� ������� � X, Y ������� .
void LCDsendString(char*);                             //������� ������ �� �������
void LCDstringXY(char*,uint8_t,uint8_t);		             //������� ������ �� ������� � ������� x,y
void LCDstring_of_sramXY(uint8_t*,uint8_t,uint8_t);			 //������� ������ �� ������� � ������� x,y �� ���
void LCDstring_of_flashXY(const uint8_t*,uint8_t, uint8_t);//������� ������ � ������� x,y �� �����

void LCDinit(void);							//������������� LCD
void LCDblank(void);			//������� ��������� ���� �� �������
void LCDnblank(void);			//������� ������� ���� �� ������� + ���������� ������� ��������.
void LCDclear(void);			//�������� ������� �� ���� + ������ �� ������� 0,0
void LCDcursor_bl(void);		//�������� �������� ������
void LCDcursor_on(void);		//�������� �������������� ������
void LCDcursor_vi(void);		//�������� ��� �������
void LCDcursorOFF(void);		//��������� ������ (�����)
void LCDacr(void);				//C������ ������ AC ������ ����� ��������� �� n+1
void LCDacl(void);				//C������ ������ AC ������ ����� ��������� �� n-1
void LCDcursorl(void);			//�������� ������ ����� �� 1 ������
void LCDcursorr(void);			//�������� ������ ������ �� 1 ������
void LCDcursorln(uint8_t);		//�������� ������ ����� �� n ��������
void LCDcursorrn(uint8_t);		//�������� ������ ������ �� n ��������
void LCDscreenl(void);			//�������� ����� ����� �� 1 ������
void LCDscreenr(void);			//�������� ����� ������ �� 1 ������
void LCDscreenln(uint8_t);		//�������� ����� ����� �� n ��������
void LCDscreenrn(uint8_t);		//�������� ����� ������ �� n ��������
void LCDscreenL(void);			//� ������ ����� �������� ����� ����� ��������� �����
void LCDscreenR(void);			//� ������ ����� �������� ����� ����� ��������� ������
void LCDresshift(void);			//������ � ������� 0,0 + ����� ���� �������, ����������� ��������
void LCDstring_of_sram(uint8_t* data,uint8_t nBytes,uint8_t x, uint8_t y);
void PrintInt(int val);
#define LINE0 0x00
#define LINE1 0x40
#define LINE2 0x14
#define LINE3 0x54

#endif /* GLDKS108_H_ */