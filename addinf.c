/*
** addinf.c for AddInf in /home/denuit_m
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Tue Oct 20 15:56:41 2015 denuit mathieu
** Last update Tue Oct 20 16:02:17 2015 denuit mathieu
*/

#include "my.h"
#include "addinf.h"

int	decimal_at(char *s, int index, int len)
{
  if (index < 0 || index >= len)
    return (0);
  else
    return (s[index] - '0');
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
  return (op.result + index);
}
