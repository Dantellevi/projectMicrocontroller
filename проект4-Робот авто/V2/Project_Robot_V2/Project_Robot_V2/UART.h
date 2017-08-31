/*
 * UART.h
 *
 * Created: 10.11.2016 15:16:37
 *  Author: DANTE_L_LEVI
 */ 


#ifndef UART_H_
#define UART_H_

#include "Main.h"




void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
void Transmit_string( char s[]);





#endif /* UART_H_ */