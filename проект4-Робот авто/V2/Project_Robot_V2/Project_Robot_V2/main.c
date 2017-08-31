/*
 * Project_Robot_V2.c
 *мини робот пылесос
 * Created: 10.11.2016 15:10:22
 * Author : Лепотенко Александр Сергеевич
 */ 

 #include "Main.h"

 void PORT_init(void)//инициализация портов ввода/вывода
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



 void HC_SR04_init(void)//инициализация УЗ-датчика
 {
	 Trig_DDr|=1<<Trig_N;
	 Trig_Port&=~(1<<Trig_N);
	 
	 
	 Echo_ddr&=~(1<<Echo_N);
	 Echo_Port&=~(1<<Echo_N);
	 
	 
 }


 void HC_SR04_Send_strob(void) // функция посылки стробирующего импульса
 {
	 Trig_Port|=(1<<Trig_N);
	 _delay_us(20);
	 Trig_Port&=~(1<<Trig_N);
	 
 }
 
 void init_interupt(void)//инициализация прерывания микроконтроллера
 {
	 MCUCR|=(1<<ISC00);
	 GICR|=(1<<INT0);
	 
	 
 }
 //автозамена для удобства пользования
 #define  Start 1
 #define  Stop 0
 
 unsigned int timer_Start_stop(char flag)//Функция запуска/остановки таймера/счетчика
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
 
 unsigned int HC_SR04_Convert_CM(unsigned int N_t)//Преобразования приходящего импульса в число
 {
	 unsigned long int c;
	 c=N_t*8;
	 c/=58;
	 c+=1;

	 return (unsigned int)c;
	 
 }
 unsigned int N_tack=0;

 ISR(INT0_vect) //прерывания по внешнему прерыванию
 {
	 if (Echo_Pin&(1<<Echo_N))//запуск и остановка подсчета времени
	 {
		 timer_Start_stop(Start);
	 }
	 else
	 {
		 N_tack=timer_Start_stop(Stop);
	 }
	 
 }
 
 unsigned int HC_SRC4_get_CM(void)//получение данных о расстоянии
 {
	 HC_SR04_Send_strob();
	 _delay_ms(100);
	 return ( char)HC_SR04_Convert_CM(N_tack);
	 
 }




 void Timer_init(void)//инициализация таймера для ШИМ
 {

 TCCR2|=(1<<WGM20)|(WGM21);
 TCCR2|=(1<<COM21);
 TCCR2|=(1<<CS21);
 OCR2=1;


 }

int main(void)
{
  char Buuf[100];//буффер для USART
  char flag_work=0;//флаг работы устройства
   char rasst=0;//переменная в которую помещяем значения от датчика
   PORT_init();//объявление функции инициализации портов ввода/вывода
   HC_SR04_init();//объявление функции инициализации уз-датчика
    init_interupt();//объявление инициализации прерываний
	sei();//разрешение глобальных прерываний
   USART_Init(UBRR_VAL);//объявление функции инициализации интерфейса USART
   Timer_init();//объявление функции работы таймера
  
   
    USART_Transmit('c');//вывод данных на терминал
    USART_Transmit('o');//вывод данных на терминал
    USART_Transmit('n');//вывод данных на терминал
    USART_Transmit('n');//вывод данных на терминал
    USART_Transmit('e');//вывод данных на терминал
    USART_Transmit('k');//вывод данных на терминал
    USART_Transmit('t');//вывод данных на терминал
    USART_Transmit(0x0d);
    USART_Transmit(0x0a);
	    while (1) 
    {
	
	rasst=HC_SRC4_get_CM();//присваиваем значение переменной 
	
 	sprintf (Buuf , "%u " , rasst-1);//передаем значение на терминал
 	Transmit_string(Buuf);//передаем значение на терминал
 	USART_Transmit(0x0d);
 	USART_Transmit(0x0a);
 	
	if (!(PINB&(1<<0)))//включена ли кнопка запуска
	{
	_delay_ms(200);
	
	
		flag_work+=1;//устанавливаем флаг работы 
	}
		
		

	if (flag_work==1)//проверка условия флага работы
			{	
			PORTB|=(1<<PB4);
			PORTB|=(1<<PB5);			
	PORTB|=(1<<PB1);//включаем шетки и турбину
	PORTC|=(1<<PC0);//включаем шетки и турбину
	PORTC|=(1<<PC2);//включаем шетки и турбину
	if (!(PINB&(1<<PB2)))//сработал передний датчик
	{
		_delay_ms(100);
		PORTB&=~(1<<PB4);
		PORTD&=~(1<<PD3);
		OCR2=250;
		_delay_ms(100);
	}else{
	PORTD|=(1<<PD3);
	PORTD|=(1<<PD5);
	
	OCR2=130;//устанавливаем значение шим для перемещения
	
	}
			}
	else{//если флаг не равен единице 
	
	PORTD&=~(1<<PD3);
	PORTD&=~(1<<PD5);
	PORTB&=~(1<<PB1);
	OCR2=15;

	PORTB&=~(1<<PB1);//включаем шетки и турбину
	PORTC&=~(1<<PC0);//включаем шетки и турбину
	PORTC&=~(1<<PC2);//включаем шетки и турбину

	}

	if (rasst<5)// если расстояние до препятствия меньше 5 см поварачиваем в левую сторону
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

