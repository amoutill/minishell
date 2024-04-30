/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:07:55 by blebas            #+#    #+#             */
/*   Updated: 2024/04/30 20:11:19 by blebas           ###   ########.fr       */
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
