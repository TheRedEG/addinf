/*
** parser.c for eval_expr in /home/denuit_m
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Wed Oct 21 14:16:34 2015 denuit mathieu
** Last update Wed Oct 21 15:42:44 2015 denuit mathieu
*/

#include "my.h"
#include "parser.h"

int	parse_expr(t_tokens *root)
{
  return (p_expression(&root));
}

int	p_expression(t_tokens **root)
{
  int	nb;
  int	val;
  int	negate;
  int	type;

  negate = 0;
  if ((*root)->type == TOK_ADD || (*root)->type == TOK_SUB)
  {
    negate = (*root)->type == TOK_SUB;
    *root = (*root)->next;
  }
  nb = negate ? -p_term(root) : p_term(root);
  while ((*root)->type == TOK_ADD || (*root)->type == TOK_SUB)
  {
    type = (*root)->type;
    *root = (*root)->next;
    val = p_term(root);
    nb = (type == TOK_SUB) ? (nb - val) : (nb + val);
  }
  return (nb);
}

int	p_term(t_tokens **root)
{
  int	nb;
  int	val;
  int	type;

  nb = p_factor(root);
  while ((*root)->type == TOK_MUL || (*root)->type == TOK_DIV ||
	 (*root)->type == TOK_MOD)
  {
    type = (*root)->type;
    *root = (*root)->next;
    val = p_factor(root);
    nb = (type == TOK_MUL) ? (nb * val) : ((type == TOK_DIV) ?
					   (nb / val) : (nb % val));
  }
  return (nb);
}

int	p_factor(t_tokens **root)
{
  int	nb;

  if ((*root)->type == TOK_NUMBER)
  {
    nb = (*root)->value;
    *root = (*root)->next;
    return (nb);
  }
  else if ((*root)->type == TOK_L_PAREN)
  {
    *root = (*root)->next;
    nb = p_expression(root);
    if ((*root)->type == TOK_R_PAREN)
    {
      *root = (*root)->next;
    }
    else
      my_putstr("Expected ')'\n");
    return (nb);
  }
  else
    return (0);
}
