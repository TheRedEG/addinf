/*
** my_strcmp.c for Piscine_C_J06 in 
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Mon Oct  5 10:09:26 2015 denuit mathieu
** Last update Tue Oct  6 23:10:29 2015 denuit mathieu
*/

int	my_strncmp(char *s1, char *s2, int n)
{
  int	i;

  if (!s1 || !s2)
    return (0);
  i = 0;
  while (s1[i] == s2[i])
  {
    if (i >= n || s1[i] == 0)
      return (0);
    i += 1;
  }
  if (i == n)
    return (0);
  else
    return (s1[i] - s2[i]);
}
