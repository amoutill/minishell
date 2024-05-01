/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:40:19 by blebas            #+#    #+#             */
/*   Updated: 2024/05/01 21:12:27 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(t_env *env, char *key)
{
	t_env	*prev;

	while (env && ft_strncmp(env->key, key, -1))
	{
		prev = env;
		env = env->next;
	}
	free(env->key);
	if (env->value)
		free(env->value);
	prev->next = env->next;
	free(env);
}
