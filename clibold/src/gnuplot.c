/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : MACRO GNUPLOT
   Module       : GNUPLOT
   Fichier      : gnuplot.h
   Creation     : 20-11-2004
   Modification : 23-11-2004
   --------------------------------------------------------------------- 
   Journal : 
   20/11/2004 : 1 - creation du fichier, version testee
   							2 - constructeurs/destructeurs
   							3 - open/close _macro
   							4 - commande plot rudimentaire

   21/11/2004   1 - ajout des styles de courbe
   							2 - possibilité de preciser l'intervalle du graphe
   							
   23/11/2004   1 - modification des styles, chaque courbe a son propre
   									style, qu'il faut configurer avec un tableau
   							2 - L'utilisateur peut désormais preciser le titre de 
   								  chaque courbe.

   ---------------------------------------------------------------------
   Notes : Ce module a ete cree pour facilite la creation de macro 
   pour le logiciel GNUplot   	
   ---------------------------------------------------------------------*/
#include "gnuplot.h"


/* ---------------------------------------------------------------------
   new_macro()
   ---------------------------------------------------------------------
   Role : Création d'une macro
   ---------------------------------------------------------------------
   E : nom du fichier macro
   S : adresse de la macro
   ---------------------------------------------------------------------
   Notes : name est le nom du fichier macro uniquement, pas de chemin 	
   --------------------------------------------------------------------- */
MAC * 
new_macro(char name[])
{
	MAC *m = malloc(sizeof(*m));
	if(m)
	{
		m->name = malloc(sizeof *(m->name)*strlen(name));
		if(m->name)
		{
			strcpy(m->name,name);
			m->fich = NULL;
			m->first = 1;
			m->openned = 0;
			
			m->plot_cfg = new_plot_config(); /*allocation config*/
  		if(!m->plot_cfg) /*echec allocation*/
  		{
  					free(m->name);
  					free(m);
  					m = NULL;
   		}
		}
		else if(!m->name) /*si allocation pathname echoue*/
		{
			free(m); /*destruction macro*/
			m = NULL; /*pour retourner null*/
		}
	}
	return m;	
}


/* ---------------------------------------------------------------------
   free_macro()
   ---------------------------------------------------------------------
   Role : Destruction d'une macro
   ---------------------------------------------------------------------
   E : pointeur sur la macro a detruire
   S : adresse de la macro
   --------------------------------------------------------------------- */
void
free_macro(MAC *m)
{
	if(m)
	{
		if(m->name)
			free(m->name);
		if(m->openned)
			fclose(m->fich);
	  if(m->plot_cfg)
	  	free_plot_config(m->plot_cfg);
		free(m);
  }
}



/* ---------------------------------------------------------------------
   set_plot_config()
   ---------------------------------------------------------------------
   Role : defini la configuration d'une commande plot
   ---------------------------------------------------------------------
   E : pointeur sur la macro
   E : nom du fichier de donnees (chemin absolu)
   E : nombre de courbes a tracer sur le graphe
   E : tableau de styles style : ex {LINES,DOTS,LINES} cf enum
   E : tableau de titres pour chq courbe
   E : intervalle en x, en y, structure de type RANGE, NULL pour laisser
   			GNUplot determiner automatiquement l'intervalle
   E : tableau de using
   S : 1 ok, 0 sinon
   --------------------------------------------------------------------- 
   Notes : si tout se passe bien, 'set_plot_config()' retourne 1, sinon
   elle retourne 0, les differents cas d'erreur sont : 
   * macro invalide (NULL)
   * erreur allocation des titres
   * erreur allocation des styles
   * erreur allocation filename
   * erreur allocation usg

   La fonction set_plot_config doit etre obligatoirement utilisee avant
   la fonction plot()
   Voir gnuplottest.c pour un exemple d'utilisation.
   ---------------------------------------------------------------------*/
unsigned int 
set_plot_config(MAC *m
							 ,char pathname[]
							 ,unsigned int n
							 ,int *style
							 ,char **title
							 ,RANGE *rge
							 ,int **usg)
{
	int i,j;
	
	if(m)/*si la macro est valide*/
	{	
		/*initialisations*/
		m->plot_cfg->nplot = n; /*nombre de courbes*/ 

 	 /**********************************************************************

 	 											GESTION DES TITRES DE COURBES

    ***********************************************************************/	
		if(title) /*si l'utilisateur precise des titres perso*/
		{
			/*tableau de pointeurs*/
			m->plot_cfg->title = vect_new(n,sizeof(*m->plot_cfg->title));
			if(m->plot_cfg->title)
			{
				for(i=0; i<n; i++)
				{
					/*allocation de la chaine a la taille qui va bien*/
					m->plot_cfg->title[i] = vect_new(strlen(title[i]),sizeof(*m->plot_cfg->title[i]));
						if(!m->plot_cfg->title[i])/*si echoue*/
						{
							for(j=0;j<i;j++)/*on libere les precedents*/
								vect_free(m->plot_cfg->title[j]);
							
							/*on libere le 1er vecteur et remet a NULL*/
							vect_free(m->plot_cfg->title);
							m->plot_cfg->title = NULL;
							/*et on quitte*/
							return 0;
						}
				}
			}
			else
				return 0;

		 /*tout c'est bien passe, on recopie les titres*/
		 for(i=0; i<n; i++)	
		 	strcpy(m->plot_cfg->title[i],title[i]);
		}
		else /*titres par defaut*/
		{
			m->plot_cfg->title = mat_new_c(n,5);
			if(m->plot_cfg->title)
			{
				for(i=0;i<n;i++)
					sprintf(m->plot_cfg->title[i],"q%d",i+1);
			}
		}	

 	 /**********************************************************************

												GESTION DES STYLES DES COURBES

    ***********************************************************************/	
		if(style)	/*si l'utilisateur precise des styles*/
		{
			/*allocation des styles*/
			m->plot_cfg->style = malloc(n * sizeof(*m->plot_cfg->style));
			if(!m->plot_cfg->style) /*echec allocation*/
			{
				for(i=0;i<n;i++)/*liberation des titres*/
					vect_free(m->plot_cfg->title[i]);
				vect_free(m->plot_cfg->title);
				m->plot_cfg->title = NULL;
				return 0;
			}

			for(i=0;i<n;i++)
				m->plot_cfg->style[i] = style[i];	
		}

 	 /**********************************************************************

 	 																FILENAME

    ***********************************************************************/	
		/*allocation du nom de fichier source*/
		m->plot_cfg->filename = malloc(strlen(pathname)*sizeof(*(m->plot_cfg->filename)));
		if(m->plot_cfg->filename)
			strcpy(m->plot_cfg->filename,pathname);/*initialisation de filename*/
  
		else /*echec allocation filename, on quitte en 0*/
		{
			for(i=0;i<n;i++)/*liberation des titres*/
					vect_free(m->plot_cfg->title[i]);
				vect_free(m->plot_cfg->title);
				m->plot_cfg->title = NULL;

				vect_free(m->plot_cfg->style);/*on libere les styles*/
				m->plot_cfg->style = NULL;
			return 0;
		}


 	 /**********************************************************************

 	 													DEFINITION DU RANGE

    ***********************************************************************/
		if(rge)
		{
		  	if(!rge->range_auto)/*si range precise par utilisateur*/
		  	{
  			  	m->plot_cfg->rge->xmin = rge->xmin;
  			  	m->plot_cfg->rge->xmax = rge->xmax;
  			  	m->plot_cfg->rge->ymin = rge->ymin;
  			  	m->plot_cfg->rge->ymax = rge->ymax;
  			  	m->plot_cfg->rge->range_auto = rge->range_auto;
  			}
  			else /*range auto*/
  				m->plot_cfg->rge->range_auto = rge->range_auto;
  	}
  	else /*rge = NULL, l'utilisateur veut un intervalle auto*/
  			m->plot_cfg->rge->range_auto = 1;
  

 	 /**********************************************************************

 	 													GESTION DES USING

    ***********************************************************************/
		/*allocation du using*/
		if(usg)
		{
		  m->plot_cfg->usg = mat_new_i(n,2);
  		if(m->plot_cfg->usg)
  		{
  			  	for(i=0;i<n;i++)/*initialisation du using*/
  							for(j=0;j<2;j++)
  									m->plot_cfg->usg[i][j] = usg[i][j];
  		}
  		else/*si echec allocation using on libere ce qui a ete alloue,remet a NULL, et on quitte*/
  		{
  			  	free(m->plot_cfg->filename);/*liberation du filename*/
  			  	m->plot_cfg->filename = NULL;
  			  	free(m->plot_cfg->rge);			/*liberation du range*/
  			  	m->plot_cfg->rge = NULL;
  			  	for(i=0;i<n;i++)/*liberation des titres*/
					  		vect_free(m->plot_cfg->title[i]);
					  vect_free(m->plot_cfg->title);
					  m->plot_cfg->title = NULL;

				    vect_free(m->plot_cfg->style);/*on libere les styles*/
				    m->plot_cfg->style = NULL;
  			  	return 0;
  		}
  	}
	}
	else	/*macro invalide*/
		return 0;

	m->plot_cfg->ok = 1;
	return 1; /*si tout c bien passe, ret=1*/
}



/* ---------------------------------------------------------------------
   open_macro()
   ---------------------------------------------------------------------
   Role : ouverture du fichier macro
   ---------------------------------------------------------------------
   E : adresse de la macro
   E : nom du fichier
   S : 0 = erreur, 1 sinon
   --------------------------------------------------------------------- */
unsigned int
open_macro(MAC *m)
{
	unsigned int ret = 1;

	if(m)
	{
		if(m->first)/*1ere ouverture, on ouvre en ecriture*/
			m->fich = fopen(m->name,"w");
		else 
			m->fich = fopen(m->name,"a+");

		if(m->fich)
			m->openned = 1;
	  else ret = 0;
	}
	else ret = 0;

	return ret;
}


/* ---------------------------------------------------------------------
   close_macro()
   ---------------------------------------------------------------------
   Role : fermeture du fichier macro
   ---------------------------------------------------------------------
   E : adresse de la macro
   S : -
   --------------------------------------------------------------------- */
void close_macro(MAC *m)
{
	if(m)
		if(m->openned)
		{ 
			fclose(m->fich);
			m->openned = 0;
			if(m->first) m->first = 0; /*si la macro ete ouverte pour la 1ere fois...*/
		}
}


/* ---------------------------------------------------------------------
   plot()
   ---------------------------------------------------------------------
   Role : inserer une commande plot dans la macro
   ---------------------------------------------------------------------
   E : pointeur sur une macro
   S : 1 ok, 0 sinon
   --------------------------------------------------------------------- 
   Notes : 
   * ATTENTION 'plot' va echouer si la structure de configuration n'a pas
   ete definie avant. (i.e. si set_plot_config() n'a pas ete appelee

   * ATTENTION : Sous windows le caractere '\' separant les noms de repertoires 
   doivent etre precedes du caractere d'echappement '\' lors de l'appel de la 
   fonction sinon le fichier macro sera invalide...

   * ATTENTION : l'existence du fichier source est sous responsabilite de 
   l'utilisateur, notons qu'il serait possible de faire verifier l'existence
   de ce fichier par 'plot()', cependant les carateres d'echappement de la
   chaine de caractere rendent invalide l'argument de 'fopen()', il faudrait 
   parser la chaine et les enlever... ce qui demanderait pour le faire
   proprement des fonctions d'analyse de chaine...
   --------------------------------------------------------------------- */
unsigned int
plot(MAC *m)
{
 size_t lenpath;
 char *com,*com2,*com3;
 int i,len;
 unsigned int size_style = 20; /*taille d'un style en caractere fixee a 20*/
 char **style; 	/*tableau de n chaines de 20 caracteres*/
 char com_tmp[40];
 unsigned int max_title = 20;

 /*format de la commande 'plot'*/
 char format1[] = "'%s' using %d:%d  title '%s' with %s";
 char format2[] = "'%s' using %d:%d  title '%s' with %s, ";

 if(m) /*si la macro existe bien*/
 {
 	 /**********************************************************************

 	 												VERIFICATIONS SECURITE

    ***********************************************************************/	

   if(!m->plot_cfg->ok) /*verifie que le plot a ete configure*/
   {
   		fprintf(stderr,"il faut configurer le plot avec set_plot_config()\n");
   		close_macro(m); /*fermeture de la macro*/
   		return 0;
   }
   
   if(!m->openned) /*si elle n'est pas ouverte*/
   		open_macro(m);

   if(m->first)
   {
   		fprintf(m->fich,"# (c) NA 2004 Module GNUplotC\n");
      fprintf(m->fich,"# macro Gnuplot generee automatiquement\n\n");
   }    


 	 /**********************************************************************

 	 										DEFINITION DU STYLE DES COURBES

    ***********************************************************************/

   /*allocation*/
   style = mat_new_c(m->plot_cfg->nplot,size_style);   
   if(!style)	/*echec allocation*/
   {
   		close_macro(m);	/*fermeture de la macro*/
   		return 0;
   }
   
   if(m->plot_cfg->style) /*l'utilisateur a defini des styles perso*/
     for(i=0; i<m->plot_cfg->nplot;i++)/*recopie des styles utilisateurs*/
       switch(m->plot_cfg->style[i])
       {
       		case LINES:
       			strcpy(style[i],"lines");break;
       		case POINTS:
       			strcpy(style[i],"points");break;
       		case LINESPOINTS:
       			strcpy(style[i],"linespoints");break;		
       		case IMPULSES:
       			strcpy(style[i],"impulses");break;
       		case DOTS:
       			strcpy(style[i],"dots");break;
       		case STEPS:
       			strcpy(style[i],"steps");break;
       		case FSTEPS:
       			strcpy(style[i],"fsteps");break;
       		case HISTEPS:
       			strcpy(style[i],"histeps");break;
       		case ERRORBARS:
       			strcpy(style[i],"errorbars");break;
       		case XERRORBARS:
       			strcpy(style[i],"errorbars");break;
       	  case DEFAULT:
       	  	strcpy(style[i],"lines");break;
       	  default:/**/
       	  	strcpy(style[i],"lines");break;
       }
      else /*l'utilisateur veut tous les styles par defaut*/
      	for(i=0; i<m->plot_cfg->nplot; i++)
      		strcpy(style[i],"lines");
   
 	 /**********************************************************************

 	 										 ECRITURE DE LA COMMANDE 'PLOT'

    ***********************************************************************/
   /*lencom = strlen(com1) + strlen(com2);*/
   lenpath = strlen(m->plot_cfg->filename);
   max_title = max(m->plot_cfg->title,m->plot_cfg->nplot);
   /*allocation chaine commande*/
   len = strlen(com_tmp)+ (strlen(format2) + strlen(m->plot_cfg->filename) + size_style + max_title)*m->plot_cfg->nplot;
   com = malloc(len*sizeof(*com));
   com2 = malloc((len-5)*sizeof(*com2));
   com3 = malloc((lenpath + strlen(format2))*sizeof(*com3));

   if(com && com2 && com3)
   {
   	 for(i=0; i<m->plot_cfg->nplot; i++)
   	 {
     	 if(i == m->plot_cfg->nplot-1) /*dernier plot sans virgule au bout*/
     	 {
     	 		sprintf(com3,format1
     	 		  					,m->plot_cfg->filename,m->plot_cfg->usg[i][0]
     	 				  			,m->plot_cfg->usg[i][1]
     	 				  			 ,m->plot_cfg->title[i]
     	 				  			 ,style[i]);
     	 }
     	 else
     	 {/*tous les premiers plot sont suivis d'une virgule*/
     	 		sprintf(com3,format2
     	 							  ,m->plot_cfg->filename,m->plot_cfg->usg[i][0]
     	 							  ,m->plot_cfg->usg[i][1]
     	 							  ,m->plot_cfg->title[i]
     	 							  ,style[i]);

     	 	/*1ere iteration on copie, et ensuite on concatène*/
     	 	(i==0)?strcpy(com2,com3):strcat(com2,com3);
     	 }
     }
     if(!m->plot_cfg->rge->range_auto)/*si range perso*/
     {
     	sprintf(com_tmp,"plot [%lg:%lg][%lg:%lg] ",m->plot_cfg->rge->xmin
     																						,m->plot_cfg->rge->xmax
     																						,m->plot_cfg->rge->ymin
     																						,m->plot_cfg->rge->ymax);
      strcpy(com,com_tmp);
     }
     else
     	strcpy(com,"plot ");

     strcat(com2,com3);
     strcat(com,com2);
     fprintf(m->fich,"%s\n",com);
     free(com);
     free(com2);
     free(com3);
   }
   close_macro(m);
 }
 return 1; 
}   


/* ---------------------------------------------------------------------
   newline()
   ---------------------------------------------------------------------
   Role : Saute une ligne dans le fichier macro
   ---------------------------------------------------------------------
   E : pointeur sur la macro
   S : 1 = ok; 0 sinon
   ---------------------------------------------------------------------
   Notes : -	
   --------------------------------------------------------------------- */
unsigned int
newline(MAC *m)
{
	unsigned int ret = 1;
	if(m)
	{
		if(m->openned)
			fprintf(m->fich,"\n");
		else 
		{
  		open_macro(m);
			fprintf(m->fich,"\n");
		}
	}
	else ret = 0;

	return ret;
}



/***************************************************************************

													FONCTIONS PRIVEES ET DEBUG

*****************************************************************************/


/* ---------------------------------------------------------------------
   new_plot_config()
   ---------------------------------------------------------------------
   Role : construction d'une _plot_cfg
   ---------------------------------------------------------------------
   E : -
   S : pointeur sur la config creee
   --------------------------------------------------------------------- */
PLOT_CONF *new_plot_config(void)
{
		PLOT_CONF *p = malloc(sizeof(*p)); /*allocation config*/
		if(p)
		{
			p->style = NULL; 						/*no style*/
			p->title = NULL; 						/*no title*/
			p->filename = NULL;					/*no filename*/
			p->usg = NULL;								/*no using*/
			p->nplot = 1;								/*default value*/
			p->ok = 0;									/*set_plot_config pas utilisee*/
			p->rge = new_plot_range(1); /*range auto par defaut*/
			if(!p->rge)
				free(p);
		}
		return p;
}


/* ---------------------------------------------------------------------
   free_plot_config()
   ---------------------------------------------------------------------
   Role : Destruction d'une _plot_cfg
   ---------------------------------------------------------------------
   E : pointeur sur la config
   S : -
   --------------------------------------------------------------------- */
void
free_plot_config(PLOT_CONF *plot_cfg)
{
	if(plot_cfg)
	{
		if(plot_cfg->rge) free(plot_cfg->rge);
		if(plot_cfg->usg) mat_free_i(plot_cfg->usg,plot_cfg->nplot);
		if(plot_cfg->filename) free(plot_cfg->filename);
		vect_free(plot_cfg->style);
		mat_free_c(plot_cfg->title,plot_cfg->nplot);
		free(plot_cfg);
	}
}


/* ---------------------------------------------------------------------
   new_plot_range()
   ---------------------------------------------------------------------
   Role : construction d'un range
   ---------------------------------------------------------------------
   E : range auto 1 si oui, 0 sinon
   S : -
   --------------------------------------------------------------------- */
RANGE *
new_plot_range(unsigned int a)
{
	RANGE *r = malloc(sizeof(*r));
	if(r)
	{
		r->xmin = 0;
		r->xmax = 0;
		r->ymin = 0;
		r->ymax = 0;
		r->range_auto = a;
	}
	return r;
}


/* ---------------------------------------------------------------------
   print_plot_config()
   ---------------------------------------------------------------------
   Role : affiche une _plot_cfg
   ---------------------------------------------------------------------
   E : pointeur sur la config
   S : -
   --------------------------------------------------------------------- */
void
print_plot_config(PLOT_CONF *p)
{
	int i,j;
	printf("config du plot\n");
	printf("**************\n");
	
	printf("style : \n");
	if(p->style)
	for(i=0;i<p->nplot;i++)
		printf("%d ; ",p->style[i]);
	else printf("styles par defaut\n");

	printf("\nfilename : %s\n",p->filename);
	printf("nombre de courbes : %d\n",p->nplot);
	
	printf("usings : \n");
	for(i=0; i<p->nplot; i++)
	{
		for(j=0;j<2;j++)
		{
			(j==0)?printf("%d",p->usg[i][j]):printf(":%d\n",p->usg[i][j]);
		}
	}
	
	printf("titres : \n");
	if(p->title)
	for(i=0;i<p->nplot;i++)
		printf("%s\n",p->title[i]);
	else printf("pas de titres\n");

	if(p->rge)
	{
		printf("ranges : \n");
		printf("[%lg:%lg][%lg:%lg]\n",p->rge->xmin,p->rge->xmax,p->rge->ymin,p->rge->ymax);
	}
}



/* ---------------------------------------------------------------------
   max()
   ---------------------------------------------------------------------
   Role : retourne la taille de la chaine de plus grande taille
   ---------------------------------------------------------------------
   E : tableau de chaines
   E : taille du tableau
   S : max
   --------------------------------------------------------------------- */
unsigned int
max(char *tab[],unsigned int n)
{
	int i,m = strlen(tab[0]);
	for(i=1; i<n;i++)
		m = (m < strlen(tab[i]))?strlen(tab[i]):m;

		return m;
}
