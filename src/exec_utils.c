/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:55:26 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 16:17:58 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_signal;

void	exit_if_invalid_cmd(t_exec exec_data, char *cmd_path)
{
	struct stat	cmd_stat;

	if(stat(cmd_path, &cmd_stat))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_and_close_child(exec_data);
		free(cmd_path);
		exit(127);
	}
	if (S_ISDIR(cmd_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		free_and_close_child(exec_data);
		free(cmd_path);
		exit(126);
	}
	if (!(cmd_stat.st_mode & S_IXUSR))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		free_and_close_child(exec_data);
		free(cmd_path);
		exit(126);
	}
}

void	free_and_close_child(t_exec exec_data)
{
	if (exec_data.current_cmd->in_fd != -1)
		close(exec_data.current_cmd->in_fd);
	if (exec_data.current_cmd->out_fd != -1)
		close(exec_data.current_cmd->out_fd);
	free_env(exec_data.env);
	free_cmd(exec_data.cmd);
	free_tklst(exec_data.tklst);
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	wait_cmd(pid_t *pid, size_t nb_cmd)
{
	int		stat_loc;
	size_t	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (pid[i] != -1)
			waitpid(pid[i], &stat_loc, 0);
		++i;
	}
	if (g_last_signal)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_last_signal = 0;
	}
	if (pid[i - 1] == -1)
		return (1);
	else if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	else if (WIFSIGNALED(stat_loc))
		return (128 + WTERMSIG(stat_loc));
	return (0);
}

void	close_fds(int in_fd, int out_fd)
{
	if (in_fd != -1)
		close(in_fd);
	if (out_fd != -1)
		close(out_fd);
}

void	advance_to_next_pipe_tk(t_exec *exec_data)
{
	while (exec_data->current_tk && exec_data->current_tk->type != pope)
		exec_data->current_tk = exec_data->current_tk->next;
	if (exec_data->current_tk && exec_data->current_tk->type == pope)
		exec_data->current_tk = exec_data->current_tk->next;
}
