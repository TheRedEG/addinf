/*
** main.c for AddInf in /home/denuit_m/rendu/addinf
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Tue Oct 20 10:28:52 2015 denuit mathieu
** Last update Tue Oct 20 22:06:14 2015 denuit mathieu
*/

#include "my.h"
#include "addinf.h"

void	fill_add_data(char **s1, char **s2, t_add_data *d)
{
  if (**s1 == '-')
  {
    d->isneg1 = 1;
    *s1 += 1;
  }
  else
    d->isneg1 = 0;
  if (**s2 == '-')
  {
    d->isneg2 = 1;
    *s2 += 1;
  }
  else
    d->isneg2 = 0;
  d->len1 = my_strlen(*s1);
  d->len2 = my_strlen(*s2);
}

int	nb_greater(char *s1, char *s2)
{
  int	len1;
  int	len2;

  while (*s1 == '0')
    s1 += 1;
  if (*s1 == 0)
    s1 -= 1;
  while (*s2 == '0')
    s2 += 1;
  if (*s2 == 0)
    s2 -= 1;
  len1 = my_strlen(s1);
  len2 = my_strlen(s2);
  if (len1 > len2)
    return (1);
  else if (len2 > len1)
    return (0);
  return (my_strcmp(s1, s2) > 0);
}

void	make_add_op(char *s1, char *s2, t_add_data *d, t_add_op *op)
{
  op->s1 = s1;
  op->s2 = s2;
  op->nblen = (d->len1 > d->len2) ? (d->len1 + 1) : (d->len2 + 1);
  if ((d->isneg1 && d->isneg2) || (!d->isneg1 && !d->isneg2))
  {
    if (nb_greater(op->s2, op->s1))
      swap(&op->s1, &op->s2);
    op->negate = (d->isneg1 && d->isneg2);
    op->add = 1;
  }
  else if (!d->isneg1 || swap(&op->s1, &op->s2))
  {
    op->add = 0;
    if (nb_greater(op->s2, op->s1))
    {
      swap(&op->s1, &op->s2);
      op->negate = 1;
    }
    else
      op->negate = 0;
  }
  op->nblen += op->negate ? 1 : 0;
  op->s1len = my_strlen(op->s1);
  op->s2len = my_strlen(op->s2);
}

int	swap(char **s1, char **s2)
{
  char	*tmp;

  tmp = *s1;
  *s1 = *s2;
  *s2 = tmp;
  return (1);
}

int	main(int argc, char **argv)
{
  if (argc != 3 || !my_isnumber(argv[1]) || !my_isnumber(argv[2]))
  {
    my_putstr("Usage: ");
    my_putstr(argv[0]);
    my_putstr(" [nb1] [nb2]\n");
  }
  else
  {
    my_putstr(addinf(argv[1], argv[2]));
    my_putchar('\n');
  }
  return (0);
}
