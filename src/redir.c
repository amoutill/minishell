/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:55:48 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/24 16:30:45 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_redir_open(t_exec exec_data, t_token *current_tk, int *in_fd,
			int *out_fd)
{
	int	fd;

	fd = open(current_tk->str, O_RDONLY);
	if (fd == -1)
	{
		open_err(current_tk->str);
		free_and_close_child(exec_data, *in_fd, *out_fd);
		exit(1);
	}
	else
		dup_and_close(fd, in_fd);
}

void	out_redir_open(t_exec exec_data, t_token *current_tk, int *in_fd,
			int *out_fd)
{
	int	fd;

	fd = open(current_tk->str, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		open_err(current_tk->str);
		free_and_close_child(exec_data, *in_fd, *out_fd);
		exit(1);
	}
	else
		dup_and_close(fd, out_fd);
}

void	out_append_open(t_exec exec_data, t_token *current_tk, int *in_fd,
			int *out_fd)
{
	int	fd;

	fd = open(current_tk->str, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		open_err(current_tk->str);
		free_and_close_child(exec_data, *in_fd, *out_fd);
		exit(1);
	}
	else
		dup_and_close(fd, out_fd);
}

void	in_here_doc_open(t_token *current_tk, int *in_fd)
{
	int		pipe_fd[2];
	char	*buff;

	buff = readline_here_doc(current_tk->str);
	pipe(pipe_fd);
	ft_putstr_fd(buff, pipe_fd[1]);
	free(buff);
	close(pipe_fd[1]);
	dup_and_close(pipe_fd[0], in_fd);
}

void	redir_open(t_exec exec_data)
{
	t_token	*current_tk;
	int		in_fd;
	int		out_fd;

	current_tk = exec_data.tklst;
	in_fd = -1;
	out_fd = -1;
	while (current_tk)
	{
		if (current_tk->type == in_redir)
			in_redir_open(exec_data, current_tk, &in_fd, &out_fd);
		else if (current_tk->type == out_redir)
			out_redir_open(exec_data, current_tk, &in_fd, &out_fd);
		else if (current_tk->type == out_append)
			out_append_open(exec_data, current_tk, &in_fd, &out_fd);
		else if (current_tk->type == in_here_doc)
			in_here_doc_open(current_tk, &in_fd);
		current_tk = current_tk->next;
	}
	replace_fds(in_fd, out_fd);
}
