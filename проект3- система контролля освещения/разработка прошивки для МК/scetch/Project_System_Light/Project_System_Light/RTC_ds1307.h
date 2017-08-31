/*
 * RTC_ds1307.h
 *
 * Created: 30.12.2016 8:50:16
 *  Author: Лепотенко Александр Сергеевич
 */ 


#ifndef RTC_DS1307_H_
#define RTC_DS1307_H_

#include "Main.h"
#include "I2C.h"


 unsigned char RTC_ConvertDEC(unsigned char c);
 unsigned char RTC_ConvertBinDec(unsigned char c);


#endif /* RTC_DS1307_H_ */