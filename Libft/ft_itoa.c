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

#include <stdio.h>
#include <stdlib.h>
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

char	*ft_itoa(int n)
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
/*int main() {
    int num = 2147483647;
    char *result = ft_itoa(num);
    if (result != NULL) {
        printf("Integer: %d\n", num);
        printf("String: %s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}*/
