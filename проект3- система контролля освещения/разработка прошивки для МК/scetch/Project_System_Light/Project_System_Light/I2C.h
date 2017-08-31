/*
 * I2C.h
 *
 * Created: 30.12.2016 8:20:10
 *  Author: Лепотенко Александр Сергеевич
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "Main.h"
#include "RTC_ds1307.h"

void Init_I2C(void);
void Start_I2C(void);
void Stop_I2C(void);
void Sendbyte_I2C(unsigned char data);
void SendByte_Addr(unsigned char data, unsigned char Adress);
unsigned char Readbyte_I2C(void);
unsigned char ReadLast_byte(void);


#endif /* I2C_H_ */