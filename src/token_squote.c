/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_squote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:48:37 by blebas            #+#    #+#             */
/*   Updated: 2024/04/10 18:46:41 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_token_end(char s)
{
	if (ft_isspace(s) || s == '|' || s == '<' || s == '>')
		return (true);
	return (false);
}

void	parse_squote(t_token *tklst, char **str)
{
	while (**str && **str != '\'')
	{
		tk_add_char(tklst, **str);
		(*str)++;
	}
}
