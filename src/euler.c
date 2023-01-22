/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : resolution EULER
   Module       : EQUDIFF
   Fichier      : euler.h
   Creation     : 20-11-2004
   Modification : 20-11-2004
   --------------------------------------------------------------------- */

#include "euler.h"

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
double euler_sca(double (*ed)(double,double),double q,double t,double dt)
{
	return q + dt*ed(t,q);
}

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
		       const void *data)
{
	int i;
	double *dxdy = malloc(n * sizeof(*dxdy)); /*vecteur des dq/dt*/
	if(dxdy)
	{
		derivs(x,y,dxdy,n,data); /*calcule dq/dt*/
		for(i=0; i<n; i++) /*met a jour tous les q[i]*/
			y[i] += h*dxdy[i];		
		free(dxdy);
		return 1;
	}
	else return 0;
}
