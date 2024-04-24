/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:27 by blebas            #+#    #+#             */
/*   Updated: 2024/04/24 20:34:29 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_signal;

void	exit_if_invalid_cmd(char *cmd_path)
{
	struct stat	cmd_stat;

	stat(cmd_path, &cmd_stat);
	if (S_ISDIR(cmd_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		exit(126);
	}
	if (!(cmd_stat.st_mode & S_IXUSR))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		exit(126);
	}
}

void	free_and_close_child(t_exec exec_data, int in_fd, int out_fd)
{
	free_env(exec_data.env);
	free_cmd(exec_data.cmd);
	free_tklst(exec_data.tklst);
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (in_fd != -1)
		close(in_fd);
	if (out_fd != -1)
		close(out_fd);
}

void	exec_forked(t_exec exec_data)
{
	char	*cmd_path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	redir_open(exec_data);
	signal(SIGQUIT, SIG_DFL);
	if (!exec_data.cmd->argv[0])
	{
		free_and_close_child(exec_data, -1, -1);
		exit(0);
	}
	cmd_path = ft_which(exec_data.env, exec_data.cmd->argv[0]);
	if (!cmd_path)
	{
		free_and_close_child(exec_data, -1, -1);
		exit(127);
	}
	exit_if_invalid_cmd(cmd_path);
	envp = init_envp(exec_data.env);
	execve(cmd_path, exec_data.cmd->argv, envp);
	perror(cmd_path);
	free(cmd_path);
	free_str_tab(envp);
	free_and_close_child(exec_data, -1, -1);
	exit(126);
}

int	exec(t_exec exec_data)
{
	pid_t	pid;
	int		stat_loc;
	int		retval;

	retval = exec_cmd(exec_data.cmd, exec_data.env);
	if (retval != -1)
		return (retval);
	pid = fork();
	if (pid == 0)
		exec_forked(exec_data);
	waitpid(pid, &stat_loc, 0);
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
