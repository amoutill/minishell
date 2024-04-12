/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:13:12 by blebas            #+#    #+#             */
/*   Updated: 2024/04/12 18:09:23 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_last_tk(t_token **tklst)
{
	if ((*tklst)->next)
		free_last_tk(&((*tklst)->next));
	else
	{
		free(*tklst);
		*tklst = NULL;
	}
}

int	parse_envar(t_env *env, t_token **tklst, char **cmdline)
{
	char	*key;
	char	*value;

	key = NULL;
	while (**cmdline && !is_token_end(**cmdline) && **cmdline != '\'' && **cmdline != '\"')
	{
		str_add_char(&key, **cmdline);
		++(*cmdline);
	}
	if (key == NULL)
	{
		tk_add_char(*tklst, '$');
		return (**cmdline == '\'' || **cmdline == '\"');
	}
	value = get_env(env, key);
	if (!value)
	{
		free_last_tk(tklst);
		return (**cmdline == '\'' || **cmdline == '\"');
	}
	//tklst_addd(&tklst, word);
	ft_skip_spaces(&value);
	while (*value && !ft_isspace(*value))
	{
		tk_add_char(*tklst, *value);
		++value;
	}
	while (*value)
	{
		ft_skip_spaces(&value);
		if (*value)
			tklst_addd(tklst, word);
		while (*value && !ft_isspace(*value))
		{
			tk_add_char(*tklst, *value);
			++value;
		}
	}
	return (**cmdline == '\'' || **cmdline == '\"');
}
