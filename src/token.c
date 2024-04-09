/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:13:24 by blebas            #+#    #+#             */
/*   Updated: 2024/04/09 16:39:54 by amoutill         ###   ########.fr       */
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

void	tklst_addd(t_token **tklst, char *str, t_tktype type)
{
	t_token	*ptr;

	if (!*tklst)
	{
		*tklst = malloc(sizeof(t_token));
		(*tklst)->str = ft_strdup(str);
		(*tklst)->type = type;
		(*tklst)->next = NULL;
		return ;
	}
	ptr = *tklst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = malloc(sizeof(t_token));
	ptr->next->str = ft_strdup(str);
	ptr->next->type = type;
	ptr->next->next = NULL;
}

void	tk_add_char(t_token *tklst, char c)
{
	char	*buf;
	size_t	len;

	//len = 0;
	while (tklst->next)
		tklst = tklst->next;
	//if (!tklst->str)
	//	tklst->str = malloc(sizeof(char) * 2);
	//else
	//{
	buf = tklst->str;
	len = ft_strlen(buf);
	tklst->str = malloc(sizeof(char) * (len + 2));
	ft_strlcpy(tklst->str, buf, -1);
	//}
	tklst->str[len + 0] = c;
	tklst->str[len + 1] = '\0';
}

t_token	*magic_tokenizer(char *str)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*boeuf;
	t_token	*tklst;

	tklst = NULL;
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		while (isspace(str[i]))
			++i;
		start = i;
		while (str[i] && !isspace(str[i]))
			++i;
		end = i;
		boeuf = malloc(sizeof(char) * (end - start + 1));
		ft_strlcpy(boeuf, &str[start], end - start + 1);
		tklst_addd(&tklst, boeuf, word);
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
