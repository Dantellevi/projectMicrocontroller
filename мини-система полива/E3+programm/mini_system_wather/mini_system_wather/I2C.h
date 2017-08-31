/*
 * I2C.h
 *
 * Created: 03.04.2017 10:57:45
 *  Author: Dante_L_Levi
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "Main.h"

void I2C(void);
void STart_I2C(void);
void STop_I2C(void);
void I2C_SendByte(unsigned char c);
void I2C_SendByteAddr(unsigned char data,unsigned char Adress);
unsigned char I2C_ReadByte(void);
unsigned char I2C_ReadLastByte(void);



#endif /* I2C_H_ */