/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:09:02 by blebas            #+#    #+#             */
/*   Updated: 2024/04/26 15:19:59 by blebas           ###   ########.fr       */
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
	if (cmd->next)
		free_cmd(cmd->next);
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

size_t	count_cmd(t_cmd *cmd)
{
	size_t	n;

	n = 0;
	while (cmd)
	{
		++n;
		cmd = cmd->next;
	}
	return (n);
}
