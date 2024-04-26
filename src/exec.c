/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:27 by blebas            #+#    #+#             */
/*   Updated: 2024/04/26 17:10:17 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_signal;

void	exec_forked(t_exec exec_data)
{
	char	*cmd_path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	redir_open(exec_data);
	signal(SIGQUIT, SIG_DFL);
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
	int		stat_loc;
	size_t	nb_cmd;
	size_t	i;
	int		pipe_fd[2];
	//int		retval;

	//retval = exec_cmd(exec_data.cmd, exec_data.env);
	//if (retval != -1)
	//	return (retval);
	nb_cmd = count_cmd(exec_data.cmd);
	pid = malloc(sizeof(pid_t) * nb_cmd);
	i = 0;
	while (i < nb_cmd)
	{
		if (i)
			exec_data.current_cmd->in_fd = pipe_fd[0];
		if (i < nb_cmd - 1)
		{
			pipe(pipe_fd);
			exec_data.current_cmd->out_fd = pipe_fd[1];
			exec_data.current_cmd->fd_to_close = pipe_fd[0];
		}
		pid[i] = fork();
		if (pid[i] == 0)
		{
			free(pid);
			exec_forked(exec_data);
		}
		if (exec_data.current_cmd->in_fd != -1)
			close(exec_data.current_cmd->in_fd);
		if (exec_data.current_cmd->out_fd != -1)
			close(exec_data.current_cmd->out_fd);
		exec_data.current_cmd = exec_data.current_cmd->next;
		i++;
		while (exec_data.current_tk && exec_data.current_tk->type != pope)
			exec_data.current_tk = exec_data.current_tk->next;
		if (exec_data.current_tk && exec_data.current_tk->type == pope)
			exec_data.current_tk = exec_data.current_tk->next;
	}
	i = 0;
	while (i < nb_cmd)
	{
		waitpid(pid[i], &stat_loc, 0);
		++i;
	}
	free(pid);
	if (g_last_signal)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_last_signal = 0;
	}
	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	else if (WIFSIGNALED(stat_loc))
		return (128 + WTERMSIG(stat_loc));
	return (0);
}
