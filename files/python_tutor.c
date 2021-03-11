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

size_t		find_break(char *buff)
{
	size_t	str_len;
	char	*ltemp;

	str_len = 0;
	while (*buff != '\0')
	{
		if (*buff == '\n')
		{
			ltemp = malloc(sizeof(*ltemp) * (str_len + 1));
			ft_strlcpy(ltemp, buff - str_len, str_len + 1);
			printf("(%s)\n", ltemp);
			str_len = -1;
		}
		str_len++;
		buff++;
	}
	return (0);
}

int	main(void)
{
	char	string[] = "Long string\nmany\nmany\n\nmany breaks.\n";

	while (find_break(string) == 1)
	{
		;
	}

	return (0);
}
