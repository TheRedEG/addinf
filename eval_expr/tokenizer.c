/*
** tokenizer.c for eval_expr in /home/denuit_m
** 
** Made by denuit mathieu
** Login   <denuit_m@epitech.net>
** 
** Started on  Wed Oct 21 12:10:23 2015 denuit mathieu
** Last update Wed Oct 21 14:26:17 2015 denuit mathieu
*/

#include "my.h"
#include "tokenizer.h"

t_tokens	*new_token_after(t_tokens *last)
{
  t_tokens	*node;

  node = malloc(sizeof(t_tokens));
  if (!node)
    return (0);
  node->type = -1;
  node->value = 0;
  node->next = 0;
  if (last)
    last->next = node;
  return (node);
}

void		free_tokens(t_tokens *root)
{
  t_tokens	*next_tok;

  while (root)
  {
    next_tok = root->next;
    free(root);
    root = next_tok;
  }
}

void	fill_single_token(char **str, t_tokens *last_node, int type)
{
  int	number;

  if (type == TOK_NUMBER)
  {
    number = my_getnbr_base(*str, "0123456789");
    last_node->type = TOK_NUMBER;
    last_node->value = number;
    while (**str >= '0' && **str <= '9')
      *str += 1;
  }
  else
  {
    last_node->type = type;
    last_node->value = 0;
    *str += 1;
  }
}

int	fill_token(char **str, t_tokens *node)
{
  if (!str || !*str || !**str)
    return (0);
  if (**str >= '0' && **str <= '9')
    fill_single_token(str, node, TOK_NUMBER);
  else if (**str == '(')
    fill_single_token(str, node, TOK_L_PAREN);
  else if (**str == ')')
    fill_single_token(str, node, TOK_R_PAREN);
  else if (**str == '+')
    fill_single_token(str, node, TOK_ADD);
  else if (**str == '-')
    fill_single_token(str, node, TOK_SUB);
  else if (**str == '*')
    fill_single_token(str, node, TOK_MUL);
  else if (**str == '/')
    fill_single_token(str, node, TOK_DIV);
  else if (**str == '%')
    fill_single_token(str, node, TOK_MOD);
  else
    return (-1);
  return (1);
}

t_tokens	*make_tokens(char *str)
{
  t_tokens	*root;
  t_tokens	*last_node;
  int		result;

  root = new_token_after(0);
  last_node = root;
  while (*str != 0)
  {
    while (*str == ' ' || *str == '\t' || *str == '\n')
      str += 1;
    result = fill_token(&str, last_node);
    if (result == 0)
      break;
    else if (result == -1)
    {
      my_putstr("invalid character '");
      my_putchar(*str);
      my_putstr("'\n");
      return (0);
    }
    last_node = new_token_after(last_node);
  }
  return (root);
}
