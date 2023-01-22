/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : resolution EULER
   Module       : EQUDIFF
   Fichier      : euler.h
   Creation     : 20-11-2004
   Modification : 20-11-2004
   --------------------------------------------------------------------- */

#ifndef _EULER_H_
#define _EULER_H_

#include <stdio.h>
#include <stdlib.h>

/* ---------------------------------------------------------------------
   euler_sca()
   ---------------------------------------------------------------------
   Role : Algorithme d'euler pour la resolution d'equation differentielles
   ---------------------------------------------------------------------
   E : Pointeur sur l'equation differentielle a resoudre
   E : fonction
   E : variable de q
   S : dq/dt
   ---------------------------------------------------------------------
   Notes : L'equation differentielle est de la forme dq/dt = f(q,t)	
   --------------------------------------------------------------------- */
double euler_sca(double (*ed)(double,double),double q,double t,double dt);



/* ---------------------------------------------------------------------
   euler_vec()
   ---------------------------------------------------------------------
   Role : Algorithme d'euler pour la resolution d'un systeme
   d'equations differentielles
   ---------------------------------------------------------------------
   E : Pointeur sur le systeme a resoudre
   E : vecteur de fonctions
   E : variable de q
   E : pas
   E : nombre d'equations du systeme
   S : 1 ok, 0 sinon
   ---------------------------------------------------------------------
   Notes : L'equation differentielle est de la forme dq/dt = f(q,t)	
   --------------------------------------------------------------------- */
unsigned int euler_vec(void (*ed)(double*,double,double *,int)
								 			 ,double q[]
								 		   ,double t
								 		   ,double dt
								 			 ,unsigned int n);

#endif
