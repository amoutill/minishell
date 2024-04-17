/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:48:37 by blebas            #+#    #+#             */
/*   Updated: 2024/04/17 18:04:48 by amoutill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_squote(t_token **tklst, char **cmdline)
{
	if (!(*tklst) || get_last_tk(*tklst)->stop)
		tklst_addd(tklst, word);
	while (**cmdline && **cmdline != '\'')
	{
		tk_add_char(*tklst, **cmdline);
		(*cmdline)++;
	}
	if (**cmdline)
		++(*cmdline);
}

void	parse_dquote(t_env *env, t_token **tklst, char **cmdline)
{
	if (!(*tklst) || get_last_tk(*tklst)->stop)
		tklst_addd(tklst, word);
	while (**cmdline && **cmdline != '\"')
	{
		if (**cmdline == '$')
		{
			++(*cmdline);
			parse_envar(env, tklst, cmdline);
		}
		else
		{
			tk_add_char(*tklst, **cmdline);
			(*cmdline)++;
		}
	}
	if (**cmdline)
		++(*cmdline);
}
