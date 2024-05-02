/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:27:35 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 15:05:20 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_export(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (0);
		}
		++i;
	}
	return (1);
}

int	export_noarg(t_env *env)
{
	while (env)
	{
		if (env->key[0] == '?')
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->value)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		env = env->next;
	}
	return (0);
}

void	export_val(char *str, t_env *env)
{
	char	*eq_ptr;
	char	*key;
	char	*value;

	value = NULL;
	eq_ptr = ft_strchr(str, '=');
	if (eq_ptr)
	{
		key = ft_substr(str, 0, eq_ptr - str);
		value = ft_substr(str, eq_ptr - str + 1, -1);
	}
	else
		key = ft_strdup(str);
	set_env(env, key, value);
	free(key);
	if (value)
		free(value);
}

int	export_cmd(t_env *env, char **argv)
{
	int		i;
	int		err;

	i = 1;
	err = 0;
	if (!argv[1])
		return (export_noarg(env));
	while (argv[i])
	{
		if (!is_valid_export(argv[i]))
		{
			++i;
			err = 1;
			continue ;
		}
		export_val(argv[i], env);
		++i;
	}
	return (err);
}
