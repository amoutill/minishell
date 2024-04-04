# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoutill <amoutill@student.42lehavre.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 15:15:21 by amoutill          #+#    #+#              #
#    Updated: 2024/04/04 15:21:52 by amoutill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= cc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -fsanitize=address
FT		= Libft
LIBFT	= $(FT)/libft.a

SOURCE	= src/main.c src/builtins/echo.c src/exec.c src/token.c src/utils.c
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
