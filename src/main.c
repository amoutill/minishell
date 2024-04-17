/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:38:15 by blebas            #+#    #+#             */
/*   Updated: 2024/04/17 19:13:23 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	main(int argc, char const *argv[], char const *envp[])
{
	char	*cmdline;
	t_token	*tklst;
	t_cmd	*cmd;
	t_env	*env;

	(void)argv;
	(void)argc;
	env = init_env(envp);
	while (1)
	{
		cmdline = readline("\e[1;36mminishell $\e[0m ");
		if (!cmdline)
			break ;
		add_history(cmdline);
		tklst = magic_tokenizer(env, cmdline);
		free(cmdline);
		print_tktlst(tklst);
		if (tklst)
		{
			cmd = init_cmd(tklst);
			exec_cmd(cmd, env);
			free_tklst(tklst);
			free_cmd(cmd);
		}
	}
	free_env(env);
	rl_clear_history();
}
