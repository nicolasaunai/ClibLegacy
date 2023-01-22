#include <stdio.h>
#include <stdlib.h>
#include "rk4.h"
#include "step.h"

#define N 2

/*parametres du systeme*/
typedef struct _param
{
	double alpha;
} PARAM;


/*systeme differentiel*/
void
sdnr(double t,const double *q,double *dq,size_t n,const void *param)
{
	const PARAM *p = param; /*barbare : tester param*/
	double al = p->alpha;
	dq[0] = q[1];
	dq[1] = -q[0]*al*t*t;
}



int main(int argc, char *argv[])
{
  int i;
  double t,tfin,q[N],q0[N],qf[0],dt;

  /*pas variable*/
  STEP *h = step_new(0,0);

  /*fichiers de resultat*/
  FILE *fich = fopen("rk4_pv.txt","w");
  FILE * fichf = fopen("rk4_pf.txt","w");


  PARAM p = {1e-2}; /*initialisation barbare des parametres*/
  
  if(fich && fichf)
  {
    q0[0]=1.; 						/*condition initiale q1(t0)*/
    q0[1]=0;						/*condition initiale q2(t0)*/
    tfin=100; 						/*valeur finale choisie pour t*/
    
    dt = 0.001;						/*determination des pas fixe et initial*/
    step_put(h,0,0.1); /*ATTENTION A NE PAS METTRE DES PAS < CRITIC SINON PLANTAGE*/
    /*on remarque que si alpha diminue le pas doit augmenter sous peine de plantage*/

    /*initialisation aux conditions initiales q0*/
    for(i=0; i<N; i++)
    {
    	q[i] = q0[i]; 
    	qf[i] = q0[i];  	
    }
    

    for(t=0;t<tfin;t+=step_GetPrev(h))		/*calcul a pas var*/
    {     
      fprintf(fich,"%lg %lg %lg %lg\n",t,step_GetNext(h),q[0],q[1]);/*impression des resultats*/
      rk4_pv2(q,t,h,N,1e-8,sdnr,&p);					  								
    }
    for(t=0;t<tfin; t+=dt)/*calcul avec pas fixe*/
    {
    	fprintf(fichf,"%lg %lg %lg\n",t,qf[0],qf[1]);
    	rk4(qf,N,t,dt,qf,sdnr,&p);
    }

    /*fermeture du fichier de resultats*/
    fclose(fich);
    fclose(fichf);
   }
   else 	
   	fprintf(stderr,"bug fichier !! \n");

   return 0;
}
