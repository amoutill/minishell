/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:38:15 by blebas            #+#    #+#             */
/*   Updated: 2024/04/05 16:20:07 by amoutill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char const *envp[])
{
	char	*str;
	t_token	*tklst;
	t_cmd	*cmd;
	t_env	*env;

	(void)argv;
	(void)argc;
	env = init_env(envp);
	print_env(env);
	while (1)
	{
		str = readline("minishell $ ");
		tklst = magic_tokenizer(str);
		cmd = init_cmd(tklst);
		exec_cmd(cmd);
		free(str);
	}
}