/*
 * Project_Robot_V2.c
 *���� ����� �������
 * Created: 10.11.2016 15:10:22
 * Author : ��������� ��������� ���������
 */ 

 #include "Main.h"

 void PORT_init(void)//������������� ������ �����/������
 {
 DDRB|=(1<<PB4);
 DDRB|=(1<<PB5);

 PORTB&=~(1<<PB4);
 PORTB&=~(1<<PB5);

 DDRB|=(1<<PB1);
 PORTB&=~(1<<PB1);

 DDRB&=(1<<PB2);
 PORTB|=(1<<PB2);

 

 DDRB&=~(1<<PB0);
 PORTB|=(1<<PB0);

 DDRD|=(1<<PD0);
 DDRD|=(1<<PD1);

 DDRD|=(1<<PD3);
 DDRD|=(1<<PD4);
 DDRD|=(1<<PD5);
 DDRD|=(1<<PD6);


 PORTD|=(1<<PD0);
 
 PORTD&=~(1<<PD3);
 PORTD&=~(1<<PD4);
 PORTD&=~(1<<PD5);
 PORTD&=~(1<<PD6);
 

 DDRC=0xFF;
 PORTC=0x00;
 }



 void HC_SR04_init(void)//������������� ��-�������
 {
	 Trig_DDr|=1<<Trig_N;
	 Trig_Port&=~(1<<Trig_N);
	 
	 
	 Echo_ddr&=~(1<<Echo_N);
	 Echo_Port&=~(1<<Echo_N);
	 
	 
 }


 void HC_SR04_Send_strob(void) // ������� ������� ������������� ��������
 {
	 Trig_Port|=(1<<Trig_N);
	 _delay_us(20);
	 Trig_Port&=~(1<<Trig_N);
	 
 }
 
 void init_interupt(void)//������������� ���������� ����������������
 {
	 MCUCR|=(1<<ISC00);
	 GICR|=(1<<INT0);
	 
	 
 }
 //���������� ��� �������� �����������
 #define  Start 1
 #define  Stop 0
 
 unsigned int timer_Start_stop(char flag)//������� �������/��������� �������/��������
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
 
 unsigned int HC_SR04_Convert_CM(unsigned int N_t)//�������������� ����������� �������� � �����
 {
	 unsigned long int c;
	 c=N_t*8;
	 c/=58;
	 c+=1;

	 return (unsigned int)c;
	 
 }
 unsigned int N_tack=0;

 ISR(INT0_vect) //���������� �� �������� ����������
 {
	 if (Echo_Pin&(1<<Echo_N))//������ � ��������� �������� �������
	 {
		 timer_Start_stop(Start);
	 }
	 else
	 {
		 N_tack=timer_Start_stop(Stop);
	 }
	 
 }
 
 unsigned int HC_SRC4_get_CM(void)//��������� ������ � ����������
 {
	 HC_SR04_Send_strob();
	 _delay_ms(100);
	 return ( char)HC_SR04_Convert_CM(N_tack);
	 
 }




 void Timer_init(void)//������������� ������� ��� ���
 {

 TCCR2|=(1<<WGM20)|(WGM21);
 TCCR2|=(1<<COM21);
 TCCR2|=(1<<CS21);
 OCR2=1;


 }

int main(void)
{
  char Buuf[100];//������ ��� USART
  char flag_work=0;//���� ������ ����������
   char rasst=0;//���������� � ������� �������� �������� �� �������
   PORT_init();//���������� ������� ������������� ������ �����/������
   HC_SR04_init();//���������� ������� ������������� ��-�������
    init_interupt();//���������� ������������� ����������
	sei();//���������� ���������� ����������
   USART_Init(UBRR_VAL);//���������� ������� ������������� ���������� USART
   Timer_init();//���������� ������� ������ �������
  
   
    USART_Transmit('c');//����� ������ �� ��������
    USART_Transmit('o');//����� ������ �� ��������
    USART_Transmit('n');//����� ������ �� ��������
    USART_Transmit('n');//����� ������ �� ��������
    USART_Transmit('e');//����� ������ �� ��������
    USART_Transmit('k');//����� ������ �� ��������
    USART_Transmit('t');//����� ������ �� ��������
    USART_Transmit(0x0d);
    USART_Transmit(0x0a);
	    while (1) 
    {
	
	rasst=HC_SRC4_get_CM();//����������� �������� ���������� 
	
 	sprintf (Buuf , "%u " , rasst-1);//�������� �������� �� ��������
 	Transmit_string(Buuf);//�������� �������� �� ��������
 	USART_Transmit(0x0d);
 	USART_Transmit(0x0a);
 	
	if (!(PINB&(1<<0)))//�������� �� ������ �������
	{
	_delay_ms(200);
	
	
		flag_work+=1;//������������� ���� ������ 
	}
		
		

	if (flag_work==1)//�������� ������� ����� ������
			{	
			PORTB|=(1<<PB4);
			PORTB|=(1<<PB5);			
	PORTB|=(1<<PB1);//�������� ����� � �������
	PORTC|=(1<<PC0);//�������� ����� � �������
	PORTC|=(1<<PC2);//�������� ����� � �������
	if (!(PINB&(1<<PB2)))//�������� �������� ������
	{
		_delay_ms(100);
		PORTB&=~(1<<PB4);
		PORTD&=~(1<<PD3);
		OCR2=250;
		_delay_ms(100);
	}else{
	PORTD|=(1<<PD3);
	PORTD|=(1<<PD5);
	
	OCR2=130;//������������� �������� ��� ��� �����������
	
	}
			}
	else{//���� ���� �� ����� ������� 
	
	PORTD&=~(1<<PD3);
	PORTD&=~(1<<PD5);
	PORTB&=~(1<<PB1);
	OCR2=15;

	PORTB&=~(1<<PB1);//�������� ����� � �������
	PORTC&=~(1<<PC0);//�������� ����� � �������
	PORTC&=~(1<<PC2);//�������� ����� � �������

	}

	if (rasst<5)// ���� ���������� �� ����������� ������ 5 �� ������������ � ����� �������
	{
		for (int i=0;i<10000;i++)
		{
		PORTD&=~(1<<PD3);
		PORTB&=~(1<<PB4);
		PORTB|=(1<<PB5);
		}
		
		
	}

	



    }
}

