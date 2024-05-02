/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:27 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 18:10:59 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_forked(t_exec exec_data)
{
	char	*cmd_path;
	char	**envp;
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
	{
		cmd_path = ft_which(exec_data.env, exec_data.current_cmd->argv[0]);
		if (!cmd_path)
		{
			free_and_close_child(exec_data);
			exit(127);
		}
		exit_if_invalid_cmd(exec_data, cmd_path);
		envp = init_envp(exec_data.env);
		execve(cmd_path, exec_data.current_cmd->argv, envp);
		perror(cmd_path);
		free(cmd_path);
		free_str_tab(envp);
	}
	free_and_close_child(exec_data);
	exit(126);
}

int	exec(t_exec exec_data)
{
	pid_t	pid[4096];
	size_t	nb_cmd;
	size_t	i;
	int		pipe_fd[2];
	int		retval;
	int		tmr;

	pipe_fd[0] = -1;
	nb_cmd = count_cmd(exec_data.cmd);
	i = 0;
	while (i < nb_cmd)
	{
		setup_pipes(&exec_data, pipe_fd, nb_cmd, i);
		tmr = redir_open(exec_data, pipe_fd[0]);
		if (!tmr)
		{
			if (nb_cmd == 1 && is_builtin(exec_data.current_cmd->argv[0]))
				return (builtins_tortilla(exec_data));
			else
			{
				pid[i] = fork();
				if (pid[i] == 0)
					exec_forked(exec_data);
				close_fds(exec_data.current_cmd->in_fd,
					exec_data.current_cmd->out_fd);
			}
		}
		else
		{
			pid[i] = -1;
			if (tmr < -1)
			{
				if (pipe_fd[0] != -1)
				{
					close(pipe_fd[0]);
					close(pipe_fd[1]);
				}
				break ;
			}
		}
		i++;
		exec_data.current_cmd = exec_data.current_cmd->next;
		advance_to_next_pipe_tk(&exec_data);
	}
	if (tmr)
		return (tmr);
	retval = wait_cmd(pid, nb_cmd);
	return (retval);
}
