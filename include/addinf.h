/*
** addinf.h for AddInf in /home/denuit_m/rendu/addinf/include
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Tue Oct 20 10:37:23 2015 denuit mathieu
** Last update Tue Oct 20 15:55:00 2015 denuit mathieu
*/

#ifndef ADDINF_H_
#define ADDINF_H_

#include <stdlib.h>

typedef struct	s_add_data
{
  int	len1;
  int	len2;
  int	isneg1;
  int	isneg2;
}		t_add_data;

typedef struct	s_add_op
{
  char	*s1;
  int	s1len;
  char	*s2;
  int	s2len;
  int	negate;
  int	nblen;
  int	add;
  char	*result;
}		t_add_op;

void	fill_add_data(char **s1, char **s2, t_add_data *d);
int	nb_greater(char *s1, char *s2);
void	make_add_op(char *s1, char *s2, t_add_data *d, t_add_op *op);
int	swap(char **s1, char **s2);
int	decimal_at(char *s, int index, int len);
char	do_addinf_carry(t_add_op *op, int *s1c, int *s2c, int *carry);
char	do_subinf_carry(t_add_op *op, int *s1c, int *s2c, int *carry);
int	do_addinf(t_add_op *op, int res_c, int add);
char	*addinf(char *s1, char *s2);

#endif
