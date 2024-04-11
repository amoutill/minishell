/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:13:24 by blebas            #+#    #+#             */
/*   Updated: 2024/04/11 14:22:01 by blebas           ###   ########.fr       */
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
	char	*buf;
	size_t	len;

	len = 0;
	while (tklst->next)
		tklst = tklst->next;
	if (!tklst->str)
		tklst->str = malloc(sizeof(char) * 2);
	else
	{
		buf = tklst->str;
		len = ft_strlen(buf);
		tklst->str = malloc(sizeof(char) * (len + 2));
		ft_strlcpy(tklst->str, buf, -1);
	}
	tklst->str[len + 0] = c;
	tklst->str[len + 1] = '\0';
}

t_token	*magic_tokenizer(char *str)
{
	t_token	*tklst;

	tklst = NULL;
	if (!str)
		return (NULL);
	while (*str)
	{
		while (isspace(*str))
			++str;
		if (*str)
			tklst_addd(&tklst, word);
		while (*str && !is_token_end(*str))
		{
			if (*str == '\'')
			{
				++str;
				parse_squote(tklst, &str);
			}
			else if (*str == '\"')
			{
				++str;
				parse_dquote(tklst, &str);
			}
			else
				tk_add_char(tklst, *str);
			if (*str)
				++str;
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
