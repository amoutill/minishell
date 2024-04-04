NAME := minishell

CC := cc
RM := rm -f

CFLAGS		= -Wall -Wextra -Werror
FT			= Libft
LIBFT		= $(FT)/libft.a

SOURCE := main.c builtins/echo.c
OBJ 	= $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) -lreadline $(OBJ) $(LIBFT)

$(LIBFT): $(FT)
	$(MAKE) -C $(FT)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clear clean fclean re
