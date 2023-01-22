/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : divers algorithmes simples, max/min, tris etc...
   Module       : CLIB/ALGO
   Fichier      : algos.h
   Creation     : 20-02-2005
   Modification : 20-02-2005
   --------------------------------------------------------------------- */

#include "algos.h"

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
void
max_d(double *tab,double *m,int *ind,size_t n)
{
	int i;
	if(tab && m && ind)
	{
		*m = tab[0]; 							/*init.*/
		*ind = 0;
		for(i=0;i<n;i++)					/*recherche*/
		{
			if(*m <= tab[i]) /*si m >= tab[i]*/
			{
				*m = tab[i];					/*on garde la valeur...*/
				*ind = i;							/*... et la position*/	
			}
		}
	}
}


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
void
min_d(double *tab,double *m,int *ind,size_t n)
{
	int i;
	if(tab && m && ind)
	{
		*m = tab[0]; 							/*init.*/
		*ind = 0;
		for(i=0;i<n;i++)					/*recherche*/
		{
			if(*m >= tab[i]) /*si m >= tab[i]*/
			{
				*m = tab[i];					/*on garde la valeur...*/
				*ind = i;							/*... et la position*/	
			}
		}
	}
}
