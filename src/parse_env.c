/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:13:12 by blebas            #+#    #+#             */
/*   Updated: 2024/04/16 17:56:13 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_last_tk(t_token **tklst)
// {
// 	if ((*tklst)->next)
// 		free_last_tk(&((*tklst)->next));
// 	else
// 	{
// 		free(*tklst);
// 		*tklst = NULL;
// 	}
// }

void	parse_envar(t_env *env, t_token **tklst, char **cmdline)
{
	char	*key;
	char	*value;

	key = NULL;
	while (**cmdline && !is_token_end(**cmdline)
		&& **cmdline != '\'' && **cmdline != '\"')
	{
		str_add_char(&key, **cmdline);
		++(*cmdline);
	}
	if (key == NULL)
	{
		if (!(*tklst) || get_last_tk(*tklst)->stop)
			tklst_addd(tklst, word);
		tk_add_char(*tklst, '$');
		return ;
	}
	value = get_env(env, key);
	if (!value)
		return ;
	if (!(*tklst) || get_last_tk(*tklst)->stop)
		tklst_addd(tklst, word);
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
}
