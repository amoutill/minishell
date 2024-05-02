/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:55:27 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 15:10:35 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_cmd(char **argv)
{
	size_t	i;
	int		nl;

	i = 1;
	if (!argv[i])
		return (0);
	if (!ft_strncmp(argv[i], "-n", -1))
	{
		nl = 0;
		++i;
	}
	else
		nl = 1;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (nl == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
