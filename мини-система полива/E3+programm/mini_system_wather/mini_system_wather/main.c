/*
 * mini_system_wather.c
 *
 * Created: 03.04.2017 10:35:21
 * Author : Dante_L_Levi
 */ 

#include "Main.h"
char buffer[80];







#define PORT_INIT_H(x,y) (x|=(1<<y))//макрос для  инициализации порта на выход
#define PORT_INIT_L(x,y) (x&=~(1<<y))//макрос для инициализации порта на вход
#define PORT_SETUP(x,y) (x|=1<<y)//макрос для установки пина в 1
#define PORT_UNSETUP(x,y) (x&=~(1<<y))//макрос для установки пина в 0
#define PORT_Toggle(x,y) (x^=(1<<y))//макрос для переключения пина из 1 в 0 и наоборот

int second=0;//секунды
int minuts=0;//минуты
int hose=0;//часы
int day=0;//день недели
int data=0;//дата
int mesiac=0;//мес¤ц
int year=0;//год


//-------------------------------------------------







void Port_init(void)
{
	
	PORT_INIT_H(DDRD,PD3);
	PORT_UNSETUP(PORTD,PD3);
	DDRD|=(1<<PD4)|(1<<PD5);
	PORTD&=~((1<<PD4)|(1<<PD5));
	DDRD|=(1<<PD6)|(1<<PD7);
	PORTD|=(1<<PD6)|(1<<PD7);
	DDRB=0xFF;
	PORTB=0x00;
	DDRC&=~((1<<PC2)|(1<<PC3)|(1<<PC4)|(1<<PC5)|(1<<PC6));
	
	PORTC|=(1<<PC2)|(1<<PC3)|(1<<PC4)|(1<<PC5)|(1<<PC6);
	DDRC|=(1<<PC7);
	PORTC|=(1<<PC7);
	
	
	
}

void Clockds_USART(void)
{
	if (KeyPrress(Select)==1)
	{
		STop_I2C();
		
		
		return;
	}
	I2C_SendByteAddr(0,0b11010000);
	_delay_ms(300);
	STart_I2C();

	I2C_SendByte(0b11010001);//отправл¤ем в устройство бит чтени¤
	second=I2C_ReadByte();
	minuts=I2C_ReadByte();
	hose=I2C_ReadByte();
	day=I2C_ReadByte();
	data=I2C_ReadByte();
	mesiac=I2C_ReadByte();
	year=I2C_ReadLastByte();
	STop_I2C();
	second=RTC_ConvertDEC(second);
	minuts=RTC_ConvertDEC(minuts);
	hose=RTC_ConvertDEC(hose);
	day=RTC_ConvertDEC(day);
	data=RTC_ConvertDEC(data);
	mesiac=RTC_ConvertDEC(mesiac);
	year=RTC_ConvertDEC(year);
	//---------------------------------------------------


	Transmit_char_usart(0x0d);
	Transmit_char_usart(0x0a);
	Transmit_char_usart(data/10+0x30);//преобразуем число в код числа
	Transmit_char_usart(data%10+0x30);//преобразуем число в код числа
	Transmit_char_usart('.');
	Transmit_char_usart(mesiac/10+0x30);//преобразуем число в код числа
	Transmit_char_usart(mesiac%10+0x30);//преобразуем число в код числа
	Transmit_char_usart('.');
	Transmit_char_usart(year/10+0x30);//преобразуем число в код числа
	Transmit_char_usart(year%10+0x30);//преобразуем число в код числа
	Transmit_char_usart('.');
	Transmit_char_usart('.');
	Transmit_char_usart('.');
	Transmit_char_usart('.');
	Transmit_char_usart('.');
	Transmit_char_usart(day+0x30);
	Transmit_char_usart('.');
	Transmit_char_usart('.');
	Transmit_char_usart('.');
	Transmit_char_usart(hose/10+0x30);//преобразуем число в код числа
	Transmit_char_usart(hose%10+0x30);
	Transmit_char_usart(':');
	Transmit_char_usart(minuts/10+0x30);//преобразуем число в код числа
	Transmit_char_usart(minuts%10+0x30);
	Transmit_char_usart(':');
	Transmit_char_usart(second/10+0x30);//преобразуем число в код числа
	Transmit_char_usart(second%10+0x30);
	Transmit_char_usart(0x0d);
	Transmit_char_usart(0x0a);
	
}

int main(void)
{
	
	Port_init();
	I2C();
   Usart_init(103);
   ADC_Init();
   LCDinit();
	Timer_PWM_init();
   sei();
   ADCSRA |= 1<<ADSC;
   
   ServoPrivod_One_0();
   ServoPrivod_Two_0();
   LCDGotoXY(0,0);
   
 
   _delay_ms(500);
   LCDclear();
  
  
 
    while (1) 
    {
		MenuProcess();
		
		//sprintf(buffer,"T1=%.1fC",Temperature_LM35(0));
		//LCDstringXY(buffer,5,1);
		
    }
}

