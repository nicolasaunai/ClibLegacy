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

#ifndef _GNUPLOT_H_
#define _GNUPLOT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vect.h" /*allocations vecteurs/matrices*/

enum styles /*non encore tous utiles*/
{
  DEFAULT=0,
  LINES,
	POINTS,
	LINESPOINTS,
	IMPULSES,
	DOTS,
	STEPS,
	FSTEPS,
	HISTEPS,
	ERRORBARS,
	XERRORBARS,
	YERRORBARS,
	XYERRORBARS,
	ERRORLINES,
	XERRORLINES,
	YERRORLINES,
	XYERRORLINES,
	BOXES,
	FILLEDCURVES,
	BOXEERRORBARS,
	BOXXYERRORBARS,
	FINANCEBARS,
	CANDLESTICKS,
	VECTORS
};

/*structure representant l'intervalle
pour le graphe GNUplot*/
typedef struct _range
{
	double xmin,xmax,ymin,ymax;
	unsigned int range_auto;
}RANGE;


/*represente les parametres
de la commande 'plot' de GNUplot*/
typedef struct _plot_conf
{
	int  *style;			 					/*ex : with {LINES,DOTS,LINES,IMPULSES}*/
	char **title;								/*n titres des courbes*/
	char *filename;						 	/*nom du fichier source*/
	int nplot;									/*nombre de courbes a tracer*/
	int **usg;			 	 					/*colones a utiliser 1:2, 1:3 => {{1,2}
															  															 {1,3}}*/
	RANGE *rge; 								/*[-1:4][-10:22] */
	unsigned int ok;						/*1 si set_plot_config, 0 sinon*/
}PLOT_CONF;


/*represente les parametres
de la macro GNUplot*/
typedef struct _mac
{
	char *name; 					/*nom du fichier macro (pas chemin)*/
	FILE *fich;						/*adresse du fichier macro*/
  unsigned int openned; /*0 = no, 1 = yes*/
  int first;						/*1 si pas encore ouvert 1 fois, 0 sinon*/
  PLOT_CONF *plot_cfg;  /*config du plot*/
} MAC;



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
MAC * new_macro(char name[]);


/* ---------------------------------------------------------------------
   free_macro()
   ---------------------------------------------------------------------
   Role : Destruction d'une macro
   ---------------------------------------------------------------------
   E : pointeur sur la macro a detruire
   S : adresse de la macro
   --------------------------------------------------------------------- */
void free_macro(MAC *);


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
   elle retourne 0
   La fonction set_plot_config doit etre obligatoirement utilisee avant
   la fonction plot()
   Voir gnuplottest.c pour un exemple d'utilisation.
   ---------------------------------------------------------------------*/
unsigned int set_plot_config(MAC *
														,char pathname[]
														,unsigned int n
														,int *style
														,char **title
														,RANGE *rge
														,int **usg);



/* ---------------------------------------------------------------------
   open_macro()
   ---------------------------------------------------------------------
   Role : ouverture du fichier macro
   ---------------------------------------------------------------------
   E : adresse de la macro
   S : 0 = erreur, 1 sinon
   --------------------------------------------------------------------- */
unsigned int open_macro(MAC *);


/* ---------------------------------------------------------------------
   close_macro()
   ---------------------------------------------------------------------
   Role : fermeture du fichier macro
   ---------------------------------------------------------------------
   E : adresse de la macro
   S : -
   --------------------------------------------------------------------- */
void close_macro(MAC *);


/* ---------------------------------------------------------------------
   plot()
   ---------------------------------------------------------------------
   Role : inserer une commande plot dans la macro
   ---------------------------------------------------------------------
   E : pointeur sur une macro
   E : nom du fichier source a tracer
   E : tableau de [n][2] pour le using, n = nombre de courbes et chaque 
   ligne précise les colones du fichier servant pour x et y
   S : - 
   --------------------------------------------------------------------- 
   Notes : 
   * pathname doit etre le chemin complet du fichier source. 
   
   * les numero de colone commencent a 1 (c'est le 'using' de la commande
   GNUplot)

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
unsigned int plot(MAC *);


/* ---------------------------------------------------------------------
   newline()
   ---------------------------------------------------------------------
   Role : Saute une ligne dans le fichier macro
   ---------------------------------------------------------------------
   E : pointeur sur la macro
   S : 1 = ok, 0 sinon
   ---------------------------------------------------------------------
   Notes : -	
   --------------------------------------------------------------------- */
unsigned int newline(MAC*);



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
PLOT_CONF *new_plot_config(void);


/* ---------------------------------------------------------------------
   free_plot_config()
   ---------------------------------------------------------------------
   Role : Destruction d'une _plot_cfg
   ---------------------------------------------------------------------
   E : pointeur sur la config
   S : -
   --------------------------------------------------------------------- */
void free_plot_config(PLOT_CONF *);


/* ---------------------------------------------------------------------
   new_plot_range()
   ---------------------------------------------------------------------
   Role : construction d'un range
   ---------------------------------------------------------------------
   E : range auto 1 si oui, 0 sinon
   S : -
   --------------------------------------------------------------------- */
RANGE *new_plot_range(unsigned int );


/* ---------------------------------------------------------------------
   print_plot_config()
   ---------------------------------------------------------------------
   Role : affiche une _plot_cfg
   ---------------------------------------------------------------------
   E : pointeur sur la config
   S : -
   --------------------------------------------------------------------- */
void print_plot_config(PLOT_CONF *);


/* ---------------------------------------------------------------------
   max()
   ---------------------------------------------------------------------
   Role : retourne la taille de la chaine de plus grande taille
   ---------------------------------------------------------------------
   E : tableau de chaines
   E : taille du tableau
   S : max
   --------------------------------------------------------------------- */
unsigned int max(char *tab[],unsigned int n);

#endif
