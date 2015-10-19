/*
** my_strstr.c for Piscine_C_J06 in 
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Mon Oct  5 10:09:26 2015 denuit mathieu
** Last update Wed Oct 14 11:32:15 2015 denuit mathieu
*/

int	m_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != 0)
    i += 1;
  return (i);
}

int	m_strncmp(char *str1, char *str2, int n)
{
  int	i;

  i = 0;
  while (str1[i] == str2[i])
  {
    if (i >= n || str1[i] == 0)
      return (0);
    i += 1;
  }
  if (i == n)
    return (0);
  else
    return (str1[i] - str2[i]);
}

char	*my_strstr(char *str, char *to_find)
{
  char	*ptr;

  if (!str || !to_find || m_strlen(str) == 0)
    return (0);
  if (m_strlen(to_find) == 0)
    return (str);
  ptr = str;
  while (m_strncmp(ptr, to_find, m_strlen(to_find)) != 0)
  {
    ptr += 1;
    if (*ptr == 0)
      return (0);
  }
  return (ptr);
}
