/*
 * RTC_ds1307.c
 *
 * Created: 30.12.2016 8:50:36
 *  Author: Лепотенко Александр Сергеевич
 */ 


 #include "RTC_ds1307.h"

 unsigned char RTC_ConvertDEC(unsigned char c)
 {

 unsigned char ch=((c>>4)*10+(0b00001111&c));
 return ch;
 }
 unsigned char RTC_ConvertBinDec(unsigned char c)
 {

 unsigned char ch=(((c/10)<<4)/(c%10));
	return ch;
 }