/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:39:39 by blebas            #+#    #+#             */
/*   Updated: 2024/05/01 16:16:05 by blebas           ###   ########.fr       */
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
# include <signal.h>
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
/*      STRINGS      */
/* ***************** */

# define STX_ERR "minishell: syntax error near unexpected token `"
# define STX_ERR_END "'\n"
# define HD_ERR \
	"bash: warning: here-document delimited by end-of-file (wanted `"
# define HD_ERR_END "')\n"

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
	int			err;
	t_token		*next;
}		t_token;

typedef struct s_env	t_env;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}				t_env;

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	int		argc;
	char	**argv;
	int		in_fd;
	int		out_fd;
	int		fd_to_close;
	t_cmd	*next;
}				t_cmd;

typedef struct s_exec
{
	t_token	*tklst;
	t_token	*current_tk;
	t_cmd	*cmd;
	t_cmd	*current_cmd;
	t_env	*env;
}				t_exec;

/* ***************** */
/*      PARSING      */
/* ***************** */

/* token.c */
size_t	tklst_len(t_token *tklst);
void	tklst_addd(t_token **tklst, t_tktype type);
void	tk_add_char(t_token *tklst, char c);
t_token	*get_last_tk(t_token *tklst);
t_cmd	*init_cmd(t_token *tklst);

/* tokenizer.c */
t_token	*magic_tokenizer(t_env *env, char *cmdline);

/* parse_quote.c */
void	parse_squote(t_token **tklst, char **cmdline);
void	parse_dquote(t_env *env, t_token **tklst, char **cmdline);

/* parse_utils.c */
bool	is_token_end(char c);
bool	is_spec_char(char c);
void	print_stx_err(t_tktype type);

/* env.c */
t_env	*new_env(char *key, char *value);
void	set_env(t_env *env, char *key, char *value);
t_env	*init_env(const char *envp[]);
char	*get_env(t_env *env, char *key);
void	free_env(t_env *env);

/* parse_env.c */
void	parse_envar(t_env *env, t_token **tklst, char **cmdline);
//void	free_last_tk(t_token **tklst);

/* parse_redir.c */
void	parse_out_redir(t_token **tklst, char **cmdline);
void	parse_out_append(t_token **tklst, char **cmdline);
void	parse_in_redir(t_token **tklst, char **cmdline);
void	parse_in_here_doc(t_token **tklst, char **cmdline);
void	parse_pipe(t_token **tklst, char **cmdline);

/* utils.c */
void	print_tktlst(t_token *token);
void	print_env(t_env *env);
int		ft_isspace(char c);
void	ft_skip_spaces(char **str);
void	str_add_char(char **str, char c);

/* token2.c */
void	free_tklst(t_token *tklst);

/* init_cmd.c */
t_cmd	*init_cmd(t_token *tklst);
char	**init_envp(t_env *env);

/* cmd_utils.c */
void	free_str_tab(char **strtab);
void	free_cmd(t_cmd *cmd);
void	print_str_tab(char **strtab);
size_t	count_cmd(t_cmd *cmd);

/* exec.c */
int		exec(t_exec exec_data);

/* exec_utils.c */
void	free_and_close_child(t_exec exec_data);
void	exit_if_invalid_cmd(char *cmd_path);
int		wait_cmd(pid_t *pid, size_t nb_cmd);
void	close_fds(int in_fd, int out_fd);
void	advance_to_next_pipe_tk(t_exec *exec_data);

/* exec_utils2.c */
void	setup_pipes(t_exec *exec_data, int pipe_fd[2], size_t nb_cmd, size_t i);

/* ft_which.c */
char	*ft_which(t_env *env, char *cmd);

/* redir.c */
void	redir_open(t_exec exec_data);

/* redir_utils.c */
void	open_err(char *file);
void	replace_fds(int in_fd, int out_fd);
void	here_doc_eof_err(char *eof);
void	dup_and_close(int fd, int *fd2);
char	*readline_here_doc(char *eof);

/* signals.c */
void	sigint_handler(int sig);
void	sig_handler_incmd(int sig);

/* ***************** */
/*     BUILTINS      */
/* ***************** */

/* echo.c */
int		echo_cmd(char **argv);

/* cd.c */
int		cd_cmd(char **argv);
int		pwd_cmd(void);

/* env_cmd */
int		env_cmd(t_env *env);

/* exec_builtins.c */
int		exec_cmd(t_cmd *cmd, t_env *env);
int		is_builtin(char *cmd);

/* wrapper.c */
int		builtins_tortilla(t_exec exec_data);

#endif
