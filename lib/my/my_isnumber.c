/*
** my_isnumber.c for LIB in /home/denuit_m/rendu/addinf/lib/my
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Tue Oct 20 16:11:08 2015 denuit mathieu
** Last update Tue Oct 20 16:18:30 2015 denuit mathieu
*/

int	my_isnumber(char *str)
{
  if (str == 0 || *str == 0)
    return (0);
  else if (*str == '-')
    str += 1;
  while (*str != 0)
  {
    if (*str < '0' || *str > '9')
      return (0);
    str += 1;
  }
  return (1);
}
