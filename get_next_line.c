/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:37:31 by lpinheir          #+#    #+#             */
/*   Updated: 2021/02/25 14:39:37 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

size_t	len_until_break(char *buff, size_t original_len)
{
	size_t	i;
	
	i = 0;
	while (*buff != '\n' && *buff != '\0' && buff != 0 && original_len > 0)
	{
		original_len--;
		i++;
		buff++;
	}
	return (i);
}

char	*get_next_break(char *buff)
{
	while (*buff == '\n')
		buff++;
	while (*buff != '\n' && *buff != 0)
		buff++;
	buff++;
	return (buff);
}

int	get_next_line(int fd, char **line)
{	
	char 	*buffer;
	static char	*temp;
	size_t	size; // futuro BUFFER_SIZE
	size_t	len_read; // o quanto leu do arquivo com base em size
	size_t	len_til_break;	

	size = 200;
	if (!(buffer = malloc(sizeof(char*) * size + 1)))
		return (0);
	if ((len_read = read(fd, buffer, size)) > 0)
	{
		buffer[len_read] = '\0';
		temp = strndup(buffer, len_read);
	}
	else
		len_read = strlen(temp);	
	len_til_break = len_until_break(temp, len_read);
	*line = strndup(temp, len_til_break);
	temp = get_next_break(temp);
	free(buffer);	
	return (1);
}
