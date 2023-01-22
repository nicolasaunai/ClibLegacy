
#include "file.h"

int main(int argc, char *argv[])
{
  
  FILE *pf = fopen("rk4.res","r");
  if(pf)
  	printf("%d\n",file_nbline(pf));
  return 0;
}
