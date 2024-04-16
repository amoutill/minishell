/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_squote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:48:37 by blebas            #+#    #+#             */
/*   Updated: 2024/04/16 16:25:48 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_token_end(char s)
{
	if (ft_isspace(s) || s == '|' || s == '<' || s == '>')
		return (true);
	return (false);
}

void	parse_squote(t_token **tklst, char **str)
{
	if (!(*tklst) || get_last_tk(*tklst)->stop)
		tklst_addd(tklst, word);
	while (**str && **str != '\'')
	{
		tk_add_char(*tklst, **str);
		(*str)++;
	}
	if (**str)
		++(*str);
}

void	parse_dquote(t_token **tklst, char **str)
{
	if (!(*tklst) || get_last_tk(*tklst)->stop)
		tklst_addd(tklst, word);
	while (**str && **str != '\"')
	{
		//if (**str == '$')
			//parse_envar();
		//else
			tk_add_char(*tklst, **str);
		(*str)++;
	}
	if (**str)
		++(*str);
}
