/*
 * RoboCartV1.c
 *
 * Created: 21/11/2022 6:10:19 p. m.
 * Author : Miller Ortiz
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usart.h"
#include "PWMconfig.h"


int main(void)
{
	DDRD = 0xFE;
	DDRB = 0x1C;
	
	int meta = 0;
	
	PWMconfig();
	
	UARTinit();

	sei();
	
    while (1) 
    {
		actua(YBuffer, XBuffer, &dutycycle1, &dutycycle2);
		
		if (sensar(0x01) && sensar(0x02))
		{
			UART_write_txt("S1 S2");
			PORTB |= (1 << PINB2) | (1 << PINB4);
			meta = meta + 1;
			if (meta == 1)
				UART_write_txt("GO");
			if (meta == 2)
			{
				UART_write_txt("END");
				meta = 0;
			}
		}
		else if (sensar(0x01) && !sensar(0x02))
		{
			UART_write_txt("S1");
			PORTB |= (1 << PINB2);
			PORTB &=~(1 << PINB4);
		}
		else if (sensar(0x02) && !sensar(0x01))
		{
			UART_write_txt("S2");
			PORTB |= (1 << PINB4);
			PORTB &=~(1 << PINB2);
		}
			
		else
		{
			UART_write_txt("OFF");
			PORTB &=~(1 << PINB2);
			PORTB &=~(1 << PINB4);
		}
		
			
    }
}

