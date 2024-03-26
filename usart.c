/*
 * usart.c
 *
 * Created: 18/11/2022 6:09:38 p. m.
 *  Author: Miller Ortiz
 */ 
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

void UARTinit() // PARA INICIAR USART EN MODO ASINCRONICO; 9600 BAUDIOS; 1 BIT DE STOP; SIN PARIDAD
{
	//DDRD &= ~(1 << 0); // PD0 ENTRADA RX
	//DDRD |= (1 << 1); // PD1 SALIDA TX
	
	UCSR0C &= ~(1 << UMSEL01); //Modo asincrono
	UCSR0C &= ~(1 << UMSEL00);
	
	UCSR0C &=~(1 << UPM00);// Paridad desactivada
	UCSR0C &=~(1 << UPM01);
	
	UCSR0C &=~(1 << USBS0); //1 bit stop
	
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); //8 bits
	UCSR0B &=~(1 << UCSZ02);
	
	UCSR0A &=~(1 << U2X0);
	
	UBRR0H = (MYUBRR >> 8); //9600
	UBRR0L = MYUBRR; 
	
	UCSR0B |= (1 << TXEN0);
	UCSR0B |= (1 << RXEN0);
	
	UCSR0B |= (1 << RXCIE0); // Habilita interrupcíón por RX
}

unsigned char UARTread()
{
	if (UCSR0A & (1 << RXC0)) // recepcion completa
		return UDR0; 
	else
		return 0;
}

void UART_write(unsigned char caracter)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = caracter;
}

void UART_write_txt(char* cadena)
{
	while (*cadena != 0x00)
	{
		UART_write(*cadena);
		cadena++;
	}
}

ISR(USART_RX_vect)
{
	if (xyflag == 0)
	{
		xyflag = 1;
		XBuffer = UDR0;
	}
	else
	{
		xyflag = 0;
		YBuffer = UDR0;
	}
}