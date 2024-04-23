/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:55:48 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/23 20:47:39 by blebas           ###   ########.fr       */
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
	{
		if (*in_fd != -1)
			dup2(fd, *in_fd);
		else
			*in_fd = dup(fd);
		close(fd);
	}
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
	{
		if (*out_fd != -1)
			dup2(fd, *out_fd);
		else
			*out_fd = dup(fd);
		close(fd);
	}
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
	{
		if (*out_fd != -1)
			dup2(fd, *out_fd);
		else
			*out_fd = dup(fd);
		close(fd);
	}
}

void	in_here_doc_open(t_token *tklst, int *in_fd)
{
	int		pipe_fd[2];
	char	*buf;
	char	*buff;
	char	*bufff;

	buff = ft_strdup("");
	pipe(pipe_fd);
	while (1)
	{
		buf = readline("> ");
		if (!buf || !ft_strncmp(buf, tklst->str, -1))
		{
			if (!buf)
			{
				ft_putstr_fd(HD_ERR, STDERR_FILENO);
				ft_putstr_fd(tklst->str, STDERR_FILENO);
				ft_putstr_fd(HD_ERR_END, STDERR_FILENO);
			}
			break ;
		}
		bufff = ft_strjoin(buff, buf);
		free(buf);
		free(buff);
		buff = ft_strjoin(bufff, "\n");
		free(bufff);
	}
	ft_putstr_fd(buff, pipe_fd[1]);
	free(buff);
	close(pipe_fd[1]);
	if (*in_fd != -1)
		dup2(pipe_fd[0], *in_fd);
	else
		*in_fd = dup(pipe_fd[0]);
	close(pipe_fd[0]);
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
	if (in_fd != -1)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != -1)
		dup2(out_fd, STDOUT_FILENO);
}
