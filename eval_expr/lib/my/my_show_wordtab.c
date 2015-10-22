/*
** my_show_wordtab.c for Piscine_C_J08 in /home/denuit_m
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Wed Oct  7 16:01:35 2015 denuit mathieu
** Last update Thu Oct  8 13:36:31 2015 denuit mathieu
*/

int	my_show_wordtab(char **tab)
{
  int	i;

  if (!tab)
    return (0);
  i = 0;
  while (tab[i] != 0)
  {
    my_putstr(tab[i]);
    my_putchar('\n');
    i += 1;
  }
  return (0);
}
