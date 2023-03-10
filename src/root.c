/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : Recherche de z?ro de fonction
   Module       : CLIB/ROOT
   Fichier      : root.h
   Creation     : 23-02-2005
   Modification : 23-02-2005
   --------------------------------------------------------------------- */

#include "root.h"

/* ---------------------------------------------------------------------
   rtnewt()
   ---------------------------------------------------------------------
   Role : avance d'un pas dans l'algorithme de newton dimension 1
   ---------------------------------------------------------------------
   E : retourne la derivee et la fonction en un point
   E : x1,x2 : intervalle ou se trouve la racine
   S  : racine
   ---------------------------------------------------------------------
   Notes : On utilise la m?thode de Newton Raphson pour trouver la
   racine d'une equatin dont on sait qu'elle se situe dans l'intervalle
   [x1;x2]. La racine rtn va etre approximee tant que la precision
   voulue est atteinte. funcd est une fonction utilisateur retournant
   la valeur de la fonction et la derivee au point x.
   --------------------------------------------------------------------- */

double rtnewt(void (*funcd)(double, double *, double *,const void *),
						 double x1, double x2,
						 double xacc,const  void *data)
{
	int j;
	double df,dx,f,rtn;
	rtn=0.5*(x1+x2);  /*1er essai : au milieu de l'intervalle*/

	for (j=1;j<=MAXIT;j++)
	{
		(*funcd)(rtn,&f,&df,data);
		dx=f/df;
		rtn -= dx;  /*formule de Newton*/				

	  if (fabs(dx) < xacc)
	  	return rtn; /*Convergence.*/
  }
  
  return 0.0;
}

