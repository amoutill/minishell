/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:18:49 by amoutill          #+#    #+#             */
/*   Updated: 2024/04/18 16:13:36 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer_spec(t_env *env, t_token **tklst, char **cmdline)
{
	++(*cmdline);
	if (*(*cmdline - 1) == '\'')
		parse_squote(tklst, cmdline);
	else if (*(*cmdline - 1) == '\"')
		parse_dquote(env, tklst, cmdline);
	else if (*(*cmdline - 1) == '$')
		parse_envar(env, tklst, cmdline);
	else if (*(*cmdline - 1) == '>')
	{
		if (**cmdline == '>')
			parse_out_append(tklst, cmdline);
		else
			parse_out_redir(tklst, cmdline);
	}
	else if (*(*cmdline - 1) == '<')
	{
		if (**cmdline == '<')
			parse_in_here_doc(tklst, cmdline);
		else
			parse_in_redir(tklst, cmdline);
	}
	else if (*(*cmdline - 1) == '|')
		parse_pipe(tklst, cmdline);
}

void	tokenizer_err_nl(t_token *tklst)
{
	tklst->err = 1;
	print_stx_err(0);
}

t_token	*magic_tokenizer(t_env *env, char *cmdline)
{
	t_token	*tklst;

	tklst = NULL;
	while (*cmdline && (!tklst || !tklst->err))
	{
		while (ft_isspace(*cmdline))
			++cmdline;
		while (*cmdline && !ft_isspace(*cmdline) && (!tklst || !tklst->err))
		{
			if (is_spec_char(*cmdline))
				tokenizer_spec(env, &tklst, &cmdline);
			else
			{
				if (!tklst || get_last_tk(tklst)->stop)
					tklst_addd(&tklst, word);
				tk_add_char(tklst, *cmdline);
				++cmdline;
			}
			if (is_token_end(*cmdline) && tklst)
				get_last_tk(tklst)->stop = 1;
		}
	}
	if (tklst && !tklst->err && get_last_tk(tklst)->type)
		tokenizer_err_nl(tklst);
	return (tklst);
}
