/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:44:23 by macbook           #+#    #+#             */
/*   Updated: 2024/05/01 17:33:49 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_cmd(void)
{
	char	*dir;
	size_t	size_dir;

	size_dir = 1024;
	dir = malloc(size_dir);
	if (!dir)
	{
		ft_putstr_fd("Memory alloc failed", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (!getcwd(dir, size_dir))
	{
		ft_putstr_fd("Cant't find directory", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	ft_putstr_fd(dir, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	cd_cmd(char **argv, t_env *env)
{
	char	*pwd;
	char	*pwdd;

	if (!argv[1])
		return (1);
	if (argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(argv[1]);
		return (1);
	}
	pwdd = getcwd(NULL, 0);
	pwd = get_env(env, "PWD");
	set_env(env, "OLDPWD", pwd);
	set_env(env, "PWD", pwdd);
	free(pwd);
	free(pwdd);
	return (0);
}
