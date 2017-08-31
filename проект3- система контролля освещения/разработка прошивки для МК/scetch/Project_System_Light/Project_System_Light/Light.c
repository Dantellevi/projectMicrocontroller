/*
 * Система управления освещением
 *
 * Created: 29.12.2016 11:50:16
 * Author : Лепотенко Александр Сергеевич
 end:	06.01.2017
 Refactor:
 */ 

#include "Main.h"

int second=0;//секунды
int minuts=0;//минуты
int house=0;//часы
int day=0;//день недели
int data_d=0;//дата
int month=0;//месяц
int year=0;//год

unsigned char count_main_led=0;

//переменные для ручной настройки

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
ISR(USART_RXC_vect)//прерывания по приходу данных по USART
{

flg_control_USART=UDR;

}

void Port_init(void)//инициализация портов ввода/вывода
{
DDRA&=~(1<<PA0);//бит 0 порта А на вход для датчика
DDRA|=(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7);//биты с 1-7 на выход для LCD дисплея

PORTA|=(1<<PA0);//устанавливаем высокий уровень
PORTA&=~((1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7));//устанавливаем низкий уровень



DDRC|=(1<<PC7)|(1<<PC6)|(1<<PC5)|(1<<PC4)|(1<<PC3);//бит с 3-7 порта С на выход для индикации работы нагрузок
PORTC&=~((1<<PC7)|(1<<PC6)|(1<<PC5)|(1<<PC4)|(1<<PC3));//устанавливает низкий лог. уровень с 3 по 7 бит порта С


DDRB&=~(1<<PB4);//порт В бит 4 на вход
PORTB|=(1<<PB4);//высокий уровень
DDRB&=~(1<<PB3);//порт В бит 3 на вход
PORTB|=(1<<PB3);//высокий уровень
DDRB&=~(1<<PB2);//порт В бит 2 на вход
PORTB|=(1<<PB2);//высокий уровень
DDRB&=~(1<<PB1);//порт В бит 1 на вход
PORTB|=(1<<PB1);//высокий уровень
DDRB&=~(1<<PB0);//порт В бит 0 на вход
PORTB|=(1<<PB0);//высокий уровень

DDRD|=(1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD5);//порт Д бит с 2-5 на выход
PORTD&=~((1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD5));//низкий уровень


}

void Auto_Mode_On_Nag(unsigned char flag_delay)//функция обработки сигнала с PIR-датчика
{


if (flag_delay==1)//если датчик сработал включаем первую нагрузку
{
	PORTD|=(1<<PD2);
PORTC|=(1<<PC6);

}
else{//выключение нагрузки с задержкой в 1с.

_delay_ms(1000);
PORTD&=~(1<<PD2);
PORTC&=~(1<<PC6);
}

}

void Nagruzka(unsigned char flag1,unsigned char flag2,unsigned char flag3,unsigned char flag4, unsigned char count1,unsigned char count2,unsigned char count3,unsigned char count4)//функция управления нагрузками в ручном режиме
{

if (flag1==1 && count1==1)//включение первой нагрузки
{

USART_Write("WOrk Nagruzka ON-1");
USART_putc(0x0d);
USART_putc(0x0a);
PORTD|=(1<<PD2);
PORTC|=(1<<PC6);

}
else if (flag1==1 && count1==2)
{

USART_Write("WOrk Nagruzka OFF-1");//выключение первой нагрузки
USART_putc(0x0d);
USART_putc(0x0a);
PORTD&=~(1<<PD2);
PORTC&=~(1<<PC6);
}


if (flag2==2 && count2==1)
{

USART_Write("WOrk Nagruzka ON-2");//включение второй нагрузки
USART_putc(0x0d);
USART_putc(0x0a);
	PORTD|=(1<<PD3);
	PORTC|=(1<<PC5);
}
else if (flag2==2 && count2==2)
{

USART_Write("WOrk Nagruzka OFF-2");//выключение второй нагрузки
USART_putc(0x0d);
USART_putc(0x0a);
	PORTD&=~(1<<PD3);
	PORTC&=~(1<<PC5);
}


if (flag3==3 &&count3==1)
{

USART_Write("WOrk Nagruzka ON-3");//включение 3-ей нагрузки
USART_putc(0x0d);
USART_putc(0x0a);
	PORTD|=(1<<PD4);
	PORTC|=(1<<PC4);
}
else if (flag3==3 &&count3==2)
{

USART_Write("WOrk Nagruzka OFF-3");//выключение 3-ей нагрузки
USART_putc(0x0d);
USART_putc(0x0a);
	PORTD&=~(1<<PD4);
	PORTC&=~(1<<PC4);
}

if (flag4==4 &&count4==1)
{
USART_Write("WOrk Nagruzka ON-4");//включение 4-ой нагрузки
	USART_putc(0x0d);
	USART_putc(0x0a);
	PORTD|=(1<<PD5);
	PORTC|=(1<<PC3);
}
else if (flag4==4 &&count4==2)
{
USART_Write("WOrk Nagruzka OFF-4");//выключение 4-ой нагрузки
USART_putc(0x0d);
USART_putc(0x0a);
	PORTD&=~(1<<PD5);
	PORTC&=~(1<<PC3);
}




}

void Main_Led_indicate(unsigned char flag_Main_led)//индикация режима работы системы
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


void Clocck_RTC_ds1307(void)//функция реализующая подсчет времени на микросхема ds1307
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
USART_putc(data_d/10+0x30);//преобразуем число в код числа
USART_putc(data_d%10+0x30);//преобразуем число в код числа
USART_putc('.');
USART_putc(month/10+0x30);//преобразуем число в код числа
USART_putc(month%10+0x30);//преобразуем число в код числа
USART_putc('.');
USART_putc(year/10+0x30);//преобразуем число в код числа
USART_putc(year%10+0x30);//преобразуем число в код числа
USART_putc('.');
USART_putc('.');
USART_putc('.');
USART_putc('.');
USART_putc('.');
USART_putc(day+0x30);
USART_putc('.');
USART_putc('.');
USART_putc('.');
USART_putc(house/10+0x30);//преобразуем число в код числа
USART_putc(house%10+0x30);
USART_putc(':');
USART_putc(minuts/10+0x30);//преобразуем число в код числа
USART_putc(minuts%10+0x30);
USART_putc(':');
USART_putc(second/10+0x30);//преобразуем число в код числа
USART_putc(second%10+0x30);
USART_putc(0x0d);
USART_putc(0x0a);


}

void USART_Control(unsigned char flag)//функция реализующая управление через USART-интерфейс
{

switch(flag)
{
//включаем первую нагрузку
case 'Q':{LCDGotoXY(5,3);
	LCDsendString("On-1 load");PORTD|=(1<<PD2);PORTC|=(1<<PC6);   break;}
case 'q':{ LCDGotoXY(5,3);
	LCDsendString("OFF-1 load");PORTD&=~(1<<PD2);PORTC&=~(1<<PC6);  break;}//выключаем первую нагрузку

case 'W':{ LCDGotoXY(5,3);
	LCDsendString("On-2 load");PORTD|=(1<<PD3);PORTC|=(1<<PC5);  break;}//включаем 2-ую нагрузку
case 'w':{ LCDGotoXY(5,3);
	LCDsendString("OFF-2 load");PORTD&=~(1<<PD3);PORTC&=~(1<<PC5);  break;}//выключаем 2-ую нагрузку

case 'E':{ LCDGotoXY(5,3);
	LCDsendString("On-3 load");PORTD|=(1<<PD4);PORTC|=(1<<PC4);  break;}//включаем 3-ю нагрузку
case 'e':{ LCDGotoXY(5,3);
	LCDsendString("OFF-3 load");PORTD&=~(1<<PD4);PORTC&=~(1<<PC4);  break;}//выключаем 3-ю нагрузку

case 'R':{LCDGotoXY(5,3);
	LCDsendString("On-4 load");PORTD|=(1<<PD5); PORTC|=(1<<PC3);  break;}//включаем 4-ю нагрузку
case 'r':{ LCDGotoXY(5,3);
	LCDsendString("OFF-4 load");PORTD&=~(1<<PD5);PORTC&=~(1<<PC3);  break;}//выключаем 4-ю нагрузку

case 'A':{ LCDGotoXY(5,3);
	LCDsendString("On-ALL load");PORTD|=(1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD5); 
	PORTC|=(1<<PC3)|(1<<PC4)|(1<<PC5)|(1<<PC6);
	 break;}//все нагрузки включены
case 'a':{LCDGotoXY(5,3);
	LCDsendString("OFF-ALL load");PORTD&=~((1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD5));
	PORTC&=~((1<<PC3)|(1<<PC4)|(1<<PC5)|(1<<PC6));
	   break;}//все выключены

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
	//сброс флагов управления при переключении режима работы
	 count_adjust_work1=0;
	 count_adjust_work2=0;
	 count_adjust_work3=0;
	count_adjust_work4=0;

	 flag_adjust_work1=0;
	flag_adjust_work2=0;
	 flag_adjust_work3=0;
	flag_adjust_work4=0;
//сброс битов контроля нагрузок
	PORTD&=~(1<<PD2);
	PORTD&=~(1<<PD3);
	PORTD&=~(1<<PD4);
	PORTD&=~(1<<PD5);
//сброс битов контроля индикации
	PORTC&=~(1<<PC6);
	PORTC&=~(1<<PC5);
	PORTC&=~(1<<PC4);
	PORTC&=~(1<<PC3);
	//счетчик режима работы системы
	count_main_led++;

	}

	Main_Led_indicate(count_main_led);
	_delay_ms(300);
	LCDclear();
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
	if (count_main_led==1)//ручное управление нагрузками
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

if(count_main_led==2)//режим контроля за движением
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
//функция управления задержкой включения освещения
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

if (count_main_led==3)//режим сна
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
if (count_main_led==4)//режим отключения системы
{
LCDGotoXY(5,1);
LCDsendString("Power On!!");
Nagruzka(0,0,0,0,0,0,0,0);

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

if (count_main_led==5)//режим управления с компьютера
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

