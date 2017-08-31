/*
*Библиотека для работы с USART
*Немного переделанная 
*
*
*/

#include "USART.h"

unsigned char cound_Send=0;//счетчик отправки сообщений

void USART_INIT(unsigned int baud)//функция инициализации
{
#if F_CPU<2000000UL && defined(U2X)//проверка тактирования

UCSRA=(1<<U2X);//установка двойной скорости
UBRRL=(F_CPU/(8UL*baud))-1;//вычисление скорости

#else

UBRRL = (F_CPU / (16UL * baud)) - 1;
#endif
UCSRB=(1<<TXEN)|(1<<RXEN);//разрешение на прием и передачу
UCSRB|=(1<<RXCIE);
}

void USART_putc(unsigned char data)//функция передачи символа
{
while (!( UCSRA & (1<<UDRE))); // ждем пока освободится регистр UDR
UDR = data;						   // начинаем передачу
if (data!= 8)
cound_Send++; // увеличиваем счетчик отправленных символов
else
cound_Send--; // если отослали backspace уменьшаем счетчик отправленных символов
}

unsigned char USART_getc(void)//функция приема символа
{

while(!(UCSRA&(1<<RXC)));//ждем очистки буффера

return UDR;//возращаем данные

}

void USART_Write(char *str1)//запись строки символов
{

for (int i=0;str1[i];i++)
{
USART_putc(str1[i]);
}

}

void USART_Write_Int(unsigned int val)//функция записи и преобразования целочисленного в символы
{

char str[MAX_LINE_LENGHT];
itoa(val,str,10);//преобразование в символы
USART_Write(str);//отправка

}

char *USART_readln(char *s)//функция чтение строки символов
{
char ch, *p;
int t;

p=s;

for (t=0;t<MAX_LINE_LENGHT;++t)
{

ch=USART_getc();// получаем символ
USART_putc(ch);// для наглядности отправляем назад
switch(ch)
{

case '\r':
s[t]='\0';/* завершает строку */
return p;

case 0x08:
if (t>0)
{
t--;
}break;

default:
s[t]=ch;


}

}

s[MAX_LINE_LENGHT-1]='\0';
return p;
}


int CharToInt(char ch)//функция преобразования символа в число
{

	if ((ch>='\0')&&(ch<='9')) // если символ число
	{
		return ch-'0';// делаем преобразование
	}else
		return -1; // иначе возвращаем 1
}


void USART_Calculation(unsigned int l)
{

for (int i=cound_Send-l;i>=0;i--)
{

USART_putc(8);

}

}

void USART_waitEnter(char *msg,char k)// функция которая ожидает нажатия клавиши
{


USART_Write(msg); // вывод сообщения
while(USART_getc()!=k); // ждем нажатия клавиши k


}
