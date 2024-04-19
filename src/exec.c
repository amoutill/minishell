/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:27 by blebas            #+#    #+#             */
/*   Updated: 2024/04/19 16:45:59 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_cmd *cmd, t_env *env)
{
	char	*cmd_path;
	pid_t	pid;

	cmd_path = ft_which(env, cmd->argv[0]);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, cmd->argv, init_envp(env));
	}
	waitpid(pid, NULL, 0);
	return (0);
}
