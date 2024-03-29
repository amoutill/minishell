/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:38:45 by blebas            #+#    #+#             */
/*   Updated: 2023/10/16 16:02:33 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	int	wc;
	int	i;

	i = 0;
	wc = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			wc++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (wc);
}

static void	*ft_alloctab(char const *s, char **str_tab, char c)
{
	int	i;
	int	wl;

	i = 0;
	while (s[i])
	{
		wl = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			wl++;
			i++;
		}
		if (wl != 0)
			*str_tab++ = (char *)malloc(sizeof(char) * (wl + 1));
		if (!(str_tab - 1))
			return (NULL);
	}
	return (*str_tab);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		wc;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	wc = ft_wordcount(s, c);
	res = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!res)
		return (NULL);
	ft_alloctab(s, res, c);
	while (i != wc)
	{
		j = 0;
		while (s[k] == c && s[k] != '\0')
			k++;
		while (s[k] != c && s[k] != '\0')
			res[i][j++] = s[k++];
		res[i][j] = '\0';
		i++;
	}
	res[i] = NULL;
	return (res);
}

/*void free_strarray(char **arr) {
    if (arr == NULL)
        return;

    int i = 0;
    while (arr[i] != NULL) {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int main() {
    const char *str = "*je**vais****caner*";
    char **result = ft_strsplit(str, '*');

    if (result) {
        printf("Original String: \"%s\"\n", str);
        printf("Split Strings:\n");
        for (int i = 0; result[i] != NULL; i++) {
            printf("%s\n", result[i]);
        }

        // Libération de la mémoire allouée
        free_strarray(result);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
} */
