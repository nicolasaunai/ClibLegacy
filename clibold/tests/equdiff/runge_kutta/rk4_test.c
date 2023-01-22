/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : resolution RK4
   Module       : EQUDIFF
   Fichier      : rk4_test.c
   Creation     : 23-11-2004
   Modification : 03-12-2004
   --------------------------------------------------------------------- 
   Notes : Ce fichier résoud un systeme differentiel du premier ordre
   a l'aide de l'algorithme de runge kutta d'ordre 4
   J'ai fait le test de deux fonctions differentes, rk4 est la fonction
   du magistere un peu modifiee, rknr provient des numerical recipes   
   ---------------------------------------------------------------------*/

#include "..\..\gnuplot\gnuplot.h" /*commandes GNUplot*/
#include "algo\rk4.h"								 /*algorithme de runge kutta d'ordre 4*/

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

void
sdnr(double t,double q[],double dq[])
{
	dq[0] = q[1];
	dq[1] = -q[0];
}


int main(void)
{
  int i,np;
  double q[N],q0[N],t,t0,dt,tfin,qnr[N],dqnr[N];

  /*creation d'une macro GNUplot*/
  MAC *m = new_macro("macro.gpm");

  /*definition des using pour les courbes GNUplot*/
  unsigned int **usg = (unsigned int**)mat_new(4,2,sizeof(**usg),sizeof(*usg));
  if(usg)
  {
  	usg[0][0]=1; usg[0][1]=2;
  	usg[1][0]=1; usg[1][1]=3;
  	usg[2][0]=1; usg[2][1]=4;
  	usg[3][0]=1; usg[3][1]=5;
  }
  int styles[4] = {LINES,LINES,POINTS,POINTS};

  /*donnons un titre a chaque courbe*/
  char *titles[4] = {"q_1","q_2","q_nr1","q_nr2"};

	RANGE r;
	r.range_auto = 0;
	r.xmin = -10;
	r.xmax = 10;
	r.ymin = -10;
	r.ymax = 10;

  FILE *fich = fopen("rk4.res","w");

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
    	q[i] = q0[i];   		
    	qnr[i] = q0[i];
    }
    
    t = t0;


    for(i=0; i<=np; i++)		/*calcul*/
    {     
      fprintf(fich,"%lg %lg %lg %lg %lg\n",t,q[0],q[1],qnr[0],qnr[1]);/*impression des resultats*/
      rk4(sd1,q,t,dt,N);/*resolution rk4*/
      sd1(qnr,t,dqnr,4);									  								
      rk4nr(qnr,dqnr,N,t,dt,qnr,sdnr);
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
    	 								 ,"D:\\Developpement\\Code C-C++\\magistere\\equdiff\\runge_kutta\\rk4.res"
    	 								 ,4
    	 								 ,styles
    	 								 ,titles
    	 								 ,NULL
    	 								 ,usg);
    	 print_plot_config(m->plot_cfg);
    	 
       plot(m);
       printf(" ok plot fini\n");
       free_macro(m);
    }
    else
    	fprintf(stderr,"erreur macro\n");
    
  }
  else fprintf(stderr,"erreur ouverture fichier\n");
  return 0;    
}
