/*
 * ������� ���������� ����������
 *
 * Created: 29.12.2016 11:50:16
 * Author : ��������� ��������� ���������
 end:	06.01.2017
 Refactor:
 */ 

#include "Main.h"

int second=0;//�������
int minuts=0;//������
int house=0;//����
int day=0;//���� ������
int data_d=0;//����
int month=0;//�����
int year=0;//���

unsigned char count_main_led=0;

//���������� ��� ������ ���������

unsigned char count_adjust_work1=0;
unsigned char count_adjust_work2=0;
unsigned char count_adjust_work3=0;
unsigned char count_adjust_work4=0;

unsigned char flag_adjust_work1=0;
unsigned char flag_adjust_work2=0;
unsigned char flag_adjust_work3=0;
unsigned char flag_adjust_work4=0;

unsigned char flag_del=0;
unsigned char flg_control_USART=0;
ISR(USART_RXC_vect)//���������� �� ������� ������ �� USART
{

flg_control_USART=UDR;

}

void Port_init(void)//������������� ������ �����/������
{
DDRA&=~(1<<PA0);//��� 0 ����� � �� ���� ��� �������
DDRA|=(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7);//���� � 1-7 �� ����� ��� LCD �������

PORTA|=(1<<PA0);//������������� ������� �������
PORTA&=~((1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7));//������������� ������ �������



DDRC|=(1<<PC7)|(1<<PC6)|(1<<PC5)|(1<<PC4)|(1<<PC3);//��� � 3-7 ����� � �� ����� ��� ��������� ������ ��������
PORTC&=~((1<<PC7)|(1<<PC6)|(1<<PC5)|(1<<PC4)|(1<<PC3));//������������� ������ ���. ������� � 3 �� 7 ��� ����� �


DDRB&=~(1<<PB4);//���� � ��� 4 �� ����
PORTB|=(1<<PB4);//������� �������
DDRB&=~(1<<PB3);//���� � ��� 3 �� ����
PORTB|=(1<<PB3);//������� �������
DDRB&=~(1<<PB2);//���� � ��� 2 �� ����
PORTB|=(1<<PB2);//������� �������
DDRB&=~(1<<PB1);//���� � ��� 1 �� ����
PORTB|=(1<<PB1);//������� �������
DDRB&=~(1<<PB0);//���� � ��� 0 �� ����
PORTB|=(1<<PB0);//������� �������

DDRD|=(1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD5);//���� � ��� � 2-5 �� �����
PORTD&=~((1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD5));//������ �������


}

void Auto_Mode_On_Nag(unsigned char flag_delay)//������� ��������� ������� � PIR-�������
{


if (flag_delay==1)//���� ������ �������� �������� ������ ��������
{
	PORTD|=(1<<PD2);
PORTC|=(1<<PC6);

}
else{//���������� �������� � ��������� � 1�.

_delay_ms(1000);
PORTD&=~(1<<PD2);
PORTC&=~(1<<PC6);
}

}

void Nagruzka(unsigned char flag1,unsigned char flag2,unsigned char flag3,unsigned char flag4, unsigned char count1,unsigned char count2,unsigned char count3,unsigned char count4)//������� ���������� ���������� � ������ ������
{

if (flag1==1 && count1==1)//��������� ������ ��������
{

USART_Write("WOrk Nagruzka ON-1");
USART_putc(0x0d);
USART_putc(0x0a);
PORTD|=(1<<PD2);
PORTC|=(1<<PC6);

}
else if (flag1==1 && count1==2)
{

USART_Write("WOrk Nagruzka OFF-1");//���������� ������ ��������
USART_putc(0x0d);
USART_putc(0x0a);
PORTD&=~(1<<PD2);
PORTC&=~(1<<PC6);
}


if (flag2==2 && count2==1)
{

USART_Write("WOrk Nagruzka ON-2");//��������� ������ ��������
USART_putc(0x0d);
USART_putc(0x0a);
	PORTD|=(1<<PD3);
	PORTC|=(1<<PC5);
}
else if (flag2==2 && count2==2)
{

USART_Write("WOrk Nagruzka OFF-2");//���������� ������ ��������
USART_putc(0x0d);
USART_putc(0x0a);
	PORTD&=~(1<<PD3);
	PORTC&=~(1<<PC5);
}


if (flag3==3 &&count3==1)
{

USART_Write("WOrk Nagruzka ON-3");//��������� 3-�� ��������
USART_putc(0x0d);
USART_putc(0x0a);
	PORTD|=(1<<PD4);
	PORTC|=(1<<PC4);
}
else if (flag3==3 &&count3==2)
{

USART_Write("WOrk Nagruzka OFF-3");//���������� 3-�� ��������
USART_putc(0x0d);
USART_putc(0x0a);
	PORTD&=~(1<<PD4);
	PORTC&=~(1<<PC4);
}

if (flag4==4 &&count4==1)
{
USART_Write("WOrk Nagruzka ON-4");//��������� 4-�� ��������
	USART_putc(0x0d);
	USART_putc(0x0a);
	PORTD|=(1<<PD5);
	PORTC|=(1<<PC3);
}
else if (flag4==4 &&count4==2)
{
USART_Write("WOrk Nagruzka OFF-4");//���������� 4-�� ��������
USART_putc(0x0d);
USART_putc(0x0a);
	PORTD&=~(1<<PD5);
	PORTC&=~(1<<PC3);
}




}

void Main_Led_indicate(unsigned char flag_Main_led)//��������� ������ ������ �������
{

switch(flag_Main_led)
{

case 1:{		

LCDGotoXY(2,0);
LCDsendString("Adjust Settings");
_delay_ms(100);

break;}


case 2:{
LCDGotoXY(2,0);
LCDsendString("Auto-PIR Sensor");
_delay_ms(100);
	break;}


case 3:{
LCDGotoXY(4,0);
LCDsendString("Sleep Mode!!!");
_delay_ms(100);
PORTC|=(1<<PC7);
	break;}


case 4:{	
LCDGotoXY(4,0);
LCDsendString("OFF System");
_delay_ms(400);break;PORTC&=~(1<<PC7);}

case 5:{
LCDGotoXY(5,0);	
LCDsendString("Control PC");
PORTC|=(1<<PC7);
_delay_ms(400);
break;}

default:{

flag_Main_led=1;

}

}

}


void Clocck_RTC_ds1307(void)//������� ����������� ������� ������� �� ���������� ds1307
{
SendByte_Addr(0,0b11010000);
_delay_ms(300);
Start_I2C();

Sendbyte_I2C(0b11010001);
second=Readbyte_I2C();
minuts=Readbyte_I2C();
house=Readbyte_I2C();
day=Readbyte_I2C();
data_d=Readbyte_I2C();
month=Readbyte_I2C();
year=Readbyte_I2C();
Stop_I2C();
second=RTC_ConvertDEC(second);
minuts=RTC_ConvertDEC(minuts);
house=RTC_ConvertDEC(house);
day=RTC_ConvertDEC(day);
data_d=RTC_ConvertDEC(data_d);
month=RTC_ConvertDEC(month);
year=RTC_ConvertDEC(year);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++
//=====================================================


USART_putc(0x0d);
USART_putc(0x0a);
USART_putc(data_d/10+0x30);//����������� ����� � ��� �����
USART_putc(data_d%10+0x30);//����������� ����� � ��� �����
USART_putc('.');
USART_putc(month/10+0x30);//����������� ����� � ��� �����
USART_putc(month%10+0x30);//����������� ����� � ��� �����
USART_putc('.');
USART_putc(year/10+0x30);//����������� ����� � ��� �����
USART_putc(year%10+0x30);//����������� ����� � ��� �����
USART_putc('.');
USART_putc('.');
USART_putc('.');
USART_putc('.');
USART_putc('.');
USART_putc(day+0x30);
USART_putc('.');
USART_putc('.');
USART_putc('.');
USART_putc(house/10+0x30);//����������� ����� � ��� �����
USART_putc(house%10+0x30);
USART_putc(':');
USART_putc(minuts/10+0x30);//����������� ����� � ��� �����
USART_putc(minuts%10+0x30);
USART_putc(':');
USART_putc(second/10+0x30);//����������� ����� � ��� �����
USART_putc(second%10+0x30);
USART_putc(0x0d);
USART_putc(0x0a);


}

void USART_Control(unsigned char flag)//������� ����������� ���������� ����� USART-���������
{

switch(flag)
{
//�������� ������ ��������
case 'Q':{LCDGotoXY(5,3);
	LCDsendString("On-1 load");PORTD|=(1<<PD2);PORTC|=(1<<PC6);   break;}
case 'q':{ LCDGotoXY(5,3);
	LCDsendString("OFF-1 load");PORTD&=~(1<<PD2);PORTC&=~(1<<PC6);  break;}//��������� ������ ��������

case 'W':{ LCDGotoXY(5,3);
	LCDsendString("On-2 load");PORTD|=(1<<PD3);PORTC|=(1<<PC5);  break;}//�������� 2-�� ��������
case 'w':{ LCDGotoXY(5,3);
	LCDsendString("OFF-2 load");PORTD&=~(1<<PD3);PORTC&=~(1<<PC5);  break;}//��������� 2-�� ��������

case 'E':{ LCDGotoXY(5,3);
	LCDsendString("On-3 load");PORTD|=(1<<PD4);PORTC|=(1<<PC4);  break;}//�������� 3-� ��������
case 'e':{ LCDGotoXY(5,3);
	LCDsendString("OFF-3 load");PORTD&=~(1<<PD4);PORTC&=~(1<<PC4);  break;}//��������� 3-� ��������

case 'R':{LCDGotoXY(5,3);
	LCDsendString("On-4 load");PORTD|=(1<<PD5); PORTC|=(1<<PC3);  break;}//�������� 4-� ��������
case 'r':{ LCDGotoXY(5,3);
	LCDsendString("OFF-4 load");PORTD&=~(1<<PD5);PORTC&=~(1<<PC3);  break;}//��������� 4-� ��������

case 'A':{ LCDGotoXY(5,3);
	LCDsendString("On-ALL load");PORTD|=(1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD5); 
	PORTC|=(1<<PC3)|(1<<PC4)|(1<<PC5)|(1<<PC6);
	 break;}//��� �������� ��������
case 'a':{LCDGotoXY(5,3);
	LCDsendString("OFF-ALL load");PORTD&=~((1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD5));
	PORTC&=~((1<<PC3)|(1<<PC4)|(1<<PC5)|(1<<PC6));
	   break;}//��� ���������

	default:LCDGotoXY(5,3);
	LCDsendString("Wait INPUT!!");
}


}

int main(void)
{
	Port_init();


   USART_INIT(9600);
   LCDinit();
   USART_Write("Work Baud=9600!!");
   USART_putc(0x0d);
   USART_putc(0x0a);
   sei();
   Init_I2C();
   Clocck_RTC_ds1307();
  
   PORTC|=(1<<PC7);
   
    while (1) 
    {
	
	LCDGotoXY(8,2);
	LCD_write_int(house);
	LCDdata(':');
	LCD_write_int(minuts);
	LCDdata(':');
	LCD_write_int(second);

	if (!(PINB&(1<<PB4)))
	{

	_delay_ms(200);
	//����� ������ ���������� ��� ������������ ������ ������
	 count_adjust_work1=0;
	 count_adjust_work2=0;
	 count_adjust_work3=0;
	count_adjust_work4=0;

	 flag_adjust_work1=0;
	flag_adjust_work2=0;
	 flag_adjust_work3=0;
	flag_adjust_work4=0;
//����� ����� �������� ��������
	PORTD&=~(1<<PD2);
	PORTD&=~(1<<PD3);
	PORTD&=~(1<<PD4);
	PORTD&=~(1<<PD5);
//����� ����� �������� ���������
	PORTC&=~(1<<PC6);
	PORTC&=~(1<<PC5);
	PORTC&=~(1<<PC4);
	PORTC&=~(1<<PC3);
	//������� ������ ������ �������
	count_main_led++;

	}

	Main_Led_indicate(count_main_led);
	_delay_ms(300);
	LCDclear();
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
	if (count_main_led==1)//������ ���������� ����������
	{
	LCDGotoXY(8,2);
	LCD_write_int(house);
	LCDdata(':');
	LCD_write_int(minuts);
	LCDdata(':');
	LCD_write_int(second);
	

flag_del=0;
		if (!(PINB&(1<<PB0)))
		{
		_delay_ms(200);

		flag_adjust_work1=1;
		count_adjust_work1+=1;
		if (count_adjust_work1>2)
		{
		count_adjust_work1=0;
		}

		}

		if (!(PINB&(1<<PB1)))
		{
			_delay_ms(200);

			flag_adjust_work2=2;
			count_adjust_work2+=1;
			if (count_adjust_work2>2)
			{
				count_adjust_work2=0;
			}

		}

		if (!(PINB&(1<<PB2)))
		{
			_delay_ms(200);

			flag_adjust_work3=3;
			count_adjust_work3+=1;
			if (count_adjust_work3>2)
			{
				count_adjust_work3=0;
			}

		}

		if (!(PINB&(1<<PB3)))
		{
			_delay_ms(200);

			flag_adjust_work4=4;
			count_adjust_work4+=1;
			if (count_adjust_work4>2)
			{
				count_adjust_work4=0;
			}

		}

		Nagruzka(flag_adjust_work1,flag_adjust_work2,flag_adjust_work3,flag_adjust_work4,count_adjust_work1,count_adjust_work2,count_adjust_work3,count_adjust_work4);


	}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

if(count_main_led==2)//����� �������� �� ���������
{

LCDGotoXY(8,2);
LCD_write_int(house);
LCDdata(':');
LCD_write_int(minuts);
LCDdata(':');
LCD_write_int(second);




if (!(PINB&(1<<PB1)))
{
	_delay_ms(200);

	flag_adjust_work2=2;
	count_adjust_work2+=1;
	if (count_adjust_work2>2)
	{
		count_adjust_work2=0;
	}

}

if (!(PINB&(1<<PB2)))
{
	_delay_ms(200);

	flag_adjust_work3=3;
	count_adjust_work3+=1;
	if (count_adjust_work3>2)
	{
		count_adjust_work3=0;
	}

}

if (!(PINB&(1<<PB3)))
{
	_delay_ms(200);

	flag_adjust_work4=4;
	count_adjust_work4+=1;
	if (count_adjust_work4>2)
	{
		count_adjust_work4=0;
	}

}

Nagruzka(flag_adjust_work1,flag_adjust_work2,flag_adjust_work3,flag_adjust_work4,count_adjust_work1,count_adjust_work2,count_adjust_work3,count_adjust_work4);


if (!(PINA&(1<<PA0)))
{
flag_del=1;

LCDGotoXY(0,1);
LCDsendString("Motion!!");
//������� ���������� ��������� ��������� ���������
Auto_Mode_On_Nag(flag_del);
}
else{
LCDGotoXY(0,1);
LCDsendString("No Motion!!");
flag_del=0;
Auto_Mode_On_Nag(flag_del);



}

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

if (count_main_led==3)//����� ���
{
LCDGotoXY(8,2);
LCD_write_int(house);
LCDdata(':');
LCD_write_int(minuts);
LCDdata(':');
LCD_write_int(second);

Nagruzka(0,0,0,0,0,0,0,0);





}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (count_main_led==4)//����� ���������� �������
{
LCDGotoXY(5,1);
LCDsendString("Power On!!");
Nagruzka(0,0,0,0,0,0,0,0);

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

if (count_main_led==5)//����� ���������� � ����������
{

LCDGotoXY(8,2);
LCD_write_int(house);
LCDdata(':');
LCD_write_int(minuts);
LCDdata(':');
LCD_write_int(second);


LCDGotoXY(5,1);
LCDsendString("USART Mode!!");
USART_Control(flg_control_USART);




}



    }
}

