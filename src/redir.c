/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:55:48 by amoutill          #+#    #+#             */
/*   Updated: 2024/05/03 13:26:02 by blebas           ###   ########.fr       */
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

int	in_here_doc_open(t_exec exec_data, int fd_tmr[2])
{
	int		pipe_fd[2];
	int		stat_loc;
	pid_t	pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
		here_doc_forked(fd_tmr, exec_data, pipe_fd);
	signal(SIGINT, sig_handler_inheredoc);
	close(pipe_fd[1]);
	waitpid(pid, &stat_loc, 0);
	signal(SIGINT, sig_handler_incmd);
	if (WIFSIGNALED(stat_loc))
	{
		close(pipe_fd[0]);
		return (-(128 + WTERMSIG(stat_loc)));
	}
	dup_and_close(pipe_fd[0], &exec_data.current_cmd->in_fd);
	return (0);
}

int	redir_open(t_exec exec_data, int fd_tmr[2])
{
	int	tmr;

	while (exec_data.current_tk && exec_data.current_tk->type != pope)
	{
		if (exec_data.current_tk->type == in_redir && in_redir_open(exec_data))
			return (1);
		else if (exec_data.current_tk->type == out_redir
			&& out_redir_open(exec_data))
			return (1);
		else if (exec_data.current_tk->type == out_append
			&& out_append_open(exec_data))
			return (1);
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
