/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:45:55 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/11 19:09:03 by blebas           ###   ########.fr       */
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

void	str_add_char(char **str, char c)
{
	char	*buf;
	size_t	len;

	len = 0;
	if (!(*str))
		*str = malloc(sizeof(char) * 2);
	else
	{
		buf = *str;
		len = ft_strlen(*str);
		*str = malloc(sizeof(char) * (len + 2));
		ft_strlcpy(*str, buf, -1);
	}
	(*str)[len + 0] = c;
	(*str)[len + 1] = '\0';
}
