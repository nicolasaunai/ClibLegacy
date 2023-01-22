/*test de newton-raphson*/

#include <stdio.h>
#include <stdlib.h>
#include "root.h"

/*parametres du systeme*/
typedef struct _param
{
	double alpha;
} PARAM;



void
f(double x,double *fx,double *dfx)
{
	*fx = x*x -2;
	*dfx = 2*x;
}

void
G1(double Q1,double *G1Q1,double *dG1Q1,void *param)
{
	PARAM *p = param;
	double mu = p->alpha;

	*G1Q1 = (1-mu)/pow(Q1+mu,2) + mu/pow(Q1+mu-1,2) - Q1;
	*dG1Q1 = -2*((1-mu)*pow(Q1+mu,-3) + mu*pow(Q1+mu-1,-3)) - 1;
}

int main(void)
{
	double root = 0;
	PARAM p = {0.1};
	root = rtnewt(G1,1,2,0.005,&p);
	printf("x0 = %lg\n",root);
	
	return 0;
}
