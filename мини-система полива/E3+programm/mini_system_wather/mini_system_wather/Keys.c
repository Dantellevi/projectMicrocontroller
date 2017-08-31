#include "KeyEVENTS.h"

int  KeyPrress(int Bits)
{
	
	
	if (!(PINC&(1<<Bits)))
	{
		_delay_ms(250);
		return 1;
	}
	else{
		
		return 0;
	}


	
}