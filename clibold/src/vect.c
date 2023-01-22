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
void *
vect_new(size_t len, size_t size_type)
{
  void *v = malloc(len * size_type);
  return v;
}

/* ---------------------------------------------------------------------
   vect_free()
   ---------------------------------------------------------------------
   Role : destructeur de vect
   ---------------------------------------------------------------------
   E : vect - adresse du vecteur a detruire
   S : -
   --------------------------------------------------------------------- */
void
vect_free(void *vect)
{
  if(vect)  free(vect); /*que ce passe-t-il si vect == NULL ?*/
}



/* ---------------------------------------------------------------------
   mat_new_d()
   ---------------------------------------------------------------------
   Role : constructeur de matrice de double
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   E : ncol - nombre de colones
   S : adresse de la matrice
   --------------------------------------------------------------------- */
double **
mat_new_d(unsigned int nrow, unsigned int ncol)
{
  int i,j;
  double **m = malloc(nrow * sizeof(double*));
  if(m)
  {
    for(i=0; i<nrow; i++)
    {
        m[i] = malloc(ncol * sizeof(double));
        if(!m[i])
        {
           for(j=0; j<=i; j++)
               free(m[i]);
           free(m);
           m = NULL;
        }
    }
  }
  return m;
}



/* ---------------------------------------------------------------------
   mat_free_d()
   ---------------------------------------------------------------------
   Role : destructeur de matrice
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   --------------------------------------------------------------------- */
void
mat_free_d(double **m,unsigned int nrow)
{
  int i;
  if(m)
  {
    for(i=0; i<nrow; i++)
        if(m[i])
            free(m[i]);
    free(m);
  }
}

/* ---------------------------------------------------------------------
   mat_new_i()
   ---------------------------------------------------------------------
   Role : constructeur de matrice de int
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   E : ncol - nombre de colones
   S : adresse de la matrice
   --------------------------------------------------------------------- */
int **
mat_new_i(unsigned int nrow, unsigned int ncol)
{
  int i,j;
  int **m = malloc(nrow * sizeof(int*));
  if(m)
  {
    for(i=0; i<nrow; i++)
    {
        m[i] = malloc(ncol * sizeof(int));
        if(!m[i])
        {
           for(j=0; j<=i; j++)
               free(m[i]);
           free(m);
           m = NULL;
        }
    }
  }
  return m;
}



/* ---------------------------------------------------------------------
   mat_free_i()
   ---------------------------------------------------------------------
   Role : destructeur de matrice
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   --------------------------------------------------------------------- */
void
mat_free_i(int **m,unsigned int nrow)
{
  int i;
  if(m)
  {
    for(i=0; i<nrow; i++)
        if(m[i])
            free(m[i]);
    free(m);
  }
}


/* ---------------------------------------------------------------------
   mat_new_c()
   ---------------------------------------------------------------------
   Role : constructeur de matrice de char
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   E : ncol - nombre de colones
   S : adresse de la matrice
   --------------------------------------------------------------------- */
char **
mat_new_c(unsigned int nrow, unsigned int ncol)
{
  int i,j;
  char **m = malloc(nrow * sizeof(char*));
  if(m)
  {
    for(i=0; i<nrow; i++)
    {
        m[i] = malloc(ncol * sizeof(char));
        if(!m[i])
        {
           for(j=0; j<=i; j++)
               free(m[i]);
           free(m);
           m = NULL;
        }
    }
  }
  return m;
}



/* ---------------------------------------------------------------------
   mat_free_c()
   ---------------------------------------------------------------------
   Role : destructeur de matrice
   ---------------------------------------------------------------------
   E : nrow - nombre de lignes
   --------------------------------------------------------------------- */
void
mat_free_c(char **m,unsigned int nrow)
{
  int i;
  if(m)
  {
    for(i=0; i<nrow; i++)
        if(m[i])
            free(m[i]);
    free(m);
  }
}
