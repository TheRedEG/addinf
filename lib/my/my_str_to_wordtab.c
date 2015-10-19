/*
** my_str_to_wordtab.c for Piscine_C_J08 in /home/denuit_m
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Wed Oct  7 16:12:37 2015 denuit mathieu
** Last update Sun Oct 11 12:31:43 2015 denuit mathieu
*/

#include <stdlib.h>

int	is_alnum(char c)
{
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    return (1);
  else if (c >= '0' && c <= '9')
    return (1);
  else
    return (0);
}

int	alnumlen(char *str)
{
  int	i;

  i = 0;
  while (is_alnum(str[i]))
    i += 1;
  return (i);
}

int	num_tokens(char *str)
{
  int	i;
  int	num;

  i = 0;
  num = 0;
  while (str[i] != 0)
  {
    if (is_alnum(str[i]))
    {
      num += 1;
      while (is_alnum(str[i]))
	i += 1;
    }
    else
    {
      i += 1;
    }
  }
  return (num);
}

char	*next_token(char **str)
{
  int	i;
  int	len;
  char	*token;

  if (str == 0 || *str == 0)
    return (0);
  i = 0;
  while (*(*str + i) != 0)
  {
    if (is_alnum(*(*str + i)))
    {
      len = alnumlen(*str + i);
      token = (char*) malloc(sizeof(char) * (len + 1));
      if (!token)
	return (0);
      my_strncpy(token, *str + i, len);
      token[len] = 0;
      *str = *str + i + len + 1;
      return (token);
    }
    i += 1;
  }
  return (0);
}

char	**my_str_to_wordtab(char *str)
{
  char	**result;
  char	*ptr;
  int	i;
  int	len;

  if (!str)
    return (0);
  len = num_tokens(str);
  result = malloc(sizeof(char*) * (len + 1));
  if (!result)
    return (0);
  i = 0;
  ptr = str;
  while (i < len)
  {
    result[i] = next_token(&ptr);
    i += 1;
  }
  result[i] = 0;
  return (result);
}
