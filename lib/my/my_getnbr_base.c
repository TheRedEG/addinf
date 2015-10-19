/*
** my_getnbr_base.c for Piscine_C_J06 in 
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Mon Oct  5 10:09:26 2015 denuit mathieu
** Last update Mon Oct 12 10:22:19 2015 denuit mathieu
*/

int	nbrlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] >= '0' && str[i] <= '9')
    i += 1;
  return (i);
}

int	get_base_id(char c, char *base)
{
  int	i;

  i = 0;
  while (base[i] != '\0')
  {
    if (base[i] == c)
      return (i);
    i += 1;
  }
  return (-1);
}

char	*get_sign(char *str, char *base, int *sign)
{
  int	i;
  int	level;

  i = 0;
  level = 1;
  while (get_base_id(str[i], base) == -1)
  {
    if (str[i] != '-' && str[i] != '+')
      return (0);
    level *= (str[i] == '-' ? -1 : 1);
    i = i + 1;
  }
  *sign = level;
  return (str + i);
}

int	getnbr(char *str, char *base)
{
  int	i;
  int	acc;
  int	pow_val;
  int	sign;

  str = get_sign(str, base, &sign);
  if (str == 0)
    return (0);
  i = nbrlen(str) - 1;
  if (my_nboverflow(str, i + 1, sign))
    return (0);
  acc = 0;
  pow_val = 1;
  while (i >= 0)
  {
    acc += pow_val * get_base_id(str[i], base);
    pow_val = pow_val * my_strlen(base);
    i -= 1;
  }
  return (acc * sign);
}

int	my_getnbr_base(char *str, char *base)
{
  char	ascii[256];
  int	i;

  if (!str || !base || my_strlen(str) == 0 || my_strlen(base) == 0)
    return (0);
  i = 0;
  while (i < 256)
  {
    ascii[i] = 0;
    i += 1;
  }
  i = 0;
  while (base[i] != '\0')
  {
    if (!ascii[base[i]])
      ascii[base[i]] = 1;
    else
      return (0);
    i += 1;
  }
  return (getnbr(str, base));
}
