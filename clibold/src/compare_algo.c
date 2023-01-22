/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : comparatif des algorithmes d'equation differentielles
   Module       : EQUDIFF
   Fichier      : compare_algo.c
   Creation     : 23-11-2004
   Modification : 23-11-2004
   --------------------------------------------------------------------- */

#include "..\..\gnuplot\gnuplot.h" 										/*commandes GNUplot*/
#include "..\runge_kutta\algo\rk4.h"								 /*algorithme de runge kutta d'ordre 4*/
#include "..\euler\algo\euler.h"

#define N 2 /*taille du systeme*/

/*systeme differentiel
dq1/dt = q2
dq2/dt = -q1*/
void
sd1(double q[],double t,double qp[],int n)
{
	qp[0] = q[1];
	qp[1] = -q[0];
}



int main(void)
{
  int i,np;
  double q1[N],q2[N],q0[N],t,t0,dt,tfin;

  /*creation d'une macro GNUplot*/
  MAC *m = new_macro("macro.gpm");

  /*definition des using pour les courbes GNUplot*/
  unsigned int **usg = (unsigned int**)mat_new(6,2,sizeof(**usg),sizeof(*usg));
  if(usg)
  {
  	usg[0][0]=1; usg[0][1]=2;
  	usg[1][0]=1; usg[1][1]=3;
  	usg[2][0]=1; usg[2][1]=4;
  	usg[3][0]=1; usg[3][1]=5;
  	usg[4][0]=1; usg[4][1]=6;
  	usg[5][0]=1; usg[5][1]=7;
  }
  int styles[6] = {LINES,LINES,POINTS,POINTS,LINES,LINES};
  char *titres[6] ={"q1_e","q2_e","q1_r","q1_r","dq1","dq2"};

  FILE *fich = fopen("compare.res","w");

  if(fich)
  {
    t0=0.; 								/*condition initiale pour t*/
    q0[0]=1.; 						/*condition initiale q1(t0)*/
    q0[1]=0.;							/*condition initiale q2(t0)*/
    np=100;								/*fin*/
    tfin=6.28; 						/*valeur finale choisie pour t*/
    dt=(tfin-t0)/(np-1);	/*pas fonction de l'intervalle*/
    
    /*initialisation aux conditions initiales q0*/
    for(i=0; i<N; i++)
    {
    	q1[i] = q0[i];   		
    	q2[i] = q0[i];
    }
    t = t0;


    for(i=0; i<=np; i++)		/*calcul*/
    { 
    	/*impression des resultats*/     
      fprintf(fich,"%lg %lg %lg %lg %lg %lg %lg \n",t,q1[0],q1[1],q2[0],q2[1],q2[0]-q1[0],q2[1]-q1[1]);
      rk4(sd1,q1,t,dt,N); 									  								/*resolution rk4*/
      euler_vec(sd1,q2,t,dt,N);															/*resolution euler*/
      t += dt; 																							/*incrementation par le pas 'dt'*/
    }

    /*fermeture du fichier de resultats*/
    fclose(fich);
    
    /*******************
    ECRITURE DE LA MACRO
    ********************/
    if(m)
    {
    	 set_plot_config(m
    	 								 ,"D:\\Developpement\\Code C-C++\\magistere\\equdiff\\comparatif\\compare.res"
    	 								 ,6
    	 								 ,styles
    	 								 ,titres
    	 								 ,NULL
    	 								 ,usg);
    	 print_plot_config(m->plot_cfg);

       plot(m);

       free_macro(m);
    }
    else
    	fprintf(stderr,"erreur macro\n");
    
  }
  else fprintf(stderr,"erreur ouverture fichier\n");
  return 0;    
}
