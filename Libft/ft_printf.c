/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:03:11 by blebas            #+#    #+#             */
/*   Updated: 2023/11/04 12:03:16 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(va_list args, const char format)
{
	int	size;

	size = 0;
	if (format == 'c')
		size += ft_printchar(va_arg(args, int));
	else if (format == 's')
		size += ft_printstr(va_arg(args, char *));
	else if (format == 'i' || format == 'd')
		size += ft_putint(va_arg(args, int));
	else if (format == 'u')
		size += ft_putu(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		size += ft_puthex(va_arg(args, unsigned int), format);
	else if (format == 'p')
		size += ft_putptr(va_arg(args, void *));
	else if (format == '%')
		size += ft_putpercent();
	return (size);
}

int	ft_printf(const char *str, ...)
{
	int		size;
	int		i;
	va_list	args;

	size = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			size += ft_format(args, str[i + 1]);
			i++;
		}
		else
			size += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (size);
}
