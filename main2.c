#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>


#include "get_next_line.h"

int     main(void)
{
	int     fd;
	char	*line;
	//char	*buffer;
	//int	size;
	//int	len_read;
	
	//size = 50;
	//buffer = malloc(sizeof(*buffer) * size + 1);

	fd = open("test_file1", O_RDONLY);
	//len_read = read(fd, buffer, size);
		

	//printf("fd is %d\n", fd);
	//printf("len_read is %d\n", len_read);

	while (get_next_line(fd, &line) == 1)
	{
		printf("there's something");
		printf("LINE\n(%s)\n", line);
		free(line);
	}	
	close(fd);     
        return (0);     
}              
