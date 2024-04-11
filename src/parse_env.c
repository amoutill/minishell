/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:13:12 by blebas            #+#    #+#             */
/*   Updated: 2024/04/11 19:46:43 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_envar(t_env *env, t_token *tklst, char **cmdline)
{
	char	*key;
	char	*value;

	key = NULL;
	while (**cmdline && !is_token_end(**cmdline))
	{
		str_add_char(&key, **cmdline);
		++cmdline;
	}
	value = get_env(env, key);
	while (*value)
	{
		while (ft_isspace(*value))
			++value;
		if (*value)
			tklst_addd(&tklst, word);
		while (*value && !ft_isspace(*value))
		{
			tk_add_char(tklst, *value);
			++value;
		}
	}
}