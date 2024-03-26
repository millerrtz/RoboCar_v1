/*
 * Sensar.c
 *
 * Created: 28/11/2022 12:24:04 a. m.
 *  Author: mille
 */ 
#include <avr/io.h>

int sensar (unsigned char sensor)
{
	if (PINB & sensor)
		return 1;
	else
		return 0;
}