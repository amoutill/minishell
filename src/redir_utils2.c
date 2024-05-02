/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:51:43 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 21:04:12 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_forked(int *fd_tmr, t_exec exec_data, int *pipe_fd)
{
	char	*eof;
	char	*buff;

	signal(SIGINT, SIG_DFL);
	if (fd_tmr[0] != -1)
		close(fd_tmr[0]);
	if (fd_tmr[1] != -1)
		close(fd_tmr[1]);
	eof = ft_strdup(exec_data.current_tk->str);
	if (exec_data.current_cmd->in_fd != -1)
		close(exec_data.current_cmd->in_fd);
	if (exec_data.current_cmd->out_fd != -1)
		close(exec_data.current_cmd->out_fd);
	free_env(exec_data.env);
	free_cmd(exec_data.cmd);
	free_tklst(exec_data.tklst);
	rl_clear_history();
	close(pipe_fd[0]);
	buff = readline_here_doc(eof);
	free(eof);
	ft_putstr_fd(buff, pipe_fd[1]);
	free(buff);
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}
