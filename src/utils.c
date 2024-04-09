/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutill <amoutill@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:45:55 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/09 16:42:09 by amoutill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_tktlst(t_token *token)
{
	while (token != NULL)
	{
		printf("%s\n", token->str);
		token = token->next;
	}
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("key: %s\nvalue: %s\n", env->key, env->value);
		env = env->next;
	}
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}
