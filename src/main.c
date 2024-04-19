/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:38:15 by blebas            #+#    #+#             */
/*   Updated: 2024/04/19 16:47:41 by blebas           ###   ########.fr       */
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
		//print_tktlst(tklst);
		//print_str_tab(init_envp(env));
		if (tklst)
		{
			if (!tklst->err)
			{
				cmd = init_cmd(tklst);
				printf("cmd: %s\n", ft_which(env, cmd->argv[0]));
				//exec_cmd(cmd, env);
				exec(cmd, env);
				free_cmd(cmd);
			}
			free_tklst(tklst);
		}
	}
	free_env(env);
	rl_clear_history();
}
