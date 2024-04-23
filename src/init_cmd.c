/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:50:08 by blebas            #+#    #+#             */
/*   Updated: 2024/04/23 15:06:39 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(t_token *tklst)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	j = 0;
	i = tklst_len(tklst);
	cmd = malloc(sizeof(t_cmd));
	cmd->argv = malloc(sizeof(char *) * (i + 1));
	cmd->argc = i;
	while (tklst != NULL && tklst->type != pope)
	{
		if (tklst->type == word)
		{
			cmd->argv[j] = ft_strdup(tklst->str);
			j++;
		}
		tklst = tklst->next;
	}
	cmd->argv[j] = NULL;
	return (cmd);
}

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (env->value)
			i++;
		env = env->next;
	}
	return (i);
}

char	**init_envp(t_env *env)
{
	int		i;
	char	*buf;
	char	**envp;

	envp = malloc(sizeof(char *) * (env_len(env)));
	i = 0;
	while (env != NULL)
	{
		if (env->value && env->key[0] != '?')
		{
			buf = ft_strjoin(env->key, "=");
			envp[i] = ft_strjoin(buf, env->value);
			free(buf);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
