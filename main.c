/*
** main.c for AddInf in /home/denuit_m/rendu/addinf
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Tue Oct 20 10:28:52 2015 denuit mathieu
** Last update Tue Oct 20 14:02:53 2015 denuit mathieu
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
  while (*s1 != 0 && *s2 != 0 && *s1 == *s2)
  {
    s1 += 1;
    s2 += 1;
  }
  if (*s2 == 0 && *s1)
    return (1);
  else if (*s1 == 0 && *s2)
    return (0);
  else
    return (*s1 > *s2);
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
  else if ((!d->isneg1 && d->isneg2) ||
	   (d->isneg1 && swap(&op->s1, &op->s2)))
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
}

int	swap(char **s1, char **s2)
{
  char	*tmp;

  tmp = *s1;
  *s1 = *s2;
  *s2 = tmp;
  return (1);
}

char		*addinf(char *s1, char *s2)
{
  t_add_data	data;
  t_add_op	op;

  fill_add_data(&s1, &s2, &data);
  make_add_op(s1, s2, &data, &op);
}

void	main(int argc, char **argv)
{
  if (argc != 3)
  {
    my_putstr("Usage: ");
    my_putstr(argv[0]);
    my_putstr(" [nb1] [nb2]\n");
  }
  else
  {
    my_putstr(addinf(argv[1], argv[2]));
  }
}
