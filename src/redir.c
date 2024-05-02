/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:55:48 by amoutill          #+#    #+#             */
/*   Updated: 2024/05/02 15:59:23 by blebas           ###   ########.fr       */
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

int	in_here_doc_open(t_exec exec_data)
{
	int		pipe_fd[2];
	char	*buff;

	buff = readline_here_doc(exec_data.current_tk->str);
	pipe(pipe_fd);
	ft_putstr_fd(buff, pipe_fd[1]);
	free(buff);
	close(pipe_fd[1]);
	dup_and_close(pipe_fd[0], &exec_data.current_cmd->in_fd);
	return (0);
}

int	redir_open(t_exec exec_data)
{
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
			if (in_here_doc_open(exec_data))
				return (1);
		}
		exec_data.current_tk = exec_data.current_tk->next;
	}
	return (0);
}
