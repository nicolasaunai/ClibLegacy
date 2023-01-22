/* ---------------------------------------------------------------------
   NA 2006
   Projet       : -
   Fonction     : comparatif des algorithmes d'equation differentielles
   Module       : EQUDIFF
   Fichier      : compare_algo.c
   Creation     : 23-11-2004
   Modification : 25-10-2006
   --------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <rk4.h>								 /*algorithme de runge kutta d'ordre 4*/
#include <euler.h>
#include <step.h>

#define N 2 /*taille du systeme*/

/*systeme differentiel
dq1/dt = q2
dq2/dt = -q1*/
void
sd(double t,const double *q, double *qp, size_t n, const void *param)
{
  qp[0] = -q[1];   /*0 : cos, 1 : sin*/
  qp[1] = q[0];
}

void
sd2(double x,const double *q, double *qp, size_t size,const void *param)
{

  int n = *(int*)param;

  qp[0] = -pow(q[1],n) -2*q[0]/x; /*boucle vs pow pour exposant entier ? (alexis)*/
  qp[1] = q[0];
}



void
sd3(double x,const double *q, double *qp, size_t size,const void *param)
{
  qp[0] = -1./3; /*boucle vs pow pour exposant entier ? (alexis)*/
  qp[1] = q[0];
}


int main(void)
{
  int i,np;
  double q1[N],q2[N],t,dt;

	STEP *h = step_new(0.001,0.001);

  FILE *fich = fopen("../data/compare.out","w");

    /*q1[0]=1.; q2[0]=1.;						
    q1[1]=0.; q2[1]=0.;*/
    q1[0]=0; q1[1] = 1;
    q2[0]=0; q2[1] = 1;	
    					
    np=10000;							/*fin*/
    dt=0.0001;							/*pas fonction de l'intervalle*/
    int n = 1;
	t = 0;
	int j;
	double err1,err2;
	
	FILE *fdt = fopen("../data/dt_err.out","w");
	
	for(j=0; j<40; j++)
	{
		    for(i=0; i<np; i++)		/*calcul*/
		    { 
		    	/*impression des resultats*/   
		    	if(t <1e-4)
		    		{
		    			rk4(q1,2,t,dt,q1,sd3,&n);
		      			euler_vec(q2,2,t,dt,q2,sd3,&n);
		      			 
		      			err1 = fabs(1-q1[1]);
		      			err2 = fabs(1-q2[1]);
		    		} 
		    	else
		    		{
		      			rk4(q1,2,t,dt,q1,sd2,&n);
		      			euler_vec(q2,2,t,dt,q2,sd2,&n);
		    		} 
		      t += dt;	
		      if(err1 <= fabs(sin(t)/t-q1[1]))													/*incrementation par le pas 'dt'*/
		      	err1 = fabs(sin(t)/t-q1[1]);
		      if(err2 <= fabs(sin(t)/t-q2[1]))
		      err2 = fabs(sin(t)/t-q2[1]);
		      
		      if(j == 0)
		      	fprintf(fich,"%lg %lg %lg %lg %lg %lg\n",t,q1[1],q2[1],q3[1],err1,err2);
		    }
		    fprintf(fdt,"%lg %lg %lg\n",dt,err1,err2);
		    dt *= 1.2;
	}
    /*fermeture du fichier de resultats*/
    fclose(fich);
    fclose(fdt);
    step_free(h);
   
  return 0;    
}
