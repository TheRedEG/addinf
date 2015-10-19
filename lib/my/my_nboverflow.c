/*
** my_nboverflow.c for Piscine_C_J10 in /home/denuit_m
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Mon Oct 12 10:00:00 2015 denuit mathieu
** Last update Mon Oct 12 10:29:15 2015 denuit mathieu
*/

int	my_nboverflow(char *str, int len, int sign)
{
  while (*str == '0')
  {
    len -= 1;
    str += 1;
  }
  if (len < 10)
    return (0);
  else if (len > 10)
    return (1);
  else
  {
    if (sign == 1)
      return (my_strncmp(str, "2147483647", 10) > 0);
    else if (sign == -1)
      return (my_strncmp(str, "2147483648", 10) > 0);
  }
}
