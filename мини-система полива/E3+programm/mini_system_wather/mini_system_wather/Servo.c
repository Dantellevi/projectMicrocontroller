#include "Servo.h"

char flag_servo_work1=0;
char flag_servo_work2=0;

void Timer_PWM_init(void)
{
	
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);
	TCCR1B|=(WGM12)|(1<<WGM13);
	TCCR1B|=(1<<CS11);
	ICR1=667;
	
	OCR1A=1;
	OCR1B=1;
}

void ServoPrivod_One_0(void)
{
	flag_servo_work1=1;
	OCR1A=58;
}
void ServoPrivod_Two_0(void)
{
	flag_servo_work2=1;
	OCR1B=58;
}


void ServoPrivod_One_90(void)
{
	flag_servo_work1=2;
	OCR1A=189;
}
void ServoPrivod_Two_90(void)
{
	flag_servo_work2=2;
		OCR1B=189;
}

void ServoPrivod_One_180(void)
{
	OCR1A=378;
}
void ServoPrivod_Two_180(void)
{
	OCR1B=378;
}


