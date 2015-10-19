/*
** my_strdup.c for Piscine_C_J08 in /home/denuit_m/rendu/Piscine_C_J08/ex_01
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Wed Oct  7 14:40:26 2015 denuit mathieu
** Last update Mon Oct 12 11:23:50 2015 denuit mathieu
*/

#include <stdlib.h>

char	*my_strdup(char *src)
{
  char	*new_str;
  int	len;
  int	i;

  len = my_strlen(src);
  new_str = malloc(sizeof(char) * (len + 1));
  if (new_str == 0)
    return (0);
  i = 0;
  while (i < len)
  {
    new_str[i] = src[i];
    i += 1;
  }
  new_str[i] = 0;
  return (new_str);
}
