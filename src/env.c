/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:10:10 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/17 17:22:46 by amoutill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}

void	set_env(t_env *env, char *key, char *value)
{
	while (env->next && ft_strncmp(env->key, key, -1))
		env = env->next;
	if (ft_strncmp(env->key, key, -1) == 0)
	{
		if (value)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(value);
		}
	}
	else
		env->next = new_env(key, value);
}

t_env	*init_env(const char *envp[])
{
	t_env	*env;
	size_t	i;
	char	*key;
	char	*value;

	env = NULL;
	while (*envp)
	{
		i = 0;
		while ((*envp)[i] && (*envp)[i] != '=')
			++i;
		key = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(key, *envp, i + 1);
		value = malloc(sizeof(char) * (ft_strlen(*envp) - i));
		ft_strlcpy(value, *envp + i + 1, ft_strlen(*envp) - i);
		if (!env)
			env = new_env(key, value);
		else
			set_env(env, key, value);
		free(key);
		free(value);
		++envp;
	}
	return (env);
}

char	*get_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, -1))
		{
			if (env->value)
				return (ft_strdup(env->value));
			return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}
