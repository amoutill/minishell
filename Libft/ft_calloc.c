/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:09:20 by blebas            #+#    #+#             */
/*   Updated: 2023/10/17 12:26:09 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned int	i;
	char			*dst;

	dst = malloc(nmemb * size);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		dst[i] = 0;
		i++;
	}
	return (dst);
}
