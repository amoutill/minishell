/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:09:02 by blebas            #+#    #+#             */
/*   Updated: 2024/04/17 19:18:30 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_tab(char **strtab)
{
	size_t	i;

	i = 0;
	while (strtab[i])
		free(strtab[i++]);
	free(strtab);
}

void	free_cmd(t_cmd *cmd)
{
	free_str_tab(cmd->argv);
	free(cmd);
}
