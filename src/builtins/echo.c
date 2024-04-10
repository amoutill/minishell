/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:55:27 by blebas            #+#    #+#             */
/*   Updated: 2024/04/10 18:49:58 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_cmd(char **argv)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (argv[i] && !ft_strncmp(argv[i], "-n", -1))
	{
		n = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
