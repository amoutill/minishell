/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:45:55 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/10 18:33:14 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_tktlst(t_token *token)
{
	while (token != NULL)
	{
		printf("str: %s\n", token->str);
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
	t_token	*first;
	t_token	*prev;

	if (!*tklst)
		return ;
	first = *tklst;
	prev = *tklst;
	while ((*tklst)->next)
	{
		prev = *tklst;
		*tklst = (*tklst)->next;
	}
	if (!(*tklst)->str)
	{
		free(*tklst);
		if (prev != *tklst)
			prev->next = NULL;
		if (first == *tklst)
			*tklst = NULL;
		else
			*tklst = first;
	}
	else if (first != *tklst)
		*tklst = first;
}
