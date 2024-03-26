/*
 * usart.h
 *
 * Created: 18/11/2022 6:10:01 p. m.
 *  Author: mille
 */ 

volatile signed char XBuffer;
volatile signed char YBuffer;

volatile unsigned char xyflag;

#ifdef USART_H_
#define USART_H_

void UARTinit();
unsigned char UARTread();
void UART_write(unsigned char caracter);
void UART_write_txt(char* cadena);

#endif

