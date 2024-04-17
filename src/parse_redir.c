/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:09:22 by blebas            #+#    #+#             */
/*   Updated: 2024/04/17 15:50:01 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_out_redir(t_token **tklst, char **str)
{
	ft_skip_spaces(str);
	tklst_addd(tklst, out_redir);
	++str;
}

void	parse_out_append(t_token **tklst, char **str)
{
	ft_skip_spaces(str);
	tklst_addd(tklst, out_append);
	++str;
}

void	parse_in_redir(t_token **tklst, char **str)
{
	ft_skip_spaces(str);
	tklst_addd(tklst, in_redir);
	++str;
}

void	parse_in_here_doc(t_token **tklst, char **str)
{
	ft_skip_spaces(str);
	tklst_addd(tklst, in_here_doc);
	++str;
}
