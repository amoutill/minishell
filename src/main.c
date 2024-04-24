/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:38:15 by blebas            #+#    #+#             */
/*   Updated: 2024/04/24 19:03:06 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

extern int	g_last_signal;

int	main(int argc, char const *argv[], char const *envp[])
{
	char	*cmdline;
	int		retval;
	char	*retval_str;
	t_exec	exec_data;

	(void)argv;
	(void)argc;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	exec_data.env = init_env(envp);
	set_env(exec_data.env, "?", "0");
	while (1)
	{
		cmdline = readline("\e[1;36mminishell $\e[0m ");
		if (g_last_signal)
		{
			set_env(exec_data.env, "?", "130");
			g_last_signal = 0;
		}
		if (!cmdline)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (cmdline[0])
			add_history(cmdline);
		exec_data.tklst = magic_tokenizer(exec_data.env, cmdline);
		free(cmdline);
		//print_tktlst(tklst);
		//print_str_tab(init_envp(env));
		if (exec_data.tklst)
		{
			if (!exec_data.tklst->err)
			{
				exec_data.cmd = init_cmd(exec_data.tklst);
				signal(SIGINT, sig_handler_incmd);
				signal(SIGQUIT, sig_handler_incmd);
				retval = exec(exec_data);
				signal(SIGINT, sigint_handler);
				signal(SIGQUIT, SIG_IGN);
				free_cmd(exec_data.cmd);
				retval_str = ft_itoa(retval);
				set_env(exec_data.env, "?", retval_str);
				free(retval_str);
			}
			free_tklst(exec_data.tklst);
		}
	}
	free_env(exec_data.env);
	rl_clear_history();
}
