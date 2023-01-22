/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : allouer des vecteurs et matrices
   Module       : VECT
   Fichier      : vect.h
   Creation     : 21-11-2004
   Modification : 21-11-2004
   --------------------------------------------------------------------- 
   Journal : 
   21/11/2004 : 1 - creation du fichier, version testee
   							2 - constructeurs/destructeurs

   ---------------------------------------------------------------------
   Notes : Ce module a ete cree pour faciliter la creation de vecteurs et
   matrices de dimension n (et n*m)
   Il n'est pas evident de creer des matrices generiques parfaitement 
   portable (taille des pointeurs), on prefera des methodes specialisees
   pour chaque type char,int, double
   ---------------------------------------------------------------------*/

#ifndef _VECT_H_
#define _VECT_H_

#include <stdio.h>
#include <stdlib.h>

/* ---------------------------------------------------------------------
   vect_new()
   ---------------------------------------------------------------------
   Role : constructeur de vect_t
   ---------------------------------------------------------------------
   E : len : longueur du vecteur (nombre d'elements)
   E : size_type - taille du type contenu
   S : Pointeur sur vecteur
   --------------------------------------------------------------------- */
void *vect_new(size_t len, size_t size_type);


/* ---------------------------------------------------------------------
   vect_free()
   ---------------------------------------------------------------------
   Role : destructeur de vect
   ---------------------------------------------------------------------
   E : vect - adresse du vecteur a detruire
   S : -
   --------------------------------------------------------------------- */
void vect_free(void *vect);



/* ---------------------------------------------------------------------
   mat_new()
   ---------------------------------------------------------------------
   Role : constructeur de matrice
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   E : ncol - nombre de colones
   S : adresse de la matrice
   --------------------------------------------------------------------- */
double **mat_new_d(unsigned int nrow, unsigned int ncol);



/* ---------------------------------------------------------------------
   mat_free()
   ---------------------------------------------------------------------
   Role : destructeur de matrice
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   --------------------------------------------------------------------- */
void mat_free_d(double **m,unsigned int nrow);


/* ---------------------------------------------------------------------
   mat_new_i()
   ---------------------------------------------------------------------
   Role : constructeur de matrice
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   E : ncol - nombre de colones
   S : adresse de la matrice
   --------------------------------------------------------------------- */
int **mat_new_i(int nrow, unsigned int ncol);



/* ---------------------------------------------------------------------
   mat_free()
   ---------------------------------------------------------------------
   Role : destructeur de matrice
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   --------------------------------------------------------------------- */
void mat_free_i(int **m,unsigned int nrow);


/* ---------------------------------------------------------------------
   mat_new_c()
   ---------------------------------------------------------------------
   Role : constructeur de matrice
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   E : ncol - nombre de colones
   S : adresse de la matrice
   --------------------------------------------------------------------- */
char **mat_new_c(unsigned int nrow, unsigned int ncol);



/* ---------------------------------------------------------------------
   mat_free()
   ---------------------------------------------------------------------
   Role : destructeur de matrice
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   --------------------------------------------------------------------- */
void mat_free_c(char **m,unsigned int nrow);

#endif
