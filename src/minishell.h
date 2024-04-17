/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:39:39 by blebas            #+#    #+#             */
/*   Updated: 2024/04/17 16:45:03 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ***************** */
/*      INCLUDES     */
/* ***************** */

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
# include <stdbool.h>
# include "../libft/libft.h"

/* ***************** */
/*       COLORS      */
/* ***************** */

# define NC		"\e[0m"
# define YELLOW	"\e[1;33m"
# define RED	"\e[1;31m"
# define GREEN	"\e[1;32m"
# define PURPLE	"\e[1;35m"
# define CYAN	"\e[1;36m"
# define BLUE	"\e[1;34m"

/* ***************** */
/*     STRUCTURES    */
/* ***************** */

typedef enum e_tktype
{
	word,
	in_redir,
	in_here_doc,
	out_redir,
	out_append,
	pope
}		t_tktype;

typedef struct s_token	t_token;

typedef struct s_token
{
	char		*str;
	t_tktype	type;
	int			stop;
	t_token		*next;
}		t_token;

typedef struct s_env	t_env;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}				t_env;

typedef struct s_cmd
{
	char	*cmd;
	int		argc;
	char	**argv;
}				t_cmd;

/* ***************** */
/*      PARSING      */
/* ***************** */

/* token.c */
size_t	tklst_len(t_token *tklst);
void	tklst_addd(t_token **tklst, t_tktype type);
void	tk_add_char(t_token *tklst, char c);
t_token	*get_last_tk(t_token *tklst);
t_token	*magic_tokenizer(t_env *env, char *str);
t_cmd	*init_cmd(t_token *tklst);

/* token_squote.c */
bool	is_token_end(char s);
void	parse_squote(t_token **tklst, char **str);
void	parse_dquote(t_env *env, t_token **tklst, char **str);

/* env.c */
t_env	*new_env(char *key, char *value);
void	set_env(t_env *env, char *key, char *value);
t_env	*init_env(const char *envp[]);
char	*get_env(t_env *env, char *key);

/* parse_env.c */
void	parse_envar(t_env *env, t_token **tklst, char **cmdline);
//void	free_last_tk(t_token **tklst);

/* parse_redir.c */
void	parse_out_redir(t_token **tklst, char **str);
void	parse_out_append(t_token **tklst, char **str);
void	parse_in_redir(t_token **tklst, char **str);
void	parse_in_here_doc(t_token **tklst, char **str);
void	parse_pipe(t_token **tklst, char **str);

/* utils.c */
void	print_tktlst(t_token *token);
void	print_env(t_env *env);
int		ft_isspace(char c);
void	ft_skip_spaces(char **str);
void	str_add_char(char **str, char c);

/* ***************** */
/*     BUILTINS      */
/* ***************** */

/* echo.c */
int		echo_cmd(char **argv);

/* cd.c */
int		cd_cmd(char **argv);
int		pwd_cmd(void);

/* env_cmd */
int		env_cmd(char **argv, t_env *env);

/* exec_builtins.c */
int		exec_cmd(t_cmd *cmd, t_env *env);

#endif
