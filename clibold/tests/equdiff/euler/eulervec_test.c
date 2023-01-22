/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : resolution EULER
   Module       : EQUDIFF
   Fichier      : eulervec_test.c
   Creation     : 20-11-2004
   Modification : 23-11-2004
   --------------------------------------------------------------------- */

#include "..\..\gnuplot\gnuplot.h" /*commandes GNUplot*/
#include "algo\euler.h"								 /*algorithme d'Euler*/

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
  double q[N],q0[N],t,t0,dt,tfin;

  /*creation d'une macro GNUplot*/
  MAC *m = new_macro("macro.gpm");
  /*definition des using pour les courbes GNUplot*/
  unsigned int **usg = (unsigned int**)mat_new(2,2,sizeof(**usg),sizeof(*usg));
  if(usg)
  {
  	usg[0][0]=1; usg[0][1]=2;
  	usg[1][0]=1; usg[1][1]=3; 
  }

  FILE *fich = fopen("euler.res","w");

  if(fich)
  {
    t0=0.; 								/*condition initiale pour t*/
    q0[0]=1.; 						/*condition initiale q1(t0)*/
    q0[1]=0.;							/*condition initiale q2(t0)*/
    q0[2]=2.;
    np=100;								/*fin*/
    tfin=10.; 						/*valeur finale choisie pour t*/
    dt=(tfin-t0)/(np-1);	/*pas fonction de l'intervalle*/
    
    /*initialisation*/
    for(i=0; i<N; i++)
    	q[i] = q0[i];   		
    t = t0;


    for(i=0; i<=np; i++)		/*calcul*/
    {
      fprintf(fich,"%lg %lg %lg \n",t,q[0],q[1]);		/*impression des resultats*/
      euler_vec(sd1,q,t,dt,N); 									  					/*systeme d'equation diff*/
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
    	 								 ,"D:\\Developpement\\Code C-C++\\magistere\\equdiff\\euler\\euler.res"
    	 								 ,N
    	 								 ,NULL
    	 								 ,NULL
    	 								 ,NULL
    	 								 ,usg);

       plot(m);
       free_macro(m);
    }
    else
    	fprintf(stderr,"erreur macro\n");
    
  }
  else fprintf(stderr,"erreur ouverture fichier\n");
  return 0;    
}
