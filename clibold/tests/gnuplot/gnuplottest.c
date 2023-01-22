/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : test du module GNUplot
   Module       : GNUPLOT
   Fichier      : gnuplottest.h
   Creation     : 21-11-2004
   Modification : 24-11-2004
   --------------------------------------------------------------------- 
   Journal : 
   21/11/2004 : 1 - creation du fichier, version testee
   23/11/2004 : 1 - mise a jour du test après maj du module
   ---------------------------------------------------------------------
   Notes : Ce module a ete cree pour facilite la creation de macro 
   pour le logiciel GNUplot. 
   La version courante permet de creer un fichier macro et d'utiliser la
   commande 'plot' afin de tracer un graphique de n courbes paramétrables. 	
   ---------------------------------------------------------------------*/


/*nous allons dans ce test creer une macro dont la tache est de
	tracer un graphique comprenant 3 courbes

	ce programme va creer dans son repertoire un fichier "macro.gpm"

il est utilisable dans gnuplot en faisant : 

load 'macro.gpm'

*/


#include "gnuplot.h" /*insertion du header GNUplot*/

/*nombre de courbes*/
#define N 2					



int main(void)
{
  /*creation d'une macro GNUplot
  MAC est le type pour une macro, il doit etre obligatoirement déclaré
  comme un pointeur.*/
  MAC *m = new_macro("macro.gpm");
  printf("test\n");

  /*definition des using*/
  int **usg = mat_new_i(2,2);
  if(usg)
  {
  	usg[0][0]=2; usg[0][1]=3;
  	usg[1][0]=4; usg[1][1]=5; 
  }

  /*Definition des styles pour chaque courbes*/
  int styles[2] = {LINES,LINES};

  /*definition des titres de chaque courbe*/
  char *titles[2] = {"Terre","Lune"};

  /*Par defaut GNUplot ne demande pas d'intervalle pour tracer
  le graphique, on peut neanmoins en preciser un, ici : [0:10][0:10]*/
	RANGE r;
	r.range_auto = 0;
	r.xmin = 0;
	r.xmax = 10;
	r.ymin = 0;
	r.ymax = 10;
  
  /*La macro est-elle bien creee ?*/
   if(m)
   {
   		/*Configuration des parametres du graphiques avant de tracer*/
    	 set_plot_config(m
    	 								 ,"D:\\Developpement\\Code C-C++\\magistere\\3corps\\res\\rk4.res"
    	 								 ,N
    	 								 ,styles		/*NULL par defaut*/
    	 								 ,titles 		/*NULL par defaut*/
    	 								 ,&r 				/*NULL par defaut*/
    	 								 ,usg);
    	 printf("\n");

    	 /*fonction de debugging, permet d'afficher les parametres
    	 de la fonction plot, attribues par set_plot_config()*/
    	 print_plot_config(m->plot_cfg);
    	 printf("\n");
    	 
    	 /*les parametres sont definis il reste a ecrire la commande*/
    	 plot(m);


    	 /*une fois l'ecriture de macro terminee, on libere la memoire*/
       free_macro(m);
    }

  return 0;
}
