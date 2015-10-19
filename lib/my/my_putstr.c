/*
** my_putstr.c for Piscine_C_J04 in /home/denuit_m/rendu/pc4
** 
** Made by mathieu denuit
** Login   <denuit_m@epitech.net>
** 
** Started on  Thu Oct  1 09:42:15 2015 mathieu denuit
** Last update Fri Oct  2 09:06:44 2015 mathieu denuit
*/

int	my_putstr(char *str)
{
  int	i;

  if (str == 0)
    return (0);
  i = 0;
  while (str[i] != '\0')
    {
      my_putchar(str[i]);
      i = i + 1;
    }
  return (0);
}
