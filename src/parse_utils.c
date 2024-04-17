/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutill <amoutill@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:24:27 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/17 17:46:00 by amoutill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_token_end(char c)
{
	if (ft_isspace(c) || c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_spec_char(char c)
{
	if (c == '\'' || c == '\"' || c == '$' || c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}
