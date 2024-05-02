/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:07:55 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 20:46:14 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipes(t_exec *exec_data, int pipe_fd[2], size_t nb_cmd, size_t i)
{
	if (i)
		exec_data->current_cmd->in_fd = pipe_fd[0];
	if (i < nb_cmd - 1)
	{
		pipe(pipe_fd);
		exec_data->current_cmd->out_fd = pipe_fd[1];
		exec_data->current_cmd->fd_to_close = pipe_fd[0];
	}
}

void	write_free_close_and_exit(t_exec exec_data, char *cmd_path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_path, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	free_and_close_child(exec_data);
	free(cmd_path);
	exit(127);
}
