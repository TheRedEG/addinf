#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//initialisation des 2 nombres
void init_nb()
{ 
}

//Swap pour que n1 > n2
int	swap(char *n1, char *n2)
{
  int	tmp;
  
  if (n1<n2)
    {
      tmp = *n1;
      *n1 = *n2;
      *n2 = tmp;
    }
  printf("%s",n1);
}

//initialisation des tampon (tmp) et (result)
int	init_tmp_result()
{
}

//calcul
int	process()
{
}

//return
int	addinf(char *n1, char *n2)
{
  swap(n1, n2);
}

