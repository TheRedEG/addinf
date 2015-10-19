#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	main(int argc ,char **argv)
{
  printf("%d",argc);
  if (argc != 3)
    {
      printf("\n");
      printf("Please enter 2 parameters");
    }
  
  printf("\n");  
  addinf(argv[1], argv[2]);
}
