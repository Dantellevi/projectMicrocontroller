/*********************************************
Date    : 05.12.2005
���������� ������ �����������.
*********************************************/

#include "90s2313.h"
#include "delay.h"

#define red PORTD.4
#define green PORTD.5
#define number_of_impuls 63    //64 - max
#define udervanie 1563
#define ofa_min 0x80
#define ofa_max 0xE8
#define kn_plus PIND.0;
#define kn_minus PIND.6;

unsigned char s_reg;//��������� SREG
unsigned char ofa;//������� ���� ->  ofa_min <= ofa <= ofa_max
unsigned char mode;//����� ������ �������� ��������� ��.

bit infra, infra_old;//�������, ���������� �������� ������� � ���
bit second_half_period;//��� �������� ������� �� ���������� timer1.
bit ir_plus, ir_minus, ir_plus_old, ir_minus_old;//������� �� ��� "+", "-"
bit closed;//���� ��������� ����������� ������� ���; �� ����� ����������� �� OVF_timer0
unsigned char num;//
bit on_new, on_old, off_new, off_old;//���� ��������� ������.
bit enable_count;
bit error;//����������� ������������ �������
bit ir_p_otp, ir_m_otp;//���������� ������ ��

unsigned int timer_ofa;//������ �������� ��������� ofa;
eeprom unsigned char pusto[1];
eeprom unsigned char plus[number_of_impuls];
eeprom unsigned char minus[number_of_impuls];
unsigned char serial[number_of_impuls];

flash unsigned char copyright[]="AMAR T0260";

unsigned int tic;//������ ������
unsigned int clock;//������ �������
bit second;//���� �������
bit in_home;//���� "������ ����"

#include "infrared.c"
void write(eeprom char *kuda)
{
for(num=0; num<number_of_impuls; num++) kuda[num]=serial[num];
mode=7;
num=0;
serial[0]=0;
}

void verify(unsigned char temp)
{
if((serial[num]<(temp-temp/4)) || (serial[num]>(temp+temp/4))) error=1;
}

void infrared(void)
{
static unsigned int zader;
static unsigned char prop;
unsigned char temp;

if(zader)//���� ��������� ������ �������
	{
	if(infra_old==1 && infra==1)
		{
		if(--zader)return;
		ir_minus=ir_plus=0;
		return;
		}
	zader=udervanie;
	return;
	}

if(!prop)
	{
	if(!infra) goto rc5_fr;
	return;
	}

if(prop < 7)
	{
	if(infra_old)
		{
		if(infra) goto rc5_count;
		}
	else
		{
		if(!infra)
			{
rc5_count:		if(++serial[0] > 250) prop=0;
			return;
			}
		}
	if(serial[0] > 0x14) ++prop;
rc5_fr:	++prop;
	serial[0]=0;
	return;
	}

if(infra_old != infra)
	{
	++num;
	serial[num]=0;
	return;
	}

//infra_old == infra
if(num<number_of_impuls && serial[num]<255) ++serial[num];
else//�������� ���������� ������������������
	{
	closed=1;
	prop=0;
	switch(mode)
		{
		case 5:
			write(plus);
			break;
		case 6:
			write(minus);
			break;
		default:
			error=0;
			for(num=0; num<number_of_impuls-1; num++)
				{
				temp=plus[num];
				if(temp==0xFF) break;
				verify(temp);
				}
			if(!error)
				{
				ir_plus=1;
    				ir_minus=0;
				}

			error=0;
	   		for(num=0; num<number_of_impuls-1; num++)
				{
				temp=minus[num];
				if(temp==0xFF) break;
				verify(temp);
				}
			if(!error)
				{
				ir_plus=0;
				ir_minus=1;
				}
			if(ir_plus || ir_minus) zader=udervanie;

			//������� ������� � ���������� num
			num=number_of_impuls;
			while(num) serial[--num]=0;
			break;
		}
	}
}
#include "keyboard.c"
//==========================================================
//��������� ������.
//==========================================================
void keyboard(void)
{
#define press_time 10
static unsigned int counter;//������� ��� �������� ������� ������ ������ ����������.
static unsigned char press_plus;//������� ���������������� ������� �� ������ "+"
static unsigned char press_minus;//������� ���������������� ������� �� ������ "-"
static unsigned char press_key;//������ ������ ������� �� ���� � mode=5 ��� 6.
static unsigned int zader;//������� ������� ������� �� ������.

if(++counter<2000) return;

//�������� �������
counter=0;

//���������� ������.
on_old=on_new;
off_old=off_new;
on_new=kn_plus;
off_new=kn_minus;

//���������� "+" � "-"
if(!on_old && !off_old && !on_new && !off_new)
	{
	if(zader > press_time*3)
		{
		mode=0;//������ ����
		in_home=1;
		clock=0;
		}
	else zader++;
	return;
	}

//���������� "-"
if(on_old && !off_old && on_new && !off_new || (ir_minus && !in_home))
	{
	if(zader>=press_time)
		{
		mode=1;//�������� ������� �������
		in_home=0;
		}
	else zader++;
	return;
	}

//���������� "+"
if(!on_old && off_old && !on_new && off_new || (ir_plus && !in_home))
	{
	if(zader>=press_time)
		{
		mode=2;//�������� �������� �������
		in_home=0;
		}
	else zader++;
	return;
	}

//��������� "-"
if(on_old && !off_old && on_new && off_new && (mode!=5) && (mode!=6) || ir_m_otp)
	{
	ir_m_otp=0;
	if(zader<press_time)
		{
		mode=3;//������ ���������
		in_home=0;
		ofa=ofa - (ofa - ofa_min)/4;
		}
	return;
	}

//��������� "+"
if(!on_old && off_old && on_new && off_new && (mode!=5) && (mode!=6) || ir_p_otp)
	{
	ir_p_otp=0;
	if(zader<press_time)
		{
		mode=4;//������ ��������
		in_home=0;
		}
	return;
	}

//������� "+"
if(on_old && off_old && !on_new && off_new)
	{
	enable_count=1;
	if(++press_plus>7)
		{
		mode=5;//����� ����������� ������� �� "+"
		goto l1;
		}
	return;
	}

//������� "-"
if(on_old && off_old && on_new && !off_new)
	{
	enable_count=1;
	if(++press_minus>7)
		{
		mode=6;//����� ����������� ������� �� "-"
l1:
		clock=0;
		}
	return;
	}

//
if(enable_count) ++press_key;
if(press_key>press_time*2)
	{
	enable_count=0;
	press_key=0;
	press_plus=0;
	press_minus=0;
	}

//���� ��� ��������� ��������� ������� ������ �� ������, �� ���������� ��������� �������.
if(mode==1 || mode==2) mode=7;

//�������� �������
zader=0;
}
#include "faza.c"
//==========================================================
//��������� ���������� �� �������������� �������� ���������.
//==========================================================
#pragma savereg-
interrupt [EXT_INT0] void ext_int0_isr(void)
{
s_reg=SREG;
#asm
	PUSH	R30
#endasm

second_half_period=0;//������������� �� ������� ��������� ���������� timer1.

TCNT1H=0xFF;//�������� timer1
TCNT1L=ofa;

TIMSK=0x82;//���������� ���������� �� ������������ timer1.

#asm
	POP	R30
#endasm
SREG=s_reg;
}
#pragma savereg+
#include "timer0.c"
//==========================================================
//��������� ���������� �������0.
//==========================================================
#pragma savereg-
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
if(closed) #asm("RETI");

//��������� ������������ ��������
#asm
	PUSH	R24
	PUSH	R25
	PUSH	R26
	PUSH	R27
	PUSH	R28
	PUSH	R29
	PUSH	R30
	PUSH	R31
	IN	R30,SREG
	ORI	R30,0x80
	PUSH	R30
#endasm

//������� ����� ��
infra_old=infra;
infra=PINB.0;

if(ir_plus_old && !ir_plus && !in_home && (mode!=1) && (mode!=2)) ir_p_otp=1;
if(ir_minus_old && !ir_minus && !in_home && (mode!=1) && (mode!=2)) ir_m_otp=1;

ir_plus_old=ir_plus;
ir_minus_old=ir_minus;

//��������� ����������
#asm("SEI");

//���������� ����� ��
infrared();

//���������� ������
keyboard();

if(++tic>=7813)//���� 0,5���
	{
	tic=0;
	clock++;//0 to 4294967295
	second=~second;
	}

//��������������� �������������� �������� � ������������.
#asm
	POP	R30
	OUT	SREG,R30
	POP	R31
	POP	R30
	POP	R29
	POP	R28
	POP	R27
	POP	R26
	POP	R25
	POP	R24
#endasm

closed=0;

#asm
	RET
#endasm
}
#pragma savereg+
#include "timer1.c"
//==========================================================
//��������� ���������� �������1 (��������� ���������).
//==========================================================
#pragma savereg-
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
//��������� ��������
s_reg=SREG;
#asm
	PUSH	R30
#endasm

//��������� ������� ���������.
PORTB=0x00;
//delay_us(7);
#asm
	LDI  R30,9
__DELAY:
	DEC  R30
	BRNE __DELAY
#endasm
PORTB=0b00011110;

//�������� 10���� ��� ������� �������.
TCNT1H=0xFF;
TCNT1L=0x64;

if(second_half_period) TIMSK=0x02;//��������� ���������� �������1.

second_half_period=1;

//��������������� ��������
#asm
	POP	R30
#endasm
SREG=s_reg;
}
#pragma savereg+

void main(void)
{
begin:
#asm("cli");
#include "init.c"
// Input/Output Ports initialization
// Port B initialization
// Func0=In Func1=Out Func2=Out Func3=Out Func4=Out Func5=In Func6=In Func7=In
// State0=T State1=1 State2=1 State3=1 State4=1 State5=T State6=T State7=T
DDRB =0b00011110;
PORTB=0b00011110;

// Port D initialization
// Func0=In Func1=In Func2=In Func3=In Func4=Out Func5=Out Func6=In
// State0=P State1=T State2=T State3=T State4=0 State5=1 State6=P
DDRD =0b00110000;
PORTD=0b01000001;

// Timer/Counter 0 initialization
// Clock source: System Clock
TCCR0=0x01;
TCNT0=0x02;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x02;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 125,000 kHz
// Mode: Normal top=FFFFh
// OC1 output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
TCCR1B=0x04;
TCCR1A=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
OCR1H=0x00;
OCR1L=0x00;

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Rising Edge
// INT1: Off
GIMSK=0x00;
MCUCR=0x03;
GIFR=0x40;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
// Analog Comparator Output: Off
ACSR=0x80;

//���������� ������
second_half_period=closed=0;
on_old=off_old=infra=infra_old=in_home=1;
mode=0;
ofa=ofa_min;
#asm("sei");

while (1)
	{
	switch(mode)
		{
		case 0: #include "mode_0.c";//������ ����
//������ ����
red=second;//������� ������� � ������� ������������
green=second;

//4 ����
if(clock==28800) mode=4;//������ ��������

//��� �������
if(clock>32400)
	{
	mode=3;//������ ��������
	clock=0;
	}
			break;
		case 1: #include "mode_1.c";//�������� ������� �������
//�������� ������� �������
if(GIMSK==0x00)
	{
	mode=7;
	break;
	}

if(++timer_ofa>7500)
	{
	timer_ofa=0;
	if(ofa>ofa_min) ofa--;
	else GIMSK=0x00;
	}
			break;
		case 2: #include "mode_2.c";//�������� �������� �������
//�������� �������� �������
if(GIMSK==0x00)
	{
	ofa=ofa_min;
	GIMSK=0x40;
	timer_ofa=0;
	}

if(++timer_ofa>7500)
	{
	timer_ofa=0;
	if(ofa<ofa_max) ofa++;
	else mode=7;
	}
			break;
		case 3: #include "mode_3.c";//������ ��������
//������ ��������
if(GIMSK==0x00)
	{
	if(in_home) mode=0;
	else mode=7;
	break;
	}

if(++timer_ofa>21000)
	{
	timer_ofa=0;
	if(ofa>ofa_min) ofa--;
	else GIMSK=0x00;
	}
			break;
		case 4: #include "mode_4.c";//������ ��������
//������ ��������
if(GIMSK==0x00)
	{
	ofa=ofa_min;
	GIMSK=0x40;
	timer_ofa=0;
	}

if(++timer_ofa>330)
	{
	timer_ofa=0;
	if(ofa<ofa_max) ofa++;
	else
		{
		if(in_home) mode=0;
		else mode=7;
		}
	}
			break;
		case 5: #include "mode_5.c";//��������� �� "+"
//��������� �� "+"
red=0;
green=second;

//���� �� 10 ��� �� ������� ������ ����������������, �� ����� �� ����������������
if(clock>20) mode=7;
			break;
		case 6: #include "mode_6.c";//��������� �� "-"
//��������� �� "-"
green=0;
red=second;

//���� �� 10 ��� �� ������� ������ ����������������, �� ����� �� ����������������
if(clock>20) mode=7;
			break;
		case 7: #include "mode_7.c";//������ ����
//������ ����
if(GIMSK==0x00) green=1;//�������� ������� ���������
else green=0;//����� ������� ���������
			break;
		default:
			goto begin;
		}
#asm
	SBIS	0x16,0
	RJMP	L1
	CBI	0x12,4
	RJMP	L2
L1:
	SBI	0x12,4
L2:
#endasm
	}
}
