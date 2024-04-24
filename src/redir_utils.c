/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:10:06 by blebas            #+#    #+#             */
/*   Updated: 2024/04/24 15:13:59 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_err(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(file);
}

void	replace_fds(int in_fd, int out_fd)
{
	if (in_fd != -1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

void	here_doc_eof_err(char *eof)
{
	ft_putstr_fd(HD_ERR, STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putstr_fd(HD_ERR_END, STDERR_FILENO);
}

void	dup_and_close(int fd, int *fd2)
{
	if (*fd2 != -1)
		dup2(fd, *fd2);
	else
		*fd2 = dup(fd);
	close(fd);
}

char	*readline_here_doc(char *eof)
{
	char	*buf;
	char	*buff;
	char	*bufff;

	buff = ft_strdup("");
	while (1)
	{
		buf = readline("> ");
		if (!buf || !ft_strncmp(buf, eof, -1))
		{
			if (!buf)
				here_doc_eof_err(eof);
			break ;
		}
		bufff = ft_strjoin(buff, buf);
		free(buf);
		free(buff);
		buff = ft_strjoin(bufff, "\n");
		free(bufff);
	}
	return (buff);
}
