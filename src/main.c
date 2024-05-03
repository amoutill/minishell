/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:38:15 by blebas            #+#    #+#             */
/*   Updated: 2024/05/03 13:52:19 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

extern int	g_last_signal;

void	free_stuff(t_exec *exec_data)
{
	free_env(exec_data->env);
	rl_clear_history();
}

void	parse(char *cmdline, t_exec *exec_data)
{
	if (cmdline[0])
		add_history(cmdline);
	exec_data->tklst = magic_tokenizer(exec_data->env, cmdline);
	exec_data->current_tk = exec_data->tklst;
	free(cmdline);
}

void	if_signaled(t_exec *exec_data)
{
	if (g_last_signal)
	{
		set_env(exec_data->env, "?", "130");
		g_last_signal = 0;
	}
}

void	init_main(t_exec *exec_data)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	exec_data->env = init_env(__environ);
}

int	main(void)
{
	char	*cmdline;
	int		retval;
	t_exec	exec_data;

	init_main(&exec_data);
	while (1)
	{
		cmdline = readline("\e[1;36mminishell $\e[0m ");
		if_signaled(&exec_data);
		if (!cmdline)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		parse(cmdline, &exec_data);
		if (exec_data.tklst)
		{
			if (!exec_data.tklst->err)
				retval = exec_in_main(&exec_data);
			else
				set_env(exec_data.env, "?", "2");
			free_tklst(exec_data.tklst);
		}
	}
	free_stuff(&exec_data);
}
