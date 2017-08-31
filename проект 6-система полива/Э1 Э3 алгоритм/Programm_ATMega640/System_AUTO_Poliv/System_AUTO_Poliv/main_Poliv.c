/*
 * System_AUTO_Poliv.c
 *
 * Created: 22.03.2017 13:49:48
 * Author : Dante_L_Levi
 */ 

#include "Main.h"



int main(void)
{
	
	USART0_INIT(103);
	USART2_INIT(103);
	TWI_init();
	USART0_puts('S');
	USART0_puts(0x0a);
	USART0_puts(0x0d);
	USART0_putsString("Blethooth");
	USART2_putsString("RF-Module");
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

