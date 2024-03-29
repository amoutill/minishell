/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:04:01 by blebas            #+#    #+#             */
/*   Updated: 2023/11/04 12:07:18 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_baseseize(unsigned long nb, char *base)
{
	if (nb / 16)
		ft_baseseize(nb / 16, base);
	ft_putchar_pf(base[nb % 16]);
}

static int	ft_sizehex(unsigned long nb)
{
	int	size;

	size = 0;
	while (nb != 0)
	{
		size++;
		nb /= 16;
	}
	return (size);
}

int	ft_puthex(unsigned int nb, char format)
{
	char	*base;

	if (format != 'x' && format != 'X')
		return (0);
	if (nb == 0)
		return (write(1, "0", 1));
	base = "0123456789abcdef";
	if (format == 'X')
		base = "0123456789ABCDEF";
	ft_baseseize(nb, base);
	return (ft_sizehex(nb));
}

int	ft_putptr(void *ptr)
{
	unsigned long	addptr;

	addptr = (unsigned long) ptr;
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	ft_putstr_pf("0x");
	ft_baseseize(addptr, "0123456789abcdef");
	return (ft_sizehex(addptr) + 2);
}
