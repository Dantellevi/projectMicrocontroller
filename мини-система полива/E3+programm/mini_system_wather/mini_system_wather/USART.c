#include "USART.h"



void Usart_init(unsigned int speed)
{
	
	UBRRH=(unsigned char)(speed>>8);
	UBRRL=(unsigned char)speed;
	
	UCSRB|=(1<<RXEN)|(1<<TXEN);
	UCSRA|=(1<<U2X);
	UCSRB|=(1<<RXCIE);
	
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	sei();
	
}


void Transmit_char_usart(unsigned char data)
{
	
	
	while(!(UCSRA&(1<<UDRE)));
	
	UDR=data;
}


void Transmit_str_usart(char*str)
{
	for(int i=0;str[i];i++)
	{
		
		Transmit_char_usart(str[i]);
	}
	
	
}

void Transmit_int(int data)
{
	char str[40];
	itoa(data,str,10);
	Transmit_str_usart(str);
	
}

ISR(USART_RXC_vect)
{


	
}


unsigned char Get_char_usart(void)
{
	
	while(!(UCSRA&(1<<RXC)));
	data_recive=UDR;
	return data_recive;
}


