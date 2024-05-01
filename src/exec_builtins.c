/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:17:12 by blebas            #+#    #+#             */
/*   Updated: 2024/05/01 17:08:09 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_cmd *cmd, t_env *env)
{
	if (!cmd->argv || !cmd->argv[0])
		return (-1);
	if (ft_strncmp(cmd->argv[0], "echo", -1) == 0)
		return (echo_cmd(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "cd", -1) == 0)
		return (cd_cmd(cmd->argv, env));
	if (ft_strncmp(cmd->argv[0], "pwd", -1) == 0)
		return (pwd_cmd());
	if (ft_strncmp(cmd->argv[0], "env", -1) == 0)
		return (env_cmd(env));
	return (-1);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", -1) == 0)
		return (1);
	return (0);
}
