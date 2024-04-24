/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:55:48 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/24 15:14:35 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_redir_open(t_token *tklst, int *in_fd)
{
	int	fd;

	fd = open(tklst->str, O_RDONLY);
	if (fd == -1)
	{
		open_err(tklst->str);
		exit(1);
	}
	else
		dup_and_close(fd, in_fd);
}

void	out_redir_open(t_token *tklst, int *out_fd)
{
	int	fd;

	fd = open(tklst->str, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		open_err(tklst->str);
		exit(1);
	}
	else
		dup_and_close(fd, out_fd);
}

void	out_append_open(t_token *tklst, int *out_fd)
{
	int	fd;

	fd = open(tklst->str, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		open_err(tklst->str);
		exit(1);
	}
	else
		dup_and_close(fd, out_fd);
}

void	in_here_doc_open(t_token *tklst, int *in_fd)
{
	int		pipe_fd[2];
	char	*buff;

	buff = readline_here_doc(tklst->str);
	pipe(pipe_fd);
	ft_putstr_fd(buff, pipe_fd[1]);
	free(buff);
	close(pipe_fd[1]);
	dup_and_close(pipe_fd[0], in_fd);
}

void	redir_open(t_token *tklst)
{
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	while (tklst)
	{
		if (tklst->type == in_redir)
			in_redir_open(tklst, &in_fd);
		else if (tklst->type == out_redir)
			out_redir_open(tklst, &out_fd);
		else if (tklst->type == out_append)
			out_append_open(tklst, &out_fd);
		else if (tklst->type == in_here_doc)
			in_here_doc_open(tklst, &in_fd);
		tklst = tklst->next;
	}
	replace_fds(in_fd, out_fd);
}
