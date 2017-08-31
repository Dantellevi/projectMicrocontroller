#ifndef USART_H_
#define USART_H_

#include "Main.h"
#include <stdlib.h>
#include <stdio.h>

unsigned char data_recive;
void Usart_init(unsigned int speed);
void Transmit_char_usart(unsigned char data);
void Transmit_str_usart(char*str);
void Transmit_int(int data);
unsigned char Get_char_usart(void);


#endif /* USART_H_ */