# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 15:15:21 by amoutill          #+#    #+#              #
#    Updated: 2024/04/30 20:08:18 by blebas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= cc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -g
FT		= libft
LIBFT	= $(FT)/libft.a

SOURCE	= src/main.c src/exec_builtins.c src/token.c src/init_cmd.c src/ft_which.c src/exec.c src/tokenizer.c src/utils.c src/env.c src/builtins/cd.c src/builtins/echo.c src/builtins/env_cmd.c  src/parse_utils.c src/parse_quote.c src/parse_env.c src/parse_redir.c src/token2.c src/cmd_utils.c src/redir.c src/redir_utils.c src/signals.c src/exec_utils.c src/exec_utils2.c
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

f:			re
	rm -f $(OBJ)

.PHONY:		all clean fclean re
