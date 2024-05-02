/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:24:56 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 21:31:56 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_long_long(char *nptr)
{
	return (is_pos_long_long(nptr) || is_neg_long_long(nptr));
}

long long	ft_atoll(const char *nptr)
{
	long long	res;
	long long	j;
	long long	k;

	res = 0;
	j = 0;
	k = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (nptr[0] == '-')
		k = -1;
	if (*nptr == '-' || *nptr == '+')
	{
		j++;
		nptr++;
		if (j >= 2)
			return (0);
	}
	while ((*nptr != '\0') && (*nptr >= '0' && *nptr <= '9'))
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	return (res * k);
}

long long	exit_kill_me(t_exec *exec_data)
{
	if (!is_long_long(exec_data->current_cmd->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(exec_data->current_cmd->argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	else if (exec_data->current_cmd->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n",
			STDERR_FILENO);
		return (1);
	}
	else
		return (ft_atoll(exec_data->current_cmd->argv[1]));
}

void	exit_cmd(t_exec *exec_data, int stdin_bkp, int stdout_bkp)
{
	long long	retval;
	char		*retval_str;

	if (exec_data->current_cmd->argv[1])
		retval = exit_kill_me(exec_data);
	else
	{
		retval_str = get_env(exec_data->env, "?");
		retval = ft_atoll(retval_str);
		free(retval_str);
	}
	if (stdin_bkp != -1)
		close(stdin_bkp);
	if (stdout_bkp != -1)
		close(stdout_bkp);
	free_cmd(exec_data->cmd);
	free_env(exec_data->env);
	free_tklst(exec_data->tklst);
	rl_clear_history();
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(retval);
}
