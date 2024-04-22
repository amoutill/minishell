/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:26:27 by blebas            #+#    #+#             */
/*   Updated: 2024/04/22 17:05:43 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_tab(t_env *env)
{
	while (env && ft_strncmp(env->key, "PATH", -1))
		env = env->next;
	if (!env)
		return (NULL);
	return (ft_split(env->value, ':'));
}

char	*compose_cmd_path(char *cmd, char *path)
{
	char	*join_path;
	char	*join_join_path;

	join_path = ft_strjoin(path, "/");
	join_join_path = ft_strjoin(join_path, cmd);
	free(join_path);
	return (join_join_path);
}

char	*ft_which(t_env *env, char *cmd)
{
	int			i;
	char		*cmd_composed;
	char		**path_tab;
	struct stat	cmd_stat;

	(void)cmd_stat;
	i = 0;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (*cmd == '\0')
		return (NULL);
	path_tab = get_path_tab(env);
	while (path_tab && path_tab[i])
	{
		cmd_composed = compose_cmd_path(cmd, path_tab[i]);
		if (!stat(cmd_composed, &cmd_stat))
		{
			free_str_tab(path_tab);
			return (cmd_composed);
		}
		free(cmd_composed);
		i++;
	}
	return (NULL);
}
