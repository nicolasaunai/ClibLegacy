/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : gestion des fichiers
   Module       : FILE
   Fichier      : file.c
   Creation     : 19-12-2004
   Modification : 19-12-2004
   --------------------------------------------------------------------- 
   Journal : 
   19/12/2004 : 1 - creation du fichier, version testee
   02/01/2005 : 1 - Ajout de la fonction file_exist()
   ---------------------------------------------------------------------
   Notes : 
   ---------------------------------------------------------------------*/


#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------------
   file_nbline()
   ---------------------------------------------------------------------
   Role : retourne le nombre de ligne d'un fichier
   ---------------------------------------------------------------------
   E : flux
   S : nombre de lignes
   --------------------------------------------------------------------- 
   Notes : retourn -1 si le fichier n'existe pas
   ----------------------------------------------------------------------*/
int file_nbline(FILE *pf);

/* ---------------------------------------------------------------------
   file_size()
   ---------------------------------------------------------------------
   Role : retourne la taille en octets du fichier
   ---------------------------------------------------------------------
   E : flux
   S : taille
   --------------------------------------------------------------------- 
   Notes : retourn -1 si le fichier n'existe pas
   ----------------------------------------------------------------------*/
int file_size(FILE *pf);


/* ---------------------------------------------------------------------
   file_exist()
   ---------------------------------------------------------------------
   Role : dit si un fichier existe ou non (est ouvrable ou pas)
   ---------------------------------------------------------------------
   E : nom du fichier
   S : 1 ok, 0 sinon
   --------------------------------------------------------------------- 
   Notes : -
   ----------------------------------------------------------------------*/
unsigned int file_exist(char *);

#endif
