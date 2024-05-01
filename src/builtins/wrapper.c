/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:54:45 by blebas            #+#    #+#             */
/*   Updated: 2024/05/01 16:18:03 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins_tortilla(t_exec exec_data)
{
	int	stdin_bkp;
	int	stdout_bkp;
	int	retval;

	stdin_bkp = dup(STDIN_FILENO);
	stdout_bkp = dup(STDOUT_FILENO);
	replace_fds(exec_data.current_cmd->in_fd, exec_data.current_cmd->out_fd);
	retval = exec_cmd(exec_data.current_cmd, exec_data.env);
	replace_fds(stdin_bkp, stdout_bkp);
	return (retval);
}
