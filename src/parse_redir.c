/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:09:22 by blebas            #+#    #+#             */
/*   Updated: 2024/04/17 18:00:33 by amoutill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_out_redir(t_token **tklst, char **cmdline)
{
	ft_skip_spaces(cmdline);
	tklst_addd(tklst, out_redir);
	++(*cmdline);
}

void	parse_out_append(t_token **tklst, char **cmdline)
{
	++(*cmdline);
	ft_skip_spaces(cmdline);
	tklst_addd(tklst, out_append);
	++(*cmdline);
}

void	parse_in_redir(t_token **tklst, char **cmdline)
{
	ft_skip_spaces(cmdline);
	tklst_addd(tklst, in_redir);
	++(*cmdline);
}

void	parse_in_here_doc(t_token **tklst, char **cmdline)
{
	++(*cmdline);
	ft_skip_spaces(cmdline);
	tklst_addd(tklst, in_here_doc);
	++(*cmdline);
}

void	parse_pipe(t_token **tklst, char **cmdline)
{
	ft_skip_spaces(cmdline);
	tklst_addd(tklst, pope);
	if (*tklst)
		get_last_tk(*tklst)->stop = 1;
	++(*cmdline);
}
