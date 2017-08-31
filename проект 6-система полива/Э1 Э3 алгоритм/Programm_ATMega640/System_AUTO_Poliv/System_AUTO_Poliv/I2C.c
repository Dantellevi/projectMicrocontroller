#include "I2C.h"

void TWI_init(void)
{
	
	TWBR=0x20;//задаем скорость 100к√ц
	
	
}

void START_TWI(void)
{
	
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//начало передачи
	while(!(TWCR&(1<<TWINT)));//ожидание установка флага
}

void STOP_TWI(void)
{
	TWCR=(1<<TWINT)|(TWSTO)|(1<<TWEN);//остановка работы
	
}

void Sendbyte_TWI(unsigned char data)
{
	
	TWDR=data;//помещаем данные в регистр данных
	TWCR=(1<<TWINT)|(1<<TWEN);//установка флагов
	while(!(TWCR&(1<<TWINT)));//ожидание установки флага
}

void SendByte_Adr(unsigned char data,unsigned char Adress)
{
	
	START_TWI();
	Sendbyte_TWI(Adress);
	Sendbyte_TWI(data);
	STOP_TWI();
	
}

unsigned char Readbyte_TWI(void)
{
	
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(!(TWCR&(1<<TWINT)));
	
	return TWDR;
}

unsigned char ReadbyteLast_TWI(void)
{
	
	TWCR=(1<<TWINT)|(1<<TWEA);
	while((TWCR&(1<<TWINT)));
	return TWDR;
	
}


