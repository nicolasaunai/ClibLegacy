/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : gestion des chaines de caracteres
   Module       : STR
   Fichier      : str.c
   Creation     : 19-12-2004
   Modification : 19-12-2004
   --------------------------------------------------------------------- 
   Journal : 
   19/12/2004 : 1 - creation du fichier, version testee
   ---------------------------------------------------------------------
   Notes : 
   ---------------------------------------------------------------------*/

#include "str.h"


/* ---------------------------------------------------------------------
   str_readnline()
   ---------------------------------------------------------------------
   Role : lire n ligne sur un flux
   ---------------------------------------------------------------------
   E : flux
   E : nombre de lignes a lire
   S : tableau des chaines lues
   --------------------------------------------------------------------- */
char **
str_readnline(FILE *pf,unsigned int n)
{
	char ligne[10];
	char **tbuf=NULL;
  char *buf = NULL,*buf_tmp = NULL,*p = NULL,*ptmp;
  int cpt=0,sizet=0,size,cptl=0;
  
  tbuf = malloc(n*sizeof(*tbuf)); /*alloue le tableau de chaines*/
  if(tbuf)
  {
    while((ptmp=fgets(ligne,sizeof(ligne),pf)))
    {
    	p = strchr(ligne,'\n'); /*recherche le \n*/
    	
    	if(p && !cpt) /*on l'a trouve du premier coup*/
    	{
    		*p = 0; /*on le supprime*/
    		size = strlen(ligne); /*recupere la taille*/
    		buf = malloc(size); /*alloue un buffer de la taille qui va bien*/
    		if(buf)
    		{
    			strcpy(buf,ligne);
    			tbuf[cptl] = buf;
    		  cptl++;
    		  cpt = 0;
    		}
    	}
    	else if(p && cpt) /*on l'a trouve, mais pas au 1er coup*/
    	{
    		*p = 0;
    		size = strlen(ligne); /*recupere la taille*/
    		buf_tmp = realloc(buf,sizet + size);
    		if(buf_tmp)
    		{
    			buf = buf_tmp;
    			strcat(buf,ligne);
    			tbuf[cptl] = buf;
    			cptl++;
    			cpt = 0;
    		}
    	}
    	else if(!p && !cpt) /*1er coup, pas trouve*/
    	{
    		buf = malloc(sizeof(ligne)); /*on recopie dans un buffer*/
    		if(buf)
    		{
    			strcpy(buf,ligne);
    		  sizet += sizeof(ligne);
    		  cpt++;
    		}
    	}
    	else if(!p && cpt) /*pas trouve n-ieme coup*/
    	{
    		buf_tmp = realloc(buf,sizet + sizeof(ligne));
    		if(buf_tmp)	
    		{
    			buf = buf_tmp;
    		  strcat(buf,ligne);
    		  sizet += sizeof(ligne);
    		  cpt++;
    		}
    	}
    }
    if(!ptmp)
    {
    		tbuf[cptl] = buf;
    		cptl++;
    		cpt=0;
    }
  }
  return tbuf;
}
