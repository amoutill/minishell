/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:58:47 by blebas            #+#    #+#             */
/*   Updated: 2024/04/17 19:07:37 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tklst(t_token *tklst)
{
	if (tklst)
	{
		free_tklst(tklst->next);
		free(tklst->str);
		free(tklst);
	}
}
