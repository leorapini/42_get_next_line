/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:37:31 by lpinheir          #+#    #+#             */
/*   Updated: 2021/03/03 11:08:46 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char			*joinstr(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*buffer;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	buffer = (char*)malloc(sizeof(*s1) *
			((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (buffer == NULL)
		return (NULL);
	while (s1[i] != 0)
		buffer[j++] = s1[i++];
	i = 0;
	while (s2[i] != 0)
		buffer[j++] = s2[i++];
	buffer[j] = 0;
	return (buffer);
}

static size_t		find_break(char *buff, char **line)
{
	size_t	str_len;
	char	*ltemp;
	char	*overflow;

	str_len = 0;
	while (*buff != '\0')
	{
		if (*buff == '\n' && str_len != 0)
		{
			if (!(ltemp = malloc(sizeof(char) * str_len + 1)))
				return (-1);
			ft_strlcpy(ltemp, buff - str_len, str_len + 1);
			*line = ft_strtrim(ltemp, "\n");
			free(ltemp);
			if (!(overflow = malloc(sizeof(char) * ft_strlen(buff) + 1)))
				return (-1);
			ft_strlcpy(overflow, buff, ft_strlen(buff) + 1);
			ft_strlcpy(buff - str_len, overflow, ft_strlen(buff) + 1);
			free(overflow);
			return (1);
		}
		str_len++;
		buff++;
	}
	return (0);
}

int					get_next_line(int fd, char **line)
{
	char		*buffer;
	char		*temp;
	static char	*storage[OPEN_MAX];
	size_t		len_read;

	if (BUFFER_SIZE < 1 || !line || fd < 0)
		return (-1);
	if (!(storage[fd]))
		if (!(storage[fd] = malloc(sizeof(storage) * BUFFER_SIZE)))
			return (-1);
	if (!(buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1)))
		return (-1);
	while ((len_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[len_read] = '\0';
		temp = joinstr(storage[fd], buffer);
		free(buffer);
		free(storage[fd]);
		storage[fd] = temp;
		if (find_break(storage[fd], line) == 1)
		{
		//	printf("\nSTORAGE:\n%s\n\n", storage);
			return (1);
		}
	}
	while (find_break(storage[fd], line) == 1)
	{
		free(buffer);
		return (1);
	}
	free(storage[fd]);
	free(buffer);
	return (0);
}
