/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:26:26 by blebas            #+#    #+#             */
/*   Updated: 2023/11/13 16:51:08 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}

char	*read_and_stash(int fd, char *stash)
{
	char	*buff;
	int		count_read;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	count_read = 1;
	while (!ft_strchr_gnl(stash, '\n') && count_read != 0)
	{
		count_read = read(fd, buff, BUFFER_SIZE);
		if (count_read == -1)
		{
			free(stash);
			free(buff);
			return (NULL);
		}
		buff[count_read] = '\0';
		stash = ft_strjoin_gnl(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*extract_line(char *stash)
{
	int		i;
	char	*s;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	s = (char *)malloc(sizeof(char) * i + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		s[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*update_stash(char *stash)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen_gnl(stash) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		s[j++] = stash[i++];
	s[j] = '\0';
	free(stash);
	return (s);
}
