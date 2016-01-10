# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/12 15:11:53 by ael-kadh          #+#    #+#              #
#    Updated: 2016/01/10 20:27:47 by ael-kadh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC = gcc
NAME = libft_malloc_$(HOSTTYPE).so

SRC = malloc.c free.c realloc.c malloc_tools.c tools.c show_alloc_mem.c

OBJ = $(SRC:.c=.o)
	HDR = ./

CFLAGS =

all: $(NAME)
	rm -f libft_malloc.so
	ln -s libft_malloc_$(HOSTTYPE).so libft_malloc.so


$(NAME): $(OBJ)
	gcc -shared -fPIC -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) -I$(HDR) $< -o $@

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)
	rm -f libft_malloc_$(HOSTTYPE).so
	rm -f libft_malloc.so

re: fclean all
