/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : gestion des chaines de caracteres
   Module       : STR
   Fichier      : str.h
   Creation     : 19-12-2004
   Modification : 19-12-2004
   --------------------------------------------------------------------- 
   Journal : 
   19/12/2004 : 1 - creation du fichier, version testee
   ---------------------------------------------------------------------
   Notes : 
   ---------------------------------------------------------------------*/

#ifndef _STR_H_
#define _STR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------------
   str_readnline()
   ---------------------------------------------------------------------
   Role : lire n ligne sur un flux
   ---------------------------------------------------------------------
   E : flux
   E : nombre de lignes a lire
   S : tableau des chaines lues
   --------------------------------------------------------------------- */
char **str_readnline(FILE *pf,unsigned int n);




#endif
