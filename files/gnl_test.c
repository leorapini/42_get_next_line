/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:37:31 by lpinheir          #+#    #+#             */
/*   Updated: 2021/03/09 11:15:31 by lpinheir         ###   ########.fr       */
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

static size_t		find_line(char *buff, char **line)
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
			if (!(overflow = malloc(sizeof(char) * ft_strlen(buff) + 1)))
				return (-1);
			ft_strlcpy(overflow, buff, ft_strlen(buff) + 1);
			ft_strlcpy(buff - str_len, overflow, ft_strlen(buff) + 1);
			return (1);
		}
		str_len++;
		buff++;
	}
	return (0);
}

static int	is_there_stuff(int fd, char *buffer, char **line)
{
	size_t	len_read;
	char	*temp;
	static char	*storage[OPEN_MAX];

	if (!(storage[fd]))
		storage[fd] = ft_strdup("");
	while ((len_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		printf("\nREAD: buffer is (%s)\n", buffer);
		buffer[len_read] = '\0';
		temp = joinstr(storage[fd], buffer);
		storage[fd] = temp;
		printf("\nREAD: storage is (%s)\n", storage[fd]);
		find_line(storage[fd], line);
		return (1);
	}
	printf("\nSTOR len is %zu\n", ft_strlen(storage[fd]));	
	if (ft_strlen(storage[fd]) > 1)
	{
		printf("\nSTOR len is %zu\n", ft_strlen(storage[fd]));
		temp = joinstr("", storage[fd]);
		storage[fd] = temp;
		printf("\nSTOR: storage is (%s)\n", storage[fd]);
		find_line(storage[fd], line);
		return (1);
	}
	return (0);

}


int					get_next_line(int fd, char **line)
{
	char		*buffer;

	if (BUFFER_SIZE < 1 || !line || fd < 0)
		return (-1);
	if (!(buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1)))
		return (-1);
	if (is_there_stuff(fd, buffer, line) == 1)
		return (1);
	return (0);
}
