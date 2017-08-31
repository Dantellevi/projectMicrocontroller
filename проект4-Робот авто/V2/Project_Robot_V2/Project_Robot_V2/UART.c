#include "UART.h"

void USART_Init( unsigned int ubrr)//Инициализация модуля USART
{
	//Зададим скорость работы USART 115200
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	
	UCSRA = 0X00;
	UCSRB|=(1<<TXEN);// Разрешение работы приемника
	// Установка формата посылки: 8 бит данных, 1 стоп-бит
	UCSRC =(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);// Обращаемся именно к регистру UCSRC (URSEL=1),
	//ассинхронный режим (UMSEL=0), без контроля четности (UPM1=0 и UPM0=0),
	//1 стоп-бит (USBS=0), 8-бит посылка (UCSZ1=1 и UCSZ0=1)
}

void USART_Transmit( unsigned char data ) //Функция отправки данных
{
	
	while ( !(UCSRA&(1<<UDRE))); 
	UDR = data; //Начало передачи данных
	
} 

 void Transmit_string( char s[])
 {
 char k;
 for (k=0;s[k]!=0;k++)
 {
 	UDR =s[k];
 	while ( !(UCSRA&(1<<UDRE)));//ждем окончания передачи
 	
 }
 
 
 }
