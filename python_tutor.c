#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

size_t			ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++ != 0)
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s;

	i = -1;
	if (!s1 || !(s = malloc((ft_strlen(s1) + 1) * sizeof(*s))))
		return (NULL);
	while (s1[++i])
		s[i] = s1[i];
	s[i] = '\0';
	return (s);
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
	size_t		len;

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


size_t	ft_trimindex(const char *s1, const char *set, int start)
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
		emptystr = ft_strdup("");
		return (emptystr);
	}
	buffer = malloc(sizeof(*buffer) * (end_i - start_i + 2));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, s1 + start_i, end_i - start_i + 2);
	return (buffer);
}



size_t		find_break(char *buff, char **line)
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

int	main(void)
{
	char	*line;
	char	string[] = "Long string with many\nmany\nmany\n\nmany breaks.\n";

	while (find_break(string, &line) == 1)
	{
		printf("\nLINE\n(%s)\n", line);
		free(line);
	}

	return (0);
}