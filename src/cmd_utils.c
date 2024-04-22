/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:09:02 by blebas            #+#    #+#             */
/*   Updated: 2024/04/22 17:37:57 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_tab(char **strtab)
{
	size_t	i;

	i = 0;
	if (!strtab)
		return ;
	while (strtab[i])
		free(strtab[i++]);
	free(strtab);
}

void	free_cmd(t_cmd *cmd)
{
	free_str_tab(cmd->argv);
	free(cmd);
}

void	print_str_tab(char **strtab)
{
	int	i;

	i = 0;
	while (strtab[i])
	{
		printf("envp : %s\n", strtab[i]);
		i++;
	}
}
