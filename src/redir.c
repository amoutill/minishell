/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:55:48 by amoutill          #+#    #+#             */
/*   Updated: 2024/05/02 19:28:26 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_redir_open(t_exec exec_data)
{
	int	fd;

	fd = open(exec_data.current_tk->str, O_RDONLY);
	if (fd == -1)
	{
		open_err(exec_data.current_tk->str);
		if (exec_data.current_cmd->in_fd != -1)
			close(exec_data.current_cmd->in_fd);
		if (exec_data.current_cmd->out_fd != -1)
			close(exec_data.current_cmd->out_fd);
		return (1);
	}
	else
	{
		dup_and_close(fd, &exec_data.current_cmd->in_fd);
		return (0);
	}
}

int	out_redir_open(t_exec exec_data)
{
	int	fd;

	fd = open(exec_data.current_tk->str, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		open_err(exec_data.current_tk->str);
		if (exec_data.current_cmd->in_fd != -1)
			close(exec_data.current_cmd->in_fd);
		if (exec_data.current_cmd->out_fd != -1)
			close(exec_data.current_cmd->out_fd);
		return (1);
	}
	else
	{
		dup_and_close(fd, &exec_data.current_cmd->out_fd);
		return (0);
	}
}

int	out_append_open(t_exec exec_data)
{
	int	fd;

	fd = open(exec_data.current_tk->str, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		open_err(exec_data.current_tk->str);
		if (exec_data.current_cmd->in_fd != -1)
			close(exec_data.current_cmd->in_fd);
		if (exec_data.current_cmd->out_fd != -1)
			close(exec_data.current_cmd->out_fd);
		return (1);
	}
	else
	{
		dup_and_close(fd, &exec_data.current_cmd->out_fd);
		return (0);
	}
}

int	in_here_doc_open(t_exec exec_data, int fd_tmr[])
{
	int		pipe_fd[2];
	int		stat_loc;
	char	*buff;
	char	*eof;
	pid_t	pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
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
	close(pipe_fd[1]);
	waitpid(pid, &stat_loc, 0);
	if (WIFSIGNALED(stat_loc))
	{
		close(pipe_fd[0]);
		return (128 + WTERMSIG(stat_loc));
	}
	dup_and_close(pipe_fd[0], &exec_data.current_cmd->in_fd);
	return (0);
}

int	redir_open(t_exec exec_data, int fd_tmr[2])
{
	int	tmr;

	while (exec_data.current_tk && exec_data.current_tk->type != pope)
	{
		if (exec_data.current_tk->type == in_redir)
		{
			if (in_redir_open(exec_data))
				return (1);
		}
		else if (exec_data.current_tk->type == out_redir)
		{
			if (out_redir_open(exec_data))
				return (1);
		}
		else if (exec_data.current_tk->type == out_append)
		{
			if (out_append_open(exec_data))
				return (1);
		}
		else if (exec_data.current_tk->type == in_here_doc)
		{
			tmr = in_here_doc_open(exec_data, fd_tmr);
			if (tmr)
				return (tmr);
		}
		exec_data.current_tk = exec_data.current_tk->next;
	}
	return (0);
}
