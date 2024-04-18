/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:24:27 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/18 16:21:18 by blebas           ###   ########.fr       */
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

void	print_stx_err(t_tktype type)
{
	ft_putstr_fd(STX_ERR, STDERR_FILENO);
	if (type == in_redir || type == in_here_doc)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (type == out_redir || type == out_append)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (type == pope)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (type == 0)
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd(STX_ERR_END, STDERR_FILENO);
}
