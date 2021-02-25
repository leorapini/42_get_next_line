#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.c"
#include <strings.h>

/*
int	get_fd(int fd, char **line)
{
	static char	*buffer;
	size_t	size;
	size_t	len_read;
	
	size = 200;
	if (!(buffer = malloc(sizeof(char*) * size + 1)))
		return (1);
	if ((len_read = read(fd, buffer, size)) > 0)
	{
		buffer[len_read] = '\0';
		*line = strndup(buffer, len_read);
		free(buffer);
	}
	else
	{
		len_read = strlen(buffer);
		*line = strndup(buffer, len_read);
		free(buffer);	
	}
	return (1);
}
*/
int     main(void)
{
	char    *line;
	int     fd = open("test.txt", O_RDONLY);
	int	print;

	print = 3;
	if (fd <= 0)
	{
		printf("error\n");
		return (1);
	}
        
	while (print > 0)
	{
		get_next_line(fd, &line);
		printf("Main:\n(%s)\n\n", line);
		print--;
 	}
        if (close(fd) < 0)
        {
                printf("error\n");
                return (1);
	}
        free(line);
        return (0);     
}              
