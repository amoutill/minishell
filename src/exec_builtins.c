/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:17:12 by blebas            #+#    #+#             */
/*   Updated: 2024/04/10 18:52:30 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_cmd *cmd)
{
	if (ft_strncmp(cmd->argv[0], "echo", -1) == 0)
		return (echo_cmd(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "cd", -1) == 0)
		return (cd_cmd(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "pwd", -1) == 0)
		return (pwd_cmd());
	return (0);
}
