/*
** my_put_nbr.c for Piscine_C_J03 in /home/denuit_m/rendu/pc3
** 
** Made by mathieu denuit
** Login   <denuit_m@epitech.net>
** 
** Started on  Wed Sep 30 16:12:55 2015 mathieu denuit
** Last update Sun Oct 11 14:50:14 2015 denuit mathieu
*/

int	my_pow10(int i)
{
  int	val;

  val = 1;
  while (i > 0)
    {
      val = val * 10;
      i = i - 1;
    }
  return (val);
}

void	my_put_nbr_special(void)
{
  my_putchar('-');
  my_putchar('2');
  my_putchar('1');
  my_putchar('4');
  my_putchar('7');
  my_putchar('4');
  my_putchar('8');
  my_putchar('3');
  my_putchar('6');
  my_putchar('4');
  my_putchar('8');
}

int	my_put_nbr_start(int nb)
{
  if (nb == -2147483648)
    {
      my_put_nbr_special();
      return (-1);
    }
  else if (nb < 0)
    {
      my_putchar('-');
      return (-nb);
    }
  else if (nb == 0)
    {
      my_putchar('0');
      return (-1);
    }
  else
    {
      return (nb);
    }
}

int	my_put_nbr(int nb)
{
  int	i;
  int	last_digit;
  int	sum;
  int	started;

  sum = 0;
  nb = my_put_nbr_start(nb);
  if (nb <= 0)
    return (0);
  i = 9;
  started = 0;
  while (i >= 0)
    {
      last_digit = (nb - sum) / my_pow10(i);
      sum = sum + last_digit * my_pow10(i);
      i = i - 1;
      started = (last_digit > 0 && !started) ? 1 : started;
      if (started == 1)
	my_putchar(last_digit + '0');
    }
  return (0);
}
