/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:34:55 by blebas            #+#    #+#             */
/*   Updated: 2024/05/03 13:23:28 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_signal = 0;

void	sigint_handler(int sig)
{
	g_last_signal = sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler_incmd(int sig)
{
	g_last_signal = sig;
}

void	sig_handler_inheredoc(int sig)
{
	g_last_signal = sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
}
