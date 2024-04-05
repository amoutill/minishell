# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoutill <amoutill@student.42lehavre.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 15:15:21 by amoutill          #+#    #+#              #
#    Updated: 2024/04/05 16:22:47 by amoutill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= cc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
FT		= Libft
LIBFT	= $(FT)/libft.a

SOURCE	= src/main.c src/exec.c src/token.c src/utils.c src/env.c src/builtins/echo.c
OBJ		= $(SOURCE:.c=.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) -lreadline $(OBJ) $(LIBFT)

$(LIBFT):	$(FT)
	$(MAKE) -C $(FT)

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clear clean fclean re
