
#include <stdio.h>
#include <stdlib.h>
#include <rk4.h>
#include <vect.h>
#include <math.h>

#define N 1000
#define PI acos(-1.)


/*
  q[0] := z
  q[1] := y
  z'= -y^n - 2z/x
  y' = z
*/
void
sd2(double x,const double *q, double *qp, size_t size,const void *param)
{

  int n = *(int*)param;

  qp[0] = q[1]*q[0];
  qp[1] = -n*q[0];
}


/*const void * CONST param 
afin que la valeur pointee de nsoit pas modifiee --> optimisations*/

void
sd(double t,const double *q, double *qp, size_t n, const void *param)
{
  qp[0] = -q[1];   /*0 : cos, 1 : sin*/
  qp[1] = q[0];
}




int main(void)
{
  int i;
  double q[2];
  
  q[0] = 500;
  q[1] = 10;
  double x = 0.;
  double h = 0.01;
  int n = 40;


  FILE *fres = fopen("../data/res.out","w");
  if(!fres)
    {
      printf("erreur ouverture fichier 'data/fres.out' - exit\n");
      vect_free(q);
      return EXIT_FAILURE;
    }



  for(i=0;i<N;i++)
    {
      rk4(q,2,x,h,q,sd2,&n);
      x += h; 
      fprintf(fres,"%lg %lg %lg\n",x,q[0],q[1]);
    }


  fclose(fres);

  return EXIT_SUCCESS;
}
