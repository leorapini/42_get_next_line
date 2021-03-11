/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:37:31 by lpinheir          #+#    #+#             */
/*   Updated: 2021/03/10 02:29:56 by lpinheir         ###   ########.fr       */
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
	static int	str_len;
	char	*ltemp;
	char	*overflow;

	str_len = 0;
	while (*buff != '\0')
	{
		if (*buff == '\n')
		{
			if (!(ltemp = malloc(sizeof(char) * str_len + 1)))
				return (-1);
			ft_strlcpy(ltemp, buff - str_len, str_len + 1);
			//printf("ltemp (%s)\n", ltemp);
			*line = ft_strdup(ltemp); //ft_strtrim(ltemp, "\n");
			free(ltemp);
			if (!(overflow = malloc(sizeof(char) * ft_strlen(buff) + 1)))
				return (-1);
			ft_strlcpy(overflow, buff, ft_strlen(buff) + 1);
			ft_strlcpy(buff - str_len, overflow, ft_strlen(buff) + 1);
			free(overflow);
			str_len = -1;
			return (1);
		}
		str_len++;
		buff++;
	}
	//printf("fim find_break\n");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	char		*buffer;
	char		*temp;
	static char	*storage[OPEN_MAX];
	int		len_read;

	if (BUFFER_SIZE < 1 || !line || fd < 0 || fd > OPEN_MAX)
	{
		//printf("Return -1\n");
		return (-1);
	}
	if (!(storage[fd]))
	{
		if (!(storage[fd] = ft_strdup("")))
			return (-1);
	}
	if (!(buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1)))
		return (-1);
	while ((len_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[len_read] = '\0';
		temp = joinstr(storage[fd], buffer);
		free(storage[fd]);
		storage[fd] = temp;
		if ((find_break(storage[fd], line)) == 1)
		{
			free(buffer);
			//printf("Return 1\n");
			return (1);
		}
	}
	if (len_read < 0)
	{
		//printf("Return -1\n");
		return (-1);
	}
	temp = joinstr("", storage[fd]);
	free(storage[fd]);
	storage[fd] = temp;
	if ((find_break(storage[fd], line)) == 1)
	{
		free(buffer);
		return (1);
	}
	free(storage[fd]);
	free(buffer);
	//printf("Return 0 END\n");
	return (0);
}
