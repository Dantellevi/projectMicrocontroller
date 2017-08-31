#include "USART.h"



void USART0_INIT(unsigned int baud)
{
	UBRR0H=(unsigned char)(baud>>8);//установка скорости старший разряд
	UBRR0L=(unsigned char)baud;//младший разряд
	


UCSR0B=(1<<TXEN0)|(1<<RXEN0);//разрешения работы приемника/передатчика
 UCSR0B |= (1<<RXCIE0);//прерывания по приемнику
UCSR0A |= (1<<U2X0);//мультиплексирование скорости
UCSR0C|=(1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);//биты настройки : 1 стоп бит и 8 бит данных



}


void USART2_INIT(unsigned int baud)
{
	
	UBRR2H=(unsigned char)(baud>>8);
	UBRR2L=(unsigned char)baud;
	


	UCSR2B=(1<<TXEN2)|(1<<RXEN2);
	UCSR2B |= (1<<RXCIE2);
	UCSR2A |= (1<<U2X2);
	UCSR2C|=(1<<USBS2)|(1<<UCSZ21)|(1<<UCSZ20);
		

}

void USART0_puts(unsigned char data)
{
	while(!(UCSR0A&(1<<UDRE0)));//ожидаем опусташение буфера
	UDR0=data;//записываем данные из переменной 
	
	
}


void USART2_puts(unsigned char data)
{
	while(!(UCSR2A&(1<<UDRE2)));
	UDR2=data;
	
	
}





void USART0_putsString(char *str1)
{

for(int i=0;str1[i];i++)//в цикле перебираем строку(массив символов)и помещаем всех в буффер
{
	USART0_puts(str1[i]);
		
}

}


void USART2_putsString(char *str1)
{

	for(int i=0;str1[i];i++)
	{
		USART2_puts(str1[i]);
		
	}

}





void USART0_putsInt(unsigned int val)
{
	 char str[MAX_LINE_LENGHT];//создаем массив символов
	itoa(val,str,10);//преобразуем принятую переменную целочисленного типа в строку(массив символов)
	USART0_putsString(str);	//выводим ее на печать
	
}


void USART2_putsInt(unsigned int val)
{
	char str[MAX_LINE_LENGHT];
	itoa(val,str,10);
	USART2_putsString(str);
	
}

int CharToInt(char ch)//функция преобразования символа в число
{

	if ((ch>='\0')&&(ch<='9')) // если символ число
	{
		return ch-'0';// делаем преобразование
	}else
	return -1; // иначе возвращаем 1
}




