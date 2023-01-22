/* ---------------------------------------------------------------------
   NA 2004
   Projet       : -
   Fonction     : Objet 'step' pour les ODE
   Module       : CLIB/ODE
   Fichier      : step.h
   Creation     : 20-02-2005
   Modification : 20-02-2005
   --------------------------------------------------------------------- */


#include <step.h>


/*------------------------------------------------------------------------
	DECLARATIONS PRIVEES DU MODULE : 
 -----------------------------------------------------------------------*/




/* structures ===============================================================*/
struct _step
{
	double hdid;
	double hnext;
};





/*------------------------------------------------------------------------
	FONCTIONS D'USAGE PUBLIC : 
  ------------------------------------------------------------------------*/





/* ---------------------------------------------------------------------
   step_new()
   ---------------------------------------------------------------------
   Role : Constructeur de l'objet STEP
   ---------------------------------------------------------------------
   E : hdid = le pas precedent
   E : hnext = pas suivant
   S : objet cree
   ---------------------------------------------------------------------
   Notes : 
   --------------------------------------------------------------------- */
STEP *
step_new(double hdid,double hnext)
{
  STEP *this = malloc(sizeof(*this));
  if(this)
	{
	  this->hdid = hdid;
	  this->hnext = hnext;
	}
  return this;
}








/* ---------------------------------------------------------------------
   step_put()
   ---------------------------------------------------------------------
   Role : permet de modifier les hdid et hnext
   ---------------------------------------------------------------------
   E : this  - step
   E : hdid  - step fait
   E : hnext - pas suivant
   S : 1 ok, 0 sinon
   ---------------------------------------------------------------------
   Notes : 0 = le STEP n'existe pas
   --------------------------------------------------------------------- */
unsigned int
step_put(STEP *this, double hdid,double hnext)
{
  unsigned int r = 0;
  if(this)
    {
      this->hdid = hdid;
      this->hnext = hnext;
      r = 1;
    }
  return r;
}






/* ---------------------------------------------------------------------
   step_GetNext()
   ---------------------------------------------------------------------
   Role : retourne la valeur du prochain pas de temps
   ---------------------------------------------------------------------
   E : objet STEP
   ---------------------------------------------------------------------
   Notes : 
   --------------------------------------------------------------------- */
double
step_GetNext(const STEP *this)
{
  return this->hnext;
}






/* ---------------------------------------------------------------------
   step_GetPrev()
   ---------------------------------------------------------------------
   Role : retourne la valeur du pas de temps precedent
   ---------------------------------------------------------------------
   E : objet STEP
   ---------------------------------------------------------------------
   Notes : 
   --------------------------------------------------------------------- */
double
step_GetPrev(const STEP *this)
{
  return this->hdid;
}








/* ---------------------------------------------------------------------
   step_free()
   ---------------------------------------------------------------------
   Role : Destructeur de l'objet STEP
   ---------------------------------------------------------------------
   E : this = step a detruire
   ---------------------------------------------------------------------
   Notes : 
   --------------------------------------------------------------------- */
void
step_free(STEP *this)
{
  if(this)
    free(this);
}
