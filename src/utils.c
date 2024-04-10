/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:45:55 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/10 15:43:28 by amoutill         ###   ########.fr       */
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

void	free_last(t_token **tklst)
{
	t_token	*prev;

	if (!*tklst)
		return ;
	prev = *tklst;
	while ((*tklst)->next)
	{
		prev = *tklst;
		*tklst = (*tklst)->next;
	}
	if (!(*tklst)->str)
	{
		if (prev != (*tklst))
			prev->next = NULL;
		free(*tklst);
		*tklst = NULL;
	}
}
