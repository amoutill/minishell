# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 15:15:21 by amoutill          #+#    #+#              #
#    Updated: 2024/04/15 15:17:58 by blebas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= cc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
FT		= libft
LIBFT	= $(FT)/libft.a

SOURCE	= src/main.c src/exec_builtins.c src/token.c src/utils.c src/env.c src/builtins/cd.c src/builtins/echo.c src/builtins/env_cmd.c src/token_squote.c src/parse_env.c
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
	$(MAKE) -C $(FT) fclean

re:			fclean all

.PHONY:		all clean fclean re
