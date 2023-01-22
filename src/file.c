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

#include "file.h"

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
int file_nbline(FILE *pf)
{
	char ligne[10];
  char *p = NULL;
  int cptl=1;
  
  if(pf)
  {
    while(fgets(ligne,sizeof(ligne),pf))
    {
    	p = strchr(ligne,'\n'); /*recherche le \n*/
    	if(p) /*on l'a trouve*/
    		  cptl++;
    }
  }
  else 
  	cptl = -1;

  return cptl;
}


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
int
file_size(FILE *pf)
{
	if(pf)
	{
		fseek(pf,0,SEEK_SET);
		fseek(pf,0,SEEK_END);
		return ftell(pf);
	}
else return 0;
}


/* ---------------------------------------------------------------------
   file_exist()
   ---------------------------------------------------------------------
   Role : dit si un fichier est ouvrable ou pas.
   ---------------------------------------------------------------------
   E : flux
   S : 1 ok, 0 sinon
   --------------------------------------------------------------------- 
   Notes : 
   ----------------------------------------------------------------------*/
unsigned int
file_exist(char *path)
{
	FILE *pf = fopen(path,"w");
	if(pf)
	{
		fclose(pf);
		remove(path);
		return 1;
	}
	else
		return 0;
}

