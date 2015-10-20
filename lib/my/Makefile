##
## Makefile for do-op in /home/denuit_m
## 
## Made by denuit mathieu
## Login   <denuit_m@epitech.net>
## 
## Started on  Fri Oct  9 09:26:08 2015 denuit mathieu
## Last update Tue Oct 20 16:13:04 2015 denuit mathieu
##

CC	= gcc

RM	= rm -f

CFLAGS	+= -Wall -I. -pedantic

NAME	= libmy.a

SRCS	= my_getnbr_base.c \
	  my_putchar.c \
	  my_put_nbr.c \
	  my_putstr.c \
	  my_show_wordtab.c \
	  my_strcmp.c \
	  my_strlen.c \
	  my_strncmp.c \
	  my_str_to_wordtab.c \
	  my_nboverflow.c \
	  my_strdup.c \
	  my_strstr.c \
	  my_isnumber.c

OBJS	= $(SRCS:.c=.o)


all: $(NAME)

.c.o:
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	cp $(NAME) ../
	cp my.h ../../include/

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(OBJS)

re: fclean all

.PHONY: all clean fclean re
