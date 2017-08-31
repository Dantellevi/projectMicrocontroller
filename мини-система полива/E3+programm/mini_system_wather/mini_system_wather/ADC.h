/*
 * ADC.h
 *
 * Created: 03.04.2017 10:36:08
 *  Author: Dante_L_Levi
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "Main.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>




void ADC_Init(void);

unsigned int read_adc_value(unsigned char port);
float Temperature_LM35(unsigned char port);
float Semsor_swit(unsigned char port);
unsigned int read_adc_value0(void);



#endif /* ADC_H_ */