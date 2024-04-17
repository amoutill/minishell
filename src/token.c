/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:13:24 by blebas            #+#    #+#             */
/*   Updated: 2024/04/17 16:45:32 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include "minishell.h"

size_t	tklst_len(t_token *tklst)
{
	int	i;

	i = 0;
	while (tklst != NULL)
	{
		i++;
		tklst = tklst->next;
	}
	return (i);
}

void	tklst_addd(t_token **tklst, t_tktype type)
{
	t_token	*ptr;

	if (!*tklst)
	{
		*tklst = ft_calloc(1, sizeof(t_token));
		(*tklst)->type = type;
		(*tklst)->str = ft_strdup("");
		return ;
	}
	ptr = *tklst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = ft_calloc(1, sizeof(t_token));
	ptr->next->type = type;
	ptr->next->str = ft_strdup("");
}

void	tk_add_char(t_token *tklst, char c)
{
	while (tklst->next)
		tklst = tklst->next;
	str_add_char(&(tklst->str), c);
}

t_token	*get_last_tk(t_token *tklst)
{
	while (tklst->next)
		tklst = tklst->next;
	return (tklst);
}

t_token	*magic_tokenizer(t_env *env, char *str)
{
	t_token	*tklst;

	tklst = NULL;
	if (!str)
		return (NULL);
	while (*str)
	{
		while (ft_isspace(*str))
			++str;
		while (*str && !ft_isspace(*str))
		{
			if (*str == '\'')
			{
				++str;
				parse_squote(&tklst, &str);
			}
			else if (*str == '\"')
			{
				++str;
				parse_dquote(env, &tklst, &str);
			}
			else if (*str == '$')
			{
				++str;
				parse_envar(env, &tklst, &str);
			}
			else if (*str == '>')
			{
				++str;
				if (*str == '>')
				{
					++str;
					parse_out_append(&tklst, &str);
				}
				else
					parse_out_redir(&tklst, &str);
			}
			else if (*str == '<')
			{
				++str;
				if (*str == '<')
				{
					++str;
					parse_in_here_doc(&tklst, &str);
				}
				else
					parse_in_redir(&tklst, &str);
			}
			else if (*str == '|')
			{
				++str;
				parse_pipe(&tklst, &str);
			}
			else
			{
				if (!tklst || get_last_tk(tklst)->stop)
					tklst_addd(&tklst, word);
				tk_add_char(tklst, *str);
				++str;
			}
			if (is_token_end(*str) && tklst)
				get_last_tk(tklst)->stop = 1;
		}
	}
	return (tklst);
}

t_cmd	*init_cmd(t_token *tklst)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	j = 0;
	i = tklst_len(tklst);
	cmd = malloc(sizeof(t_cmd));
	cmd->argv = malloc(sizeof(char *) * (i + 1));
	cmd->argc = i;
	while (tklst != NULL)
	{
		cmd->argv[j] = ft_strdup(tklst->str);
		tklst = tklst->next;
		j++;
	}
	cmd->argv[j] = NULL;
	return (cmd);
}
