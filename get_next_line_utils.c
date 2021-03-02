/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:55:27 by lpinheir          #+#    #+#             */
/*   Updated: 2021/03/02 18:23:52 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++ != 0)
		len++;
	return (len);
}

size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	counter;

	if (!src)
		return (0);
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	counter = 0;
	while (*src != 0 && counter < (dstsize - 1))
	{
		*dst = *src;
		src++;
		dst++;
		counter++;
	}
	*dst = 0;
	return (srclen);
}

char			*ft_strchr(const char *s, int c)
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

static size_t	ft_trimindex(const char *s1, const char *set, int start)
{
	size_t	i;

	if (start == 1)
	{
		i = 0;
		while (s1[i] != 0)
		{
			if (ft_strchr(set, s1[i]) == 0)
				break ;
			i++;
		}
		return (i);
	}
	if (ft_strlen(s1) == 0)
		return (0);
	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i--;
	}
	return (i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	start_i;
	size_t	end_i;
	char	*emptystr;
	char	*buffer;

	if (!s1)
		return (NULL);
	start_i = ft_trimindex(s1, set, 1);
	end_i = ft_trimindex(s1, set, 0);
	if (start_i > end_i)
	{
		emptystr = (char *)malloc(sizeof(char*) * 2);
		ft_strlcpy(emptystr, "", 2);
		return (emptystr);
	}
	buffer = (char *)malloc(sizeof(char) * (end_i - start_i + 2));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, s1 + start_i, end_i - start_i + 2);
	return (buffer);
}
