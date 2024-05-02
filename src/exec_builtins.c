/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:17:12 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 18:53:20 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_exec exec_data, int stdin_bkp, int stdout_bkp)
{
	if (!exec_data.current_cmd->argv || !exec_data.current_cmd->argv[0])
		return (-1);
	if (ft_strncmp(exec_data.current_cmd->argv[0], "echo", -1) == 0)
		return (echo_cmd(exec_data.current_cmd->argv));
	if (ft_strncmp(exec_data.current_cmd->argv[0], "cd", -1) == 0)
		return (cd_cmd(exec_data.current_cmd->argv, exec_data.env));
	if (ft_strncmp(exec_data.current_cmd->argv[0], "pwd", -1) == 0)
		return (pwd_cmd());
	if (ft_strncmp(exec_data.current_cmd->argv[0], "env", -1) == 0)
		return (env_cmd(exec_data.env));
	if (ft_strncmp(exec_data.current_cmd->argv[0], "export", -1) == 0)
		return (export_cmd(exec_data.env, exec_data.current_cmd->argv));
	if (ft_strncmp(exec_data.current_cmd->argv[0], "unset", -1) == 0)
		return (unset_cmd(exec_data.current_cmd->argv, exec_data.env));
	if (ft_strncmp(exec_data.current_cmd->argv[0], "exit", -1) == 0)
		return (exit_cmd(&exec_data, stdin_bkp, stdout_bkp), 0);
	return (-1);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", -1) == 0)
		return (1);
	return (0);
}
