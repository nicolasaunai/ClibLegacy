/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : resolution RUNGE KUTTA ordre 4
   Module       : EQUDIFF
   Fichier      : rk4.c
   Creation     : 23-11-2004
   Modification : 22-02-2005
   --------------------------------------------------------------------- 
   Journal      
   1.0 - Ajout de void *data, permet a l'utilisateur de faire passer des
   parametres au systeme sous la forme qu'il veut. 
   ---------------------------------------------------------------------*/

#include "rk4.h"



/*------------------------------------------------------------------------
	FONCTIONS D'USAGE PUBLIC : 
	------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------
   rk4()
   ---------------------------------------------------------------------
   Role : Algorithme de runge kutta d'ordre 4 pour la resolution 
   d'equation differentielles d'ordre 1
   ---------------------------------------------------------------------
   E : valeurs des n variables
   E : nombre d'equations
   E : variable de y
   E : pas
   E : tableau de sortie, peut etre identique a y
   E : fonction derivee, fournie par l'utilisateur
   E : data = parametres du systeme
   S : - 
   ---------------------------------------------------------------------
   Notes : L'equation differentielle est de la forme dq/dt = f(q,t)

   ALGORITHME RUNGE-KUTTA ordre 4 : 
   p1 = f(t,q(t))
   p2 = f(t+dt/2, q(t) + dt/2*p1)
   p3 = f(t+dt/2, q(t) + dt/2*p2)
   p4 = f(t+dt, q(t) + dt*p3)

   q(t+dt) = q(t) + dt/6 * (p1 + 2*p2 + 2*p3 + p4)
   --------------------------------------------------------------------- 
   Notes : On donne les valeurs des variable dans y[0..n-1] et de leur
   derivees dans dydx[0..n-1] au point x, et utilise l'algorithme de 
   runge kutta d'ordre 4 pour incrementer la solution d'un pas h et
   retourner la solution dans le tableau yout[0..n-1] qui n'a pas besoin
   d'etre different du tableau y.
   L'utilisateur fournit la fonction derivs(x,y,dy,n,param), qui retourne les
   derivees dy de y au point x.
   --------------------------------------------------------------------- */
void 
rk4(double y[], int n, double x, double h, double yout[],
		void (*derivs)(double, const double *, double *,size_t,const void *),
		const void *data)
{
	int i;
	double xh,hh,h6,*dym,*dyt,*yt,*dydx;

	dym = vect_new(n,sizeof (*dym));
	dyt = vect_new(n,sizeof (*dyt));
	yt = vect_new(n,sizeof (*yt));
	dydx = vect_new(n,sizeof(*dydx));

	hh = h*0.5;
	h6 = h/6.0;
	xh = x + hh;

	derivs(x,y,dydx,n,data);			/*Premiere etape k1/h = f(x,y)*/
	for (i=0; i<n; i++)			
	 yt[i] = y[i] + hh*dydx[i];  /*2nd param de etape 2 : Y2 = yn + 0.5*h*(k1/h)*/

	derivs(xh,yt,dyt,n,data); /*seconde etape k2/h = f(x + 0.5*h, Y2)*/
	for (i=0; i<n; i++)      
		yt[i] = y[i] + hh*dyt[i];/*2nd param de etape 3 : Y3 = yn + 0.5*h*(k2/h)*/

	derivs(xh,yt,dym,n,data); /*troisieme etape k3/h = f(x + 0.5*h, Y3)*/
	for (i=0; i<n; i++)
	{
		yt[i] = y[i] + h*dym[i];/*Y4 = yn + h*(k3/h)*/
		dym[i] += dyt[i];/*somme etape 2 et 3 et met dans dym*/
	}

	derivs(x+h,yt,dyt,n,data); /*quatrieme etape : k4/h = f(x + h, Y4)*/


	for (i=0; i<n; i++)/* Accumule les increments avec leur poid respectif*/
 		yout[i] = y[i] + h6*(dydx[i] + dyt[i] + 2.0*dym[i]);/*yn+1 = yn + 1/6*h*(k1+k4+ 2*(k2+k3))*/

 	vect_free(yt);
  vect_free(dyt);
  vect_free(dym);
  vect_free(dydx);
}


/* ---------------------------------------------------------------------
   rk4_pv()
   ---------------------------------------------------------------------
   Role : Algorithme de Runge-Kutta d'ordre 4 a pas adaptatif 
   cf. Numerical recipes pour l'evaluation de l'erreur
   ---------------------------------------------------------------------
   E : Ytin = donnees au temps tin
   E : tin = temps de départ du pas
   E : h = structure de pas, pas fait et pas suivant cf STEP.h
   E : n = nombre d'equations
   E : precis = precision demandee
   E : derivs = derivee des fonctions
   E : data = parametres du systeme
   S : - 
   ---------------------------------------------------------------------
   Notes : L'utilisateur fournit les donnees Ytin[0..n-1] au temps 'tin'
   des 'n' equations, la fonction avance d'un pas 'h.hnext' selon la 
   precision 'precis' demandee.
   ---------------------------------------------------------------------*/
void rk4_pv(double *Ytin, 
						double tin,
						STEP *h,
						int n, 
						double precis,
						void(*derivs)(double,const double *,double *,size_t,const void *),
						const void *data)
{
	double expo2 = 0.2;   /*valeurs de l'exposant dans calcul d'erreur*/
	double expo25 = 0.25;	

	double *P,*Y1,*Y2,*DY,*erry; /*variables temporaires, stockage*/

	double delta, delta0; /*erreur, erreur max*/
	int i,s=0,cpt = 0;  /*evite boucle infinie*/

 double *Y = NULL;		
 double t,pas;				
  
 /*allocation des tableaux temporaires*/
 P = vect_new(n,sizeof(*P));
 Y = vect_new(n,sizeof(*Y));
 Y1 = vect_new(n,sizeof(*Y1));		/*tableau du grand pas 2*'pas'*/
 Y2 = vect_new(n,sizeof(*Y2));		/*tableau des 2 petits pas 'pas'*/		
 DY = vect_new(n,sizeof(*DY));		/*contient la dérivée de Y*/
 erry = vect_new(n,sizeof(*erry)); /*Y2 -Y1*/
 

 for(i=0; i<n; i++) /*recopie des valeurs initiales*/
 		Y[i] = Ytin[i];
 
	pas = step_GetNext(h);
	t = tin;          		/*temps = temps initial*/


 /*tant que le step n'est pas dans la precision requise on fait : 
 		un grand pas de 2*'pas' et deux patits pas de 'pas' (h)*/
 for(;;)
 {
 		/*grand pas de longueur 'pas'*/
 		rk4(Y,n,t,pas,Y1,derivs,data);

 		/*2 petits pas de longueur 'pas/2'*/
 		rk4(Y,n,t,pas*0.5,P,derivs,data);
 		rk4(P,n,t,pas*0.5,Y2,derivs,data);

 		/*on estime l'erreur qu'on a fait entre faire 
 		  1 grand pas et faire 2 petits  ===> on met ça dans erry*/
 		for(i=0;i<n;i++)
 		{
 			erry[i] = fabs(Y2[i] - Y1[i])/15;
 		}
 		
 	 
 	 /*on cherche maintenant a savoir si le calcul courant est ok.
 	 	s'il est ok comment doit-on augmenter le pas ?
 	 	si on doit le refaire : de combien doit-on diminuer le pas ?

 	 	delta0 est l'erreur maximale autorisee elle s'obtient a partir
 	 	d'une formule delta0 = precision*|Y2max| + pas*|DYmax|*/

 	 	derivs(t,Y2,DY,n,data); /*on calcule DY*/
 	 	

 	 	/*on cherche maintenant l'erreur maximale sur toutes les equations
 	  on adaptera le pas en fonction de la plus grosse erreur*/
 	  max_d(erry,&delta,&s,n);
  	delta0 = precis * (fabs(Y2[s]) + pas * fabs(DY[s]));
 	  
 	  /*on calcule le nouveau pas*/
 	  if(delta)
 	  {
 	  	if(delta < delta0)
 	   	  step_put(h,step_GetPrev(h),0.95 * pas * pow(delta0/delta,expo2));
 	   	else
 	   		step_put(h,step_GetPrev(h),0.95 * pas * pow(delta0/delta,expo25));
 	  }
 	 	else
 	 		step_put(h,step_GetPrev(h),10 * pas); /*si pas d'erreur (err_max=0) on augmente de 10*/
 	  

 	  /* if(h->hnext > pas_m)si le nouveau pas est trop grand on le met au max
 	  	h->hnext = pas_m;*/

 	  
 	    /*si delta > delta0 (i.e. si l'une des equations a une erreur plus
 	  	grande que l'erreur max autorisée pour la precision voulue) alors
 	  	on recommence avec le pas plus petit calculé*/
 	  	if(delta > delta0)
   	  {	
   	  	pas = step_GetNext(h);
   	  }

 	  	/*si delta < delta0 (i.e. toutes les fonctions ont une erreur inf
 	  	a l'erreur max pour la precision voulue) alors on accepte le point
 	  	et on ajuste le pas*/
 	  	else	/*ok on sort*/
 	  	{  			
 	  		for(i=0;i<n;i++) /*on passe au point suivant en tenant compte de l'erreur*/
 	  			Y[i] = Y2[i] + erry[i];
 	  		
 	  		step_put(h,pas,step_GetNext(h));/*copie du pas effectue*/ 
 	  		break; /*step reussi : fin*/
 	  	}
 	  	cpt ++; /*un essai de plus...*/
 }
 if(cpt >= MAXSTEP)/*au cas où...*/
 {
 	printf("trop d'iteration dans rk4_pv\n");
 	return;
 }

  /*on recopie finalement dans le vecteur
  utilisateur*/
  for(i=0;i<n;i++)
  	Ytin[i] = Y[i];


  /*liberation memoire*/
  vect_free (P) ;
  vect_free(Y);	
  vect_free (Y1) ;
  vect_free (Y2) ;
  vect_free (DY) ;
  vect_free (erry) ;
}



/* ---------------------------------------------------------------------
   rk4naul()
   ---------------------------------------------------------------------
   Role : Algorithme de runge kutta d'ordre 4 pour la resolution 
   d'equation differentielles (fonction_magistere /home/enseignement/naulin)
   un peu modifiee
   ---------------------------------------------------------------------
   E : Pointeur sur le systeme a resoudre
   E : fonction
   E : variable de q
   S : dq/dt
   ---------------------------------------------------------------------
   Notes : L'equation differentielle est de la forme dq/dt = f(q,t)

   ALGORITHME RUNGE-KUTTA ordre 4 : 
   p1 = f(t,q(t))
   p2 = f(t+dt/2, q(t) + dt/2*p1)
   p3 = f(t+dt/2, q(t) + dt/2*p2)
   p4 = f(t+dt, q(t) + dt*p3)

   q(t+dt) = q(t) + dt/6 * (p1 + 2*p2 + 2*p3 + p4)
   --------------------------------------------------------------------- */

unsigned int
rk4naul(void(*sd)(double*,double,double*,int)
							,double q[]
							,double t
							,double dt
							,int n)
{
	int i,k,p;
	double *y[PM+1],*z[PM]; /*y[0] = q(t)
														y[1] = q(t) + dt/2*p1
														y[2] = q(t) + dt/2*p2 etc...*/
														
	static const double a[PM][PM] = {{1./2,0,0,0} 
																	,{0,1./2,0,0}
																	,{0,0,1,0}
																	,{1./6,1./3,1./3,1./6}};

  static const double b[PM] ={0,1./2,1./2,1};

  for(i=0; i<PM+1; i++)
  {
  	y[i] = vect_new(n,sizeof(*y[i])); /*allocation, chaque ligne : vecteur*/
  	if(!y[i])													/*si echec alloc*/
  	{
  		for(k=0;k<i;k++)								/*pour tous les vecteurs alloues*/
  			if(y[k])											/*si bien alloue*/
  				vect_free(y[k]);						/*on libere la memoire*/
  				
  	  return 0;											  /*on quitte : 0 = erreur*/
    }
  }
  for(i=0; i<PM; i++)
  {
  	z[i] = vect_new(n,sizeof(*z[i])); /*allocation, chaque ligne : vecteur*/
  	if(!z[i])													/*si echec alloc*/
  	{
  		for(k=0;k<i;k++)								/*pour tous les vecteurs alloues*/
  			if(z[k])											/*si bien alloue*/
  				vect_free(z[k]);						/*on libere la memoire*/
  				
  	  return 0;											  /*on quitte : 0 = erreur*/
    }
  }
  for(i=0; i<n; i++) /*initialisation pour p1*/
  	y[0][i] = q[i];

  /*calcul*/
  for(p=1; p<=PM; p++)
  {
  	/*calcul des p_i*/
  	sd(y[p-1] 						/*q[i]*/
  		,t + b[p-1]*dt 			/*t + (dt/2||dt||0)*/
  		,z[p-1] 						/*p_i*/
  		,n); 								/*taille systeme*/

  		for(i=0;i<n;i++)
  			y[p][i] = q[i]; /*recopie des composantes du i-eme vecteur*/
  	  
  	  for(k=0; k<p; k++) /*on fait le y avec le p_i precedent*/
  	  	for(i=0; i<n; i++)
  	  		y[p][i] += dt * a[p-1][k]*z[k][i]; /*ex : q(t) + dt/2*p2*/
  }
  
  for(i=0;i<n;i++)
  	q[i] = y[PM][i];
  
  /*liberation de la memoire*/
  for(i=0;i<PM+1;i++)
  		vect_free(y[i]);
  
  for(i=0;i<PM;i++)
  		vect_free(z[i]);
  return 1;
}



