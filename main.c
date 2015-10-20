/*
** main.c for AddInf in /home/denuit_m/rendu/addinf
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Tue Oct 20 10:28:52 2015 denuit mathieu
** Last update Tue Oct 20 15:47:01 2015 denuit mathieu
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
  if (my_strlen(s1) > my_strlen(s2))
    return (1);
  else if (my_strlen(s2) > my_strlen(s1))
    return (0);
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

int	decimal_at(char *s, int index, int len)
{
  if (index < 0 || index >= len)
    return (0);
  else
    return s[index] - '0';
}

char	do_addinf_carry(t_add_op *op, int *s1c, int *s2c, int *carry)
{
  char	res;
  res = decimal_at(op->s1, *s1c, op->s1len) + *carry;
  res += decimal_at(op->s2, *s2c, op->s2len);
  *carry = res >= 10 ? 1 : 0;
  if (*carry)
    res -= 10;
  res += '0';
  *s1c -= 1;
  *s2c -= 1;
  return (res);
}

char	do_subinf_carry(t_add_op *op, int *s1c, int *s2c, int *carry)
{
  char	res;
  res = decimal_at(op->s1, *s1c, op->s1len) - *carry;
  res -= decimal_at(op->s2, *s2c, op->s2len);
  *carry = res < 0 ? 1 : 0;
  if (*carry)
    res += 10;
  res += '0';
  *s1c -= 1;
  *s2c -= 1;
  return (res);
}

int	do_addinf(t_add_op *op, int res_c, int add)
{
  int	s1_c;
  int	s2_c;
  int	carry;

  s1_c = op->s1len - 1;
  s2_c = op->s2len - 1;
  carry = 0;
  while (s1_c >= 0)
  {
    op->result[res_c] = add ? do_addinf_carry(op, &s1_c, &s2_c, &carry) :
      do_subinf_carry(op, &s1_c, &s2_c, &carry);
    res_c -= 1;
  }
  if (carry)
  {
    op->result[res_c] = '1';
    return (res_c);
  }
  return (res_c + 1);
}

char		*addinf(char *s1, char *s2)
{
  t_add_data	data;
  t_add_op	op;
  int		index;

  fill_add_data(&s1, &s2, &data);
  make_add_op(s1, s2, &data, &op);
  op.result = malloc(sizeof(char) * (op.nblen + 1));
  op.result[op.nblen] = 0;
  if (op.add)
    index = do_addinf(&op, op.nblen - 1, 1);
  else
    index = do_addinf(&op, op.nblen - 1, 0);
  while (index < op.nblen - 1 && op.result[index] == '0')
    index += 1;
  if (op.negate)
  {
    index -= 1;
    op.result[index] = '-';
  }
  return op.result + index;
}

int	main(int argc, char **argv)
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
    my_putchar('\n');
  }
  return (0);
}
