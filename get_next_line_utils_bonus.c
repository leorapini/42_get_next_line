/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:55:27 by lpinheir          #+#    #+#             */
/*   Updated: 2021/03/16 14:14:13 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t			ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++ != 0)
		len++;
	return (len);
}

char			*ft_strdup(const char *s1)
{
	char	*buffer;
	int		len;

	len = ft_strlen(s1);
	buffer = (char *)malloc(sizeof(*s1) * (len + 1));
	if (buffer == NULL)
		return (NULL);
	ft_strlcpy(buffer, s1, len + 1);
	return (buffer);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buffer;
	int		i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	buffer = (char *)malloc(sizeof(*s) * (len + 1));
	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (len > 0)
	{
		buffer[i] = s[start];
		i++;
		start++;
		len--;
	}
	buffer[i] = 0;
	return (buffer);
}

char			*ft_strjoin(char const *s1, char const *s2)
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
