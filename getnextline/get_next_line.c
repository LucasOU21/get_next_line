/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luolivei <luolivei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 18:02:31 by luolivei          #+#    #+#             */
/*   Updated: 2026/09/23 18:58:07 by luolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_next(char *stash)
{
	char	*remainder;
	size_t	nl;

	nl = 0;
	while (stash[nl] && stash[nl] != '\n')
		nl++;
	if (!stash[nl])
	{
		free(stash);
		return (NULL);
	}
	remainder = ft_strjoin(stash + nl + 1, NULL);
	free(stash);
	return (remainder);
}

static char	*ft_line(char *stash)
{
	char	*line;
	size_t	len;

	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	line[len] = '\0';
	while (len--)
		line[len] = stash[len];
	return (line);
}

static char	*read_file(int fd, char *stash)
{
	char	*chunk;
	char	*joined;
	ssize_t	bytes_read;

	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
	{
		free(stash);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		chunk[bytes_read] = '\0';
		joined = ft_strjoin(stash, chunk);
		free(stash);
		stash = joined;
		if (!stash)
			break ;
	}
	free(chunk);
	if (bytes_read < 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_line(stash);
	if (line)
		stash = ft_next(stash);
	else
	{
		free(stash);
		stash = NULL;
	}
	return (line);
}
