/*
 * stepper_motor.c
 *
 * Created: 16.08.2016 21:42:26
 *  Author: Dante_L_Levi
 */ 
#include "stepper_motor.h"

#define  SM_port PORTC
#define  SM_ddr  DDRC
#define  IN1 PORTC0
#define  IN2 PORTC1
#define  IN3 PORTC2
#define  IN4 PORTC3



#define  SM_portD PORTD
#define  SM_ddrD  DDRD
#define  IND1 PORTD3
#define  IND2 PORTD4
#define  IND3 PORTD5
#define  IND4 PORTD6

#define SM_delay _delay_ms(1);

int i=0;

void SM_ini(void)
{
	SM_ddr|=(1<<IN4)|(1<<IN3)|(1<<IN2)|(1<<IN1);
	SM_port&=~(1<<IN4)|(1<<IN3)|(1<<IN2)|(1<<IN1);

	SM_ddrD|=(1<<IND4)|(1<<IND3)|(1<<IND2)|(1<<IND1);
	SM_portD&=~(1<<IND4)|(1<<IND3)|(1<<IND2)|(1<<IND1);

}

void SM_set1(void)
{
	SM_port|=(1<<IN1);SM_portD|=(1<<IND1);
	SM_port&=~(1<<IN2);SM_portD&=~(1<<IND2);
	SM_port&=~(1<<IN3);SM_portD&=~(1<<IND3);
	SM_port&=~(1<<IN4);SM_portD&=~(1<<IND4);
	
	SM_delay;

}
void SM_set2(void)
{
	SM_port|=(1<<IN1);SM_portD|=(1<<IND1);
	SM_port|=(1<<IN4);SM_portD|=(1<<IND4);
	SM_port&=~(1<<IN2);SM_portD&=~(1<<IND2);
	SM_port&=~(1<<IN3);SM_portD&=~(1<<IND3);
	SM_delay;
	
}
void SM_set3(void)
{
	SM_port|=(1<<IN4);SM_portD|=(1<<IND4);
	SM_port&=~(1<<IN1);SM_portD&=~(1<<IND1);
	SM_port&=~(1<<IN2);SM_portD&=~(1<<IND2);
	SM_port&=~(1<<IN3);SM_portD&=~(1<<IND3);
	
	SM_delay;
	
}
void SM_set4(void)
{
	SM_port|=(1<<IN4);SM_portD|=(1<<IND4);
	SM_port|=(1<<IN3);SM_portD|=(1<<IND3);
	SM_port&=~(1<<IN1);SM_portD&=~(1<<IND1);
	SM_port&=~(1<<IN2);SM_portD&=~(1<<IND2);
	SM_delay;
	
}
void SM_set5(void)
{
	SM_port|=(1<<IN3);SM_portD|=(1<<IND3);
	SM_port&=~(1<<IN1);SM_portD&=~(1<<IND1);
	SM_port&=~(1<<IN2);SM_portD&=~(1<<IND2);
	SM_port&=~(1<<IN4);SM_portD&=~(1<<IND4);
	SM_delay;
	
}
void SM_set6(void)
{
	SM_port|=(1<<IN3);SM_portD|=(1<<IND3);
	SM_port|=(1<<IN2);SM_portD|=(1<<IND2);
	SM_port&=~(1<<IN1);SM_portD&=~(1<<IND1);
	SM_port&=~(1<<IN4);SM_portD&=~(1<<IND4);
	SM_delay;
	
}
void SM_set7(void)
{
	SM_port|=(1<<IN2);SM_portD|=(1<<IND2);
	SM_port&=~(1<<IN1);SM_portD&=~(1<<IND1);
	SM_port&=~(1<<IN3);SM_portD&=~(1<<IND3);
	SM_port&=~(1<<IN4);SM_portD&=~(1<<IND4);
	SM_delay;
	
}
void SM_set8(void)
{
	SM_port|=(1<<IN1);SM_portD|=(1<<IND1);
	SM_port|=(1<<IN2);SM_portD|=(1<<IND2);
	SM_port&=~(1<<IN3);SM_portD&=~(1<<IND3);
	SM_port&=~(1<<IN4);SM_portD&=~(1<<IND4);
	SM_delay;
	
}

void SMforvard(void)
{
	SM_set1();
	SM_set2();
	SM_set3();
	SM_set4();
	SM_set5();
	SM_set6();
	SM_set7();
	SM_set8();
}

void SM_back(void)
{
	SM_set8();
	SM_set7();
	SM_set6();
	SM_set5();
	SM_set4();
	SM_set3();
	SM_set2();
	SM_set1();
}