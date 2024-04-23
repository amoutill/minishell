/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:38:15 by blebas            #+#    #+#             */
/*   Updated: 2024/04/23 15:08:46 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	main(int argc, char const *argv[], char const *envp[])
{
	char	*cmdline;
	int		retval;
	char	*retval_str;
	t_token	*tklst;
	t_cmd	*cmd;
	t_env	*env;

	(void)argv;
	(void)argc;
	env = init_env(envp);
	set_env(env, "?", "0");
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
				retval = exec(cmd, env);
				free_cmd(cmd);
				retval_str = ft_itoa(retval);
				set_env(env, "?", retval_str);
				free(retval_str);
			}
			free_tklst(tklst);
		}
	}
	free_env(env);
	rl_clear_history();
}
