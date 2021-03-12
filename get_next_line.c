/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:37:31 by lpinheir          #+#    #+#             */
/*   Updated: 2021/03/12 16:13:06 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void			ft_bzero(void *s, size_t n)
{
	unsigned char	*news;

	news = (unsigned char *)s;
	while (n > 0)
	{
		*news = 0;
		news++;
		n--;
	}
}

static char			*ft_strchr(const char *s, int c)
{
	char	target;
	int		len;

	target = (char)c;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (*s == target && target == '\0')
			return ((char *)s);
		if (*s == target)
			return ((char *)s);
		if (*s == '\0')
			return (0);
		s++;
	}
	return (0);
}

static size_t		find_break(char *buff, char **line)
{
	int		str_len;
	char	*ltemp;
	char	*overflow;

	str_len = 0;
	if (buff[0] == '\0')
	{
		*line = ft_strdup("");
		return (0);
	}
	if ((overflow = ft_strchr(buff, 10)) == NULL)
		return (0);
	while (buff[str_len] != '\0' && buff[str_len] != '\n')
		str_len++;
	if (buff[0] == '\n')
		*line = ft_strdup("");
	else
	{
		ltemp = ft_substr(buff, 0, str_len);
		*line = ltemp;
	}
	ft_bzero(buff, str_len);
	ft_strlcpy(buff, overflow + 1, ft_strlen(overflow));
	return (1);
}

int					get_next_line(int fd, char **line)
{
	char		*buffer;
	char		*temp;
	static char	*storage[OPEN_MAX];
	int			len_read;

	if (BUFFER_SIZE < 1 || !line || fd < 0 || fd > OPEN_MAX)
		return (-1);
	if (!(storage[fd]))
		if (!(storage[fd] = ft_strdup("")))
			return (-1);
	if (!(buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1)))
		return (-1);
	while ((len_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[len_read] = '\0';
		temp = ft_strjoin(storage[fd], buffer);
		free(storage[fd]);
		storage[fd] = temp;
		if ((find_break(storage[fd], line)) == 1)
			return (1);
	}
	free(buffer);
	if (len_read < 0)
	{
		free(storage[fd]);
		return (-1);
	}
	else if ((find_break(storage[fd], line)) == 1)
		return (1);
	if (ft_strlen(storage[fd]) > 0)
		*line = ft_strdup(storage[fd]);
	free(storage[fd]);
	return (0);
}
