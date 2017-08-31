#include "button.h"

static unsigned char button_cnt[5]={0};
	
	void Read_Button_State (unsigned char b);
	
	
	void init_button_timer(void)
	{
		
		TIMSK|=(1<<TOIE0);
		TCCR0|=(1<<CS01);
	}
	
	ISR(TIMER0_OVF_vect)
	{
		Read_Button_State(Button_Right);
		Read_Button_State(Button_Up);
		Read_Button_State(Button_Down);
		Read_Button_State(Button_Left);
		Read_Button_State(Button_Select);
		
	}


unsigned char Read_Button_Press (unsigned char b)
{
	unsigned int adc_value;
	adc_value=read_adc_value(4);
	
	switch (b)
	{
		case Button_Right:
		if(adc_value<25) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
		case Button_Up:
		if((adc_value>115)&&(adc_value<180)) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
		case Button_Down:
		if((adc_value>180)&&(adc_value<500)) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
		case Button_Left:
		if((adc_value>500)&&(adc_value<700)) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
		case Button_Select:
		if((adc_value>700)&&(adc_value<1000)) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
	}
	return ST_ERROR;
}

void Read_Button_State (unsigned char b)
{
	if ((button_state[b]&ST_LOCKED)!=0) return;
	if (Read_Button_Press(b)==ST_UNPRESSED)
	{
		if (button_cnt[b]>0)
		{
			button_cnt[b]--;
		}
		else
		{
			if((button_state[b]&ST_PRESSED)!=0)
			{
				button_state[b] |= ST_UNPRESSURE;
				button_state[b] &= ~ST_PRESSED;
				button_state[b] |= ST_UNPRESSED;
			}
		}
	}
	else
	{
		if (button_cnt[b]<5)
		{
			button_cnt[b]++;
		}
		else
		{
			if((button_state[b]&ST_UNPRESSED)!=0)
			{
				button_state[b] |= ST_PRESSURE;
				button_state[b] &= ~ST_UNPRESSED;
				button_state[b] |= ST_PRESSED;
			}
		}
	}
}

void ResetButtonState(unsigned char b, unsigned char st)
{
	button_state[b]&=~st;
}
//-----------------------------------------
void SetButtonState(unsigned char b, unsigned char st)
{
	button_state[b]|=st;
}
//-----------------------------------------
void Button_ini(void)
{
	unsigned char i;
	//������� ������� ������
	for (i=0;i<5;i++)
	{
		button_state[i]=ST_UNPRESSED;
	}
	//�������� ������
	init_button_timer();
}