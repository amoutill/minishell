/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:27 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 21:18:42 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_notabuiltin(t_exec *exec_data)
{
	char	*cmd_path;
	char	**envp;

	cmd_path = ft_which(exec_data->env, exec_data->current_cmd->argv[0]);
	if (!cmd_path)
	{
		free_and_close_child(*exec_data);
		exit(127);
	}
	exit_if_invalid_cmd(*exec_data, cmd_path);
	envp = init_envp(exec_data->env);
	execve(cmd_path, exec_data->current_cmd->argv, envp);
	perror(cmd_path);
	free(cmd_path);
	free_str_tab(envp);
}

void	exec_forked(t_exec exec_data)
{
	int		retval;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (exec_data.current_cmd->fd_to_close != -1)
		close(exec_data.current_cmd->fd_to_close);
	replace_fds(exec_data.current_cmd->in_fd, exec_data.current_cmd->out_fd);
	if (!exec_data.current_cmd->argv[0])
	{
		free_and_close_child(exec_data);
		exit(0);
	}
	if (is_builtin(exec_data.current_cmd->argv[0]))
	{
		retval = exec_cmd(exec_data, -1, -1);
		free_and_close_child(exec_data);
		exit(retval);
	}
	else
		exec_notabuiltin(&exec_data);
	free_and_close_child(exec_data);
	exit(126);
}

int	returny_things(t_ilovethenorm *aaa)
{
	if (aaa->retval)
		return (aaa->retval);
	return (wait_cmd(aaa->pid, aaa->nb_cmd));
}

int	exec(t_exec exec_data)
{
	t_ilovethenorm	aaa;

	aaa = init_things(exec_data.cmd);
	while (aaa.i < aaa.nb_cmd)
	{
		other_things(&exec_data, &aaa);
		if (!(aaa.retval))
		{
			if (aaa.nb_cmd == 1 && is_builtin(exec_data.current_cmd->argv[0]))
				return (builtins_tortilla(exec_data));
			else
				other_things_but_in_else(exec_data, &aaa);
		}
		else
		{
			aaa.pid[aaa.i] = -1;
			if (aaa.retval < -1)
			{
				closing_pipey_things(&aaa);
				break ;
			}
		}
		bottom_of_while_things(&exec_data, &aaa);
	}
	return (returny_things(&aaa));
}
