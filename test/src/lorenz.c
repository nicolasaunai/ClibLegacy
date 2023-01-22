
#include <stdio.h>
#include <stdlib.h>
#include <rk4.h>
#include <vect.h>
#include <math.h>

#define N 10000000
#define PI acos(-1.)

typedef struct _plorenz
{
  double Pr;
  double b;
  double Ra;
} PLORENZ;



/*const void * CONST param 
afin que la valeur pointee de nsoit pas modifiee --> optimisations*/

void
sd(double t,const double *q, double *qp, size_t n, const void *param)
{
  PLORENZ *p = (PLORENZ*)param;
  
  qp[0] = p->Pr*(q[1]-q[0]);
  qp[1] = (p->Ra - q[2])*q[0]-q[1];
  qp[2] = q[0]*q[1]-p->b*q[2];
}



void decale(double *t,int s)
{
	int i;
	double *tmp = malloc(s*sizeof(double));
	
	for(i=0;i<s;i++)
	{
		tmp[i] = t[i];
	}	
	for(i=1;i<s;i++)
	{
		t[i] = tmp[i-1];
	}
	free(tmp);
}


int main(void)
{
  int i;
  double q[3];
  
  PLORENZ param;
  param.Pr = 10;
  param.b = 8./3;
  param.Ra = 28;
  
  q[0] = 2;
  q[1] = 2;
  q[2] = 3;
  double x = 0.;
  double h = 0.001;
  
  int j=0,dj=99;
  double qdt2[3] = {0,0,0};	
	
  /*double qi=0;
  double qj=0;
  double qk=0;*/
  double qdt[48] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



  FILE *fres = fopen("../data/lorenz.out","w");
  if(!fres)
    {
      printf("erreur ouverture fichier 'data/lorenz.out' - exit\n");
      return EXIT_FAILURE;
    }


  FILE *fres2 = fopen("../data/lorenzX.out","w");
  if(!fres2)
    {
      printf("erreur ouverture fichier 'data/lorenzX.out' - exit\n");
      return EXIT_FAILURE;
    }
    
    

  for(i=0;i<N;i++)
    {
      rk4(q,3,x,h,q,sd,&param);
      x += h; 
      fprintf(fres,"%lg %lg %lg %lg\n",x,q[0],q[1],q[2]);
      dj++;
      if(dj == 100)
      {
      	dj = 1;
      	qdt2[j] = q[1];
      	j++;	
      }
      if(j==3)
      {
      	j=0;
      	fprintf(fres2,"%lg %lg %lg\n",qdt2[0],qdt2[1],qdt2[2]);		
      }
      /*decale(qdt,48);*/
      /*for(j=12;j>=1; j--)
      {
      	qdt[j] = qdt[j-1];	
      }*/
      /*qdt[5] = qdt[4];
      qdt[4] = qdt[3];
      qdt[3] = qdt[2];
      qdt[2] = qdt[1];
      qdt[1] = qdt[0];*/ 
      /*qdt[0] = q[1];*/
      /*qk = qj;
      qj = qi;
      qi = q[0]; mcourant*/
    }


  fclose(fres);
  fclose(fres2);
  
  
  return EXIT_SUCCESS;
}
