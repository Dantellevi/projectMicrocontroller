/*
*���������� ��� ������ � USART
*������� ������������ 
*
*
*/

#include "USART.h"

unsigned char cound_Send=0;//������� �������� ���������

void USART_INIT(unsigned int baud)//������� �������������
{
#if F_CPU<2000000UL && defined(U2X)//�������� ������������

UCSRA=(1<<U2X);//��������� ������� ��������
UBRRL=(F_CPU/(8UL*baud))-1;//���������� ��������

#else

UBRRL = (F_CPU / (16UL * baud)) - 1;
#endif
UCSRB=(1<<TXEN)|(1<<RXEN);//���������� �� ����� � ��������
UCSRB|=(1<<RXCIE);
}

void USART_putc(unsigned char data)//������� �������� �������
{
while (!( UCSRA & (1<<UDRE))); // ���� ���� ����������� ������� UDR
UDR = data;						   // �������� ��������
if (data!= 8)
cound_Send++; // ����������� ������� ������������ ��������
else
cound_Send--; // ���� �������� backspace ��������� ������� ������������ ��������
}

unsigned char USART_getc(void)//������� ������ �������
{

while(!(UCSRA&(1<<RXC)));//���� ������� �������

return UDR;//��������� ������

}

void USART_Write(char *str1)//������ ������ ��������
{

for (int i=0;str1[i];i++)
{
USART_putc(str1[i]);
}

}

void USART_Write_Int(unsigned int val)//������� ������ � �������������� �������������� � �������
{

char str[MAX_LINE_LENGHT];
itoa(val,str,10);//�������������� � �������
USART_Write(str);//��������

}

char *USART_readln(char *s)//������� ������ ������ ��������
{
char ch, *p;
int t;

p=s;

for (t=0;t<MAX_LINE_LENGHT;++t)
{

ch=USART_getc();// �������� ������
USART_putc(ch);// ��� ����������� ���������� �����
switch(ch)
{

case '\r':
s[t]='\0';/* ��������� ������ */
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


int CharToInt(char ch)//������� �������������� ������� � �����
{

	if ((ch>='\0')&&(ch<='9')) // ���� ������ �����
	{
		return ch-'0';// ������ ��������������
	}else
		return -1; // ����� ���������� 1
}


void USART_Calculation(unsigned int l)
{

for (int i=cound_Send-l;i>=0;i--)
{

USART_putc(8);

}

}

void USART_waitEnter(char *msg,char k)// ������� ������� ������� ������� �������
{


USART_Write(msg); // ����� ���������
while(USART_getc()!=k); // ���� ������� ������� k


}
