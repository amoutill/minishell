/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:03:41 by blebas            #+#    #+#             */
/*   Updated: 2023/11/04 12:08:03 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putint(int nb)
{
	int		size;
	char	*temp;

	temp = ft_itoa_pf(nb);
	size = ft_printstr(temp);
	free(temp);
	return (size);
}

int	ft_putu(unsigned int nb)
{
	int		size;
	char	*temp;

	size = 0;
	if (nb == 0)
		size += write(1, "0", 1);
	else
	{
		temp = ft_unsigneditoa(nb);
		size = ft_printstr(temp);
		free(temp);
	}
	return (size);
}
