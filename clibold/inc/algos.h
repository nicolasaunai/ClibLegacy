/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : divers algorithmes simples, max/min, tris etc...
   Module       : CLIB/ALGO
   Fichier      : algos.h
   Creation     : 20-02-2005
   Modification : 20-02-2005
   --------------------------------------------------------------------- */


#ifndef _ALGO_H_
#define _ALGO_H_

#include <stdlib.h>

#define MAX(a,b) (a >= b)?a:b

/* ---------------------------------------------------------------------
   max()
   ---------------------------------------------------------------------
   Role : retourne le max d'un tableau de double ainsi que sa position
   ---------------------------------------------------------------------
   E : tableau de double
   E : m = max
   E : ind = indice du max
   E : n = taille du tableau
   S : -
   ---------------------------------------------------------------------
   Notes : 
   --------------------------------------------------------------------- */
void max_d(double *tab,double *m,int *ind,size_t n);


/* ---------------------------------------------------------------------
   min()
   ---------------------------------------------------------------------
   Role : retourne le min d'un tableau de double ainsi que sa position
   ---------------------------------------------------------------------
   E : tableau de double
   E : m = min
   E : ind = indice du min
   E : n = taille du tableau
   ---------------------------------------------------------------------
   Notes : 
   --------------------------------------------------------------------- */
void min_d(double *tab,double *m,int *ind,size_t n);


#endif
