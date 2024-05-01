/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:44:23 by macbook           #+#    #+#             */
/*   Updated: 2024/05/01 18:24:59 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_cmd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	ft_putstr_fd(dir, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(dir);
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
