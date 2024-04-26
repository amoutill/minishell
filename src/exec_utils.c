/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:55:26 by blebas            #+#    #+#             */
/*   Updated: 2024/04/26 16:55:49 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
