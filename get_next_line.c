/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:37:31 by lpinheir          #+#    #+#             */
/*   Updated: 2021/03/01 10:05:48 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strjoin.c"

// gnl prints overflow correctly but doesn't process it 
/*
size_t	find_brea2(char *buff, size_t original_len, char *storage)
{
	size_t 	str_len;
	char	*temp;
	char	*buff_n_stor;
	int	counter;

	counter = 1;
	str_len = 0;
	buff_n_stor = 
}
*/
size_t	find_break(char *buff, size_t original_len, char *storage)
{
	size_t	str_len;
	char	*ltemp;
	
	str_len = 0;
	while (original_len >= 0)
	{
		if (*buff == '\n')
		{
			if (str_len != 0)
			{
				ltemp = malloc(sizeof(char) * str_len + 1);
				strlcpy(ltemp, buff - (str_len), str_len + 1);
				printf("\nLINE:\n(%s)\n", ltemp);
				free(ltemp);
				str_len = 0;
			}
		}
		if (*buff == '\0')
		{
			strlcpy(storage, buff - (str_len), str_len + 1);
			return (0);	
		}
		str_len++;
		buff++;
		original_len--;
	}
	printf("end of find break");
	return (0);
}


int	get_next_line(int fd)
{	
	char		*buffer;
	char		*temp;
	static char	*storage;
	size_t		size; // futuro BUFFER_SIZE
	size_t		len_read; // o quanto leu do arquivo com base em size

	size = 22; // temporary size
	if (storage == 0)
	{
		storage = strdup("");
	}
	if (!(buffer = malloc(sizeof(char*) * size + 1)))
		return (-1);
	if ((len_read = read(fd, buffer, size)) > 0)
	{
		buffer[len_read] = '\0';	
		temp = ft_strjoin(storage, buffer);
		while (find_break(temp, strlen(temp), storage) != 0)
			;
		return (1);
	}
	return (0);
}
