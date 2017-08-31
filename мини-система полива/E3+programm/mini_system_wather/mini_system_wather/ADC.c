#include "ADC.h"



void ADC_Init(void)
{
	ADMUX|=(1<<REFS0);
	ADCSRA|=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)|(1<<ADEN);
	ADCSRA|=(1<<ADSC);
	
	
}

unsigned int read_adc_value(unsigned char port)
{
	
 	ADMUX=port|(ADMUX&0xF0);
 	_delay_us(10);
 	ADCSRA|=(1<<ADSC);
 	while((ADCSRA&(1<<ADIF))==0);
 	
 	return ADCW;
}



float Temperature_LM35(unsigned char port)
{
	float  Temp;
	
	
	Temp=(read_adc_value(port)*5)/10.24;
	
	return Temp;
	
}

float Semsor_swit(unsigned char port)
{
	
	int  Temp;
	
	
	Temp=(int)((read_adc_value(port)*5)/1024);
	
	return Temp;
	
	
}





