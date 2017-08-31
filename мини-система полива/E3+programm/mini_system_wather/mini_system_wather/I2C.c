#include "I2C.h"


void I2C(void)
{
	TWBR=0x20;//скорость передачи (100к?ц при 8 ћ?ц)
	
}

void STart_I2C(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	
}

void STop_I2C(void)
{
	
	
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	
}

void I2C_SendByte(unsigned char c)
{
	
	TWDR=c;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	
}

void I2C_SendByteAddr(unsigned char data,unsigned char Adress)
{
	
	STart_I2C();
	I2C_SendByte(Adress);
	I2C_SendByte(data);
	STop_I2C();
	
}

unsigned char I2C_ReadByte(void)
{
	
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}


unsigned char I2C_ReadLastByte(void)
{
	
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
	
}
