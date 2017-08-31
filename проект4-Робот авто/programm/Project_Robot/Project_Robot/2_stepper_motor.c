/*
 * ��������� ��� ���������� �������� �����������(2 ���������)
 *
 * Created: 13.10.2016 8:25:58
 *  Author: ��������� ��������� ���������
 */ 


#include "Stepper.h"

#define pause _delay_ms(100)
//����� ��� ������ 1
#define Motor_1 PORTC 
#define C0 PC0
#define C1 PC1
#define C2 PC2
#define C3 PC3
//-----------------------
 //����� ��� ������ 2
#define Motor_2 PORTD
#define D0 PD3
#define D1 PD4
#define D2 PD5
#define D3 PD6


//������ �������� �������  ������ ������� �������
void down_M_all(void)
{
	 PORTB|=(1<<PB6);
	 PORTB|=(1<<PB7);
	Motor_1|=(1<<C0);
	Motor_2|=(1<<D0);
	 pause;
	
	Motor_1&=~(1<<C1);
	Motor_2&=~(1<<D1);
	  pause;
	
	Motor_1|=(1<<C3);
	Motor_2|=(1<<D3);
	   pause;
	
	Motor_1&=~(1<<C2);
	Motor_2&=~(1<<D2);
	     pause;
	   
	Motor_1|=(1<<C1);
	Motor_2|=(1<<D1);
	 pause;
	
	Motor_1&=~(1<<C0);
	Motor_2&=~(1<<D0);
	   pause;
	
	Motor_1 |= (1<<C2);
	Motor_2 |= (1<<D2);
	  pause;
	
	Motor_1 &=~(1<<C3);
	Motor_1 |=(1<<C0);
	Motor_2 &=~(1<<D3);
	Motor_2 |=(1<<D0);
	  pause;
	
	
}
//--------------------------------------------------------------





 
 
 //������� �������� ������ ���� ����������
 void UP_move_all(void)
 {
	  PORTB|=(1<<PB7);
	  PORTB|=(1<<PB6);
	 Motor_1 &=~(1<<C3);
	 Motor_1 |=(1<<C0);
	 PORTB|=(1<<PB6);
	 Motor_2 &=~(1<<D3);
	 Motor_2 |=(1<<D0);
	   pause;
	 
	 Motor_1 |= (1<<C2);
	 Motor_2 |= (1<<D2);
	   pause;
	 
	 Motor_1&=~(1<<C0);
	 Motor_2&=~(1<<D0);
	    pause;
	 
	 Motor_1|=(1<<C1);
	 Motor_2|=(1<<D1);
	   pause;
	 
	 Motor_1&=~(1<<C2);
	 Motor_2&=~(1<<D2);
	    pause;
	 
	 Motor_1|=(1<<C3);
	 Motor_2|=(1<<D3);
	   pause;
	 
	 Motor_1&=~(1<<C1);
	 Motor_2&=~(1<<D1);
	  pause;
	 
	 Motor_1|=(1<<C0);
	 Motor_2|=(1<<D0);
	   pause;
	 
	 
	 //--------------
 
 }
 
 
  //������ �������� ������-2 ������ ������� �������
  void down_M_2(void)
  {
	  PORTB|=(1<<PB7);
	   PORTB&=~(1<<PB6);
	  Motor_2|=(1<<D0);
	    pause;
	  
	  Motor_2&=~(1<<D1);
	  pause;
	  
	  Motor_2|=(1<<D3);
	  pause;
	  
	  Motor_2&=~(1<<D2);
	   pause;
	  
	  Motor_2|=(1<<D1);
	   pause;
	  
	  Motor_2&=~(1<<D0);
	    pause;
	  
	  Motor_2 |= (1<<D2);
	   pause;
	  
	  Motor_2 &=~(1<<D3);
	  Motor_2 |=(1<<D0);
	    pause;
	  
	  
  }
  //--------------------------------------------------------------
  //�������� ������� ������ ������ ������� �������
   void down_M_1(void)
   {
	   PORTB|=(1<<PB6);
	    PORTB&=~(1<<PB7);
	   Motor_1|=(1<<C0);
	    pause;
	   
	   Motor_1&=~(1<<C1);
	     pause;
	   
	   Motor_1|=(1<<C3);
	    pause;
	   
	   Motor_1&=~(1<<C2);
	    pause;
	   
	   Motor_1|=(1<<C1);
	   pause;
	   
	   Motor_1&=~(1<<C0);
	    pause;
	   
	   Motor_1 |= (1<<C2);
	  pause;
	   
	   Motor_1 &=~(1<<C3);
	   Motor_1 |=(1<<C0);
	    pause;
	   
	   
   }
   //--------------------------------------------------------------






  
  
  //������� �������� ������ ��� ������ 2
  void UP_move_2(void)
  {
	   PORTB|=(1<<PB7);
	    PORTB&=~(1<<PB6);
	  Motor_2 &=~(1<<D3);
	  Motor_2 |=(1<<D0);
	     pause;
	  
	  Motor_2 |= (1<<D2);
	    pause;
	  
	  Motor_2&=~(1<<D0);
	    pause;
	  
	  Motor_2|=(1<<D1);
	  pause;
	  
	  Motor_2&=~(1<<D2);
	     pause;
	  
	  Motor_2|=(1<<D3);
	    pause;
	  
	  Motor_2&=~(1<<D1);
	     pause;
	  
	  Motor_2|=(1<<D0);
	    pause;
	  
  }
	  //--------------
	  
	  //������� �������� ������ ��� ������ 2
	  void UP_move_1(void)
	  {
		  PORTB|=(1<<PB6);
		  PORTB&=~(1<<PB7);
		  Motor_1 &=~(1<<C3);
		  Motor_1 |=(1<<C0);
		 pause;
		  
		  Motor_1 |= (1<<C2);
		   pause;
		  
		  Motor_1&=~(1<<C0);
		  pause;
		  
		  Motor_1|=(1<<C1);
		  pause;
		  
		  Motor_1&=~(1<<C2);
		  pause;
		  
		  Motor_1|=(1<<C3);
		pause;
		  
		  Motor_1&=~(1<<C1);
		   pause;
		  
		  Motor_1|=(1<<C0);
		  pause;
		  
	  }
		  //------------------------------------------------------------------------
	  

  