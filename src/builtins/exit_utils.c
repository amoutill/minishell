/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:25:30 by blebas            #+#    #+#             */
/*   Updated: 2024/05/02 21:32:35 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pos_long_long(char *nptr)
{
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	i = 0;
	while ((nptr[start] >= 9 && nptr[start] <= 13) || nptr[start] == ' ')
		++start;
	if (nptr[start] == '+')
		++start;
	end = start;
	while (nptr[end] >= '0' && nptr[end] <= '9')
		++end;
	while (nptr[end + i])
	{
		if (((nptr[end + i] < 9 || nptr[end + i] > 13)) && nptr[end + i] != ' ')
			return (0);
		++i;
	}
	if ((end - start) == 0 || (end - start) > 19 || ((end - start) == 19
			&& ft_strncmp(&nptr[start], "9223372036854775807", 19) > 0))
		return (0);
	return (1);
}

int	is_neg_long_long(char *nptr)
{
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	i = 0;
	while ((nptr[start] >= 9 && nptr[start] <= 13) || nptr[start] == ' ')
		++start;
	if (nptr[start] != '-')
		return (0);
	++start;
	end = start;
	while (nptr[end] >= '0' && nptr[end] <= '9')
		++end;
	while (nptr[end + i])
	{
		if (((nptr[end + i] < 9 || nptr[end + i] > 13)) && nptr[end + i] != ' ')
			return (0);
		++i;
	}
	if ((end - start) == 0 || (end - start) > 19 || ((end - start) == 19
			&& ft_strncmp(&nptr[start], "9223372036854775808", 19) > 0))
		return (0);
	return (1);
}
