/*
 * Project_Robot.c
 *������ ������ �������� � �������� ����������� �����������
 * Created: 13.10.2016 8:22:37
 * Author :��������� ��������� ���������
 */ 

#include "Main.h"

void Port_ini(void)//������������� ������ ����������������
{
	DDRC=0xFF;
	PORTC=0x00;
	DDRD|=(1<<PD3);
	DDRD|=(1<<PD4);
	DDRD|=(1<<PD5);
	DDRD|=(1<<PD6);
	
	PORTD&=~(1<<PD3);
	PORTD&=~(1<<PD4);
	PORTD&=~(1<<PD5);
	PORTD&=~(1<<PD6);
	
	DDRB|=(1<<PB0);
	DDRB|=(1<<PB6);
	DDRB|=(1<<PB7);
	PORTB&=~(1<<PB6);
	PORTB&=~(1<<PB7);
	PORTB&=~(1<<PB0);
	
}

//����������� ����� Echo
#define Echo_Port PORTD
#define Echo_ddr DDRD
#define  Echo_Pin PIND
#define Echo_N 2

//���������� ����� Trig
#define Trig_Port PORTD
#define Trig_DDr DDRD
#define Trig_Pin PIND
#define Trig_N 7


//������������� ������ HC-SR04
void HC_SR04_init(void)
{
	Trig_DDr|=1<<Trig_N;
	Trig_Port&=~(1<<Trig_N);
	
	
	Echo_ddr&=~(1<<Echo_N);
	Echo_Port&=~(1<<Echo_N);
	
	
}

// ������� ������� ������������� ��������
void HC_SR04_Send_strob(void)
{
	Trig_Port|=(1<<Trig_N);
	_delay_us(20);
	Trig_Port&=~(1<<Trig_N);
	
}
//������������� ���������� ����������������
void init_interupt(void)
{
	MCUCR|=(1<<ISC00);
	GICR|=(1<<INT0);
	
	
}
//���������� ��� �������� �����������
#define  Start 1
#define  Stop 0
//������� �������/��������� �������/��������
unsigned int timer_Start_stop(char flag)
{
	unsigned int rez;
	
	if (flag)
	{
		TCNT1H=0;
		TCNT1L=0;
		TCCR1B|=(1<<CS11);
	}
	else{
	TCCR1B&=~(1<<CS11);
	rez=TCNT1H;
	rez<<=8;
	rez|=TCNT1L;
	
	
	return rez;
	
	}
	
	
}
//�������������� ����������� �������� � ����� 	
unsigned int HC_SR04_Convert_CM(unsigned int N_t)
{
unsigned long int c;
c=N_t*8;
c/=58;
c+=2;

return (unsigned int)c;
	
}
	unsigned int N_tack=0;

	//���������� �� �������� ����������
	ISR(INT0_vect)
	{
	if (Echo_Pin&(1<<Echo_N))
	{
		timer_Start_stop(Start);
	}
		else
		{
			N_tack=timer_Start_stop(Stop);
		}
	
	}
	
	unsigned int HC_SRC4_get_CM(void)
	{
		HC_SR04_Send_strob();
		_delay_ms(100);
		return HC_SR04_Convert_CM(N_tack);
		
	}
	
//������� ���������� ��������� ��������� � ����������� �� ���������� �� �������
void  Switcher(unsigned int Prep)
{
	if(Prep>10)
	{

	for (int i=0;i<511;i++)
	{
	PORTB|=(1<<PB6);
	PORTB|=(1<<PB7);
	SMforvard();
	}
	
	

	
	
	
	
	}
	
	if(Prep<10&&Prep>5)
	{
		
	}
	if(Prep<5)
	{
		
		for (int i=0;i<511;i++)
		{
			PORTB|=(1<<PB6);
			PORTB|=(1<<PB7);
			SM_back();
		}
		
		
	}
	
}		
		
	

int main(void)
{
    Port_ini();
	HC_SR04_init();
	init_interupt();
	sei();
	unsigned int S;
	
    while (1) 
    {
	PORTB|=(1<<PB0);
		S=HC_SRC4_get_CM();
		
		Switcher(S);
		
		
		
		
	
    }
}

