/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:34:18 by blebas            #+#    #+#             */
/*   Updated: 2024/05/01 20:13:08 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_unset(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (0);
		}
		++i;
	}
	return (1);
}

int	unset_cmd(char **argv, t_env *env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_unset(argv[i]))
		{
			++i;
			continue ;
		}
		del_env(env, argv[i]);
		++i;
	}
	return (0);
}
