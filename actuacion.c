/*
 * actuacion.c
 *
 * Created: 26/11/2022 8:53:09 p. m.
 *  Author: mille
 */
#include <avr/io.h>
#include <math.h>
#define PXMAX 125

void stop (double **dc1, double **dc2);
void adelante ();
void atras();
 
void actua (volatile signed char Ys, volatile signed char Xs, double *dc1, double *dc2)
{
	volatile signed int Y, X;
	volatile signed int pY, pX;
	
	Y = Ys;
	X = Xs;
	
	if (Y > 0)
	{
		adelante();
		
		pY = (Y * 60) / PXMAX;
		pX = ((fabs(X)) * pY) / PXMAX;
		
		if ((X >= -20) && (X <= 20))
		{
			*dc1 = pY;
			*dc2 = pY;
		}
		else if (X < -20) // ir a izquierda
		{
			*dc1 = pY - pX;
			*dc2 = pY;
		}
		else if (X > 20) // ir a derecha
		{
			*dc1 = pY;
			*dc2 = pY - pX;
		}
		
		else
			stop(&dc1, &dc2);
	}
	
	else if (Y < 0)
	{
		atras();
		
		pY = ((fabs(Y)) * 60) / PXMAX;
		pX = ((fabs(X)) * pY) / PXMAX;
		
		if ((X >= -20) && (X <= 20))
		{
			*dc1 = pY;
			*dc2 = pY;
		}
		else if (X < -20) // ir a izquierda
		{
			*dc1 = pY - pX;
			*dc2 = pY;
		}
		else if (X > 20) // ir a derecha
		{
			*dc1 = pY;
			*dc2 = pY - pX;
		}
		
		else
		stop(&dc1, &dc2);
	}
	
	else
		stop(&dc1, &dc2);
}

void stop (double **dc1, double **dc2)
{
	PORTD &=~(1 << PIND4) & ~(1 << PIND7);
	PORTD &=~(1 << PIND2) & ~(1 << PIND3);
	**dc1 = 0;
	**dc2 = 0;
}

void adelante ()
{
	PORTD |= (1 << PIND4) | (1 << PIND7);
	PORTD &=~(1 << PIND2) & ~(1 << PIND3);
}
void atras()
{
	PORTD &=~(1 << PIND4) & ~(1 << PIND7);
	PORTD |= (1 << PIND2) | (1 << PIND3);
}

