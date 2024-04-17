/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:13:12 by blebas            #+#    #+#             */
/*   Updated: 2024/04/17 19:06:35 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_envar_key(char **cmdline)
{
	char	*key;

	key = NULL;
	while (**cmdline && !is_token_end(**cmdline)
		&& **cmdline != '\'' && **cmdline != '\"')
	{
		str_add_char(&key, **cmdline);
		++(*cmdline);
	}
	return (key);
}

void	parse_envar_val_to_tk(t_token **tklst, char *value)
{
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

void	parse_envar(t_env *env, t_token **tklst, char **cmdline)
{
	char	*key;
	char	*value;

	key = parse_envar_key(cmdline);
	if (key == NULL)
	{
		if (!(*tklst) || get_last_tk(*tklst)->stop)
			tklst_addd(tklst, word);
		tk_add_char(*tklst, '$');
		return ;
	}
	value = get_env(env, key);
	free(key);
	if (!value)
		return ;
	parse_envar_val_to_tk(tklst, value);
	if (value)
		free(value);
}
