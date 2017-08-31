/*
 * I2C.c
 *
 * Created: 30.12.2016 8:20:23
 *  Author: Лепотенко Александр Сергеевич
 */ 


 #include "I2C.h"

 void Init_I2C(void)
 {
 TWBR=0x20;//скорость передачи состовляет 100кГц


 }

 void Start_I2C(void)
 {

 TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//начало передачи
 while(!(TWCR&(1<<TWINT)));//ожидание установки флага

 }

 void Stop_I2C(void)
 {

 TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//конец передачи

 }

 void Sendbyte_I2C(unsigned char data)
 {

 TWDR=data;//помещаем данные в регистр данных
 TWCR=(1<<TWINT)|(1<<TWEN);//установка флагов для занесения данных в регистр
 while(!(TWCR&(1<<TWINT)));//ожидание установки флагов

 }

 void SendByte_Addr(unsigned char data, unsigned char Adress)
 {

 Start_I2C();//начало передачи
 Sendbyte_I2C(Adress);//в старший разряд передаем адрес
 Sendbyte_I2C(data);//в младший передаем данные
 Stop_I2C();//конец передачи

 }

 unsigned char Readbyte_I2C(void)
 {

 TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//формируем запрос на данные
 while(!(TWCR&(1<<TWINT)));//ожидаем 
 return TWDR;//получаем данные от ведомого 
 }

 unsigned char ReadLast_byte(void)
 {
 TWCR=(1<<TWINT)|(1<<TWEA);//формируем запрос на данные
 while(!(TWCR&(1<<TWINT)));//ожидаем 
 return TWDR;//получаем данные от ведомого

 }