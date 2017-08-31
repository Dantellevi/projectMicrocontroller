
#ifndef I2C_H_
#define I2C_H_


#include "Main.h"
void TWI_init(void);
void START_TWI(void);
void STOP_TWI(void);
void Sendbyte_TWI(unsigned char data);
void SendByte_Adr(unsigned char data,unsigned char Adress);
unsigned char Readbyte_TWI(void);
unsigned char ReadbyteLast_TWI(void);



#endif /* I2C_H_ */