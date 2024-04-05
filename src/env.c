/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutill <amoutill@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:10:10 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/05 16:47:55 by amoutill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_env	*init_env(const char *envp[])
{
	t_env	*env;
	t_env	*env_first;
	size_t	i;

	env_first = NULL;
	while (*envp)
	{
		if (!env_first)
		{
			env = malloc(sizeof(t_env));
			env_first = env;
		}
		else
		{
			env->next = malloc(sizeof(t_env));
			env = env->next;
		}
		i = 0;
		while ((*envp)[i] && (*envp)[i] != '=')
			++i;
		env->key = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(env->key, *envp, i + 1);
		env->value = malloc(sizeof(char) * (ft_strlen(*envp) - i));
		ft_strlcpy(env->value, *envp + i + 1, ft_strlen(*envp) - i);
		++envp;
	}
	env->next = NULL;
	return (env_first);
}
