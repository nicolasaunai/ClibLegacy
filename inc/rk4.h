/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : resolution RUNGE KUTTA ordre 4
   Module       : EQUDIFF
   Fichier      : rk4.c
   Creation     : 23-11-2004
   Modification : 25-03-2005
   --------------------------------------------------------------------- 
   Journal      
   1.0 - Ajout de void *data, permet a l'utilisateur de faire passer des
   parametres au systeme sous la forme qu'il veut. 
   ---------------------------------------------------------------------*/


#ifndef _RK4_H_
#define _RK4_H_

#define PM 4 					/*nombre d'ep de runge kutta*/
#define MAXSTEP 1000	                        /*prevent. boucle inf. rk4_pv*/
#include <math.h>			
#include "vect.h"			        /*allocation perso*/
#include "step.h"			        /*gestion des pas*/
#include "algos.h"		                /*algorithmes divers simples, ex : max/min*/



/* ---------------------------------------------------------------------
   rk4()
   ---------------------------------------------------------------------
   Role : Algorithme de runge kutta d'ordre 4 pour la resolution 
   d'equation differentielles d'ordre 1
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

   ALGORITHME RUNGE-KUTTA ordre 4 : 
   p1 = f(t,q(t))
   p2 = f(t+dt/2, q(t) + dt/2*p1)
   p3 = f(t+dt/2, q(t) + dt/2*p2)
   p4 = f(t+dt, q(t) + dt*p3)

   q(t+dt) = q(t) + dt/6 * (p1 + 2*p2 + 2*p3 + p4)
   --------------------------------------------------------------------- 
   Notes : On donne les valeurs des variable dans y[0..n-1] et de leur
   derivees dans dydx[0..n-1] au point x, et utilise l'algorithme de 
   runge kutta d'ordre 4 pour incrementer la solution d'un pas h et
   retourner la solution dans le tableau yout[0..n-1] qui n'a pas besoin
   d'etre different du tableau y.
   L'utilisateur fournit la fonction derivs(x,y,dy,n,param), qui retourne les
   derivees dy de y au point x.
   --------------------------------------------------------------------- */
void rk4(double y[], 
	 int n,
	 double x,
	 double h,
	 double yout[],
	 void (*derivs)(double,const double *, double *,size_t,const void *),
	 const void *data);










/* ---------------------------------------------------------------------
   rk4_pv()
   ---------------------------------------------------------------------
   Role : Algorithme de Runge-Kutta d'ordre 4 a pas adaptatif 
   cf. Numerical recipes pour l'evaluation de l'erreur
   ---------------------------------------------------------------------
   E : Ytin = donnees au temps tin
   E : tin = temps de départ du pas
   E : h = structure de pas, pas fait et pas suivant cf STEP.h
   E : n = nombre d'equations
   E : precis = precision demandee
   E : derivs = derivee des fonctions
   E : data = parametres du systeme
   S : - 
   ---------------------------------------------------------------------
   Notes : L'utilisateur fournit les donnees Ytin[0..n-1] au temps 'tin'
   des 'n' equations, la fonction avance d'un pas 'h.hnext' selon la 
   precision 'precis' demandee.
   ---------------------------------------------------------------------*/
void rk4_pv(double *Ytin,
	    double tin,
	    STEP *h,
	    int n, 
	    double precis,
	    void(*derivs)(double,const double *,double *,size_t,const void *),
	    const void *data);







/* ---------------------------------------------------------------------
   rk4naul()
   ---------------------------------------------------------------------
   Role : Algorithme de runge kutta d'ordre 4 pour la resolution 
   d'equation differentielles (fonction_magistere /home/enseignement/naulin)
   un peu modifiee
   ---------------------------------------------------------------------
   E : Pointeur sur le systeme a resoudre
   E : fonction
   E : variable de q
   S : dq/dt
   ---------------------------------------------------------------------
   Notes : L'equation differentielle est de la forme dq/dt = f(q,t)

   ALGORITHME RUNGE-KUTTA ordre 4 : 
   p1 = f(t,q(t))
   p2 = f(t+dt/2, q(t) + dt/2*p1)
   p3 = f(t+dt/2, q(t) + dt/2*p2)
   p4 = f(t+dt, q(t) + dt*p3)

   q(t+dt) = q(t) + dt/6 * (p1 + 2*p2 + 2*p3 + p4)
   --------------------------------------------------------------------- */
unsigned int
rk4naul(void(*sd)(double*,double,double*,int)
	,double q[]
	,double t
	,double dt
	,int n);


#endif
