/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:13:24 by blebas            #+#    #+#             */
/*   Updated: 2024/04/18 16:31:41 by blebas           ###   ########.fr       */
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
		return ;
	}
	ptr = *tklst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = ft_calloc(1, sizeof(t_token));
	ptr->next->type = type;
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
	while (tklst != NULL && tklst->type == word)
	{
		cmd->argv[j] = ft_strdup(tklst->str);
		tklst = tklst->next;
		j++;
	}
	cmd->argv[j] = NULL;
	return (cmd);
}
