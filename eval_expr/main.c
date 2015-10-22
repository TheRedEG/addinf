/*
** main.c for evalexpr in /home/denuit_m/rendu/Piscine_C_evalexpr
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Wed Oct 21 11:43:47 2015 denuit mathieu
** Last update Wed Oct 21 16:19:47 2015 denuit mathieu
*/

#include "my.h"
#include "tokenizer.h"
#include "parser.h"

int		eval_expr(char *str)
{
  t_tokens	*tokens;
  int		val;

  tokens = make_tokens(str);
  if (tokens == 0)
    return (0);
  val = parse_expr(tokens);
  free_tokens(tokens);
  return (val);
}

int	main(int ac, char **av)
{
  if (ac > 1)
  {
    my_put_nbr(eval_expr(av[1]));
    my_putchar('\n');
  }
  return (0);
}
