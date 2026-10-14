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

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	if (!buffer)
		return (ft_strjoin("", buf));
	if (!buf)
		return (buffer);
	temp = ft_strjoin(buffer, buf);
	free(buffer);
	free(buf);
	return (temp);
}

char	*ft_next(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	new_buffer = ft_calloc(ft_strlen(buffer + i) + 1, sizeof(char));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	free(buffer);
	return (new_buffer);
}

char	*ft_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	char	*temp;
	ssize_t	byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	while (1)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
		{
			free(res);
			return (NULL);
		}
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			free(res);
			return (NULL);
		}
		if (byte_read == 0)
		{
			free(buffer);
			break ;
		}
		buffer[byte_read] = '\0';
		temp = ft_free(res, buffer);
		if (!temp)
		{
			free(res);
			return (NULL);
		}
		res = temp;
		if (ft_strchr(res, '\n'))
			break ;
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(1, 1);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	if (!buffer[0])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}
