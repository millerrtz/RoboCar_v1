/*
 * actuacion.h
 *
 * Created: 26/11/2022 8:52:51 p. m.
 *  Author: mille
 */ 

#ifdef ACTUACION_H_
#define ACTUACION_H_

double actua (volatile signed char Ys, volatile signed char Xs, double *dc1, double *dc2);
void stop (double **dc1, double **dc2);
void adelante ();
void atras();

#endif
