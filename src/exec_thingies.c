/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_thingies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:33:11 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 21:09:00 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ilovethenorm	init_things(t_cmd *some_cmd)
{
	t_ilovethenorm	exec_things;

	exec_things.pipe_fd[0] = -1;
	exec_things.pipe_fd[1] = -1;
	exec_things.nb_cmd = count_cmd(some_cmd);
	exec_things.i = 0;
	return (exec_things);
}

void	other_things(t_exec *exec_data, t_ilovethenorm *aaa)
{
	setup_pipes(exec_data, aaa->pipe_fd, aaa->nb_cmd, aaa->i);
	aaa->retval = redir_open(*exec_data, aaa->pipe_fd);
}

void	other_things_but_in_else(t_exec exec_data, t_ilovethenorm *aaa)
{
	aaa->pid[aaa->i] = fork();
	if (aaa->pid[aaa->i] == 0)
		exec_forked(exec_data);
}

void	closing_pipey_things(t_ilovethenorm *aaa)
{
	if (aaa->pipe_fd[0] != -1)
	{
		close(aaa->pipe_fd[0]);
		close(aaa->pipe_fd[1]);
	}
}

void	bottom_of_while_things(t_exec *exec_data, t_ilovethenorm *aaa)
{
	close_fds(exec_data->current_cmd->in_fd, exec_data->current_cmd->out_fd);
	aaa->i++;
	exec_data->current_cmd = exec_data->current_cmd->next;
	advance_to_next_pipe_tk(exec_data);
}
