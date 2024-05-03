/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:52:11 by blebas            #+#    #+#             */
/*   Updated: 2024/05/03 13:52:42 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_in_main(t_exec *exec_data)
{
	char	*retval_str;
	int		retval;

	exec_data->cmd = init_cmd(exec_data->tklst);
	exec_data->current_cmd = exec_data->cmd;
	signal(SIGINT, sig_handler_incmd);
	signal(SIGQUIT, sig_handler_incmd);
	retval = exec(*exec_data);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	free_cmd(exec_data->cmd);
	if (retval < 0)
		retval_str = ft_itoa(-retval);
	else
		retval_str = ft_itoa(retval);
	set_env(exec_data->env, "?", retval_str);
	free(retval_str);
	return (retval);
}
