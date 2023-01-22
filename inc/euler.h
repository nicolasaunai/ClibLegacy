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
   E : y[]    - valeurs des n variables
   E : n      - nombre d'equations
   E : x      - variable de y
   E : h      - pas
   E : yout   - tableau de sortie, peut etre identique a y
   E : derivs - fonction derivee, fournie par l'utilisateur
   E : data   -  parametres du systeme
   S : - 
   ---------------------------------------------------------------------
   Notes : L'equation differentielle est de la forme dq/dt = f(q,t)	
   --------------------------------------------------------------------- */
unsigned int euler_vec(double y[],
		       int n,
		       double x,
		       double h,
		       double yout[],
		       void (*derivs)(double, const double *, double *,size_t,const void *),
		       const void *data);

#endif
