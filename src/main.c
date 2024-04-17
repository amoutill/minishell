/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:38:15 by blebas            #+#    #+#             */
/*   Updated: 2024/04/17 18:28:35 by amoutill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	main(int argc, char const *argv[], char const *envp[])
{
	char	*str;
	t_token	*tklst;
	t_cmd	*cmd;
	t_env	*env;

	(void)argv;
	(void)argc;
	env = init_env(envp);
	while (1)
	{
		str = readline("\e[1;36mminishell $\e[0m ");
		if (!str)
			exit(EXIT_SUCCESS);
		add_history(str);
		tklst = magic_tokenizer(env, str);
		free(str);
		print_tktlst(tklst);
		if (tklst)
		{
			cmd = init_cmd(tklst);
			exec_cmd(cmd, env);
		}
	}
}
