/*
 * PWMconfig.c
 *
 * Created: 26/11/2022 11:41:25 p. m.
 *  Author: mille
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PWMconfig.h"

void PWMconfig ()
{
	////////// TIMER 1
	
	TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	
	TCCR0B |= (1 << CS00) | (1 << CS01);
	TCCR0B &= ~(1 << CS02);
	
	TIMSK0 |= (1 << TOIE0);
	
	OCR0A = 0;
	
	///////// TIMER 2
	
	TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
	
	TCCR2B |= (1 << CS22);
	TCCR2B &= ~(1 << CS21) & ~(1 << CS20);
	
	TIMSK2 |= (1 << TOIE2);
	
	OCR2A = 0;
	
}

ISR(TIMER0_OVF_vect)
{
	OCR0A = (dutycycle1 / 100.0) * 255;
}

ISR(TIMER2_OVF_vect)
{
	OCR2A = (dutycycle2 / 100.0) * 255;
}