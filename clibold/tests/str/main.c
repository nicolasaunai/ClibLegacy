#include "str.h"

void truc()
{
	char ligne[10];
  char *buf,*buf_tmp,*p;
  int cpt=0,sizet=0,size;
  
  while(fgets(ligne,sizeof(ligne),stdin))
  {
  	p = strchr(ligne,'\n'); /*recherche le \n*/
  	if(p && !cpt) /*on l'a trouve du premier coup*/
  	{
  		p = 0; /*on le supprime*/
  		size = strlen(ligne); /*recupere la taille*/
  		buf = malloc(size); /*alloue un buffer de la taille qui va bien*/
  		if(buf)
  			strcpy(buf,ligne);
  		break;
  	}
  	else if(p && cpt) /*on l'a trouve, mais pas au 1er coup*/
  	{
  		p = 0;
  		size = strlen(ligne); /*recupere la taille*/
  		buf_tmp = realloc(buf,sizet + size);
  		if(buf_tmp)
  		{
  			buf = buf_tmp;
  			strcat(buf,ligne);
  			break;
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
  printf("=> %s\n",buf);
  printf("taille = %d\n",strlen(buf));
  free(buf);
}

int main(int argc, char *argv[])
{
  FILE *pf = fopen("test.txt","r");
  char **tab;
  int i;
  int nb=0;
  printf("nbre de lignes a lire\n");
  scanf("%d",&nb);
  printf("\n");
  if(pf)
  {
  	tab = str_readnline(pf,nb);
  	for(i=0;i<nb;i++)
  		printf("%d : %s      taille = %d\n",i,tab[i],strlen(tab[i]));
  	fclose(pf);
  }
  
  return 0;
}
