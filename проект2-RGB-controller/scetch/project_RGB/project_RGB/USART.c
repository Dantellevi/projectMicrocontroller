#include "USART.h"


#define ANY 0

unsigned int cSend = 0;   // ������� ������������ ��������


inline void uart_init(unsigned int baud)  // ������� ������������� UART'a (��������� uart_init(9600))
{
	#if F_CPU < 2000000UL && defined(U2X)
	UCSRA =(1<<U2X);             // ���� ������� ���� 2 ���, ��� ���������� ��������� ��������
	UBRRL = (F_CPU / (8UL * baud)) - 1;
	#else
	UBRRL = (F_CPU / (16UL * baud)) - 1;
	#endif
	UCSRB =(1<<TXEN) |(1<<RXEN); // �������� �����/��������
}

inline void uart_putc(unsigned char data) // ������� �������� ������ ������� (�����) (��������� uart_putc('a'))
{
	
	while ( !( UCSRA & (1<<UDRE) ) ); // ���� ���� ����������� ������� UDR
	UDR = data;						   // �������� ��������
	if (data != 8)
	cSend++; // ����������� ������� ������������ ��������
	else
	cSend--; // ���� �������� backspace ��������� ������� ������������ ��������
}

inline unsigned char uart_getc (void) // ������� �������� 1-�� ������� (�����)
{
	while ( !(UCSRA & (1<<RXC)) );   // ���� ������� �������
	return UDR;						  // �������� ���������
}

inline void uart_write (char *str)	// ������� �������� ������
{
	for(int i = 0; str[i]; ++i)
	uart_putc(str[i]);
}

inline void uart_write_int(unsigned int val)
{
	char str[MAX_LINE_LENGHT];
	itoa(val, str, 10); // ���������� �������� val � ������
	uart_write(str);	 // �������� ������
}

inline char *uart_readln(char *s)
{
	char ch, *p;
	int t;

	p = s;  /* uart_readln() ���������� ��������� s */

	for(t=0; t<MAX_LINE_LENGHT; ++t){
		ch = uart_getc();  // �������� ������
		uart_putc(ch);		// ��� ����������� ���������� �����
		switch(ch) {
			case '\r':
			s[t] = '\0'; /* ��������� ������ */
			return p;
			case 0x08:
			if(t>0) t--;
			break;
			default:
			s[t] = ch;
		}
	}
	s[MAX_LINE_LENGHT - 1] = '\0';
	return p;
}

inline int CharToInt(char ch)
{
	if ((ch >= '0') && (ch <= '9')) // ���� ������ �����
	return ch - '0';			  // ������ ��������������
	else
	return -1; 					  // ����� ���������� 1
}

inline void uart_clr(unsigned int l)
{
	for(int i = cSend - l; i >= 0 ; i--)
	{
		uart_putc(8);
	}
}

inline void uart_wait(char *msg, char k) // ������� ������� ������� ������� �������
{
	uart_write(msg);                     // ����� ���������
	while(uart_getc() != k);			 // ���� ������� ������� k
	
}