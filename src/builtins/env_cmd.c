/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:16:58 by blebas            #+#    #+#             */
/*   Updated: 2024/04/15 15:30:05 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_cmd(char **argv, t_env *env)
{
	if (argv[1])
	{
		ft_putstr_fd("Too many args\n", STDERR_FILENO);
		return (0);
	}
	while (env != NULL)
	{
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		env = env->next;
	}
	return (0);
}