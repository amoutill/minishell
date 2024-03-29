/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:00:32 by blebas            #+#    #+#             */
/*   Updated: 2023/10/16 16:04:28 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ft_value(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

char	*ft_itoa_pf(int n)
{
	long int	nb;
	char		*dst;
	int			size;

	nb = n;
	size = ft_size(nb);
	dst = (char *)malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (NULL);
	dst[size] = '\0';
	if (nb < 0)
		dst[0] = '-';
	else if (nb == 0)
		dst[0] = '0';
	while (nb != 0)
	{
		size--;
		dst[size] = ft_value(nb % 10) + '0';
		nb = nb / 10;
	}
	return (dst);
}

static int	ft_sizeu(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_unsigneditoa(unsigned int n)
{
	char	*dst;
	int		size;

	size = ft_sizeu(n);
	dst = (char *)malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (NULL);
	dst[size] = '\0';
	while (n != 0)
	{
		size--;
		dst[size] = (n % 10) + '0';
		n = n / 10;
	}
	return (dst);
}
