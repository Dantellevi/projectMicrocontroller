/*
 * I2C.c
 *
 * Created: 30.12.2016 8:20:23
 *  Author: ��������� ��������� ���������
 */ 


 #include "I2C.h"

 void Init_I2C(void)
 {
 TWBR=0x20;//�������� �������� ���������� 100���


 }

 void Start_I2C(void)
 {

 TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//������ ��������
 while(!(TWCR&(1<<TWINT)));//�������� ��������� �����

 }

 void Stop_I2C(void)
 {

 TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//����� ��������

 }

 void Sendbyte_I2C(unsigned char data)
 {

 TWDR=data;//�������� ������ � ������� ������
 TWCR=(1<<TWINT)|(1<<TWEN);//��������� ������ ��� ��������� ������ � �������
 while(!(TWCR&(1<<TWINT)));//�������� ��������� ������

 }

 void SendByte_Addr(unsigned char data, unsigned char Adress)
 {

 Start_I2C();//������ ��������
 Sendbyte_I2C(Adress);//� ������� ������ �������� �����
 Sendbyte_I2C(data);//� ������� �������� ������
 Stop_I2C();//����� ��������

 }

 unsigned char Readbyte_I2C(void)
 {

 TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//��������� ������ �� ������
 while(!(TWCR&(1<<TWINT)));//������� 
 return TWDR;//�������� ������ �� �������� 
 }

 unsigned char ReadLast_byte(void)
 {
 TWCR=(1<<TWINT)|(1<<TWEA);//��������� ������ �� ������
 while(!(TWCR&(1<<TWINT)));//������� 
 return TWDR;//�������� ������ �� ��������

 }