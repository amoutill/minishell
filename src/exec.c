/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:27 by blebas            #+#    #+#             */
/*   Updated: 2024/04/30 21:11:59 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_forked(t_exec exec_data)
{
	char	*cmd_path;
	char	**envp;

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
	cmd_path = ft_which(exec_data.env, exec_data.current_cmd->argv[0]);
	if (!cmd_path)
	{
		free_and_close_child(exec_data);
		exit(127);
	}
	exit_if_invalid_cmd(cmd_path);
	envp = init_envp(exec_data.env);
	execve(cmd_path, exec_data.current_cmd->argv, envp);
	perror(cmd_path);
	free(cmd_path);
	free_str_tab(envp);
	free_and_close_child(exec_data);
	exit(126);
}

int	exec(t_exec exec_data)
{
	pid_t	*pid;
	size_t	nb_cmd;
	size_t	i;
	int		pipe_fd[2];
	int		retval;

	nb_cmd = count_cmd(exec_data.cmd);
	pid = malloc(sizeof(pid_t) * nb_cmd);
	i = 0;
	while (i < nb_cmd)
	{
		setup_pipes(&exec_data, pipe_fd, nb_cmd, i);
		redir_open(exec_data);
		pid[i] = fork();
		if (pid[i++] == 0)
		{
			free(pid);
			exec_forked(exec_data);
		}
		close_fds(exec_data.current_cmd->in_fd, exec_data.current_cmd->out_fd);
		exec_data.current_cmd = exec_data.current_cmd->next;
		advance_to_next_pipe_tk(&exec_data);
	}
	retval = wait_cmd(pid, nb_cmd);
	free(pid);
	return (retval);
}
