/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:37:31 by lpinheir          #+#    #+#             */
/*   Updated: 2021/03/12 00:02:49 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

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

/*
static size_t		last_chance(char *buff, char **line)
{
	char	*ltemp;

	ltemp = ft_strdup(buff);
	*line = ltemp;
	bzero(buff, ft_strlen(buff));
	return (1);
}
*/


static size_t		find_break(char *buff, char **line, int len_read)
{
	int	str_len;
	int	i;
	char	*ltemp;
	char	*overflow;

	i = 0;
	str_len = 0;
//	printf("FIND_BREAK START\n");
//	printf("Buff is %c\n", buff[0]);
//	printf("Buff len_read is %d\n", len_read);
	while (buff[str_len] != '\0' && buff[str_len] != '\n')
		str_len++;
	if (len_read == 0 && buff[str_len] == '\0' && ft_strlen(buff) > 0)
	{		
		ltemp = ft_strdup(buff);
		*line = ltemp;
		bzero(buff, ft_strlen(buff));
//		printf("ENTRAMOS\n");
		return (1);
	}
	else if (buff[0] == '\0')
	{
		*line = ft_strdup("");
		//printf("FB: BUFF '\\0', Return (0)\n");
		return (0);
	}
	if ((overflow = strchr(buff, 10)) == NULL)
	{ 
		//printf("FB: NO '\\n' in Buffer, Return (0)\n");
		return (0);
	}
	if (buff[0] == '\n')
	{
		//printf("FB: buff[0] is '\\n line - dup()\n");
		*line = ft_strdup("");
	}
	else
	{
		//printf("FB: line points to ltemp. str_len is %d\n", str_len);
		ltemp = ft_substr(buff, 0, str_len);
		*line = ltemp;
	}
	bzero(buff, str_len);
	//printf("FB: Storage zeroed\n");
	ft_strlcpy(buff, overflow + 1, ft_strlen(overflow));
	//printf("FB: Overflow copied to storage\n");
	//printf("FIND_BREAK ENDS, Return (1)\n");
	return (1);
}

int					get_next_line(int fd, char **line)
{
	char		*buffer;
	char		*temp;
	static char	*storage[OPEN_MAX];
	int		len_read;
	
	if (BUFFER_SIZE < 1 || !line || fd < 0 || fd > OPEN_MAX)
	{
	//	printf("Return -1 (BFSize, Line, Fd or OpenMax)\n");
		return (-1);
	}
	if (!(storage[fd]))
	{
	//	printf("Malloc(ed) Storage[%d]\n", fd);
		if (!(storage[fd] = ft_strdup("")))
		{	
	//		printf("Return -1 (Storage Alloc)\n");
			return (-1);
		}
	}
	if (!(buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1)))
		return (-1);
	//printf("Malloc(ed) Buffer\n");
	while ((len_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
	//	printf("GNL: Found stuff to read\n");
		buffer[len_read] = '\0';
		temp = joinstr(storage[fd], buffer);
		free(storage[fd]);
		storage[fd] = temp;
		if ((find_break(storage[fd], line, len_read)) == 1)
		{
			free(buffer);
		//	printf("GNL: Found Break in Read, Buffer Freed, Return 1\n");
			return (1);
		}
	}
	if (len_read < 0)
	{
		printf("len_read < 0, Return -1\n");
		return (-1);
	}
	//printf("NOTHING TO READ, reading from storage\n");
	temp = joinstr("", storage[fd]);
	free(storage[fd]);
	storage[fd] = temp;
	if ((find_break(storage[fd], line, len_read)) == 1)
	{
		free(buffer);
		printf("GNL storage len is %zu\n", ft_strlen(storage[fd]));
		if (ft_strlen(storage[fd]) == 0)
			return (0);
//		printf("Found Break in Read, Buffer Freed, Return 1\n");
		return (1);
	}
	/*
	if (ft_strlen(storage[fd]) > 0)
	{	
		free(buffer);
		printf("LAST CHANGE\n");
		return (last_chance(storage[fd], line));
	}
	*/
	free(storage[fd]);
	free(buffer);
//	printf("Found nothing in storage, Buffer + Storage Freed, END (0)\n");
	return (0);
}
