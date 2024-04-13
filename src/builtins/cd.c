/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:44:23 by macbook           #+#    #+#             */
/*   Updated: 2024/04/13 14:44:24 by macbook          ###   ########.fr       */
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

int	cd_cmd(char **argv)
{
	if (argv[2])
	{
		ft_putstr_fd("Too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
