/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:39:39 by blebas            #+#    #+#             */
/*   Updated: 2024/04/04 15:24:31 by amoutill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*LIBRARY*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"

/*COLORS*/

# define NC		"\e[0m"
# define YELLOW	"\e[1;33m"
# define RED	"\e[1;31m"
# define GREEN	"\e[1;32m"
# define PURPLE	"\e[1;35m"
# define CYAN	"\e[1;36m"
# define BLUE	"\e[1;34m"

/*STRUCTURES*/

typedef enum	e_tktype
{
	word,
	in_redir,
	in_here_doc,
	out_redir,
	out_append,
	pope
}		t_tktype;

typedef struct	s_token	t_token;

typedef struct	s_token
{
	char		*str;
	t_tktype	type;
	t_token		*next;
}		t_token;

typedef	struct	s_cmd
{
	char	*cmd;
	int		argc;
	char	**argv;
}				t_cmd;

/*FONCTIONS*/

//token.c
size_t	tklst_len(t_token *tklst);
void	tklst_addd(t_token **tklst, char *str, t_tktype type);
t_token	*magic_tokenizer(char *str);
t_cmd	*init_cmd(t_token *tklst);

//utils.c
void	print_tktlst(t_token *token);

//exec.c
int		exec_cmd(t_cmd *cmd);

//echo.c
int		echo_cmd(char **argv);

#endif
