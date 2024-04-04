/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:38:15 by blebas            #+#    #+#             */
/*   Updated: 2024/03/28 13:38:26 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[])
{
	char	*str;
	t_token	*tklst;
	t_cmd	*cmd;
	(void)argv;
	(void)argc;

	while (1)
	{
		str = readline("minishell $ ");
		tklst = magic_tokenizer(str);
		cmd = init_cmd(tklst);
		exec_cmd(cmd);
		free(str);
	}
}
